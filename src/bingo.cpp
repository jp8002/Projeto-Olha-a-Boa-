#include <iostream>
#include <time.h>
using namespace std;

struct Numero
	{
		int num;
		bool check;
};
	
struct Cartela{
		Numero numeros[5][5];
		Cartela *nextNo;
		int acertos = 0;
		int colunas[5] = {-1,-1,-1,-1,-1};
		int linhas[5] = {-1,-1,-1,-1,-1};
		int linhas_saidas = 0;
		int colunas_saidas = 0;
		string letras[5] = {"B","I","N","G","O"};
};
struct Bingo{
		Cartela *noIn = new Cartela;
		
};

struct procura_return{
	bool achado;
	int posicao;

};

void preencher_cartela(Bingo *);

void mostrar_cartela(Cartela cartela);

bool procura(Bingo *, int );

void procura_teste(Bingo *, int, int *);

void sortear(Bingo *);

bool checar(Bingo *, int);

void checar_linhas(Cartela *);

void checar_colunas(Cartela *);

bool in(int[], int posicao);


int main(){
	Bingo bingo; // CRiação do objeto bingo

	preencher_cartela(&bingo);
	mostrar_cartela(*bingo.noIn);
	sortear(&bingo);
	mostrar_cartela(*bingo.noIn);
	cout << bingo.noIn->acertos;

	delete bingo.noIn;

}

void preencher_cartela(Bingo *bingo){
	int random , limite = 15, minimo = 1, teste , i=0, j=0;
	int lista[5]; 
	srand (time(NULL)); // Gegração da semente randomica

	// Laço de repetição responsável por gerar os Números e preencher a a cartela

	for ( i = 0; i < 5; ++i)
	{
		
		j = 0;
		while( j < 5){
			random = minimo + (rand() % (limite - minimo) + 1);
			if(procura(bingo, random) == true){
				continue;
			}

			if (i == 2 && j == 2) {
				bingo->noIn->numeros[j][i].num = 0;
				bingo->noIn->numeros[j][i].check = true;
				j++;
				continue;
			}

			
			bingo->noIn->numeros[j][i].num = random;
			
			bingo->noIn->numeros[j][i].check = false;
			
			j++;
		}
		
		limite += 15;
		minimo += 15;
		
	}
}

bool procura(Bingo *bingo, int random){
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (random == bingo->noIn->numeros[i][j].num) {
				return true;
			}
		}
	}

	return false;
}

void procura_teste(Bingo *bingo, int random, int *posicao){
	int linhas = 0;

	for (int i = 0; i < 5; i++) {
		if (in(bingo->noIn->linhas, i)) {
			cout << "pula. linha " << i << endl;
			continue;
		}
		for (int j = 0; j < 5; j++) {
			if (random == bingo->noIn->numeros[i][j].num) {
				cout << i << "||" << j << endl;
				posicao[0] = i;
				posicao[1] = j;
			}
		}
	}

	if (linhas == 5) {
		cout << "LINHA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!"<< endl;
		mostrar_cartela(*bingo->noIn);
	}

	
	
}

void mostrar_cartela(Cartela cartela){
	string teste;
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

	
}


void sortear(Bingo *bingo){

	int random ;
	srand (time(NULL)); // Gegração da semente randomica
	int v[75];
	v[0] = 15000;

	
	for (int i = 0; i < 75; i++) {
		random = rand() % 75 + 1;
		for (int j = -1; j < i; j++) {
			if (random == v[j]) {
				i--;
				break;
			}
			v[i] = random;
		}

	}

	for (int i = 0; i < 75; i++)
	{
		cout << v[i] << " | ";
	}

	cout << endl;
	

	for (int i = 0; i < 75; i++)
	{
		if(checar(bingo, v[i])){
			break;
		}
		cout << "vezes " << i << endl;
		
	}
	

	

	
}

bool checar(Bingo *bingo ,int random){
	int posicao[2] = {-1,-1};
	procura_teste(bingo, random, posicao);

	

	if (posicao[0] != -1)
	{		
			cout << "alocar em " << posicao[0] << " && " << posicao[1] << endl;
			bingo->noIn->numeros[posicao[0]][posicao[1]].num = 99;
			bingo->noIn->numeros[posicao[0]][posicao[1]].check = true;
			bingo->noIn->acertos++;

	}

	if(bingo->noIn->acertos == 24){
		cout << "BINGO!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << endl;
		return true;
	}

	checar_linhas(bingo->noIn);
	checar_colunas(bingo->noIn);

	mostrar_cartela(*bingo->noIn);
	cout<< "<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<," <<bingo->noIn->acertos << endl;
	return false;


}

bool in(int lista[5], int posicao){
	for (int i = 0;  i < 5; i++) {
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
		if (in(cartela->linhas, i)) {
			continue;
		}

		for (int j = 0; j < 5; j++) {
			if (cartela->numeros[i][j].check == true){
				tempacertos++;
			}
		}

		if (tempacertos == 5) {
			int qtd = cartela->linhas_saidas;
			cout << qtd << "LINHA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! [ " << i + 1 << " ]" << endl;
			cartela->linhas[qtd] = i;
			cartela->linhas_saidas++;
		}
	}

}

void checar_colunas(Cartela *cartela){
	int tempacertos = 0;

	for (int i = 0; i < 5; i++) {
		tempacertos = 0;
		if (in(cartela->colunas, i)) {
			
			continue;
		}

		for (int j = 0; j < 5; j++) {
			if (cartela->numeros[j][i].check == true){
				tempacertos++;
			}
		}

		if (tempacertos == 5) {
			int qtd = cartela->colunas_saidas;
			cout << qtd << "COLUNA!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! [ " << cartela->letras[i] << " ]" << endl;
			cartela->colunas[qtd] = i;
			cartela->colunas_saidas++;
		}
	}

}