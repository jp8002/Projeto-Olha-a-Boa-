//Sistema gerenciador de Cartelas de Bingo
//Versão Final
//Autor: João Pedro Pereira dos Santos

#include <cstddef>
#include <iostream>
#include <time.h>
#include <string>
#include <fstream>

using namespace std;

struct Acertos{
	int quantidade = 0;
	int acertados[24];
};


struct Numero
	{
		int num;
		bool check;
};
	
struct Cartela{
		int id;
		Acertos acertos;
		Numero numeros[5][5];
		Cartela *nextNo = NULL;
		int colunas[5] = {-1,-1,-1,-1,-1};
		int linhas[5] = {-1,-1,-1,-1,-1};
		int linhas_saidas = 0;
		int colunas_saidas = 0;
		string letras[5] = {"B","I","N","G","O"};
};
struct Bingo{
		Cartela *noIn = NULL;
		Cartela *NOfiM = NULL;
		int qtdSorteados = 0;
		int nCartelas;
		
};

void criar_cartelas(Bingo *);

void preencher_cartela(Cartela *, int);

void mostrar_cartela(Cartela , int);

void escrever_cartela(Cartela);

bool procura_repeticao(Cartela *, int );

void procura_sorteado(Cartela *, int, int *);

bool checar_sorteado(Cartela *, int, int);

void checar_linhas(Cartela *);

void checar_colunas(Cartela *);

void mostrar_sorteado(int[], Bingo *);

bool in(int[], int posicao, int);

void limpar();

void parar();

void bubblesort(int *, int);


int main(){
	int sorteado, saidos[75], escolha ;

	Bingo bingo; // CRiação do objeto bingo
	

	do {
		limpar();
		cout << "+---------- Gerenciador de Bingo ---------+" << endl;
		cout << "| 1 - Cadastrar Cartelas                  |" << endl;
		cout << "| 2 - Marcar número                       |" << endl;
		cout << "| 3 - Mostrar Cartelas                    |" << endl;
		cout << "| 4 - Mostrar Números sorteados           |" << endl;
		cout << "| 5 - SAIR                                |" << endl;
		cout << "+ Bingo Garantido em = " <<  75 - bingo.qtdSorteados  <<  "		  |" << endl;
		cout << "+-----------------------------------------+" << endl;

		cin >> escolha;
		
		switch(escolha){
			case 1:{
				if (bingo.noIn != NULL) {
					cout << "Espere o fim da rodada para criar novas cartelas" << endl;
					parar();
					break;
				}
				cout << "Quantas cartelas você vai querer ?" <<endl;
				cin >> bingo.nCartelas;

				for(int i = 0; i < bingo.nCartelas; i++){
					criar_cartelas(&bingo);
				}
			

				preencher_cartela(bingo.noIn, bingo.nCartelas);
				mostrar_cartela(*bingo.noIn,bingo.nCartelas);

				break;
			}

			case 2:{
				if (bingo.noIn == NULL) {
					cout << "Crie novas cartelas para começar." << endl;
					parar();
					break;
				}

				limpar();

				cout << "Qual foi o número sorteado?" << endl;
				
				cin >> sorteado;
				if (in(saidos, sorteado,bingo.qtdSorteados)) {
					cout << "Esse número já foi inserido" << endl;
					parar();
					break;
				}

				else if (sorteado == 0 || sorteado > 75) {
					cout << "Esse número não existe no bingo" << endl;
					parar();
					break;
				}
				
				saidos[bingo.qtdSorteados] = sorteado;
				bubblesort(saidos, bingo.qtdSorteados);
				bingo.qtdSorteados++;
				

				limpar();
				if(checar_sorteado(bingo.noIn, sorteado, bingo.nCartelas)){
					do {
						Cartela *temp = bingo.noIn->nextNo;
						delete bingo.noIn;
						bingo.noIn = temp;
						sorteado= 0;
						bingo.qtdSorteados = 0;
					}while (bingo.noIn != NULL);
				}
				break;
			}
			case 3:{
				if (bingo.noIn == NULL) {
					cout << "Crie novas cartelas para começar." << endl;
					parar();
					break;
				}
				limpar();
				mostrar_cartela(*bingo.noIn, bingo.nCartelas);
				parar();
				break;
			}

			case 4:{
				if (bingo.noIn == NULL) {
					cout << "Crie novas cartelas para começar." << endl;
					parar();
					break;
				}
				mostrar_sorteado(saidos, &bingo);
				parar();
				break;
			}

			case 5:{
				do {
						Cartela *temp = bingo.noIn->nextNo;
						delete bingo.noIn;
						bingo.noIn = temp;
						sorteado= 0;
						bingo.qtdSorteados = 0;
				}while (bingo.noIn != NULL);

				break;
			}

			default:
				cout << "Essa escolha não existe"<< endl;
				parar();
				break;
		}
		
	
	}while (escolha != 5);	

}

