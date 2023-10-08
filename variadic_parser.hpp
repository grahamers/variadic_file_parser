#include <iostream>
#include <string> 
#include <stdexcept> 
#include <stdexcept> 
#include <sstream> 


// bool converter
void convert(std::string& str, bool& b) // can throw std::out_of_range, std::invalid_argument
{

	transform(str.begin(), str.end(), str.begin(), ::tolower);
	b = (str == "true" ?  true : false);
};

// double converter
void convert(const std::string& str, double& d) // can throw std::out_of_range, std::invalid_argument
{
	d = std::stod(str);
};

// int converter
void convert(const std::string& str, int& i) // can throw std::out_of_range, std::invalid_argument
{
	i = std::stoi(str);
};

// float converter
void convert(const std::string& str, float& f) // can throw std::out_of_range, std::invalid_argument
{
	f = std::stof(str);
};


// add your own converts here following as above.
// catch custom exceptions in from_string below and handle
//
//


/*  "integral" concept: equal to true, if T is the type bool, char, char8_t (since C++20), 
 *  char16_t, char32_t, wchar_t, short, int, long, long long, or any 
 *  implementation-defined extended integer types, including any signed, 
 *  unsigned, and cv-qualified variants. Otherwise, value is equal to false
 */
template<typename T>
concept arithmetic = std::integral<T> or std::floating_point<T>;


template <typename T>
	requires arithmetic<T>
void from_string(const std::string& input, T& arg, size_t& pos, const char separator)
{

	std::string to_convert;
	try
	{
		size_t loc = input.find(separator, pos);
		if (loc == std::string::npos)
		{
			loc = input.length();
		}
		to_convert = input.substr(pos, loc-pos);

		convert(to_convert, arg);
		pos = loc +1;
	}
	catch (const std::out_of_range& oor_ex)
	{

		std::ostringstream oss;
		oss  	<< "Exception: string conversion (range) at pos: " << pos;
		throw std::out_of_range(oss.str());
	}
	catch (const std::invalid_argument& ia_ex)
	{
		std::ostringstream oss;
		oss << "Exception: string conversion (invalid) at pos: " << pos;
		throw std::invalid_argument(oss.str());
	}
	catch (const std::exception & ex)
	{
		std::ostringstream oss;
		oss << "Exception: string conversion (general) at pos: " << pos << std::endl;
		throw;
	}
	catch (...)
	{
		std::cerr << "Exception: string conversion (critical) impossible for arg: " 
			       << to_convert << ", pos: " << pos << ", to type " << std::endl;
	}
}

void from_string(const std::string& input, std::string& arg, size_t& pos, const char separator)
{
	try
	{
		size_t loc = input.find(separator,pos);
		if (loc == std::string::npos)
		{
			loc = input.length();
		}
		arg = input.substr(pos, loc-pos);
		arg.erase(std::remove_if(arg.begin(), arg.end(), ::isspace), arg.end());

		pos = loc+1;
	}
	catch (...)
	{
		std::cerr << "ERROR cannot parse input: " << input << ", pos: " << pos << std::endl;
		arg = "NULL";
	}
};

void from_string(const std::string& input, char& arg, size_t& pos, const char separator)
{
	try
	{
		// cater for input (',' is separator) "1,2,  S , 12.2" 
		// where we are looking for the S char
		while (pos < input.size())
		{
			if (std::isspace(input[pos]))
			{
				++pos;
			}
			else if (std::isalpha(input[pos]))
			{
				arg = input[pos];
				++pos;
			}
			else if (input[pos] == separator)
			{
				pos+=1;
				break;
			}
		}
	}
	catch (...)
	{
		std::cerr << "Rubbish input: " <<  input << ", " << separator << std::endl;
		arg = 'X';
	}
};

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

void parse_line(size_t start_pos, std::string& input, const char separator)
{
};
#pragma GCC diagnostic pop
	template <typename P1 , typename ...Param>
void parse_line(size_t start_pos, std::string& input, const char separator, P1& p1 , Param&... args)
{
	from_string(input, p1, start_pos, separator);
	parse_line(start_pos, input, separator, args...);

}



