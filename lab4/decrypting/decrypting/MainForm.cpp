#include<sstream>
#include "MainForm.h"
#include "../../Vigenere_cipher.h"

using namespace System;
using namespace System::Windows::Forms;

String^ file_to_WinString(const std::string& filename)
{
	std::ifstream file(filename);

	String^ result;

	std::stringstream buffer;
	buffer << file.rdbuf();

	result = gcnew String(buffer.str().c_str());

	file.close();

	return result;
}

[STAThreadAttribute]
int main(array<String^>^ args)
{
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	decrypting::MainForm form;

	try
	{
		Vigenere_cipher cipherer("key.txt");

		auto result_cipher = cipherer.decipher("./ciphered.txt", "./output.txt");
		if (!result_cipher)
		{
			form.add_page1("Input is empty\n");
		}
		else
		{
			form.add_page1("Ключ: " + gcnew String(cipherer.get_key().c_str()));
			form.add_page2(file_to_WinString("./ciphered.txt"));
			form.add_page3(file_to_WinString("./output.txt"));
		}
	}
	catch (int err)
	{
		if (err == 0)
			form.add_page1("Key file is empty");
		if (err == 1)
			form.add_page1("Invalid character");
	}

	Application::Run(% form);
	return 0;
}