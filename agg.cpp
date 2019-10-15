#include <iostream>
#include <fstream>
#include <cstdio>
#include <cstring>
using namespace std;

struct Informacao
{
	char *ordena;
	char *media;
};

void registraMenor(Informacao *info, int numArqs, ofstream &fout);
void intercala(int numArqs);
int particiona(Informacao *info, int beg, int end, int pivo);
void quickSort2(Informacao *info, int beg, int end);
void quickSort(Informacao *info, int tam);

int main(int agrc, char **argv)
{
	char *pOrd, *pMed, *token, *elemento;
	//vetor que guarda o nome maximo do arquivo a ser criado
	char temp[1000] = {' '};
	int memoria = atoi(argv[2]), cOrd, cMed, linha, cont;
	cOrd = cMed = linha = cont = 0;
	string aux;

	ifstream fin(argv[1]);
	getline(fin, aux);
	char *cab = (char *)aux.c_str();

	pOrd = strstr(cab, argv[3]);
	pMed = strstr(cab, argv[4]);

	for (int i = 0; &cab[i] != pOrd; i++)
	{
		if (cab[i] == ',')
			cOrd++;
	}

	for (int i = 0; &cab[i] != pMed; i++)
	{
		if (cab[i] == ',')
			cMed++;
	}

	while (!fin.eof())
	{
		Informacao *informacao = new Informacao[memoria];

		for (int i = 0; i < memoria && !fin.eof(); i++)
		{
			getline(fin, aux);
			elemento = (char *)aux.c_str();

			token = strtok(elemento, ",");

			for (int j = 0; token != NULL; j++)
			{
				if (cOrd == j)
				{
					linha++;
					//informacao[i].ordena = token;
					informacao[i].ordena = new char[strlen(token) + 1];
					strcpy(informacao[i].ordena, token);
				}
				else if (cMed == j)
				{
					//informacao[i].media = token;
					informacao[i].media = new char[strlen(token) + 1];
					strcpy(informacao[i].media, token);
				}
				token = strtok(NULL, ",");
			}
		}

		quickSort(informacao, linha);
		sprintf(temp, "buffer%d.txt", cont++);
		ofstream fout(temp);
		for (int i = 0; i < linha; i++)
		{
			(i == linha - 1) ? fout << informacao[i].ordena << ',' << informacao[i].media : fout << informacao[i].ordena << ',' << informacao[i].media << endl;
		}

		for (int i = 0; i < linha; i++)
		{
			delete[] informacao[i].ordena;
			delete[] informacao[i].media;
		}
		delete[] informacao;
		linha = 0;
	}
	//Ordena de forma intercalada os dados dos arquivos temporarios
	intercala(cont);
	return 0;
}

void registraMenor(Informacao *info, int numArqs, ofstream &fout)
{
	Informacao infoAux;
	infoAux.ordena = info[0].ordena;
	infoAux.media = info[0].media;

	for (int i = 1; i < numArqs; i++)
		if (strcmp(infoAux.ordena, info[i].ordena) > 0)
		{
			infoAux.ordena = info[i].ordena;
			infoAux.media = info[i].media;
		}
	fout << infoAux.ordena << ',' << infoAux.media << endl;
}

void intercala(int numArqs)
{
	char nomeArq[1000] = {' '};
	char *elemento, *token;
	string aux;
	ifstream *repo = new ifstream[numArqs];
	Informacao *info = new Informacao[numArqs];

	ofstream fout("final.txt", ios::app);

	for (int j = 0; /*Alguma coisa*/; j++)
	{
		for (int i = 0; i < numArqs; i++)
		{
			sprintf(nomeArq, "buffer%d.txt", i);
			//cout << nomeArq << endl;
			repo[i] = ifstream(nomeArq);
			getline(repo[i], aux);
			elemento = (char *)aux.c_str();

			token = strtok(elemento, ",");

			info[i].ordena = new char[strlen(token) + 1];
			strcpy(info[i].ordena, token);
			token = strtok(NULL, "\0,\n");
			info[i].media = new char[strlen(token) + 1];
			strcpy(info[i].media, token);

			//cout << info[i].ordena << ' ' << info[i].media << endl;
		}
		registraMenor(info, numArqs, fout);
		
	}
	for (int i = 0; i < numArqs; i++)
	{
		delete[] info[i].ordena;
		delete[] info[i].media;
	}
	delete[] info;
	delete[] repo;
}

int particiona(Informacao *info, int beg, int end, int pivo)
{
	char valorPivo[100];
	strcpy(valorPivo, info[pivo].ordena);
	//colocamos o pivo temporariamente na ultima posição
	swap(info[end - 1], info[pivo]);
	// ao acharmos um elemento menor do que o pivo, vamos coloca-lo
	// na posicao "pos"
	int pos = beg;
	for (int i = beg; i < end - 1; i++)
	{
		if (strcmp(info[i].ordena, valorPivo) < 0)
		{
			swap(info[pos], info[i]);
			pos++;
		}
	}
	//coloque o pivo depois do ultimo elemento menor que ele
	swap(info[pos], info[end - 1]);
	return pos;
}

void quickSort2(Informacao *info, int beg, int end)
{
	if (beg == end)
		return;
	int pos = particiona(info, beg, end, beg);
	quickSort2(info, beg, pos);
	quickSort2(info, pos + 1, end);
}

void quickSort(Informacao *info, int tam)
{
	quickSort2(info, 0, tam);
}