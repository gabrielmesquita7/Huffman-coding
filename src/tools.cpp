#include "tools.hpp"

void normalize_recurrence()
{
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
        cout << "word: " << wit->first << "\t\t\t\t" << wit->second << endl;
    }
}