#include "tools.hpp"

map<string, string> binarycods;

void normalize_recurrence(Huffman &h)
{
    Tree *no;
    bool stw;
    vector<string> stopwords;
    stopwords.insert(stopwords.end(), "a");
    stopwords.insert(stopwords.end(), "e");
    stopwords.insert(stopwords.end(), "i");
    stopwords.insert(stopwords.end(), "o");
    stopwords.insert(stopwords.end(), "u");
    stopwords.insert(stopwords.end(), "é");
    string word;
    ifstream file;
    file.open("doc.txt");
    if (file.is_open() == false)
    {
        cout << "Arquivo doc nao encontrado!" << endl;
        abort();
    }

    map<string, float> categories;
    while (file.good())
    {
        string buffer;
        while (getline(file, buffer))
        {
            stringstream ss(buffer);
            ss.imbue(locale(locale(), new word_reader(" ,.\n?!;\"")));
            while (ss >> word)
            {
                transform(word.begin(), word.end(), word.begin(), ::tolower); // transforma todas as palavras em lowercase para facilitar a contagem
                int res = 1;
                stw = false;
                for (auto &i : stopwords)
                {
                    res = i.compare(word);
                    if (res == 0)
                    {
                        stw = true;
                        break;
                    }
                }
                if (stw == false)
                {
                    categories[word]++;
                }
            }
        }
    }
    // NORMALIZACAO
    auto max = get_max(categories);
    auto min = get_min(categories);

    for (map<string, float>::iterator wit = categories.begin(); wit != categories.end(); ++wit)
    {
        wit->second = wit->second / (max.second - min.second);
    }

    for (map<string, float>::iterator wit = categories.begin(); wit != categories.end(); ++wit)
    {
        no = new Tree;
        no->data = wit->first;
        no->freq = wit->second;
        no->esq = NULL;
        no->dir = NULL;
        no->prox = NULL;
        InsertData(&h, no);
    }
}

void BinarySequence(Tree *HuffmanTree, string Cod)
{
    if (HuffmanTree->data != "#")
    {
        binarycods[HuffmanTree->data] = Cod;
    }
    if (HuffmanTree->esq != NULL)
    {
        BinarySequence(HuffmanTree->esq, Cod + '0');
    }
    if (HuffmanTree->dir != NULL)
    {
        BinarySequence(HuffmanTree->dir, Cod + '1');
    }
}

void BinaryEnconding()
{
    vector<bool> sequence;
    char Ctrue = '1';
    char Cfalse = '0';
    FILE *file;
    file = fopen("compressed.bin", "wb");
    if (!file)
    {
        cout << "Nao foi possivel abrir o arquivo comprimido! Saindo..." << endl;
        return;
    }
    string BinaryCode;
    for (map<string, string>::iterator wit = binarycods.begin(); wit != binarycods.end(); ++wit)
    {
        // cout << wit->first << "=>" << wit->second << endl; //print das palavras e seus respectivos codigos binarios
        BinaryCode += wit->second;
    }

    cout << "\n--- CODIFICACAO BINARIA DO ARQUIVO: ---\n"
         << endl;
    cout << BinaryCode << endl
         << endl;

    for (int i = 0; i < int(BinaryCode.length()); i++)
    {
        if (BinaryCode.at(i) == Ctrue)
        {
            sequence.push_back(true);
        }
        else if (BinaryCode.at(i) == Cfalse)
        {
            sequence.push_back(false);
        }
    }

    for (auto &&i : sequence)
    {
        bool aux = sequence[i];
        fwrite(&aux, sizeof(bool), 1, file);
    }
    sequence.clear();
    fclose(file);
}