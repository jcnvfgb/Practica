#pragma once

#include <string>
#include "TemplateMatcher.h"
#include "KeypointMatcher.h"

namespace Practica {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::IO;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form {
	public:
		MyForm(void) {
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm() {
			if (components) {
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;
		System::Windows::Forms::Label^ label3;
		System::Windows::Forms::Label^ label4;


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void) {
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 29);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(260, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Выбрать картинку";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(219, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Нажмите на кнопку для выбора картинки";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(12, 80);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(202, 13);
			this->label2->TabIndex = 2;
			this->label2->Text = L"Нажмите на кнопку для выбора видео";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(12, 96);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(260, 23);
			this->button2->TabIndex = 3;
			this->button2->Text = L"Выбрать видео";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(12, 149);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(260, 23);
			this->button3->TabIndex = 4;
			this->button3->Text = L"Начать поиск";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(13, 55);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(35, 13);
			this->label3->TabIndex = 5;
			this->label3->Text = L"label3";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(13, 122);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(35, 13);
			this->label4->TabIndex = 6;
			this->label4->Text = L"label4";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 261);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


	public: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
		OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();
		openFileDialog->Filter = "Image Files (*.bmp;*.jpg;*.jpeg;*.png;*.gif)|*.bmp;*.jpg;*.jpeg;*.png;*.gif";
		openFileDialog->Title = "Open Image";

		if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			this->label3->Text = openFileDialog->FileName;
		}
	}
	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
		OpenFileDialog^ openFileDialog = gcnew OpenFileDialog();
		openFileDialog->Filter = "Video Files (*.avi;*.mp4;*.mkv;*.flv;*.3gp)|*.avi;*.mp4;*.mkv;*.flv;*.3gp";
		openFileDialog->Title = "Open Video";

		if (openFileDialog->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			this->label4->Text = openFileDialog->FileName;
		}
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		const char* videoFilePathPtr = (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(label4->Text).ToPointer());
		std::string videoFilePath(videoFilePathPtr, label4->Text->Length);
		System::Runtime::InteropServices::Marshal::FreeHGlobal(System::IntPtr((void*)videoFilePathPtr));

		const char* templateFilePathPtr = (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(label3->Text).ToPointer());
		std::string templateFilePath(templateFilePathPtr, label3->Text->Length);
		System::Runtime::InteropServices::Marshal::FreeHGlobal(System::IntPtr((void*)templateFilePathPtr));

		//double threshold = 0.8;

		//TemplateMatcher matcher(videoFilePath, templateFilePath, threshold);
		//matcher.match();

		cv::Mat img_object = cv::imread(templateFilePath);
		cv::VideoCapture cap = cv::VideoCapture(videoFilePath);

		KeypointMatcher matcher(0.5f, img_object);

		cv::Mat frame, frame_found;

		while (cap.read(frame)) {

			matcher.Match(frame, frame_found);

			imshow("Video", frame_found);

			if (cv::waitKey(1) == 'q') {
				return;
			}
		};

	}
	};
}
