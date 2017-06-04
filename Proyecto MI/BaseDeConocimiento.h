#ifndef BASEDECONOCIMIENTO_H
#define BASEDECONOCIMIENTO_H

#include <list>
#include <string>
#include "Regla.h"

class BaseDeConocimiento {

public:
	BaseDeConocimiento();
	~BaseDeConocimiento();
	void agregarRegla(Regla *regla);
	Regla* obtenerRegla(int &x);
	int getNumeroReglas();
	int getReglasMarcadas();
	void setReglasMarcadas(int numReglas);
	void ordenarMenorAMayor();
	string ToString();

private:
	vector<Regla*> reglas;
	int reglasMarcadas = 0;
};
#endif // !BASEDECONOCIMIENTO_H