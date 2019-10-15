#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
using namespace std;

struct Informacao{
	char* ordena;
	char* media;
};

int particiona(Informacao *info, int beg, int end, int pivo) {
	char valorPivo[100];
	strcpy(valorPivo, info[pivo].ordena);
	//colocamos o pivo temporariamente na ultima posição
	swap(info[end-1],info[pivo]);
	// ao acharmos um elemento menor do que o pivo, vamos coloca-lo
	// na posicao "pos"
	int pos = beg;
	for(int i = beg; i < end-1; i++) {
		if(strcmp(info[i].ordena, valorPivo) > 0){
			swap(info[pos], info[i]);
			pos++;
		}
	}
	//coloque o pivo depois do ultimo elemento menor que ele
	swap(info[pos],info[end-1]);
	return pos;
}

void quickSort2(Informacao *info, int beg, int end) {
	if(beg == end)
		return;
	int pos = particiona(info, beg, end, beg);
	quickSort2(info, beg, pos);
	quickSort2(info, pos + 1, end);
}

void quickSort(Informacao *info, int tam) {
	quickSort2(info, 0, tam);
}

int main(int agrc, char **argv){

	int memoria = atoi(argv[2]), cOrd = 0, cMed = 0, k = 0;
	char * pOrd, *pMed, *token;
	string aux;
	char* elemento; 
	//char contArq = 33;

	ifstream fin(argv[1]);
	getline(fin, aux);
	char *cab = (char *)aux.c_str();


	pOrd = strstr(cab, argv[3]);
	pMed = strstr(cab, argv[4]);

	for(int i = 0; &cab[i] != pOrd; i++){
		if(cab[i] == ',')
			cOrd++;
	}

	for(int i = 0; &cab[i] != pMed; i++){
		if(cab[i] == ',')
			cMed++;
	}

	while(!fin.eof()){
		Informacao *informacao = new Informacao[memoria];
		
		for(int i = 0; i < memoria && !fin.eof();i++){
			getline(fin, aux);
			elemento = (char*)aux.c_str();

			token = strtok(elemento, ",");


			for(int j=0; token != NULL;j++){
				if(cOrd == j){
					k++;
					//informacao[i].ordena = token;
					informacao[i].ordena = new char[strlen(token)];
					strcpy(informacao[i].ordena, token);
				}else if(cMed == j){
					//informacao[i].media = token;
					informacao[i].media = new char[strlen(token)];
					strcpy(informacao[i].media, token);
				}
				token = strtok(NULL, ",");
			}
		}
		
		quickSort(informacao, k);
		for(int i=0;i<k;i++){
			cout<<informacao[i].ordena<<endl;
		}
		for(int i = 0; i < k; i++){
			delete[] informacao[i].ordena;
			delete[] informacao[i].media;
		}
		delete[] informacao;
		k=0;
	}

	//mergeSort(v, memoria);
	return 0;
}