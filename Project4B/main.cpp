 #include <iostream>
#include <fstream>

#include "CharacterList.h"
#include "HuffmanTree.h"

#define FIRST_CHAR(x) x & 0xff
#define SECOND_CHAR(x) x >> 8

/* 
	return key
		0 : success
		1 : no file given
		2 : failed to open file
*/
int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cout << "No file given!\n";
		return 1;
	}

	std::ifstream file(argv[1]);// argv[1] = filename
	if (!file.is_open())
	{
		std::cout << "Failed to open file " << argv[1];
		return 2;
	}

	// File successfuly opened
	CharacterList list;
	char ch = 0;
	std::string message = "";

	while (!file.eof())
	{	
		if (ch)
		{
			list.addCharacter(ch);
			message += ch;
		}
		file.get(ch);
	}

	HuffmanTree hTree("preorder1.txt", "inorder1.txt");

	for (int i = 1; i < list.getUniqueCharacters(); i = i)
	{
		list.order();
		TreeNode left = list.extractMin();
		TreeNode right = list.extractMin();
		
		TreeNode parent = hTree.add(left, right);
		list.addNode(parent);
	}

	TreeNode top = list.extractMin();

	hTree.preorder(top);
	hTree.inorder(top);
	hTree.encodeCharacters(top);

	std::ofstream codeFile("code1.txt");
	
	int* message_int = new int[message.length()];

	for (unsigned int i = 0; i < message.length(); i++)
	{
		message_int[i] = message[i];
	}

	std::string encodedMessage1 = hTree.encodeMessage(message_int, message.length());

	codeFile << encodedMessage1;

	std::cout << "Phase 1 code Length: " << encodedMessage1.length() << " bits" << std::endl;

	//Phase 2

	struct CharPair
	{
		char char1 = 0;
		char char2 = 0;
		int occurances = 1;
	};

	CharPair* characterPairs = new CharPair[message.length() - 1];
	int numPairs = 0;

	for (unsigned int i = 1; i < message.length(); i ++)
	{
		bool duplicate = false;

		for (unsigned int j = 0; j < i - 1; j++)
		{
			if ((message[i - 1] == characterPairs[j].char1) && (message[i] == characterPairs[j].char2))
			{
				characterPairs[j].occurances++;
				duplicate = true;
				break;
			}
		}

		if (duplicate) 
			continue;

		characterPairs[numPairs].char1 = message[i - 1];

		characterPairs[numPairs].char2 = message[i];

		numPairs++;
	}

	for (int i = 0; i < numPairs - 1; i++)
	{
		if (characterPairs[i].occurances < characterPairs[i + 1].occurances)
		{
			CharPair tmp = characterPairs[i];

			characterPairs[i] = characterPairs[i + 1];
			characterPairs[i + 1] = tmp;
		}
	}

	int replacedLength = message.length();

	for (int i = 0; i < numPairs; i++)//cycle through pairs
	{
		int* new_message_int = new int[replacedLength];
		int new_replacedLength = replacedLength;
		int replaced = 0;

		//replace instances of pair
		for (int j = 0; j < replacedLength; j++)
		{
			if ((j < (replacedLength - 1)) && (message_int[j] == characterPairs[i].char1)
				&& (message_int[j + 1] == characterPairs[i].char2))
			{
				new_message_int[j - replaced] = (characterPairs[i].char2 << 8) + characterPairs[i].char1;
				replaced++;
				new_replacedLength--;
				j++;
			}
			else
			{
				new_message_int[j - replaced] = message_int[j];
			}
		}

		CharacterList list2;

		for (int j = 0; j < new_replacedLength; j++)
		{
			list2.addCharacter(new_message_int[j]);
		}

		HuffmanTree hTree2("preorder2.txt", "inorder2.txt");

		for (int j = 1; j < list2.getUniqueCharacters(); j = j)
		{
			list2.order();
			TreeNode left = list2.extractMin();
			TreeNode right = list2.extractMin();

			TreeNode parent = hTree2.add(left, right);
			list2.addNode(parent);
		}

		TreeNode top2 = list2.extractMin();

		hTree2.preorder(top2);
		hTree2.inorder(top2);
		hTree2.encodeCharacters(top2);

		std::string encodedMessage2 = hTree2.encodeMessage(new_message_int, new_replacedLength);

		if (encodedMessage2.length() < encodedMessage1.length())
		{
			encodedMessage1 = encodedMessage2;
			message_int = new_message_int;
			replacedLength = new_replacedLength;
		}
	}

	std::ofstream codeFile2("code2.txt");
	codeFile2 << encodedMessage1;

	std::cout << "Phase 2 code Length: " << encodedMessage1.length() << " bits" << std::endl;

	return 0;
}