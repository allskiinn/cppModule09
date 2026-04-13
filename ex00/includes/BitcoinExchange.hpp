#ifndef BTC_H
# define BTC_H

# include <fstream>
# include <iostream>
# include <map>
# include <string>
# include <sstream>
# include <cstdlib>
# include <climits>
# include <exception>

class BitcoinExchange
{
  private:
	std::map<std::string, double> btcData;
  public:
	BitcoinExchange();
	BitcoinExchange(const BitcoinExchange& other);
	BitcoinExchange& operator=(const BitcoinExchange& other);
	~BitcoinExchange();
	void validInputFile(std::string fileName);
	int checkDate(int year, int month, int day, std::string line);
	int isLeapYear(int year);
	void findDateAndCalculate(std::string date, double value);
	void showMap();

	class FileNotFound : public std::exception {
		public :
			virtual const char *what() const throw();
	};
	class FileInputError : public std::exception {
		public :
			virtual const char *what() const throw();
	};
	class FileEmpty : public std::exception {
		public :
			virtual const char *what() const throw();
	};
};

#endif