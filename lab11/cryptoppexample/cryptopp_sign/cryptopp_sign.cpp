#include "../cryptoppexample/cryptopp_example.h"

int main(int argc, char* argv[])
{
	if (argc != 2)
		return -1;

	try {
		cryptoppexample::signer_verifier(argv[1]);
	}
	catch (...) {}

	return 0;
}