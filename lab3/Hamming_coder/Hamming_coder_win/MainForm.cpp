#include<sstream>
#include "MainForm.h"
#include "../../Hamming_code.h"

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
	Hammingcoderwin::MainForm form;

	Hamming_code coder;
	form.add_page1(gcnew String(coder.code_to_string().c_str()));

	auto result_coder = coder.encode("./input2.txt", "./coded.txt");
	if (!result_coder)
	{
		form.add_page1("Input is empty\n");
	}
	else
	{
		form.add_page1("Coded Input lenght: " + result_coder);
		form.add_page2(file_to_WinString("./input2.txt"));
		form.add_page3(file_to_WinString("./coded.txt"));
	}

	Application::Run(% form);
	return 0;
}