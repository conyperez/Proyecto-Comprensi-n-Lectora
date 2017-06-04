#ifndef CONECTOR_H
#define CONECTOR_H

#include <string>
#include "BaseDeHechos.h"
#include "Hecho.h"
#include "BaseDeConocimiento.h"
#include "Regla.h"


class Conector {

public:
	Conector();
	~Conector();
	static Conector* obtenerConector();
	void agregarRegla(Regla *regla);
	void agregarHecho(Hecho *hecho);
	bool getLeyendoRegla();
	void inicioRegla();
	void finRegla();
	BaseDeConocimiento* obtenerBaseDeConocimiento();
	BaseDeHechos* obtenerBaseDeHechos();
	void cerrarArchivo();
	string ToString();

private:
	static Conector *conector;
	BaseDeConocimiento *reglas;
	BaseDeHechos *hechos;
	bool leyendoRegla = false;
};
#endif // CONECTOR_H