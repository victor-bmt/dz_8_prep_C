#include <iostream>
#include <fstream>
#include <ios>
#include <stdexcept>
#include <string>
#include <new>
#include "file_for_search.h"

txtFile::txtFile(const char* file_name)
{
	try
	{
		file.open(file_name, std::ifstream::in);

		if (!file.is_open())
		{
			std::string error("can't open file \"");
		       	error += file_name;
		       	error += "\"";
			throw std::runtime_error(error);
		}
	}

	catch (std::runtime_error& ex)
	{
		std::cout << "txtFile construction failed"
			<< std::endl;
		throw;
	}
	
	catch (std::bad_alloc& ex)
	{
		std::cout << "txtFile construction failed"
			<< std::endl;
		throw;

	}
}

txtFile::~txtFile()
{
	if (file.is_open())
		file.close();
}


bool txtFile::print_repeating_more_than_N(const int N)
{	
	try
	{
		file.peek();
		if (file.eof())
		{
			std::cout << "File is empty"
				<< std::endl;
			return false;
		}
	
		size_t start = 0;
		size_t finish = 0;
		int word_counter = 0;
		int pos = 0;
		std::string str;
		std::string word;
		bool flag = false;
	
		pos = seek_next_word(pos);
		while (file.good())
		{
			
			start = finish = 0;
			std::getline(file, str);
		
			// Если убрать эту проверку, последняя строка будет считываться два раза
			if (file.good())
				
				while (finish != str.size())	
				{
					extract_word(str, word, start, finish);
					
					// Ищем слово в том случае, если оно еще не встречалось
					if (!find_word_before(word, pos + start))
					{
						word_counter = find_word_after(word, pos + finish);
	
						if (word_counter > N)
						{
							print_word(word, word_counter);
							flag = true;
						}
					}
				}
	
			pos += str.size() + 1;
			pos = seek_next_word(pos);
		}

		return flag;
	}

	catch (std::bad_alloc& ex)
	{
		std::cout << "Bad allocation during file proccesing."
			<< std::endl;
		throw;
	}
}

size_t txtFile::find_word_after(const std::string& aWord, const size_t begin, const size_t init_count)
{	
	try
	{
		size_t start = 0;
		size_t finish = 0;
		size_t count = init_count;
		// Ищем, начиная со следующего предложения
		int pos = to_next_sentence(begin);
		std::string str;
		std::string word;

		pos = seek_next_word(pos);
	
		while (file.good())
		{
			start = finish = 0;
			std::getline(file, str);
	
			// Если убрать эту проверку, последняя строка считывается два раза
			if (file.good())
					
				while (finish != str.size())
				{
					extract_word(str, word, start, finish);
				
					if (!word.compare(aWord) && (word.size() > 0))
					{
						++count;
						// str.size() + 1 прибавится позже, в итоге получим необходимую позицию pos
						pos = to_next_sentence(pos + finish) - (str.size() + 1);
						break;
					}
				}
	
			pos += str.size() + 1;
			pos = seek_next_word(pos);
		}

		return count;
	}

	catch (std::bad_alloc& ex)
	{
		std::cout << "Bad allocation during \"find_word_after()\" execution."
			<< std::endl;
		throw;
	}

}


size_t txtFile::seek_next_word(size_t pos)
{
	try
	{
		const std::string word_separators(" \t\n\v\f\r!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~");
	
		file.seekg(pos);
		int ch = file.peek();
	
		if (!file.good())
			return pos;
		
		while (word_separators.find_first_of(static_cast<char>(ch)) != word_separators.npos)
		{
			file.ignore();
			++pos;
			ch = file.peek();
				
			if (file.eof())
				break;
		}
		
		return pos;
	}

	catch (std::bad_alloc& ex)
	{
		std::cout << "Bad allocation during \"seek_next_word()\" execution."
			<< std::endl;
		throw;
	}
}

void txtFile::extract_word(const std::string& str, std::string& word, size_t& start, size_t& finish)
{
	try
	{
		const std::string word_separators(" \t\n\v\f\r!\"#$%&'()*+,-./:;<=>?@[\\]^_`{|}~");
	
		start = str.find_first_not_of(word_separators, finish);
		if (start == str.npos)
			finish = start = str.size();
		else
		{
			finish = start;
			finish = str.find_first_of(word_separators, start);
	
			if (finish == str.npos)
			finish = str.size();
		}
	
		word.clear();
		word.resize(finish - start);
		std::copy(str.begin() + start, str.begin() + finish, word.begin());
	}

	catch (std::bad_alloc& ex)
	{
		std::cout << "Bad allocation during \"extract_word()\" execution."
			<< std::endl;
		throw;
	}

	return;
}

void txtFile::print_word(const std::string& word, const int word_counter)
{
	std::cout << "\"" << word << "\" "
		<< "repeats in " << word_counter << " different sentences."
		<< std::endl;
	
	return;
}


size_t txtFile::to_next_sentence(const size_t pos)
{
	try
	{
		const std::string sentence_separators(".?!");
		size_t offset = 0;
		size_t dummy = 0;
		std::string str;

		file.seekg(pos);
	
		while (file.good())
		{
			std::getline(file, str);
	
			if (!file.eof())
			{
				dummy = str.find_first_of(sentence_separators);
	
				if (dummy == str.npos)
					offset += str.size() + 1;
				else
				{
					offset += dummy + 1;
					break;
				}
			}
		}
		
		return pos + offset;
	}

	catch (std::bad_alloc& ex)
	{
		std::cout << "Bad allocation during \"to_next_sentence()\" execution."
			<< std::endl;
		throw;
	}
}

bool txtFile::find_word_before(const std::string& aWord, const size_t end)
{
	try
	{
		size_t start = 0;
		size_t finish = 0;
		size_t pos = 0;
		std::string str;
		std::string word;
		bool flag = false;

		pos = seek_next_word(pos);
	
		while (file.good() && (pos < end))
		{
			start = finish = 0;
			std::getline(file, str);	

			if (str.size() > (end - pos))
				str.resize(end - pos);
	
			// Если убрать эту проверку, последняя строка будет считываться два раза
			if (file.good() && (pos < end))
					
				while (finish != str.size())	
				{
					extract_word(str, word, start, finish);
	
					if (!word.compare(aWord))
					{
						flag = true;
						break;
					}	
				}
	
			if (flag)
				break;
			else
				pos += str.size() + 1;
			
			pos = seek_next_word(pos);
		}
	
		return flag;
	}
	
	catch (std::bad_alloc& ex)
	{
		std::cout << "Bad allocation during \"find_word_before()\" execution."
			<< std::endl;
		throw;
	}
}
