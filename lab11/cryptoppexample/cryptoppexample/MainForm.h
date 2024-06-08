#pragma once
#include <string>
#include <Windows.h>
#include <msclr\marshal_cppstd.h>

namespace cryptoppexample
{
	void run_process_on_file(std::string execname, std::string filename);

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
		}

	protected:
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button4;

	private: System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(13, 96);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(510, 36);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Symmetrical (en/de)cryption";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(13, 45);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(510, 26);
			this->textBox1->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 22);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(74, 20);
			this->label1->TabIndex = 2;
			this->label1->Text = L"Filename";
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(12, 138);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(510, 36);
			this->button2->TabIndex = 0;
			this->button2->Text = L"Asymmetrical (en/de)cryption";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MainForm::button2_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(13, 180);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(510, 36);
			this->button3->TabIndex = 0;
			this->button3->Text = L"Sign/Verify";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MainForm::button3_Click);
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(13, 222);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(510, 36);
			this->button4->TabIndex = 0;
			this->button4->Text = L"Hash";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &MainForm::button4_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(535, 277);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"MainForm";
			this->Text = L"cryptopp";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		System::Void button1_Click(System::Object^ sender, System::EventArgs^ e)
		{
			run_process_on_file("cryptopp_sym.exe", msclr::interop::marshal_as<std::string>(textBox1->Text));
		}

	private:
		System::Void button2_Click(System::Object^ sender, System::EventArgs^ e)
		{
			run_process_on_file("cryptopp_asym.exe", msclr::interop::marshal_as<std::string>(textBox1->Text));
		}

	private:
		System::Void button3_Click(System::Object^ sender, System::EventArgs^ e)
		{
			run_process_on_file("cryptopp_sign.exe", msclr::interop::marshal_as<std::string>(textBox1->Text));
		}

	private:
		System::Void button4_Click(System::Object^ sender, System::EventArgs^ e)
		{
			run_process_on_file("cryptopp_hash.exe", msclr::interop::marshal_as<std::string>(textBox1->Text));
		}
	};
}
