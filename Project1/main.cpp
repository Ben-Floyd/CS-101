#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <ctype.h>

#include "Table.h"

int main(int argc, char* argv[])
{
	//check if file was passed
	if (argc < 2)
	{
		std::cout << "ERROR: No file given\n";
		return 1;
	}

	//reads filename from command line input
	std::string filename = argv[1];

	//opens file 'filename' from project dir for reading
	std::ifstream inFile(filename);

	//checks to see if file is open
	if (!inFile.is_open())
	{ //print error message  
		std::cout << "Failed to open " << filename << "\n";
	}
	else
	{ //handle file reading
		char ch;
		int numWords = 0;
		std::string word;
		Table table;

		while (!inFile.eof())
		{
			inFile.get(ch);

			if (isalpha(ch))
				word += ch;
			else if (word != "")
			{
				table.AddWord(word);
				word = "";
				numWords++;
			}
		}

		std::cout << "The number of words found in the file was " << numWords
			<< "\nThe number of unique words found in the file was " << table.GetWordListLength()
			<< ".\n";

		while (true)
		{
			std::cout << "\nPlease enter a word: ";

			std::string str;
			std::cin >> str;

			bool valid = false;

			for (unsigned int i = 0; i < str.length(); i++)
			{
				if (!isalpha(str.at(i)) && str.at(i) != '?')
				{
					std::cout <<"ERROR: invalid input\n";
					valid = false;
					i = str.length();
				}
				else
					valid = true;
			}

			if (valid)
				table.FindWord(str);
		}
	}

	return 0;
}