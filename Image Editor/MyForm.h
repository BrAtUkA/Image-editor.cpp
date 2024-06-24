#include "ImageProcessing.h"
#include "ImageThreaded.h"
#include <string>

#include <chrono>  
#include <fstream> 
#include <iomanip>
#include <string>

#pragma once

// Reference for InputBox
#using <Microsoft.VisualBasic.dll>

namespace ImageEditor {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Text;
	using namespace System::IO;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public: System::Windows::Forms::Button^ generate;
	public: System::Windows::Forms::RichTextBox^ promptBox;
	public: System::Windows::Forms::Label^ brightVal;
	public: System::Windows::Forms::TrackBar^ brightTrack;
	public: System::Windows::Forms::Label^ label6;
	public: System::Windows::Forms::Label^ pixelateVal;
	public: System::Windows::Forms::TrackBar^ pixelateTrack;
	public: System::Windows::Forms::Label^ label5;
	public: System::Windows::Forms::Label^ sharpVal;
	public: System::Windows::Forms::TrackBar^ sharpTrack;
	public: System::Windows::Forms::Label^ Sharpness;
	public: System::Windows::Forms::CheckBox^ grayscaleCheck;
	public: System::Windows::Forms::Button^ resetB;
	public: System::Windows::Forms::Label^ contrastVal;
	public: System::Windows::Forms::TrackBar^ contrastTrack;
	public: System::Windows::Forms::Label^ label3;
	public: System::Windows::Forms::Panel^ divider;
	private: System::Windows::Forms::Panel^ pomptPad;
	private: System::Windows::Forms::Panel^ sidePanel2;
	public: System::Windows::Forms::Panel^ panel2;
	public: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::Panel^ sidePanel3;
	public: System::Windows::Forms::Panel^ panel4;
	public: System::Windows::Forms::Label^ label4;
	public: System::Windows::Forms::Button^ pageLeft;
	public: System::Windows::Forms::Label^ label7;
	public: System::Windows::Forms::Button^ pageRight2;
	public: System::Windows::Forms::Label^ label8;
	public: System::Windows::Forms::Button^ pageLeft2;
	public: System::Windows::Forms::Button^ pageRight3;
	public: System::Windows::Forms::Label^ label9;
	public: System::Windows::Forms::Label^ vibranceVal;
	public: System::Windows::Forms::Label^ label11;
	public: System::Windows::Forms::TrackBar^ vibranceTrack;
	public: System::Windows::Forms::Label^ hueVal;
	public: System::Windows::Forms::Label^ label13;
	public: System::Windows::Forms::TrackBar^ hueTrack;
	public: System::Windows::Forms::Label^ label10;
	public: System::Windows::Forms::Label^ label16;
	public: System::Windows::Forms::Label^ label15;
	public: System::Windows::Forms::Label^ label14;
	public: System::Windows::Forms::TrackBar^ Btrack;
	public: System::Windows::Forms::TrackBar^ Gtrack;
	public: System::Windows::Forms::TrackBar^ Rtrack;
	public: System::Windows::Forms::Label^ bVal;
	public: System::Windows::Forms::Label^ gVal;
	public: System::Windows::Forms::Label^ rVal;
	public: System::Windows::Forms::Button^ apply1;
	public: System::Windows::Forms::CheckBox^ invertCheck;
	public: System::Windows::Forms::CheckBox^ sepiaCheck;
	public: System::Windows::Forms::Label^ label17;
	public: System::Windows::Forms::TrackBar^ posterTrack;
	public: System::Windows::Forms::Label^ posterVal;
	public: System::Windows::Forms::Button^ apply2;
	public: System::Windows::Forms::CheckBox^ edgeCheck;
	public: System::Windows::Forms::CheckBox^ embossCheck;
	public: System::Windows::Forms::Label^ label18;
	public: System::Windows::Forms::TrackBar^ blurTrack;
	public: System::Windows::Forms::Label^ blurVal;
	public: System::Windows::Forms::Label^ label19;
	public: System::Windows::Forms::TrackBar^ glitchTrack;
	public: System::Windows::Forms::Label^ glitchVal;
	public: System::Windows::Forms::CheckBox^ exaGlCheck;
	public: System::Windows::Forms::Label^ label20;
	public: System::Windows::Forms::RichTextBox^ targetColor;
	private: System::Windows::Forms::Panel^ txtMargin;
	public: System::Windows::Forms::RichTextBox^ repColor;
	private: System::Windows::Forms::Panel^ txtMargin2;
	public: System::Windows::Forms::Label^ label23;
	public: System::Windows::Forms::Label^ label22;
	public: System::Windows::Forms::CheckBox^ interpCheck;
	public: System::Windows::Forms::Label^ label21;
	public: System::Windows::Forms::TrackBar^ threshTrack;
	public: System::Windows::Forms::Label^ label25;
	public: System::Windows::Forms::Label^ label24;
	public: System::Windows::Forms::Label^ threshVal;
	public: System::Windows::Forms::CheckBox^ oilCheck;
	private: System::Windows::Forms::ComboBox^ modelBox;
	public: System::Windows::Forms::Label^ label26;
	public: System::Windows::Forms::Label^ label27;
	public: System::Windows::Forms::Label^ modelDetails;
	public: System::Windows::Forms::Label^ label28;
	public: System::Windows::Forms::Label^ label29;
	public: System::Windows::Forms::Label^ label31;
	public: System::Windows::Forms::Label^ label30;
	public: System::Windows::Forms::Label^ label32;
	public: System::Windows::Forms::Panel^ tipSeperator;
	public: System::Windows::Forms::Button^ test;

	public:

	public:

	public:

