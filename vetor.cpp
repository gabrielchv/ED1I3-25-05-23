#include <iostream>
using namespace std;

#define MAX 30

struct Fila {
	int ini;
	int fim;
	int nos[MAX];
};

Fila* init() {
	Fila *f = new Fila;
	f->ini = 0;
	f->fim = 0;
	return f;
}

int isEmpty(Fila *f) {
	return (f->ini == f->fim);
}

int incrementa(int i) {
	return (i==MAX ? 0 : ++i);
}

int count(Fila *f) {
	int qtde = 0;
	int i = f->ini;
	while (i != f->fim) {
		qtde++;
		i = incrementa(i);
	}
	return qtde;
}

int enqueue(Fila *f, int v) {
	int podeEnfileirar = (incrementa(f->fim) != f->ini);
	if (podeEnfileirar) {
		f->nos[f->fim] = v;
		f->fim = incrementa(f->fim);
	}
    return podeEnfileirar;	
}

int dequeue(Fila *f) {
	int ret;
	if (isEmpty(f)) {
		ret = -1;
	}
	else {
		ret = f->nos[f->ini];
		f->ini = incrementa(f->ini);
	}
	return ret;
}

bool isBiggerThanLast(Fila *f, int v) {
    return f->nos[f->fim - 1] < v;
}

bool smallerFistItem(Fila *f1, Fila *f2) {
    if (isEmpty(f1)) return false;
    if (isEmpty(f2)) return true;
    return f1->nos[f1->ini] < f2->nos[f2->ini];
}

void addCrescent(Fila *filaPar, Fila *filaImpar) {
    int val;
	cout << "Digite um valor maior que o anterior: ";
    cin >> val;
    while (!isBiggerThanLast(filaPar, val) || !isBiggerThanLast(filaImpar, val)) {
        cout << "Digite novamente o valor: ";
        cin >> val;
    }
    val % 2 == 0 ? enqueue(filaPar, val) : enqueue(filaImpar, val);
}

int main(int argc, char** argv) {
	Fila *filaPar;
	Fila *filaImpar;
	filaPar = init();
	filaImpar = init();
	
	while ((count(filaPar) + count(filaImpar)) < MAX) {
	    addCrescent(filaPar, filaImpar);
	}
	
	while ((count(filaPar) + count(filaImpar)) > 0) {
	    if (smallerFistItem(filaPar, filaImpar)) {
	        cout << filaPar->nos[filaPar->ini] << endl;
	        dequeue(filaPar);
	    }
	    else {
	        cout << filaImpar->nos[filaImpar->ini] << endl;
	        dequeue(filaImpar);
	    }
	}
    
	return 0;
}
