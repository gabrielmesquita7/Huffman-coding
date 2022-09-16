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

typedef struct Record Record;
typedef struct Tree Tree;

struct Record
{
	int key;
	int value;
};

struct Tree
{
	Record reg;
	Tree *esq, *dir;
};

Tree *CreateTree();
bool TVazia(Tree **t);
void insertTree(Tree **t, Record r);
void pesquisa(Tree **t, Tree **aux, Record r);
int isInTree(Tree *t, Record r);

void removeTree(Tree **t, Record r);
void antecessor(Tree **t, Tree *aux);

void preordem(Tree *t);
void central(Tree *t);
void posordem(Tree *t);

#endif