	public: System::Windows::Forms::Label^ label2;
	public:
		MyForm(void)
		{
			InitializeComponent();
			pageLeft->FlatAppearance->BorderColor = sidePanel->BackColor;

			pageLeft2->FlatAppearance->BorderColor = sidePanel->BackColor;
			pageRight2->FlatAppearance->BorderColor = sidePanel->BackColor;

			pageRight3->FlatAppearance->BorderColor = sidePanel->BackColor;
			generate->FlatAppearance->BorderColor = sidePanel->BackColor;

			apply1->FlatAppearance->BorderColor = sidePanel->BackColor;
			apply2->FlatAppearance->BorderColor = sidePanel->BackColor;

			modelBox->SelectedIndex = 0;
			modelBox->DropDownStyle = ComboBoxStyle::DropDownList;

			modelDetails->Text = "SDXL-v1.0 is a newer SD model\nto mostly generate dream-like\nand stylized images, also being\na little better at text.";
			
			// Enable drag and drop
			this->AllowDrop = true;
			this->DragEnter += gcnew DragEventHandler(this, &MyForm::Form_DragEnter);
			this->DragDrop += gcnew DragEventHandler(this, &MyForm::Form_DragDrop);
			
			// Enable keyboard shortcuts
			this->KeyPreview = true;
			this->KeyDown += gcnew KeyEventHandler(this, &MyForm::Form_KeyDown);
			
			// Initialize undo/redo
			ImageCache::Initialize();
			//
			//TODO: Add the constructor code here
			//
		}
	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^ ToolBar;
	private: System::Windows::Forms::Panel^ workspace;
	public: System::Windows::Forms::PictureBox^ pictureBox1;
	private: System::Windows::Forms::Button^ zoomIn;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ MoveRight;
	private: System::Windows::Forms::Button^ MoveLeft;
	private: System::Windows::Forms::Button^ closeImage;
	private: System::Windows::Forms::Button^ openImage;
	private: System::Windows::Forms::Button^ zoomReset;
	private: System::Windows::Forms::Button^ ZoomOut;
	private: System::Windows::Forms::OpenFileDialog^ ofd;
	private: System::Windows::Forms::Button^ saveImage;
	private: System::Windows::Forms::SaveFileDialog^ sfd;
	private: System::Windows::Forms::Panel^ sidePanel;

		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->ToolBar = (gcnew System::Windows::Forms::Panel());
			this->test = (gcnew System::Windows::Forms::Button());
			this->saveImage = (gcnew System::Windows::Forms::Button());
			this->closeImage = (gcnew System::Windows::Forms::Button());
			this->openImage = (gcnew System::Windows::Forms::Button());
			this->zoomReset = (gcnew System::Windows::Forms::Button());
			this->ZoomOut = (gcnew System::Windows::Forms::Button());
			this->zoomIn = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->resetB = (gcnew System::Windows::Forms::Button());
			this->MoveRight = (gcnew System::Windows::Forms::Button());
			this->MoveLeft = (gcnew System::Windows::Forms::Button());
			this->workspace = (gcnew System::Windows::Forms::Panel());
			this->sidePanel2 = (gcnew System::Windows::Forms::Panel());
			this->oilCheck = (gcnew System::Windows::Forms::CheckBox());
			this->threshVal = (gcnew System::Windows::Forms::Label());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->targetColor = (gcnew System::Windows::Forms::RichTextBox());
			this->txtMargin = (gcnew System::Windows::Forms::Panel());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->interpCheck = (gcnew System::Windows::Forms::CheckBox());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->repColor = (gcnew System::Windows::Forms::RichTextBox());
			this->txtMargin2 = (gcnew System::Windows::Forms::Panel());
			this->exaGlCheck = (gcnew System::Windows::Forms::CheckBox());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->glitchTrack = (gcnew System::Windows::Forms::TrackBar());
			this->glitchVal = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->blurTrack = (gcnew System::Windows::Forms::TrackBar());
			this->blurVal = (gcnew System::Windows::Forms::Label());
			this->embossCheck = (gcnew System::Windows::Forms::CheckBox());
			this->edgeCheck = (gcnew System::Windows::Forms::CheckBox());
			this->apply2 = (gcnew System::Windows::Forms::Button());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->posterTrack = (gcnew System::Windows::Forms::TrackBar());
			this->posterVal = (gcnew System::Windows::Forms::Label());
			this->sepiaCheck = (gcnew System::Windows::Forms::CheckBox());
			this->invertCheck = (gcnew System::Windows::Forms::CheckBox());
			this->pageRight2 = (gcnew System::Windows::Forms::Button());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->pageLeft2 = (gcnew System::Windows::Forms::Button());
			this->panel2 = (gcnew System::Windows::Forms::Panel());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->grayscaleCheck = (gcnew System::Windows::Forms::CheckBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->pixelateTrack = (gcnew System::Windows::Forms::TrackBar());
			this->pixelateVal = (gcnew System::Windows::Forms::Label());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->threshTrack = (gcnew System::Windows::Forms::TrackBar());
			this->sidePanel = (gcnew System::Windows::Forms::Panel());
			this->apply1 = (gcnew System::Windows::Forms::Button());
			this->bVal = (gcnew System::Windows::Forms::Label());
			this->gVal = (gcnew System::Windows::Forms::Label());
			this->rVal = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->Btrack = (gcnew System::Windows::Forms::TrackBar());
			this->Gtrack = (gcnew System::Windows::Forms::TrackBar());
			this->Rtrack = (gcnew System::Windows::Forms::TrackBar());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->hueVal = (gcnew System::Windows::Forms::Label());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->hueTrack = (gcnew System::Windows::Forms::TrackBar());
			this->vibranceVal = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->vibranceTrack = (gcnew System::Windows::Forms::TrackBar());
			this->sharpVal = (gcnew System::Windows::Forms::Label());
			this->Sharpness = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->pageLeft = (gcnew System::Windows::Forms::Button());
			this->brightVal = (gcnew System::Windows::Forms::Label());
			this->brightTrack = (gcnew System::Windows::Forms::TrackBar());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->sharpTrack = (gcnew System::Windows::Forms::TrackBar());
			this->contrastVal = (gcnew System::Windows::Forms::Label());
			this->contrastTrack = (gcnew System::Windows::Forms::TrackBar());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->divider = (gcnew System::Windows::Forms::Panel());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->generate = (gcnew System::Windows::Forms::Button());
			this->promptBox = (gcnew System::Windows::Forms::RichTextBox());
			this->pomptPad = (gcnew System::Windows::Forms::Panel());
			this->ofd = (gcnew System::Windows::Forms::OpenFileDialog());
			this->sfd = (gcnew System::Windows::Forms::SaveFileDialog());
			this->sidePanel3 = (gcnew System::Windows::Forms::Panel());
			this->tipSeperator = (gcnew System::Windows::Forms::Panel());
			this->label32 = (gcnew System::Windows::Forms::Label());
			this->label31 = (gcnew System::Windows::Forms::Label());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->modelDetails = (gcnew System::Windows::Forms::Label());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->modelBox = (gcnew System::Windows::Forms::ComboBox());
			this->pageRight3 = (gcnew System::Windows::Forms::Button());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->panel4 = (gcnew System::Windows::Forms::Panel());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->ToolBar->SuspendLayout();
			this->workspace->SuspendLayout();
			this->sidePanel2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->glitchTrack))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->blurTrack))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->posterTrack))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pixelateTrack))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->threshTrack))->BeginInit();
			this->sidePanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Btrack))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Gtrack))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Rtrack))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->hueTrack))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->vibranceTrack))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->brightTrack))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->sharpTrack))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->contrastTrack))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			this->sidePanel3->SuspendLayout();
			this->SuspendLayout();
			// 
			// ToolBar
			// 
			this->ToolBar->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(7)), static_cast<System::Int32>(static_cast<System::Byte>(2)),
				static_cast<System::Int32>(static_cast<System::Byte>(15)));
			this->ToolBar->Controls->Add(this->test);
			this->ToolBar->Controls->Add(this->saveImage);
			this->ToolBar->Controls->Add(this->closeImage);
			this->ToolBar->Controls->Add(this->openImage);
			this->ToolBar->Controls->Add(this->zoomReset);
			this->ToolBar->Controls->Add(this->ZoomOut);
			this->ToolBar->Controls->Add(this->zoomIn);
			this->ToolBar->Controls->Add(this->label1);
			this->ToolBar->Controls->Add(this->resetB);
			this->ToolBar->Controls->Add(this->MoveRight);
			this->ToolBar->Controls->Add(this->MoveLeft);
			this->ToolBar->Dock = System::Windows::Forms::DockStyle::Bottom;
			this->ToolBar->Location = System::Drawing::Point(0, 724);
			this->ToolBar->Name = L"ToolBar";
			this->ToolBar->Size = System::Drawing::Size(1590, 91);
			this->ToolBar->TabIndex = 0;
			// 
			// test
			// 
			this->test->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(189)), static_cast<System::Int32>(static_cast<System::Byte>(165)),
				static_cast<System::Int32>(static_cast<System::Byte>(231)));
			this->test->Cursor = System::Windows::Forms::Cursors::Default;
			this->test->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->test->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->test->ForeColor = System::Drawing::Color::Black;
			this->test->Location = System::Drawing::Point(772, 31);
			this->test->Name = L"test";
			this->test->Size = System::Drawing::Size(56, 32);
			this->test->TabIndex = 93;
			this->test->Text = L"Test";
			this->test->UseVisualStyleBackColor = false;
			this->test->Click += gcnew System::EventHandler(this, &MyForm::test_Click);
			// 
			// saveImage
			// 
			this->saveImage->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F));
			this->saveImage->Location = System::Drawing::Point(1495, 22);
			this->saveImage->Name = L"saveImage";
			this->saveImage->Size = System::Drawing::Size(81, 47);
			this->saveImage->TabIndex = 9;
			this->saveImage->Text = L"Save";
			this->saveImage->UseVisualStyleBackColor = true;
			this->saveImage->Click += gcnew System::EventHandler(this, &MyForm::saveImage_Click);
			// 
			// closeImage
			// 
			this->closeImage->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F));
			this->closeImage->Location = System::Drawing::Point(1177, 23);
			this->closeImage->Name = L"closeImage";
			this->closeImage->Size = System::Drawing::Size(93, 47);
			this->closeImage->TabIndex = 8;
			this->closeImage->Text = L"Close";
			this->closeImage->UseVisualStyleBackColor = true;
			this->closeImage->Click += gcnew System::EventHandler(this, &MyForm::closeImage_Click);
			// 
			// openImage
			// 
			this->openImage->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->openImage->Location = System::Drawing::Point(1083, 23);
			this->openImage->Name = L"openImage";
			this->openImage->Size = System::Drawing::Size(93, 47);
			this->openImage->TabIndex = 7;
			this->openImage->Text = L"Open";
			this->openImage->UseVisualStyleBackColor = true;
			this->openImage->Click += gcnew System::EventHandler(this, &MyForm::openImage_Click);
			// 
			// zoomReset
			// 
			this->zoomReset->Font = (gcnew System::Drawing::Font(L"Segoe UI Black", 12.75F, System::Drawing::FontStyle::Bold));
			this->zoomReset->Location = System::Drawing::Point(1000, 23);
			this->zoomReset->Name = L"zoomReset";
			this->zoomReset->Size = System::Drawing::Size(41, 47);
			this->zoomReset->TabIndex = 6;
			this->zoomReset->Text = L"=";
			this->zoomReset->UseVisualStyleBackColor = true;
			this->zoomReset->Click += gcnew System::EventHandler(this, &MyForm::zoomReset_Click);
			// 
			// ZoomOut
			// 
			this->ZoomOut->Font = (gcnew System::Drawing::Font(L"Segoe UI Black", 12.75F, System::Drawing::FontStyle::Bold));
			this->ZoomOut->Location = System::Drawing::Point(953, 23);
			this->ZoomOut->Name = L"ZoomOut";
			this->ZoomOut->Size = System::Drawing::Size(41, 47);
			this->ZoomOut->TabIndex = 5;
			this->ZoomOut->Text = L"-";
			this->ZoomOut->UseVisualStyleBackColor = true;
			this->ZoomOut->Click += gcnew System::EventHandler(this, &MyForm::ZoomOut_Click);
			// 
			// zoomIn
			// 
			this->zoomIn->Font = (gcnew System::Drawing::Font(L"Segoe UI Black", 12.75F, System::Drawing::FontStyle::Bold));
			this->zoomIn->Location = System::Drawing::Point(906, 23);
			this->zoomIn->Name = L"zoomIn";
			this->zoomIn->Size = System::Drawing::Size(41, 47);
			this->zoomIn->TabIndex = 4;
			this->zoomIn->Text = L"+";
			this->zoomIn->UseVisualStyleBackColor = true;
			this->zoomIn->Click += gcnew System::EventHandler(this, &MyForm::zoomIn_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12.25F));
			this->label1->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label1->Location = System::Drawing::Point(845, 36);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(55, 20);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Zoom:";
			// 
			// resetB
			// 
			this->resetB->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->resetB->Location = System::Drawing::Point(1408, 22);
			this->resetB->Name = L"resetB";
			this->resetB->Size = System::Drawing::Size(81, 47);
			this->resetB->TabIndex = 60;
			this->resetB->Text = L"Reset";
			this->resetB->UseVisualStyleBackColor = true;
			this->resetB->Click += gcnew System::EventHandler(this, &MyForm::reset_Click);
			// 
			// MoveRight
			// 
			this->MoveRight->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.25F));
			this->MoveRight->Location = System::Drawing::Point(85, 24);
			this->MoveRight->Name = L"MoveRight";
			this->MoveRight->Size = System::Drawing::Size(57, 47);
			this->MoveRight->TabIndex = 2;
			this->MoveRight->Text = L">";
			this->MoveRight->UseVisualStyleBackColor = true;
			this->MoveRight->Click += gcnew System::EventHandler(this, &MyForm::MoveRight_Click);
			// 
			// MoveLeft
			// 
			this->MoveLeft->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10.25F));
			this->MoveLeft->Location = System::Drawing::Point(22, 24);
			this->MoveLeft->Name = L"MoveLeft";
			this->MoveLeft->Size = System::Drawing::Size(57, 47);
			this->MoveLeft->TabIndex = 1;
			this->MoveLeft->Text = L"<";
			this->MoveLeft->UseVisualStyleBackColor = true;
			this->MoveLeft->Click += gcnew System::EventHandler(this, &MyForm::MoveLeft_Click);
			// 
			// workspace
			// 
			this->workspace->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(17)), static_cast<System::Int32>(static_cast<System::Byte>(12)),
				static_cast<System::Int32>(static_cast<System::Byte>(22)));
			this->workspace->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->workspace->Controls->Add(this->sidePanel2);
			this->workspace->Controls->Add(this->sidePanel);
			this->workspace->Controls->Add(this->pictureBox1);
			this->workspace->Dock = System::Windows::Forms::DockStyle::Fill;
			this->workspace->Location = System::Drawing::Point(0, 0);
			this->workspace->Name = L"workspace";
			this->workspace->Size = System::Drawing::Size(1590, 724);
			this->workspace->TabIndex = 1;
			// 
			// sidePanel2
			// 
			this->sidePanel2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(29)), static_cast<System::Int32>(static_cast<System::Byte>(18)),
				static_cast<System::Int32>(static_cast<System::Byte>(52)));
			this->sidePanel2->Controls->Add(this->oilCheck);
			this->sidePanel2->Controls->Add(this->threshVal);
			this->sidePanel2->Controls->Add(this->label25);
			this->sidePanel2->Controls->Add(this->targetColor);
			this->sidePanel2->Controls->Add(this->txtMargin);
			this->sidePanel2->Controls->Add(this->label23);
			this->sidePanel2->Controls->Add(this->label22);
			this->sidePanel2->Controls->Add(this->interpCheck);
			this->sidePanel2->Controls->Add(this->label21);
			this->sidePanel2->Controls->Add(this->repColor);
			this->sidePanel2->Controls->Add(this->txtMargin2);
			this->sidePanel2->Controls->Add(this->exaGlCheck);
			this->sidePanel2->Controls->Add(this->label20);
			this->sidePanel2->Controls->Add(this->label19);
			this->sidePanel2->Controls->Add(this->glitchTrack);
			this->sidePanel2->Controls->Add(this->glitchVal);
			this->sidePanel2->Controls->Add(this->label18);
			this->sidePanel2->Controls->Add(this->blurTrack);
			this->sidePanel2->Controls->Add(this->blurVal);
			this->sidePanel2->Controls->Add(this->embossCheck);
			this->sidePanel2->Controls->Add(this->edgeCheck);
			this->sidePanel2->Controls->Add(this->apply2);
			this->sidePanel2->Controls->Add(this->label17);
			this->sidePanel2->Controls->Add(this->posterTrack);
			this->sidePanel2->Controls->Add(this->posterVal);
			this->sidePanel2->Controls->Add(this->sepiaCheck);
			this->sidePanel2->Controls->Add(this->invertCheck);
			this->sidePanel2->Controls->Add(this->pageRight2);
			this->sidePanel2->Controls->Add(this->label8);
			this->sidePanel2->Controls->Add(this->pageLeft2);
			this->sidePanel2->Controls->Add(this->panel2);
			this->sidePanel2->Controls->Add(this->label12);
			this->sidePanel2->Controls->Add(this->grayscaleCheck);
			this->sidePanel2->Controls->Add(this->label5);
			this->sidePanel2->Controls->Add(this->pixelateTrack);
			this->sidePanel2->Controls->Add(this->pixelateVal);
			this->sidePanel2->Controls->Add(this->label24);
			this->sidePanel2->Controls->Add(this->threshTrack);
			this->sidePanel2->Location = System::Drawing::Point(975, 0);
			this->sidePanel2->Name = L"sidePanel2";
			this->sidePanel2->Size = System::Drawing::Size(301, 722);
			this->sidePanel2->TabIndex = 2;
			this->sidePanel2->Visible = false;
			// 
			// oilCheck
			// 
			this->oilCheck->AutoSize = true;
			this->oilCheck->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.25F));
			this->oilCheck->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->oilCheck->Location = System::Drawing::Point(174, 522);
			this->oilCheck->Name = L"oilCheck";
			this->oilCheck->Size = System::Drawing::Size(50, 27);
			this->oilCheck->TabIndex = 114;
			this->oilCheck->Text = L"Oil";
			this->oilCheck->UseVisualStyleBackColor = true;
			this->oilCheck->CheckedChanged += gcnew System::EventHandler(this, &MyForm::oilCheck_CheckedChanged);
			// 
			// threshVal
			// 
			this->threshVal->AutoSize = true;
			this->threshVal->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->threshVal->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->threshVal->Location = System::Drawing::Point(239, 395);
			this->threshVal->Name = L"threshVal";
			this->threshVal->Size = System::Drawing::Size(15, 17);
			this->threshVal->TabIndex = 113;
			this->threshVal->Text = L"0";
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label25->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label25->Location = System::Drawing::Point(154, 454);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(37, 17);
			this->label25->TabIndex = 112;
			this->label25->Text = L"With:";
			// 
			// targetColor
			// 
			this->targetColor->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(54)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				static_cast<System::Int32>(static_cast<System::Byte>(75)));
			this->targetColor->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->targetColor->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->targetColor->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(155)), static_cast<System::Int32>(static_cast<System::Byte>(90)),
				static_cast<System::Int32>(static_cast<System::Byte>(199)));
			this->targetColor->Location = System::Drawing::Point(93, 452);
			this->targetColor->MaxLength = 6;
			this->targetColor->Name = L"targetColor";
			this->targetColor->Size = System::Drawing::Size(54, 22);
			this->targetColor->TabIndex = 83;
			this->targetColor->Text = L"Hex";
			this->targetColor->TextChanged += gcnew System::EventHandler(this, &MyForm::targetColor_TextChanged);
			this->targetColor->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::targetColor_KeyPress);
			this->targetColor->Leave += gcnew System::EventHandler(this, &MyForm::targetColor_Leave);
			this->targetColor->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::targetColor_MouseDown);
			// 
			// txtMargin
			// 
			this->txtMargin->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(54)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				static_cast<System::Int32>(static_cast<System::Byte>(75)));
			this->txtMargin->Location = System::Drawing::Point(91, 448);
			this->txtMargin->Name = L"txtMargin";
			this->txtMargin->Size = System::Drawing::Size(56, 28);
			this->txtMargin->TabIndex = 74;
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label23->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label23->Location = System::Drawing::Point(173, 395);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(69, 17);
			this->label23->TabIndex = 110;
			this->label23->Text = L"Threshold:";
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.25F));
			this->label22->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label22->Location = System::Drawing::Point(19, 377);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(115, 23);
			this->label22->TabIndex = 109;
			this->label22->Text = L"Replace Color";
			// 
			// interpCheck
			// 
			this->interpCheck->AutoSize = true;
			this->interpCheck->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.25F));
			this->interpCheck->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->interpCheck->Location = System::Drawing::Point(249, 489);
			this->interpCheck->Name = L"interpCheck";
			this->interpCheck->Size = System::Drawing::Size(15, 14);
			this->interpCheck->TabIndex = 106;
			this->interpCheck->UseVisualStyleBackColor = true;
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label21->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label21->Location = System::Drawing::Point(179, 486);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(71, 17);
			this->label21->TabIndex = 107;
			this->label21->Text = L"Interpolate";
			// 
			// repColor
			// 
			this->repColor->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(54)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				static_cast<System::Int32>(static_cast<System::Byte>(75)));
			this->repColor->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->repColor->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->repColor->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(155)), static_cast<System::Int32>(static_cast<System::Byte>(90)),
				static_cast<System::Int32>(static_cast<System::Byte>(199)));
			this->repColor->Location = System::Drawing::Point(198, 452);
			this->repColor->MaxLength = 6;
			this->repColor->Name = L"repColor";
			this->repColor->Size = System::Drawing::Size(54, 22);
			this->repColor->TabIndex = 105;
			this->repColor->Text = L"Hex";
			this->repColor->TextChanged += gcnew System::EventHandler(this, &MyForm::repColor_TextChanged);
			this->repColor->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MyForm::repColor_KeyPress);
			this->repColor->Leave += gcnew System::EventHandler(this, &MyForm::repColor_Leave);
			this->repColor->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::repColor_MouseDown);
			// 
			// txtMargin2
			// 
			this->txtMargin2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(54)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				static_cast<System::Int32>(static_cast<System::Byte>(75)));
			this->txtMargin2->Location = System::Drawing::Point(196, 448);
			this->txtMargin2->Name = L"txtMargin2";
			this->txtMargin2->Size = System::Drawing::Size(56, 28);
			this->txtMargin2->TabIndex = 104;
			// 
			// exaGlCheck
			// 
			this->exaGlCheck->AutoSize = true;
			this->exaGlCheck->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.25F));
			this->exaGlCheck->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->exaGlCheck->Location = System::Drawing::Point(246, 311);
			this->exaGlCheck->Name = L"exaGlCheck";
			this->exaGlCheck->Size = System::Drawing::Size(15, 14);
			this->exaGlCheck->TabIndex = 102;
			this->exaGlCheck->UseVisualStyleBackColor = true;
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label20->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label20->Location = System::Drawing::Point(174, 308);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(74, 17);
			this->label20->TabIndex = 103;
			this->label20->Text = L"Exaggerate";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.25F));
			this->label19->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label19->Location = System::Drawing::Point(14, 295);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(58, 23);
			this->label19->TabIndex = 99;
			this->label19->Text = L"Glitch:";
			// 
			// glitchTrack
			// 
			this->glitchTrack->Location = System::Drawing::Point(28, 330);
			this->glitchTrack->Maximum = 100;
			this->glitchTrack->Name = L"glitchTrack";
			this->glitchTrack->Size = System::Drawing::Size(241, 45);
			this->glitchTrack->TabIndex = 100;
			this->glitchTrack->TickStyle = System::Windows::Forms::TickStyle::None;
			this->glitchTrack->ValueChanged += gcnew System::EventHandler(this, &MyForm::glitchTrack_ValueChanged);
			// 
			// glitchVal
			// 
			this->glitchVal->AutoSize = true;
			this->glitchVal->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.25F));
			this->glitchVal->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->glitchVal->Location = System::Drawing::Point(72, 295);
			this->glitchVal->Name = L"glitchVal";
			this->glitchVal->Size = System::Drawing::Size(19, 23);
			this->glitchVal->TabIndex = 101;
			this->glitchVal->Text = L"0";
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.25F));
			this->label18->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label18->Location = System::Drawing::Point(14, 219);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(44, 23);
			this->label18->TabIndex = 96;
			this->label18->Text = L"Blur:";
			// 
			// blurTrack
			// 
			this->blurTrack->Location = System::Drawing::Point(28, 254);
			this->blurTrack->Maximum = 20;
			this->blurTrack->Name = L"blurTrack";
			this->blurTrack->Size = System::Drawing::Size(241, 45);
			this->blurTrack->TabIndex = 97;
			this->blurTrack->TickStyle = System::Windows::Forms::TickStyle::None;
			this->blurTrack->ValueChanged += gcnew System::EventHandler(this, &MyForm::blurTrack_ValueChanged);
			// 
			// blurVal
			// 
			this->blurVal->AutoSize = true;
			this->blurVal->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.25F));
			this->blurVal->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->blurVal->Location = System::Drawing::Point(59, 219);
			this->blurVal->Name = L"blurVal";
			this->blurVal->Size = System::Drawing::Size(19, 23);
			this->blurVal->TabIndex = 98;
			this->blurVal->Text = L"0";
			// 
			// embossCheck
			// 
			this->embossCheck->AutoSize = true;
			this->embossCheck->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.25F));
			this->embossCheck->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->embossCheck->Location = System::Drawing::Point(174, 552);
			this->embossCheck->Name = L"embossCheck";
			this->embossCheck->Size = System::Drawing::Size(87, 27);
			this->embossCheck->TabIndex = 95;
			this->embossCheck->Text = L"Emboss";
			this->embossCheck->UseVisualStyleBackColor = true;
			this->embossCheck->CheckedChanged += gcnew System::EventHandler(this, &MyForm::embossCheck_CheckedChanged);
			// 
			// edgeCheck
			// 
			this->edgeCheck->AutoSize = true;
			this->edgeCheck->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.25F));
			this->edgeCheck->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->edgeCheck->Location = System::Drawing::Point(174, 585);
			this->edgeCheck->Name = L"edgeCheck";
			this->edgeCheck->Size = System::Drawing::Size(74, 27);
			this->edgeCheck->TabIndex = 94;
			this->edgeCheck->Text = L"Edges";
			this->edgeCheck->UseVisualStyleBackColor = true;
			this->edgeCheck->CheckedChanged += gcnew System::EventHandler(this, &MyForm::edgeCheck_CheckedChanged);
			// 
			// apply2
			// 
			this->apply2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(81)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(147)));
			this->apply2->Cursor = System::Windows::Forms::Cursors::Default;
			this->apply2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->apply2->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->apply2->ForeColor = System::Drawing::Color::White;
			this->apply2->Location = System::Drawing::Point(114, 636);
			this->apply2->Name = L"apply2";
			this->apply2->Size = System::Drawing::Size(56, 32);
			this->apply2->TabIndex = 93;
			this->apply2->Text = L"Apply";
			this->apply2->UseVisualStyleBackColor = false;
			this->apply2->Click += gcnew System::EventHandler(this, &MyForm::apply_Click);
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.25F));
			this->label17->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label17->Location = System::Drawing::Point(14, 147);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(82, 23);
			this->label17->TabIndex = 82;
			this->label17->Text = L"Posterize:";
			// 
			// posterTrack
			// 
			this->posterTrack->Location = System::Drawing::Point(28, 182);
			this->posterTrack->Maximum = 50;
			this->posterTrack->Minimum = 1;
			this->posterTrack->Name = L"posterTrack";
			this->posterTrack->Size = System::Drawing::Size(241, 45);
			this->posterTrack->TabIndex = 83;
			this->posterTrack->TickStyle = System::Windows::Forms::TickStyle::None;
			this->posterTrack->Value = 1;
			this->posterTrack->ValueChanged += gcnew System::EventHandler(this, &MyForm::posterTrack_ValueChanged);
			// 
			// posterVal
			// 
			this->posterVal->AutoSize = true;
			this->posterVal->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.25F));
			this->posterVal->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->posterVal->Location = System::Drawing::Point(93, 147);
			this->posterVal->Name = L"posterVal";
			this->posterVal->Size = System::Drawing::Size(19, 23);
			this->posterVal->TabIndex = 84;
			this->posterVal->Text = L"1";
			// 
			// sepiaCheck
			// 
			this->sepiaCheck->AutoSize = true;
			this->sepiaCheck->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.25F));
			this->sepiaCheck->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->sepiaCheck->Location = System::Drawing::Point(40, 585);
			this->sepiaCheck->Name = L"sepiaCheck";
			this->sepiaCheck->Size = System::Drawing::Size(111, 27);
			this->sepiaCheck->TabIndex = 81;
			this->sepiaCheck->Text = L"Sepia Tone";
			this->sepiaCheck->UseVisualStyleBackColor = true;
			this->sepiaCheck->CheckedChanged += gcnew System::EventHandler(this, &MyForm::sepiaCheck_CheckedChanged);
			// 
			// invertCheck
			// 
			this->invertCheck->AutoSize = true;
			this->invertCheck->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.25F));
			this->invertCheck->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->invertCheck->Location = System::Drawing::Point(40, 552);
			this->invertCheck->Name = L"invertCheck";
			this->invertCheck->Size = System::Drawing::Size(126, 27);
			this->invertCheck->TabIndex = 80;
			this->invertCheck->Text = L"Invert Colors";
			this->invertCheck->UseVisualStyleBackColor = true;
			this->invertCheck->CheckedChanged += gcnew System::EventHandler(this, &MyForm::invertCheck_CheckedChanged);
			// 
			// pageRight2
			// 
			this->pageRight2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(81)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(147)));
			this->pageRight2->Cursor = System::Windows::Forms::Cursors::Default;
			this->pageRight2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->pageRight2->ForeColor = System::Drawing::Color::White;
			this->pageRight2->Location = System::Drawing::Point(177, 683);
			this->pageRight2->Name = L"pageRight2";
			this->pageRight2->Size = System::Drawing::Size(27, 23);
			this->pageRight2->TabIndex = 79;
			this->pageRight2->Text = L">";
			this->pageRight2->UseVisualStyleBackColor = false;
			this->pageRight2->Click += gcnew System::EventHandler(this, &MyForm::pageRight2_Click);
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label8->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(233)), static_cast<System::Int32>(static_cast<System::Byte>(214)),
				static_cast<System::Int32>(static_cast<System::Byte>(250)));
			this->label8->Location = System::Drawing::Point(112, 686);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(60, 17);
			this->label8->TabIndex = 78;
			this->label8->Text = L"Page 2/3";
			// 
			// pageLeft2
			// 
			this->pageLeft2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(81)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(147)));
			this->pageLeft2->Cursor = System::Windows::Forms::Cursors::Default;
			this->pageLeft2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->pageLeft2->ForeColor = System::Drawing::Color::White;
			this->pageLeft2->Location = System::Drawing::Point(78, 683);
			this->pageLeft2->Name = L"pageLeft2";
			this->pageLeft2->Size = System::Drawing::Size(27, 23);
			this->pageLeft2->TabIndex = 77;
			this->pageLeft2->Text = L"<";
			this->pageLeft2->UseVisualStyleBackColor = false;
			this->pageLeft2->Click += gcnew System::EventHandler(this, &MyForm::pageLeft2_Click);
			// 
			// panel2
			// 
			this->panel2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(74)), static_cast<System::Int32>(static_cast<System::Byte>(68)),
				static_cast<System::Int32>(static_cast<System::Byte>(83)));
			this->panel2->Location = System::Drawing::Point(15, 64);
			this->panel2->Name = L"panel2";
			this->panel2->Size = System::Drawing::Size(273, 1);
			this->panel2->TabIndex = 56;
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 18.25F, System::Drawing::FontStyle::Bold));
			this->label12->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label12->Location = System::Drawing::Point(12, 26);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(176, 35);
			this->label12->TabIndex = 55;
			this->label12->Text = L"Effects/Filters:";
			// 
			// grayscaleCheck
			// 
			this->grayscaleCheck->AutoSize = true;
			this->grayscaleCheck->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.25F));
			this->grayscaleCheck->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->grayscaleCheck->Location = System::Drawing::Point(40, 522);
			this->grayscaleCheck->Name = L"grayscaleCheck";
			this->grayscaleCheck->Size = System::Drawing::Size(101, 27);
			this->grayscaleCheck->TabIndex = 61;
			this->grayscaleCheck->Text = L"Grayscale";
			this->grayscaleCheck->UseVisualStyleBackColor = true;
			this->grayscaleCheck->CheckedChanged += gcnew System::EventHandler(this, &MyForm::grayscaleCheck_CheckedChanged);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.25F));
			this->label5->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label5->Location = System::Drawing::Point(14, 75);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(73, 23);
			this->label5->TabIndex = 65;
			this->label5->Text = L"Pixelate:";
			// 
			// pixelateTrack
			// 
			this->pixelateTrack->Location = System::Drawing::Point(28, 110);
			this->pixelateTrack->Maximum = 200;
			this->pixelateTrack->Minimum = 1;
			this->pixelateTrack->Name = L"pixelateTrack";
			this->pixelateTrack->Size = System::Drawing::Size(241, 45);
			this->pixelateTrack->TabIndex = 66;
			this->pixelateTrack->TickStyle = System::Windows::Forms::TickStyle::None;
			this->pixelateTrack->Value = 1;
			this->pixelateTrack->ValueChanged += gcnew System::EventHandler(this, &MyForm::pixelateTrack_ValueChanged);
			// 
			// pixelateVal
			// 
			this->pixelateVal->AutoSize = true;
			this->pixelateVal->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.25F));
			this->pixelateVal->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->pixelateVal->Location = System::Drawing::Point(93, 75);
			this->pixelateVal->Name = L"pixelateVal";
			this->pixelateVal->Size = System::Drawing::Size(19, 23);
			this->pixelateVal->TabIndex = 67;
			this->pixelateVal->Text = L"1";
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label24->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label24->Location = System::Drawing::Point(35, 454);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(57, 17);
			this->label24->TabIndex = 111;
			this->label24->Text = L"Replace:";
			// 
			// threshTrack
			// 
			this->threshTrack->Location = System::Drawing::Point(28, 415);
			this->threshTrack->Maximum = 250;
			this->threshTrack->Name = L"threshTrack";
			this->threshTrack->Size = System::Drawing::Size(241, 45);
			this->threshTrack->TabIndex = 108;
			this->threshTrack->TickStyle = System::Windows::Forms::TickStyle::None;
			this->threshTrack->ValueChanged += gcnew System::EventHandler(this, &MyForm::threshTrack_ValueChanged);
			// 
			// sidePanel
			// 
			this->sidePanel->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(29)), static_cast<System::Int32>(static_cast<System::Byte>(18)),
				static_cast<System::Int32>(static_cast<System::Byte>(52)));
			this->sidePanel->Controls->Add(this->apply1);
			this->sidePanel->Controls->Add(this->bVal);
			this->sidePanel->Controls->Add(this->gVal);
			this->sidePanel->Controls->Add(this->rVal);
			this->sidePanel->Controls->Add(this->label16);
			this->sidePanel->Controls->Add(this->label15);
			this->sidePanel->Controls->Add(this->label14);
			this->sidePanel->Controls->Add(this->Btrack);
			this->sidePanel->Controls->Add(this->Gtrack);
			this->sidePanel->Controls->Add(this->Rtrack);
			this->sidePanel->Controls->Add(this->label10);
			this->sidePanel->Controls->Add(this->hueVal);
			this->sidePanel->Controls->Add(this->label13);
			this->sidePanel->Controls->Add(this->hueTrack);
			this->sidePanel->Controls->Add(this->vibranceVal);
			this->sidePanel->Controls->Add(this->label11);
			this->sidePanel->Controls->Add(this->vibranceTrack);
			this->sidePanel->Controls->Add(this->sharpVal);
			this->sidePanel->Controls->Add(this->Sharpness);
			this->sidePanel->Controls->Add(this->label7);
			this->sidePanel->Controls->Add(this->pageLeft);
			this->sidePanel->Controls->Add(this->brightVal);
			this->sidePanel->Controls->Add(this->brightTrack);
			this->sidePanel->Controls->Add(this->label6);
			this->sidePanel->Controls->Add(this->sharpTrack);
			this->sidePanel->Controls->Add(this->contrastVal);
			this->sidePanel->Controls->Add(this->contrastTrack);
			this->sidePanel->Controls->Add(this->label3);
			this->sidePanel->Controls->Add(this->divider);
			this->sidePanel->Controls->Add(this->label2);
			this->sidePanel->Location = System::Drawing::Point(1287, 0);
			this->sidePanel->Name = L"sidePanel";
			this->sidePanel->Size = System::Drawing::Size(301, 722);
			this->sidePanel->TabIndex = 1;
			// 
			// apply1
			// 
			this->apply1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(81)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(147)));
			this->apply1->Cursor = System::Windows::Forms::Cursors::Default;
			this->apply1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->apply1->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->apply1->ForeColor = System::Drawing::Color::White;
			this->apply1->Location = System::Drawing::Point(114, 636);
			this->apply1->Name = L"apply1";
			this->apply1->Size = System::Drawing::Size(56, 32);
			this->apply1->TabIndex = 92;
			this->apply1->Text = L"Apply";
			this->apply1->UseVisualStyleBackColor = false;
			this->apply1->Click += gcnew System::EventHandler(this, &MyForm::apply_Click);
			// 
			// bVal
			// 
			this->bVal->AutoSize = true;
			this->bVal->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->bVal->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->bVal->Location = System::Drawing::Point(253, 598);
			this->bVal->Name = L"bVal";
			this->bVal->Size = System::Drawing::Size(17, 20);
			this->bVal->TabIndex = 91;
			this->bVal->Text = L"0";
			// 
			// gVal
			// 
			this->gVal->AutoSize = true;
			this->gVal->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->gVal->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->gVal->Location = System::Drawing::Point(253, 573);
			this->gVal->Name = L"gVal";
			this->gVal->Size = System::Drawing::Size(17, 20);
			this->gVal->TabIndex = 90;
			this->gVal->Text = L"0";
			// 
			// rVal
			// 
			this->rVal->AutoSize = true;
			this->rVal->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->rVal->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->rVal->Location = System::Drawing::Point(253, 549);
			this->rVal->Name = L"rVal";
			this->rVal->Size = System::Drawing::Size(17, 20);
			this->rVal->TabIndex = 89;
			this->rVal->Text = L"0";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.25F));
			this->label16->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label16->Location = System::Drawing::Point(28, 597);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(24, 23);
			this->label16->TabIndex = 88;
			this->label16->Text = L"B:";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.25F));
			this->label15->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label15->Location = System::Drawing::Point(27, 574);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(26, 23);
			this->label15->TabIndex = 87;
			this->label15->Text = L"G:";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.25F));
			this->label14->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label14->Location = System::Drawing::Point(27, 548);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(24, 23);
			this->label14->TabIndex = 86;
			this->label14->Text = L"R:";
			// 
			// Btrack
			// 
			this->Btrack->Location = System::Drawing::Point(57, 599);
			this->Btrack->Maximum = 120;
			this->Btrack->Name = L"Btrack";
			this->Btrack->Size = System::Drawing::Size(190, 45);
			this->Btrack->TabIndex = 85;
			this->Btrack->TickStyle = System::Windows::Forms::TickStyle::None;
			this->Btrack->Value = 20;
			this->Btrack->ValueChanged += gcnew System::EventHandler(this, &MyForm::Btrack_ValueChanged);
			// 
			// Gtrack
			// 
			this->Gtrack->Location = System::Drawing::Point(57, 574);
			this->Gtrack->Maximum = 120;
			this->Gtrack->Name = L"Gtrack";
			this->Gtrack->Size = System::Drawing::Size(190, 45);
			this->Gtrack->TabIndex = 84;
			this->Gtrack->TickStyle = System::Windows::Forms::TickStyle::None;
			this->Gtrack->Value = 20;
			this->Gtrack->ValueChanged += gcnew System::EventHandler(this, &MyForm::Gtrack_ValueChanged);
			// 
			// Rtrack
			// 
			this->Rtrack->Location = System::Drawing::Point(57, 549);
			this->Rtrack->Maximum = 120;
			this->Rtrack->Name = L"Rtrack";
			this->Rtrack->Size = System::Drawing::Size(190, 45);
			this->Rtrack->TabIndex = 83;
			this->Rtrack->TickStyle = System::Windows::Forms::TickStyle::None;
			this->Rtrack->Value = 20;
			this->Rtrack->ValueChanged += gcnew System::EventHandler(this, &MyForm::Rtrack_ValueChanged);
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.25F));
			this->label10->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label10->Location = System::Drawing::Point(14, 509);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(103, 23);
			this->label10->TabIndex = 82;
			this->label10->Text = L"Color Boost:";
			// 
			// hueVal
			// 
			this->hueVal->AutoSize = true;
			this->hueVal->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.25F));
			this->hueVal->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->hueVal->Location = System::Drawing::Point(62, 418);
			this->hueVal->Name = L"hueVal";
			this->hueVal->Size = System::Drawing::Size(24, 23);
			this->hueVal->TabIndex = 81;
			this->hueVal->Text = L"0 ";
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.25F));
			this->label13->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label13->Location = System::Drawing::Point(14, 418);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(45, 23);
			this->label13->TabIndex = 79;
			this->label13->Text = L"Hue:";
			// 
			// hueTrack
			// 
			this->hueTrack->Location = System::Drawing::Point(28, 453);
			this->hueTrack->Maximum = 360;
			this->hueTrack->Name = L"hueTrack";
			this->hueTrack->Size = System::Drawing::Size(241, 45);
			this->hueTrack->TabIndex = 80;
			this->hueTrack->TickStyle = System::Windows::Forms::TickStyle::None;
			this->hueTrack->ValueChanged += gcnew System::EventHandler(this, &MyForm::hueTrack_ValueChanged);
			// 
			// vibranceVal
			// 
			this->vibranceVal->AutoSize = true;
			this->vibranceVal->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.25F));
			this->vibranceVal->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->vibranceVal->Location = System::Drawing::Point(98, 336);
			this->vibranceVal->Name = L"vibranceVal";
			this->vibranceVal->Size = System::Drawing::Size(19, 23);
			this->vibranceVal->TabIndex = 78;
			this->vibranceVal->Text = L"0";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.25F));
			this->label11->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label11->Location = System::Drawing::Point(14, 335);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(81, 23);
			this->label11->TabIndex = 76;
			this->label11->Text = L"Vibrance:";
			// 
			// vibranceTrack
			// 
			this->vibranceTrack->Location = System::Drawing::Point(28, 370);
			this->vibranceTrack->Maximum = 300;
			this->vibranceTrack->Minimum = -250;
			this->vibranceTrack->Name = L"vibranceTrack";
			this->vibranceTrack->Size = System::Drawing::Size(241, 45);
			this->vibranceTrack->TabIndex = 77;
			this->vibranceTrack->TickStyle = System::Windows::Forms::TickStyle::None;
			this->vibranceTrack->ValueChanged += gcnew System::EventHandler(this, &MyForm::vibranceTrack_ValueChanged);
			// 
			// sharpVal
			// 
			this->sharpVal->AutoSize = true;
			this->sharpVal->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.25F));
			this->sharpVal->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->sharpVal->Location = System::Drawing::Point(104, 252);
			this->sharpVal->Name = L"sharpVal";
			this->sharpVal->Size = System::Drawing::Size(19, 23);
			this->sharpVal->TabIndex = 64;
			this->sharpVal->Text = L"0";
			// 
			// Sharpness
			// 
			this->Sharpness->AutoSize = true;
			this->Sharpness->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.25F));
			this->Sharpness->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->Sharpness->Location = System::Drawing::Point(14, 252);
			this->Sharpness->Name = L"Sharpness";
			this->Sharpness->Size = System::Drawing::Size(96, 23);
			this->Sharpness->TabIndex = 62;
			this->Sharpness->Text = L"Sharpness: ";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(233)), static_cast<System::Int32>(static_cast<System::Byte>(214)),
				static_cast<System::Int32>(static_cast<System::Byte>(250)));
			this->label7->Location = System::Drawing::Point(112, 686);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(60, 17);
			this->label7->TabIndex = 75;
			this->label7->Text = L"Page 1/3";
			// 
			// pageLeft
			// 
			this->pageLeft->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(81)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(147)));
			this->pageLeft->Cursor = System::Windows::Forms::Cursors::Default;
			this->pageLeft->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->pageLeft->ForeColor = System::Drawing::Color::White;
			this->pageLeft->Location = System::Drawing::Point(78, 683);
			this->pageLeft->Name = L"pageLeft";
			this->pageLeft->Size = System::Drawing::Size(27, 23);
			this->pageLeft->TabIndex = 74;
			this->pageLeft->Text = L"<";
			this->pageLeft->UseVisualStyleBackColor = false;
			this->pageLeft->Click += gcnew System::EventHandler(this, &MyForm::pageLeft_Click);
			// 
			// brightVal
			// 
			this->brightVal->AutoSize = true;
			this->brightVal->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.25F));
			this->brightVal->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->brightVal->Location = System::Drawing::Point(103, 170);
			this->brightVal->Name = L"brightVal";
			this->brightVal->Size = System::Drawing::Size(37, 23);
			this->brightVal->TabIndex = 70;
			this->brightVal->Text = L"100";
			// 
			// brightTrack
			// 
			this->brightTrack->Location = System::Drawing::Point(25, 204);
			this->brightTrack->Maximum = 100;
			this->brightTrack->Minimum = -100;
			this->brightTrack->Name = L"brightTrack";
			this->brightTrack->Size = System::Drawing::Size(241, 45);
			this->brightTrack->TabIndex = 69;
			this->brightTrack->TickStyle = System::Windows::Forms::TickStyle::None;
			this->brightTrack->ValueChanged += gcnew System::EventHandler(this, &MyForm::brightTrack_ValueChanged);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.25F));
			this->label6->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label6->Location = System::Drawing::Point(11, 169);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(93, 23);
			this->label6->TabIndex = 68;
			this->label6->Text = L"Brightness:";
			// 
			// sharpTrack
			// 
			this->sharpTrack->Location = System::Drawing::Point(28, 287);
			this->sharpTrack->Maximum = 200;
			this->sharpTrack->Minimum = 100;
			this->sharpTrack->Name = L"sharpTrack";
			this->sharpTrack->Size = System::Drawing::Size(241, 45);
			this->sharpTrack->TabIndex = 63;
			this->sharpTrack->TickStyle = System::Windows::Forms::TickStyle::None;
			this->sharpTrack->Value = 100;
			this->sharpTrack->ValueChanged += gcnew System::EventHandler(this, &MyForm::sharpTrack_ValueChanged);
			// 
			// contrastVal
			// 
			this->contrastVal->AutoSize = true;
			this->contrastVal->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.25F));
			this->contrastVal->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->contrastVal->Location = System::Drawing::Point(98, 86);
			this->contrastVal->Name = L"contrastVal";
			this->contrastVal->Size = System::Drawing::Size(19, 23);
			this->contrastVal->TabIndex = 59;
			this->contrastVal->Text = L"0";
			// 
			// contrastTrack
			// 
			this->contrastTrack->Location = System::Drawing::Point(28, 121);
			this->contrastTrack->Maximum = 200;
			this->contrastTrack->Name = L"contrastTrack";
			this->contrastTrack->Size = System::Drawing::Size(241, 45);
			this->contrastTrack->TabIndex = 58;
			this->contrastTrack->TickStyle = System::Windows::Forms::TickStyle::None;
			this->contrastTrack->Value = 100;
			this->contrastTrack->Scroll += gcnew System::EventHandler(this, &MyForm::contrastTrack_Scroll);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.25F));
			this->label3->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label3->Location = System::Drawing::Point(14, 86);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(79, 23);
			this->label3->TabIndex = 57;
			this->label3->Text = L"Contrast:";
			// 
			// divider
			// 
			this->divider->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(74)), static_cast<System::Int32>(static_cast<System::Byte>(68)),
				static_cast<System::Int32>(static_cast<System::Byte>(83)));
			this->divider->Location = System::Drawing::Point(15, 64);
			this->divider->Name = L"divider";
			this->divider->Size = System::Drawing::Size(273, 1);
			this->divider->TabIndex = 56;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 18.25F, System::Drawing::FontStyle::Bold));
			this->label2->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label2->Location = System::Drawing::Point(12, 26);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(131, 35);
			this->label2->TabIndex = 55;
			this->label2->Text = L"Essentials:";
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(17)), static_cast<System::Int32>(static_cast<System::Byte>(12)),
				static_cast<System::Int32>(static_cast<System::Byte>(22)));
			this->pictureBox1->Location = System::Drawing::Point(3, 2);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(1280, 720);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::Zoom;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			// 
			// generate
			// 
			this->generate->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(134)), static_cast<System::Int32>(static_cast<System::Byte>(107)),
				static_cast<System::Int32>(static_cast<System::Byte>(135)));
			this->generate->Enabled = false;
			this->generate->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->generate->ForeColor = System::Drawing::Color::White;
			this->generate->Location = System::Drawing::Point(214, 648);
			this->generate->Name = L"generate";
			this->generate->Size = System::Drawing::Size(74, 23);
			this->generate->TabIndex = 72;
			this->generate->Text = L"Generate";
			this->generate->UseVisualStyleBackColor = false;
			this->generate->Click += gcnew System::EventHandler(this, &MyForm::generate_Click);
			// 
			// promptBox
			// 
			this->promptBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(54)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				static_cast<System::Int32>(static_cast<System::Byte>(75)));
			this->promptBox->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->promptBox->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->promptBox->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(225)), static_cast<System::Int32>(static_cast<System::Byte>(206)),
				static_cast<System::Int32>(static_cast<System::Byte>(238)));
			this->promptBox->Location = System::Drawing::Point(26, 434);
			this->promptBox->MaxLength = 279;
			this->promptBox->Name = L"promptBox";
			this->promptBox->Size = System::Drawing::Size(251, 195);
			this->promptBox->TabIndex = 71;
			this->promptBox->Text = L"";
			this->promptBox->TextChanged += gcnew System::EventHandler(this, &MyForm::promptBox_TextChanged);
			// 
			// pomptPad
			// 
			this->pomptPad->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(54)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				static_cast<System::Int32>(static_cast<System::Byte>(75)));
			this->pomptPad->Location = System::Drawing::Point(15, 419);
			this->pomptPad->Name = L"pomptPad";
			this->pomptPad->Size = System::Drawing::Size(273, 223);
			this->pomptPad->TabIndex = 73;
			// 
			// ofd
			// 
			this->ofd->FileName = L"openFileDialog1";
			this->ofd->Filter = L"Image Files (*.bmp;*.jpg;*.jpeg;*.gif;*.png;*.tiff;*.ico)|*.bmp;*.jpg;*.jpeg;*.gi"
				L"f;*.png;*.tiff;*.ico|All Files (*.*)|*.*\"";
			// 
			// sfd
			// 
			this->sfd->Filter = L"Image Files (*.bmp;*.jpg;*.jpeg;*.gif;*.png;*.tiff;*.ico)|*.bmp;*.jpg;*.jpeg;*.gi"
				L"f;*.png;*.tiff;*.ico|All Files (*.*)|*.*";
			this->sfd->Title = L"Save Edited Image";
			// 
			// sidePanel3
			// 
			this->sidePanel3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(29)), static_cast<System::Int32>(static_cast<System::Byte>(18)),
				static_cast<System::Int32>(static_cast<System::Byte>(52)));
			this->sidePanel3->Controls->Add(this->tipSeperator);
			this->sidePanel3->Controls->Add(this->label32);
			this->sidePanel3->Controls->Add(this->label31);
			this->sidePanel3->Controls->Add(this->label30);
			this->sidePanel3->Controls->Add(this->label29);
			this->sidePanel3->Controls->Add(this->label28);
			this->sidePanel3->Controls->Add(this->modelDetails);
			this->sidePanel3->Controls->Add(this->label27);
			this->sidePanel3->Controls->Add(this->label26);
			this->sidePanel3->Controls->Add(this->modelBox);
			this->sidePanel3->Controls->Add(this->pageRight3);
			this->sidePanel3->Controls->Add(this->label9);
			this->sidePanel3->Controls->Add(this->generate);
			this->sidePanel3->Controls->Add(this->promptBox);
			this->sidePanel3->Controls->Add(this->panel4);
			this->sidePanel3->Controls->Add(this->label4);
			this->sidePanel3->Controls->Add(this->pomptPad);
			this->sidePanel3->Location = System::Drawing::Point(667, 0);
			this->sidePanel3->Name = L"sidePanel3";
			this->sidePanel3->Size = System::Drawing::Size(301, 722);
			this->sidePanel3->TabIndex = 3;
			this->sidePanel3->Visible = false;
			// 
			// tipSeperator
			// 
			this->tipSeperator->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(74)), static_cast<System::Int32>(static_cast<System::Byte>(68)),
				static_cast<System::Int32>(static_cast<System::Byte>(83)));
			this->tipSeperator->Location = System::Drawing::Point(18, 262);
			this->tipSeperator->Name = L"tipSeperator";
			this->tipSeperator->Size = System::Drawing::Size(264, 1);
			this->tipSeperator->TabIndex = 58;
			// 
			// label32
			// 
			this->label32->AutoSize = true;
			this->label32->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label32->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(203)), static_cast<System::Int32>(static_cast<System::Byte>(169)),
				static_cast<System::Int32>(static_cast<System::Byte>(226)));
			this->label32->Location = System::Drawing::Point(33, 385);
			this->label32->Name = L"label32";
			this->label32->Size = System::Drawing::Size(106, 20);
			this->label32->TabIndex = 120;
			this->label32->Text = L"e.g \"(dark:3.7)\"";
			// 
			// label31
			// 
			this->label31->AutoSize = true;
			this->label31->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label31->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(203)), static_cast<System::Int32>(static_cast<System::Byte>(169)),
				static_cast<System::Int32>(static_cast<System::Byte>(226)));
			this->label31->Location = System::Drawing::Point(32, 362);
			this->label31->Name = L"label31";
			this->label31->Size = System::Drawing::Size(215, 20);
			this->label31->TabIndex = 119;
			this->label31->Text = L"control use \"(your words:float)\"";
			// 
			// label30
			// 
			this->label30->AutoSize = true;
			this->label30->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label30->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(203)), static_cast<System::Int32>(static_cast<System::Byte>(169)),
				static_cast<System::Int32>(static_cast<System::Byte>(226)));
			this->label30->Location = System::Drawing::Point(33, 341);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(229, 20);
			this->label30->TabIndex = 118;
			this->label30->Text = L"word, e.g \"((dark))\" or for manual";
			// 
			// label29
			// 
			this->label29->AutoSize = true;
			this->label29->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label29->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(203)), static_cast<System::Int32>(static_cast<System::Byte>(169)),
				static_cast<System::Int32>(static_cast<System::Byte>(226)));
			this->label29->Location = System::Drawing::Point(34, 319);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(216, 20);
			this->label29->TabIndex = 117;
			this->label29->Text = L"use (()) to increase focus on the";
			// 
			// label28
			// 
			this->label28->AutoSize = true;
			this->label28->Font = (gcnew System::Drawing::Font(L"Segoe UI", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label28->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(203)), static_cast<System::Int32>(static_cast<System::Byte>(169)),
				static_cast<System::Int32>(static_cast<System::Byte>(226)));
			this->label28->Location = System::Drawing::Point(34, 299);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(219, 20);
			this->label28->TabIndex = 116;
			this->label28->Text = L"When writing prompts, you can ";
			// 
			// modelDetails
			// 
			this->modelDetails->AutoSize = true;
			this->modelDetails->Font = (gcnew System::Drawing::Font(L"Segoe UI", 12.25F));
			this->modelDetails->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->modelDetails->Location = System::Drawing::Point(25, 159);
			this->modelDetails->Name = L"modelDetails";
			this->modelDetails->Size = System::Drawing::Size(79, 23);
			this->modelDetails->TabIndex = 115;
			this->modelDetails->Text = L"..details...";
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label27->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label27->Location = System::Drawing::Point(21, 76);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(74, 25);
			this->label27->TabIndex = 85;
			this->label27->Text = L"Model:";
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Font = (gcnew System::Drawing::Font(L"Segoe UI", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label26->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(203)), static_cast<System::Int32>(static_cast<System::Byte>(169)),
				static_cast<System::Int32>(static_cast<System::Byte>(226)));
			this->label26->Location = System::Drawing::Point(121, 270);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(40, 25);
			this->label26->TabIndex = 84;
			this->label26->Text = L"Tip";
			// 
			// modelBox
			// 
			this->modelBox->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(54)), static_cast<System::Int32>(static_cast<System::Byte>(31)),
				static_cast<System::Int32>(static_cast<System::Byte>(75)));
			this->modelBox->DisplayMember = L"stabilityai/stable-diffusion-xl-base-1.0";
			this->modelBox->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->modelBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->modelBox->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(225)), static_cast<System::Int32>(static_cast<System::Byte>(206)),
				static_cast<System::Int32>(static_cast<System::Byte>(238)));
			this->modelBox->FormattingEnabled = true;
			this->modelBox->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"stabilityai/stable-diffusion-xl-base-1.0", L"stabilityai/stable-diffusion-2-1" });
			this->modelBox->Location = System::Drawing::Point(29, 113);
			this->modelBox->Name = L"modelBox";
			this->modelBox->Size = System::Drawing::Size(251, 24);
			this->modelBox->TabIndex = 83;
			this->modelBox->DropDown += gcnew System::EventHandler(this, &MyForm::modelBox_DropDown);
			this->modelBox->SelectionChangeCommitted += gcnew System::EventHandler(this, &MyForm::modelBox_SelectionChangeCommitted);
			// 
			// pageRight3
			// 
			this->pageRight3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(81)), static_cast<System::Int32>(static_cast<System::Byte>(40)),
				static_cast<System::Int32>(static_cast<System::Byte>(147)));
			this->pageRight3->Cursor = System::Windows::Forms::Cursors::Default;
			this->pageRight3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->pageRight3->ForeColor = System::Drawing::Color::White;
			this->pageRight3->Location = System::Drawing::Point(177, 683);
			this->pageRight3->Name = L"pageRight3";
			this->pageRight3->Size = System::Drawing::Size(27, 23);
			this->pageRight3->TabIndex = 82;
			this->pageRight3->Text = L">";
			this->pageRight3->UseVisualStyleBackColor = false;
			this->pageRight3->Click += gcnew System::EventHandler(this, &MyForm::pageRight3_Click);
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Segoe UI", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label9->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(233)), static_cast<System::Int32>(static_cast<System::Byte>(214)),
				static_cast<System::Int32>(static_cast<System::Byte>(250)));
			this->label9->Location = System::Drawing::Point(112, 686);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(60, 17);
			this->label9->TabIndex = 81;
			this->label9->Text = L"Page 3/3";
			// 
			// panel4
			// 
			this->panel4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(74)), static_cast<System::Int32>(static_cast<System::Byte>(68)),
				static_cast<System::Int32>(static_cast<System::Byte>(83)));
			this->panel4->Location = System::Drawing::Point(15, 64);
			this->panel4->Name = L"panel4";
			this->panel4->Size = System::Drawing::Size(273, 1);
			this->panel4->TabIndex = 56;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Segoe UI Semibold", 18.25F, System::Drawing::FontStyle::Bold));
			this->label4->ForeColor = System::Drawing::SystemColors::ButtonHighlight;
			this->label4->Location = System::Drawing::Point(12, 26);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(258, 35);
			this->label4->TabIndex = 55;
			this->label4->Text = L"Aritficial Intelligence:";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1590, 815);
			this->Controls->Add(this->sidePanel3);
			this->Controls->Add(this->workspace);
			this->Controls->Add(this->ToolBar);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->MinimumSize = System::Drawing::Size(1280, 720);
			this->Name = L"MyForm";
			this->Text = L"Image Editor";
			this->ToolBar->ResumeLayout(false);
			this->ToolBar->PerformLayout();
			this->workspace->ResumeLayout(false);
			this->sidePanel2->ResumeLayout(false);
			this->sidePanel2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->glitchTrack))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->blurTrack))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->posterTrack))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pixelateTrack))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->threshTrack))->EndInit();
			this->sidePanel->ResumeLayout(false);
			this->sidePanel->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Btrack))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Gtrack))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->Rtrack))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->hueTrack))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->vibranceTrack))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->brightTrack))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->sharpTrack))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->contrastTrack))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			this->sidePanel3->ResumeLayout(false);
			this->sidePanel3->PerformLayout();
			this->ResumeLayout(false);

		}

