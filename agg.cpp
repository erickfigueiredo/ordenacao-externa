/*
*Alunos:
*Erick Lima Figueiredo - 98898
*Savio Mendes Miranda - 98886
*Yago Lopes Lamas - 98897
*/

#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <string.h>

using namespace std;

int extraiInt();
int ordenaString();
bool comparaChar(int inicio, int fim, char v[], char palavra[]);
void intercalaArquivo();
void merge();
void mergeSort();


int main(int argc, char **argv)
{
	int memoria, linhas, inicio = 0, numParametros = 0,
	   	   	   	   	   	   	   	   posChave = 0, posMedia = 0;
	string firstLinha;
	
	ifstream fin(argv[1]);   							        //Abre o arquivo passado pelo terminal
	
	getline(fin, firstLinha);							 	   //Copia a primeira linha dele para uma string
	char *linhaPtr = new char[firstLinha.length()+1];		   //Cria um vetor de char com o comprimento da string+1 ('\0')
	strcpy(linhaPtr, firstLinha.c_str());					   //Copia o conteudo da string para o vetor
	
	for(int i = 0; linhaPtr[i]!='\0'; i++){					   //Esse for irá contar quantas colunas de dados temos (numParametros)			
	             									           //E qual a posição da coluna do C (posChave), com a qual devemos ordenar
		if(linhaPtr[i] == ','){								   //Calcula tambem a posição da coluna dos valores que será calculada a média (posMedia)
			numParametros++;
			if(comparaChar(inicio, i, linhaPtr, argv[3])){
				posChave = numParametros;
			}
			if(comparaChar(inicio, i, linhaPtr, argv[4])){
				posMedia = numParametros;
			}
			inicio = i+1;
		}
	}
	numParametros++;							//Como conta as , precisa somar 1
	if(posChave == 0){							//Se terminar com a posicao 0 quer dizer que é o ultimo parametro
		posChave = numParametros;
	}else if(posMedia == 0){
		posMedia = numParametros;
	}

	return 0;
}

bool comparaChar(int inicio, int fim, char v[], char palavra[]){
	int i;
	
	for(i = inicio; i < fim; i++){
		if(palavra[i-inicio] == '\0'){
			return false;
		}else if(v[i] != palavra[i-inicio]){
			return false;
		}
	}
	return true;
	
}