void criar_cartelas(Bingo *bingo){
	Cartela *tempCartela = new Cartela(); 
	if (bingo->noIn == NULL) {
		tempCartela->id = 1;
		
		bingo->noIn = tempCartela;
		bingo->NOfiM = tempCartela;
		
		return;
	}

	
	tempCartela->id = bingo->NOfiM->id+1;
	bingo->NOfiM->nextNo = tempCartela;
	bingo->NOfiM = tempCartela;
}

void preencher_cartela(Cartela *cartela, int max){
	if (max != 1) {
		preencher_cartela(cartela->nextNo, --max );
	}
	
	int random , limite = 15, minimo = 0, teste , i=0, j=0;
	int lista[5];
	struct timespec ts;
    timespec_get(&ts, TIME_UTC);
	srand (ts.tv_nsec); // Gegração da semente randomica

	// Laço de repetição responsável por gerar os Números e preencher a a cartela

	for ( i = 0; i < 5; ++i)
	{
		
		j = 0;
		while( j < 5){
			random = minimo + (rand() % (limite - minimo) + 1);
			if(procura_repeticao(cartela, random) == true){
				continue;
			}

			if (i == 2 && j == 2) {
				cartela->numeros[j][i].num = 0;
				cartela->numeros[j][i].check = true;
				j++;
				continue;
			}

			
			cartela->numeros[j][i].num = random;
			
			cartela->numeros[j][i].check = false;
			
			j++;

		}
		
		limite += 15;
		minimo += 15;
		
	}
	escrever_cartela(*cartela);
}

bool procura_repeticao(Cartela *cartela, int random){
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (random == cartela->numeros[i][j].num) {
				return true;
			}
		}
	}

	return false;
}



void mostrar_cartela(Cartela cartela, int max){
	if (max != 1) {
		mostrar_cartela(*cartela.nextNo, --max);
	}
	string teste;

	cout << "  -----Cartela " << cartela.id << "-----" << endl;
	for (int i = 0; i < 5; i++) {
		cout << " " << cartela.letras[i] << " | ";
	}

	cout << "\n";

	for (int i = 0; i < 5; ++i)
	{	
		for (int j = 0; j< 5; j++) {
			if (cartela.numeros[i][j].num < 10){
				cout << " ";
			}
			cout << cartela.numeros[i][j].num << " | " ;
		}
		
		
		cout << "\n";
	}
	cout << "\n";

	
}

void escrever_cartela(Cartela cartela){
	char numstr[50];
	sprintf(numstr, "%d", cartela.id);

	string txt, nome = "cartela";
	txt  = nome + numstr;

	ofstream outFile(txt);

	 if (!outFile) {
        cout << "Erro ao abrir o arquivo de saída." << endl;
    }

	
	for (int i = 0; i < 5; i++) {
		outFile << " " << cartela.letras[i] << " | ";
	}

	outFile << "\n";

	for (int i = 0; i < 5; ++i)
	{	
		for (int j = 0; j< 5; j++) {
			if (cartela.numeros[i][j].num < 10){
				outFile << " ";
			}
			outFile << cartela.numeros[i][j].num << " | " ;
		}
		
		
		outFile << "\n";
	}
	outFile << "\n";
	outFile.close();

}

