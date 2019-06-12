#include <vector>
#include <string>
#include <iostream>

#include "Table.h"


void Table::AddWord(std::string str)
{
	ToLower(str);

	if (m_wordListLength > 0)
	{
		for (int i = 0; i < m_wordListLength; i++)
		{
			if (m_wordList[i].word == str)
			{
				m_wordList[i].occurances++;
				return;
			}
		}
	}

	Word word = { str, 1 };
	m_wordListLength++;
	m_wordList.push_back(word);

	return;
}

void Table::FindWord(std::string word)
{
	ToLower(word);

	bool found = false;

	for (int i = 0; i < m_wordListLength; i++)
	{
		if (CheckMatch(m_wordList[i].word, word))
		{
			std::cout << "The word " << m_wordList[i].word << " appears " << m_wordList[i].occurances
				<< " times in the document.\n";
			found = true;
		}
	} 

	if (!found)
		std::cout << "The word " << word << " appears 0 times is the document.\n";
}

int Table::GetWordListLength()
{
	return m_wordListLength;
}

void Table::ToLower(std::string &str)
{
	for (unsigned int i = 0; i < str.length(); i++)
	{
		if ((str[i] <= 'Z') && (str[i] != '?'))
			str[i] = str[i] - ('Z' - 'z');
	}
}

bool Table::CheckMatch(std::string base, std::string input)
{
	if (base.length() > input.length())
		return false;

	unsigned int wildcards = 0;

	unsigned int basePos = 0;

	for (unsigned int i = 0; i < input.length(); i++)
	{
		bool found = false;

		if (input.at(i) != '?')
		{
			for (unsigned int x = 0; x <= wildcards; x++)
			{
				if ((basePos + x) < base.length())
				{
					if (input.at(i) == base.at(basePos + x))
					{
						found = true;
						wildcards = 0;
						basePos += x + 1;
					}
				}
			}
			if (!found && (input.at(i) != '?'))
				return false;
		}
		else
			wildcards++;

	}

	if (basePos + wildcards < base.length())
		return false;
	else
		return true;
}