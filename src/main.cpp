#include "tools.hpp"

int main()
{
     Huffman h;
     Tree *finalTree = new Tree;

     CreateHuffman(&h);
     normalize_recurrence(h);

     finalTree = HuffmanTree(&h);
     // cout << "---- ARVORE DE HUFFMAN: ----" << endl;
     // PrintTree(finalTree, 0);
     BinarySequence(finalTree, "");
     BinaryEnconding();
     cout << "Documento comprimido com sucesso em \"compressed.bin\"" << endl;
     return 0;
}