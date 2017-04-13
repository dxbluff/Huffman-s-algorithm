#include "HuffmanTree.h"
#include <exception>

void HuffmanTree::attachLeftSubtree(HuffmanTree &leftSubtree)
{
	if (root->leftChildPtr)
		throw std::exception("HuffmanTree: the left subtree already exist");
	else
	{
		root->leftChildPtr = leftSubtree.root;
		capacity += leftSubtree.capacity;
		leftSubtree.root = NULL;
		leftSubtree.capacity = 0u;
		return;
	}
}

void HuffmanTree::attachRightSubtree(HuffmanTree &rightSubtree)
{
	if (root->rightChildPtr)
		throw std::exception("HuffmanTree: the right subtree already exist");
	else
	{
		root->rightChildPtr = rightSubtree.root;
		capacity += rightSubtree.capacity;
		rightSubtree.root = NULL;
		rightSubtree.capacity = 0u;
		return;
	}
}

void HuffmanTree::destroyTree(HuffmanNode*& nodePtr)
{
	if (nodePtr)
	{
		destroyTree(nodePtr->leftChildPtr);
		destroyTree(nodePtr->rightChildPtr);
		delete nodePtr;
		nodePtr = NULL;
		--capacity;
	}
	return;
}

void HuffmanTree::get_encoding_table_helper(HuffmanNode *nodePtr, std::string cur_way, std::map<unsigned char, std::string> &table) const
{
	if (nodePtr->leftChildPtr)
	{
		get_encoding_table_helper(nodePtr->leftChildPtr, cur_way + "0", table);
		get_encoding_table_helper(nodePtr->rightChildPtr, cur_way + "1", table);
	}
	else
		table[nodePtr->byte] = cur_way;
	return;
}

void HuffmanTree::copyTree(HuffmanNode* src_nodePtr, HuffmanNode*& nodePtr) const
{
	if (src_nodePtr)
	{
		nodePtr = new HuffmanNode(src_nodePtr->byte);
		copyTree(src_nodePtr->leftChildPtr, nodePtr->leftChildPtr);
		copyTree(src_nodePtr->rightChildPtr, nodePtr->rightChildPtr);
	}
	else
		nodePtr = NULL;
}

unsigned int HuffmanTree::size() const
{
	return capacity;
}

HuffmanTree::HuffmanTree() : root(NULL), capacity(0) {};

HuffmanTree::HuffmanTree(const HuffmanTree& src_tree)
{
	copyTree(src_tree.root, root); //from src_tree to *this
	capacity = src_tree.capacity;
}

HuffmanTree::HuffmanTree(const unsigned char _symb = '\0') : capacity(1)
{
	root = new HuffmanNode(_symb, NULL, NULL);
	if (!root)
		throw std::exception("HuffmanTree: cannot allocate memory");
}

HuffmanTree::HuffmanTree(const unsigned char _symb, HuffmanTree& leftSubtree, HuffmanTree& rightSubtree) : capacity(1)
{
	root = new HuffmanNode(_symb, NULL, NULL);
	if (root)
	{
		attachLeftSubtree(leftSubtree);
		attachRightSubtree(rightSubtree);
	}
	else
		throw std::exception("HuffmanTree: cannot allocate memory");
}

HuffmanTree::HuffmanTree(HuffmanTree &leftSubtree, HuffmanTree &rightSubtree) : capacity(1)
{
	root = new HuffmanNode;
	if (root)
	{
		attachLeftSubtree(leftSubtree);
		attachRightSubtree(rightSubtree);
	}
	else
		throw std::exception("HuffmanTree: cannot allocate memory");
}

HuffmanTree::~HuffmanTree()
{
	destroyTree(root);
}

std::map<unsigned char, std::string> HuffmanTree::get_encoding_table()
{
	std::map<unsigned char, std::string> HuffmanTable;
	get_encoding_table_helper(root, "", HuffmanTable);
	//destroyTree(root);
	return HuffmanTable;
}

char HuffmanTree::get_root_item() const
{
	if (root)
		return root->byte;
	else
		throw std::exception("HuffmanTree: root ptr is NULL");
}