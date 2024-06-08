#include<fstream>
#include<iostream>

//ascii chars from 0 to 9 and from A to V
bool generate_text(std::ofstream& out, unsigned int size = 1000)
{
	for (size_t i = 0; i < size; i++)
	{
		char r = rand() % 32 + 0x30;
		
		if (r > 0x39) r += 7;

		out << r;
	}

	return true;
}

int main()
{
	std::cout << "Text size: ";
	size_t size = 1000;

	std::cin >> size;
	if (std::cin)
	{
		std::ofstream out("./input2.txt");
		generate_text(out, size);
		out.close();
	}

	return 0;
}