#include <sstream>
#include <msclr\marshal_cppstd.h>
#include "main_form.h"
#include "feistel_cipher.cpp"
#include "LFSR.cpp"

namespace MyForms {

	using namespace System;
	using namespace System::Text;



	// <String read

	String^ main_form::file_to_String(const std::string& filename)
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

	String^ main_form::file_to_HexString(const std::string& filename)
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

	String^ main_form::file_to_BinString(const std::string& filename)
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

	void main_form::String_to_file(String^ str, const std::string& filename)
	{
		std::ofstream file(filename, std::ios::binary);

		std::string stdstr = msclr::interop::marshal_as<std::string>(str);

		file << stdstr;
		file.close();
	}

	void main_form::HexString_to_file(String^ str, const std::string& filename)
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

	String^ main_form::String_to_HexString(String^ str)
	{
		return BitConverter::ToString(Encoding::Default->GetBytes(str))->Replace("-", "");
	}

	String^ main_form::String_to_BinString(String^ str)
	{
		return HexString_to_BinString(String_to_HexString(str));
	}

	String^ main_form::HexString_to_String(String^ str)
	{
		String^ result("");

		for (int i = 0; i < str->Length; i += 2) {
			result += Convert::ToChar(Convert::ToByte(str->Substring(i, 2), 16));
		}

		return result;
	}

	String^ main_form::HexString_to_BinString(String^ str)
	{
		String^ result("");

		for (int i = 0; i < str->Length; i += 2) {
			std::string stdstr = msclr::interop::marshal_as<std::string>(str->Substring(i, 2));
			result += Convert::ToString(std::stoi(stdstr, NULL, 16), 2)->PadLeft(8, '0');
		}

		return result;
	}

	String^ main_form::BinString_to_HexString(String^ str)
	{
		String^ result("");

		for (int i = 0; i < str->Length; i += 8) {
			std::string stdstr = msclr::interop::marshal_as<std::string>(str->Substring(i, 8));
			result += Convert::ToString(std::stoi(stdstr, NULL, 2), 16)->ToUpper()->PadLeft(2, '0');
		}

		return result;
	}

	String^ main_form::BinString_to_String(String^ str)
	{
		return HexString_to_String(BinString_to_HexString(str));
	}

	// String conversions>





	void main_form::textBoxChrChanged(TextBox^ textBoxC, TextBox^ textBoxH, TextBox^ textBoxB)
	{
		if (*text_chngd != false)
			return;

		*text_chngd = true;
		
		try {
			textBoxH->Text = String_to_HexString(textBoxC->Text);
			textBoxB->Text = String_to_BinString(textBoxC->Text);
		}
		catch (Exception^) {
			try {
				textBoxC->Text = HexString_to_String(textBoxH->Text);
			}
			catch (Exception^) {}
		}

		*text_chngd = false;
	}

	void main_form::textBoxHexChanged(TextBox^ textBoxC, TextBox^ textBoxH, TextBox^ textBoxB)
	{
		if (textBoxH->Text->Length % 2 != 0)
			return;

		if (*text_chngd != false)
			return;

		*text_chngd = true;

		try {
			textBoxC->Text = HexString_to_String(textBoxH->Text);
			textBoxB->Text = HexString_to_BinString(textBoxH->Text);
		}
		catch (Exception^) {
			try {
				textBoxH->Text = BinString_to_HexString(textBoxB->Text);
			}
			catch (Exception^) {}
		}

		*text_chngd = false;
	}

	void main_form::textBoxBinChanged(TextBox^ textBoxC, TextBox^ textBoxH, TextBox^ textBoxB)
	{
		if (textBoxB->Text->Length % 8 != 0)
			return;

		if (*text_chngd != false)
			return;

		*text_chngd = true;

		try {
			textBoxC->Text = BinString_to_String(textBoxB->Text);
			textBoxH->Text = BinString_to_HexString(textBoxB->Text);
		}
		catch (Exception^) {
			try {
				textBoxB->Text = HexString_to_BinString(textBoxH->Text);
			}
			catch (Exception^) {}
		}

		*text_chngd = false;
	}





	bool main_form::encryption_begin()
	{
		try {
			if (textBox2->Text->Length < 2)
				throw 2;
			for (size_t extra = textBox2->Text->Length % 16; extra > 0 && extra < 16; ++extra)
				textBox2->Text += '\0';

			HexString_to_file(textBox2->Text, "input.txt");
		}
		catch (int) {
			MessageBox::Show("Invalid Message in hex", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return false;
		}
		try {
			if (textBox5->Text->Length < 2)
				throw 5;
			for (size_t extra = textBox5->Text->Length % 16; extra > 0 && extra < 16; ++extra)
				textBox5->Text += '\0';

			HexString_to_file(textBox5->Text, "key.txt");
			textBox13->Text = textBox4->Text;
			textBox14->Text = textBox5->Text;
			textBox15->Text = textBox6->Text;
		}
		catch (int) {
			MessageBox::Show("Invalid Key in hex", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return false;
		}

		return true;
	}

	void main_form::encryption_end()
	{
		textBox8->Text = file_to_HexString("ciphered.txt");
		textBox7->Text = HexString_to_String(textBox8->Text);
		textBox9->Text = HexString_to_BinString(textBox8->Text);

		textBox10->Text = textBox7->Text;
		textBox11->Text = textBox8->Text;
		textBox12->Text = textBox9->Text;
	}

	System::Void main_form::button1_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (!encryption_begin())
			return;

		feistel_cipher<>::cipher("input.txt", "ciphered.txt", "key.txt");

		encryption_end();
	}

	System::Void main_form::button2_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (!encryption_begin())
			return;

		feistel_cipher<>::cipher<8, 1, 0>("input.txt", "ciphered.txt", "key.txt");

		encryption_end();
	}

