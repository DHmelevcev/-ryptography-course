#include "main_form.h"
//#include <slimcpplib/long_io.h>

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array<String^>^ args)
{
	//uint_t m = uint_t(1) << 20;

	//std::vector<bool> sample(m, false);
	//
	//RSArandomgenerator::RSA_gen<slim::uint256_t> gen(time(0));
	//for (uint_t i = 0; i < m; ++i) {
	//	sample[i] = gen.next_bit();
	//	//std::cout << sample[i];
	//}

	//std::cout << "\nChi sqr: " << chi_squared_statistic(sample) << '\n';
	//std::cout << "Balance: " << balance_statistic(sample) << '\n';
	//auto cycles = cyclicality_statistic(sample);
	//std::cout << "Cycles:";
	//for (const auto& it : cycles) {
	//	std::cout << " " << it.first << "-" << it.second;
	//}
	//std::cout << "\nCorrelation: " << correlation_statistic(sample) << '\n';
	//std::cout << "\nFrequency test: " << frequency_test(sample) << '\n';
	//std::cout << "Chain test: " << chain_test(sample) << '\n';
	//auto ext_rnd_res = extended_randomness_test(sample);
	//std::cout << "Extended randomness test:";
	//for (const auto& it : ext_rnd_res) {
	//	std::cout << " " << it;
	//}

	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	RSArandomgenerator::main_form form;
	Application::Run(% form);
	return 0;
}
