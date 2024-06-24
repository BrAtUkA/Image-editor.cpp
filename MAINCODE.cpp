#include "ImageStone.h"
#include "ImageThreaded.h"
#include <string>

#include <chrono>  
#include <fstream> 
#include <iomanip>
#include <string>

#pragma once

namespace ImageEditor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Text;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{

// ------------------------------------------ CODE START ------------------------------------------
	array<String^>^ files;
	String^ path;
	int currentIndex;
	const int zoomLevel = 100;
	int Zooms = 0;

	//IMAGE BROWSE
		void OpenImg(String^ filePath, bool AI) {
			if (IsImage(filePath)) {

				String^ prompt = promptBox->Text->Replace("\n", " ");
				if (prompt->Length > 100) {
					prompt = prompt->Substring(0, 100) + "...";
				}

				(AI) ? MyForm::Text = "Image Editor - AI Gen - \"" + prompt + "\"       (" + filePath + ")" :
					MyForm::Text = "Image Editor - " + System::IO::Path::GetFileName(filePath) + "      (" + filePath + ")";

				pictureBox1->ImageLocation = filePath;
				path = System::IO::Path::GetDirectoryName(filePath);
				files = System::IO::Directory::GetFiles(path);

				for (int i = 0; i < files->Length; i++) {
					if (files[i] == filePath) {
						currentIndex = i;
						break;
					}
				}

			}
			else {
				MessageBox::Show("Selected file is not an image.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
		private: System::Void openImage_Click(System::Object^ sender, System::EventArgs^ e) {
			if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
				String^ filePath = ofd->FileName;
				OpenImg(filePath, false);

			}
		}

		private: System::Void saveImage_Click(System::Object^ sender, System::EventArgs^ e) {
			if (pictureBox1->Image != nullptr) {

				String^ originalFileName = files[currentIndex];
				String^ editedFileName = System::IO::Path::GetFileNameWithoutExtension(originalFileName) + "_edited" + System::IO::Path::GetExtension(originalFileName);
				sfd->FileName = editedFileName;

				if (sfd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
					String^ savePath = sfd->FileName;
					pictureBox1->Image->Save(savePath);
				}
			}
		}

		private: System::Void closeImage_Click(System::Object^ sender, System::EventArgs^ e) {
			pictureBox1->ImageLocation = "";
			MyForm::Text = "Image Editor";
		}

	//FILE NAVIGATION
		private: System::Void MoveRight_Click(System::Object^ sender, System::EventArgs^ e) {
			if (files != nullptr) {
				do {
					if (currentIndex != files->Length - 1) {
						currentIndex++;
					}
					else {

						break;
					}
				} while (!IsImage(files[currentIndex]));

				MyForm::Text = "Image Editor - " + System::IO::Path::GetFileName(files[currentIndex]) + "      (" + files[currentIndex] + ")";
				pictureBox1->ImageLocation = files[currentIndex];
			}
		}

		private: System::Void MoveLeft_Click(System::Object^ sender, System::EventArgs^ e) {
			if (files != nullptr) {
				do {
					if (currentIndex != 0) {
						currentIndex--;
					}
					else {
						break;
					}
				} while (!IsImage(files[currentIndex]));

				MyForm::Text = "Image Editor - " + System::IO::Path::GetFileName(files[currentIndex]) + "      (" + files[currentIndex] + ")";
				pictureBox1->ImageLocation = files[currentIndex];
			}
		}


	// ZOOM
		private: System::Void zoomIn_Click(System::Object^ sender, System::EventArgs^ e) {
			pictureBox1->Top -= zoomLevel / 2;
			pictureBox1->Left -= zoomLevel / 2;
			pictureBox1->Height += zoomLevel;
			pictureBox1->Width += zoomLevel;
			Zooms++;
		}


		private: System::Void ZoomOut_Click(System::Object^ sender, System::EventArgs^ e) {
			pictureBox1->Top += zoomLevel / 2;
			pictureBox1->Left += zoomLevel / 2;
			pictureBox1->Height -= zoomLevel;
			pictureBox1->Width -= zoomLevel;
			Zooms--;
		}

		private: System::Void zoomReset_Click(System::Object^ sender, System::EventArgs^ e) {
			int newZoom = Zooms;
			if (Zooms > 0) {
				for (int i = 0; i < newZoom; i++) {
					ZoomOut->PerformClick();
				}
			}

			if (Zooms < 0) {
				for (int i = 0; i > newZoom; i--) {
					zoomIn->PerformClick();
				}
			}

			Zooms = 0;
		}


	private: System::Void apply_Click(System::Object^ sender, System::EventArgs^ e) {

		if (files != nullptr && files->Length > 0 && currentIndex >= 0 && currentIndex < files->Length) {
			MyForm::Text = "Applying...";

			String^ originalFilePath = files[currentIndex];
			Bitmap^ originalImage = gcnew Bitmap(originalFilePath);
			pictureBox1->Image = originalImage;

			// ESSENTIALS
				//Contrast
				if (contrastTrack->Value != 100) {
					pictureBox1->Image = SetContrast(gcnew Bitmap(pictureBox1->Image), contrastTrack->Value);
				}

				// Sharpen
				if (sharpTrack->Value != 100) {
					pictureBox1->Image = SharpenImage(gcnew Bitmap(pictureBox1->Image), sharpTrack->Value);
					pictureBox1->Refresh();
				}

				//Bright
				if (brightTrack->Value != 0) {
					pictureBox1->Image = SetBrightness(gcnew Bitmap(pictureBox1->Image), brightTrack->Value);
				}

				//Hue
				if (hueTrack->Value != 0) {
					pictureBox1->Image = AdjustHue(gcnew Bitmap(pictureBox1->Image), hueTrack->Value);
				}

				//Vibrance
				if (vibranceTrack->Value != 0) {
					pictureBox1->Image = AdjustVibrance(gcnew Bitmap(pictureBox1->Image), vibranceTrack->Value);
				}

				//ColorBoost
				if (Rtrack->Value != 20 || Btrack->Value != 20 || Gtrack->Value != 20) {
					pictureBox1->Image = ColorBoost(gcnew Bitmap(pictureBox1->Image), 
														Rtrack->Value, 
														Gtrack->Value, 
														Btrack->Value);
				}

			// EFFECTS & FILTERS
				//Pixelate
				if (pixelateTrack->Value != 1) {
					pictureBox1->Image = PixelateImage(gcnew Bitmap(pictureBox1->Image), pixelateTrack->Value);
				}
				//Posterize
				if (posterTrack->Value != 1) {
					pictureBox1->Image = PosterizeImage(gcnew Bitmap(pictureBox1->Image), posterTrack->Value);
				}
				//Blur
				if (blurTrack->Value != 0) {
					pictureBox1->Image = BlurImage(gcnew Bitmap(pictureBox1->Image), blurTrack->Value);
				}
				//Glitch
				if (glitchTrack->Value != 0) {
					if(exaGlCheck->Checked)
						pictureBox1->Image = ExaGlitchEffect(gcnew Bitmap(pictureBox1->Image), glitchTrack->Value);
					else
						pictureBox1->Image = GlitchEffect(gcnew Bitmap(pictureBox1->Image), glitchTrack->Value);
				}
				//Replace Color
				if (targetColor->Text->Length == 6 && repColor->Text->Length == 6) {
					pictureBox1->Image = ReplaceColor(gcnew Bitmap(pictureBox1->Image), targetColor->Text, repColor->Text, threshTrack->Value, interpCheck->Checked);
				}

				//CheckBox FX
					if (sepiaCheck->Checked) 
						pictureBox1->Image = SepiaTone(gcnew Bitmap(pictureBox1->Image));
					if (grayscaleCheck->Checked) 
						pictureBox1->Image = ConvertToGrayScale(gcnew Bitmap(pictureBox1->Image));
					if (invertCheck->Checked) 
						pictureBox1->Image = InvertColors(gcnew Bitmap(pictureBox1->Image));
					if (edgeCheck->Checked)
						pictureBox1->Image = ApplyEdgeDetection(gcnew Bitmap(pictureBox1->Image));
					if (embossCheck->Checked)
						pictureBox1->Image = EmbossImage(gcnew Bitmap(pictureBox1->Image));
					if (oilCheck->Checked)
						pictureBox1->Image = ApplyOilPaintingEffect(gcnew Bitmap(pictureBox1->Image));


			MyForm::Text = "Image Editor - " + System::IO::Path::GetFileName(originalFilePath) + "      (" + originalFilePath + ")";
		}
	}

	private: System::Void reset_Click(System::Object^ sender, System::EventArgs^ e) {
		if (sidePanel->Visible) {
			contrastTrack->Value = 100;
			contrastVal->Text = "100";

			brightTrack->Value = 0;
			brightVal->Text = "100";

			sharpTrack->Value = 100;
			sharpVal->Text = "0";

			vibranceTrack->Value = 0;
			vibranceVal->Text = "0";

			hueTrack->Value = 0;
			hueVal->Text = "0�";

			Rtrack->Value = 20;
			rVal->Text = "0";
			Gtrack->Value = 20;
			gVal->Text = "0";
			Btrack->Value = 20;
			bVal->Text = "0";
		}

		if (sidePanel2->Visible) {
			pixelateTrack->Value = 1;
			pixelateVal->Text = "1";

			posterTrack->Value = 1;
			posterVal->Text = "1";

			glitchTrack->Value = 0;
			glitchVal->Text = "0";
			exaGlCheck->Checked = false;

			blurTrack->Value = 0;
			blurVal->Text = "0";

			targetColor->Text = "Hex";
			repColor->Text = "Hex";
			targetColor->ForeColor = Color::FromArgb(155, 90, 199);
			repColor->ForeColor = Color::FromArgb(155, 90, 199);
			threshTrack->Value = 0;
			threshVal->Text = "0";
			interpCheck->Checked = false;

			// Commented because changing triggers the CheckChanged event potentially modifying the image in an unwanted way.

			// grayscaleCheck->Checked = false;
			// invertCheck->Checked = false;
			// sepiaCheck->Checked = false;
			// edgeCheck->Checked = false;
			// embossCheck->Checked = false;
		}

	}





	//FX CheckBoxes:
		void checkChanged(Windows::Forms::CheckBox^ check, Bitmap^ (*func)(Bitmap^)) {
			if (files != nullptr && files->Length > 0 && currentIndex >= 0 && currentIndex < files->Length) {
				if (check->Checked) {
					pictureBox1->Image = func(gcnew Bitmap(pictureBox1->Image));
				}
				else {
					System::EventArgs^ e;
					System::Object^ sender;
					apply_Click(sender, e);
				}
			}

		}

		private: System::Void grayscaleCheck_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			checkChanged(grayscaleCheck, ConvertToGrayScale);
		}

		private: System::Void invertCheck_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			checkChanged(invertCheck, InvertColors);
		}

