#include <fstream>
#include <string>

class txtFile
{
	private:
		std::ifstream file;
		
		// Перемещает указатель в файле на позицию начала следующего слова после seek
		// и возвращает ее
		size_t seek_next_word(size_t pos);

		// Вспомогательная функция для извлечения из строки очередного слова.
		// В start и finish запишутся соответственно позиции начала и конца слова в строке.
		// В word запишется очередное слово
		void extract_word(const std::string& str, std::string& word, size_t& start, size_t& finish);

		void print_word(const std::string& word, const int N);

		size_t find_word_after(const std::string& aWord, const size_t begin, const size_t init_count = 1);
		bool find_word_before(const std::string& aWord, const size_t end);
		size_t to_next_sentence(const size_t pos);


	public:
		txtFile(const char* file_name);
		txtFile(const txtFile&) = delete;
		txtFile& operator = (const txtFile&) = delete;
		~txtFile();

		bool print_repeating_more_than_N(const int N);
	
};
