#include "HuffmanTree.h"
#include <exception>
#include <iostream>

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
		if (nodePtr->rightChildPtr) //Если есть оба потомка
		{
			get_encoding_table_helper(nodePtr->leftChildPtr, cur_way + "0", table);
			get_encoding_table_helper(nodePtr->rightChildPtr, cur_way + "1", table);
		}
		else //Если только левый потомок
		{
			std::string err_msg = "HuffmanTree: the tree is built incorrectly (one of the nodes has only 1 child)";
			throw std::exception(err_msg.c_str());
		}
	}
	else if (nodePtr->rightChildPtr) //Если только правый потомок
	{
		std::string err_msg = "HuffmanTree: the tree is built incorrectly (one of the nodes has only 1 child)";
		throw std::exception(err_msg.c_str());
	}
	else //Если нет потомков
	{
		table[nodePtr->byte] = cur_way;
	}
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

HuffmanTree::HuffmanTree(const HuffmanTree& src_tree) : capacity(src_tree.capacity)
{
	copyTree(src_tree.root, root); //from src_tree to *this
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
	if (!root)
		throw std::exception("HuffmanTree: root ptr is NULL");
	else if (!(root->leftChildPtr && root->rightChildPtr))
		throw std::exception("HuffmanTree: root ptr doesn't contain both children");
	std::map<unsigned char, std::string> HuffmanTable;
	get_encoding_table_helper(root, "", HuffmanTable);
	//destroyTree(root);
	return HuffmanTable;
}

char HuffmanTree::get_root_item() const
{
	if (root)
	{
		if (!(root->leftChildPtr || root->rightChildPtr))
			return root->byte;
		else
			throw std::exception("HuffmanTree: root ptr is service and doen't contain a symbol");
	}
	else
		throw std::exception("HuffmanTree: root ptr is NULL");
}

void HuffmanTree::restore_text(std::ifstream& input, const long long input_size, const std::string& output_name)
{
	if (!root)
		throw std::exception("HuffmanTree: root ptr is NULL");
	std::ofstream output(output_name, std::ofstream::binary);
	HuffmanNode *curPtr = root;
	while (input.tellg() < input_size)
	{
		unsigned char tmp;
		input.read((char *)&tmp, sizeof(tmp));
		for (unsigned char i = 0u; i < 8u; ++i)
		{
			if (tmp & (1u << 7u))
				curPtr = curPtr->rightChildPtr;
			else
				curPtr = curPtr->leftChildPtr;
			tmp <<= 1u;
			if (!curPtr->leftChildPtr)
			{
				unsigned char write_byte = curPtr->byte;
				output.write((char *)&write_byte, sizeof(write_byte));
				curPtr = root;
			}
		}
	}
	input.close();
	output.close();
}