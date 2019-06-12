#pragma once
#include <fstream>
#include <iostream>

#include "CharacterList.h"

class HuffmanTree
{
public:
	HuffmanTree(std::string preorderFileName, std::string inorderFileName);
	~HuffmanTree();

	TreeNode add(TreeNode left, TreeNode right);
	void preorder(TreeNode node);
	void inorder(TreeNode node);
	void encodeCharacters(TreeNode node);
	std::string encodeMessage(int message[], int length);
	
private:
	TreeNode** nodeArray;
	int arraySize;
	int nodes;
	int treeID;
	std::ofstream preorderFile;
	std::ofstream inorderFile;
};

