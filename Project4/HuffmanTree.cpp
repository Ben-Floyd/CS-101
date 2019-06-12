#include "HuffmanTree.h"



HuffmanTree::HuffmanTree()
{
	nodeArray = new TreeNode * [4];
	arraySize = 2;
	nodes = 0;
	treeID = 0;
	preorderFile.open("preorder1.txt");
	inorderFile.open("inorder1.txt");
}


HuffmanTree::~HuffmanTree()
{
	preorderFile.close();
	inorderFile.close();
}

TreeNode HuffmanTree::add(TreeNode left, TreeNode right)
{
	int leftNodeIndex = nodes;
	int rightNodeIndex = nodes + 1;
	nodes += 2;

	if (nodes >= arraySize)
	{
		TreeNode** tmp = new TreeNode * [arraySize *= 2];

		for (int i = 0; i < nodes; i++)
		{
			tmp[i] = nodeArray[i];
		}

		nodeArray = tmp;
	}

	nodeArray[leftNodeIndex] = new TreeNode(left);

	if (nodeArray[leftNodeIndex]->leftChild != nullptr)
	{
		nodeArray[leftNodeIndex]->leftChild->parent = nodeArray[leftNodeIndex];
	}

	if (nodeArray[leftNodeIndex]->rightChild != nullptr)
	{
		nodeArray[leftNodeIndex]->rightChild->parent = nodeArray[leftNodeIndex];
	}

	nodeArray[rightNodeIndex] = new TreeNode(right);

	if (nodeArray[rightNodeIndex]->leftChild != nullptr)
	{
		nodeArray[rightNodeIndex]->leftChild->parent = nodeArray[rightNodeIndex];
	}

	if (nodeArray[rightNodeIndex]->rightChild != nullptr)
	{
		nodeArray[rightNodeIndex]->rightChild->parent = nodeArray[rightNodeIndex];
	}

	Character empty;
	empty.character = 0;
	empty.occurances = (left.character.occurances + right.character.occurances);

	treeID++;
	TreeNode parent = { empty, treeID, "", nullptr, nodeArray[leftNodeIndex], nodeArray[rightNodeIndex] };
	return parent;
}

void HuffmanTree::preorder(TreeNode node)
{
	if (preorderFile.is_open())
	{
		if (node.character.character == 0)
		{
			preorderFile << "i " << node.id << "\n";
		}
		else
		{
			preorderFile << "s " << (int)node.character.character << "\n";
		}
	
		if (node.leftChild != nullptr)
		{
			preorder(*(node.leftChild));
		}
		if (node.rightChild != nullptr)
		{
			preorder(*(node.rightChild));
		}
		else
		{
			//preorderFile.flush();
			return;
		}
	}
	else
	{
		std::cout << "Preorder Fialed to Open\n";
	}
}

void HuffmanTree::inorder(TreeNode node)
{
	if (inorderFile.is_open())
	{
		if (node.leftChild != nullptr)
		{
			inorder(*(node.leftChild));
		}

		if (node.character.character == 0)
		{
			inorderFile << "i " << node.id << "\n";
		}
		else
		{
			inorderFile << "s " << (int)node.character.character << "\n";
		}

		if (node.rightChild != nullptr)
		{
			inorder(*(node.rightChild));
		}
		else
		{
			//inorderFile.flush();
			return;
		}
	}
	else
	{
		std::cout << "Inorder Fialed to Open\n";
	}
}

void HuffmanTree::encodeCharacters(TreeNode node)
{
	if ((node.parent == nullptr) && (node.encoding == ""))
	{
		if (node.leftChild != nullptr)
		{
			node.leftChild->encoding = "0";
			node.rightChild->encoding = "1";
			encodeCharacters(*(node.leftChild));
			encodeCharacters(*(node.rightChild));
		}
		else
		{
			node.encoding = "0";
		}
	}
	else
	{
		if (node.leftChild != nullptr)
		{
			node.leftChild->encoding = node.encoding + "0";
			encodeCharacters(*(node.leftChild));
		}

		if (node.rightChild != nullptr)
		{
			node.rightChild->encoding = node.encoding + "1";
			encodeCharacters(*(node.rightChild));
		}
	}
}

std::string HuffmanTree::encodeMessage(std::string message)
{
	std::string encodedMessage = "";

	for (char ch : message)
	{
		for (int i = 0; i < nodes; i++)
		{
			if (ch == nodeArray[i]->character.character)
			{
				encodedMessage += nodeArray[i]->encoding;
				break;
			}
		}
	}

	return encodedMessage;
}
