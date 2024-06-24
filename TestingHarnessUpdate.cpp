#include <chrono>  
#include <fstream> 
#include <iomanip>
#include <string>


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

