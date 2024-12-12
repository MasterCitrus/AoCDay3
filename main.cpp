#include <fstream>
#include <vector>
#include <iostream>
#include <string>
#include <regex>


std::string CheckInstruction(std::string data);
std::vector<std::pair<int, int>> GetNumbers(std::string data, int iteration);

int main()
{
	std::ifstream io;
	io.open("input.txt");
	std::string data;

	for (std::string line; std::getline(io, line);)
	{
		data.append(line);
	}

	std::vector<std::pair<int, int>> numbers;

	int i = 0;
	numbers = GetNumbers(data, ++i);
	

	int totalNumber = 0;

	for (auto n : numbers)
	{
		totalNumber += (n.first * n.second);
	}

	std::cout << "All mul() results: " << totalNumber << "\n\n";

	std::string newData = CheckInstruction(data);

	numbers = GetNumbers(newData, ++i);

	totalNumber = 0;

	for (auto n : numbers)
	{
		totalNumber += (n.first * n.second);
	}

	std::cout << "All do() mul() results: " << totalNumber << "\n\n";
}

std::string CheckInstruction(std::string data)
{
	std::size_t end = data.size();
	std::size_t doPos = 0;
	std::size_t dnPos = 0;
	std::vector<std::string> temp;
	std::string string;

	std::ofstream output;
	output.open("output.txt");

	while (end != std::string::npos)
	{
		doPos = data.rfind("do()", end);
		dnPos = data.rfind("don't()", end);

		if (end - doPos < end - dnPos)
		{
			string = data.substr(doPos, (end - doPos) + 1);
			temp.push_back(string);
			//std::cout << string << std::endl;
			output << string << std::endl;
			end = doPos - 1;
		}
		else
		{
			end = dnPos - 1;
		}
		if (doPos == std::string::npos && dnPos == std::string::npos)
		{
			doPos = data.find("do()", 0);
			dnPos = data.find("don't()", 0);

			if (doPos < dnPos)
			{
				string = data.substr(0, doPos);
				temp.push_back(string);
				output << string << std::endl;
				break;
			}
			else break;
		}
	}

	string.clear();

	for (auto s : temp)
	{
		string.append(s);
	}

	return string;
}

std::vector<std::pair<int, int>> GetNumbers(std::string data, int iteration)
{
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

	std::string file;

	file.append("mul").append(std::to_string(iteration)).append(".txt");
	std::ofstream output(file);
	for (auto s : commands)
	{
		output << s << std::endl;
	}
	

	output.close();

	return numbers;
}
