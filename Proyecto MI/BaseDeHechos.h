#ifndef BASEDEHECHOS_H
#define BASEDEHECHOS_H

#include <string>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <map>
#include "Regla.h"
#include "Hecho.h"

using namespace std;

class BaseDeHechos {

private:
	map<Hecho*, int> hechos;

public:
	BaseDeHechos();
	~BaseDeHechos();
	void agregarHecho(Hecho *hecho);
	bool existeHecho(Hecho *hecho);
	int estadoHecho(Hecho *hecho);
	string hechosVerdaderos();
	string ToString();
};
#endif // BASEDEHECHOS_H
