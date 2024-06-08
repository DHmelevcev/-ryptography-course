#pragma once
#include <string>

#include <cryptlib.h>
#include <filters.h>
#include <sha.h>

#include "Server.h"

namespace RBAC {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace Runtime::InteropServices;

	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();

			server = new Server();
			permissions = new uint16_t {};
			cookie = new char[Server::cookie_lenght] {};
		}

	protected:
		~MainForm()
		{
			if (components)
			{
				delete components;
				delete server;
				delete permissions;
				delete cookie;
			}
		}

	private: Server* server;
	private: uint16_t* permissions;
	private: char* cookie;

	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::TextBox^ textBox3;

	private: System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(42, 96);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(585, 26);
			this->textBox1->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(42, 70);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(55, 20);
			this->label1->TabIndex = 0;
			this->label1->Text = L"Логин";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(42, 178);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(585, 26);
			this->textBox2->TabIndex = 1;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(42, 152);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(67, 20);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Пароль";
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::SystemColors::Window;
			this->button1->Location = System::Drawing::Point(244, 257);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(181, 57);
			this->button1->TabIndex = 2;
			this->button1->Text = L"Войти";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &MainForm::login_button_click);
			// 
			// button2
			// 
			this->button2->Enabled = false;
			this->button2->Location = System::Drawing::Point(46, 257);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(162, 57);
			this->button2->TabIndex = 3;
			this->button2->Text = L"Прочитать";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Visible = false;
			this->button2->Click += gcnew System::EventHandler(this, &MainForm::read_button_click);
			// 
			// button3
			// 
			this->button3->Enabled = false;
			this->button3->Location = System::Drawing::Point(253, 257);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(162, 57);
			this->button3->TabIndex = 3;
			this->button3->Text = L"Записать";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Visible = false;
			this->button3->Click += gcnew System::EventHandler(this, &MainForm::write_button_click);
			// 
			// button4
			// 
			this->button4->Enabled = false;
			this->button4->Location = System::Drawing::Point(465, 257);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(162, 57);
			this->button4->TabIndex = 3;
			this->button4->Text = L"Очистить";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Visible = false;
			this->button4->Click += gcnew System::EventHandler(this, &MainForm::clear_button_click);
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(46, 29);
			this->textBox3->Multiline = true;
			this->textBox3->Name = L"textBox3";
			this->textBox3->ReadOnly = true;
			this->textBox3->Size = System::Drawing::Size(581, 222);
			this->textBox3->TabIndex = 4;
			this->textBox3->Visible = false;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(683, 406);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"MainForm";
			this->Text = L"RBAC";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		System::Void login_button_click(System::Object^ sender,System::EventArgs^ e);

		System::Void read_button_click(System::Object^ sender, System::EventArgs^ e);

		System::Void write_button_click(System::Object^ sender, System::EventArgs^ e);

		System::Void clear_button_click(System::Object^ sender, System::EventArgs^ e);
	};
}
