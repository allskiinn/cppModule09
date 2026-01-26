#include "../includes/BitcoinExchange.hpp"
#include <iomanip>

BitcoinExchange::BitcoinExchange()
{
	std::string date, value;
	std::ifstream data("srcs/data.csv");
	if (!data.is_open())
		throw BitcoinExchange::FileNotFound();
	std::string line;
	getline(data, line);
	while (getline(data, line))
	{
		std::stringstream ln(line);
		getline(ln, date, ',');
		getline(ln, value);
		btcData.insert(std::make_pair(date, atof(value.c_str())));
	}
	data.close();
};

BitcoinExchange::~BitcoinExchange(){};

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
	std::map<std::string, float>::const_iterator i;
	for (i = other.btcData.begin(); i != other.btcData.end(); ++i)
		this->btcData[i->first] = i->second;
};

const char* BitcoinExchange::FileNotFound::what() const throw(){
	return "cannot open file";
}

const char* BitcoinExchange::FileInputError::what() const throw(){
	return "Invalid first line in data file. Expected 'date | value'.";
}

const char* BitcoinExchange::FileEmpty::what() const throw(){
	return "File is empty.";
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
	{
		this->btcData.clear();
		std::map<std::string, float>::const_iterator it;
		for (it = other.btcData.begin(); it != other.btcData.end(); ++it)
		{
			this->btcData[it->first] = it->second;
		}
	}
	return *this;
};

void BitcoinExchange::validInputFile(std::string fileName)
{
	int year;
	int month;
	int day;
	float value;
	std::string date;

	std::string line;
	std::ifstream file(fileName.c_str());
	if (!file.is_open())
		throw BitcoinExchange::FileNotFound();
	getline(file, line);
	if (line != "date | value")
		throw BitcoinExchange::FileInputError();
	bool firstLine = true;
	while (getline(file, line))
	{
		if (firstLine)
			firstLine = false;
		if (line.length() < 14) {
			std::cout << "Error : bad input => " << line << std::endl;
			continue ;
		} else if (sscanf((line.c_str()), "%d-%d-%d | %f", &year, &month, &day, &value) == 4)
		{
			if (std::isspace(line[13]) || line[11] != '|' || line[line.length() - 1] == '.') {
				std::cout << "Error : bad input => " << line << std::endl;
				continue ;
			}
			if (value > 1000) std::cout << "Error: too large number." << std::endl;
			else if (value < 0) std::cout << "Error: not a positive a number." << std::endl;
			else {
				if (!checkDate(year, month, day, line))
				{
					size_t pos;
					pos = line.find(' ');
					date = line.substr(0, pos);
					findDateAndCalculate(date, value);
				}
			}
		} else {
			std::cout << "Error : bad input => " << line << std::endl;
			continue ;
		}
	}
	if (firstLine)
		throw BitcoinExchange::FileEmpty();
}

int BitcoinExchange::isLeapYear(int year)
{
	bool ReturnValue = ((year % 4 == 0 && year % 100 != 0) || year % 400 == 0) ? true : false;
	return (ReturnValue);
}

int BitcoinExchange::checkDate(int year, int month, int day, std::string line)
{
	if (month < 1 || month > 12 || day < 1) {
		std::cout << "Error : Invalid Date => " << line << std::endl;
		return 1;
	}
	int months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (month == 2 && (isLeapYear(year) == true))
		months[1] = 29;
	if (day > months[month - 1])
	{
		std::cout << "Error : Invalid Day => " << line << std::endl;
		return 1;
	}
	if (year < 2009 || (year == 2009 && month == 1 && day < 2))
	{
		std::cout << "Error : min year (2009-01-02) => " << line << std::endl;
		return 1;
	}
	if (year > 2022 || (year == 2022 && month == 3 && day > 29))
	{
		std::cout << "Error : max year (2022-03-29) => " << line << std::endl;
		return 1;
	}
	return 0;
}

void BitcoinExchange::findDateAndCalculate(std::string date, float value)
{
	std::map<std::string, float>::iterator it;
	it = this->btcData.lower_bound(date);
	if (it == this->btcData.end()) {
		it--;
		std::cout << date << " => " << value << " = " << value * (*it).second << std::endl;
		return ;
	}
	if (it == this->btcData.begin()) {
		std::cerr << "cannot find any closer data" << std::endl;
		return ;
	} else {
		if ((*it).first != date) it--;
		std::cout << date << " => " << value << " = " << (float)(value * (*it).second) << std::endl;
	}
}

void BitcoinExchange::showMap()
{
	std::map<std::string, float>::const_iterator it;
	for (it = btcData.begin(); it != btcData.end(); ++it)
		std::cout << it->first << ", " << it->second << std::endl;
}
