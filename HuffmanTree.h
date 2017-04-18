#pragma once
#include <cstddef> // NULL definition
#include <map> // for {[char] = code} table
#include <string>
#include <fstream>

class HuffmanNode
{
private:
	unsigned char byte;
	HuffmanNode *leftChildPtr, *rightChildPtr;
	HuffmanNode(const unsigned char _symb = '\0') : byte(_symb), leftChildPtr(NULL), rightChildPtr(NULL) {};
	HuffmanNode(const unsigned char _symb, HuffmanNode* leftPtr, HuffmanNode* rightPtr) : byte(_symb), leftChildPtr(leftPtr), rightChildPtr(rightPtr) {};
	friend class HuffmanTree;
};

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
	void restore_text(std::ifstream& input, const long long input_size, const std::string& output_name); //REWRITE
	char get_root_item() const;
};