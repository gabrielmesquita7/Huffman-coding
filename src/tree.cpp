#include "tree.hpp"

Tree *CreateTree()
{
  return NULL;
}

bool TVazia(Tree **t)
{
  return *t == NULL;
}

void insertTree(Tree **t, Record r)
{

  if (TVazia(t))
  {
    *t = (Tree *)malloc(sizeof(Tree));
    (*t)->esq = NULL;
    (*t)->dir = NULL;
    (*t)->reg = r;
  }
  else
  {

    if (r.key < (*t)->reg.key)
    {
      insertTree(&(*t)->esq, r);
    }

    if (r.key > (*t)->reg.key)
    {
      insertTree(&(*t)->dir, r);
    }
  }
}

void pesquisa(Tree **t, Tree **aux, Record r)
{

  if (*t == NULL)
  {
    cout << "[ERROR]: Node not found!" << endl;
    return;
  }

  if ((*t)->reg.key > r.key)
  {
    pesquisa(&(*t)->esq, aux, r);
    return;
  }
  if ((*t)->reg.key < r.key)
  {
    pesquisa(&(*t)->dir, aux, r);
    return;
  }

  *aux = *t;
}

int isInTree(Tree *t, Record r)
{

  if (t == NULL)
  {
    return 0;
  }

  return t->reg.key == r.key || isInTree(t->esq, r) || isInTree(t->dir, r);
}

void antecessor(Tree **t, Tree *aux)
{

  if ((*t)->dir != NULL)
  {
    antecessor(&(*t)->dir, aux);
    return;
  }

  aux->reg = (*t)->reg;
  aux = *t;
  *t = (*t)->esq;
  free(aux);
}

void removeTree(Tree **t, Record r)
{
  Tree *aux;

  if (*t == NULL)
  {
    cout << "[ERROR]: Record not found!!!" << endl;
    return;
  }

  if (r.key < (*t)->reg.key)
  {
    removeTree(&(*t)->esq, r);
    return;
  }
  if (r.key > (*t)->reg.key)
  {
    removeTree(&(*t)->dir, r);
    return;
  }

  if ((*t)->dir == NULL)
  {
    aux = *t;
    *t = (*t)->esq;
    free(aux);
    return;
  }

  if ((*t)->esq != NULL)
  {
    antecessor(&(*t)->esq, *t);
    return;
  }

  aux = *t;
  *t = (*t)->dir;
  free(aux);
}

void preordem(Tree *t)
{
  if (!(t == NULL))
  {
    cout << "  " << t->reg.key;
    preordem(t->esq);
    preordem(t->dir);
  }
}

void central(Tree *t)
{
  if (!(t == NULL))
  {
    central(t->esq);
    cout << "  " << t->reg.key;
    central(t->dir);
  }
}

void posordem(Tree *t)
{
  if (!(t == NULL))
  {
    posordem(t->esq);
    posordem(t->dir);
    cout << "  " << t->reg.key;
  }
}