	System::Void main_form::button3_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (!encryption_begin())
			return;

		feistel_cipher<16, 14, 1, 0>::cipher("input.txt", "ciphered.txt", "key.txt");

		encryption_end();
	}

	System::Void main_form::button4_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (!encryption_begin())
			return;

		feistel_cipher<16, 14, 1, 0>::cipher<8, 1, 0>("input.txt", "ciphered.txt", "key.txt");

		encryption_end();
	}





	bool main_form::decryption_begin()
	{
		try {
			if (textBox11->Text->Length < 2)
				throw 11;
			for (size_t extra = textBox11->Text->Length % 16; extra > 0 && extra < 16; ++extra)
				textBox11->Text += '\0';

			HexString_to_file(textBox11->Text, "ciphered.txt");
		}
		catch (int) {
			MessageBox::Show("Invalid Encrypted in hex", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return false;
		}
		try {
			if (textBox14->Text->Length < 2)
				throw 14;
			for (size_t extra = textBox14->Text->Length % 16; extra > 0 && extra < 16; ++extra)
				textBox14->Text += '\0';

			HexString_to_file(textBox14->Text, "key.txt");
			textBox4->Text = textBox13->Text;
			textBox5->Text = textBox14->Text;
			textBox6->Text = textBox15->Text;
		}
		catch (int) {
			MessageBox::Show("Invalid Key in hex", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return false;
		}

		return true;
	}

	void main_form::decryption_end()
	{
		textBox17->Text = file_to_HexString("output.txt");
		textBox16->Text = HexString_to_String(textBox17->Text);
		textBox18->Text = HexString_to_BinString(textBox17->Text);
	}

	System::Void main_form::button5_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (!decryption_begin())
			return;

		feistel_cipher<>::decipher("ciphered.txt", "output.txt", "key.txt");

		decryption_end();
	}

	System::Void main_form::button6_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (!decryption_begin())
			return;

		feistel_cipher<>::decipher<8, 1, 0>("ciphered.txt", "output.txt", "key.txt");

		decryption_end();
	}

	System::Void main_form::button7_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (!decryption_begin())
			return;

		feistel_cipher<16, 14, 1, 0>::decipher("ciphered.txt", "output.txt", "key.txt");

		decryption_end();
	}

	System::Void main_form::button8_Click(System::Object^ sender, System::EventArgs^ e)
	{
		if (!decryption_begin())
			return;

		feistel_cipher<16, 14, 1, 0>::decipher<8, 1, 0>("ciphered.txt", "output.txt", "key.txt");

		decryption_end();
	}

	System::Void main_form::button9_Click(System::Object^ sender, System::EventArgs^ e)
	{
		uint64_t m1, k1, m2, k2;
		try {
			m1 = Convert::ToUInt64(textBox20->Text, 16);
			k1 = Convert::ToUInt64(textBox23->Text, 16);
			m2 = Convert::ToUInt64(textBox26->Text, 16);
			k2 = Convert::ToUInt64(textBox29->Text, 16);
		}
		catch (Exception^) {
			MessageBox::Show("Args must be 64-bit long", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		feistel_cipher<>::avalanche_test("test.txt", m1, k1, m2, k2);
		MessageBox::Show("", "Done", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
	}

	System::Void main_form::button10_Click(System::Object^ sender, System::EventArgs^ e)
	{
		uint64_t m1, k1, m2, k2;
		try {
			m1 = Convert::ToUInt64(textBox20->Text, 16);
			k1 = Convert::ToUInt64(textBox23->Text, 16);
			m2 = Convert::ToUInt64(textBox26->Text, 16);
			k2 = Convert::ToUInt64(textBox29->Text, 16);
		}
		catch (Exception^) {
			MessageBox::Show("Args must be 64-bit long", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		feistel_cipher<>::avalanche_test<8, 1, 0>("test.txt", m1, k1, m2, k2);
		MessageBox::Show("", "Done", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
	}

	System::Void main_form::button11_Click(System::Object^ sender, System::EventArgs^ e)
	{
		uint64_t m1, k1, m2, k2;
		try {
			m1 = Convert::ToUInt64(textBox20->Text, 16);
			k1 = Convert::ToUInt64(textBox23->Text, 16);
			m2 = Convert::ToUInt64(textBox26->Text, 16);
			k2 = Convert::ToUInt64(textBox29->Text, 16);
		}
		catch (Exception^) {
			MessageBox::Show("Args must be 64-bit long", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		feistel_cipher<16, 14, 1, 0>::avalanche_test("test.txt", m1, k1, m2, k2);
		MessageBox::Show("", "Done", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
	}

	System::Void main_form::button12_Click(System::Object^ sender, System::EventArgs^ e)
	{
		uint64_t m1, k1, m2, k2;
		try {
			m1 = Convert::ToUInt64(textBox20->Text, 16);
			k1 = Convert::ToUInt64(textBox23->Text, 16);
			m2 = Convert::ToUInt64(textBox26->Text, 16);
			k2 = Convert::ToUInt64(textBox29->Text, 16);
		}
		catch (Exception^) {
			MessageBox::Show("Args must be 64-bit long", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
			return;
		}

		feistel_cipher<16, 14, 1, 0>::avalanche_test<8, 1, 0>("test.txt", m1, k1, m2, k2);
		MessageBox::Show("", "Done", MessageBoxButtons::OK, MessageBoxIcon::Asterisk);
	}
}