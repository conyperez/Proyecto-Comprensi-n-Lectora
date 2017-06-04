#include "Regla.h"
#include <string>

Regla::Regla(Hecho* head, vector<Hecho*> boddy)
{
	cabeza = new Hecho(head->getRelacion(), head->getArgumento());
	cuerpo = boddy;
}

Regla::Regla() { }

Regla::~Regla() { }

Hecho * Regla::getCabeza() const
{
	return cabeza;
}


void Regla::setCabeza(Hecho* head)
{
	cabeza = head;
}

vector<Hecho*> Regla::getCuerpo() const
{
	return cuerpo;
}

void Regla::setCuerpo(vector<Hecho*> boddy)
{
	cuerpo = boddy;
}

bool Regla::getMarcada()
{
	return marcada;
}

void Regla::setMarcada(bool marca)
{
	marcada = marca;
}

int Regla::getNumeroCondiciones()
{
	if (this->cabeza != nullptr)
		return cuerpo.size();
	else
		return 0;
}

int Regla::getHechosConfirmados()
{
	return hechosConfirmados;
}

void Regla::setHechosConfirmados(int confirmados)
{
	hechosConfirmados = confirmados;
}

double Regla::getPorcentajeHechosConfirmados()
{
	return (hechosConfirmados * 100.0) / getNumeroCondiciones();
}

bool Regla::operator == (Regla *r2)
{
	if (this == nullptr && r2 == nullptr)
		return true;
	else if ((this == nullptr && r2 != nullptr) || (this != nullptr && r2 == nullptr))
		return false;
	else if ((this->getCabeza() == r2->getCabeza()) && (this->getNumeroCondiciones() == r2->getNumeroCondiciones())) {
		bool iguales = true;
		for (int x = 0; x < this->getNumeroCondiciones(); x++) {
			//Tienen el mismo numero de condiciones por lo que el limite de x vale para los dos
			if (this->getCuerpo().at(x) != r2->getCuerpo().at(x)) {
				iguales = false;
			}
		}
		return iguales;
	}
	return false;
}

bool Regla::operator != (Regla *r2)
{
	if (this == r2)
		return false;
	return true;
}

bool Regla::Equals(Regla *r1)
{
	if (this == r1)
		return true;
	return false;
}

int Regla::GetHashCode()
{
	return 0;
}

string Regla::ToString()
{
	string texto = "Regla Tiene " + to_string(getNumeroCondiciones()) + " Condiciones\n";
	texto += "Cabeza " + cabeza->ToString() + " \n";
	for (int x = 0; x<getNumeroCondiciones(); x++)
	{
		texto = texto + "Cuerpo " + to_string((x + 1)) + ": " + cuerpo[x]->ToString() + " \n";
	}
	return texto;
}

Regla::Regla(const Regla &r) { }

Regla &Regla::operator=(const Regla &r) { return *this; }