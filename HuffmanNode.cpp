#include "HuffmanNode.h"
#include <cstddef>

HuffmanNode::HuffmanNode(const unsigned char _symb) : byte(_symb), leftChildPtr(NULL), rightChildPtr(NULL) {};

HuffmanNode::HuffmanNode(const unsigned char _symb, HuffmanNode* leftPtr, HuffmanNode* rightPtr) : byte(_symb), leftChildPtr(leftPtr), rightChildPtr(rightPtr) {};