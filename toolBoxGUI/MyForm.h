#pragma once
#include<opencv2/opencv.hpp>
#include"iostream"
#include <msclr\marshal_cppstd.h>
#include <stack>

namespace toolBoxGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace std;
	using namespace cv;

	/* SRC IMG*/

	Mat image,imageBlinding;
	Mat imageClone;
	std::string stdFileName, stdFileName2;
	double gammaValue = 1.0;
	std::stack<cv::Mat> undoStack;
	int fType,matrixSize,grayLevelType;
	bool isSelectingRange;
	bool isStartTextFieldBeingEdited = false;
	bool isEndTextFieldBeingEdited = false;
	int image_width, image_height;
	int laplaceValue;


	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
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
		//Functions
	private:
		System::Drawing::Bitmap^ ConvertGrayscaleToBitmap(const cv::Mat& grayscaleImage)
		{
			System::Drawing::Bitmap^ bitmapImage = gcnew System::Drawing::Bitmap(grayscaleImage.cols, grayscaleImage.rows);

			for (int y = 0; y < grayscaleImage.rows; y++)
			{
				for (int x = 0; x < grayscaleImage.cols; x++)
				{
					int pixelValue = grayscaleImage.at<uchar>(y, x);
					System::Drawing::Color color = System::Drawing::Color::FromArgb(pixelValue, pixelValue, pixelValue);
					bitmapImage->SetPixel(x, y, color);
				}
			}
			imageprev->Image = bitmapImage;
			return bitmapImage;
		}
		System::Void ApplyGammaCorrection() {

			double gammaValue = GammaBar->Value / 10.0;

			Gamma_textBox->Text = gammaValue.ToString();

			 imageClone = cv::Mat(image.rows, image.cols, CV_32FC1);


			for (int i = 0; i < image.rows; i++)
				for (int j = 0; j < image.cols; j++)
					imageClone.at<float>(i, j) = powf(image.at<uchar>(i, j), gammaValue);

			normalize(imageClone, imageClone, 0, 255, NORM_MINMAX);
			convertScaleAbs(imageClone, imageClone);
			ConvertGrayscaleToBitmap(imageClone);
		}

		System::Void ApplyThresholding() {

			imageClone = image.clone();
			double thresholdvalue = threshold_trackBar->Value;
			threshold(imageClone, imageClone, thresholdvalue, 255, THRESH_BINARY);
			threshold_label->Text = "Threshold: " + threshold_trackBar->Value.ToString();
			ConvertGrayscaleToBitmap(imageClone);
		}

		Mat CropAndScale(Mat& input, Rect cropRect) {
			Mat cropped = input(cropRect);
			Mat scaled;
			resize(cropped, scaled, cv::Size(), 2.0, 2.0, 0);
			return scaled;
		}

	private: System::Windows::Forms::Button^ showbutton;
	private: System::Windows::Forms::Button^ equalizebutton;


	private: System::Windows::Forms::Button^ negbutton;
	private: System::Windows::Forms::Button^ Transbutton;
	private: System::Windows::Forms::TextBox^ X_value;
	private: System::Windows::Forms::TextBox^ Y_value;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::PictureBox^ imageprev;
	private: System::Windows::Forms::OpenFileDialog^ openFileDialog1;
	private: System::Windows::Forms::Button^ reset;
	private: System::Windows::Forms::TrackBar^ GammaBar;
	private: System::Windows::Forms::TextBox^ Gamma_textBox;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::GroupBox^ groupBox1;
	private: System::Windows::Forms::Button^ save_button;
	private: System::Windows::Forms::Button^ logTrans_button;
	private: System::Windows::Forms::Button^ rotation_button;
	private: System::Windows::Forms::Button^ cropButton;
	private: System::Windows::Forms::ComboBox^ bitPlaneComboBox;
	private: System::Windows::Forms::ComboBox^ flipComboBox;
	private: System::Windows::Forms::Button^ undoButton;
	private: System::Windows::Forms::ComboBox^ filterMatrix;
	private: System::Windows::Forms::ComboBox^ filterType;
	private: System::Windows::Forms::Button^ filterButton;
	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::TextBox^ constLevel;
private: System::Windows::Forms::TextBox^ selectedGlevelStart;



private: System::Windows::Forms::Button^ grayLevel_button;
private: System::Windows::Forms::Button^ edge_button;
private: System::Windows::Forms::Button^ Blinding;
private: System::Windows::Forms::OpenFileDialog^ openFileDialog2;
private: System::Windows::Forms::TextBox^ selectedGlevelEnd;
private: System::Windows::Forms::ComboBox^ grayLevel_combobox;
private: System::Windows::Forms::GroupBox^ groupBox3;
private: System::Windows::Forms::TrackBar^ threshold_trackBar;

private: System::Windows::Forms::Label^ label5;
private: System::Windows::Forms::TextBox^ skewing_textBox;
private: System::Windows::Forms::TrackBar^ LPF_trackBar;

private: System::Windows::Forms::Label^ label6;
private: System::Windows::Forms::GroupBox^ groupBox4;
private: System::Windows::Forms::GroupBox^ Thresholding;
private: System::Windows::Forms::GroupBox^ groupBox5;



