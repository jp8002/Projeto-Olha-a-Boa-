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
		int acertos;
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

int procura(Bingo *, int, int *);

void sortear(Bingo *);

void checar(Bingo *, int);



int main(){
	Bingo bingo; // CRiação do objeto bingo

	preencher_cartela(&bingo);
	mostrar_cartela(*bingo.noIn);
	sortear(&bingo);

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

void procura(Bingo *bingo, int random, int posicao){
	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (random == bingo->noIn->numeros[i][j].num) {

				return ;
			}
		}
	}

	return ;
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

	
	for (int i = 0; i < 75; i++) {
		random = rand() % 75 + 1;
		for (int j = 0; j < i; j++) {
			if (random == v[j]) {
				i--;
				break;
			}
			v[i] = random;
		}

		checar(bingo, random);
	}

	
}

void checar(Bingo *bingo ,int random){
	int posicao[2];
		
			
}