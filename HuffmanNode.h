#pragma once

class HuffmanNode
{
private:
	unsigned char byte;
	HuffmanNode *leftChildPtr, *rightChildPtr;
	HuffmanNode(const unsigned char _symb = '\0');
	HuffmanNode(const unsigned char _symb, HuffmanNode * leftPtr, HuffmanNode * rightPtr);
	friend class HuffmanTree;
};