bool checar_sorteado(Cartela *cartela ,int random, int max){
	if (max != 1) {
		if (checar_sorteado(cartela->nextNo, random, --max)){
			return true;
		}
	}
	int posicao[2] = {-1,-1};
	procura_sorteado(cartela, random, posicao);

	
	if (posicao[0] != -1)
	{		
			cout << "____________________________________________________________________________________________________________________________\n" << endl;
			cout << "O número "<< random << " foi encontrado na Cartela " << cartela->id << " na coluna " << cartela->letras[posicao[1]] << " e na linha " << posicao[0] + 1 << "\n"<< endl;
			mostrar_cartela(*cartela, 1);
			cartela->acertos.acertados[cartela->acertos.quantidade] = random;
			cartela->numeros[posicao[0]][posicao[1]].num = 99;
			cartela->numeros[posicao[0]][posicao[1]].check = true;
			cartela->acertos.quantidade++;
			parar();

	}

	checar_linhas(cartela);
	checar_colunas(cartela);

	if(cartela->acertos.quantidade == 23){
		limpar();
		cout << "OLHA A BOA !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!. NA cartela " << cartela->id << endl;
		mostrar_cartela(*cartela, 1);
		parar();
	}

	if(cartela->acertos.quantidade == 24){
		limpar();
		cout << "BINGO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!. NA cartela " << cartela->id << endl;
		mostrar_cartela(*cartela, 1);
		parar();
		return true;
	}

	return false;


}

void procura_sorteado(Cartela *cartela, int random, int *posicao){
	int linhas = 0;

	for (int i = 0; i < 5; i++) {
		if (in(cartela->linhas, i,5)) {
			continue;
		}
		for (int j = 0; j < 5; j++) {
			if (random == cartela->numeros[i][j].num) {
				posicao[0] = i;
				posicao[1] = j;
			}
		}
	}
	
}

bool in(int lista[], int posicao, int fim){
	for (int i = 0;  i < fim; i++) {
		if (lista[i] == posicao) {
			return true;
		}
	}
	return false;
}

void checar_linhas(Cartela *cartela){
	int tempacertos = 0;

	for (int i = 0; i < 5; i++) {
		tempacertos = 0;
		if (in(cartela->linhas, i,5)) {
			continue;
		}

		for (int j = 0; j < 5; j++) {
			if (cartela->numeros[i][j].check == true){
				tempacertos++;
			}
		}

		if (tempacertos == 5) {
			limpar();
			int qtd = cartela->linhas_saidas;
			cout << "LINHA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! [ " << i + 1 << " ]. NA cartela " << cartela->id  << endl;
			mostrar_cartela(*cartela, 1);
			cartela->linhas[qtd] = i;
			cartela->linhas_saidas++;
			parar();
		}
	}

}

void checar_colunas(Cartela *cartela){
	int tempacertos = 0;

	for (int i = 0; i < 5; i++) {
		tempacertos = 0;
		if (in(cartela->colunas, i,5)) {
			
			continue;
		}

		for (int j = 0; j < 5; j++) {
			if (cartela->numeros[j][i].check == true){
				tempacertos++;
			}
		}

		if (tempacertos == 5) {
			limpar();
			int qtd = cartela->colunas_saidas;
			cout << "COLUNA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! [ " << cartela->letras[i] << " ]. NA cartela " << cartela->id  << endl;
			mostrar_cartela(*cartela, 1);
			cartela->colunas[qtd] = i;
			cartela->colunas_saidas++;
			parar();
		}
	}

}

void mostrar_sorteado(int lista[], Bingo *bingo){
	Cartela *temp = bingo->noIn;

	for (int i = 0; i < bingo->nCartelas ; i++) {
		cout << "Caterla " << temp->id << " tem "<< temp->acertos.quantidade<<" sorteados : ";
		bubblesort(temp->acertos.acertados, temp->acertos.quantidade - 1);
		for (int j =0; j < temp->acertos.quantidade; j++) {
			cout << temp->acertos.acertados[j] << ",";
		}

		temp = temp->nextNo;
		cout << endl;
	}

	cout << "Número sorteados: ";
	for (int i = 0; i < bingo->qtdSorteados; i++) {
		cout << lista[i] << ",";
	}
	cout << endl;
}

void limpar(){
	#ifdef _WIN32
		system("cls");
	#else
		system("clear");
	#endif

}

void parar(){
	#ifdef _WIN32
		system("pause");
	
	#else
		system("read -rsp $'Press enter to continue...\n'");
	#endif
	
}

void bubblesort(int *lista, int qtd){
	bool troca = true;
	int temp, end = qtd;

	while (troca == true) {
		troca = false;
		for (int i = 0; i< end; i++) {
			if (lista[i] > lista[i+1]){
				temp = lista[i];
				lista[i] = lista[i+1];
				lista[i + 1] = temp;
				troca = true;
			}
		}

	}

}