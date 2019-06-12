#pragma once

struct Word
{
	std::string word;
	int occurances;
};

class Table
{
public:
	void AddWord(std::string word);
	void FindWord(std::string word);
	int GetWordListLength();
private:
	//functions
	void ToLower(std::string &str);
	bool CheckMatch(std::string base, std::string input);

	//variables
	std::vector<Word> m_wordList;
	int m_wordListLength = 0;
};

