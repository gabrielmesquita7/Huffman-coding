#ifndef TREE_HPP
#define TREE_HPP

#include <iostream>
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

typedef struct Tree Tree;
typedef struct Huffman Huffman;

struct Tree
{
	string data;
	float freq;
	Tree *esq, *dir, *prox;
};

struct Huffman
{
	Tree *inicio;
};

void CreateHuffman(Huffman *h);
void InsertData(Huffman *h, Tree *no);
Tree *removeTree(Huffman *h);
void PrintTree(Tree *no, int altura);
Tree *HuffmanTree(Huffman *h);

#endif
