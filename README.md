<h1 align="center">Huffman Coding</h1>

<p style="font-size:120%;" align="center">
    <a href="#problema">Problema</a> -
    <a href="#desenvolvimento">Desenvolvimento</a> -
    <a href="#saida">Saida</a> -
    <a href="#resultado">Resultado</a> -
    <a href="#executar">Executar</a>

</p>

# Problema
### Elabore uma árvore binária que utilize o código de Huffman para comprimir arquivos. Para tanto, **(1)** contabilizar a recorrência de cada palavra (RP) no arquivo; **(2)** normalizar a contabilização entre 0 e 1 utilizando a formula -> *RP / (max(RP) - min(RP))*; **(3)** Montar a árvore com as regras apresentadas por Huffman; **(4)** Troque as palavras pela codificação binária (utilizar booleano para representar 0 e 1); **(5)** Salve o arquivo em formato binário e observe qual foi o ganho de espaço obtido.


# Desenvolvimento
## O problema foi desenvolvido da seguinte maneira:
### Tratamento das strings e contabilização da recorrência:
* Primeiro foi pensado em uma forma de tokenizar e contabilizar a recorrencia de cada palavra no arquivo **(RP)**, para tal foi utilizado uma struct que tokeniza o arquivo dada uma stringstream para armazenar as palavras e simbolos como delimitadores.


```cpp
struct word_reader : ctype<char> // tokenizer
{
    word_reader(string const &delims) : ctype<char>(get_table(delims)) {}
    ...
    stringstream ss(buffer);
            ss.imbue(locale(locale(), new word_reader(" ,.\n?!;\"")));
```
* Foi utilizado um vetor de strings para armazenar as stopwords que não entram na contabilização como orientado o professor.

```cpp
    vector<string> stopwords;
    stopwords.insert(stopwords.end(), "a");
    stopwords.insert(stopwords.end(), "e");
    stopwords.insert(stopwords.end(), "i");
    stopwords.insert(stopwords.end(), "o");
    stopwords.insert(stopwords.end(), "u");
    stopwords.insert(stopwords.end(), "é");
```

* Feito a leitura e o tratamento de strings do arquivo, é feito um loop até o final do arquivo para o armazenamento dos tokens em uma **map**, onde sua chave vai ser a palavra armazena e a frequencia contabilizada em **float** toda vez que a chave ser a mesma.

```cpp
    map<string, float> categories;
    while (file.good())
    {
    ...
    categories[word]++;
    }
```

* Por fim é feita a normalização da recorrência utilizando a formula *RP / (max(RP) - min(RP))* e armazenado no lugar da frequencia anterior.

```cpp
    auto max = get_max(categories);
    auto min = get_min(categories);

    for (map<string, float>::iterator wit = categories.begin(); wit != categories.end(); ++wit)
    {
        wit->second = wit->second / (max.second - min.second);
    }
```
### Criação da Arvore de Huffman:
* Foi utilizada as seguintes estruturas para melhor formular o código de Huffman, onde é preciso representar uma lista de árvores (chamado de floresta) e depois reduzido a uma árvore.
```cpp
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
```

* Resumidamente, as seguintes funções atuam para auxiliar uma espécie de lista dinâmica, porém uma **lista de árvores**, sendo assim toda função leva em consideração o filho esquerdo e direito, além do ponteiro proximo da lista.

* Dito isso, é necessário abordar somente os pontos importantes que levam em consideração as regras apresentadas por Huffman.

> ```cpp
> void InsertData(Huffman *h, Tree *no);
> ```
> A ordenação por recorrência é feita na hora da inserção para facilitar na hora da criação da Arvore final.

> ```cpp
> Tree *HuffmanTree(Huffman *h)
> ```
> A criação da arvore de huffman é feita em cima de lista de árvores previamente alocadas com seus valores sendo seu simbolo e sua frequência, para cada combinação de DUAS árvores é feita a exclusão das mesmas e alocadas como filhos de uma nova árvore que tem como frequencia a soma de seus novos filhos. É feito esse mesmo processo até que reste somente uma árvore.


### Transformar em código binário:

> ```cpp
> void BinarySequence(Tree *HuffmanTree, string Cod);
> ```
> A regra geral para formar os bits de uma palavra de código é, partindo da raiz, percorrer o caminho até a folha correspondente, de tal modo que, cada arco percorrido para a direita equivale, por exemplo, a um bit ’1’ na palavra de código e cada arco percorrido para a esquerda equivale a um bit ’0’. *Função recursiva*

![image](https://user-images.githubusercontent.com/55333375/191399844-096312d4-ea1b-4f0f-adbd-4482755f010f.png)


> ```cpp
> void BinaryEnconding();
> ```
> Por fim é feito o armazenamento do código binario de cada palavra em uma **única string** e depois utilizando a mesma string, é feito a leitura dos '0' e '1' para criar um vector de booleano, ou seja, para cada 0 é armazenado um *false* no vector e 1 ao contrário. Com isso, finalmente é escrito o vetor de booleano no arquivo **.bin** completando a **compressão** do arquivo original.




# Saida
### É esperado uma print da codificação binária do arquivo e a confirmação da compressão do arquivo

![Captura de tela de 2022-09-20 23-16-40](https://user-images.githubusercontent.com/55333375/191399307-fff14dc8-b7bc-4fe2-b739-f5105bcf91a1.png)


# Resultado
### Foi observado a seguinte diminuição do tamanho do arquivo em relação ao original: *625 bytes* *->* *348 bytes*, fazendo alguns cálculos foi constatado uma diminuição de *44,32%* do tamanho do arquivo.

> Calculo:
> 
![Captura de tela de 2022-09-20 23-18-14](https://user-images.githubusercontent.com/55333375/191399467-6b4f34eb-938f-4a03-9fdb-94d561883e31.png)

# Executar
* Como executar:

<html>
<table>
    <tr>
        <td><code>make clean</code></td>
    <tr>
        <td><code>make</code></td>
    </tr>
    <tr>
        <td><code>make run</code></td>
    </tr>
    <tr>
</table>
</html>
