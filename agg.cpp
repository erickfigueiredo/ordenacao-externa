/*
*Alunos:
*Erick Lima Figueiredo - 98898
*Savio Mendes Miranda - 98886
*Yago Lopes Lamas - 98897
*/

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cstring>

using namespace std;

bool comparaChar(int inicio, int fim, char v[], char palavra[]);
int extraiInt();
int ordenaString();
void intercalaArquivo();
void merge();
void mergeSort();


int main(int argc, char **argv)
{
	int memoria = atoi(argv[2]), linhas, numParametros = 1;
	string cabecalho;

	//Abre o arquivo passado pelo terminal
	ifstream fin(argv[1]);

	//Copia a primeira linha dele para uma string
	getline(fin, cabecalho);

	//Cria um vetor de char com o comprimento da string+1 ('\0')
	char *linhaPtr = new char[cabecalho.length() + 1];

	//Copia o conteudo da string para o vetor
	strcpy(linhaPtr, cabecalho.c_str());

	//Esse for conta quantas colunas de dados temos (numParametros)
	for(int i = 0; linhaPtr[i] != '\0'; i++)
		if(linhaPtr[i] == ',')
			numParametros++;

	//Ordenação extrena de 2 caminhos
	fstream arquivo0("arquivo0.txt");
	fstream arquivo1("arquivo1.txt");
	fstream arquivo2("arquivo2.txt");
	fstream arquivo3("arquivo3.txt");
	
	//Auxiliar para pegar o tamanho das linhas
	string *vet = new string[memoria];
	int *comprimento = new int[memoria];
	int maior = -1, arquivo = 0;

		//Ve qual a maior linha das que irao para a memoria
		for(int i = 0; i < memoria; i++)
		{
			getline(fin, vet[i]);
			comprimento[i] = vet[i].length();
			if(maior < comprimento[i])
			{
				maior = comprimento[i];
			}
		}

		//Copia os registros para um vetor de char para trabalharmos
		char **registros = new char*[memoria];

		for(int i = 0; i < memoria; i++)
		{
			registros[i] = new char[maior];
		}

		for(int i = 0; i < memoria; i++)
		{
			strcpy(registros[i], (vet[i]).c_str());
			cout << registros[i] << endl;
		}

		//Ordena esse vetor registros

		//Salva ele no primeiro arquivo (0)

		//Salva o vetor ordenado no dispositivo e passa para o proximo

	return 0;
}