private: System::Windows::Forms::Label^ threshold_label;
private: System::Windows::Forms::Label^ size_label;
private: System::Windows::Forms::GroupBox^ groupBox6;
private: System::Windows::Forms::Button^ userManual_button;
private: System::Windows::Forms::TrackBar^ laplace_trackBar;



















	protected:

	protected:

	private:
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
			this->showbutton = (gcnew System::Windows::Forms::Button());
			this->equalizebutton = (gcnew System::Windows::Forms::Button());
			this->negbutton = (gcnew System::Windows::Forms::Button());
			this->Transbutton = (gcnew System::Windows::Forms::Button());
			this->X_value = (gcnew System::Windows::Forms::TextBox());
			this->Y_value = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->imageprev = (gcnew System::Windows::Forms::PictureBox());
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->reset = (gcnew System::Windows::Forms::Button());
			this->GammaBar = (gcnew System::Windows::Forms::TrackBar());
			this->Gamma_textBox = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->save_button = (gcnew System::Windows::Forms::Button());
			this->logTrans_button = (gcnew System::Windows::Forms::Button());
			this->rotation_button = (gcnew System::Windows::Forms::Button());
			this->cropButton = (gcnew System::Windows::Forms::Button());
			this->bitPlaneComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->flipComboBox = (gcnew System::Windows::Forms::ComboBox());
			this->undoButton = (gcnew System::Windows::Forms::Button());
			this->filterMatrix = (gcnew System::Windows::Forms::ComboBox());
			this->filterType = (gcnew System::Windows::Forms::ComboBox());
			this->filterButton = (gcnew System::Windows::Forms::Button());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->laplace_trackBar = (gcnew System::Windows::Forms::TrackBar());
			this->constLevel = (gcnew System::Windows::Forms::TextBox());
			this->selectedGlevelStart = (gcnew System::Windows::Forms::TextBox());
			this->grayLevel_button = (gcnew System::Windows::Forms::Button());
			this->edge_button = (gcnew System::Windows::Forms::Button());
			this->Blinding = (gcnew System::Windows::Forms::Button());
			this->openFileDialog2 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->selectedGlevelEnd = (gcnew System::Windows::Forms::TextBox());
			this->grayLevel_combobox = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->threshold_trackBar = (gcnew System::Windows::Forms::TrackBar());
			this->threshold_label = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->skewing_textBox = (gcnew System::Windows::Forms::TextBox());
			this->LPF_trackBar = (gcnew System::Windows::Forms::TrackBar());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->Thresholding = (gcnew System::Windows::Forms::GroupBox());
			this->size_label = (gcnew System::Windows::Forms::Label());
			this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
			this->userManual_button = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->imageprev))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->GammaBar))->BeginInit();
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->laplace_trackBar))->BeginInit();
			this->groupBox3->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->threshold_trackBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->LPF_trackBar))->BeginInit();
			this->groupBox4->SuspendLayout();
			this->Thresholding->SuspendLayout();
			this->groupBox6->SuspendLayout();
			this->SuspendLayout();
			// 
			// showbutton
			// 
			this->showbutton->Location = System::Drawing::Point(826, 711);
			this->showbutton->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->showbutton->Name = L"showbutton";
			this->showbutton->Size = System::Drawing::Size(123, 40);
			this->showbutton->TabIndex = 0;
			this->showbutton->Text = L"browse image";
			this->showbutton->UseVisualStyleBackColor = true;
			this->showbutton->Click += gcnew System::EventHandler(this, &MyForm::showbutton_Click);
			// 
			// equalizebutton
			// 
			this->equalizebutton->Location = System::Drawing::Point(10, 14);
			this->equalizebutton->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->equalizebutton->Name = L"equalizebutton";
			this->equalizebutton->Size = System::Drawing::Size(149, 42);
			this->equalizebutton->TabIndex = 1;
			this->equalizebutton->Text = L"equalization";
			this->equalizebutton->UseVisualStyleBackColor = true;
			this->equalizebutton->Click += gcnew System::EventHandler(this, &MyForm::equalizebutton_Click);
			// 
			// negbutton
			// 
			this->negbutton->Location = System::Drawing::Point(346, 14);
			this->negbutton->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->negbutton->Name = L"negbutton";
			this->negbutton->Size = System::Drawing::Size(146, 42);
			this->negbutton->TabIndex = 2;
			this->negbutton->Text = L"negative";
			this->negbutton->UseVisualStyleBackColor = true;
			this->negbutton->Click += gcnew System::EventHandler(this, &MyForm::negbutton_Click);
			// 
			// Transbutton
			// 
			this->Transbutton->Location = System::Drawing::Point(233, 33);
			this->Transbutton->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->Transbutton->Name = L"Transbutton";
			this->Transbutton->Size = System::Drawing::Size(127, 42);
			this->Transbutton->TabIndex = 3;
			this->Transbutton->Text = L"Translation";
			this->Transbutton->UseVisualStyleBackColor = true;
			this->Transbutton->Click += gcnew System::EventHandler(this, &MyForm::Transbutton_Click);
			// 
			// X_value
			// 
			this->X_value->Location = System::Drawing::Point(15, 27);
			this->X_value->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->X_value->Name = L"X_value";
			this->X_value->Size = System::Drawing::Size(28, 26);
			this->X_value->TabIndex = 4;
			// 
			// Y_value
			// 
			this->Y_value->Location = System::Drawing::Point(15, 63);
			this->Y_value->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->Y_value->Name = L"Y_value";
			this->Y_value->Size = System::Drawing::Size(28, 26);
			this->Y_value->TabIndex = 5;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(50, 33);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(56, 19);
			this->label1->TabIndex = 6;
			this->label1->Text = L"x-value";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(49, 66);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(55, 19);
			this->label2->TabIndex = 7;
			this->label2->Text = L"y-value";
			// 
			// imageprev
			// 
			this->imageprev->BackColor = System::Drawing::SystemColors::ControlLight;
			this->imageprev->Location = System::Drawing::Point(557, 14);
			this->imageprev->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->imageprev->Name = L"imageprev";
			this->imageprev->Size = System::Drawing::Size(758, 644);
			this->imageprev->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->imageprev->TabIndex = 8;
			this->imageprev->TabStop = false;
			this->imageprev->Click += gcnew System::EventHandler(this, &MyForm::imageprev_Click);
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// reset
			// 
			this->reset->Location = System::Drawing::Point(1077, 711);
			this->reset->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->reset->Name = L"reset";
			this->reset->Size = System::Drawing::Size(116, 40);
			this->reset->TabIndex = 9;
			this->reset->Text = L"reset";
			this->reset->UseVisualStyleBackColor = true;
			this->reset->Click += gcnew System::EventHandler(this, &MyForm::reset_Click);
			// 
			// GammaBar
			// 
			this->GammaBar->Location = System::Drawing::Point(6, 66);
			this->GammaBar->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->GammaBar->Maximum = 20;
			this->GammaBar->Name = L"GammaBar";
			this->GammaBar->RightToLeft = System::Windows::Forms::RightToLeft::Yes;
			this->GammaBar->RightToLeftLayout = true;
			this->GammaBar->Size = System::Drawing::Size(238, 56);
			this->GammaBar->TabIndex = 10;
			this->GammaBar->Value = 10;
			this->GammaBar->Scroll += gcnew System::EventHandler(this, &MyForm::GammaBar_Scroll);
			this->GammaBar->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::GammaBar_MouseUp);
			// 
			// Gamma_textBox
			// 
			this->Gamma_textBox->Location = System::Drawing::Point(263, 66);
			this->Gamma_textBox->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->Gamma_textBox->Name = L"Gamma_textBox";
			this->Gamma_textBox->Size = System::Drawing::Size(87, 26);
			this->Gamma_textBox->TabIndex = 11;
			this->Gamma_textBox->TextChanged += gcnew System::EventHandler(this, &MyForm::Gamma_textBox_TextChanged);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(260, 33);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(86, 19);
			this->label3->TabIndex = 12;
			this->label3->Text = L"GammaValue";
			this->label3->Click += gcnew System::EventHandler(this, &MyForm::label3_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->BackColor = System::Drawing::Color::SkyBlue;
			this->groupBox1->Controls->Add(this->label3);
			this->groupBox1->Controls->Add(this->GammaBar);
			this->groupBox1->Controls->Add(this->Gamma_textBox);
			this->groupBox1->Location = System::Drawing::Point(10, 287);
			this->groupBox1->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Padding = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->groupBox1->Size = System::Drawing::Size(380, 119);
			this->groupBox1->TabIndex = 13;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"GammaCorrection";
			// 
			// save_button
			// 
			this->save_button->Location = System::Drawing::Point(1199, 711);
			this->save_button->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->save_button->Name = L"save_button";
			this->save_button->Size = System::Drawing::Size(116, 40);
			this->save_button->TabIndex = 14;
			this->save_button->Text = L"Save";
			this->save_button->UseVisualStyleBackColor = true;
			this->save_button->Click += gcnew System::EventHandler(this, &MyForm::save_button_Click);
			// 
			// logTrans_button
			// 
			this->logTrans_button->Location = System::Drawing::Point(169, 14);
			this->logTrans_button->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->logTrans_button->Name = L"logTrans_button";
			this->logTrans_button->Size = System::Drawing::Size(171, 42);
			this->logTrans_button->TabIndex = 15;
			this->logTrans_button->Text = L"LogTransformation";
			this->logTrans_button->UseVisualStyleBackColor = true;
			this->logTrans_button->Click += gcnew System::EventHandler(this, &MyForm::logTrans_button_Click);
			// 
			// rotation_button
			// 
			this->rotation_button->Location = System::Drawing::Point(10, 63);
			this->rotation_button->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->rotation_button->Name = L"rotation_button";
			this->rotation_button->Size = System::Drawing::Size(146, 42);
			this->rotation_button->TabIndex = 16;
			this->rotation_button->Text = L"Rotation";
			this->rotation_button->UseVisualStyleBackColor = true;
			this->rotation_button->Click += gcnew System::EventHandler(this, &MyForm::rotation_button_Click);
			// 
			// cropButton
			// 
			this->cropButton->Location = System::Drawing::Point(169, 63);
			this->cropButton->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->cropButton->Name = L"cropButton";
			this->cropButton->Size = System::Drawing::Size(75, 42);
			this->cropButton->TabIndex = 17;
			this->cropButton->Text = L"Crop";
			this->cropButton->UseVisualStyleBackColor = true;
			this->cropButton->Click += gcnew System::EventHandler(this, &MyForm::cropButton_Click);
			// 
			// bitPlaneComboBox
			// 
			this->bitPlaneComboBox->FormattingEnabled = true;
			this->bitPlaneComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(8) {
				L"1", L"2", L"4", L"8", L"16", L"32", L"64",
					L"128"
			});
			this->bitPlaneComboBox->Location = System::Drawing::Point(355, 125);
			this->bitPlaneComboBox->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->bitPlaneComboBox->Name = L"bitPlaneComboBox";
			this->bitPlaneComboBox->Size = System::Drawing::Size(121, 27);
			this->bitPlaneComboBox->TabIndex = 18;
			this->bitPlaneComboBox->Text = L"Bit plane";
			this->bitPlaneComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::bitPlaneComboBox_SelectedIndexChanged);
			// 
			// flipComboBox
			// 
			this->flipComboBox->FormattingEnabled = true;
			this->flipComboBox->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Horizontal", L"Vertical", L"Horizontal&Vertical" });
			this->flipComboBox->Location = System::Drawing::Point(227, 125);
			this->flipComboBox->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->flipComboBox->Name = L"flipComboBox";
			this->flipComboBox->Size = System::Drawing::Size(121, 27);
			this->flipComboBox->TabIndex = 19;
			this->flipComboBox->Text = L"Flip";
			this->flipComboBox->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::flipComboBox_SelectedIndexChanged);
			// 
			// undoButton
			// 
			this->undoButton->Location = System::Drawing::Point(955, 711);
			this->undoButton->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->undoButton->Name = L"undoButton";
			this->undoButton->Size = System::Drawing::Size(116, 40);
			this->undoButton->TabIndex = 20;
			this->undoButton->Text = L"Undo";
			this->undoButton->UseVisualStyleBackColor = true;
			this->undoButton->Click += gcnew System::EventHandler(this, &MyForm::undoButton_Click);
			// 
			// filterMatrix
			// 
			this->filterMatrix->FormattingEnabled = true;
			this->filterMatrix->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"3", L"5" });
			this->filterMatrix->Location = System::Drawing::Point(6, 84);
			this->filterMatrix->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->filterMatrix->Name = L"filterMatrix";
			this->filterMatrix->Size = System::Drawing::Size(121, 27);
			this->filterMatrix->TabIndex = 21;
			this->filterMatrix->Text = L"Filter Matrix";
			this->filterMatrix->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::filterMatrix_SelectedIndexChanged);
			// 
			// filterType
			// 
			this->filterType->FormattingEnabled = true;
			this->filterType->Items->AddRange(gcnew cli::array< System::Object^  >(6) {
				L"Avaraging", L"Weighted", L"Median", L"Gaussian Blur",
					L"Laplacian", L"Sobel"
			});
			this->filterType->Location = System::Drawing::Point(6, 36);
			this->filterType->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->filterType->Name = L"filterType";
			this->filterType->Size = System::Drawing::Size(121, 27);
			this->filterType->TabIndex = 22;
			this->filterType->Text = L"Filter Type";
			this->filterType->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::filterType_SelectedIndexChanged);
			// 
			// filterButton
			// 
			this->filterButton->Location = System::Drawing::Point(250, 52);
			this->filterButton->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->filterButton->Name = L"filterButton";
			this->filterButton->Size = System::Drawing::Size(112, 40);
			this->filterButton->TabIndex = 23;
			this->filterButton->Text = L"Filter";
			this->filterButton->UseVisualStyleBackColor = true;
			this->filterButton->Click += gcnew System::EventHandler(this, &MyForm::filterButton_Click);
			// 
			// groupBox2
			// 
			this->groupBox2->BackColor = System::Drawing::Color::SkyBlue;
			this->groupBox2->Controls->Add(this->laplace_trackBar);
			this->groupBox2->Controls->Add(this->filterType);
			this->groupBox2->Controls->Add(this->filterButton);
			this->groupBox2->Controls->Add(this->filterMatrix);
			this->groupBox2->Location = System::Drawing::Point(10, 414);
			this->groupBox2->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Padding = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->groupBox2->Size = System::Drawing::Size(380, 118);
			this->groupBox2->TabIndex = 24;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Image Filtering";
			// 
			// laplace_trackBar
			// 
			this->laplace_trackBar->Location = System::Drawing::Point(140, 36);
			this->laplace_trackBar->Maximum = 9;
			this->laplace_trackBar->Minimum = 1;
			this->laplace_trackBar->Name = L"laplace_trackBar";
			this->laplace_trackBar->Size = System::Drawing::Size(104, 56);
			this->laplace_trackBar->SmallChange = 2;
			this->laplace_trackBar->TabIndex = 24;
			this->laplace_trackBar->TickFrequency = 2;
			this->laplace_trackBar->Value = 1;
			this->laplace_trackBar->Visible = false;
			this->laplace_trackBar->Scroll += gcnew System::EventHandler(this, &MyForm::laplace_trackBar_Scroll);
			// 
			// constLevel
			// 
			this->constLevel->Location = System::Drawing::Point(144, 25);
			this->constLevel->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->constLevel->Name = L"constLevel";
			this->constLevel->Size = System::Drawing::Size(100, 26);
			this->constLevel->TabIndex = 25;
			this->constLevel->Text = L"Constant Level";
			// 
			// selectedGlevelStart
			// 
			this->selectedGlevelStart->Location = System::Drawing::Point(8, 69);
			this->selectedGlevelStart->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->selectedGlevelStart->Name = L"selectedGlevelStart";
			this->selectedGlevelStart->Size = System::Drawing::Size(121, 26);
			this->selectedGlevelStart->TabIndex = 26;
			this->selectedGlevelStart->Text = L"Start";
			this->selectedGlevelStart->Click += gcnew System::EventHandler(this, &MyForm::selectedGlevelStart_Click);
			// 
			// grayLevel_button
			// 
			this->grayLevel_button->Location = System::Drawing::Point(263, 58);
			this->grayLevel_button->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->grayLevel_button->Name = L"grayLevel_button";
			this->grayLevel_button->Size = System::Drawing::Size(104, 37);
			this->grayLevel_button->TabIndex = 28;
			this->grayLevel_button->Text = L"Gray Level slicing";
			this->grayLevel_button->UseVisualStyleBackColor = true;
			this->grayLevel_button->Click += gcnew System::EventHandler(this, &MyForm::grayLevel_button_Click);
			// 
			// edge_button
			// 
			this->edge_button->Location = System::Drawing::Point(10, 116);
			this->edge_button->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->edge_button->Name = L"edge_button";
			this->edge_button->Size = System::Drawing::Size(203, 43);
			this->edge_button->TabIndex = 29;
			this->edge_button->Text = L"EdgeBased Segmentation";
			this->edge_button->UseVisualStyleBackColor = true;
			this->edge_button->Click += gcnew System::EventHandler(this, &MyForm::edge_button_Click);
			// 
			// Blinding
			// 
			this->Blinding->Location = System::Drawing::Point(250, 63);
			this->Blinding->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->Blinding->Name = L"Blinding";
			this->Blinding->Size = System::Drawing::Size(90, 42);
			this->Blinding->TabIndex = 30;
			this->Blinding->Text = L"Blinding";
			this->Blinding->UseVisualStyleBackColor = true;
			this->Blinding->Click += gcnew System::EventHandler(this, &MyForm::Blinding_Click);
			// 
			// openFileDialog2
			// 
			this->openFileDialog2->FileName = L"openFileDialog2";
			// 
			// selectedGlevelEnd
			// 
			this->selectedGlevelEnd->Location = System::Drawing::Point(8, 102);
			this->selectedGlevelEnd->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->selectedGlevelEnd->Name = L"selectedGlevelEnd";
			this->selectedGlevelEnd->Size = System::Drawing::Size(121, 26);
			this->selectedGlevelEnd->TabIndex = 31;
			this->selectedGlevelEnd->Text = L"End";
			this->selectedGlevelEnd->Click += gcnew System::EventHandler(this, &MyForm::selectedGlevelEnd_Click);
			// 
			// grayLevel_combobox
			// 
			this->grayLevel_combobox->FormattingEnabled = true;
			this->grayLevel_combobox->Items->AddRange(gcnew cli::array< System::Object^  >(2) { L"preserve all values", L"constant level" });
			this->grayLevel_combobox->Location = System::Drawing::Point(8, 25);
			this->grayLevel_combobox->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->grayLevel_combobox->Name = L"grayLevel_combobox";
			this->grayLevel_combobox->Size = System::Drawing::Size(121, 27);
			this->grayLevel_combobox->TabIndex = 32;
			this->grayLevel_combobox->Text = L"Gray Level Type";
			this->grayLevel_combobox->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::grayLevel_combobox_SelectedIndexChanged);
			// 
			// groupBox3
			// 
			this->groupBox3->BackColor = System::Drawing::Color::SkyBlue;
			this->groupBox3->Controls->Add(this->grayLevel_button);
			this->groupBox3->Controls->Add(this->selectedGlevelEnd);
			this->groupBox3->Controls->Add(this->constLevel);
			this->groupBox3->Controls->Add(this->selectedGlevelStart);
			this->groupBox3->Controls->Add(this->grayLevel_combobox);
			this->groupBox3->Location = System::Drawing::Point(10, 540);
			this->groupBox3->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Padding = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->groupBox3->Size = System::Drawing::Size(380, 136);
			this->groupBox3->TabIndex = 33;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Gray Level Slicing";
			// 
			// threshold_trackBar
			// 
			this->threshold_trackBar->Location = System::Drawing::Point(49, 26);
			this->threshold_trackBar->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->threshold_trackBar->Maximum = 255;
			this->threshold_trackBar->Name = L"threshold_trackBar";
			this->threshold_trackBar->Size = System::Drawing::Size(243, 56);
			this->threshold_trackBar->TabIndex = 34;
			this->threshold_trackBar->Scroll += gcnew System::EventHandler(this, &MyForm::threshold_trackBar_Scroll);
			this->threshold_trackBar->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::threshold_trackBar_MouseUp);
			// 
			// threshold_label
			// 
			this->threshold_label->AutoSize = true;
			this->threshold_label->Location = System::Drawing::Point(298, 22);
			this->threshold_label->Name = L"threshold_label";
			this->threshold_label->Size = System::Drawing::Size(40, 19);
			this->threshold_label->TabIndex = 35;
			this->threshold_label->Text = L"value";
			this->threshold_label->Click += gcnew System::EventHandler(this, &MyForm::threshold_label_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(351, 75);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(59, 19);
			this->label5->TabIndex = 37;
			this->label5->Text = L"Skewing";
			this->label5->Click += gcnew System::EventHandler(this, &MyForm::label5_Click);
			// 
			// skewing_textBox
			// 
			this->skewing_textBox->Location = System::Drawing::Point(415, 72);
			this->skewing_textBox->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->skewing_textBox->Name = L"skewing_textBox";
			this->skewing_textBox->Size = System::Drawing::Size(100, 26);
			this->skewing_textBox->TabIndex = 38;
			this->skewing_textBox->TextChanged += gcnew System::EventHandler(this, &MyForm::skewing_textBox_TextChanged);
			this->skewing_textBox->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &MyForm::skewing_textBox_KeyDown);
			// 
			// LPF_trackBar
			// 
			this->LPF_trackBar->Location = System::Drawing::Point(6, 20);
			this->LPF_trackBar->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->LPF_trackBar->Maximum = 150;
			this->LPF_trackBar->Name = L"LPF_trackBar";
			this->LPF_trackBar->Size = System::Drawing::Size(243, 56);
			this->LPF_trackBar->TabIndex = 39;
			this->LPF_trackBar->TickFrequency = 0;
			this->LPF_trackBar->Scroll += gcnew System::EventHandler(this, &MyForm::LPF_trackBar_Scroll);
			this->LPF_trackBar->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::LPF_trackBar_MouseUp);
			// 
			// groupBox4
			// 
			this->groupBox4->BackColor = System::Drawing::Color::SkyBlue;
			this->groupBox4->Controls->Add(this->label1);
			this->groupBox4->Controls->Add(this->X_value);
			this->groupBox4->Controls->Add(this->Y_value);
			this->groupBox4->Controls->Add(this->Transbutton);
			this->groupBox4->Controls->Add(this->label2);
			this->groupBox4->Location = System::Drawing::Point(10, 172);
			this->groupBox4->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Padding = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->groupBox4->Size = System::Drawing::Size(380, 107);
			this->groupBox4->TabIndex = 41;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Translation";
			// 
			// Thresholding
			// 
			this->Thresholding->BackColor = System::Drawing::Color::SkyBlue;
			this->Thresholding->Controls->Add(this->threshold_trackBar);
			this->Thresholding->Controls->Add(this->threshold_label);
			this->Thresholding->Location = System::Drawing::Point(10, 683);
			this->Thresholding->Name = L"Thresholding";
			this->Thresholding->Size = System::Drawing::Size(380, 76);
			this->Thresholding->TabIndex = 42;
			this->Thresholding->TabStop = false;
			this->Thresholding->Text = L"Thresholding";
			// 
			// size_label
			// 
			this->size_label->AutoSize = true;
			this->size_label->Location = System::Drawing::Point(1235, 674);
			this->size_label->Name = L"size_label";
			this->size_label->Size = System::Drawing::Size(36, 19);
			this->size_label->TabIndex = 43;
			this->size_label->Text = L"Size";
			this->size_label->Click += gcnew System::EventHandler(this, &MyForm::size_label_Click);
			// 
			// groupBox6
			// 
			this->groupBox6->BackColor = System::Drawing::Color::SkyBlue;
			this->groupBox6->Controls->Add(this->LPF_trackBar);
			this->groupBox6->Location = System::Drawing::Point(415, 683);
			this->groupBox6->Name = L"groupBox6";
			this->groupBox6->Size = System::Drawing::Size(285, 76);
			this->groupBox6->TabIndex = 44;
			this->groupBox6->TabStop = false;
			this->groupBox6->Text = L"Low Pass Filter";
			// 
			// userManual_button
			// 
			this->userManual_button->Location = System::Drawing::Point(706, 711);
			this->userManual_button->Name = L"userManual_button";
			this->userManual_button->Size = System::Drawing::Size(114, 40);
			this->userManual_button->TabIndex = 45;
			this->userManual_button->Text = L"User manual";
			this->userManual_button->UseVisualStyleBackColor = true;
			this->userManual_button->Click += gcnew System::EventHandler(this, &MyForm::userManual_button_Click);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 19);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoScroll = true;
			this->AutoSize = true;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->BackColor = System::Drawing::Color::Linen;
			this->ClientSize = System::Drawing::Size(1327, 767);
			this->Controls->Add(this->userManual_button);
			this->Controls->Add(this->groupBox6);
			this->Controls->Add(this->size_label);
			this->Controls->Add(this->Thresholding);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->skewing_textBox);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->groupBox3);
			this->Controls->Add(this->Blinding);
			this->Controls->Add(this->edge_button);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->undoButton);
			this->Controls->Add(this->flipComboBox);
			this->Controls->Add(this->bitPlaneComboBox);
			this->Controls->Add(this->cropButton);
			this->Controls->Add(this->rotation_button);
			this->Controls->Add(this->logTrans_button);
			this->Controls->Add(this->save_button);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->reset);
			this->Controls->Add(this->imageprev);
			this->Controls->Add(this->negbutton);
			this->Controls->Add(this->equalizebutton);
			this->Controls->Add(this->showbutton);
			this->Font = (gcnew System::Drawing::Font(L"Comic Sans MS", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Icon = (cli::safe_cast<System::Drawing::Icon^>(resources->GetObject(L"$this.Icon")));
			this->Margin = System::Windows::Forms::Padding(3, 4, 3, 4);
			this->Name = L"MyForm";
			this->Text = L"ToolBox";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->imageprev))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->GammaBar))->EndInit();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->laplace_trackBar))->EndInit();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->threshold_trackBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->LPF_trackBar))->EndInit();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->Thresholding->ResumeLayout(false);
			this->Thresholding->PerformLayout();
			this->groupBox6->ResumeLayout(false);
			this->groupBox6->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void showbutton_Click(System::Object^ sender, System::EventArgs^ e) {
		openFileDialog1->ShowDialog();
		imageprev->Image = imageprev->Image->FromFile(openFileDialog1->FileName);
		stdFileName = msclr::interop::marshal_as<std::string>(openFileDialog1->FileName);

		image = imread(stdFileName, 0);
		ConvertGrayscaleToBitmap(image);
		image_width = image.cols;
		image_height = image.rows;
		System::String^ width_image = System::Convert::ToString(image_width);
		System::String^ height_image = System::Convert::ToString(image_height);
		size_label->Text = width_image + " x " + height_image;

	}
	private: System::Void equalizebutton_Click(System::Object^ sender, System::EventArgs^ e) {

		undoStack.push(image.clone());
		equalizeHist(image, image);
		ConvertGrayscaleToBitmap(image);
	}
	private: System::Void negbutton_Click(System::Object^ sender, System::EventArgs^ e) {

		undoStack.push(image.clone());
		for (int i = 0; i < image.rows; i++)
			for (int j = 0; j < image.cols; j++)
				image.at<uchar>(i, j) = 255 - image.at<uchar>(i, j);
		ConvertGrayscaleToBitmap(image);
		
	}
    private: System::Void Transbutton_Click(System::Object^ sender, System::EventArgs^ e) {

		undoStack.push(image.clone());
		int tx = Convert::ToInt32(X_value->Text);
		int ty = Convert::ToInt32(Y_value->Text);
	    Mat TM = (Mat_<float>(2, 3) << 1, 0, tx, 0, 1, ty);
	    warpAffine(image, image, TM, image.size());
		ConvertGrayscaleToBitmap(image);
	
}
    private: System::Void reset_Click(System::Object^ sender, System::EventArgs^ e) {

	    image = imread(stdFileName, 0);
		ConvertGrayscaleToBitmap(image);
}
	private: System::Void GammaBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
		undoStack.push(image.clone());
		ApplyGammaCorrection();
}

    private: System::Void Gamma_textBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {

		undoStack.push(image.clone());
		gammaValue = System::Convert::ToDouble(Gamma_textBox->Text);
		GammaBar->Value = static_cast<float>(gammaValue * 10);
		ApplyGammaCorrection();
		
}
private: System::Void label3_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void save_button_Click(System::Object^ sender, System::EventArgs^ e) {

		SaveFileDialog^ sfd = gcnew SaveFileDialog();
		sfd->Filter = "Image Files (.png;.bmp;.jpg)|.png;.bmp;.jpg|All files (.)|.";
		if (sfd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			// Convert the image to System::Drawing::Bitmap
			Bitmap^ bmp = ConvertGrayscaleToBitmap(image);
			// Save the bitmap to the specified file format
			bmp->Save(sfd->FileName);
		}
}
private: System::Void logTrans_button_Click(System::Object^ sender, System::EventArgs^ e) {

	undoStack.push(image.clone());
	Mat dst_8(image.rows, image.cols, CV_32FC1);
	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			dst_8.at<float>(i, j) = log(image.at<uchar>(i, j) + 1);
		}
	}
	normalize(dst_8, image, 0, 255, NORM_MINMAX);
	convertScaleAbs(image, image);
	ConvertGrayscaleToBitmap(image);
}
private: System::Void rotation_button_Click(System::Object^ sender, System::EventArgs^ e) {

	undoStack.push(image.clone());
	Mat R = getRotationMatrix2D(Point2f(image.cols / 2, image.rows / 2), 270, 1);
	warpAffine(image, image, R, image.size());

	image_width = image.cols;
	image_height = image.rows;
	System::String^ width_image = System::Convert::ToString(image_width);
	System::String^ height_image = System::Convert::ToString(image_height);
	size_label->Text = width_image + " x " + height_image;
	
	ConvertGrayscaleToBitmap(image);
}
private: System::Void cropButton_Click(System::Object^ sender, System::EventArgs^ e) {

	undoStack.push(image.clone());
	Rect size;
	namedWindow("image", 0);
	size = selectROI("image", image);
	destroyWindow("image");
	 image = CropAndScale(image, size);

	image_width = image.cols;
	image_height = image.rows;
	System::String^ width_image = System::Convert::ToString(image_width);
	System::String^ height_image = System::Convert::ToString(image_height);
	size_label->Text = width_image + " x " + height_image;
	ConvertGrayscaleToBitmap(image);
}
private: System::Void bitPlaneComboBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {

	undoStack.push(image.clone());
	for (int i = 0; i < image.rows; i++)
		for (int j = 0; j < image.cols; j++) {
			if (image.at<uchar>(i, j) & Convert::ToInt32(bitPlaneComboBox->Text))
				image.at<uchar>(i, j) = 255;
			else
				image.at<uchar>(i, j) = 0;
		}
	ConvertGrayscaleToBitmap(image);
}
private: System::Void flipComboBox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {

	undoStack.push(image.clone());
	if (flipComboBox->Text == "Horizontal") {
		flip(image, image, 1);
	}
	else if (flipComboBox->Text == "Vertical") {
		flip(image, image, 0);
	}
	else if (flipComboBox->Text == "Horizontal&Vertical") {
		flip(image, image, -1);
	}
	ConvertGrayscaleToBitmap(image);
}
private: System::Void undoButton_Click(System::Object^ sender, System::EventArgs^ e) {

	if (!undoStack.empty()) {
		image = undoStack.top();
		undoStack.pop();
		ConvertGrayscaleToBitmap(image);
	}
}
private: System::Void filterType_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {

	if (filterType->Text == "Avaraging")
	{
		laplace_trackBar->Visible = false;
		fType = 1;
	}
	else if (filterType->Text == "Weighted")
	{
		laplace_trackBar->Visible = false;
		fType = 2;
	}
	else if (filterType->Text == "Median")
	{
		laplace_trackBar->Visible = false;
		fType = 3;
	}
	else if (filterType->Text == "Gaussian Blur")
	{
		laplace_trackBar->Visible = false;
		fType = 4;
	}
	else if (filterType->Text == "Laplacian")
	{
		laplace_trackBar->Visible = TRUE;
		fType = 5;
	}
	else if (filterType->Text == "Sobel")
	{
		laplace_trackBar->Visible = false;
		fType = 6;
	}

}
private: System::Void filterMatrix_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {

	if (filterMatrix->Text == "3")
		matrixSize = 3;
	else if (filterMatrix->Text == "5")
		matrixSize = 5;

}
private: System::Void filterButton_Click(System::Object^ sender, System::EventArgs^ e) {

	Mat kernel;
	undoStack.push(image.clone());
	switch (fType)
	{
	case 1:
		switch (matrixSize)
		{
		case 3:
			kernel = (Mat_<float>(3, 3) << 1, 1, 1,
				1, 1, 1,
				1, 1, 1);
			kernel = kernel / 9;
			break;
		case 5:
			kernel = (Mat_<float>(5, 5) << 1, 1, 1, 1, 1,
				1, 1, 1, 1, 1,
				1, 1, 1, 1, 1,
				1, 1, 1, 1, 1,
				1, 1, 1, 1, 1);
			kernel = kernel / 25;
			break;
		default:
			break;
		}
		filter2D(image, image, CV_8UC1, kernel);
		break;
	case 2:
		switch (matrixSize)
		{
		case 3:
			kernel = (Mat_<float>(3, 3) << 1, 2, 1,
				2, 4, 2,
				1, 2, 1);
			kernel = kernel / 16;
			break;
		case 5:
			kernel = (Mat_<float>(5, 5) << 1, 2, 3, 2, 1,
				2, 4, 6, 4, 2,
				3, 6, 9, 6, 3,
				2, 4, 6, 4, 2,
				1, 2, 3, 2, 1);
			kernel = kernel / 81;
			break;
		default:
			break;
		}
		filter2D(image, image, CV_8UC1, kernel);
		break;
	case 3:
		switch (matrixSize)
		{
		case 3:
			medianBlur(image, image, 3);
			break;
		case 5:
			medianBlur(image, image, 5);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	case 4:
		switch (matrixSize)
		{
		case 3:
			GaussianBlur(image, image, cv::Size(3, 3), 0);
			break;
		case 5:
			GaussianBlur(image, image, cv::Size(5, 5), 0);
			break;
		default:
			break;
		}
		break;
	case 5:
		Laplacian(image, image, CV_8UC1, laplaceValue);
		break;
	case 6:
		Mat dst_H, dst_V;
		Mat kernal_H = (Mat_<float>(3, 3) << -1, -2, -1
			, 0, 0, 0
			, 1, 2, 1);
		filter2D(image, dst_H, CV_16SC1, kernal_H);
		convertScaleAbs(dst_H, dst_H);

		Mat kernal_V = (Mat_<float>(3, 3) << -1, 0, 1
			, -2, 0, 2
			, -1, 0, 1);
		filter2D(image, dst_V, CV_16SC1, kernal_V);
		convertScaleAbs(dst_V, dst_V);

		addWeighted(dst_H, 1, dst_V, 1, 0, image);
		break;
	}
	ConvertGrayscaleToBitmap(image);
}

	private: System::Void imageprev_Click(System::Object^ sender, System::EventArgs^ e) {

		MouseEventArgs^ mouseEvent = (MouseEventArgs^)e;
		int x = mouseEvent->X;
		int y = mouseEvent->Y;

		if (x >= 0 && x < image.cols && y >= 0 && y < image.rows) {
			int currentIntensity = static_cast<int>(image.at<uchar>(y, x));

			// Now 'currentIntensity' contains the intensity of the pixel at (x, y)

			if (isStartTextFieldBeingEdited) {
				// If the start text field is being edited, update its value
				selectedGlevelStart->Text = currentIntensity.ToString();

				// Reset the flag
				isStartTextFieldBeingEdited = false;
			}

			if (isEndTextFieldBeingEdited) {
				// If the end text field is being edited, update its value
				selectedGlevelEnd->Text = currentIntensity.ToString();

				// Reset the flag
				isEndTextFieldBeingEdited = false;
			}
		}
	}

private: System::Void selectedGlevelStart_Click(System::Object^ sender, System::EventArgs^ e) {
		   isStartTextFieldBeingEdited = true;
		   imageprev->SizeMode = PictureBoxSizeMode::Normal;
}

private: System::Void selectedGlevelEnd_Click(System::Object^ sender, System::EventArgs^ e) {
		   isEndTextFieldBeingEdited = true;
		   
}

private: System::Void grayLevel_combobox_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
		   if (grayLevel_combobox->Text == "preserve all values")
			   grayLevelType = 0;
		   else if (grayLevel_combobox->Text == "constant level")
			   grayLevelType = 1;
}

