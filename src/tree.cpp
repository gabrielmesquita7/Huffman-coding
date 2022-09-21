#include "tree.hpp"

void CreateHuffman(Huffman *h)
{
  h->inicio = NULL;
}

void InsertData(Huffman *h, Tree *no)
{
  Tree *aux;

  if (h->inicio == NULL)
  {
    h->inicio = no;
  }
  else if (no->freq < h->inicio->freq)
  {
    no->prox = h->inicio;
    h->inicio = no;
  }
  else
  {
    aux = h->inicio;
    while (aux->prox && aux->prox->freq <= no->freq)
    {
      aux = aux->prox;
    }
    no->prox = aux->prox;
    aux->prox = no;
  }
}

Tree *removeTree(Huffman *h)
{
  Tree *aux = NULL;

  aux = h->inicio;
  h->inicio = aux->prox;
  return aux;
}

void PrintTree(Tree *no, int altura)
{
  if (no != NULL)
  {
    int i = 0;
    while (i < altura)
    {
      cout << "|-> ";
      i++;
    }
    if (altura == 0)
    {
      cout << "Root: ";
    }

    cout << no->data << "::" << no->freq << endl;
    altura++;

    PrintTree(no->esq, altura);
    PrintTree(no->dir, altura);
  }
}

Tree *HuffmanTree(Huffman *h)
{
  Tree *node1 = new Tree;
  Tree *node2 = new Tree;

  Tree *aux;

  while (h->inicio->prox != NULL)
  {
    node1 = removeTree(h);
    node2 = removeTree(h);

    Tree *pai = new Tree;

    pai->data = '#';
    pai->freq = (node1->freq + node2->freq);
    pai->esq = node1;
    pai->dir = node2;

    aux = h->inicio;
    while (true)
    {
      if (aux == NULL)
      {
        h->inicio = pai;
        pai->prox = NULL;
        break;
      }
      else if (aux->prox == NULL)
      {
        pai->prox = aux->prox;
        aux->prox = pai;
        break;
      }
      else if (aux->prox->freq >= pai->freq)
      {
        pai->prox = aux->prox;
        aux->prox = pai;
        break;
      }
      aux = aux->prox;
    }
  }
  return h->inicio;
}