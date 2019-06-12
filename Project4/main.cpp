#include <iostream>
#include <fstream>

#include "CharacterList.h"
#include "HuffmanTree.h"

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
			list.addCharcter(ch);
			message += ch;
		}
		file.get(ch);
	}

	HuffmanTree hTree;

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

	std::string encodedMessage = hTree.encodeMessage(message);
	codeFile << encodedMessage;

	std::cout << "Phase 1 code length " << encodedMessage.length() << " bits" << std::endl;

	return 0;
}