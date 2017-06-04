#include "BaseDeConocimiento.h"
#include "Regla.h"
#include <algorithm>

BaseDeConocimiento::BaseDeConocimiento() { }

BaseDeConocimiento::~BaseDeConocimiento() { }

void BaseDeConocimiento::agregarRegla(Regla *regla)
{
	reglas.push_back(regla);
}

Regla* BaseDeConocimiento::obtenerRegla(int &x)
{
	Regla *regla = reglas[x];
	return regla;
}

int BaseDeConocimiento::getNumeroReglas()
{
	return reglas.size();
}

int BaseDeConocimiento::getReglasMarcadas()
{
	return reglasMarcadas;
}

void BaseDeConocimiento::setReglasMarcadas(int numReglas)
{
	reglasMarcadas = numReglas;
}

static bool comparator(const Regla *r1, const Regla* r2) {
	Regla *re1 = new Regla(r1->getCabeza(), r1->getCuerpo());
	Regla *re2 = new Regla(r2->getCabeza(), r2->getCuerpo());
	size_t largo1 = 0;
	size_t largo2 = 0;
	if (re1 != nullptr)
		largo1 = re1->getCuerpo().size();
	if (re2 != nullptr)
		largo2 = re2->getCuerpo().size();
	return largo1 < largo2;
}

void BaseDeConocimiento::ordenarMenorAMayor()
{
	std::make_heap(reglas.begin(), reglas.end(), comparator);
	std::sort_heap(reglas.begin(), reglas.end(), comparator);
}

string BaseDeConocimiento::ToString()
{
	string texto = "\nNumero de reglas: " + to_string(reglas.size()) + "\n";
	int tam = reglas.size();
	for (int i = 0; i < tam; i++)
	{
		string cuerpo = "";
		Regla *regla = reglas[i];
		texto += regla->ToString() + "\n";
		for (unsigned int y = 0; y < regla->getCuerpo().size(); y++) {
			cuerpo += regla->getCuerpo().at(y)->getArgumento().at(0).ToString() + ", ";
		}
		string marcada = "true ";
		if (regla->getMarcada() == false) {
			marcada = "false ";
		}
		texto = texto + "Marcada: " + marcada + "\t" + regla->getCabeza()->getRelacion() + "(" + regla->getCabeza()->getArgumento().at(0).ToString() + ") :- " + cuerpo + "\n";
	}
	return texto;
}
