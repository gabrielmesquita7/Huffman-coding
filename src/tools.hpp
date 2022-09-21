#ifndef TOOLS_HPP
#define TOOLS_HPP

#include "tree.hpp"

struct word_reader : ctype<char> // tokenizer
{
    word_reader(string const &delims) : ctype<char>(get_table(delims)) {}
    static ctype_base::mask const *get_table(string const &delims)
    {
        static vector<ctype_base::mask> rc(table_size, ctype_base::mask());

        for (char ch : delims)
            rc[ch] = ctype_base::space;
        return &rc[0];
    }
};

template <typename KeyType, typename ValueType> // max(RP)
pair<KeyType, ValueType> get_max(const map<KeyType, ValueType> &x)
{
    using pairtype = pair<KeyType, ValueType>;
    return *max_element(x.begin(), x.end(), [](const pairtype &p1, const pairtype &p2)
                        { return p1.second < p2.second; });
}

template <typename KeyType, typename ValueType> // min(RP)
pair<KeyType, ValueType> get_min(const map<KeyType, ValueType> &x)
{
    using pairtype = pair<KeyType, ValueType>;
    return *min_element(x.begin(), x.end(), [](const pairtype &p1, const pairtype &p2)
                        { return p1.second < p2.second; });
}

void normalize_recurrence(Huffman &h);
void BinarySequence(Tree *HuffmanTree, string Cod);
void BinaryEnconding();

#endif