#pragma once
#include "HuffmanNode.h"
#include <map>
#include <string>

class HuffmanTree
{
private:
	HuffmanNode* root;
	unsigned int capacity;
	void attachLeftSubtree(HuffmanTree& leftSubtree);
	void attachRightSubtree(HuffmanTree& rightSubtree);
	void destroyTree(HuffmanNode*& nodePtr);
	void get_encoding_table_helper(HuffmanNode* nodePtr, std::string cur_way, std::map<unsigned char, std::string>& table) const;
	void copyTree(HuffmanNode* src_nodePtr, HuffmanNode*& nodePtr) const; //from src_nodePtr to nodePtr
public:
	unsigned int size() const;
	HuffmanTree();
	HuffmanTree(const HuffmanTree& src);
	HuffmanTree(const unsigned char _symb);
	HuffmanTree(const unsigned char _symb, HuffmanTree& leftSubtree, HuffmanTree& rightSubtree);
	HuffmanTree(HuffmanTree& leftSubtree, HuffmanTree& rightSubtree);
	~HuffmanTree();
	std::map<unsigned char, std::string> get_encoding_table();
	char get_root_item() const;
};