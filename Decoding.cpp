#include "HuffmanTree.h"
#include <iostream>
#include <fstream>
#include <map>
#include <string>

int main()
{
	std::string input_name;
	std::cout << "Filename for decoding: ";
	std::cin >> input_name;
	std::ifstream input(input_name, std::ifstream::binary);
	input.seekg(0, input.end);
	long long input_size = input.tellg();
	input.seekg(0, input.beg);
	unsigned short int counter;
	input.read((char *)&counter, sizeof(counter));
	std::multimap<unsigned int, HuffmanTree*> freq;
	for (unsigned short int i = 0u; i < counter; ++i) //Считывание частот символов
	{
		unsigned int symbol_freq;
		input.read((char *)&symbol_freq, sizeof(symbol_freq));
		unsigned char symbol;
		input.read((char *)&symbol, sizeof(symbol));
		freq.insert(std::pair<unsigned int, HuffmanTree*>(symbol_freq, new HuffmanTree(symbol)));
	}
	while (freq.size() > 1) //Построение дерева хаффмана
	{
		std::pair<unsigned int, HuffmanTree*> last(freq.begin()->first, freq.begin()->second);
		freq.erase(freq.begin());
		std::pair<unsigned int, HuffmanTree*> prelast(freq.begin()->first, freq.begin()->second);
		freq.erase(freq.begin());
		freq.insert(std::pair<unsigned int, HuffmanTree*>(last.first + prelast.first, new HuffmanTree(*(last.second), *(prelast.second))));
	}
	//TODO: Восстановление текста по закодированному файлу и дереву Хаффмана
	freq.begin()->second->restore_text(input, input_size, input_name + ".decoded");
}