// ------------------------------------------ CODE START ------------------------------------------
	array<String^>^ files;
	String^ path;
	int currentIndex;
	const int zoomLevel = 100;
	int Zooms = 0;

// ==================== DRAG AND DROP ====================
	private: System::Void Form_DragEnter(System::Object^ sender, DragEventArgs^ e) {
		if (e->Data->GetDataPresent(DataFormats::FileDrop)) {
			array<String^>^ droppedFiles = safe_cast<array<String^>^>(e->Data->GetData(DataFormats::FileDrop));
			if (droppedFiles->Length > 0 && IsImage(droppedFiles[0])) {
				e->Effect = DragDropEffects::Copy;
			}
			else if (droppedFiles->Length > 0 && droppedFiles[0]->EndsWith(".iestyle", StringComparison::OrdinalIgnoreCase)) {
				e->Effect = DragDropEffects::Copy; // Allow style file drop
			}
			else {
				e->Effect = DragDropEffects::None;
			}
		}
	}
	
	private: System::Void Form_DragDrop(System::Object^ sender, DragEventArgs^ e) {
		array<String^>^ droppedFiles = safe_cast<array<String^>^>(e->Data->GetData(DataFormats::FileDrop));
		if (droppedFiles->Length > 0) {
			String^ filePath = droppedFiles[0];
			
			// Check if it's a style preset file
			if (filePath->EndsWith(".iestyle", StringComparison::OrdinalIgnoreCase)) {
				ImportStylePreset(filePath);
			}
			else if (IsImage(filePath)) {
				OpenImg(filePath, false);
			}
		}
	}

