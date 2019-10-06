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
	int memoria, linhas, numParametros = 1;
	string cabecalho;
	
	//Abre o arquivo passado pelo terminal
	ifstream fin(argv[1]);   							        
	
	//Copia a primeira linha dele para uma string
	getline(fin, cabecalho);			

	//Cria um vetor de char com o comprimento da string+1 ('\0')				 	   
	char *linhaPtr = new char[cabecalho.length()+1];		

	//Copia o conteudo da string para o vetor   
	strcpy(linhaPtr, cabecalho.c_str());		

	//Esse for conta quantas colunas de dados temos (numParametros)
	for(int i = 0; linhaPtr[i]!='\0'; i++)
		if(linhaPtr[i] == ',')
			numParametros++;

	cout << numParametros << endl;		
	return 0;
}