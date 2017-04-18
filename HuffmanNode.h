#pragma once
#include <cstddef> //NULL definition

class HuffmanNode
{
private:
	unsigned char byte;
	HuffmanNode *leftChildPtr, *rightChildPtr;
	HuffmanNode(const unsigned char _symb = '\0') : byte(_symb), leftChildPtr(NULL), rightChildPtr(NULL) {};
	HuffmanNode(const unsigned char _symb, HuffmanNode* leftPtr, HuffmanNode* rightPtr) : byte(_symb), leftChildPtr(leftPtr), rightChildPtr(rightPtr) {};
	friend class HuffmanTree;
};