// ==================== KEYBOARD SHORTCUTS ====================
	private: System::Void Form_KeyDown(System::Object^ sender, KeyEventArgs^ e) {
		// Ctrl+O - Open Image
		if (e->Control && e->KeyCode == Keys::O) {
			openImage_Click(nullptr, nullptr);
			e->Handled = true;
		}
		// Ctrl+S - Save Image
		else if (e->Control && e->KeyCode == Keys::S) {
			saveImage_Click(nullptr, nullptr);
			e->Handled = true;
		}
		// Ctrl+Z - Undo
		else if (e->Control && e->KeyCode == Keys::Z) {
			PerformUndo();
			e->Handled = true;
		}
		// Ctrl+Y or Ctrl+Shift+Z - Redo
		else if ((e->Control && e->KeyCode == Keys::Y) || (e->Control && e->Shift && e->KeyCode == Keys::Z)) {
			PerformRedo();
			e->Handled = true;
		}
		// Ctrl+E - Export Style
		else if (e->Control && e->KeyCode == Keys::E) {
			ExportStylePreset();
			e->Handled = true;
		}
		// Ctrl+I - Import Style
		else if (e->Control && e->KeyCode == Keys::I) {
			ImportStylePreset();
			e->Handled = true;
		}
		// Ctrl+R - Reset to Original
		else if (e->Control && e->KeyCode == Keys::R) {
			ResetToOriginal();
			e->Handled = true;
		}
		// Enter - Apply Effects
		else if (e->KeyCode == Keys::Enter && !promptBox->Focused) {
			apply_Click(nullptr, nullptr);
			e->Handled = true;
		}
		// Escape - Close Image
		else if (e->KeyCode == Keys::Escape) {
			closeImage_Click(nullptr, nullptr);
			e->Handled = true;
		}
		// Left/Right Arrow - Navigate images
		else if (e->KeyCode == Keys::Left && !promptBox->Focused && !targetColor->Focused && !repColor->Focused) {
			MoveLeft_Click(nullptr, nullptr);
			e->Handled = true;
		}
		else if (e->KeyCode == Keys::Right && !promptBox->Focused && !targetColor->Focused && !repColor->Focused) {
			MoveRight_Click(nullptr, nullptr);
			e->Handled = true;
		}
		// +/- for zoom
		else if (e->KeyCode == Keys::Oemplus || e->KeyCode == Keys::Add) {
			zoomIn_Click(nullptr, nullptr);
			e->Handled = true;
		}
		else if (e->KeyCode == Keys::OemMinus || e->KeyCode == Keys::Subtract) {
			ZoomOut_Click(nullptr, nullptr);
			e->Handled = true;
		}
	}

