#include <sstream>
#include <fstream>
#include "MainForm.h"
#include "RandomPrimalGenerator.h"
#include "Factorisator.h"

using namespace System;
using namespace System::Windows::Forms;

template<typename T>
void saveVector(std::vector<T>& sample, const std::string& filename)
{
	std::ofstream file(filename);

	for (auto& i : sample)
	{
		file << i << "  ";
	}

	file.close();
}

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
	MillerRabin::MainForm form;
	
	try
	{
		//***FACTORISATION***//
		Factorisator fact;
		uint64_t number = Convert::ToInt64(file_to_WinString("input.txt"));
		auto factors = fact.factorise(number);
		auto factors_string = fact.to_string(factors);

		form.add_page1(gcnew String((std::to_string(number) + " = " + factors_string + '\n').c_str()));
		form.add_page1(gcnew String(std::to_string(fact.loops()).c_str()) + " loops  ");
		form.add_page1(gcnew String(std::to_string(fact.time().count()).c_str()) + " mcs");
		saveVector(std::vector<std::string>({ factors_string }), "factors.txt");



		//***PRIMAL GENERATOR***//
		
		//RandomPrimalGenerator gen;

		//uint16_t digits = Convert::ToInt16(file_to_WinString("input.txt"));

		//auto prime = gen.next(digits);
		//auto loops = gen.loops();
		//auto time  = gen.time();

		//saveVector(std::vector<uint64_t>({prime}), "prime.txt");
		//form.add_page1("Prime: " + file_to_WinString("prime.txt"));
		//form.add_page1(gcnew String(std::to_string(loops).c_str()) + " loops  ");
		//form.add_page1(gcnew String(std::to_string(time.count()).c_str()) + " mcs");
	}
	catch (int err)
	{
		if (err == 1) form.add_page1("Trying generate zero digits number");
		if (err == 2) form.add_page1("Trying generate number with amount digits > 64");
		if (err == 3) form.add_page1("Trying to test primality of number < 1");
	}
	catch (System::FormatException^ err)
	{
		form.add_page1("Input file broken");
	}

	Application::Run(% form);
	return 0;
}