#include "CharacterList.h"

CharacterList::CharacterList()
{
	uniqueCharcters = 0;
	arraySize = 1;
	treeDepth = 0;
	characterArray = new TreeNode* [1];
}

CharacterList::~CharacterList()
{
	delete[] characterArray;
}

void CharacterList::addCharcter(char ch)
{
	bool unique = true;

	for (int i = 0; i < uniqueCharcters; i++)
	{
		if (ch == characterArray[i]->character.character)
		{
			characterArray[i]->character.occurances++;
			unique = false;
			break;
		}
	}

	if (unique)
	{
		Character c;
		c.character = ch;
		c.occurances = 1;
		characterArray[uniqueCharcters++] = new TreeNode{ c, 0, "", nullptr, nullptr, nullptr };

		if (uniqueCharcters >= arraySize)
		{
			TreeNode** tmp = new TreeNode * [arraySize *= 2];
			for (int i = 0; i < uniqueCharcters; i++)
			{
				tmp[i] = characterArray[i];
			}

			characterArray = tmp;
			//if the unique characters start a new layer increase depth of tree
			if ((uniqueCharcters - 1) >= (twoToTheN(treeDepth + 1) - 1))//(2^n) - 1 = first node of depth n starting at 0
			{
				treeDepth++;
			}
		}
	}
}

void CharacterList::addNode(TreeNode node)
{
	characterArray[uniqueCharcters++] = new TreeNode(node);

	if (uniqueCharcters >= arraySize)
	{
		TreeNode** tmp = new TreeNode * [arraySize *= 2];
		for (int i = 0; i < uniqueCharcters; i++)
		{
			tmp[i] = characterArray[i];
		}

		characterArray = tmp;
		//if the unique characters start a new layer increase depth of tree
		if ((uniqueCharcters - 1) >= (twoToTheN(treeDepth + 1) - 1))//(2^n) - 1 = first node of depth n starting at 0
		{
			treeDepth++;
		}
	}
}

TreeNode CharacterList::extractMin()
{
	TreeNode tmp = *characterArray[0];
	
	delete characterArray[0];
	characterArray[0] = characterArray[--uniqueCharcters];
	reorder(0);

	if (uniqueCharcters < (arraySize / 4))
	{
		arraySize /= 2;
		TreeNode** tmp = new TreeNode * [arraySize];
		for (int i = 0; i < uniqueCharcters; i++)
		{
			tmp[i] = characterArray[i];
		}
		delete[] characterArray;
		characterArray = tmp;
	}

	return tmp;
}

void CharacterList::order()
{
	for (int layer = treeDepth - 1; layer >= 0; layer--)
	{
		for (int node = twoToTheN(layer) - 1; node <= (2 * twoToTheN(layer) - 2); node++)
		{
			reorder(node);
		}
	}
}

int CharacterList::getUniqueCharacters()
{
	return uniqueCharcters;
}

void CharacterList::reorder(int node)
{
	int tmpNode = node;
	int leftChild = 2 * node + 1;
	int rightChild = 2 * node + 2;

	while (leftChild < uniqueCharcters)
	{
		if (rightChild >= uniqueCharcters)
		{
			if (characterArray[leftChild]->character.occurances < characterArray[tmpNode]->character.occurances)
			{
				TreeNode* tmp = characterArray[leftChild];
				characterArray[leftChild] = characterArray[tmpNode];
				characterArray[tmpNode] = tmp;
				tmpNode = leftChild;
				leftChild = 2 * tmpNode + 1;
				rightChild = 2 * tmpNode + 2;
			}
			else
			{
				break;
			}
		}
		else if (characterArray[leftChild]->character.occurances <= characterArray[rightChild]->character.occurances)
		{
			if (characterArray[leftChild]->character.occurances < characterArray[tmpNode]->character.occurances)
			{
				TreeNode* tmp = characterArray[leftChild];
				characterArray[leftChild] = characterArray[tmpNode];
				characterArray[tmpNode] = tmp;
				tmpNode = leftChild;
				leftChild = 2 * tmpNode + 1;
				rightChild = 2 * tmpNode + 2;
			}
			else
			{
				break;
			}
		}
		else
		{
			if (characterArray[rightChild]->character.occurances < characterArray[tmpNode]->character.occurances)
			{
				TreeNode* tmp = characterArray[rightChild];
				characterArray[rightChild] = characterArray[tmpNode];
				characterArray[tmpNode] = tmp;
				tmpNode = rightChild;
				leftChild = 2 * tmpNode + 1;
				rightChild = 2 * tmpNode + 2;
			}
			else
			{
				break;
			}
		}
	}
}

int CharacterList::twoToTheN(int n)
{
	int out = 1;
	for (int i = 0; i < n; i++)
	{
		out *= 2;
	}

	return out;
}
