#pragma once
#include <sstream>
#include <msclr\marshal_cppstd.h>
#include "XOR_cipher.cpp"
#include "LFSR.cpp"
#include "binary_statistics.h"

namespace scrambler {

	enum text_changed {
		False,
		True
	};

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Text;

	public ref class main : public System::Windows::Forms::Form
	{
	public:
		main(void)
		{
			InitializeComponent();

			text_chngd = new text_changed(text_changed::True);

			textBoxM1h->Text = file_to_HexString("input.txt");
			textBoxM1c->Text = HexString_to_String(textBoxM1h->Text);
			textBoxM1b->Text = HexString_to_BinString(textBoxM1h->Text);
			textBoxM3c->Text = HexString_to_String(textBoxM1h->Text);
			textBoxM3h->Text = textBoxM1h->Text;
			textBoxM3b->Text = HexString_to_BinString(textBoxM1h->Text);
			
			textBoxS3i->Text = HexString_to_String(file_to_HexString("seed.txt"));
			textBoxS4i->Text = textBoxS3i->Text;
			textBoxS5i->Text = textBoxS3i->Text;

			*text_chngd = text_changed::False;
		}

	protected:
		~main()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		// <Buttons handlers

		System::Void button1_Click(System::Object^ sender, System::EventArgs^ e)
		{
			try {
				HexString_to_file(textBoxM1h->Text, "input.txt");
			}
			catch (int) {
				MessageBox::Show("Invalid Message in hex", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			XOR_cipher::cipher1("input.txt", "ciphered.txt");

			textBoxK1h->Text = file_to_HexString("ciphered.txt.key.txt");
			textBoxK1c->Text = HexString_to_String(textBoxK1h->Text);
			textBoxK1b->Text = HexString_to_BinString(textBoxK1h->Text);

			textBoxK2c->Text = textBoxK1c->Text;
			textBoxK2h->Text = textBoxK1h->Text;
			textBoxK2b->Text = textBoxK1b->Text;

			textBoxE1h->Text = file_to_HexString("ciphered.txt");
			textBoxE1c->Text = HexString_to_String(textBoxE1h->Text);
			textBoxE1b->Text = HexString_to_BinString(textBoxE1h->Text);

			textBoxE2c->Text = textBoxE1c->Text;
			textBoxE2h->Text = textBoxE1h->Text;
			textBoxE2b->Text = textBoxE1b->Text;
		}

		System::Void button2_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (textBoxE2h->Text->Length != textBoxK2h->Text->Length) {
				MessageBox::Show("Encrypted text and Key are not same lenght", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			try {
				HexString_to_file(textBoxE2h->Text, "ciphered.txt");
			}
			catch (int) {
				MessageBox::Show("Invalid Encrypted in hex", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			try {
				HexString_to_file(textBoxK2h->Text, "ciphered.txt.key.txt");
			}
			catch (int) {
				MessageBox::Show("Invalid Key in hex", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			XOR_cipher::decipher1("ciphered.txt", "output.txt");

			textBoxD2h->Text = file_to_HexString("output.txt");
			textBoxD2c->Text = HexString_to_String(textBoxD2h->Text);
			textBoxD2b->Text = HexString_to_BinString(textBoxD2h->Text);
		}

		template<uint64_t first, uint64_t ...rest>
		System::Void button3_Click()
		{
			try {
				HexString_to_file(textBoxM3h->Text, "input.txt");
			}
			catch (int) {
				MessageBox::Show("Invalid Message in hex", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			try {
				Convert::ToUInt64(textBoxS3i->Text);
			}
			catch (Exception^) {
				MessageBox::Show("Invalid Seed", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			String_to_file(textBoxS3i->Text, "seed.txt");
			textBoxS4i->Text = textBoxS3i->Text;
			textBoxS5i->Text = textBoxS3i->Text;

			XOR_cipher::cipher2<first, rest...>("input.txt", "ciphered.txt", "seed.txt");

			textBoxE3h->Text = file_to_HexString("ciphered.txt");
			textBoxE3c->Text = HexString_to_String(textBoxE3h->Text);
			textBoxE3b->Text = HexString_to_BinString(textBoxE3h->Text);

			textBoxE4c->Text = textBoxE3c->Text;
			textBoxE4h->Text = textBoxE3h->Text;
			textBoxE4b->Text = textBoxE3b->Text;
		}
		
		template<uint64_t first, uint64_t ...rest>
		System::Void button4_Click()
		{
			try {
				HexString_to_file(textBoxE4h->Text, "ciphered.txt");
			}
			catch (int) {
				MessageBox::Show("Invalid Encrypted in hex", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			try {
				Convert::ToUInt64(textBoxS4i->Text);
			}
			catch (Exception^) {
				MessageBox::Show("Invalid Seed", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			String_to_file(textBoxS4i->Text, "seed.txt");
			textBoxS3i->Text = textBoxS4i->Text;
			textBoxS5i->Text = textBoxS4i->Text;

			XOR_cipher::cipher2<first, rest...>("ciphered.txt", "output.txt", "seed.txt");

			textBoxD4h->Text = file_to_HexString("output.txt");
			textBoxD4c->Text = HexString_to_String(textBoxD4h->Text);
			textBoxD4b->Text = HexString_to_BinString(textBoxD4h->Text);
		}

		template<uint64_t first, uint64_t ...rest>
		System::Void button5_Click()
		{
			uint64_t seed = 0;

			try {
				seed = Convert::ToUInt64(textBoxS5i->Text);
			}
			catch (Exception^) {
				MessageBox::Show("Invalid Seed", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			LFSR<first, rest...> scram(seed);
			uint64_t period = scram.period();
			std::vector<bool> sample;
			sample.resize(period);
			for (size_t i = 0; i < period; ++i)
				sample[i] = static_cast<bool>(scram.next_bit());

			textBoxR51->Text = Convert::ToString(period);
			textBoxR52->Text = Convert::ToString(chi_squared_statistic(sample));
			textBoxR53->Text = Convert::ToString(balance_statistic(sample));
			auto cyclicality = cyclicality_statistic(sample);
			textBoxR54->Text = "";
			for (const auto& it : cyclicality) {
				textBoxR54->Text += Convert::ToString(it.first);
				textBoxR54->Text += " - ";
				textBoxR54->Text += Convert::ToString(it.second);
				textBoxR54->Text += "    ";

			}
			textBoxR55->Text = Convert::ToString(correlation_statistic(sample));
		}

		System::Void button31_Click(System::Object^ sender, System::EventArgs^ e) { button3_Click<11, 2, 0>(); }

		System::Void button32_Click(System::Object^ sender, System::EventArgs^ e) { button3_Click<11, 5, 2, 0>(); }

		System::Void button41_Click(System::Object^ sender, System::EventArgs^ e) { button4_Click<11, 2, 0>(); }

		System::Void button42_Click(System::Object^ sender, System::EventArgs^ e) { button4_Click<11, 5, 2, 0>(); }

		System::Void button51_Click(System::Object^ sender, System::EventArgs^ e) { button5_Click<11, 2, 0>(); }

		System::Void button52_Click(System::Object^ sender, System::EventArgs^ e) { button5_Click<11, 5, 2, 0>(); }

		// Buttons handlers>



		// <Text handlers

		text_changed* text_chngd;

		System::Void textBoxM1c_TextChanged(System::Object^ sender, System::EventArgs^ e) 
		{
			if (*text_chngd != text_changed::False)
				return;

			*text_chngd = text_changed::True;

			textBoxM1h->Text = String_to_HexString(textBoxM1c->Text);
			textBoxM1b->Text = String_to_BinString(textBoxM1c->Text);

			*text_chngd = text_changed::False;
		}
		
		System::Void textBoxM1h_TextChanged(System::Object^ sender, System::EventArgs^ e) 
		{
			if (textBoxM1h->Text->Length % 2 != 0)
				return;

			if (*text_chngd != text_changed::False)
				return;

			*text_chngd = text_changed::True;

			textBoxM1c->Text = HexString_to_String(textBoxM1h->Text);
			textBoxM1b->Text = HexString_to_BinString(textBoxM1h->Text);

			*text_chngd = text_changed::False;
		}
		
		System::Void textBoxM1b_TextChanged(System::Object^ sender, System::EventArgs^ e) 
		{
			if (textBoxM1b->Text->Length % 8 != 0)
				return;

			if (*text_chngd != text_changed::False)
				return;

			*text_chngd = text_changed::True;

			textBoxM1c->Text = BinString_to_String(textBoxM1b->Text);
			textBoxM1h->Text = BinString_to_HexString(textBoxM1b->Text);

			*text_chngd = text_changed::False;
		}

		System::Void textBoxE2h_TextChanged(System::Object^ sender, System::EventArgs^ e)
		{
			if (textBoxE2h->Text->Length % 2 != 0)
				return;

			if (*text_chngd != text_changed::False)
				return;

			*text_chngd = text_changed::True;

			textBoxE2c->Text = HexString_to_String(textBoxE2h->Text);
			textBoxE2b->Text = HexString_to_BinString(textBoxE2h->Text);

			*text_chngd = text_changed::False;
		}
		
		System::Void textBoxE2b_TextChanged(System::Object^ sender, System::EventArgs^ e)
		{
			if (textBoxE2b->Text->Length % 8 != 0)
				return;

			if (*text_chngd != text_changed::False)
				return;

			*text_chngd = text_changed::True;

			textBoxE2c->Text = BinString_to_String(textBoxE2b->Text);
			textBoxE2h->Text = BinString_to_HexString(textBoxE2b->Text);

			*text_chngd = text_changed::False;
		}
		
		System::Void textBoxK2h_TextChanged(System::Object^ sender, System::EventArgs^ e)
		{
			if (textBoxK2h->Text->Length % 2 != 0)
				return;

			if (*text_chngd != text_changed::False)
				return;

			*text_chngd = text_changed::True;

			textBoxK2c->Text = HexString_to_String(textBoxK2h->Text);
			textBoxK2b->Text = HexString_to_BinString(textBoxK2h->Text);

			*text_chngd = text_changed::False;
		}
		
		System::Void textBoxK2b_TextChanged(System::Object^ sender, System::EventArgs^ e)
		{
			if (textBoxK2b->Text->Length % 8 != 0)
				return;

			if (*text_chngd != text_changed::False)
				return;

			*text_chngd = text_changed::True;

			textBoxK2c->Text = BinString_to_String(textBoxK2b->Text);
			textBoxK2h->Text = BinString_to_HexString(textBoxK2b->Text);

			*text_chngd = text_changed::False;
		}

		System::Void textBoxM3c_TextChanged(System::Object^ sender, System::EventArgs^ e)
		{
			if (*text_chngd != text_changed::False)
				return;

			*text_chngd = text_changed::True;

			textBoxM3h->Text = String_to_HexString(textBoxM3c->Text);
			textBoxM3b->Text = String_to_BinString(textBoxM3c->Text);

			*text_chngd = text_changed::False;
		}

		System::Void textBoxM3h_TextChanged(System::Object^ sender, System::EventArgs^ e)
		{
			if (textBoxM3h->Text->Length % 2 != 0)
				return;

			if (*text_chngd != text_changed::False)
				return;

			*text_chngd = text_changed::True;

			textBoxM3c->Text = HexString_to_String(textBoxM3h->Text);
			textBoxM3b->Text = HexString_to_BinString(textBoxM3h->Text);

			*text_chngd = text_changed::False;
		}

		System::Void textBoxM3b_TextChanged(System::Object^ sender, System::EventArgs^ e)
		{
			if (textBoxM3b->Text->Length % 8 != 0)
				return;

			if (*text_chngd != text_changed::False)
				return;

			*text_chngd = text_changed::True;

			textBoxM3c->Text = BinString_to_String(textBoxM3b->Text);
			textBoxM3h->Text = BinString_to_HexString(textBoxM3b->Text);

			*text_chngd = text_changed::False;
		}

		System::Void textBoxE4h_TextChanged(System::Object^ sender, System::EventArgs^ e)
		{
			if (textBoxE4h->Text->Length % 2 != 0)
				return;

			if (*text_chngd != text_changed::False)
				return;

			*text_chngd = text_changed::True;

			textBoxE4c->Text = HexString_to_String(textBoxE4h->Text);
			textBoxE4b->Text = HexString_to_BinString(textBoxE4h->Text);

			*text_chngd = text_changed::False;
		}

		System::Void textBoxE4b_TextChanged(System::Object^ sender, System::EventArgs^ e)
		{
			if (textBoxE4b->Text->Length % 8 != 0)
				return;

			if (*text_chngd != text_changed::False)
				return;

			*text_chngd = text_changed::True;

			textBoxE4c->Text = BinString_to_String(textBoxE4b->Text);
			textBoxE4h->Text = BinString_to_HexString(textBoxE4b->Text);

			*text_chngd = text_changed::False;
		}

		// Text handlers>



		// <String read

		static String^ file_to_String(const std::string& filename)
		{
			std::ifstream file(filename, std::ios::binary);

			String^ result("");

			std::stringstream buffer;
			buffer << file.rdbuf();
			file.close();

			std::string str = buffer.str();

			for (int i = 0; i < str.length(); ++i) {
				result += Convert::ToChar(static_cast<unsigned char>(str[i]));
			}

			return result;
		}

		static String^ file_to_HexString(const std::string& filename)
		{
			std::ifstream file(filename, std::ios::binary);

			String^ result("");

			std::stringstream buffer;
			buffer << file.rdbuf();
			file.close();

			std::string str = buffer.str();

			for (int i = 0; i < str.length(); ++i) {
				result += Convert::ToString(static_cast<unsigned char>(str[i]), 16)->ToUpper()->PadLeft(2, '0');
			}

			return result;
		}

		static String^ file_to_BinString(const std::string& filename)
		{
			std::ifstream file(filename, std::ios::binary);

			String^ result("");

			std::stringstream buffer;
			buffer << file.rdbuf();
			file.close();

			std::string str = buffer.str();

			for (int i = 0; i < str.length(); ++i) {
				result += Convert::ToString(static_cast<unsigned char>(str[i]), 2)->PadLeft(8, '0');
			}

			return result;
		}

		// String read>



		// <String write

		static void String_to_file(String^ str, const std::string& filename)
		{
			std::ofstream file(filename, std::ios::binary);

			std::string stdstr = msclr::interop::marshal_as<std::string>(str);

			file << stdstr;
			file.close();
		}

		static void HexString_to_file(String^ str, const std::string& filename)
		{
			if (str->Length % 2 != 0)
				throw 21;

			std::ofstream file(filename, std::ios::binary);

			std::string stdstr;
			for (int i = 0; i < str->Length; i += 2) {
				std::string substr = msclr::interop::marshal_as<std::string>(str->Substring(i, 2));
				stdstr += static_cast<unsigned char>(std::stoi(substr, NULL, 16));
			}

			file << stdstr;
			file.close();
		}

		// String write>



		// <String conversions

		static String^ String_to_HexString(String^ str)
		{
			return BitConverter::ToString(Encoding::Default->GetBytes(str))->Replace("-", "");
		}

		static String^ String_to_BinString(String^ str)
		{	
			return HexString_to_BinString(String_to_HexString(str));
		}

		static String^ HexString_to_String(String^ str)
		{
			String^ result("");

			for (int i = 0; i < str->Length; i += 2) {
				result += Convert::ToChar(Convert::ToByte(str->Substring(i, 2), 16));
			}

			return result;
		}

		static String^ HexString_to_BinString(String^ str)
		{	
			String^ result("");

			for (int i = 0; i < str->Length; i += 2) {
				std::string stdstr = msclr::interop::marshal_as<std::string>(str->Substring(i, 2));
				result += Convert::ToString(std::stoi(stdstr, NULL, 16), 2)->PadLeft(8, '0');
			}

			return result;
		}

		static String^ BinString_to_HexString(String^ str)
		{	
			String^ result("");

			for (int i = 0; i < str->Length; i += 8) {
				std::string stdstr = msclr::interop::marshal_as<std::string>(str->Substring(i, 8));
				result += Convert::ToString(std::stoi(stdstr, NULL, 2), 16)->ToUpper()->PadLeft(2, '0');
			}

			return result;
		}

		static String^ BinString_to_String(String^ str)
		{	
			return HexString_to_String(BinString_to_HexString(str));
		}

		// String conversions>



	private: System::Windows::Forms::TabControl^ tabControl;
	private: System::Windows::Forms::TabPage^ tabPage1;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ labelE1;
	private: System::Windows::Forms::Label^ labelK1;
	private: System::Windows::Forms::Label^ labelM1;
	private: System::Windows::Forms::Label^ labelb13;
	private: System::Windows::Forms::Label^ labelb12;
	private: System::Windows::Forms::Label^ labelb11;
	private: System::Windows::Forms::Label^ labelh13;
	private: System::Windows::Forms::Label^ labelh12;
	private: System::Windows::Forms::Label^ labelh11;
	private: System::Windows::Forms::Label^ labelc13;
	private: System::Windows::Forms::Label^ labelc12;
	private: System::Windows::Forms::Label^ labelc11;
	private: System::Windows::Forms::TextBox^ textBoxE1b;
	private: System::Windows::Forms::TextBox^ textBoxK1b;
	private: System::Windows::Forms::TextBox^ textBoxM1b;
	private: System::Windows::Forms::TextBox^ textBoxE1h;
	private: System::Windows::Forms::TextBox^ textBoxE1c;
	private: System::Windows::Forms::TextBox^ textBoxK1h;
	private: System::Windows::Forms::TextBox^ textBoxK1c;
	private: System::Windows::Forms::TextBox^ textBoxM1h;
	private: System::Windows::Forms::TextBox^ textBoxM1c;
	private: System::Windows::Forms::TabPage^ tabPage2;
	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::Label^ labelD2;
	private: System::Windows::Forms::Label^ labelK2;
	private: System::Windows::Forms::Label^ labelE2;
	private: System::Windows::Forms::Label^ labelb23;
	private: System::Windows::Forms::Label^ labelb22;
	private: System::Windows::Forms::Label^ labelb21;
	private: System::Windows::Forms::Label^ labelh23;
	private: System::Windows::Forms::Label^ labelh22;
	private: System::Windows::Forms::Label^ labelh21;
	private: System::Windows::Forms::Label^ labelc23;
	private: System::Windows::Forms::Label^ labelc22;
	private: System::Windows::Forms::Label^ labelc21;
	private: System::Windows::Forms::TextBox^ textBoxD2b;
	private: System::Windows::Forms::TextBox^ textBoxK2b;
	private: System::Windows::Forms::TextBox^ textBoxE2b;
	private: System::Windows::Forms::TextBox^ textBoxD2h;
	private: System::Windows::Forms::TextBox^ textBoxD2c;
	private: System::Windows::Forms::TextBox^ textBoxK2h;
	private: System::Windows::Forms::TextBox^ textBoxK2c;
	private: System::Windows::Forms::TextBox^ textBoxE2h;
	private: System::Windows::Forms::TextBox^ textBoxE2c;
	private: System::Windows::Forms::TabPage^ tabPage3;
	private: System::Windows::Forms::Button^ button32;
	private: System::Windows::Forms::Button^ button31;
	private: System::Windows::Forms::Label^ labelS3;
	private: System::Windows::Forms::Label^ labelE3;
	private: System::Windows::Forms::Label^ labelM3;
	private: System::Windows::Forms::Label^ labelb32;
	private: System::Windows::Forms::Label^ labelb31;
	private: System::Windows::Forms::Label^ labelh32;
	private: System::Windows::Forms::Label^ labelh31;
	private: System::Windows::Forms::Label^ labeli31;
	private: System::Windows::Forms::Label^ labelc32;
	private: System::Windows::Forms::Label^ labelc31;
	private: System::Windows::Forms::TextBox^ textBoxE3b;
	private: System::Windows::Forms::TextBox^ textBoxM3b;
	private: System::Windows::Forms::TextBox^ textBoxE3h;
	private: System::Windows::Forms::TextBox^ textBoxS3i;
	private: System::Windows::Forms::TextBox^ textBoxE3c;
	private: System::Windows::Forms::TextBox^ textBoxM3h;
	private: System::Windows::Forms::TextBox^ textBoxM3c;
	private: System::Windows::Forms::TabPage^ tabPage4;
	private: System::Windows::Forms::Button^ button42;
	private: System::Windows::Forms::Button^ button41;
	private: System::Windows::Forms::Label^ labelS4;
	private: System::Windows::Forms::Label^ labelD4;
	private: System::Windows::Forms::Label^ labelE4;
	private: System::Windows::Forms::Label^ labelb42;
	private: System::Windows::Forms::Label^ labelb41;
	private: System::Windows::Forms::Label^ labelh42;
	private: System::Windows::Forms::Label^ labelh41;
	private: System::Windows::Forms::Label^ labeli4;
	private: System::Windows::Forms::Label^ labelc42;
	private: System::Windows::Forms::Label^ labelc41;
	private: System::Windows::Forms::TextBox^ textBoxD4b;
	private: System::Windows::Forms::TextBox^ textBoxE4b;
	private: System::Windows::Forms::TextBox^ textBoxD4h;
	private: System::Windows::Forms::TextBox^ textBoxS4i;
	private: System::Windows::Forms::TextBox^ textBoxD4c;
	private: System::Windows::Forms::TextBox^ textBoxE4h;
	private: System::Windows::Forms::TextBox^ textBoxE4c;
	private: System::Windows::Forms::TabPage^ tabPage5;
	private: System::Windows::Forms::Button^ button52;
	private: System::Windows::Forms::Button^ button51;
	private: System::Windows::Forms::Label^ label55;
	private: System::Windows::Forms::Label^ label54;
	private: System::Windows::Forms::Label^ label53;
	private: System::Windows::Forms::Label^ label52;
	private: System::Windows::Forms::Label^ label51;
	private: System::Windows::Forms::Label^ labelS5;
	private: System::Windows::Forms::Label^ labeli5;
	private: System::Windows::Forms::TextBox^ textBoxR55;
	private: System::Windows::Forms::TextBox^ textBoxR54;
	private: System::Windows::Forms::TextBox^ textBoxR53;
	private: System::Windows::Forms::TextBox^ textBoxR52;
	private: System::Windows::Forms::TextBox^ textBoxR51;
	private: System::Windows::Forms::TextBox^ textBoxS5i;

	private: System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// “ребуемый метод дл€ поддержки конструктора Ч не измен€йте 
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->tabControl = (gcnew System::Windows::Forms::TabControl());
			this->tabPage1 = (gcnew System::Windows::Forms::TabPage());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->labelE1 = (gcnew System::Windows::Forms::Label());
			this->labelK1 = (gcnew System::Windows::Forms::Label());
			this->labelM1 = (gcnew System::Windows::Forms::Label());
			this->labelb13 = (gcnew System::Windows::Forms::Label());
			this->labelb12 = (gcnew System::Windows::Forms::Label());
			this->labelb11 = (gcnew System::Windows::Forms::Label());
			this->labelh13 = (gcnew System::Windows::Forms::Label());
			this->labelh12 = (gcnew System::Windows::Forms::Label());
			this->labelh11 = (gcnew System::Windows::Forms::Label());
			this->labelc13 = (gcnew System::Windows::Forms::Label());
			this->labelc12 = (gcnew System::Windows::Forms::Label());
			this->labelc11 = (gcnew System::Windows::Forms::Label());
			this->textBoxE1b = (gcnew System::Windows::Forms::TextBox());
			this->textBoxK1b = (gcnew System::Windows::Forms::TextBox());
			this->textBoxM1b = (gcnew System::Windows::Forms::TextBox());
			this->textBoxE1h = (gcnew System::Windows::Forms::TextBox());
			this->textBoxE1c = (gcnew System::Windows::Forms::TextBox());
			this->textBoxK1h = (gcnew System::Windows::Forms::TextBox());
			this->textBoxK1c = (gcnew System::Windows::Forms::TextBox());
			this->textBoxM1h = (gcnew System::Windows::Forms::TextBox());
			this->textBoxM1c = (gcnew System::Windows::Forms::TextBox());
			this->tabPage2 = (gcnew System::Windows::Forms::TabPage());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->labelD2 = (gcnew System::Windows::Forms::Label());
			this->labelK2 = (gcnew System::Windows::Forms::Label());
			this->labelE2 = (gcnew System::Windows::Forms::Label());
			this->labelb23 = (gcnew System::Windows::Forms::Label());
			this->labelb22 = (gcnew System::Windows::Forms::Label());
			this->labelb21 = (gcnew System::Windows::Forms::Label());
			this->labelh23 = (gcnew System::Windows::Forms::Label());
			this->labelh22 = (gcnew System::Windows::Forms::Label());
			this->labelh21 = (gcnew System::Windows::Forms::Label());
			this->labelc23 = (gcnew System::Windows::Forms::Label());
			this->labelc22 = (gcnew System::Windows::Forms::Label());
			this->labelc21 = (gcnew System::Windows::Forms::Label());
			this->textBoxD2b = (gcnew System::Windows::Forms::TextBox());
			this->textBoxK2b = (gcnew System::Windows::Forms::TextBox());
			this->textBoxE2b = (gcnew System::Windows::Forms::TextBox());
			this->textBoxD2h = (gcnew System::Windows::Forms::TextBox());
			this->textBoxD2c = (gcnew System::Windows::Forms::TextBox());
			this->textBoxK2h = (gcnew System::Windows::Forms::TextBox());
			this->textBoxK2c = (gcnew System::Windows::Forms::TextBox());
			this->textBoxE2h = (gcnew System::Windows::Forms::TextBox());
			this->textBoxE2c = (gcnew System::Windows::Forms::TextBox());
			this->tabPage3 = (gcnew System::Windows::Forms::TabPage());
			this->button32 = (gcnew System::Windows::Forms::Button());
			this->button31 = (gcnew System::Windows::Forms::Button());
			this->labelS3 = (gcnew System::Windows::Forms::Label());
			this->labelE3 = (gcnew System::Windows::Forms::Label());
			this->labelM3 = (gcnew System::Windows::Forms::Label());
			this->labelb32 = (gcnew System::Windows::Forms::Label());
			this->labelb31 = (gcnew System::Windows::Forms::Label());
			this->labelh32 = (gcnew System::Windows::Forms::Label());
			this->labelh31 = (gcnew System::Windows::Forms::Label());
			this->labeli31 = (gcnew System::Windows::Forms::Label());
			this->labelc32 = (gcnew System::Windows::Forms::Label());
			this->labelc31 = (gcnew System::Windows::Forms::Label());
			this->textBoxE3b = (gcnew System::Windows::Forms::TextBox());
			this->textBoxM3b = (gcnew System::Windows::Forms::TextBox());
			this->textBoxE3h = (gcnew System::Windows::Forms::TextBox());
			this->textBoxS3i = (gcnew System::Windows::Forms::TextBox());
			this->textBoxE3c = (gcnew System::Windows::Forms::TextBox());
			this->textBoxM3h = (gcnew System::Windows::Forms::TextBox());
			this->textBoxM3c = (gcnew System::Windows::Forms::TextBox());
			this->tabPage4 = (gcnew System::Windows::Forms::TabPage());
			this->button42 = (gcnew System::Windows::Forms::Button());
			this->button41 = (gcnew System::Windows::Forms::Button());
			this->labelS4 = (gcnew System::Windows::Forms::Label());
			this->labelD4 = (gcnew System::Windows::Forms::Label());
			this->labelE4 = (gcnew System::Windows::Forms::Label());
			this->labelb42 = (gcnew System::Windows::Forms::Label());
			this->labelb41 = (gcnew System::Windows::Forms::Label());
			this->labelh42 = (gcnew System::Windows::Forms::Label());
			this->labelh41 = (gcnew System::Windows::Forms::Label());
			this->labeli4 = (gcnew System::Windows::Forms::Label());
			this->labelc42 = (gcnew System::Windows::Forms::Label());
			this->labelc41 = (gcnew System::Windows::Forms::Label());
			this->textBoxD4b = (gcnew System::Windows::Forms::TextBox());
			this->textBoxE4b = (gcnew System::Windows::Forms::TextBox());
			this->textBoxD4h = (gcnew System::Windows::Forms::TextBox());
			this->textBoxS4i = (gcnew System::Windows::Forms::TextBox());
			this->textBoxD4c = (gcnew System::Windows::Forms::TextBox());
			this->textBoxE4h = (gcnew System::Windows::Forms::TextBox());
			this->textBoxE4c = (gcnew System::Windows::Forms::TextBox());
			this->tabPage5 = (gcnew System::Windows::Forms::TabPage());
			this->button52 = (gcnew System::Windows::Forms::Button());
			this->button51 = (gcnew System::Windows::Forms::Button());
			this->label55 = (gcnew System::Windows::Forms::Label());
			this->label54 = (gcnew System::Windows::Forms::Label());
			this->label53 = (gcnew System::Windows::Forms::Label());
			this->textBoxR55 = (gcnew System::Windows::Forms::TextBox());
			this->label52 = (gcnew System::Windows::Forms::Label());
			this->textBoxR54 = (gcnew System::Windows::Forms::TextBox());
			this->label51 = (gcnew System::Windows::Forms::Label());
			this->textBoxR53 = (gcnew System::Windows::Forms::TextBox());
			this->labelS5 = (gcnew System::Windows::Forms::Label());
			this->textBoxR52 = (gcnew System::Windows::Forms::TextBox());
			this->labeli5 = (gcnew System::Windows::Forms::Label());
			this->textBoxR51 = (gcnew System::Windows::Forms::TextBox());
			this->textBoxS5i = (gcnew System::Windows::Forms::TextBox());
			this->tabControl->SuspendLayout();
			this->tabPage1->SuspendLayout();
			this->tabPage2->SuspendLayout();
			this->tabPage3->SuspendLayout();
			this->tabPage4->SuspendLayout();
			this->tabPage5->SuspendLayout();
			this->SuspendLayout();
			// 
			// tabControl
			// 
			this->tabControl->Controls->Add(this->tabPage1);
			this->tabControl->Controls->Add(this->tabPage2);
			this->tabControl->Controls->Add(this->tabPage3);
			this->tabControl->Controls->Add(this->tabPage4);
			this->tabControl->Controls->Add(this->tabPage5);
			this->tabControl->Location = System::Drawing::Point(0, 0);
			this->tabControl->Margin = System::Windows::Forms::Padding(0);
			this->tabControl->Name = L"tabControl";
			this->tabControl->SelectedIndex = 0;
			this->tabControl->Size = System::Drawing::Size(1180, 745);
			this->tabControl->TabIndex = 0;
			// 
			// tabPage1
			// 
			this->tabPage1->Controls->Add(this->button1);
			this->tabPage1->Controls->Add(this->labelE1);
			this->tabPage1->Controls->Add(this->labelK1);
			this->tabPage1->Controls->Add(this->labelM1);
			this->tabPage1->Controls->Add(this->labelb13);
			this->tabPage1->Controls->Add(this->labelb12);
			this->tabPage1->Controls->Add(this->labelb11);
			this->tabPage1->Controls->Add(this->labelh13);
			this->tabPage1->Controls->Add(this->labelh12);
			this->tabPage1->Controls->Add(this->labelh11);
			this->tabPage1->Controls->Add(this->labelc13);
			this->tabPage1->Controls->Add(this->labelc12);
			this->tabPage1->Controls->Add(this->labelc11);
			this->tabPage1->Controls->Add(this->textBoxE1b);
			this->tabPage1->Controls->Add(this->textBoxK1b);
			this->tabPage1->Controls->Add(this->textBoxM1b);
			this->tabPage1->Controls->Add(this->textBoxE1h);
			this->tabPage1->Controls->Add(this->textBoxE1c);
			this->tabPage1->Controls->Add(this->textBoxK1h);
			this->tabPage1->Controls->Add(this->textBoxK1c);
			this->tabPage1->Controls->Add(this->textBoxM1h);
			this->tabPage1->Controls->Add(this->textBoxM1c);
			this->tabPage1->Location = System::Drawing::Point(4, 34);
			this->tabPage1->Name = L"tabPage1";
			this->tabPage1->Padding = System::Windows::Forms::Padding(3);
			this->tabPage1->Size = System::Drawing::Size(1172, 707);
			this->tabPage1->TabIndex = 0;
			this->tabPage1->Text = L"GammaE";
			this->tabPage1->UseVisualStyleBackColor = true;
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(404, 537);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(303, 79);
			this->button1->TabIndex = 3;
			this->button1->Text = L"Encrypt";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &main::button1_Click);
			// 
			// labelE1
			// 
			this->labelE1->AutoSize = true;
			this->labelE1->Location = System::Drawing::Point(41, 350);
			this->labelE1->Name = L"labelE1";
			this->labelE1->Size = System::Drawing::Size(100, 25);
			this->labelE1->TabIndex = 2;
			this->labelE1->Text = L"Encrypted";
			// 
			// labelK1
			// 
			this->labelK1->AutoSize = true;
			this->labelK1->Location = System::Drawing::Point(41, 173);
			this->labelK1->Name = L"labelK1";
			this->labelK1->Size = System::Drawing::Size(47, 25);
			this->labelK1->TabIndex = 2;
			this->labelK1->Text = L"Key";
			// 
			// labelM1
			// 
			this->labelM1->AutoSize = true;
			this->labelM1->Location = System::Drawing::Point(41, 0);
			this->labelM1->Name = L"labelM1";
			this->labelM1->Size = System::Drawing::Size(93, 25);
			this->labelM1->TabIndex = 2;
			this->labelM1->Text = L"Message";
			// 
			// labelb13
			// 
			this->labelb13->AutoSize = true;
			this->labelb13->Location = System::Drawing::Point(7, 450);
			this->labelb13->Name = L"labelb13";
			this->labelb13->Size = System::Drawing::Size(38, 25);
			this->labelb13->TabIndex = 1;
			this->labelb13->Text = L"bin";
			// 
			// labelb12
			// 
			this->labelb12->AutoSize = true;
			this->labelb12->Location = System::Drawing::Point(7, 273);
			this->labelb12->Name = L"labelb12";
			this->labelb12->Size = System::Drawing::Size(38, 25);
			this->labelb12->TabIndex = 1;
			this->labelb12->Text = L"bin";
			// 
			// labelb11
			// 
			this->labelb11->AutoSize = true;
			this->labelb11->Location = System::Drawing::Point(7, 100);
			this->labelb11->Name = L"labelb11";
			this->labelb11->Size = System::Drawing::Size(38, 25);
			this->labelb11->TabIndex = 1;
			this->labelb11->Text = L"bin";
			// 
			// labelh13
			// 
			this->labelh13->AutoSize = true;
			this->labelh13->Location = System::Drawing::Point(1, 414);
			this->labelh13->Name = L"labelh13";
			this->labelh13->Size = System::Drawing::Size(44, 25);
			this->labelh13->TabIndex = 1;
			this->labelh13->Text = L"hex";
			// 
			// labelh12
			// 
			this->labelh12->AutoSize = true;
			this->labelh12->Location = System::Drawing::Point(1, 237);
			this->labelh12->Name = L"labelh12";
			this->labelh12->Size = System::Drawing::Size(44, 25);
			this->labelh12->TabIndex = 1;
			this->labelh12->Text = L"hex";
			// 
			// labelh11
			// 
			this->labelh11->AutoSize = true;
			this->labelh11->Location = System::Drawing::Point(1, 64);
			this->labelh11->Name = L"labelh11";
			this->labelh11->Size = System::Drawing::Size(44, 25);
			this->labelh11->TabIndex = 1;
			this->labelh11->Text = L"hex";
			// 
			// labelc13
			// 
			this->labelc13->AutoSize = true;
			this->labelc13->Location = System::Drawing::Point(6, 378);
			this->labelc13->Name = L"labelc13";
			this->labelc13->Size = System::Drawing::Size(39, 25);
			this->labelc13->TabIndex = 1;
			this->labelc13->Text = L"chr";
			// 
			// labelc12
			// 
			this->labelc12->AutoSize = true;
			this->labelc12->Location = System::Drawing::Point(6, 201);
			this->labelc12->Name = L"labelc12";
			this->labelc12->Size = System::Drawing::Size(39, 25);
			this->labelc12->TabIndex = 1;
			this->labelc12->Text = L"chr";
			// 
			// labelc11
			// 
			this->labelc11->AutoSize = true;
			this->labelc11->Location = System::Drawing::Point(6, 28);
			this->labelc11->Name = L"labelc11";
			this->labelc11->Size = System::Drawing::Size(39, 25);
			this->labelc11->TabIndex = 1;
			this->labelc11->Text = L"chr";
			// 
			// textBoxE1b
			// 
			this->textBoxE1b->Location = System::Drawing::Point(46, 450);
			this->textBoxE1b->Name = L"textBoxE1b";
			this->textBoxE1b->ReadOnly = true;
			this->textBoxE1b->Size = System::Drawing::Size(1099, 30);
			this->textBoxE1b->TabIndex = 0;
			// 
			// textBoxK1b
			// 
			this->textBoxK1b->Location = System::Drawing::Point(46, 273);
			this->textBoxK1b->Name = L"textBoxK1b";
			this->textBoxK1b->ReadOnly = true;
			this->textBoxK1b->Size = System::Drawing::Size(1099, 30);
			this->textBoxK1b->TabIndex = 0;
			// 
			// textBoxM1b
			// 
			this->textBoxM1b->Location = System::Drawing::Point(46, 100);
			this->textBoxM1b->Name = L"textBoxM1b";
			this->textBoxM1b->Size = System::Drawing::Size(1099, 30);
			this->textBoxM1b->TabIndex = 0;
			this->textBoxM1b->TextChanged += gcnew System::EventHandler(this, &main::textBoxM1b_TextChanged);
			// 
			// textBoxE1h
			// 
			this->textBoxE1h->Location = System::Drawing::Point(46, 414);
			this->textBoxE1h->Name = L"textBoxE1h";
			this->textBoxE1h->ReadOnly = true;
			this->textBoxE1h->Size = System::Drawing::Size(1099, 30);
			this->textBoxE1h->TabIndex = 0;
			// 
			// textBoxE1c
			// 
			this->textBoxE1c->Location = System::Drawing::Point(46, 378);
			this->textBoxE1c->Name = L"textBoxE1c";
			this->textBoxE1c->ReadOnly = true;
			this->textBoxE1c->Size = System::Drawing::Size(1099, 30);
			this->textBoxE1c->TabIndex = 0;
			// 
			// textBoxK1h
			// 
			this->textBoxK1h->Location = System::Drawing::Point(46, 237);
			this->textBoxK1h->Name = L"textBoxK1h";
			this->textBoxK1h->ReadOnly = true;
			this->textBoxK1h->Size = System::Drawing::Size(1099, 30);
			this->textBoxK1h->TabIndex = 0;
			// 
			// textBoxK1c
			// 
			this->textBoxK1c->Location = System::Drawing::Point(46, 201);
			this->textBoxK1c->Name = L"textBoxK1c";
			this->textBoxK1c->ReadOnly = true;
			this->textBoxK1c->Size = System::Drawing::Size(1099, 30);
			this->textBoxK1c->TabIndex = 0;
			// 
			// textBoxM1h
			// 
			this->textBoxM1h->Location = System::Drawing::Point(46, 64);
			this->textBoxM1h->Name = L"textBoxM1h";
			this->textBoxM1h->Size = System::Drawing::Size(1099, 30);
			this->textBoxM1h->TabIndex = 0;
			this->textBoxM1h->TextChanged += gcnew System::EventHandler(this, &main::textBoxM1h_TextChanged);
			// 
			// textBoxM1c
			// 
			this->textBoxM1c->Location = System::Drawing::Point(46, 28);
			this->textBoxM1c->Name = L"textBoxM1c";
			this->textBoxM1c->Size = System::Drawing::Size(1099, 30);
			this->textBoxM1c->TabIndex = 0;
			this->textBoxM1c->TextChanged += gcnew System::EventHandler(this, &main::textBoxM1c_TextChanged);
			// 
			// tabPage2
			// 
			this->tabPage2->Controls->Add(this->button2);
			this->tabPage2->Controls->Add(this->labelD2);
			this->tabPage2->Controls->Add(this->labelK2);
			this->tabPage2->Controls->Add(this->labelE2);
			this->tabPage2->Controls->Add(this->labelb23);
			this->tabPage2->Controls->Add(this->labelb22);
			this->tabPage2->Controls->Add(this->labelb21);
			this->tabPage2->Controls->Add(this->labelh23);
			this->tabPage2->Controls->Add(this->labelh22);
			this->tabPage2->Controls->Add(this->labelh21);
			this->tabPage2->Controls->Add(this->labelc23);
			this->tabPage2->Controls->Add(this->labelc22);
			this->tabPage2->Controls->Add(this->labelc21);
			this->tabPage2->Controls->Add(this->textBoxD2b);
			this->tabPage2->Controls->Add(this->textBoxK2b);
			this->tabPage2->Controls->Add(this->textBoxE2b);
			this->tabPage2->Controls->Add(this->textBoxD2h);
			this->tabPage2->Controls->Add(this->textBoxD2c);
			this->tabPage2->Controls->Add(this->textBoxK2h);
			this->tabPage2->Controls->Add(this->textBoxK2c);
			this->tabPage2->Controls->Add(this->textBoxE2h);
			this->tabPage2->Controls->Add(this->textBoxE2c);
			this->tabPage2->Location = System::Drawing::Point(4, 34);
			this->tabPage2->Margin = System::Windows::Forms::Padding(0);
			this->tabPage2->Name = L"tabPage2";
			this->tabPage2->Size = System::Drawing::Size(1172, 707);
			this->tabPage2->TabIndex = 1;
			this->tabPage2->Text = L"GammaD";
			this->tabPage2->UseVisualStyleBackColor = true;
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(404, 537);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(303, 79);
			this->button2->TabIndex = 25;
			this->button2->Text = L"Decrypt";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &main::button2_Click);
			// 
			// labelD2
			// 
			this->labelD2->AutoSize = true;
			this->labelD2->Location = System::Drawing::Point(41, 350);
			this->labelD2->Name = L"labelD2";
			this->labelD2->Size = System::Drawing::Size(101, 25);
			this->labelD2->TabIndex = 24;
			this->labelD2->Text = L"Decrypted";
			// 
			// labelK2
			// 
			this->labelK2->AutoSize = true;
			this->labelK2->Location = System::Drawing::Point(41, 173);
			this->labelK2->Name = L"labelK2";
			this->labelK2->Size = System::Drawing::Size(47, 25);
			this->labelK2->TabIndex = 23;
			this->labelK2->Text = L"Key";
			// 
			// labelE2
			// 
			this->labelE2->AutoSize = true;
			this->labelE2->Location = System::Drawing::Point(41, 0);
			this->labelE2->Name = L"labelE2";
			this->labelE2->Size = System::Drawing::Size(100, 25);
			this->labelE2->TabIndex = 22;
			this->labelE2->Text = L"Encrypted";
			// 
			// labelb23
			// 
			this->labelb23->AutoSize = true;
			this->labelb23->Location = System::Drawing::Point(7, 450);
			this->labelb23->Name = L"labelb23";
			this->labelb23->Size = System::Drawing::Size(38, 25);
			this->labelb23->TabIndex = 20;
			this->labelb23->Text = L"bin";
			// 
			// labelb22
			// 
			this->labelb22->AutoSize = true;
			this->labelb22->Location = System::Drawing::Point(7, 273);
			this->labelb22->Name = L"labelb22";
			this->labelb22->Size = System::Drawing::Size(38, 25);
			this->labelb22->TabIndex = 19;
			this->labelb22->Text = L"bin";
			// 
			// labelb21
			// 
			this->labelb21->AutoSize = true;
			this->labelb21->Location = System::Drawing::Point(7, 100);
			this->labelb21->Name = L"labelb21";
			this->labelb21->Size = System::Drawing::Size(38, 25);
			this->labelb21->TabIndex = 18;
			this->labelb21->Text = L"bin";
			// 
			// labelh23
			// 
			this->labelh23->AutoSize = true;
			this->labelh23->Location = System::Drawing::Point(1, 414);
			this->labelh23->Name = L"labelh23";
			this->labelh23->Size = System::Drawing::Size(44, 25);
			this->labelh23->TabIndex = 17;
			this->labelh23->Text = L"hex";
			// 
			// labelh22
			// 
			this->labelh22->AutoSize = true;
			this->labelh22->Location = System::Drawing::Point(1, 237);
			this->labelh22->Name = L"labelh22";
			this->labelh22->Size = System::Drawing::Size(44, 25);
			this->labelh22->TabIndex = 16;
			this->labelh22->Text = L"hex";
			// 
			// labelh21
			// 
			this->labelh21->AutoSize = true;
			this->labelh21->Location = System::Drawing::Point(1, 64);
			this->labelh21->Name = L"labelh21";
			this->labelh21->Size = System::Drawing::Size(44, 25);
			this->labelh21->TabIndex = 21;
			this->labelh21->Text = L"hex";
			// 
			// labelc23
			// 
			this->labelc23->AutoSize = true;
			this->labelc23->Location = System::Drawing::Point(6, 378);
			this->labelc23->Name = L"labelc23";
			this->labelc23->Size = System::Drawing::Size(39, 25);
			this->labelc23->TabIndex = 15;
			this->labelc23->Text = L"chr";
			// 
			// labelc22
			// 
			this->labelc22->AutoSize = true;
			this->labelc22->Location = System::Drawing::Point(6, 201);
			this->labelc22->Name = L"labelc22";
			this->labelc22->Size = System::Drawing::Size(39, 25);
			this->labelc22->TabIndex = 14;
			this->labelc22->Text = L"chr";
			// 
			// labelc21
			// 
			this->labelc21->AutoSize = true;
			this->labelc21->Location = System::Drawing::Point(6, 28);
			this->labelc21->Name = L"labelc21";
			this->labelc21->Size = System::Drawing::Size(39, 25);
			this->labelc21->TabIndex = 13;
			this->labelc21->Text = L"chr";
			// 
			// textBoxD2b
			// 
			this->textBoxD2b->Location = System::Drawing::Point(46, 450);
			this->textBoxD2b->Name = L"textBoxD2b";
			this->textBoxD2b->ReadOnly = true;
			this->textBoxD2b->Size = System::Drawing::Size(1099, 30);
			this->textBoxD2b->TabIndex = 11;
			// 
			// textBoxK2b
			// 
			this->textBoxK2b->Location = System::Drawing::Point(46, 273);
			this->textBoxK2b->Name = L"textBoxK2b";
			this->textBoxK2b->Size = System::Drawing::Size(1099, 30);
			this->textBoxK2b->TabIndex = 10;
			this->textBoxK2b->TextChanged += gcnew System::EventHandler(this, &main::textBoxK2b_TextChanged);
			// 
			// textBoxE2b
			// 
			this->textBoxE2b->Location = System::Drawing::Point(46, 100);
			this->textBoxE2b->Name = L"textBoxE2b";
			this->textBoxE2b->Size = System::Drawing::Size(1099, 30);
			this->textBoxE2b->TabIndex = 9;
			this->textBoxE2b->TextChanged += gcnew System::EventHandler(this, &main::textBoxE2b_TextChanged);
			// 
			// textBoxD2h
			// 
			this->textBoxD2h->Location = System::Drawing::Point(46, 414);
			this->textBoxD2h->Name = L"textBoxD2h";
			this->textBoxD2h->ReadOnly = true;
			this->textBoxD2h->Size = System::Drawing::Size(1099, 30);
			this->textBoxD2h->TabIndex = 8;
			// 
			// textBoxD2c
			// 
			this->textBoxD2c->Location = System::Drawing::Point(46, 378);
			this->textBoxD2c->Name = L"textBoxD2c";
			this->textBoxD2c->ReadOnly = true;
			this->textBoxD2c->Size = System::Drawing::Size(1099, 30);
			this->textBoxD2c->TabIndex = 7;
			// 
			// textBoxK2h
			// 
			this->textBoxK2h->Location = System::Drawing::Point(46, 237);
			this->textBoxK2h->Name = L"textBoxK2h";
			this->textBoxK2h->Size = System::Drawing::Size(1099, 30);
			this->textBoxK2h->TabIndex = 6;
			this->textBoxK2h->TextChanged += gcnew System::EventHandler(this, &main::textBoxK2h_TextChanged);
			// 
			// textBoxK2c
			// 
			this->textBoxK2c->Location = System::Drawing::Point(46, 201);
			this->textBoxK2c->Name = L"textBoxK2c";
			this->textBoxK2c->ReadOnly = true;
			this->textBoxK2c->Size = System::Drawing::Size(1099, 30);
			this->textBoxK2c->TabIndex = 5;
			// 
			// textBoxE2h
			// 
			this->textBoxE2h->Location = System::Drawing::Point(46, 64);
			this->textBoxE2h->Name = L"textBoxE2h";
			this->textBoxE2h->Size = System::Drawing::Size(1099, 30);
			this->textBoxE2h->TabIndex = 12;
			this->textBoxE2h->TextChanged += gcnew System::EventHandler(this, &main::textBoxE2h_TextChanged);
			// 
			// textBoxE2c
			// 
			this->textBoxE2c->Location = System::Drawing::Point(46, 28);
			this->textBoxE2c->Name = L"textBoxE2c";
			this->textBoxE2c->ReadOnly = true;
			this->textBoxE2c->Size = System::Drawing::Size(1099, 30);
			this->textBoxE2c->TabIndex = 4;
			// 
			// tabPage3
			// 
			this->tabPage3->Controls->Add(this->button32);
			this->tabPage3->Controls->Add(this->button31);
			this->tabPage3->Controls->Add(this->labelS3);
			this->tabPage3->Controls->Add(this->labelE3);
			this->tabPage3->Controls->Add(this->labelM3);
			this->tabPage3->Controls->Add(this->labelb32);
			this->tabPage3->Controls->Add(this->labelb31);
			this->tabPage3->Controls->Add(this->labelh32);
			this->tabPage3->Controls->Add(this->labelh31);
			this->tabPage3->Controls->Add(this->labeli31);
			this->tabPage3->Controls->Add(this->labelc32);
			this->tabPage3->Controls->Add(this->labelc31);
			this->tabPage3->Controls->Add(this->textBoxE3b);
			this->tabPage3->Controls->Add(this->textBoxM3b);
			this->tabPage3->Controls->Add(this->textBoxE3h);
			this->tabPage3->Controls->Add(this->textBoxS3i);
			this->tabPage3->Controls->Add(this->textBoxE3c);
			this->tabPage3->Controls->Add(this->textBoxM3h);
			this->tabPage3->Controls->Add(this->textBoxM3c);
			this->tabPage3->Location = System::Drawing::Point(4, 34);
			this->tabPage3->Name = L"tabPage3";
			this->tabPage3->Padding = System::Windows::Forms::Padding(3);
			this->tabPage3->Size = System::Drawing::Size(1172, 707);
			this->tabPage3->TabIndex = 2;
			this->tabPage3->Text = L"ScramblerE";
			this->tabPage3->UseVisualStyleBackColor = true;
			// 
			// button32
			// 
			this->button32->Location = System::Drawing::Point(713, 537);
			this->button32->Name = L"button32";
			this->button32->Size = System::Drawing::Size(303, 79);
			this->button32->TabIndex = 25;
			this->button32->Text = L"Encrypt   x11+x5+x2+1";
			this->button32->UseVisualStyleBackColor = true;
			this->button32->Click += gcnew System::EventHandler(this, &main::button32_Click);
			// 
			// button31
			// 
			this->button31->Location = System::Drawing::Point(95, 537);
			this->button31->Name = L"button31";
			this->button31->Size = System::Drawing::Size(303, 79);
			this->button31->TabIndex = 25;
			this->button31->Text = L"Encrypt   x11+x2+1";
			this->button31->UseVisualStyleBackColor = true;
			this->button31->Click += gcnew System::EventHandler(this, &main::button31_Click);
			// 
			// labelS3
			// 
			this->labelS3->AutoSize = true;
			this->labelS3->Location = System::Drawing::Point(41, 178);
			this->labelS3->Name = L"labelS3";
			this->labelS3->Size = System::Drawing::Size(59, 25);
			this->labelS3->TabIndex = 23;
			this->labelS3->Text = L"Seed";
			// 
			// labelE3
			// 
			this->labelE3->AutoSize = true;
			this->labelE3->Location = System::Drawing::Point(41, 303);
			this->labelE3->Name = L"labelE3";
			this->labelE3->Size = System::Drawing::Size(100, 25);
			this->labelE3->TabIndex = 23;
			this->labelE3->Text = L"Encrypted";
			// 
			// labelM3
			// 
			this->labelM3->AutoSize = true;
			this->labelM3->Location = System::Drawing::Point(41, 0);
			this->labelM3->Name = L"labelM3";
			this->labelM3->Size = System::Drawing::Size(93, 25);
			this->labelM3->TabIndex = 22;
			this->labelM3->Text = L"Message";
			// 
			// labelb32
			// 
			this->labelb32->AutoSize = true;
			this->labelb32->Location = System::Drawing::Point(7, 403);
			this->labelb32->Name = L"labelb32";
			this->labelb32->Size = System::Drawing::Size(38, 25);
			this->labelb32->TabIndex = 19;
			this->labelb32->Text = L"bin";
			// 
			// labelb31
			// 
			this->labelb31->AutoSize = true;
			this->labelb31->Location = System::Drawing::Point(7, 100);
			this->labelb31->Name = L"labelb31";
			this->labelb31->Size = System::Drawing::Size(38, 25);
			this->labelb31->TabIndex = 18;
			this->labelb31->Text = L"bin";
			// 
			// labelh32
			// 
			this->labelh32->AutoSize = true;
			this->labelh32->Location = System::Drawing::Point(1, 367);
			this->labelh32->Name = L"labelh32";
			this->labelh32->Size = System::Drawing::Size(44, 25);
			this->labelh32->TabIndex = 16;
			this->labelh32->Text = L"hex";
			// 
			// labelh31
			// 
			this->labelh31->AutoSize = true;
			this->labelh31->Location = System::Drawing::Point(1, 64);
			this->labelh31->Name = L"labelh31";
			this->labelh31->Size = System::Drawing::Size(44, 25);
			this->labelh31->TabIndex = 21;
			this->labelh31->Text = L"hex";
			// 
			// labeli31
			// 
			this->labeli31->AutoSize = true;
			this->labeli31->Location = System::Drawing::Point(13, 206);
			this->labeli31->Name = L"labeli31";
			this->labeli31->Size = System::Drawing::Size(32, 25);
			this->labeli31->TabIndex = 14;
			this->labeli31->Text = L"int";
			// 
			// labelc32
			// 
			this->labelc32->AutoSize = true;
			this->labelc32->Location = System::Drawing::Point(6, 331);
			this->labelc32->Name = L"labelc32";
			this->labelc32->Size = System::Drawing::Size(39, 25);
			this->labelc32->TabIndex = 14;
			this->labelc32->Text = L"chr";
			// 
			// labelc31
			// 
			this->labelc31->AutoSize = true;
			this->labelc31->Location = System::Drawing::Point(6, 28);
			this->labelc31->Name = L"labelc31";
			this->labelc31->Size = System::Drawing::Size(39, 25);
			this->labelc31->TabIndex = 13;
			this->labelc31->Text = L"chr";
			// 
			// textBoxE3b
			// 
			this->textBoxE3b->Location = System::Drawing::Point(46, 403);
			this->textBoxE3b->Name = L"textBoxE3b";
			this->textBoxE3b->ReadOnly = true;
			this->textBoxE3b->Size = System::Drawing::Size(1099, 30);
			this->textBoxE3b->TabIndex = 10;
			// 
			// textBoxM3b
			// 
			this->textBoxM3b->Location = System::Drawing::Point(46, 100);
			this->textBoxM3b->Name = L"textBoxM3b";
			this->textBoxM3b->Size = System::Drawing::Size(1099, 30);
			this->textBoxM3b->TabIndex = 9;
			this->textBoxM3b->TextChanged += gcnew System::EventHandler(this, &main::textBoxM3b_TextChanged);
			// 
			// textBoxE3h
			// 
			this->textBoxE3h->Location = System::Drawing::Point(46, 367);
			this->textBoxE3h->Name = L"textBoxE3h";
			this->textBoxE3h->ReadOnly = true;
			this->textBoxE3h->Size = System::Drawing::Size(1099, 30);
			this->textBoxE3h->TabIndex = 6;
			// 
			// textBoxS3i
			// 
			this->textBoxS3i->BackColor = System::Drawing::SystemColors::Window;
			this->textBoxS3i->Location = System::Drawing::Point(46, 206);
			this->textBoxS3i->Name = L"textBoxS3i";
			this->textBoxS3i->Size = System::Drawing::Size(1099, 30);
			this->textBoxS3i->TabIndex = 5;
			// 
			// textBoxE3c
			// 
			this->textBoxE3c->Location = System::Drawing::Point(46, 331);
			this->textBoxE3c->Name = L"textBoxE3c";
			this->textBoxE3c->ReadOnly = true;
			this->textBoxE3c->Size = System::Drawing::Size(1099, 30);
			this->textBoxE3c->TabIndex = 5;
			// 
			// textBoxM3h
			// 
			this->textBoxM3h->Location = System::Drawing::Point(46, 64);
			this->textBoxM3h->Name = L"textBoxM3h";
			this->textBoxM3h->Size = System::Drawing::Size(1099, 30);
			this->textBoxM3h->TabIndex = 12;
			this->textBoxM3h->TextChanged += gcnew System::EventHandler(this, &main::textBoxM3h_TextChanged);
			// 
			// textBoxM3c
			// 
			this->textBoxM3c->Location = System::Drawing::Point(46, 28);
			this->textBoxM3c->Name = L"textBoxM3c";
			this->textBoxM3c->Size = System::Drawing::Size(1099, 30);
			this->textBoxM3c->TabIndex = 4;
			this->textBoxM3c->TextChanged += gcnew System::EventHandler(this, &main::textBoxM3c_TextChanged);
			// 
			// tabPage4
			// 
			this->tabPage4->Controls->Add(this->button42);
			this->tabPage4->Controls->Add(this->button41);
			this->tabPage4->Controls->Add(this->labelS4);
			this->tabPage4->Controls->Add(this->labelD4);
			this->tabPage4->Controls->Add(this->labelE4);
			this->tabPage4->Controls->Add(this->labelb42);
			this->tabPage4->Controls->Add(this->labelb41);
			this->tabPage4->Controls->Add(this->labelh42);
			this->tabPage4->Controls->Add(this->labelh41);
			this->tabPage4->Controls->Add(this->labeli4);
			this->tabPage4->Controls->Add(this->labelc42);
			this->tabPage4->Controls->Add(this->labelc41);
			this->tabPage4->Controls->Add(this->textBoxD4b);
			this->tabPage4->Controls->Add(this->textBoxE4b);
			this->tabPage4->Controls->Add(this->textBoxD4h);
			this->tabPage4->Controls->Add(this->textBoxS4i);
			this->tabPage4->Controls->Add(this->textBoxD4c);
			this->tabPage4->Controls->Add(this->textBoxE4h);
			this->tabPage4->Controls->Add(this->textBoxE4c);
			this->tabPage4->Location = System::Drawing::Point(4, 34);
			this->tabPage4->Name = L"tabPage4";
			this->tabPage4->Padding = System::Windows::Forms::Padding(3);
			this->tabPage4->Size = System::Drawing::Size(1172, 707);
			this->tabPage4->TabIndex = 3;
			this->tabPage4->Text = L"ScramblerD";
			this->tabPage4->UseVisualStyleBackColor = true;
			// 
			// button42
			// 
			this->button42->Location = System::Drawing::Point(713, 537);
			this->button42->Name = L"button42";
			this->button42->Size = System::Drawing::Size(303, 79);
			this->button42->TabIndex = 44;
			this->button42->Text = L"Decrypt   x11+x5+x2+1";
			this->button42->UseVisualStyleBackColor = true;
			this->button42->Click += gcnew System::EventHandler(this, &main::button42_Click);
			// 
			// button41
			// 
			this->button41->Location = System::Drawing::Point(95, 537);
			this->button41->Name = L"button41";
			this->button41->Size = System::Drawing::Size(303, 79);
			this->button41->TabIndex = 43;
			this->button41->Text = L"Decrypt   x11+x2+1";
			this->button41->UseVisualStyleBackColor = true;
			this->button41->Click += gcnew System::EventHandler(this, &main::button41_Click);
			// 
			// labelS4
			// 
			this->labelS4->AutoSize = true;
			this->labelS4->Location = System::Drawing::Point(41, 178);
			this->labelS4->Name = L"labelS4";
			this->labelS4->Size = System::Drawing::Size(59, 25);
			this->labelS4->TabIndex = 42;
			this->labelS4->Text = L"Seed";
			// 
			// labelD4
			// 
			this->labelD4->AutoSize = true;
			this->labelD4->Location = System::Drawing::Point(41, 303);
			this->labelD4->Name = L"labelD4";
			this->labelD4->Size = System::Drawing::Size(101, 25);
			this->labelD4->TabIndex = 41;
			this->labelD4->Text = L"Decrypted";
			// 
			// labelE4
			// 
			this->labelE4->AutoSize = true;
			this->labelE4->Location = System::Drawing::Point(41, 0);
			this->labelE4->Name = L"labelE4";
			this->labelE4->Size = System::Drawing::Size(100, 25);
			this->labelE4->TabIndex = 40;
			this->labelE4->Text = L"Encrypted";
			// 
			// labelb42
			// 
			this->labelb42->AutoSize = true;
			this->labelb42->Location = System::Drawing::Point(7, 403);
			this->labelb42->Name = L"labelb42";
			this->labelb42->Size = System::Drawing::Size(38, 25);
			this->labelb42->TabIndex = 38;
			this->labelb42->Text = L"bin";
			// 
			// labelb41
			// 
			this->labelb41->AutoSize = true;
			this->labelb41->Location = System::Drawing::Point(7, 100);
			this->labelb41->Name = L"labelb41";
			this->labelb41->Size = System::Drawing::Size(38, 25);
			this->labelb41->TabIndex = 37;
			this->labelb41->Text = L"bin";
			// 
			// labelh42
			// 
			this->labelh42->AutoSize = true;
			this->labelh42->Location = System::Drawing::Point(1, 367);
			this->labelh42->Name = L"labelh42";
			this->labelh42->Size = System::Drawing::Size(44, 25);
			this->labelh42->TabIndex = 36;
			this->labelh42->Text = L"hex";
			// 
			// labelh41
			// 
			this->labelh41->AutoSize = true;
			this->labelh41->Location = System::Drawing::Point(1, 64);
			this->labelh41->Name = L"labelh41";
			this->labelh41->Size = System::Drawing::Size(44, 25);
			this->labelh41->TabIndex = 39;
			this->labelh41->Text = L"hex";
			// 
			// labeli4
			// 
			this->labeli4->AutoSize = true;
			this->labeli4->Location = System::Drawing::Point(13, 206);
			this->labeli4->Name = L"labeli4";
			this->labeli4->Size = System::Drawing::Size(32, 25);
			this->labeli4->TabIndex = 35;
			this->labeli4->Text = L"int";
			// 
			// labelc42
			// 
			this->labelc42->AutoSize = true;
			this->labelc42->Location = System::Drawing::Point(6, 331);
			this->labelc42->Name = L"labelc42";
			this->labelc42->Size = System::Drawing::Size(39, 25);
			this->labelc42->TabIndex = 34;
			this->labelc42->Text = L"chr";
			// 
			// labelc41
			// 
			this->labelc41->AutoSize = true;
			this->labelc41->Location = System::Drawing::Point(6, 28);
			this->labelc41->Name = L"labelc41";
			this->labelc41->Size = System::Drawing::Size(39, 25);
			this->labelc41->TabIndex = 33;
			this->labelc41->Text = L"chr";
			// 
			// textBoxD4b
			// 
			this->textBoxD4b->Location = System::Drawing::Point(46, 403);
			this->textBoxD4b->Name = L"textBoxD4b";
			this->textBoxD4b->ReadOnly = true;
			this->textBoxD4b->Size = System::Drawing::Size(1099, 30);
			this->textBoxD4b->TabIndex = 31;
			// 
			// textBoxE4b
			// 
			this->textBoxE4b->Location = System::Drawing::Point(46, 100);
			this->textBoxE4b->Name = L"textBoxE4b";
			this->textBoxE4b->Size = System::Drawing::Size(1099, 30);
			this->textBoxE4b->TabIndex = 30;
			this->textBoxE4b->TextChanged += gcnew System::EventHandler(this, &main::textBoxE4b_TextChanged);
			// 
			// textBoxD4h
			// 
			this->textBoxD4h->Location = System::Drawing::Point(46, 367);
			this->textBoxD4h->Name = L"textBoxD4h";
			this->textBoxD4h->ReadOnly = true;
			this->textBoxD4h->Size = System::Drawing::Size(1099, 30);
			this->textBoxD4h->TabIndex = 29;
			// 
			// textBoxS4i
			// 
			this->textBoxS4i->BackColor = System::Drawing::SystemColors::Window;
			this->textBoxS4i->Location = System::Drawing::Point(46, 206);
			this->textBoxS4i->Name = L"textBoxS4i";
			this->textBoxS4i->Size = System::Drawing::Size(1099, 30);
			this->textBoxS4i->TabIndex = 28;
			// 
			// textBoxD4c
			// 
			this->textBoxD4c->Location = System::Drawing::Point(46, 331);
			this->textBoxD4c->Name = L"textBoxD4c";
			this->textBoxD4c->ReadOnly = true;
			this->textBoxD4c->Size = System::Drawing::Size(1099, 30);
			this->textBoxD4c->TabIndex = 27;
			// 
			// textBoxE4h
			// 
			this->textBoxE4h->Location = System::Drawing::Point(46, 64);
			this->textBoxE4h->Name = L"textBoxE4h";
			this->textBoxE4h->Size = System::Drawing::Size(1099, 30);
			this->textBoxE4h->TabIndex = 32;
			this->textBoxE4h->TextChanged += gcnew System::EventHandler(this, &main::textBoxE4h_TextChanged);
			// 
			// textBoxE4c
			// 
			this->textBoxE4c->Location = System::Drawing::Point(46, 28);
			this->textBoxE4c->Name = L"textBoxE4c";
			this->textBoxE4c->ReadOnly = true;
			this->textBoxE4c->Size = System::Drawing::Size(1099, 30);
			this->textBoxE4c->TabIndex = 26;
			// 
			// tabPage5
			// 
			this->tabPage5->Controls->Add(this->button52);
			this->tabPage5->Controls->Add(this->button51);
			this->tabPage5->Controls->Add(this->label55);
			this->tabPage5->Controls->Add(this->label54);
			this->tabPage5->Controls->Add(this->label53);
			this->tabPage5->Controls->Add(this->textBoxR55);
			this->tabPage5->Controls->Add(this->label52);
			this->tabPage5->Controls->Add(this->textBoxR54);
			this->tabPage5->Controls->Add(this->label51);
			this->tabPage5->Controls->Add(this->textBoxR53);
			this->tabPage5->Controls->Add(this->labelS5);
			this->tabPage5->Controls->Add(this->textBoxR52);
			this->tabPage5->Controls->Add(this->labeli5);
			this->tabPage5->Controls->Add(this->textBoxR51);
			this->tabPage5->Controls->Add(this->textBoxS5i);
			this->tabPage5->Location = System::Drawing::Point(4, 34);
			this->tabPage5->Name = L"tabPage5";
			this->tabPage5->Padding = System::Windows::Forms::Padding(3);
			this->tabPage5->Size = System::Drawing::Size(1172, 707);
			this->tabPage5->TabIndex = 4;
			this->tabPage5->Text = L"ScramblerR";
			this->tabPage5->UseVisualStyleBackColor = true;
			// 
			// button52
			// 
			this->button52->Location = System::Drawing::Point(713, 485);
			this->button52->Name = L"button52";
			this->button52->Size = System::Drawing::Size(303, 79);
			this->button52->TabIndex = 49;
			this->button52->Text = L"Research   x11+x5+x2+1";
			this->button52->UseVisualStyleBackColor = true;
			this->button52->Click += gcnew System::EventHandler(this, &main::button52_Click);
			// 
			// button51
			// 
			this->button51->Location = System::Drawing::Point(95, 485);
			this->button51->Name = L"button51";
			this->button51->Size = System::Drawing::Size(303, 79);
			this->button51->TabIndex = 48;
			this->button51->Text = L"Research   x11+x2+1";
			this->button51->UseVisualStyleBackColor = true;
			this->button51->Click += gcnew System::EventHandler(this, &main::button51_Click);
			// 
			// label55
			// 
			this->label55->AutoSize = true;
			this->label55->Location = System::Drawing::Point(41, 350);
			this->label55->Name = L"label55";
			this->label55->Size = System::Drawing::Size(107, 25);
			this->label55->TabIndex = 47;
			this->label55->Text = L"Correlation";
			// 
			// label54
			// 
			this->label54->AutoSize = true;
			this->label54->Location = System::Drawing::Point(41, 289);
			this->label54->Name = L"label54";
			this->label54->Size = System::Drawing::Size(99, 25);
			this->label54->TabIndex = 47;
			this->label54->Text = L"Cyclicality";
			// 
			// label53
			// 
			this->label53->AutoSize = true;
			this->label53->Location = System::Drawing::Point(41, 228);
			this->label53->Name = L"label53";
			this->label53->Size = System::Drawing::Size(83, 25);
			this->label53->TabIndex = 47;
			this->label53->Text = L"Balance";
			// 
			// textBoxR55
			// 
			this->textBoxR55->BackColor = System::Drawing::SystemColors::Control;
			this->textBoxR55->Location = System::Drawing::Point(46, 378);
			this->textBoxR55->Name = L"textBoxR55";
			this->textBoxR55->ReadOnly = true;
			this->textBoxR55->Size = System::Drawing::Size(1099, 30);
			this->textBoxR55->TabIndex = 45;
			// 
			// label52
			// 
			this->label52->AutoSize = true;
			this->label52->Location = System::Drawing::Point(41, 167);
			this->label52->Name = L"label52";
			this->label52->Size = System::Drawing::Size(118, 25);
			this->label52->TabIndex = 47;
			this->label52->Text = L"Chi squared";
			// 
			// textBoxR54
			// 
			this->textBoxR54->BackColor = System::Drawing::SystemColors::Control;
			this->textBoxR54->Location = System::Drawing::Point(46, 317);
			this->textBoxR54->Name = L"textBoxR54";
			this->textBoxR54->ReadOnly = true;
			this->textBoxR54->Size = System::Drawing::Size(1099, 30);
			this->textBoxR54->TabIndex = 45;
			// 
			// label51
			// 
			this->label51->AutoSize = true;
			this->label51->Location = System::Drawing::Point(41, 106);
			this->label51->Name = L"label51";
			this->label51->Size = System::Drawing::Size(68, 25);
			this->label51->TabIndex = 47;
			this->label51->Text = L"Period";
			// 
			// textBoxR53
			// 
			this->textBoxR53->BackColor = System::Drawing::SystemColors::Control;
			this->textBoxR53->Location = System::Drawing::Point(46, 256);
			this->textBoxR53->Name = L"textBoxR53";
			this->textBoxR53->ReadOnly = true;
			this->textBoxR53->Size = System::Drawing::Size(1099, 30);
			this->textBoxR53->TabIndex = 45;
			// 
			// labelS5
			// 
			this->labelS5->AutoSize = true;
			this->labelS5->Location = System::Drawing::Point(41, 0);
			this->labelS5->Name = L"labelS5";
			this->labelS5->Size = System::Drawing::Size(59, 25);
			this->labelS5->TabIndex = 47;
			this->labelS5->Text = L"Seed";
			// 
			// textBoxR52
			// 
			this->textBoxR52->BackColor = System::Drawing::SystemColors::Control;
			this->textBoxR52->Location = System::Drawing::Point(46, 195);
			this->textBoxR52->Name = L"textBoxR52";
			this->textBoxR52->ReadOnly = true;
			this->textBoxR52->Size = System::Drawing::Size(1099, 30);
			this->textBoxR52->TabIndex = 45;
			// 
			// labeli5
			// 
			this->labeli5->AutoSize = true;
			this->labeli5->Location = System::Drawing::Point(13, 28);
			this->labeli5->Name = L"labeli5";
			this->labeli5->Size = System::Drawing::Size(32, 25);
			this->labeli5->TabIndex = 46;
			this->labeli5->Text = L"int";
			// 
			// textBoxR51
			// 
			this->textBoxR51->BackColor = System::Drawing::SystemColors::Control;
			this->textBoxR51->Location = System::Drawing::Point(46, 134);
			this->textBoxR51->Name = L"textBoxR51";
			this->textBoxR51->ReadOnly = true;
			this->textBoxR51->Size = System::Drawing::Size(1099, 30);
			this->textBoxR51->TabIndex = 45;
			// 
			// textBoxS5i
			// 
			this->textBoxS5i->BackColor = System::Drawing::SystemColors::Window;
			this->textBoxS5i->Location = System::Drawing::Point(46, 28);
			this->textBoxS5i->Name = L"textBoxS5i";
			this->textBoxS5i->Size = System::Drawing::Size(1099, 30);
			this->textBoxS5i->TabIndex = 45;
			// 
			// main
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::White;
			this->ClientSize = System::Drawing::Size(1178, 744);
			this->Controls->Add(this->tabControl);
			this->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->Margin = System::Windows::Forms::Padding(4);
			this->MaximizeBox = false;
			this->Name = L"main";
			this->Text = L"Lab 2";
			this->tabControl->ResumeLayout(false);
			this->tabPage1->ResumeLayout(false);
			this->tabPage1->PerformLayout();
			this->tabPage2->ResumeLayout(false);
			this->tabPage2->PerformLayout();
			this->tabPage3->ResumeLayout(false);
			this->tabPage3->PerformLayout();
			this->tabPage4->ResumeLayout(false);
			this->tabPage4->PerformLayout();
			this->tabPage5->ResumeLayout(false);
			this->tabPage5->PerformLayout();
			this->ResumeLayout(false);

		}
#pragma endregion
	};
}