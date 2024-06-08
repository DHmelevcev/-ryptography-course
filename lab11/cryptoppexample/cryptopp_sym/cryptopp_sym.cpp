#include "../cryptoppexample/cryptopp_example.h"

int main(int argc, char* argv[])
{
	if (argc != 2)
		return -1;

	try {
		cryptoppexample::symmetric_chipher_dechipher(argv[1]);
	}
	catch (...) {}

	return 0;
}