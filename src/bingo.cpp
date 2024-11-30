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
		string colunas[5] = {"B","I","N","G","O"};
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
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (random == bingo->noIn->numeros[i][j].num) {
				cout << i << "||" << j << endl;
				posicao[0] = i;
				posicao[1] = j;
			}
		}
	}
	
}

void mostrar_cartela(Cartela cartela){
	for (int i = 0; i < 5; i++) {
		cout << " " << cartela.colunas[i] << " | ";
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

	if(bingo->noIn->acertos == 24){
		cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!BINGO" << endl;
		return true;
	}

	

	if (posicao[0] != -1)
	{		
			cout << "alocar em " << posicao[0] << " && " << posicao[1] << endl;
			bingo->noIn->numeros[posicao[0]][posicao[1]].num = -1;
			bingo->noIn->numeros[posicao[0]][posicao[1]].check = true;
			bingo->noIn->acertos++;

	}
	return false;
			
}