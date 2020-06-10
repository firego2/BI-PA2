#ifndef __PROGTEST__
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <climits>
#include <cassert>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <cstdint>
#include <map>
#include <vector>
#include <algorithm>
#include <set>
#include <queue>
using namespace std;
#endif /* __PROGTEST__ */

struct NODE
{
	char ch;
	bool l;
	NODE* leftChild;
	NODE* rightChild;
};

bool recursive_read_tree(ifstream& ifs, NODE* nodes, uint8_t* byte, int* shift, bool right)
{
	uint8_t temp = 0;
	uint8_t i_ch = 0;
	temp = *byte;
	temp <<= (*shift);
	temp >>= 7;
	if (temp == 1)
	{
		(*shift)++;
		if (((*shift) / 8) == 1) (*shift) = 0;
		i_ch = *byte;
		i_ch <<= (*shift);
		if (!(ifs.read((char*)byte, sizeof(uint8_t)))) return false;
		if ((*shift) == 0)
		{
			i_ch = *byte;
			if (!(ifs.read((char*)byte, sizeof(uint8_t)))) return false;
		}
		else
		{
			temp = *byte;
			temp >>= (8 - (*shift));
			i_ch += temp;
		}
		if (i_ch < 0 || i_ch > 127) return false;
		nodes->l = true;
		nodes->ch = static_cast<char>(i_ch);
		if (right) return true;
	}
	else
	{
		(*shift)++;
		if (((*shift) / 8) == 1)
		{
			(*shift) = 0;
			if (!(ifs.read((char*)byte, sizeof(uint8_t)))) return false;
		}
		NODE* lChild = new NODE;
		lChild->leftChild = NULL;
		lChild->rightChild = NULL;
		lChild->l = false;
		if (!recursive_read_tree(ifs, lChild, byte, shift, false)) return false;
		NODE* rChild = new NODE;
		rChild->leftChild = NULL;
		rChild->rightChild = NULL;
		rChild->l = false;
		if (!recursive_read_tree(ifs, rChild, byte, shift, true)) return false;
		nodes->leftChild = lChild;
		nodes->rightChild = rChild;
	}
	return true;
}



bool get_Bit(ifstream& ifs, uint8_t* bit, uint8_t* byte, int* shift)
{
	(*bit) = (*byte);
	(*bit) <<= (*shift);
	(*bit) >>= 7;
	(*shift)++;
	if ((*shift) / 8 == 1)
	{
		(*shift) = 0;
		if (!(ifs.read((char*)byte, sizeof(uint8_t)))) return false;
	}
	return true;
}

bool decode(ofstream& ofs, ifstream& ifs, NODE* nodes, uint8_t* byte, int* count, int* shift, bool& flag)
{
	NODE* act = nodes;
	uint8_t temp = 0;
	for (int i = 0; i < (*count); i++)
	{
		act = nodes;
		while (1)
		{
			if (act->l)
			{
				if (!ofs.write((const char*)&act->ch, sizeof(char))) return false;
				break;
			}
			if (!get_Bit(ifs, &temp, byte, shift))
			{
				if (i != ((*count) - 1)) return false;
				else if (*shift != 0)
				{
					return true;
				}
			}
			if (temp == 0) act = act->leftChild;
			else act = act->rightChild;
		}
	}
	return true;
}

bool get_Count(ifstream& ifs, int* shift, int* count, uint8_t* byte, bool& flag)
{

	uint8_t temp = 0;
	if (!get_Bit(ifs, &temp, byte, shift)) return false;
	if ((*shift) / 8 == 1)
	{
		(*shift) = 0;
		if (!(ifs.read((char*)byte, sizeof(uint8_t)))) return false;
	}
	if (temp == 1)
	{
		(*count) = 4096;
		return true;
	}
	else
	{
		flag = true;
		uint16_t count16 = 0;
		for (int i = 0; i < 12; i++)
		{
			if (!get_Bit(ifs, &temp, byte, shift)) return false;
			count16 <<= 1;
			count16 += temp;
			temp = 0;
		}
		(*count) = count16;
	}
	return true;
}

