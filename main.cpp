#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <regex>


int main()
{
	std::ifstream io;
	io.open("input.txt");
	std::string data;
	data.reserve(20000);

	for (std::string line; std::getline(io, line);)
	{
		data.append(line);
	}

	//std::cout << data << std::endl;

	std::size_t pos = 0;
	std::string temp;

	std::vector<std::pair<int, int>> numbers;
	std::pair<int, int> number;

	std::vector<std::string> commands;

	std::regex getMul("mul\\([0-9]+,[0-9]+\\)");
	std::regex num("\\d{1,3}");
	std::smatch m;
	bool first = true;

	for (std::sregex_iterator i = std::sregex_iterator(data.begin(), data.end(), getMul); i != std::sregex_iterator(); ++i)
	{
		m = *i;
		commands.push_back(m.str());
	}

	for (auto command : commands)
	{
		for (std::sregex_iterator i = std::sregex_iterator(command.begin(), command.end(), num); i != std::sregex_iterator(); ++i)
		{
			m = *i;
			if (first)
			{
				first = false;
				number.first = std::stoi(m.str());
			}
			else
			{
				first = true;
				number.second = std::stoi(m.str());
			}
		}
		numbers.push_back(number);
	}

	int totalNumber = 0;

	for (auto n : numbers)
	{
		totalNumber += (n.first * n.second);
	}

	std::cout << "All mul() results: " << totalNumber;
}
