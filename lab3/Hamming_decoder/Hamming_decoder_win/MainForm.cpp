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
	Hammingdecoderwin::MainForm form;

	Hamming_code coder;
	form.add_page1(gcnew String(coder.code_to_string().c_str()));

	auto result_decoder = coder.decode("./coded.txt", "./output.txt");
	if (!result_decoder[0])
	{
		form.add_page1("Coded Input is empty\n");
	}
	else
	{
		form.add_page1("Output lenght: " + result_decoder[0] + "\nErrors after: ");
		for (auto it = result_decoder.begin() + 1; it != result_decoder.end(); ++it)
			form.add_page1(" " + *it);
		form.add_page2(file_to_WinString("./coded.txt"));
		form.add_page3(file_to_WinString("./output.txt"));
	}

	Application::Run(% form);
	return 0;
}