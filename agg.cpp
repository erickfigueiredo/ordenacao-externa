#include <iostream>
#include <fstream>
#include <cstdio>
#include <iomanip>
#include <cstring>
using namespace std;

struct Informacao
{
	char *ordena;
	char *media;
};

void agregaChaves(int totLinha);
void registraMenor(Informacao *info, bool zerouArquivo, int numArqs, ofstream &fout, int &posMenor);
void preencheVetorChar(Informacao *info, int pos, ifstream &fin);
int intercala(int numArqs, int memoria, int linha);
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
	int linhaFinal;
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
		linhaFinal = linha;
		linha = 0;
	}
	//Ordena de forma intercalada os dados dos arquivos temporarios

	agregaChaves(intercala(cont, memoria, linhaFinal));
	return 0;
}

void agregaChaves(int totLinhas)
{
	char *token, *chave, *elemento, *compara;
	double media = 0;
	int contMedia = 1;
	int contLinha = 1;
	string aux;

	ifstream ffin("final.txt");
	for (int i = 0; !ffin.eof() && contLinha != totLinhas; i++)
	{
		getline(ffin, aux);
		elemento = (char *)aux.c_str();
		token = strtok(elemento, ",");
		chave = new char[strlen(token) + 1];
		strcpy(chave, token);
		token = strtok(NULL, "\0,\n");
		if (i == 0)
		{
			compara = new char[strlen(chave) + 1];
			strcpy(compara, chave);
			media = atof(token);
		}
		else
		{
			if (strcmp(chave, compara) == 0)
			{
				media += atof(token);
				contMedia++;
				contLinha++;
			}
			else
			{
				cout << fixed << setprecision(6) << compara << ',' << media / (double)contMedia << endl;
				delete[] compara;
				compara = new char[strlen(chave)+1];
				strcpy(compara, chave);
				media = atof(token);
				contMedia = 1;
				contLinha++;
			}
		}
		
		delete[] chave;
	}
	cout << fixed << setprecision(6) << compara << ',' << media / (double)contMedia << endl;
}

void registraMenor(Informacao *info, bool zerouArquivo[], int numArqs, ofstream &fout, int &posMenor, int &contLinha)
{
	Informacao infoAux;
	int posNaoNula = 0;
	posMenor = 0;
	for (int i = 0; i < numArqs; i++)
		if (!zerouArquivo[i])
		{
			infoAux.ordena = info[i].ordena;
			infoAux.media = info[i].media;
			posNaoNula = i;
			break;
		}

	for (int i = posNaoNula; i < numArqs; i++)
		if (strcmp(infoAux.ordena, info[i].ordena) > 0 && zerouArquivo[i] != true)
		{
			posMenor = i;
			infoAux.ordena = info[i].ordena;
			infoAux.media = info[i].media;
		}
	fout << infoAux.ordena << ',' << infoAux.media << endl;
	contLinha++;
}

int intercala(int numArqs, int memoria, int linha)
{
	char nomeArq[1000] = {' '};
	char *elemento, *token;
	int contLinha = 0;
	bool zerouArquivo[numArqs];
	int posMenor;
	string aux;
	ifstream *repo = new ifstream[numArqs];
	Informacao *info = new Informacao[numArqs];

	ofstream fout("final.txt", ios::app);
	for (int i = 0; i < numArqs; i++)
	{
		zerouArquivo[i] = false;
	}
	for (int i = 0; i < numArqs; i++)
	{
		sprintf(nomeArq, "buffer%d.txt", i);
		repo[i] = ifstream(nomeArq);
		getline(repo[i], aux);
		elemento = (char *)aux.c_str();

		token = strtok(elemento, ",");

		info[i].ordena = new char[strlen(token) + 1];
		strcpy(info[i].ordena, token);
		token = strtok(NULL, "\0,\n");
		info[i].media = new char[strlen(token) + 1];
		strcpy(info[i].media, token);
	}
	for (int k = 0; contLinha < ((memoria * numArqs - (memoria - linha))); k++)
	{
		registraMenor(info, zerouArquivo, numArqs, fout, posMenor, contLinha);
		if (repo[posMenor].eof())
		{
			zerouArquivo[posMenor] = true;
		}
		else
		{
			getline(repo[posMenor], aux);
			elemento = (char *)aux.c_str();

			token = strtok(elemento, ",");
			delete[] info[posMenor].ordena;
			delete[] info[posMenor].media;
			info[posMenor].ordena = new char[strlen(token) + 1];
			strcpy(info[posMenor].ordena, token);
			token = strtok(NULL, "\0,\n");
			info[posMenor].media = new char[strlen(token) + 1];
			strcpy(info[posMenor].media, token);
		}
	}

	for (int i = 0; i < numArqs; i++)
	{
		delete[] info[i].ordena;
		delete[] info[i].media;
	}
	delete[] info;
	delete[] repo;

	return ((memoria * numArqs - (memoria - linha)));
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