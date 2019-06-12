#pragma once
#include <iostream>

struct Character
{
	int character = 0;
	int occurances = 0;
};

struct TreeNode
{
	Character character;
	int id;
	std::string encoding;
	TreeNode* parent;
	TreeNode* leftChild;
	TreeNode* rightChild;
};

class CharacterList
{
public:
	CharacterList();
	~CharacterList();

	void addCharacter(int ch);
	void addNode(TreeNode node);
	void order();
	TreeNode extractMin();
	int getUniqueCharacters();

private:
	void reorder(int node);
	int twoToTheN(int n);

	int uniqueCharcters;
	int arraySize;
	int treeDepth;
	TreeNode** characterArray;
};

