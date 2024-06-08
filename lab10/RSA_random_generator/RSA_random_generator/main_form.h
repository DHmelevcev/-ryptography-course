#pragma once
#include "rsa_generator.h"
#include "binary_statistics.h"

namespace RSArandomgenerator {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class main_form : public System::Windows::Forms::Form
	{
	public:
		main_form(void)
		{
			InitializeComponent();
		}

	protected:
		~main_form()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ textBox5;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;

	private: System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(14, 74);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(577, 34);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Generate";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &main_form::button1_Click);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(60, 12);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(280, 26);
			this->textBox1->TabIndex = 1;
			this->textBox1->Text = L"0";
			// 
			// textBox2
			// 
			this->textBox2->Location = System::Drawing::Point(14, 162);
			this->textBox2->Name = L"textBox2";
			this->textBox2->ReadOnly = true;
			this->textBox2->Size = System::Drawing::Size(577, 26);
			this->textBox2->TabIndex = 1;
			// 
			// textBox3
			// 
			this->textBox3->Location = System::Drawing::Point(14, 218);
			this->textBox3->Name = L"textBox3";
			this->textBox3->ReadOnly = true;
			this->textBox3->Size = System::Drawing::Size(577, 26);
			this->textBox3->TabIndex = 1;
			// 
			// textBox4
			// 
			this->textBox4->Location = System::Drawing::Point(14, 280);
			this->textBox4->Multiline = true;
			this->textBox4->Name = L"textBox4";
			this->textBox4->ReadOnly = true;
			this->textBox4->Size = System::Drawing::Size(577, 522);
			this->textBox4->TabIndex = 1;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(10, 18);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(44, 20);
			this->label1->TabIndex = 2;
			this->label1->Text = L"seed";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(10, 139);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(84, 20);
			this->label2->TabIndex = 3;
			this->label2->Text = L"Frequency";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(275, 130);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(48, 20);
			this->label3->TabIndex = 4;
			this->label3->Text = L"Tests";
			// 
			// textBox5
			// 
			this->textBox5->Location = System::Drawing::Point(386, 12);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(205, 26);
			this->textBox5->TabIndex = 1;
			this->textBox5->Text = L"10000";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(346, 15);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(34, 20);
			this->label4->TabIndex = 2;
			this->label4->Text = L"bits";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(10, 195);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(50, 20);
			this->label5->TabIndex = 3;
			this->label5->Text = L"Chain";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(10, 257);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(77, 20);
			this->label6->TabIndex = 3;
			this->label6->Text = L"Extended";
			// 
			// main_form
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 20);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(607, 814);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label6);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->textBox4);
			this->Controls->Add(this->textBox3);
			this->Controls->Add(this->textBox5);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->button1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"main_form";
			this->Text = L"RSA generator";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private:
		System::Void button1_Click(System::Object^ sender, System::EventArgs^ e)
		{
			RSArandomgenerator::RSA_gen<slim::uint512_t> gen(Convert::ToUInt32(textBox1->Text));
			std::vector<bool> sample(Convert::ToUInt64(textBox5->Text), false);

			for (uint_t i = 0; i < sample.size(); ++i) {
				sample[i] = gen.next_bit();
				//std::cout << sample[i];
			}

			textBox2->Text = Convert::ToString(frequency_test(sample, "frectestsum.txt"));
			textBox3->Text = Convert::ToString(chain_test(sample, "chaintest"));
			auto ext_rnd_res = extended_randomness_test(sample, "extendedtest");
			textBox4->Text = "";
			for (const auto& it : ext_rnd_res) {
				textBox4->Text += Convert::ToString(it) + Environment::NewLine;
			}

			saveVector(sample, "result.txt");
		}
	};
}
