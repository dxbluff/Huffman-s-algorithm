#include <iostream>
#include <string>
#include <sstream>
#include <map>
#include <fstream>
#include <bitset>
#include <cstdlib>
#include <ctime>
#include "HuffmanTree.h"

void gendata(std::string filename)
{
	std::srand(std::time(NULL));
	std::ofstream output(filename, std::ofstream::binary);
	for (unsigned int i = 1u; i; ++i)
	{
		int tmp = rand();
		output.write((char *)&tmp, sizeof(tmp));
	}
	output.close();
	return;
}

int main()
{
	gendata("input");
	std::ifstream input("input", std::ifstream::binary);
	input.seekg(0, input.end);
	long long input_size = input.tellg();
	input.seekg(0, input.beg);
	std::multimap<unsigned int, HuffmanTree*> freq;
	{
		std::map<unsigned char, unsigned int> tmp_freq;
		while (input.tellg() < input_size)
		{
			unsigned char tmp;
			input.read((char *)&tmp, sizeof(tmp));
			++tmp_freq[tmp];
		}
		for (auto &key_val : tmp_freq)
			freq.insert(std::pair<unsigned int, HuffmanTree*>(key_val.second, new HuffmanTree(key_val.first)));
	}
	for (auto &key_val : freq)
		std::cout << key_val.first << ": " << key_val.second->get_root_item() << std::endl;
	while (freq.size() > 1)
	{
		std::pair<unsigned int, HuffmanTree*> last(freq.begin()->first, freq.begin()->second);
		freq.erase(freq.begin());
		std::pair<unsigned int, HuffmanTree*> prelast(freq.begin()->first, freq.begin()->second);
		freq.erase(freq.begin());
		freq.insert(std::pair<unsigned int, HuffmanTree*>(last.first + prelast.first, new HuffmanTree(*(last.second), *(prelast.second))));
	}
	std::map<unsigned char, std::string> HuffmanTable = freq.begin()->second->get_encoding_table();
	std::cout << "========" << std::endl;
	for (auto &key_val : HuffmanTable)
		std::cout << key_val.first << ": " << key_val.second << std::endl;
	input.seekg(0, input.beg);
	std::string output_bits = "";
	while (input.tellg() < input_size)
	{
		unsigned char tmp;
		input.read((char *)&tmp, sizeof(tmp));
		output_bits += HuffmanTable[tmp];
	}
	std::istringstream output_bits_stream(output_bits);
	output_bits_stream.seekg(0, output_bits_stream.end);
	long long output_bits_stream_size = output_bits_stream.tellg();
	output_bits_stream.seekg(0, output_bits_stream.beg);
	std::ofstream output("output", std::ofstream::binary);
	while (output_bits_stream.tellg() < output_bits_stream_size)
	{
		unsigned char buff;
		output_bits_stream.read((char *)&buff, sizeof(buff));
		output.write((char *)&buff, sizeof(buff));
	}
	input.close();
	output.close();
	return 0;
}