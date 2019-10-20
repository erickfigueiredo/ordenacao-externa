/*
Desenvolvido por: 	Erick Lima Figueredo - 98898
					Sávio Mendes Miranda - 98886
					Yago Lopes Lamas - 98897

Disciplina: INF 112 - Giovanni Ventorim Comarela
*/

#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <fstream>
using namespace std;

struct Informacao{ char *ordena; char *media;};

void agregaChaves(int totLinhas);
void deletaBuffers(int numArqs);
void intercala(int numArqs, int memoria, int linha);
int particiona(Informacao *info, int beg, int end, int pivo);
void quickSort(Informacao *info, int tam);
void quickSort2(Informacao *info, int beg, int end);


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
			(i == linha - 1) ? fout << informacao[i].ordena << ',' << informacao[i].media << ';' : fout << informacao[i].ordena << ',' << informacao[i].media << ';' << endl;
		}
		fout.close();

		for (int i = 0; i < linha; i++)
		{
			delete[] informacao[i].ordena;
			delete[] informacao[i].media;
		}
		delete[] informacao;
		linha = 0;
	}
	fin.close();
	//Ordena de forma intercalada os dados dos arquivos temporarios
	intercala(cont, memoria, linha);
	deletaBuffers(cont);
	return 0;
}

void quickSort(Informacao *info, int tam)
{
	quickSort2(info, 0, tam);
}
void quickSort2(Informacao *info, int beg, int end)
{
	if (beg == end)
		return;
	int pos = particiona(info, beg, end, beg);
	quickSort2(info, beg, pos);
	quickSort2(info, pos + 1, end);
}

int particiona(Informacao *info, int beg, int end, int pivo)
{
	char valorPivo[1000];
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

void intercala(int numArqs, int memoria, int linha)
{
	Informacao infoAux;
	bool zerouArquivo[numArqs] = {false};
	char nomeArq[1000] = {' '};
	char *elemento;
	int contLinha, contNulo = 0, posMenor;
	contLinha = posMenor = 0;
	string cadeiaAteVirg;

	ifstream *repo = new ifstream[numArqs];
	Informacao *info = new Informacao[numArqs];

	ofstream fout("final.txt");

	//Preenchemos as posicoes do vetor de informacao com o menor elemento de cada struct
	for (int i = 0; i < numArqs; i++)
	{
		sprintf(nomeArq, "buffer%d.txt", i);
		repo[i] = ifstream(nomeArq);

		getline(repo[i], cadeiaAteVirg, ',');
		elemento = (char *)cadeiaAteVirg.c_str();

		info[i].ordena = new char[strlen(elemento) + 1];
		strcpy(info[i].ordena, elemento);

		getline(repo[i], cadeiaAteVirg, ';');
		elemento = (char *)cadeiaAteVirg.c_str();

		repo[i].ignore(1, '\n');

		info[i].media = new char[strlen(elemento) + 1];
		strcpy(info[i].media, elemento);
	}

	while (contNulo < numArqs)
	{
		for (int i = 0; i < numArqs; i++)
			if (!zerouArquivo[i])
			{
				infoAux = info[i];
				posMenor = i;
				break;
			}

		for (int i = 0; i < numArqs; i++)
			if (strcmp(info[i].ordena, infoAux.ordena) < 0 && !zerouArquivo[i])
			{
				posMenor = i;
				infoAux = info[i];
			}

		fout << infoAux.ordena << ',' << infoAux.media << ';' << endl;

		if (repo[posMenor].peek() == -1)
		{
			contNulo++;
			zerouArquivo[posMenor] = true;
		}

		delete[] info[posMenor].ordena;
		delete[] info[posMenor].media;

		getline(repo[posMenor], cadeiaAteVirg, ',');
		elemento = (char *)cadeiaAteVirg.c_str();

		info[posMenor].ordena = new char[strlen(elemento) + 1];
		strcpy(info[posMenor].ordena, elemento);

		getline(repo[posMenor], cadeiaAteVirg, ';');

		repo[posMenor].ignore(1, '\n');

		elemento = (char *)cadeiaAteVirg.c_str();

		info[posMenor].media = new char[strlen(elemento) + 1];
		strcpy(info[posMenor].media, elemento);
	}

	//Daqui pra baixo nao ha erros
	fout.close();
	for (int i = 0; i < numArqs; i++)
	{
		delete[] info[i].ordena;
		delete[] info[i].media;
		repo[i].close();
	}
	delete[] info;
	delete[] repo;
	agregaChaves(memoria * numArqs - memoria - linha);
}

void agregaChaves(int totLinhas)
{
	char *chave, *elemento, *compara;
	long double media = 0;
	int contMedia = 1;
	string aux;

	ifstream fin("final.txt");
	for (int i = 0; fin.peek() != -1; i++)
	{
		getline(fin, aux, ',');
		elemento = (char *)aux.c_str();

		chave = new char[strlen(elemento) + 1];
		strcpy(chave, elemento);

		getline(fin, aux, ';');
		elemento = (char *)aux.c_str();
		fin.ignore(1,'\n');
		if (i == 0)
		{
			compara = new char[strlen(chave)+1];
			strcpy(compara, chave);
			media = atof(elemento);
		}
		else
		{
			if (strcmp(chave, compara) == 0)
			{
				media += atof(elemento);
				contMedia++;
			}
			else
			{
				cout <<fixed << setprecision(50) <<compara << ',' << media / (long double)contMedia << endl;
				delete[] compara;
				compara = new char[strlen(chave)+1];
				strcpy(compara, chave);
				media = atof(elemento);
				contMedia = 1;
			}
		}
		delete[] chave;
	}
	cout << compara << ',' << media / (double)contMedia << endl;
	delete[]compara;
	fin.close();
}
void deletaBuffers(int numArqs)
{
	char nomeArq[1000] = {' '};
	for (int i = 0; i < numArqs; i++)
	{
		sprintf(nomeArq, "buffer%d.txt", i);
		remove(nomeArq);
	}
}