private: System::Void grayLevel_button_Click(System::Object^ sender, System::EventArgs^ e) {
	undoStack.push(image.clone());
	for (int i = 0; i < image.rows; i++)
		for (int j = 0; j < image.cols; j++) {

			if (image.at<uchar>(i, j) >= Convert::ToInt32(selectedGlevelStart->Text) && image.at<uchar>(i, j) <= Convert::ToInt32(selectedGlevelEnd->Text))
				image.at<uchar>(i, j) = 255;
			else
			{
				switch (grayLevelType)
				{
				case 0:
					image.at<uchar>(i, j) = image.at<uchar>(i, j);
					break;
				case 1:
					image.at<uchar>(i, j) = Convert::ToInt32(constLevel->Text);
					break;
				default:
					break;
				}
			}

		}
	imageprev->SizeMode = PictureBoxSizeMode::StretchImage;
	ConvertGrayscaleToBitmap(image);
	
}
private: System::Void edge_button_Click(System::Object^ sender, System::EventArgs^ e) {
	undoStack.push(image.clone());
	Mat kernel_L = (Mat_<float>(3, 3) << -1, -1, -1, -1, 8, -1, -1, -1, -1);
	filter2D(image, image, CV_8UC1, kernel_L);
	ConvertGrayscaleToBitmap(image);
}
private: System::Void Blinding_Click(System::Object^ sender, System::EventArgs^ e) {

	undoStack.push(image.clone());
	openFileDialog2->ShowDialog();
	stdFileName2 = msclr::interop::marshal_as<std::string>(openFileDialog2->FileName);
	imageBlinding = imread(stdFileName2, 0);


	Mat image_blind(image.rows, image.cols, CV_8UC1);
	resize(imageBlinding, imageBlinding, cv::Size(image.cols, image.rows), 0, 0, 0);

	for (int i = 0; i < image.rows; i++)
		for (int j = 0; j < image.cols; j++)
			image_blind.at<uchar>(i, j) = image.at<uchar>(i, j) * 0.7 + imageBlinding.at<uchar>(i, j) * 0.3;

	image = image_blind;
	ConvertGrayscaleToBitmap(image);
}

