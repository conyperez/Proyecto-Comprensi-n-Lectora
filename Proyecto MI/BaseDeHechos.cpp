#include "BaseDeHechos.h"
#include "Hecho.h"

BaseDeHechos::BaseDeHechos()
{
	hechos = map<Hecho*, int>();
}

BaseDeHechos::~BaseDeHechos() { }

void BaseDeHechos::agregarHecho(Hecho *hecho)
{
	cout << "Agregando hecho: " + hecho->getArgumento().at(0).ToString() << endl;
	cout << "Estado del hecho: " + hecho->getEstadoTexto() << endl;
	if (this->existeHecho(hecho)) {
		if (this->estadoHecho(hecho) == FALSO &&
			hecho->getEstado() == VERDADERO) {
			hechos.erase(hecho);	// Remover elemento
			hechos.insert(pair<Hecho*, int>(hecho, hecho->getEstado()));
		}
	}
	else if (hecho->getEstado() != INDETERMINADO) {
		hechos.insert(pair<Hecho*, int>(hecho, hecho->getEstado()));
		cout << hecho->getEstado() << endl;
	} else {
		cout << "Error: Intento ingresar un hecho indeterminado" << endl;
	}
}

bool BaseDeHechos::existeHecho(Hecho *hecho)
{
	for (map<Hecho*, int>::iterator it = hechos.begin(); it != hechos.end(); it++) {
		Hecho *tmpHecho = it->first;
		if (tmpHecho->getArgumento().at(0).ToString() == hecho->getArgumento().at(0).ToString() && hecho->getRelacion() == tmpHecho->getRelacion()) {
			//cout << "Existe en la base de hechos " << hecho->getArgumento().at(0).ToString() << endl;
			return true;
		}
	}
	//cout << "No existe en la base de hechos " << hecho->getArgumento().at(0).ToString() << endl;
	return false;
}

int BaseDeHechos::estadoHecho(Hecho *hecho)
{
	int valor = -1;
	for (map<Hecho*, int>::iterator it = hechos.begin(); it != hechos.end(); it++) {
		Hecho *tmpHecho = it->first;
		if (tmpHecho->getArgumento().at(0).ToString() == hecho->getArgumento().at(0).ToString() && hecho->getRelacion() == tmpHecho->getRelacion()) {
			cout << "VALOR ESTADO: " << it->second << endl;
			valor = it->second;
		}
	}
	return valor;
}

string BaseDeHechos::hechosVerdaderos()
{
	string texto = "";
	for (map<Hecho*, int>::iterator it = hechos.begin(); it != hechos.end(); it++) {
		if (it->second == VERDADERO) {
			Hecho *hecho = it->first;
			texto = texto + hecho->getArgumento().at(0).ToString() + ", ";
		}
	}
	if (texto.length() > 0)
		texto = texto.substr(0, texto.length() - 2).replace(texto.begin(), texto.end(), "_", " ");
	return texto;
}

string BaseDeHechos::ToString()
{
	string texto = "Numero de hechos: " + to_string(hechos.size()) + "\n";
	for (map<Hecho*, int>::iterator it = hechos.begin(); it != hechos.end(); it++) {
		Hecho *hecho = it->first;
		texto = texto + hecho->getEstadoTexto() + "\t\t" + hecho->getArgumento().at(0).ToString() + "\n";
	}
	return texto;
}
