#ifndef HECHO_H
#define HECHO_H

#include <string>
#include <vector>
#include "Argumento.h"

using namespace std;

const int VERDADERO = 0;
const int FALSO = 1;
const int INDETERMINADO = 2;

class Hecho {

private:

	string relacion;
	vector<Argumento> argumentos;
	int estado;
	bool permanente = false;

public:
	Hecho();
	Hecho(string predicado, vector<Argumento> arg, int est);
	Hecho(string predicado, vector<Argumento> arg);
	Hecho(string predicado, Argumento arg, int est);
	Hecho(string predicado, Argumento arg);
	~Hecho();
	string getRelacion();
	void setRelacion(string rel);
	vector<Argumento> getArgumento();
	void setArgumento(vector<Argumento> arg);
	void setArgumento(Argumento arg);
	int getNumeroArgumentos();
	int getEstado();
	void setEstado(int est);
	string getEstadoTexto();
	bool getPermanente();
	void setPermanente(bool per);
	bool operator==(Hecho *h2);
	bool operator!=(Hecho *h2);
	bool Equals(Hecho *h1);
    int GetHashCode();
	string ToString();
	Hecho(const Hecho &h);
	Hecho& operator=(const Hecho &h);
};
#endif // HECHO_H