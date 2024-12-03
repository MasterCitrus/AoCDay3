#include <fstream>
#include <vector>
#include <iostream>
#include <string>


bool CheckCharacter(std::string data, std::size_t pos);

int main()
{
	std::ifstream io;
	io.open("input.txt");
	std::string data;

	for (std::string line; std::getline(io, line);)
	{
		data.append(line);
	}

	std::size_t pos = 0;

	while (pos != std::string::npos)
	{
		pos = data.find("mul(", pos) + 4;
	}
}

bool CheckCharacter(std::string data, std::size_t pos)
{
	char check = data[pos];
	if(check == )
}
