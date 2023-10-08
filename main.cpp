#include <iostream>
#include <fstream>
#include <istream>
#include <iomanip>

#include "variadic_parser.hpp"


void populate_ex(const std::string& line, std::string& err)
{
			err+=(", input string: \"");
			std::copy(line.begin(), line.end() - 1, std::back_inserter(err));
		   err+=("\"");
}

void readData(std::istream& in)
{
	std::string line;
	while(getline(in, line))
	{

		try
		{
			switch(line[0])
			{
				case 'N':
					{
						char c;
						std::string symbol;
						int user, qty, userOrderId, price;
						parse_line(2, line, ',' , user, symbol, price, qty, c, userOrderId);
						std::cout 
								<< "User: " << user 
								<< ", symbol: " << symbol 
								<< ", price: " << price 
								<< ", qty: " << qty 
								<< ", Side: \"" << c 
								<< "\", userOrderId: " << userOrderId 
								<< std::endl;
						break;
					}
				case 'C':
					{
						int user, userOrderId;
						parse_line(2, line, ',', user, userOrderId);
						std::cout 
								<< "user: " << user 
								<< ", userOrderId: "
								<< userOrderId 
								<< std::endl;

						break;
					}
				case 'R':
					{
						int int1 , int2 , int3;
						float f1;
						parse_line(2, line, ',', int1, int2, int3, f1);
						std::cout 
								<< "int1: " << int1 
								<< ", int2 : " << int2 
								<< ", f1: " << f1  
								<< std::endl;
						break;
					}
				case 'P':
					{
						//cout << "ReplaceOrder: ";
						int user, userOrderId;
						double qty;
						std::string symbol;
						char side;
						parse_line(2, line, ',', user, userOrderId, qty, symbol, side);
						std::streamsize ss = std::cout.precision();
						std::cout 
							<< std::fixed 
							<< "user: " << user 
							<< ", userOrderId: " << userOrderId 
							<< ", qty: " << qty 
							<< ", symbol: " << symbol
							<< ", side: " << side 
							<< std::endl;
						std::cout.precision (ss);
						break;
					}
				case 'Q':
					{
						int user, userOrderId;
						double qty;
						double price;
						bool valid;
						parse_line(2, line, ',', user, userOrderId, qty, valid, price);
						std::streamsize ss = std::cout.precision();
						std::cout 
							<< "user: " << user 
							<< ", userOrderId: " << userOrderId 
							<< ", qty: " << qty 
							<< ", valid: " << std::boolalpha << valid
							<< ", price: " << price 
							<< std::endl;
						std::cout.precision (ss);
						break;
					}

				case 'F':
					{
						float f1, f2;
						char c;
						parse_line(2, line, ',', f1, c, f2);
						std::cout 
							<< "f1: " << f1  
							<< ", c: " << c 
							<< ", f2: " << f2 
							<< std::endl;
						break;
					}
				default:
					{
						// ignore everything else
						std::cerr << "Ignoring line: " << line << std::endl;
					} 
			}
		}
		catch (const std::out_of_range& oor)
		{
			std::string err(oor.what());
			populate_ex(line, err);
			std::cerr << err << std::endl;
		}
		catch (const std::invalid_argument& ia)
		{

			std::string err(ia.what());
			populate_ex(line, err);
			std::cerr << err << std::endl;
		}
		catch ( const std::exception& ex)
		{
			std::cerr << ex.what() << std::endl;
		}

	}

}


int main(int argc, char** argv)
{

	if ( argc > 1 )
	{
		//cout << "Reading from file: " << argv[1] << endl;
		// The input file has been passed in the command line.
		// Read the data from it.
		std::ifstream ifile(argv[1]);
		if ( ifile )
		{
			readData(ifile);
		}
		else
		{
			std::cerr << "No such file " << argv[1] << std::endl;
			return 1;
		}
	}
	else
	{
		// No input file has been passed in the command line.
		// Read the data from stdin (std::cin).
		std::cout << "Reading from stdin " << std::endl;
		readData(std::cin);
	}


	return 0;
}


