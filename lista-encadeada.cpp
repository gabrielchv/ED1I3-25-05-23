#include <iostream>
using namespace std;

#define MAX 30

struct No {
	int dado;
	struct No *prox;
};

struct Fila {
	No *ini;
	No *fim;
};

Fila* init() {
	Fila *f = new Fila;
	f->ini = NULL;
	f->fim = NULL;
	return f;
}

int isEmpty(Fila *f) {
	return (f->ini == NULL);
}

int count(Fila *f) {
	int qtde = 0;
	No *no;
	no = f->ini;
	while(no != NULL) {
		qtde++;
		no = no->prox;
	}
	return qtde;
}

void enqueue(Fila *f, int v) {
	No *no = new No;
	no->dado = v;
	no->prox = NULL;
	if (isEmpty(f)) {
	   f->ini = no;
	}
	else {
		f->fim->prox = no;
	}
	f->fim = no;
}

int dequeue(Fila *f) {
	int ret;
	if (isEmpty(f)) {
		ret = -1;
	}
	else {
		No *no = f->ini;
		ret = no->dado;
		f->ini = no->prox;
		if (f->ini == NULL) {
			f->fim = NULL;
		}
		free(no);
	}
	return ret;
}

bool isBiggerThanLast(Fila *f1, int v) {
    if (isEmpty(f1)) return true;
    return f1->ini->dado < v;
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

bool smallerFistItem(Fila *f1, Fila *f2) {
    if (isEmpty(f1)) return false;
    if (isEmpty(f2)) return true;
    return f1->ini->dado < f2->ini->dado;
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
	        cout << filaPar->ini->dado << endl;
	        dequeue(filaPar);
	    }
	    else {
	        cout << filaImpar->ini->dado << endl;
	        dequeue(filaImpar);
	    }
	}
	
	return 1;
}
