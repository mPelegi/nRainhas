#include <iostream>
#include <stdlib.h>
#include <vector>
#include <algorithm> 

using namespace std;

vector<vector<int>> possibilidades; //"Matriz" onde as possibilidades serao armazenadas, o index corresponde a linha, e o valor a coluna
vector<vector<int>> tabuleiro;
int n = 0;                          //Input do usuario para definir o tamanho do tabuleiro e a quantidade de rainhas

void printarPossibilidade(vector<int> possibilidade) { //Metodo para escrever na tela a possibilidade encontrada
    cout << "[ ";
    for (auto posicaoRainha : possibilidade) {
        cout << posicaoRainha << " ";
    }
    cout << "]" << endl;
}

void printarResultado() { //Metodo para escrever na tela o resultado do algoritmo, mostrando a quantidade de solucoes e o modelo do tabuleiro
    int possibilidadeCount = 0; //Controle do numero da possibilidade

    cout << endl;
    cout << "Quantidade de solucoes: " << possibilidades.size() << endl;

    for (auto possibilidade : possibilidades) { //Laco para percorrer as possibilidades encontradas
        possibilidadeCount++;
        cout << "Possibilidade " << possibilidadeCount << ": ";
        printarPossibilidade(possibilidade);
        cout << endl;

        for (auto posicaoRainha : possibilidade) { //Laco para percorrer a posicao de cada rainha em cada possibilidade
            for (int i = 0; i < n; i++) //Laco para escrever na tela o tabuleiro
            {
                if (i == posicaoRainha - 1) { //Se o valor de i corresponde a posicao de uma rainha, escreve "R", se nao escreve "-"
                    cout << " R ";
                    continue;
                }
                cout << " - ";
            }
            cout << endl;
        }
        cout << endl << endl;
    }
}

void criarTabuleiro(int n) { //Metodo para criar um tabuleiro (matriz) do tamanho informado pelo usuario
    tabuleiro = vector<vector<int>>(n, vector<int>(n, 0));
}

bool posicaoValida(int linha, int coluna) { //Metodo para verificar a validade de uma posicao
    int i, j;

    for (i = 0; i < coluna; i++) { //Verificar a esquerda da linha
        if (tabuleiro[linha][i]) {
            return false;
        }
    }

    for (i = linha, j = coluna; i >= 0 && j >= 0; i--, j--) { //Verificar a esquerda da diagonal superior
        if (tabuleiro[i][j]) {
            return false;
        }
    }

    for (i = linha, j = coluna; j >= 0 && i < n; i++, j--) { //Verificar a esquerda da diagonal inferior
        if (tabuleiro[i][j]) {
            return false;
        }
    }

    return true;
}

bool procurarPossibilidades(int coluna) { //Metodo para identificar as possibilidades
    if (coluna == n) { //Verificar se a coluna informada chegou no limite do tabuleiro
        vector<int> possibilidade;
        for (int i = 0; i < n; i++) { //Laco para percorrer as linhas do tabuleiro
            for (int j = 0; j < n; j++) { //Laco para percorrer as colunas do tabuleiro
                if (tabuleiro[i][j] == 1) //Verificar se a posicao no tabuleiro esta ocupada por uma rainha
                    possibilidade.push_back(j + 1); //Inserindo a posição da rainha no vetor de possibilidade
            }
        }
        possibilidades.push_back(possibilidade); //Inserindo o vetor da possibilidade na matriz de possibilidades
        return true; //Retorno do resultado final de uma possibilidade apos validacao, resolve todas chamadas recursivas dessa tentativa
    }

    bool possibilidadeValida = false;

    for (int i = 0; i < n; i++) { //Laco para percorrer as linhas do tabuleiro de acordo com o coluna informada
        if (posicaoValida(i, coluna)) { //Chamada do metodo para verificar se a combinacao da linha e coluna e valida de acordo com as verificacoes a esquerda
            tabuleiro[i][coluna] = 1; //Marca a combinacao de linha e coluna com uma possivel rainha

            possibilidadeValida = procurarPossibilidades(coluna + 1) || possibilidadeValida; //Recursividade para checar as possibilidades

            tabuleiro[i][coluna] = 0; //Se a possibilidade nao pode ser satisfeita, remove as rainhas das combinacoes definidas ate aqui
        }
    }

    return possibilidadeValida;
}

void nRainhas() {
    possibilidades.clear();

    cout << "Problema das N-Rainhas" << endl;
    cout << "Informe o valor de N: ";
    cin >> n;

    if (n <= 0 || n == 2 || n == 3) { //Verificacoes de casos especificos onde nao sera possivel encontrar solucoes
        cout << "Nao existem solucoes possiveis para N = " << n << "!" << endl << endl;
        return;
    };

    criarTabuleiro(n);

    if (procurarPossibilidades(0) == false) { //Caso nao exista solucoes para algum valor de N qualquer
        cout << "Nao existem solucoes possiveis para N = " << n << "!" << endl << endl;
        return;
    }

    sort(possibilidades.begin(), possibilidades.end());
    printarResultado(); //Escreve na tela o resultado final do desafio para o N informado, incluindo cada uma das solucoes, se houver
}

int main()
{
    nRainhas(); //Inicio do desafio
    system("pause");
    return 0;
}

