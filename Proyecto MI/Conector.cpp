#include "Conector.h"

Conector *Conector::conector = Conector::obtenerConector();

Conector::Conector() {
	reglas = new BaseDeConocimiento();
	hechos = new BaseDeHechos();
}

Conector::~Conector() { }

void Conector::agregarRegla(Regla *regla)
{
	reglas->agregarRegla(regla);
}

void Conector::agregarHecho(Hecho *hecho)
{
	hechos->agregarHecho(hecho);
}

void Conector::cerrarArchivo()
{
	reglas = new BaseDeConocimiento();
	hechos = new BaseDeHechos();
}

Conector* Conector::obtenerConector()
{
	if (Conector::conector == nullptr) {
		Conector *conector = new Conector();
		return conector;
	}
	return Conector::conector;
}

bool Conector::getLeyendoRegla()
{
	return leyendoRegla;
}

void Conector::inicioRegla()
{
	leyendoRegla = true;
}

void Conector::finRegla()
{
	leyendoRegla = false;
}

BaseDeHechos* Conector::obtenerBaseDeHechos()
{
	return hechos;
}

BaseDeConocimiento* Conector::obtenerBaseDeConocimiento()
{
	return reglas;
}

string Conector::ToString()
{
	string texto = "Base de Conocimiento\n";
	for (int x = 0; x<reglas->getNumeroReglas(); x++)
	{
		texto = texto + reglas->obtenerRegla(x)->ToString();
	}
	texto += "Base de Hechos\n";
	return texto;
}