		private: System::Void sepiaCheck_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			checkChanged(sepiaCheck, SepiaTone);
		}

		private: System::Void edgeCheck_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			checkChanged(edgeCheck, ApplyEdgeDetection);
		}

		private: System::Void embossCheck_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			checkChanged(embossCheck, EmbossImage);
		}

		private: System::Void oilCheck_CheckedChanged(System::Object^ sender, System::EventArgs^ e) {
			checkChanged(oilCheck, ApplyOilPaintingEffect);
		}

	//Label Value Updates:
		//Essentials:
			private: System::Void contrastTrack_Scroll(System::Object^ sender, System::EventArgs^ e) {
				int contrast = contrastTrack->Value - 100;
				contrastVal->Text = contrast.ToString();
			}

			private: System::Void brightTrack_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
				int bright = brightTrack->Value + 100;
				brightVal->Text = bright.ToString();
			}

			private: System::Void sharpTrack_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
				double sharp = sharpTrack->Value;
				sharp -= 100;
				sharp /= 100;

				sharpVal->Text = sharp.ToString();
			}
			private: System::Void vibranceTrack_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
				float vibrance = vibranceTrack->Value / 10.0;
				vibranceVal->Text = vibrance.ToString();
			}

			private: System::Void hueTrack_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
				hueVal->Text = hueTrack->Value.ToString() + "�";
			}

			private: System::Void Rtrack_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
				rVal->Text = ((Rtrack->Value / 20.0)-1).ToString();
			}

			private: System::Void Gtrack_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
				gVal->Text = ((Gtrack->Value / 20.0)-1).ToString();
			}
			private: System::Void Btrack_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
				bVal->Text = ((Btrack->Value / 20.0)-1).ToString();
			} 



	//Effects & Filters:
		private: System::Void pixelateTrack_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
			int blockSize = pixelateTrack->Value;
			pixelateVal->Text = blockSize.ToString();

		}
		private: System::Void posterTrack_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
			posterVal->Text = posterTrack->Value.ToString();
		}
		private: System::Void blurTrack_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
			blurVal->Text = blurTrack->Value.ToString();
		}
		private: System::Void glitchTrack_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
			glitchVal->Text = glitchTrack->Value.ToString();
		}
		private: System::Void threshTrack_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
			float thresh = threshTrack->Value / 2.5;
			threshVal->Text = thresh.ToString();
		}



	//Artificial Intelligence
		String^ GenerateRandomString(int length) {
				String^ chars = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
				Random^ random = gcnew Random();
				StringBuilder^ result = gcnew StringBuilder(length);

				for (int i = 0; i < length; i++) {
					result->Append(chars[random->Next(chars->Length)]);
				}
				return result->ToString();
		}

		private: System::Void generate_Click(System::Object^ sender, System::EventArgs^ e) {
			String^ promp = promptBox->Text->Replace("\n", " ");
			if (promp->Length > 100)
				promp = promp->Substring(0, 100) + "...";

			MyForm::Text = "Generating...     \"" + promp + "\"";

			pictureBox1->Image = GenerateImageFromText(promp, modelBox->SelectedItem->ToString());

			String^ imageGenPath = Path::GetTempPath() + "ImageGen";
			Directory::CreateDirectory(imageGenPath);

			String^ savePath = Path::Combine(imageGenPath, GenerateRandomString(8) + ".png");
			pictureBox1->Image->Save(savePath);

			OpenImg(savePath, true);
		}


		private: System::Void promptBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
			if (promptBox->Text == "") {
				generate->Enabled = false;
				generate->BackColor = Color::FromArgb(134, 107, 135);
			}
			else if(promptBox->Text->Length >= 3) {
				generate->Enabled = true;
				generate->BackColor = Color::FromArgb(94, 56, 114);

			}
		}



	//Page Navigation
		private: System::Void pageLeft_Click(System::Object^ sender, System::EventArgs^ e) {
			sidePanel2->Location = sidePanel->Location;
			sidePanel->Visible = false;
			sidePanel2->Visible = true;
		}

		private: System::Void pageRight2_Click(System::Object^ sender, System::EventArgs^ e) {
			sidePanel2->Visible = false;
			sidePanel->Visible = true;
		}

		private: System::Void pageLeft2_Click(System::Object^ sender, System::EventArgs^ e) {
			sidePanel3->Location = sidePanel->Location;
			sidePanel2->Visible = false;
			sidePanel3->Visible = true;
		}
		private: System::Void pageRight3_Click(System::Object^ sender, System::EventArgs^ e) {
			sidePanel3->Visible = false;
			sidePanel2->Visible = true;
		}



	//UI elements Behaviour customization
		// Validate HEX
			private: System::Void targetColor_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
				if (System::Char::IsControl(e->KeyChar)) {
					return;
				}

				// (0-9, A-F, a-f)
				bool isHexDigit = (e->KeyChar >= '0' && e->KeyChar <= '9') ||
					(e->KeyChar >= 'A' && e->KeyChar <= 'F') ||
					(e->KeyChar >= 'a' && e->KeyChar <= 'f');

				if (!isHexDigit) {
					e->Handled = true;
				}

				// Change text color to white when typing
				targetColor->ForeColor = Color::FromArgb(225, 206, 238);
			}

			private: System::Void repColor_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e) {
				if (System::Char::IsControl(e->KeyChar)) {
					return;
				}

				// (0-9, A-F, a-f)
				bool isHexDigit = (e->KeyChar >= '0' && e->KeyChar <= '9') ||
					(e->KeyChar >= 'A' && e->KeyChar <= 'F') ||
					(e->KeyChar >= 'a' && e->KeyChar <= 'f');

				if (!isHexDigit) {
					e->Handled = true;
				}

				// Change text color to white when typing
				repColor->ForeColor = Color::FromArgb(225, 206, 238);
			}

		//Remove "Hex" and swap colors accordingly.
			private: System::Void targetColor_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
				if (targetColor->Text == "Hex") {
					targetColor->Text = "";
				}
				targetColor->ForeColor = Color::FromArgb(225, 206, 238);
			}

			private: System::Void repColor_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
				if (repColor->Text == "Hex") {
					repColor->Text = "";
				}
				repColor->ForeColor = Color::FromArgb(225, 206, 238);
			}

			private: System::Void targetColor_Leave(System::Object^ sender, System::EventArgs^ e) {
				if (targetColor->Text == "") {
					targetColor->Text = "Hex";
					targetColor->ForeColor = Color::FromArgb(155, 90, 199);
				}
			}

			private: System::Void repColor_Leave(System::Object^ sender, System::EventArgs^ e) {
				if (repColor->Text == "") {
					repColor->Text = "Hex";
					repColor->ForeColor = Color::FromArgb(155, 90, 199);
				}
			}

			private: System::Void targetColor_TextChanged(System::Object^ sender, System::EventArgs^ e) {
				if (targetColor->Text->Length == 0 || targetColor->Text == "Hex") {
					targetColor->ForeColor = Color::FromArgb(155, 90, 199);
				}
				else {
					targetColor->ForeColor = Color::FromArgb(225, 206, 238);
				}
			}

			private: System::Void repColor_TextChanged(System::Object^ sender, System::EventArgs^ e) {
				if (repColor->Text->Length == 0 || repColor->Text == "Hex") {
					repColor->ForeColor = Color::FromArgb(155, 90, 199);
				}
				else {
					repColor->ForeColor = Color::FromArgb(225, 206, 238);
				}
			}

		//Remove Highlight from model select
		private: System::Void modelBox_DropDown(System::Object^ sender, System::EventArgs^ e) {
			modelBox->Select(modelBox->Text->Length, 0);
		}

		//Update Model Details
		private: System::Void modelBox_SelectionChangeCommitted(System::Object^ sender, System::EventArgs^ e) {
			switch (modelBox->SelectedIndex) {
				case 0:
					modelDetails->Text = "SDXL-v1.0 is a newer SD model\nto mostly generate dream-like\nand stylized images, also being\na little better at text."; break;
				case 1:
					modelDetails->Text = "Stable-Diffusion v2.1 is capable\nof generating good quality\nphoto-realistic images."; break;

		//		case 2:
		//			modelDetails->Text = "SD-Cascade is the newest SD\nmodel based on SD3 capable of\ngenerating proper text."; break;//-----\
		//		case 3:																													   // |-> These Two models often return 503 because of less workers on the api endpoint.
		//			modelDetails->Text = "Anything-v4 is a SD based model\nfocused on generating anime\nstyle images."; break;//-------------/
			}
		}




	// ===============================<TESTING>=================================

		int slow, ok, laggy;
		bool total = false;

		void WriteToLog(std::string funcName, std::chrono::high_resolution_clock::time_point start, std::chrono::high_resolution_clock::time_point end) {
			auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
			double durationSeconds = duration.count() / 1000.0;  

			std::ofstream outfile("ImageEditor_Logs.txt", std::ios_base::app);
			outfile << std::left << std::setw(20) << funcName << ": "
				<< std::fixed << std::setprecision(2) << durationSeconds << " second(s) ";

			if (total) {
				outfile.close();
				return;
			}

			if (duration.count() > 2500) {
				outfile << "LAGGY" << std::endl;
				laggy++;
			}
			else if (duration.count() > 1500) {
				outfile << "SLOW" << std::endl;
				slow++;
			}
			else {
				outfile << "OK" << std::endl;
				ok++;
			}
			outfile.close();
		}

		private: System::Void test_Click(System::Object^ sender, System::EventArgs^ e) {
			System::Windows::Forms::DialogResult result = MessageBox::Show("Run performance tests? This may take a while.", "Confirmation", MessageBoxButtons::OKCancel, MessageBoxIcon::Information);

			if (result != System::Windows::Forms::DialogResult::OK) {
				return;
			}
			if (!System::IO::File::Exists("sample.png")) {
				MessageBox::Show("The sample image 'sample.png' was not found in the same directory as the executable.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return; 
			}

			Bitmap^ image = gcnew Bitmap("sample.png");
			pictureBox1->Image = image;
			MyForm::Text = "Testing...";

			std::ofstream outfile("ImageEditor_Logs.txt");
			outfile.close();

			outfile.open("ImageEditor_Logs.txt", std::ios_base::app);
			outfile << "====================ESSENTIALS=====================\n" << std::endl;
			outfile.close();

			auto Totalstart = std::chrono::high_resolution_clock::now();

			auto start = std::chrono::high_resolution_clock::now();
			SetContrast(image, 120);
			auto end = std::chrono::high_resolution_clock::now();
			WriteToLog("SetContrast", start, end);

			start = std::chrono::high_resolution_clock::now();
			SharpenImage(image, 180);
			end = std::chrono::high_resolution_clock::now();
			WriteToLog("SharpenImage", start, end);

			start = std::chrono::high_resolution_clock::now();
			SetBrightness(image, 40);
			end = std::chrono::high_resolution_clock::now();
			WriteToLog("SetBrightness", start, end);

			start = std::chrono::high_resolution_clock::now();
			AdjustHue(image, 90);
			end = std::chrono::high_resolution_clock::now();
			WriteToLog("AdjustHue", start, end);

			start = std::chrono::high_resolution_clock::now();
			AdjustVibrance(image, 80);
			end = std::chrono::high_resolution_clock::now();
			WriteToLog("AdjustVibrance", start, end);

			start = std::chrono::high_resolution_clock::now();
			ColorBoost(image, 30, 60, 10);
			end = std::chrono::high_resolution_clock::now();
			WriteToLog("ColorBoost", start, end);

			outfile.open("ImageEditor_Logs.txt", std::ios_base::app);
			outfile << "\n====================EFFECTS=====================\n" << std::endl;
			outfile.close();

			start = std::chrono::high_resolution_clock::now();
			PixelateImage(image, 4);
			end = std::chrono::high_resolution_clock::now();
			WriteToLog("Pixelate", start, end);

			start = std::chrono::high_resolution_clock::now();
			PosterizeImage(image, 3);
			end = std::chrono::high_resolution_clock::now();
			WriteToLog("Posterize", start, end);

			start = std::chrono::high_resolution_clock::now();
			BlurImage(image, 5);
			end = std::chrono::high_resolution_clock::now();
			WriteToLog("Blur", start, end);

			start = std::chrono::high_resolution_clock::now();
			GlitchEffect(image, 10);
			end = std::chrono::high_resolution_clock::now();
			WriteToLog("Glitch", start, end);

			start = std::chrono::high_resolution_clock::now();
			ExaGlitchEffect(image, 10);
			end = std::chrono::high_resolution_clock::now();
			WriteToLog("   |_ Exaggerated", start, end);

			start = std::chrono::high_resolution_clock::now();
			ReplaceColor(image, "FFFFFF", "000000", 128, false);
			end = std::chrono::high_resolution_clock::now();
			WriteToLog("ColorReplace", start, end);

			start = std::chrono::high_resolution_clock::now();
			ReplaceColor(image, "FFFFFF", "000000", 128, true);
			end = std::chrono::high_resolution_clock::now();
			WriteToLog("   |_ Interpolated", start, end);

			start = std::chrono::high_resolution_clock::now();
			SepiaTone(image);
			end = std::chrono::high_resolution_clock::now();
			WriteToLog("Sepia", start, end);

			start = std::chrono::high_resolution_clock::now();
			ConvertToGrayScale(image);
			end = std::chrono::high_resolution_clock::now();
			WriteToLog("Grayscale", start, end);

			start = std::chrono::high_resolution_clock::now();
			InvertColors(image);
			end = std::chrono::high_resolution_clock::now();
			WriteToLog("Invert", start, end);

			start = std::chrono::high_resolution_clock::now();
			ApplyEdgeDetection(image);
			end = std::chrono::high_resolution_clock::now();
			WriteToLog("Edge Detection", start, end);

			start = std::chrono::high_resolution_clock::now();
			EmbossImage(image);
			end = std::chrono::high_resolution_clock::now();
			WriteToLog("Emboss", start, end);

			start = std::chrono::high_resolution_clock::now();
			ApplyOilPaintingEffect(image);
			end = std::chrono::high_resolution_clock::now();
			WriteToLog("Oil Painting", start, end);

			auto Totalend = std::chrono::high_resolution_clock::now();
			total = true;
			outfile.open("ImageEditor_Logs.txt", std::ios_base::app);
			outfile << "\n====================OVERALL=====================\n" << std::endl;
			WriteToLog("Total Time", Totalstart, Totalend);
			outfile << "\n\nLaggy: " << laggy << "/19"<<std::endl;
			outfile << "Slow: " << slow << "/19" << std::endl;
			outfile << "Ok: " << ok << "/19" << std::endl;
			outfile.close();

			pictureBox1->Image = nullptr;
			MyForm::Text = "Image Editor";
		}
};
}
