#pragma once
#include <string>

namespace MyForms {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class main_form : public System::Windows::Forms::Form
	{
	public:
		main_form(void) : text_chngd(new bool(true))
		{
			InitializeComponent();

			textBox2->Text = file_to_HexString("input.txt");
			textBox1->Text = HexString_to_String(textBox2->Text);
			textBox3->Text = HexString_to_BinString(textBox2->Text);

			textBox5->Text = file_to_HexString("key.txt");
			textBox4->Text = HexString_to_String(textBox5->Text);
			textBox6->Text = HexString_to_BinString(textBox5->Text);
			textBox13->Text = textBox4->Text;
			textBox14->Text = textBox5->Text;
			textBox15->Text = textBox6->Text;

			*text_chngd = false;
		}

	protected:
		~main_form()
		{
			if (components)
			{
				delete components;
			}
		}

	protected:
		bool* text_chngd;

		static String^ file_to_String(const std::string& filename);
		static String^ file_to_HexString(const std::string& filename);
		static String^ file_to_BinString(const std::string& filename);

		static void String_to_file(String^ str, const std::string& filename);
		static void HexString_to_file(String^ str, const std::string& filename);

		static String^ String_to_HexString(String^ str);
		static String^ String_to_BinString(String^ str);
		static String^ HexString_to_String(String^ str);
		static String^ HexString_to_BinString(String^ str);
		static String^ BinString_to_HexString(String^ str);
		static String^ BinString_to_String(String^ str);

		void textBoxChrChanged(TextBox^ textBoxC, TextBox^ textBoxH, TextBox^ textBoxB);
		void textBoxHexChanged(TextBox^ textBoxC, TextBox^ textBoxH, TextBox^ textBoxB);
		void textBoxBinChanged(TextBox^ textBoxC, TextBox^ textBoxH, TextBox^ textBoxB);

		bool encryption_begin();
		void encryption_end();
		bool decryption_begin();
		void decryption_end();

	private: System::ComponentModel::Container^ components;

	private: System::Windows::Forms::TabPage^ tabPage2;
	private: System::Windows::Forms::TabPage^ tabPage1;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TabControl^ tabControl;
	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TextBox^ textBox9;
	private: System::Windows::Forms::TextBox^ textBox6;
	private: System::Windows::Forms::TextBox^ textBox8;
	private: System::Windows::Forms::TextBox^ textBox5;
	private: System::Windows::Forms::TextBox^ textBox7;
	private: System::Windows::Forms::TextBox^ textBox3;
	private: System::Windows::Forms::TextBox^ textBox4;
	private: System::Windows::Forms::Button^ button8;
	private: System::Windows::Forms::Button^ button7;
	private: System::Windows::Forms::Button^ button6;
	private: System::Windows::Forms::Button^ button5;
	private: System::Windows::Forms::Label^ label13;
	private: System::Windows::Forms::Label^ label14;
	private: System::Windows::Forms::Label^ label15;
	private: System::Windows::Forms::Label^ label16;
	private: System::Windows::Forms::Label^ label17;
	private: System::Windows::Forms::Label^ label18;
	private: System::Windows::Forms::Label^ label19;
	private: System::Windows::Forms::Label^ label20;
	private: System::Windows::Forms::Label^ label21;
	private: System::Windows::Forms::Label^ label22;
	private: System::Windows::Forms::TextBox^ textBox18;
	private: System::Windows::Forms::Label^ label23;
	private: System::Windows::Forms::TextBox^ textBox15;
	private: System::Windows::Forms::TextBox^ textBox17;
	private: System::Windows::Forms::Label^ label24;
	private: System::Windows::Forms::TextBox^ textBox14;
	private: System::Windows::Forms::TextBox^ textBox16;
	private: System::Windows::Forms::TextBox^ textBox12;
	private: System::Windows::Forms::TextBox^ textBox13;
	private: System::Windows::Forms::TextBox^ textBox11;
	private: System::Windows::Forms::TextBox^ textBox10;
	private: System::Windows::Forms::Button^ button4;
	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::TabPage^ tabPage3;
	private: System::Windows::Forms::Label^ label40;
	private: System::Windows::Forms::Label^ label25;
	private: System::Windows::Forms::Label^ label39;
	private: System::Windows::Forms::Label^ label26;
	private: System::Windows::Forms::Label^ label38;
	private: System::Windows::Forms::Label^ label37;
	private: System::Windows::Forms::Label^ label27;
	private: System::Windows::Forms::Label^ label36;
	private: System::Windows::Forms::Label^ label28;
	private: System::Windows::Forms::Label^ label35;
	private: System::Windows::Forms::Label^ label29;
	private: System::Windows::Forms::Label^ label34;
	private: System::Windows::Forms::Label^ label30;
	private: System::Windows::Forms::TextBox^ textBox30;
	private: System::Windows::Forms::Label^ label31;
	private: System::Windows::Forms::Label^ label33;
	private: System::Windows::Forms::TextBox^ textBox24;
	private: System::Windows::Forms::TextBox^ textBox29;
	private: System::Windows::Forms::Label^ label32;
	private: System::Windows::Forms::TextBox^ textBox27;
	private: System::Windows::Forms::TextBox^ textBox23;
	private: System::Windows::Forms::TextBox^ textBox28;
	private: System::Windows::Forms::TextBox^ textBox21;
	private: System::Windows::Forms::TextBox^ textBox26;
	private: System::Windows::Forms::TextBox^ textBox22;
	private: System::Windows::Forms::TextBox^ textBox25;
	private: System::Windows::Forms::TextBox^ textBox20;
	private: System::Windows::Forms::TextBox^ textBox19;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Button^ button12;
	private: System::Windows::Forms::Button^ button11;
	private: System::Windows::Forms::Button^ button10;
	private: System::Windows::Forms::Button^ button9;

#pragma region Windows Form Designer generated code

