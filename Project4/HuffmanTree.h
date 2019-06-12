#pragma once
#include <fstream>
#include <iostream>

#include "CharacterList.h"

class HuffmanTree
{
public:
	HuffmanTree();
	~HuffmanTree();

	TreeNode add(TreeNode left, TreeNode right);
	void preorder(TreeNode node);
	void inorder(TreeNode node);
	void encodeCharacters(TreeNode node);
	std::string encodeMessage(std::string message);
	
private:
	TreeNode** nodeArray;
	int arraySize;
	int nodes;
	int treeID;
	std::ofstream preorderFile;
	std::ofstream inorderFile;
};

