#include "../includes/BitcoinExchange.hpp"
#include <iomanip>
#include <cerrno>
#include <cstring>

static bool tryOpenDataCsv(std::ifstream &data)
{
	const char *paths[] = {"data.csv", "srcs/data.csv", 0};
	for (int i = 0; paths[i]; ++i)
	{
		data.clear();
		data.open(paths[i]);
		if (data.is_open())
			return true;
	}
	return false;
}

static bool parseStrictDouble(const std::string &s, double &out)
{
	char *end = 0;
	errno = 0;
	out = std::strtod(s.c_str(), &end);
	if (errno != 0)
		return false;
	if (end == s.c_str() || *end != '\0')
		return false;
	return true;
}

static bool parseInputLine(const std::string &line, std::string &date, double &value)
{
	if (line.size() < 14)
		return false;
	const std::string sep = " | ";
	size_t pos = line.find(sep);
	if (pos == std::string::npos)
		return false;
	date = line.substr(0, pos);
	std::string valueStr = line.substr(pos + sep.size());
	if (date.size() != 10 || valueStr.empty())
		return false;
	return parseStrictDouble(valueStr, value);
}

static bool parseDateStrict(const std::string &date, int &year, int &month, int &day)
{
	if (date.size() != 10 || date[4] != '-' || date[7] != '-')
		return false;
	std::stringstream ys(date.substr(0, 4));
	std::stringstream ms(date.substr(5, 2));
	std::stringstream ds(date.substr(8, 2));
	ys >> year;
	ms >> month;
	ds >> day;
	if (ys.fail() || ms.fail() || ds.fail())
		return false;
	if (!ys.eof() || !ms.eof() || !ds.eof())
		return false;
	return true;
}

BitcoinExchange::BitcoinExchange()
{
	std::string date, value;
	std::ifstream data;
	if (!tryOpenDataCsv(data))
		throw BitcoinExchange::FileNotFound();
	std::string line;
	getline(data, line);
	while (getline(data, line))
	{
		std::stringstream ln(line);
		getline(ln, date, ',');
		getline(ln, value);
		double d = 0.0;
		if (!parseStrictDouble(value, d))
			continue;
		btcData.insert(std::make_pair(date, d));
	}
	data.close();
};

BitcoinExchange::~BitcoinExchange(){};

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
{
	std::map<std::string, double>::const_iterator i;
	for (i = other.btcData.begin(); i != other.btcData.end(); ++i)
		this->btcData[i->first] = i->second;
};

const char* BitcoinExchange::FileNotFound::what() const throw(){
	return "Error: could not open file.";
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
		std::map<std::string, double>::const_iterator it;
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
	double value;
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
		if (!parseInputLine(line, date, value))
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}

		if (!parseDateStrict(date, year, month, day))
		{
			std::cout << "Error: bad input => " << line << std::endl;
			continue;
		}
		if (value > 1000.0)
			std::cout << "Error: too large a number." << std::endl;
		else if (value < 0.0)
			std::cout << "Error: not a positive number." << std::endl;
		else if (!checkDate(year, month, day, line))
			findDateAndCalculate(date, value);
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
		std::cout << "Error: bad input => " << line << std::endl;
		return 1;
	}
	int months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	if (month == 2 && (isLeapYear(year) == true))
		months[1] = 29;
	if (day > months[month - 1])
	{
		std::cout << "Error: bad input => " << line << std::endl;
		return 1;
	}
	if (year < 2009 || (year == 2009 && month == 1 && day < 2))
	{
		std::cout << "Error: bad input => " << line << std::endl;
		return 1;
	}
	return 0;
}

void BitcoinExchange::findDateAndCalculate(std::string date, double value)
{
	std::map<std::string, double>::iterator it;
	it = this->btcData.lower_bound(date);
	if (btcData.empty())
	{
		std::cerr << "Error: database is empty" << std::endl;
		return;
	}
	if (it == this->btcData.end()) {
		it--;
		std::cout << date << " => " << value << " = " << value * (*it).second << std::endl;
		return ;
	}
	if (it == this->btcData.begin() && (*it).first != date) {
		std::cout << "Error: bad input => " << date << std::endl;
		return ;
	}
	if ((*it).first != date)
		it--;
	std::cout << date << " => " << value << " = " << (value * (*it).second) << std::endl;
}

void BitcoinExchange::showMap()
{
	std::map<std::string, double>::const_iterator it;
	for (it = btcData.begin(); it != btcData.end(); ++it)
		std::cout << it->first << ", " << it->second << std::endl;
}