		void InitializeComponent(void)
		{
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->button8 = (gcnew System::Windows::Forms::Button());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->button5 = (gcnew System::Windows::Forms::Button());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label21 = (gcnew System::Windows::Forms::Label());
			this->label22 = (gcnew System::Windows::Forms::Label());
			this->textBox18 = (gcnew System::Windows::Forms::TextBox());
			this->label23 = (gcnew System::Windows::Forms::Label());
			this->textBox15 = (gcnew System::Windows::Forms::TextBox());
			this->textBox17 = (gcnew System::Windows::Forms::TextBox());
			this->label24 = (gcnew System::Windows::Forms::Label());
			this->textBox14 = (gcnew System::Windows::Forms::TextBox());
			this->textBox16 = (gcnew System::Windows::Forms::TextBox());
			this->textBox12 = (gcnew System::Windows::Forms::TextBox());
			this->textBox13 = (gcnew System::Windows::Forms::TextBox());
			this->textBox11 = (gcnew System::Windows::Forms::TextBox());
			this->textBox10 = (gcnew System::Windows::Forms::TextBox());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->textBox9 = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->textBox6 = (gcnew System::Windows::Forms::TextBox());
			this->textBox8 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->textBox5 = (gcnew System::Windows::Forms::TextBox());
			this->textBox7 = (gcnew System::Windows::Forms::TextBox());
			this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			this->textBox4 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->tabControl = (gcnew System::Windows::Forms::TabControl());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->button12 = (gcnew System::Windows::Forms::Button());
			this->button11 = (gcnew System::Windows::Forms::Button());
			this->button10 = (gcnew System::Windows::Forms::Button());
			this->button9 = (gcnew System::Windows::Forms::Button());
			this->label40 = (gcnew System::Windows::Forms::Label());
			this->label25 = (gcnew System::Windows::Forms::Label());
			this->label39 = (gcnew System::Windows::Forms::Label());
			this->label26 = (gcnew System::Windows::Forms::Label());
			this->label38 = (gcnew System::Windows::Forms::Label());
			this->label37 = (gcnew System::Windows::Forms::Label());
			this->label27 = (gcnew System::Windows::Forms::Label());
			this->label36 = (gcnew System::Windows::Forms::Label());
			this->label28 = (gcnew System::Windows::Forms::Label());
			this->label35 = (gcnew System::Windows::Forms::Label());
			this->label29 = (gcnew System::Windows::Forms::Label());
			this->label34 = (gcnew System::Windows::Forms::Label());
			this->label30 = (gcnew System::Windows::Forms::Label());
			this->textBox30 = (gcnew System::Windows::Forms::TextBox());
			this->label31 = (gcnew System::Windows::Forms::Label());
			this->label33 = (gcnew System::Windows::Forms::Label());
			this->textBox24 = (gcnew System::Windows::Forms::TextBox());
			this->textBox29 = (gcnew System::Windows::Forms::TextBox());
			this->label32 = (gcnew System::Windows::Forms::Label());
			this->textBox27 = (gcnew System::Windows::Forms::TextBox());
			this->textBox23 = (gcnew System::Windows::Forms::TextBox());
			this->textBox28 = (gcnew System::Windows::Forms::TextBox());
			this->textBox21 = (gcnew System::Windows::Forms::TextBox());
			this->textBox26 = (gcnew System::Windows::Forms::TextBox());
			this->textBox22 = (gcnew System::Windows::Forms::TextBox());
			this->textBox25 = (gcnew System::Windows::Forms::TextBox());
			this->textBox20 = (gcnew System::Windows::Forms::TextBox());
			this->textBox19 = (gcnew System::Windows::Forms::TextBox());
			this->tabPage2->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabControl->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->SuspendLayout();
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->button8);
			this->tabPage2->Controls->Add(this->button7);
			this->tabPage2->Controls->Add(this->button6);
			this->tabPage2->Controls->Add(this->button5);
			this->tabPage2->Controls->Add(this->label13);
			this->tabPage2->Controls->Add(this->label14);
			this->tabPage2->Controls->Add(this->label15);
			this->tabPage2->Controls->Add(this->label16);
			this->tabPage2->Controls->Add(this->label17);
			this->tabPage2->Controls->Add(this->label18);
			this->tabPage2->Controls->Add(this->label19);
			this->tabPage2->Controls->Add(this->label20);
			this->tabPage2->Controls->Add(this->label21);
			this->tabPage2->Controls->Add(this->label22);
			this->tabPage2->Controls->Add(this->textBox18);
			this->tabPage2->Controls->Add(this->label23);
			this->tabPage2->Controls->Add(this->textBox15);
			this->tabPage2->Controls->Add(this->textBox17);
			this->tabPage2->Controls->Add(this->label24);
			this->tabPage2->Controls->Add(this->textBox14);
			this->tabPage2->Controls->Add(this->textBox16);
			this->tabPage2->Controls->Add(this->textBox12);
			this->tabPage2->Controls->Add(this->textBox13);
			this->tabPage2->Controls->Add(this->textBox11);
			this->tabPage2->Controls->Add(this->textBox10);
			this->tabPage2->Location = System::Drawing::Point(4, 29);
			this->tabPage2->Margin = System::Windows::Forms::Padding(0);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Size = System::Drawing::Size(1254, 633);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"Decryption";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// button8
			// 
			this->button8->Location = System::Drawing::Point(927, 505);
			this->button8->Name = L"button8";
			this->button8->Size = System::Drawing::Size(250, 75);
			this->button8->TabIndex = 28;
			this->button8->Text = L"Vi = 32LFSR(8), F = S(X) xor Vi";
			this->button8->UseVisualStyleBackColor = true;
			this->button8->Click += gcnew System::EventHandler(this, &main_form::button8_Click);
			// 
			// button7
			// 
			this->button7->Location = System::Drawing::Point(645, 505);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(250, 75);
			this->button7->TabIndex = 27;
			this->button7->Text = L"Vi = 32, F = S(X) xor Vi";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &main_form::button7_Click);
			// 
			// button6
			// 
			this->button6->Location = System::Drawing::Point(361, 505);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(250, 75);
			this->button6->TabIndex = 26;
			this->button6->Text = L"Vi = 32LFSR(8), F = Vi";
			this->button6->UseVisualStyleBackColor = true;
			this->button6->Click += gcnew System::EventHandler(this, &main_form::button6_Click);
			// 
			// button5
			// 
			this->button5->Location = System::Drawing::Point(77, 505);
			this->button5->Name = L"button5";
			this->button5->Size = System::Drawing::Size(250, 75);
			this->button5->TabIndex = 25;
			this->button5->Text = L"Vi = 32, F = Vi";
			this->button5->UseVisualStyleBackColor = true;
			this->button5->Click += gcnew System::EventHandler(this, &main_form::button5_Click);
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label13->Location = System::Drawing::Point(72, 326);
			this->label13->Margin = System::Windows::Forms::Padding(3, 20, 3, 0);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(101, 25);
			this->label13->TabIndex = 24;
			this->label13->Text = L"Decrypted";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label14->Location = System::Drawing::Point(33, 426);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(38, 25);
			this->label14->TabIndex = 20;
			this->label14->Text = L"bin";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label15->Location = System::Drawing::Point(72, 173);
			this->label15->Margin = System::Windows::Forms::Padding(3, 20, 3, 0);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(47, 25);
			this->label15->TabIndex = 23;
			this->label15->Text = L"Key";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label16->Location = System::Drawing::Point(33, 273);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(38, 25);
			this->label16->TabIndex = 19;
			this->label16->Text = L"bin";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label17->Location = System::Drawing::Point(27, 390);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(44, 25);
			this->label17->TabIndex = 18;
			this->label17->Text = L"hex";
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label18->Location = System::Drawing::Point(72, 20);
			this->label18->Margin = System::Windows::Forms::Padding(3, 20, 3, 0);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(100, 25);
			this->label18->TabIndex = 22;
			this->label18->Text = L"Encrypted";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label19->Location = System::Drawing::Point(27, 237);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(44, 25);
			this->label19->TabIndex = 17;
			this->label19->Text = L"hex";
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label20->Location = System::Drawing::Point(32, 354);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(39, 25);
			this->label20->TabIndex = 21;
			this->label20->Text = L"chr";
			// 
			// label21
			// 
			this->label21->AutoSize = true;
			this->label21->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label21->Location = System::Drawing::Point(33, 120);
			this->label21->Name = L"label21";
			this->label21->Size = System::Drawing::Size(38, 25);
			this->label21->TabIndex = 16;
			this->label21->Text = L"bin";
			// 
			// label22
			// 
			this->label22->AutoSize = true;
			this->label22->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label22->Location = System::Drawing::Point(32, 201);
			this->label22->Name = L"label22";
			this->label22->Size = System::Drawing::Size(39, 25);
			this->label22->TabIndex = 15;
			this->label22->Text = L"chr";
			// 
			// textBox18
			// 
			this->textBox18->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox18->Location = System::Drawing::Point(77, 426);
			this->textBox18->Name = L"textBox18";
			this->textBox18->ReadOnly = true;
			this->textBox18->Size = System::Drawing::Size(1100, 30);
			this->textBox18->TabIndex = 11;
			// 
			// label23
			// 
			this->label23->AutoSize = true;
			this->label23->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label23->Location = System::Drawing::Point(27, 84);
			this->label23->Name = L"label23";
			this->label23->Size = System::Drawing::Size(44, 25);
			this->label23->TabIndex = 14;
			this->label23->Text = L"hex";
			// 
			// textBox15
			// 
			this->textBox15->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox15->Location = System::Drawing::Point(77, 273);
			this->textBox15->Name = L"textBox15";
			this->textBox15->Size = System::Drawing::Size(1100, 30);
			this->textBox15->TabIndex = 10;
			this->textBox15->TextChanged += gcnew System::EventHandler(this, &main_form::textBox15_TextChanged);
			// 
			// textBox17
			// 
			this->textBox17->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox17->Location = System::Drawing::Point(77, 390);
			this->textBox17->Name = L"textBox17";
			this->textBox17->ReadOnly = true;
			this->textBox17->Size = System::Drawing::Size(1100, 30);
			this->textBox17->TabIndex = 9;
			// 
			// label24
			// 
			this->label24->AutoSize = true;
			this->label24->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label24->Location = System::Drawing::Point(32, 48);
			this->label24->Name = L"label24";
			this->label24->Size = System::Drawing::Size(39, 25);
			this->label24->TabIndex = 13;
			this->label24->Text = L"chr";
			// 
			// textBox14
			// 
			this->textBox14->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox14->Location = System::Drawing::Point(77, 237);
			this->textBox14->Name = L"textBox14";
			this->textBox14->Size = System::Drawing::Size(1100, 30);
			this->textBox14->TabIndex = 8;
			this->textBox14->TextChanged += gcnew System::EventHandler(this, &main_form::textBox14_TextChanged);
			// 
			// textBox16
			// 
			this->textBox16->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox16->Location = System::Drawing::Point(77, 354);
			this->textBox16->Name = L"textBox16";
			this->textBox16->ReadOnly = true;
			this->textBox16->Size = System::Drawing::Size(1100, 30);
			this->textBox16->TabIndex = 7;
			// 
			// textBox12
			// 
			this->textBox12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox12->Location = System::Drawing::Point(77, 120);
			this->textBox12->Name = L"textBox12";
			this->textBox12->Size = System::Drawing::Size(1100, 30);
			this->textBox12->TabIndex = 6;
			this->textBox12->TextChanged += gcnew System::EventHandler(this, &main_form::textBox12_TextChanged);
			// 
			// textBox13
			// 
			this->textBox13->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox13->Location = System::Drawing::Point(77, 201);
			this->textBox13->Name = L"textBox13";
			this->textBox13->Size = System::Drawing::Size(1100, 30);
			this->textBox13->TabIndex = 5;
			this->textBox13->TextChanged += gcnew System::EventHandler(this, &main_form::textBox13_TextChanged);
			// 
			// textBox11
			// 
			this->textBox11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox11->Location = System::Drawing::Point(77, 84);
			this->textBox11->Name = L"textBox11";
			this->textBox11->Size = System::Drawing::Size(1100, 30);
			this->textBox11->TabIndex = 12;
			this->textBox11->TextChanged += gcnew System::EventHandler(this, &main_form::textBox11_TextChanged);
			// 
			// textBox10
			// 
			this->textBox10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox10->Location = System::Drawing::Point(77, 48);
			this->textBox10->Name = L"textBox10";
			this->textBox10->Size = System::Drawing::Size(1100, 30);
			this->textBox10->TabIndex = 4;
			this->textBox10->TextChanged += gcnew System::EventHandler(this, &main_form::textBox10_TextChanged);
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->button4);
			this->tabPage1->Controls->Add(this->button3);
			this->tabPage1->Controls->Add(this->button2);
			this->tabPage1->Controls->Add(this->button1);
			this->tabPage1->Controls->Add(this->label12);
			this->tabPage1->Controls->Add(this->label11);
			this->tabPage1->Controls->Add(this->label8);
			this->tabPage1->Controls->Add(this->label7);
			this->tabPage1->Controls->Add(this->label10);
			this->tabPage1->Controls->Add(this->label4);
			this->tabPage1->Controls->Add(this->label6);
			this->tabPage1->Controls->Add(this->label9);
			this->tabPage1->Controls->Add(this->label3);
			this->tabPage1->Controls->Add(this->label5);
			this->tabPage1->Controls->Add(this->textBox9);
			this->tabPage1->Controls->Add(this->label2);
			this->tabPage1->Controls->Add(this->textBox6);
			this->tabPage1->Controls->Add(this->textBox8);
			this->tabPage1->Controls->Add(this->label1);
			this->tabPage1->Controls->Add(this->textBox5);
			this->tabPage1->Controls->Add(this->textBox7);
			this->tabPage1->Controls->Add(this->textBox3);
			this->tabPage1->Controls->Add(this->textBox4);
			this->tabPage1->Controls->Add(this->textBox2);
			this->tabPage1->Controls->Add(this->textBox1);
			this->tabPage1->Location = System::Drawing::Point(4, 29);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(1254, 633);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"Encryption";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(927, 505);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(250, 75);
			this->button4->TabIndex = 3;
			this->button4->Text = L"Vi = 32LFSR(8), F = S(X) xor Vi";
			this->button4->UseVisualStyleBackColor = true;
			this->button4->Click += gcnew System::EventHandler(this, &main_form::button4_Click);
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(645, 505);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(250, 75);
			this->button3->TabIndex = 3;
			this->button3->Text = L"Vi = 32, F = S(X) xor Vi";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &main_form::button3_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(361, 505);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(250, 75);
			this->button2->TabIndex = 3;
			this->button2->Text = L"Vi = 32LFSR(8), F = Vi";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &main_form::button2_Click);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(77, 505);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(250, 75);
			this->button1->TabIndex = 3;
			this->button1->Text = L"Vi = 32, F = Vi";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &main_form::button1_Click);
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label12->Location = System::Drawing::Point(72, 326);
			this->label12->Margin = System::Windows::Forms::Padding(3, 20, 3, 0);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(100, 25);
			this->label12->TabIndex = 2;
			this->label12->Text = L"Encrypted";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label11->Location = System::Drawing::Point(33, 426);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(38, 25);
			this->label11->TabIndex = 1;
			this->label11->Text = L"bin";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label8->Location = System::Drawing::Point(72, 173);
			this->label8->Margin = System::Windows::Forms::Padding(3, 20, 3, 0);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(47, 25);
			this->label8->TabIndex = 2;
			this->label8->Text = L"Key";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label7->Location = System::Drawing::Point(33, 273);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(38, 25);
			this->label7->TabIndex = 1;
			this->label7->Text = L"bin";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label10->Location = System::Drawing::Point(27, 390);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(44, 25);
			this->label10->TabIndex = 1;
			this->label10->Text = L"hex";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label4->Location = System::Drawing::Point(72, 20);
			this->label4->Margin = System::Windows::Forms::Padding(3, 20, 3, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(93, 25);
			this->label4->TabIndex = 2;
			this->label4->Text = L"Message";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label6->Location = System::Drawing::Point(27, 237);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(44, 25);
			this->label6->TabIndex = 1;
			this->label6->Text = L"hex";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label9->Location = System::Drawing::Point(32, 354);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(39, 25);
			this->label9->TabIndex = 1;
			this->label9->Text = L"chr";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label3->Location = System::Drawing::Point(33, 120);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(38, 25);
			this->label3->TabIndex = 1;
			this->label3->Text = L"bin";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label5->Location = System::Drawing::Point(32, 201);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(39, 25);
			this->label5->TabIndex = 1;
			this->label5->Text = L"chr";
			// 
			// textBox9
			// 
			this->textBox9->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox9->Location = System::Drawing::Point(77, 426);
			this->textBox9->Name = L"textBox9";
			this->textBox9->ReadOnly = true;
			this->textBox9->Size = System::Drawing::Size(1100, 30);
			this->textBox9->TabIndex = 0;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label2->Location = System::Drawing::Point(27, 84);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(44, 25);
			this->label2->TabIndex = 1;
			this->label2->Text = L"hex";
			// 
			// textBox6
			// 
			this->textBox6->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox6->Location = System::Drawing::Point(77, 273);
			this->textBox6->Name = L"textBox6";
			this->textBox6->Size = System::Drawing::Size(1100, 30);
			this->textBox6->TabIndex = 0;
			this->textBox6->TextChanged += gcnew System::EventHandler(this, &main_form::textBox6_TextChanged);
			// 
			// textBox8
			// 
			this->textBox8->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox8->Location = System::Drawing::Point(77, 390);
			this->textBox8->Name = L"textBox8";
			this->textBox8->ReadOnly = true;
			this->textBox8->Size = System::Drawing::Size(1100, 30);
			this->textBox8->TabIndex = 0;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label1->Location = System::Drawing::Point(32, 48);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(39, 25);
			this->label1->TabIndex = 1;
			this->label1->Text = L"chr";
			// 
			// textBox5
			// 
			this->textBox5->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox5->Location = System::Drawing::Point(77, 237);
			this->textBox5->Name = L"textBox5";
			this->textBox5->Size = System::Drawing::Size(1100, 30);
			this->textBox5->TabIndex = 0;
			this->textBox5->TextChanged += gcnew System::EventHandler(this, &main_form::textBox5_TextChanged);
			// 
			// textBox7
			// 
			this->textBox7->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox7->Location = System::Drawing::Point(77, 354);
			this->textBox7->Name = L"textBox7";
			this->textBox7->ReadOnly = true;
			this->textBox7->Size = System::Drawing::Size(1100, 30);
			this->textBox7->TabIndex = 0;
			// 
			// textBox3
			// 
			this->textBox3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox3->Location = System::Drawing::Point(77, 120);
			this->textBox3->Name = L"textBox3";
			this->textBox3->Size = System::Drawing::Size(1100, 30);
			this->textBox3->TabIndex = 0;
			this->textBox3->TextChanged += gcnew System::EventHandler(this, &main_form::textBox3_TextChanged);
			// 
			// textBox4
			// 
			this->textBox4->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox4->Location = System::Drawing::Point(77, 201);
			this->textBox4->Name = L"textBox4";
			this->textBox4->Size = System::Drawing::Size(1100, 30);
			this->textBox4->TabIndex = 0;
			this->textBox4->TextChanged += gcnew System::EventHandler(this, &main_form::textBox4_TextChanged);
			// 
			// textBox2
			// 
			this->textBox2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox2->Location = System::Drawing::Point(77, 84);
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(1100, 30);
			this->textBox2->TabIndex = 0;
			this->textBox2->TextChanged += gcnew System::EventHandler(this, &main_form::textBox2_TextChanged);
			// 
			// textBox1
			// 
			this->textBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox1->Location = System::Drawing::Point(77, 48);
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(1100, 30);
			this->textBox1->TabIndex = 0;
			this->textBox1->TextChanged += gcnew System::EventHandler(this, &main_form::textBox1_TextChanged);
			// 
			// tabControl
			// 
			this->tabControl->Controls->Add(this->tabPage1);
			this->tabControl->Controls->Add(this->tabPage2);
			this->tabControl->Controls->Add(this->tabPage3);
			this->tabControl->Location = System::Drawing::Point(0, 0);
			this->tabControl->Margin = System::Windows::Forms::Padding(0);
			this->tabControl->Name = L"tabControl";
			this->tabControl->SelectedIndex = 0;
			this->tabControl->Size = System::Drawing::Size(1262, 666);
			this->tabControl->TabIndex = 1;
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->button12);
			this->tabPage3->Controls->Add(this->button11);
			this->tabPage3->Controls->Add(this->button10);
			this->tabPage3->Controls->Add(this->button9);
			this->tabPage3->Controls->Add(this->label40);
			this->tabPage3->Controls->Add(this->label25);
			this->tabPage3->Controls->Add(this->label39);
			this->tabPage3->Controls->Add(this->label26);
			this->tabPage3->Controls->Add(this->label38);
			this->tabPage3->Controls->Add(this->label37);
			this->tabPage3->Controls->Add(this->label27);
			this->tabPage3->Controls->Add(this->label36);
			this->tabPage3->Controls->Add(this->label28);
			this->tabPage3->Controls->Add(this->label35);
			this->tabPage3->Controls->Add(this->label29);
			this->tabPage3->Controls->Add(this->label34);
			this->tabPage3->Controls->Add(this->label30);
			this->tabPage3->Controls->Add(this->textBox30);
			this->tabPage3->Controls->Add(this->label31);
			this->tabPage3->Controls->Add(this->label33);
			this->tabPage3->Controls->Add(this->textBox24);
			this->tabPage3->Controls->Add(this->textBox29);
			this->tabPage3->Controls->Add(this->label32);
			this->tabPage3->Controls->Add(this->textBox27);
			this->tabPage3->Controls->Add(this->textBox23);
			this->tabPage3->Controls->Add(this->textBox28);
			this->tabPage3->Controls->Add(this->textBox21);
			this->tabPage3->Controls->Add(this->textBox26);
			this->tabPage3->Controls->Add(this->textBox22);
			this->tabPage3->Controls->Add(this->textBox25);
			this->tabPage3->Controls->Add(this->textBox20);
			this->tabPage3->Controls->Add(this->textBox19);
			this->tabPage3->Location = System::Drawing::Point(4, 29);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Padding = System::Windows::Forms::Padding(3);
			this->tabPage3->Size = System::Drawing::Size(1254, 633);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"Avalanche Test";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// button12
			// 
			this->button12->Location = System::Drawing::Point(927, 573);
			this->button12->Name = L"button12";
			this->button12->Size = System::Drawing::Size(250, 50);
			this->button12->TabIndex = 32;
			this->button12->Text = L"Vi = 32LFSR(8), F = S(X) xor Vi";
			this->button12->UseVisualStyleBackColor = true;
			this->button12->Click += gcnew System::EventHandler(this, &main_form::button12_Click);
			// 
			// button11
			// 
			this->button11->Location = System::Drawing::Point(645, 573);
			this->button11->Name = L"button11";
			this->button11->Size = System::Drawing::Size(250, 50);
			this->button11->TabIndex = 31;
			this->button11->Text = L"Vi = 32, F = S(X) xor Vi";
			this->button11->UseVisualStyleBackColor = true;
			this->button11->Click += gcnew System::EventHandler(this, &main_form::button11_Click);
			// 
			// button10
			// 
			this->button10->Location = System::Drawing::Point(361, 573);
			this->button10->Name = L"button10";
			this->button10->Size = System::Drawing::Size(250, 50);
			this->button10->TabIndex = 30;
			this->button10->Text = L"Vi = 32LFSR(8), F = Vi";
			this->button10->UseVisualStyleBackColor = true;
			this->button10->Click += gcnew System::EventHandler(this, &main_form::button10_Click);
			// 
			// button9
			// 
			this->button9->Location = System::Drawing::Point(77, 573);
			this->button9->Name = L"button9";
			this->button9->Size = System::Drawing::Size(250, 50);
			this->button9->TabIndex = 29;
			this->button9->Text = L"Vi = 32, F = Vi";
			this->button9->UseVisualStyleBackColor = true;
			this->button9->Click += gcnew System::EventHandler(this, &main_form::button9_Click);
			// 
			// label40
			// 
			this->label40->AutoSize = true;
			this->label40->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label40->Location = System::Drawing::Point(72, 428);
			this->label40->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
			this->label40->Name = L"label40";
			this->label40->Size = System::Drawing::Size(63, 25);
			this->label40->TabIndex = 15;
			this->label40->Text = L"Key 2";
			// 
			// label25
			// 
			this->label25->AutoSize = true;
			this->label25->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label25->Location = System::Drawing::Point(72, 156);
			this->label25->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
			this->label25->Name = L"label25";
			this->label25->Size = System::Drawing::Size(63, 25);
			this->label25->TabIndex = 15;
			this->label25->Text = L"Key 1";
			// 
			// label39
			// 
			this->label39->AutoSize = true;
			this->label39->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label39->Location = System::Drawing::Point(33, 528);
			this->label39->Name = L"label39";
			this->label39->Size = System::Drawing::Size(38, 25);
			this->label39->TabIndex = 9;
			this->label39->Text = L"bin";
			// 
			// label26
			// 
			this->label26->AutoSize = true;
			this->label26->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label26->Location = System::Drawing::Point(33, 256);
			this->label26->Name = L"label26";
			this->label26->Size = System::Drawing::Size(38, 25);
			this->label26->TabIndex = 9;
			this->label26->Text = L"bin";
			// 
			// label38
			// 
			this->label38->AutoSize = true;
			this->label38->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label38->Location = System::Drawing::Point(72, 292);
			this->label38->Margin = System::Windows::Forms::Padding(3, 3, 3, 0);
			this->label38->Name = L"label38";
			this->label38->Size = System::Drawing::Size(109, 25);
			this->label38->TabIndex = 16;
			this->label38->Text = L"Message 2";
			// 
			// label37
			// 
			this->label37->AutoSize = true;
			this->label37->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label37->Location = System::Drawing::Point(27, 492);
			this->label37->Name = L"label37";
			this->label37->Size = System::Drawing::Size(44, 25);
			this->label37->TabIndex = 10;
			this->label37->Text = L"hex";
			// 
			// label27
			// 
			this->label27->AutoSize = true;
			this->label27->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label27->Location = System::Drawing::Point(72, 20);
			this->label27->Margin = System::Windows::Forms::Padding(3, 20, 3, 0);
			this->label27->Name = L"label27";
			this->label27->Size = System::Drawing::Size(109, 25);
			this->label27->TabIndex = 16;
			this->label27->Text = L"Message 1";
			// 
			// label36
			// 
			this->label36->AutoSize = true;
			this->label36->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label36->Location = System::Drawing::Point(33, 392);
			this->label36->Name = L"label36";
			this->label36->Size = System::Drawing::Size(38, 25);
			this->label36->TabIndex = 11;
			this->label36->Text = L"bin";
			// 
			// label28
			// 
			this->label28->AutoSize = true;
			this->label28->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label28->Location = System::Drawing::Point(27, 220);
			this->label28->Name = L"label28";
			this->label28->Size = System::Drawing::Size(44, 25);
			this->label28->TabIndex = 10;
			this->label28->Text = L"hex";
			// 
			// label35
			// 
			this->label35->AutoSize = true;
			this->label35->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label35->Location = System::Drawing::Point(32, 456);
			this->label35->Name = L"label35";
			this->label35->Size = System::Drawing::Size(39, 25);
			this->label35->TabIndex = 12;
			this->label35->Text = L"chr";
			// 
			// label29
			// 
			this->label29->AutoSize = true;
			this->label29->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label29->Location = System::Drawing::Point(33, 120);
			this->label29->Name = L"label29";
			this->label29->Size = System::Drawing::Size(38, 25);
			this->label29->TabIndex = 11;
			this->label29->Text = L"bin";
			// 
			// label34
			// 
			this->label34->AutoSize = true;
			this->label34->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label34->Location = System::Drawing::Point(27, 356);
			this->label34->Name = L"label34";
			this->label34->Size = System::Drawing::Size(44, 25);
			this->label34->TabIndex = 13;
			this->label34->Text = L"hex";
			// 
			// label30
			// 
			this->label30->AutoSize = true;
			this->label30->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label30->Location = System::Drawing::Point(32, 184);
			this->label30->Name = L"label30";
			this->label30->Size = System::Drawing::Size(39, 25);
			this->label30->TabIndex = 12;
			this->label30->Text = L"chr";
			// 
			// textBox30
			// 
			this->textBox30->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox30->Location = System::Drawing::Point(77, 528);
			this->textBox30->Name = L"textBox30";
			this->textBox30->Size = System::Drawing::Size(1100, 30);
			this->textBox30->TabIndex = 3;
			this->textBox30->TextChanged += gcnew System::EventHandler(this, &main_form::textBox30_TextChanged);
			// 
			// label31
			// 
			this->label31->AutoSize = true;
			this->label31->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label31->Location = System::Drawing::Point(27, 84);
			this->label31->Name = L"label31";
			this->label31->Size = System::Drawing::Size(44, 25);
			this->label31->TabIndex = 13;
			this->label31->Text = L"hex";
			// 
			// label33
			// 
			this->label33->AutoSize = true;
			this->label33->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label33->Location = System::Drawing::Point(32, 320);
			this->label33->Name = L"label33";
			this->label33->Size = System::Drawing::Size(39, 25);
			this->label33->TabIndex = 14;
			this->label33->Text = L"chr";
			// 
			// textBox24
			// 
			this->textBox24->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox24->Location = System::Drawing::Point(77, 256);
			this->textBox24->Name = L"textBox24";
			this->textBox24->Size = System::Drawing::Size(1100, 30);
			this->textBox24->TabIndex = 3;
			this->textBox24->TextChanged += gcnew System::EventHandler(this, &main_form::textBox24_TextChanged);
			// 
			// textBox29
			// 
			this->textBox29->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox29->Location = System::Drawing::Point(77, 492);
			this->textBox29->Name = L"textBox29";
			this->textBox29->Size = System::Drawing::Size(1100, 30);
			this->textBox29->TabIndex = 4;
			this->textBox29->TextChanged += gcnew System::EventHandler(this, &main_form::textBox29_TextChanged);
			// 
			// label32
			// 
			this->label32->AutoSize = true;
			this->label32->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label32->Location = System::Drawing::Point(32, 48);
			this->label32->Name = L"label32";
			this->label32->Size = System::Drawing::Size(39, 25);
			this->label32->TabIndex = 14;
			this->label32->Text = L"chr";
			// 
			// textBox27
			// 
			this->textBox27->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox27->Location = System::Drawing::Point(77, 392);
			this->textBox27->Name = L"textBox27";
			this->textBox27->Size = System::Drawing::Size(1100, 30);
			this->textBox27->TabIndex = 5;
			this->textBox27->TextChanged += gcnew System::EventHandler(this, &main_form::textBox27_TextChanged);
			// 
			// textBox23
			// 
			this->textBox23->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox23->Location = System::Drawing::Point(77, 220);
			this->textBox23->Name = L"textBox23";
			this->textBox23->Size = System::Drawing::Size(1100, 30);
			this->textBox23->TabIndex = 4;
			this->textBox23->TextChanged += gcnew System::EventHandler(this, &main_form::textBox23_TextChanged);
			// 
			// textBox28
			// 
			this->textBox28->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox28->Location = System::Drawing::Point(77, 456);
			this->textBox28->Name = L"textBox28";
			this->textBox28->Size = System::Drawing::Size(1100, 30);
			this->textBox28->TabIndex = 6;
			this->textBox28->TextChanged += gcnew System::EventHandler(this, &main_form::textBox28_TextChanged);
			// 
			// textBox21
			// 
			this->textBox21->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox21->Location = System::Drawing::Point(77, 120);
			this->textBox21->Name = L"textBox21";
			this->textBox21->Size = System::Drawing::Size(1100, 30);
			this->textBox21->TabIndex = 5;
			this->textBox21->TextChanged += gcnew System::EventHandler(this, &main_form::textBox21_TextChanged);
			// 
			// textBox26
			// 
			this->textBox26->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox26->Location = System::Drawing::Point(77, 356);
			this->textBox26->Name = L"textBox26";
			this->textBox26->Size = System::Drawing::Size(1100, 30);
			this->textBox26->TabIndex = 7;
			this->textBox26->TextChanged += gcnew System::EventHandler(this, &main_form::textBox26_TextChanged);
			// 
			// textBox22
			// 
			this->textBox22->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox22->Location = System::Drawing::Point(77, 184);
			this->textBox22->Name = L"textBox22";
			this->textBox22->Size = System::Drawing::Size(1100, 30);
			this->textBox22->TabIndex = 6;
			this->textBox22->TextChanged += gcnew System::EventHandler(this, &main_form::textBox22_TextChanged);
			// 
			// textBox25
			// 
			this->textBox25->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox25->Location = System::Drawing::Point(77, 320);
			this->textBox25->Name = L"textBox25";
			this->textBox25->Size = System::Drawing::Size(1100, 30);
			this->textBox25->TabIndex = 8;
			this->textBox25->TextChanged += gcnew System::EventHandler(this, &main_form::textBox25_TextChanged);
			// 
			// textBox20
			// 
			this->textBox20->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox20->Location = System::Drawing::Point(77, 84);
			this->textBox20->Name = L"textBox20";
			this->textBox20->Size = System::Drawing::Size(1100, 30);
			this->textBox20->TabIndex = 7;
			this->textBox20->TextChanged += gcnew System::EventHandler(this, &main_form::textBox20_TextChanged);
			// 
			// textBox19
			// 
			this->textBox19->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->textBox19->Location = System::Drawing::Point(77, 48);
			this->textBox19->Name = L"textBox19";
			this->textBox19->Size = System::Drawing::Size(1100, 30);
			this->textBox19->TabIndex = 8;
			this->textBox19->TextChanged += gcnew System::EventHandler(this, &main_form::textBox19_TextChanged);
			// 
			// main_form
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(144, 144);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Dpi;
			this->ClientSize = System::Drawing::Size(1258, 664);
			this->Controls->Add(this->tabControl);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->Name = L"main_form";
			this->Text = L"Feistel cipher";
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->tabControl->ResumeLayout(false);
			this->tabPage3->ResumeLayout(false);
			this->tabPage3->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion

		private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e)
		{textBoxChrChanged(textBox1, textBox2, textBox3);}

		private: System::Void textBox2_TextChanged(System::Object^ sender, System::EventArgs^ e)
		{textBoxHexChanged(textBox1, textBox2, textBox3);}

		private: System::Void textBox3_TextChanged(System::Object^ sender, System::EventArgs^ e)
		{textBoxBinChanged(textBox1, textBox2, textBox3);}

		private: System::Void textBox4_TextChanged(System::Object^ sender, System::EventArgs^ e)
		{textBoxChrChanged(textBox4, textBox5, textBox6);}

		private: System::Void textBox5_TextChanged(System::Object^ sender, System::EventArgs^ e)
		{textBoxHexChanged(textBox4, textBox5, textBox6);}

		private: System::Void textBox6_TextChanged(System::Object^ sender, System::EventArgs^ e)
		{textBoxBinChanged(textBox4, textBox5, textBox6);}

		private: System::Void textBox10_TextChanged(System::Object^ sender, System::EventArgs^ e)
		{textBoxChrChanged(textBox10, textBox11, textBox12);}

		private: System::Void textBox11_TextChanged(System::Object^ sender, System::EventArgs^ e)
		{textBoxHexChanged(textBox10, textBox11, textBox12);}

		private: System::Void textBox12_TextChanged(System::Object^ sender, System::EventArgs^ e)
		{textBoxBinChanged(textBox10, textBox11, textBox12);}

		private: System::Void textBox13_TextChanged(System::Object^ sender, System::EventArgs^ e)
		{textBoxChrChanged(textBox13, textBox14, textBox15);}

		private: System::Void textBox14_TextChanged(System::Object^ sender, System::EventArgs^ e)
		{textBoxHexChanged(textBox13, textBox14, textBox15);}

		private: System::Void textBox15_TextChanged(System::Object^ sender, System::EventArgs^ e)
		{textBoxBinChanged(textBox13, textBox14, textBox15);}

		private: System::Void textBox19_TextChanged(System::Object^ sender, System::EventArgs^ e)
		{textBoxChrChanged(textBox19, textBox20, textBox21);}

		private: System::Void textBox20_TextChanged(System::Object^ sender, System::EventArgs^ e)
		{textBoxHexChanged(textBox19, textBox20, textBox21);}

		private: System::Void textBox21_TextChanged(System::Object^ sender, System::EventArgs^ e)
		{textBoxBinChanged(textBox19, textBox20, textBox21);}

		private: System::Void textBox22_TextChanged(System::Object^ sender, System::EventArgs^ e)
		{textBoxChrChanged(textBox22, textBox23, textBox24);}

		private: System::Void textBox23_TextChanged(System::Object^ sender, System::EventArgs^ e)
		{textBoxHexChanged(textBox22, textBox23, textBox24);}

		private: System::Void textBox24_TextChanged(System::Object^ sender, System::EventArgs^ e)
		{textBoxBinChanged(textBox22, textBox23, textBox24);}

		private: System::Void textBox25_TextChanged(System::Object^ sender, System::EventArgs^ e)
		{textBoxChrChanged(textBox25, textBox26, textBox27);}

		private: System::Void textBox26_TextChanged(System::Object^ sender, System::EventArgs^ e)
		{textBoxHexChanged(textBox25, textBox26, textBox27);}

		private: System::Void textBox27_TextChanged(System::Object^ sender, System::EventArgs^ e)
		{textBoxBinChanged(textBox25, textBox26, textBox27);}

		private: System::Void textBox28_TextChanged(System::Object^ sender, System::EventArgs^ e)
		{textBoxChrChanged(textBox28, textBox29, textBox30);}

		private: System::Void textBox29_TextChanged(System::Object^ sender, System::EventArgs^ e)
		{textBoxHexChanged(textBox28, textBox29, textBox30);}

		private: System::Void textBox30_TextChanged(System::Object^ sender, System::EventArgs^ e)
		{textBoxBinChanged(textBox28, textBox29, textBox30);}
		
		private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e);

		private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e);

		private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e);

		private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e);

		private: System::Void button5_Click(System::Object^ sender, System::EventArgs^ e);

		private: System::Void button6_Click(System::Object^ sender, System::EventArgs^ e);

		private: System::Void button7_Click(System::Object^ sender, System::EventArgs^ e);

		private: System::Void button8_Click(System::Object^ sender, System::EventArgs^ e);

		private: System::Void button9_Click(System::Object^ sender, System::EventArgs^ e);

		private: System::Void button10_Click(System::Object^ sender, System::EventArgs^ e);

		private: System::Void button11_Click(System::Object^ sender, System::EventArgs^ e);

		private: System::Void button12_Click(System::Object^ sender, System::EventArgs^ e);
	};
}
