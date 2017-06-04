#include "Hecho.h"
#include "Argumento.h"

Hecho::Hecho() { }

Hecho::Hecho(string predicado, vector<Argumento> arg, int est)
{
	relacion = predicado;
	argumentos = arg;
	estado = est;
}

Hecho::Hecho(string predicado, vector<Argumento> arg)
{
	relacion = predicado;
	argumentos = arg;
	estado = INDETERMINADO;
}

Hecho::Hecho(string predicado, Argumento arg, int est)
{
	relacion = predicado;
	argumentos.push_back(arg);
	estado = est;
}

Hecho::Hecho(string predicado, Argumento arg)
{
	relacion = predicado;
	argumentos.push_back(arg);
	estado = INDETERMINADO;
}

Hecho::~Hecho() { }

string Hecho::getRelacion()
{
	return relacion;
}

void Hecho::setRelacion(string rel)
{
	relacion = rel;
}

vector<Argumento> Hecho::getArgumento()
{
	return argumentos;
}

void Hecho::setArgumento(vector<Argumento> arg) {
	argumentos = arg;
}

void Hecho::setArgumento(Argumento arg) {
	argumentos.push_back(arg);
}

int Hecho::getNumeroArgumentos()
{
	if (argumentos.size() != 0)
		return argumentos.size();
	else
		return 0;
}

int Hecho::getEstado()
{
	return estado;
}

void Hecho::setEstado(int est)
{
	estado = est;
}

string Hecho::getEstadoTexto()
{
	if (this->estado == VERDADERO)
		return "Verdadero";
	else if (this->estado == FALSO)
		return "Falso";
	else
		return "Indeterminado";
}

bool Hecho::getPermanente()
{
	return permanente;
}

void Hecho::setPermanente(bool per)
{
	permanente = per;
}

bool Hecho::operator == (Hecho *h2)
{
	if (this == nullptr && h2 == nullptr)
		return true;
	else if ((this == nullptr && h2 != nullptr) || (this != nullptr && h2 == nullptr))
		return false;
	else if (this->getRelacion() == h2->getRelacion() && this->getNumeroArgumentos() == h2->getNumeroArgumentos()) {
		bool iguales = true;
		for (int x = 0; x < this->getNumeroArgumentos(); x++) {
			//Tienen el mismo numero de argumento por lo que el limite de x vale para los dos
			if (this->argumentos[x] != &h2->argumentos[x]) {
				iguales = false;
			}
		}
		return iguales;
	}
	return false;
}

bool Hecho::operator != (Hecho *h2)
{
	if (this == h2)
		return false;
	return true;
}

bool Hecho::Equals(Hecho *h1)
{
	if (this == h1)
		return true;
	return false;
}

string Hecho::ToString()
{
	string texto = "Hecho " + relacion + " con " + to_string(getNumeroArgumentos()) + " argumentos\n";
	for (int x = 0; x < getNumeroArgumentos(); x++) {
		texto += "\tArgumento " + to_string((x + 1)) + ": " + argumentos[x].ToString() + " \n";
	}
	return texto;
}

int Hecho::GetHashCode()
{
	int valor = std::stoi(getRelacion(), nullptr, 0); //stoi: transforma de string a int.
	for (unsigned int x = 0; x<argumentos.size(); x++)
	{
		valor += argumentos[x].GetHashCode();
	}
	return valor;
}

Hecho::Hecho(const Hecho &h) { }

Hecho &Hecho::operator=(const Hecho &h) { return *this; }