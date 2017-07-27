#include <iostream>
#include <cstdlib>
#include <stdexcept>
#include <new>
#include "file_for_search.h"

int main(int argc, char* argv[])
{
	try
	{
		if (argc != 3)
			throw std::runtime_error("Incorrect arguments");

		txtFile f1(argv[1]);
	
		if (!f1.print_repeating_more_than_N(std::stoi(std::string(argv[2]))))
			std::cout << "Nothing is find"
				<< std::endl;
	}

	catch (std::runtime_error& ex)
	{
		std::cout << ex.what()
			<< std::endl;
		return 1;
	}

	catch (std::bad_alloc& ex)
	{
		std::cout << ex.what()
			<< std::endl;
		return 2;
	}	

	catch (std::exception& ex)
	{
		std::cout << ex.what()
			<< std::endl;
		return 3;
	}

	catch (...)
	{
		std::cout << "Unknown error occured"
			<< std::endl;
		throw;
	}

	return 0;
}
