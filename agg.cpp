/*
Desenvolvido por: 	Erick Lima Figueredo - 98898
					Sávio Mendes Miranda - 98886
					Yago Lopes Lamas	 - 98897
Disciplina: INF 112 - Giovanni Ventorim Comarela
*/

#include <cstdio>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <fstream>
using namespace std;

//Escopo do programa
struct Informacao{ char *ordena; char *media;};

//Prototipacao das funcoes
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

	//Abre o arquivo e armazena suas iformações em um vetor auxiliar
	ifstream fin(argv[1]);
	getline(fin, aux);


	//cab aponta para  aux
	char *cab = (char *)aux.c_str();
	
	pOrd = strstr(cab, argv[3]);//Verifica se argv[3] esta contido  em  "cab"
	pMed = strstr(cab, argv[4]);//Verifica se argv[4] esta contido  em  "cab"

	//Conta o número de vírgulas (colunas) de "pOrd"
	for (int i = 0; &cab[i] != pOrd; i++)
	{
		if (cab[i] == ',')
			cOrd++;
	}
	//Conta o número de vírgula (colunas) de "pMed"
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
			//Lê os dados de fin.
			getline(fin, aux);
			elemento = (char *)aux.c_str();
			
			//Quebra "aux" nas virgulas(separador de colunas).
			token = strtok(elemento, ",");

			for (int j = 0; token != NULL; j++)
			{
				if (cOrd == j)
				{
					linha++;

					//Aloca  ordena usando o número de colunas como parâmetro e copia as informações.
					informacao[i].ordena = new char[strlen(token) + 1];
					strcpy(informacao[i].ordena, token);
				}
				else if (cMed == j)
				{	
					//Aloca media usando o numero de colunas como parâmetro
					informacao[i].media = new char[strlen(token) + 1];
					strcpy(informacao[i].media, token);
				}
				token = strtok(NULL, ",");
			}
		}

		quickSort(informacao, linha);  //Ordena as iformações dentro do arquivi 
		sprintf(temp, "buffer%d.txt", cont++); //Cria arquivos temporarios que cabem na memória do computador
		ofstream fout(temp);
		//Preeche as informações nesses arquivos
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
	//deletaBuffers(cont);
	return 0;
}

void quickSort(Informacao *info, int tam)
{
	quickSort2(info, 0, tam);//Scopo da função
}
void quickSort2(Informacao *info, int beg, int end)
{
	if (beg == end)    //Verifica se terminou a função (fim = inicio).

		return;

	int pos = particiona(info, beg, end, beg);   //Divide os dados em 2 partes

	//chama a função para essas partes
	quickSort2(info, beg, pos);
	quickSort2(info, pos + 1, end);
}

int particiona(Informacao *info, int beg, int end, int pivo)
{
	char valorPivo[1000];
	strcpy(valorPivo, info[pivo].ordena);
	//colocamos o pivo temporariamente na ultima posição
	swap(info[end - 1], info[pivo]);
	/* ao acharmos um elemento menor do que o pivo, vamos coloca-lo
	na posicao "pos" */
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
	bool *zerouArquivo = (bool *)calloc(numArqs, sizeof(bool));
	char nomeArq[1000] = {' '};
	char *elemento, *to	ken, *resto;
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

		getline(repo[i], cadeiaAteVirg);
		elemento = (char *)cadeiaAteVirg.c_str();
	
		token  = strtok(elemento, ",");
		info[i].ordena = new char[strlen(token) + 1];
		strcpy(info[i].ordena, token);

		token = strtok(NULL, ";");

		info[i].media = new char[strlen(token) + 1];
		strcpy(info[i].media, token);
	}

	while (contNulo < numArqs)//Enquanto ouver arquivos
	{
		for (int i = 0; i < numArqs; i++)
			if (!zerouArquivo[i])//Verifica se zeraram os arquivos.
			{
				//Encontra a posição do menor arquivo.
				infoAux = info[i];
				posMenor = i;
				break;
			}

		for (int i = 0; i < numArqs; i++)
		
			//Verifica se esta ordenado ou terminou o arquivo
			if (strcmp(info[i].ordena, infoAux.ordena) < 0 && !zerouArquivo[i])
			{
				//Encontra a posição do memor arquivo.
				posMenor = i; 
				infoAux = info[i];
			}
		//Escreve a informação a ser ordenada e a media a ser calculada
		fout << infoAux.ordena << ',' << infoAux.media << ';' << endl;

		//Verifica se terminaram os arquivos
		if (repo[posMenor].peek() == -1)
		{
			contNulo++;
			zerouArquivo[posMenor] = true;
		}
		
		delete[] info[posMenor].ordena;
		delete[] info[posMenor].media;

		getline(repo[posMenor], cadeiaAteVirg);
		elemento = (char *)cadeiaAteVirg.c_str();
		
		token = strtok_r(elemento, ",", &resto);//Quebra a string nas ","

		//Aloca ordena com tamanho (posMenor) e recebe token.
		info[posMenor].ordena = new char[strlen(token) + 1];
		strcpy(info[posMenor].ordena, token);

		//Aloca media com tamanho (posMenor) e recebe resto.
		info[posMenor].media = new char[strlen(resto) + 1];
		strcpy(info[posMenor].media, resto);
	}
	fout.close();

	//Desaloca os vetores até então alocados
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
	char *chave, *elemento, *compara, *token;
	long double media = 0;
	int contMedia = 1;
	string aux;

	ifstream fin("final.txt");
	for (int i = 0; fin.peek() != -1; i++)
	{
		//O getline pega a linha toda, incluindo o \n
		getline(fin, aux);
		elemento = (char *)aux.c_str();//elemonto aponta para "aux"
		token = strtok(elemento, ",");//quebra a string nas virgulas
		chave = new char[strlen(token) + 1];//aloca a string
		strcpy(chave, token);//copia para a string "chave"
		token = strtok(NULL, ";");
		
		if (i == 0)
		{
			compara = new char[strlen(chave)+1];//aloca compara
			strcpy(compara, chave);//copia a string chave
			media = atof(token);//Descarta os espaços em branco e interpreta como numero os caracteres da string
		}
		else
		{
			if (strcmp(chave, compara) == 0)//verifica se são iguais
			{
				media += atof(token);
				contMedia++;
			}
			else
			{
				//Exibe o Item comparado e a média
				cout <<fixed << setprecision(50) <<compara << ',' << media / (long double)contMedia << endl;
				delete[] compara;//Desaloca "compara"
				compara = new char[strlen(chave)+1];//Aloca novamente pegando proximo caracter
				strcpy(compara, chave);
				media = atof(token);//converte para doble
				contMedia = 1;
			}
		}
		delete[] chave;
	}
	//Exibe a media
	cout << compara << ',' << media / (double)contMedia << endl;
	delete[]compara;
	fin.close();
}
void deletaBuffers(int numArqs)
{
	//Apaga os arquivos temporarios.
	char nomeArq[1000] = {' '};
	for (int i = 0; i < numArqs; i++)
	{
		sprintf(nomeArq, "buffer%d.txt", i);
		remove(nomeArq);
	}
}