// ==================== UNDO / REDO ====================
	private: void PerformUndo() {
		if (ImageCache::CanUndo() && pictureBox1->Image != nullptr) {
			// Push current state to redo stack
			ImageCache::PushRedo(safe_cast<Bitmap^>(pictureBox1->Image));
			
			// Pop from undo stack
			Bitmap^ undoImage = ImageCache::PopUndo();
			if (undoImage != nullptr) {
				if (pictureBox1->Image != nullptr) {
					delete pictureBox1->Image;
				}
				pictureBox1->Image = undoImage;
				pictureBox1->Refresh();
			}
		}
		else {
			// If no undo available, reset to original
			ResetToOriginal();
		}
	}
	
	private: void PerformRedo() {
		if (ImageCache::CanRedo()) {
			// Push current state to undo stack
			if (pictureBox1->Image != nullptr) {
				ImageCache::PushUndo(safe_cast<Bitmap^>(pictureBox1->Image));
			}
			
			// Pop from redo stack
			Bitmap^ redoImage = ImageCache::PopRedo();
			if (redoImage != nullptr) {
				if (pictureBox1->Image != nullptr) {
					delete pictureBox1->Image;
				}
				pictureBox1->Image = redoImage;
				pictureBox1->Refresh();
			}
		}
	}
	
	private: void ResetToOriginal() {
		Bitmap^ original = ImageCache::GetOriginal();
		if (original != nullptr) {
			if (pictureBox1->Image != nullptr) {
				// Save current state to undo before resetting
				ImageCache::PushUndo(safe_cast<Bitmap^>(pictureBox1->Image));
				delete pictureBox1->Image;
			}
			pictureBox1->Image = original;
			pictureBox1->Refresh();
		}
	}

