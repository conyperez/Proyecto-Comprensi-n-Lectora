#ifndef MOTORDEINFERENCIA_H
#define MOTORDEINFERENCIA_H

#include "BaseDeHechos.h"
#include "BaseDeConocimiento.h"
#include "Hecho.h"
#include <string>

using namespace std;

const int ENCADENAMIENTO_ATRAS = 0;
const int ENCADENAMIENTO_ADELANTE = 1;

class MotorDeInferencia {

private:
	BaseDeHechos *baseHechos;
	BaseDeConocimiento *baseConocimiento;

	string textoPregunta = "";
	bool respondioUsuario = false;
	bool respuesta = false;
	bool terminoInferencia = false;
	bool detenerInferencia = false;
	string justificacion = "";
	int nivel = 0;

public:
	MotorDeInferencia(BaseDeHechos *baseHechos, BaseDeConocimiento *baseConocimiento);
	~MotorDeInferencia();
	Hecho* encadenamientoHaciaAdelante(string hecho);
	Hecho* encadenamientoHaciaAtras(Hecho *hechoMeta);
	Hecho* ejecutar(string objetivo, int encadenamiento);
	bool getRespondioUsuario();
	void setRespondioUsuario(bool value);
	string getTextoPregunta();
	void setTextPregunta(string value);
	void setDetenerInferencia(bool value);
	bool getTerminoInferencia();
	string getJustificacion();
};
#endif // MOTORDEINFERENCIA_H