bool decompressFile(const char* inFileName, const char* outFileName)
{
	ifstream file;
	ofstream fout;
	NODE* nodes = new NODE;
	nodes->leftChild = NULL;
	nodes->rightChild = NULL;
	nodes->l = false;
	int count = 0;
	uint8_t byte = 0;
	int shift = 0;
	file.open(inFileName, ios_base::binary);
	fout.open(outFileName, ios_base::binary);
	if (!file.is_open() || !file)
	{
		fout.close();
		return false;
	}
	if (!(file.read((char*)&byte, sizeof(uint8_t))))
	{
		return false;
	}
	if (!recursive_read_tree(file, nodes, &byte, &shift, false))
	{
		file.close();
		fout.close();
		return false;
	}
	if (!fout.is_open() || !fout)
	{
		file.close();
		fout.close();
		return false;
	}
	bool flag = false;
	while (1)
	{
		if (!get_Count(file, &shift, &count, &byte, flag))
		{
			file.close();
			fout.close();
			return false;
		}
		if (count == 0) return true;
		if (!decode(fout, file, nodes, &byte, &count, &shift, flag)) {
			file.close();
			fout.close();
			return false;
		}
		count = 0;
		if (flag) break;
	}
	file.close();
	fout.close();
	return true;
}

bool compressFile(const char* inFileName, const char* outFileName)
{

	return false;
}
#ifndef __PROGTEST__
bool identicalFiles(const char* fileName1, const char* fileName2)
{
	return true;
}

int main(void)
{

	/*assert(decompressFile("tests/test0.huf", "tempfile"));
	assert(identicalFiles("tests/test0.orig", "tempfile"));

	assert(decompressFile("tests/test1.huf", "tempfile"));
	assert(identicalFiles("tests/test1.orig", "tempfile"));

	assert(decompressFile("tests/test2.huf", "tempfile"));
	assert(identicalFiles("tests/test2.orig", "tempfile"));

	assert(decompressFile("tests/test3.huf", "tempfile"));
	assert(identicalFiles("tests/test3.orig", "tempfile"));

	assert(decompressFile("tests/test4.huf", "tempfile"));
	assert(identicalFiles("tests/test4.orig", "tempfile"));

	assert(!decompressFile("tests/test5.huf", "tempfile"));*/


	/*assert(decompressFile("tests/extra0.huf", "tempfile"));
	assert(identicalFiles("tests/extra0.orig", "tempfile"));

	assert(decompressFile("tests/extra1.huf", "tempfile"));
	assert(identicalFiles("tests/extra1.orig", "tempfile"));

	assert(decompressFile("tests/extra2.huf", "tempfile"));
	assert(identicalFiles("tests/extra2.orig", "tempfile"));

	assert(decompressFile("tests/extra3.huf", "tempfile"));
	assert(identicalFiles("tests/extra3.orig", "tempfile"));

	assert(decompressFile("tests/extra4.huf", "tempfile"));
	assert(identicalFiles("tests/extra4.orig", "tempfile"));

	assert(decompressFile("tests/extra5.huf", "tempfile"));
	assert(identicalFiles("tests/extra5.orig", "tempfile"));

	assert(decompressFile("tests/extra6.huf", "tempfile"));
	assert(identicalFiles("tests/extra6.orig", "tempfile"));

	assert(decompressFile("tests/extra7.huf", "tempfile"));
	assert(identicalFiles("tests/extra7.orig", "tempfile"));

	assert(decompressFile("tests/extra8.huf", "tempfile"));
	assert(identicalFiles("tests/extra8.orig", "tempfile"));

	assert(decompressFile("tests/extra9.huf", "tempfile"));
	assert(identicalFiles("tests/extra9.orig", "tempfile"));*/

	return 0;
}
#endif /* __PROGTEST__ */