// ==================== STYLE PRESET EXPORT / IMPORT ====================
	private: StylePreset^ GetCurrentStylePreset() {
		StylePreset^ preset = gcnew StylePreset();
		
		// Essentials
		preset->Contrast = contrastTrack->Value;
		preset->Brightness = brightTrack->Value;
		preset->Sharpness = sharpTrack->Value;
		preset->Vibrance = vibranceTrack->Value;
		preset->Hue = hueTrack->Value;
		preset->RedBoost = Rtrack->Value;
		preset->GreenBoost = Gtrack->Value;
		preset->BlueBoost = Btrack->Value;
		
		// Effects
		preset->Pixelate = pixelateTrack->Value;
		preset->Posterize = posterTrack->Value;
		preset->Blur = blurTrack->Value;
		preset->Glitch = glitchTrack->Value;
		preset->ExaggeratedGlitch = exaGlCheck->Checked;
		
		// Color replacement
		if (targetColor->Text != "Hex") preset->TargetColor = targetColor->Text;
		if (repColor->Text != "Hex") preset->ReplacementColor = repColor->Text;
		preset->ColorThreshold = threshTrack->Value;
		preset->ColorInterpolate = interpCheck->Checked;
		
		// Checkbox effects
		preset->Grayscale = grayscaleCheck->Checked;
		preset->Invert = invertCheck->Checked;
		preset->Sepia = sepiaCheck->Checked;
		preset->EdgeDetection = edgeCheck->Checked;
		preset->Emboss = embossCheck->Checked;
		preset->OilPaint = oilCheck->Checked;
		
		return preset;
	}
	
	private: void ApplyStylePreset(StylePreset^ preset) {
		if (preset == nullptr) return;
		
		// Apply essentials
		contrastTrack->Value = Math::Max(contrastTrack->Minimum, Math::Min(contrastTrack->Maximum, preset->Contrast));
		contrastVal->Text = contrastTrack->Value.ToString();
		
		brightTrack->Value = Math::Max(brightTrack->Minimum, Math::Min(brightTrack->Maximum, preset->Brightness));
		brightVal->Text = (brightTrack->Value + 100).ToString();
		
		sharpTrack->Value = Math::Max(sharpTrack->Minimum, Math::Min(sharpTrack->Maximum, preset->Sharpness));
		double sharp = (sharpTrack->Value - 100) / 100.0;
		sharpVal->Text = sharp.ToString();
		
		vibranceTrack->Value = Math::Max(vibranceTrack->Minimum, Math::Min(vibranceTrack->Maximum, preset->Vibrance));
		vibranceVal->Text = (vibranceTrack->Value / 10.0f).ToString();
		
		hueTrack->Value = Math::Max(hueTrack->Minimum, Math::Min(hueTrack->Maximum, preset->Hue));
		hueVal->Text = hueTrack->Value.ToString() + L"\u00B0";
		
		Rtrack->Value = Math::Max(Rtrack->Minimum, Math::Min(Rtrack->Maximum, preset->RedBoost));
		rVal->Text = ((Rtrack->Value / 20.0) - 1).ToString();
		
		Gtrack->Value = Math::Max(Gtrack->Minimum, Math::Min(Gtrack->Maximum, preset->GreenBoost));
		gVal->Text = ((Gtrack->Value / 20.0) - 1).ToString();
		
		Btrack->Value = Math::Max(Btrack->Minimum, Math::Min(Btrack->Maximum, preset->BlueBoost));
		bVal->Text = ((Btrack->Value / 20.0) - 1).ToString();
		
		// Apply effects
		pixelateTrack->Value = Math::Max(pixelateTrack->Minimum, Math::Min(pixelateTrack->Maximum, preset->Pixelate));
		pixelateVal->Text = pixelateTrack->Value.ToString();
		
		posterTrack->Value = Math::Max(posterTrack->Minimum, Math::Min(posterTrack->Maximum, preset->Posterize));
		posterVal->Text = posterTrack->Value.ToString();
		
		blurTrack->Value = Math::Max(blurTrack->Minimum, Math::Min(blurTrack->Maximum, preset->Blur));
		blurVal->Text = blurTrack->Value.ToString();
		
		glitchTrack->Value = Math::Max(glitchTrack->Minimum, Math::Min(glitchTrack->Maximum, preset->Glitch));
		glitchVal->Text = glitchTrack->Value.ToString();
		
		exaGlCheck->Checked = preset->ExaggeratedGlitch;
		
		// Color replacement
		if (!String::IsNullOrEmpty(preset->TargetColor)) {
			targetColor->Text = preset->TargetColor;
			targetColor->ForeColor = Color::White;
		}
		if (!String::IsNullOrEmpty(preset->ReplacementColor)) {
			repColor->Text = preset->ReplacementColor;
			repColor->ForeColor = Color::White;
		}
		threshTrack->Value = Math::Max(threshTrack->Minimum, Math::Min(threshTrack->Maximum, preset->ColorThreshold));
		threshVal->Text = (threshTrack->Value / 2.5f).ToString();
		interpCheck->Checked = preset->ColorInterpolate;
		
		// Checkbox effects
		grayscaleCheck->Checked = preset->Grayscale;
		invertCheck->Checked = preset->Invert;
		sepiaCheck->Checked = preset->Sepia;
		edgeCheck->Checked = preset->EdgeDetection;
		embossCheck->Checked = preset->Emboss;
		oilCheck->Checked = preset->OilPaint;
	}
	
	private: void ExportStylePreset() {
		SaveFileDialog^ styleSfd = gcnew SaveFileDialog();
		styleSfd->Filter = "Image Editor Style (*.iestyle)|*.iestyle";
		styleSfd->Title = "Export Style Preset";
		styleSfd->DefaultExt = "iestyle";
		
		// Prompt for preset name
		String^ presetName = Microsoft::VisualBasic::Interaction::InputBox(
			"Enter a name for this style preset:",
			"Export Style",
			"My Style",
			-1, -1);
		
		if (String::IsNullOrEmpty(presetName)) return;
		
		styleSfd->FileName = presetName;
		
		if (styleSfd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			StylePreset^ preset = GetCurrentStylePreset();
			preset->PresetName = presetName;
			
			if (preset->SaveToFile(styleSfd->FileName)) {
				MessageBox::Show("Style preset exported successfully!\n\nFile: " + styleSfd->FileName + 
					"\n\nShare this file with others to let them use your style.",
					"Export Successful", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			else {
				MessageBox::Show("Failed to export style preset.", "Export Error", 
					MessageBoxButtons::OK, MessageBoxIcon::Error);
			}
		}
	}
	
	private: void ImportStylePreset() {
		OpenFileDialog^ styleOfd = gcnew OpenFileDialog();
		styleOfd->Filter = "Image Editor Style (*.iestyle)|*.iestyle|All Files (*.*)|*.*";
		styleOfd->Title = "Import Style Preset";
		
		if (styleOfd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			ImportStylePreset(styleOfd->FileName);
		}
	}
	
	private: void ImportStylePreset(String^ filePath) {
		StylePreset^ preset = StylePreset::LoadFromFile(filePath);
		
		if (preset != nullptr) {
			System::Windows::Forms::DialogResult result = MessageBox::Show(
				"Style: " + preset->PresetName + "\nBy: " + preset->Author + 
				"\n\nDo you want to apply this style and process the image?",
				"Import Style", MessageBoxButtons::YesNoCancel, MessageBoxIcon::Question);
			
			if (result == System::Windows::Forms::DialogResult::Yes) {
				ApplyStylePreset(preset);
				// Apply to current image
				if (pictureBox1->Image != nullptr) {
					apply_Click(nullptr, nullptr);
				}
			}
			else if (result == System::Windows::Forms::DialogResult::No) {
				ApplyStylePreset(preset);
				// Just set the sliders, don't apply
			}
		}
		else {
			MessageBox::Show("Failed to load style preset.\nThe file may be corrupted or in an invalid format.",
				"Import Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
		}
	}

	//IMAGE BROWSE
		void OpenImg(String^ filePath, bool AI) {
			if (IsImage(filePath)) {
				try {
					String^ prompt = promptBox->Text->Replace("\n", " ");
					if (prompt->Length > 100) {
						prompt = prompt->Substring(0, 100) + "...";
					}

					(AI) ? MyForm::Text = "Image Editor - AI Gen - \"" + prompt + "\"       (" + filePath + ")" :
						MyForm::Text = "Image Editor - " + System::IO::Path::GetFileName(filePath) + "      (" + filePath + ")";

					// Dispose old image before loading new one
					if (pictureBox1->Image != nullptr) {
						delete pictureBox1->Image;
						pictureBox1->Image = nullptr;
					}

					// Load and cache the original image for faster re-apply operations
					Bitmap^ loadedImage = gcnew Bitmap(filePath);
					ImageCache::SetOriginal(loadedImage);
					pictureBox1->Image = gcnew Bitmap(loadedImage);

					path = System::IO::Path::GetDirectoryName(filePath);
					files = System::IO::Directory::GetFiles(path);

					for (int i = 0; i < files->Length; i++) {
						if (files[i] == filePath) {
							currentIndex = i;
							break;
						}
					}
				}
				catch (Exception^ ex) {
					MessageBox::Show("Failed to open image: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
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
			// Dispose current image and clear cache
			if (pictureBox1->Image != nullptr) {
				delete pictureBox1->Image;
				pictureBox1->Image = nullptr;
			}
			ImageCache::Clear();
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
				
				// Load new image and update cache
				if (pictureBox1->Image != nullptr) {
					delete pictureBox1->Image;
					pictureBox1->Image = nullptr;
				}
				Bitmap^ newImage = gcnew Bitmap(files[currentIndex]);
				ImageCache::SetOriginal(newImage);
				ImageCache::Clear(); // Clear undo/redo for new image
				ImageCache::SetOriginal(newImage); // Re-set after clear
				pictureBox1->Image = gcnew Bitmap(newImage);
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
				
				// Load new image and update cache
				if (pictureBox1->Image != nullptr) {
					delete pictureBox1->Image;
					pictureBox1->Image = nullptr;
				}
				Bitmap^ newImage = gcnew Bitmap(files[currentIndex]);
				ImageCache::SetOriginal(newImage);
				ImageCache::Clear(); // Clear undo/redo for new image
				ImageCache::SetOriginal(newImage); // Re-set after clear
				pictureBox1->Image = gcnew Bitmap(newImage);
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
			this->Cursor = Cursors::WaitCursor;

			try {
				String^ originalFilePath = files[currentIndex];
				
				// Save current state for undo before applying new effects
				if (pictureBox1->Image != nullptr) {
					ImageCache::PushUndo(safe_cast<Bitmap^>(pictureBox1->Image));
				}
				
				// Use cached original if available, otherwise load from disk
				Bitmap^ cachedOriginal = ImageCache::GetOriginal();
				Bitmap^ workingImage = (cachedOriginal != nullptr) ? cachedOriginal : gcnew Bitmap(originalFilePath);
				
				// Dispose old image before replacing
				if (pictureBox1->Image != nullptr && pictureBox1->Image != workingImage) {
					delete pictureBox1->Image;
				}

				// ESSENTIALS - Apply filters to single working image (no excessive copying)
				if (contrastTrack->Value != 100) {
					workingImage = SetContrast(workingImage, contrastTrack->Value);
				}

				if (sharpTrack->Value != 100) {
					workingImage = SharpenImage(workingImage, sharpTrack->Value);
				}

				if (brightTrack->Value != 0) {
					workingImage = SetBrightness(workingImage, brightTrack->Value);
				}

				if (hueTrack->Value != 0) {
					workingImage = AdjustHue(workingImage, hueTrack->Value);
				}

				if (vibranceTrack->Value != 0) {
					workingImage = AdjustVibrance(workingImage, vibranceTrack->Value);
				}

				if (Rtrack->Value != 20 || Btrack->Value != 20 || Gtrack->Value != 20) {
					workingImage = ColorBoost(workingImage, Rtrack->Value, Gtrack->Value, Btrack->Value);
				}

				// EFFECTS & FILTERS
				if (pixelateTrack->Value != 1) {
					workingImage = PixelateImage(workingImage, pixelateTrack->Value);
				}

				if (posterTrack->Value != 1) {
					workingImage = PosterizeImage(workingImage, posterTrack->Value);
				}

				if (blurTrack->Value != 0) {
					workingImage = BlurImage(workingImage, blurTrack->Value);
				}

				if (glitchTrack->Value != 0) {
					workingImage = exaGlCheck->Checked ? 
						ExaGlitchEffect(workingImage, glitchTrack->Value) : 
						GlitchEffect(workingImage, glitchTrack->Value);
				}

				if (targetColor->Text->Length == 6 && repColor->Text->Length == 6) {
					workingImage = ReplaceColor(workingImage, targetColor->Text, repColor->Text, threshTrack->Value, interpCheck->Checked);
				}

				// CheckBox FX
				if (sepiaCheck->Checked) 
					workingImage = SepiaTone(workingImage);
				if (grayscaleCheck->Checked) 
					workingImage = ConvertToGrayScale(workingImage);
				if (invertCheck->Checked) 
					workingImage = InvertColors(workingImage);
				if (edgeCheck->Checked)
					workingImage = ApplyEdgeDetection(workingImage);
				if (embossCheck->Checked)
					workingImage = EmbossImage(workingImage);
				if (oilCheck->Checked)
					workingImage = ApplyOilPaintingEffect(workingImage);

				pictureBox1->Image = workingImage;
				pictureBox1->Refresh();
				
				MyForm::Text = "Image Editor - " + System::IO::Path::GetFileName(originalFilePath) + "      (" + originalFilePath + ")";
			}
			catch (Exception^ ex) {
				MessageBox::Show("Error applying effects: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				MyForm::Text = "Image Editor";
			}
			finally {
				this->Cursor = Cursors::Default;
			}
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
			hueVal->Text = L"0\u00B0";

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
				float vibrance = vibranceTrack->Value / 10.0f;
				vibranceVal->Text = vibrance.ToString();
			}

			private: System::Void hueTrack_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
				hueVal->Text = hueTrack->Value.ToString() + L"\u00B0";
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
			float thresh = threshTrack->Value / 2.5f;
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
			this->Cursor = Cursors::WaitCursor;
			generate->Enabled = false;

			try {
				Bitmap^ generatedImage = GenerateImageFromText(promp, modelBox->SelectedItem->ToString());
				
				if (generatedImage != nullptr) {
					pictureBox1->Image = generatedImage;

					String^ imageGenPath = Path::GetTempPath() + "ImageGen";
					Directory::CreateDirectory(imageGenPath);

					String^ savePath = Path::Combine(imageGenPath, GenerateRandomString(8) + ".png");
					pictureBox1->Image->Save(savePath);

					OpenImg(savePath, true);
				}
				else {
					MyForm::Text = "Image Editor - Generation Failed";
				}
			}
			catch (Exception^ ex) {
				MessageBox::Show("Failed to generate image: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				MyForm::Text = "Image Editor";
			}
			finally {
				this->Cursor = Cursors::Default;
				generate->Enabled = promptBox->Text->Length >= 3;
			}
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
