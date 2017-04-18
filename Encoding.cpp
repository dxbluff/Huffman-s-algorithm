#include "HuffmanTree.h"
#include <iostream>
#include <string>
#include <map>
#include <fstream>

//КОДИРОВАНИЕ

int main()
{
	std::string input_name;
	std::cout << "Filename for encoding: ";
	std::cin >> input_name;
	std::ifstream input(input_name, std::ifstream::binary);
	if (!input.is_open())
	{
		std::cout << "Couldn't open " + input_name << std::endl;
		return 1;
	}
	input.seekg(0, input.end);
	long long input_size = input.tellg();
	input.seekg(0, input.beg);
	std::multimap<unsigned int, HuffmanTree*> freq; // <freq : char>
	{ //Подсчёт частот символов в тексте
		std::map<unsigned char, unsigned int> tmp_freq; // <char : freq>
		while (input.tellg() < input_size)
		{
			unsigned char tmp;
			input.read((char *)&tmp, sizeof(tmp));
			++tmp_freq[tmp];
		}
		for (auto &key_val : tmp_freq)
			freq.insert(std::pair<unsigned int, HuffmanTree*>(key_val.second, new HuffmanTree(key_val.first)));
	}
	std::ofstream output(input_name + ".huff", std::ofstream::binary);
	{ //Запись в output служебной информации для восстановления дерева Хаффмана
		unsigned short int counter = freq.size();
		output.write((char *)&counter, sizeof(counter));
		for (auto &freq_char_pair : freq)
		{
			unsigned char symbol = freq_char_pair.second->get_root_item();
			unsigned int symbol_freq = freq_char_pair.first;
			output.write((char *)&symbol_freq, sizeof(symbol_freq));
			output.write((char *)&symbol, sizeof(symbol));
		}
	}
	while (freq.size() > 1) //Построение дерева хаффмана
	{
		std::pair<unsigned int, HuffmanTree*> last(freq.begin()->first, freq.begin()->second);
		freq.erase(freq.begin());
		std::pair<unsigned int, HuffmanTree*> prelast(freq.begin()->first, freq.begin()->second);
		freq.erase(freq.begin());
		freq.insert(std::pair<unsigned int, HuffmanTree*>(last.first + prelast.first, new HuffmanTree(*(last.second), *(prelast.second))));
	}
	std::map<unsigned char, std::string> HuffmanTable = freq.begin()->second->get_encoding_table(); //Получение таблицы <символ : код>
	std::string output_bits = "";
	input.seekg(0, input.beg);
	while (input.tellg() < input_size)
	{
		unsigned char tmp;
		input.read((char *)&tmp, sizeof(tmp));
		output_bits += HuffmanTable[tmp];
		while (output_bits.length() > 7u)
		{
			unsigned char tmp = 0u;
			for (unsigned char i = 0u; i < 8u; ++i)
				if (output_bits[i] == '1')
					tmp |= 1u << (7u - i);
			output_bits.erase(0, 8);
			output.write((char *)&tmp, sizeof(tmp));
		}
	}
	if (!output_bits.empty())
	{
		unsigned char tmp = 0u;
		for (unsigned char i = 0u; i < output_bits.length(); ++i)
			if (output_bits[i] == '1')
				tmp |= 1u << (7u - i);
		output.write((char *)&tmp, sizeof(tmp));
	}
	long long output_size = output.tellp();
	std::cout << input_name << ": " << input_size << " bytes\n" << (input_name + ".huff") << ": " << output_size << " bytes\n" <<
		"Compression efficiency: " << ((float)input_size / output_size * 100) << "%\n";
	input.close();
	output.close();
	return 0;
}