private: System::Void threshold_trackBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
	ApplyThresholding();
}
private: System::Void threshold_trackBar_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	undoStack.push(image.clone());
	image = imageClone;

}
private: System::Void skewing_textBox_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
	undoStack.push(image.clone());
	if (e->KeyCode == Keys::Enter) {
		// Your code for the transformation
		Point2f src_p[3];
		src_p[0] = Point2f(0, 0);
		src_p[1] = Point2f(image.cols - 1, 0);
		src_p[2] = Point2f(Convert::ToInt32(skewing_textBox->Text), image.rows - 1);

		Point2f dst_p[3];

		dst_p[0] = Point2f(0, 0);
		dst_p[1] = Point2f(image.cols - 1, 0);
		dst_p[2] = Point2f(0, image.rows - 1);
		Mat SM = getAffineTransform(src_p, dst_p);
		warpAffine(image, image, SM, image.size());

		ConvertGrayscaleToBitmap(image);
	}
}
private: System::Void LPF_trackBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
	// Get the frequency value from the trackbar
	double freqValue = LPF_trackBar->Value * 3;
	int m = getOptimalDFTSize(image.rows);
	int n = getOptimalDFTSize(image.cols);
	Mat padded;
	copyMakeBorder(image, padded, 0, m - image.rows, 0, n - image.cols, 0);
	padded.convertTo(padded, CV_32FC1, 1.0 / 255.0);
	Mat planes[2] = { padded, Mat::zeros(padded.size(),CV_32FC1) };
	Mat complexI;
	merge(planes, 2, complexI);
	dft(complexI, complexI);
	////////////////
	int cx = complexI.cols / 2;
	int cy = complexI.rows / 2;
	Mat p1(complexI, Rect(0, 0, cx, cy));
	Mat p2(complexI, Rect(cx, 0, cx, cy));
	Mat p3(complexI, Rect(0, cy, cx, cy));
	Mat p4(complexI, Rect(cx, cy, cx, cy));
	Mat temp;
	p1.copyTo(temp);
	p4.copyTo(p1);
	temp.copyTo(p4);
	p2.copyTo(temp);
	p3.copyTo(p2);
	temp.copyTo(p3);
	//////////////////
	Mat Lfilter(complexI.size(), CV_32FC1);
	// int freqValue = 900;
	// namedWindow("after IDFT", 0);
	 //createTrackbar("d0", "after IDFT", &d0, 200);
	for (int i = 0; i < Lfilter.rows; i++)
		for (int j = 0; j < Lfilter.cols; j++)
		{
			double z1 = i - Lfilter.rows / 2;
			double z2 = j - Lfilter.cols / 2;
			if (sqrt(pow(z1, 2) + pow(z2, 2)) <= freqValue)
				Lfilter.at<float>(i, j) = 1;
			else
				Lfilter.at<float>(i, j) = 0;
		}
	namedWindow("Lfilter", 0);
	imshow("Lfilter", Lfilter);
	split(complexI, planes);
	Mat outR, outI;
	multiply(planes[0], Lfilter, outR);
	multiply(planes[1], Lfilter, outI);
	Mat out_planes[2] = { outR, outI };
	Mat out_complexI;
	merge(out_planes, 2, out_complexI);
	idft(out_complexI, out_complexI);
	split(out_complexI, planes);

	magnitude(planes[0], planes[1], imageClone);
	normalize(imageClone, imageClone, 1, 0, cv::NORM_MINMAX);
	imageClone.convertTo(imageClone, CV_8SC1, 255);
	convertScaleAbs(imageClone, imageClone);

	ConvertGrayscaleToBitmap(imageClone);

}
private: System::Void LPF_trackBar_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {

	undoStack.push(image.clone());
	image = imageClone;
}
private: System::Void threshold_label_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void size_label_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void userManual_button_Click(System::Object^ sender, System::EventArgs^ e) {

	System::String^ guideMessage = "manual Guide:\n\n";

	guideMessage += "Histogram Equalization: Enhances the contrast of the image.\n\n";
	guideMessage += "Log Transformation: Adjusts the intensity of the pixels using a logarithmic function.\n\n";
	guideMessage += "Negative: Inverts the colors of the image.\n\n";
	guideMessage += "Rotations: Rotates the image by 270 degrees.\n\n";
	guideMessage += "Crop: Crops the image to a selected region.\n\n";
	guideMessage += "Blinding: Blends the image with another image.\n\n";
	guideMessage += "Skewing: Skews the image based on the specified value.\n\n";
	guideMessage += "Edge Detection: use derivative filter, makes a high pass filter to detect the edges to get the object off the image.\n\n";
	guideMessage += "Flip: Flips the image horizontally, vertically, or both.\n\n";
	guideMessage += "Bit-Plane Slicing: Slices the image based on selected bit planes.\n\n";
	guideMessage += "Translation: Translates the image by a specified value.\n\n";
	guideMessage += "Gamma Correction: Adjusts the brightness of the image.\n\n";
	guideMessage += "Image Filtering: Applies various filters to the image.\n\n";
	guideMessage += "Gray Level Slicing: Highlights pixels within a specified intensity range.\n\n";
	guideMessage += "Thresholding: Converts the image to binary based on a threshold value.\n\n";
	guideMessage += "Low-Pass Filter: Applies a low-pass filter to the image.\n";

	MessageBox::Show(guideMessage, "User manual");
}
private: System::Void label5_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void skewing_textBox_TextChanged(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void laplace_trackBar_Scroll(System::Object^ sender, System::EventArgs^ e) {
	 laplaceValue = laplace_trackBar->Value;
	if (laplaceValue % 2 == 0) {
		// Make it odd by incrementing (you can adjust as needed)
		laplaceValue++;
		laplace_trackBar->Value = laplaceValue;
	}
}
private: System::Void GammaBar_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
	undoStack.push(image.clone());
	image = imageClone;
}
};
}
