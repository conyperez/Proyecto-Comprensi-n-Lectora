#include "stdafx.h"
#include <iostream>
#include <vector>
#include "Argumento.h"
#include "Conector.h"
#include "LeerArchivo.h"
#include "MotorDeInferencia.h"
#include "BaseDeConocimiento.h"
#include "BaseDeHechos.h"

using namespace std;

int main()
{
	LeerArchivo *archivo = new LeerArchivo(); // Se asume que esta bueno (REVISAR)
	archivo->lectura();

	Conector *conector = Conector::obtenerConector();
	BaseDeConocimiento *baseConocimiento = conector->obtenerBaseDeConocimiento();
	baseConocimiento->ordenarMenorAMayor();
	//cout << "---------BASE CONOCIMIENTO--------" << endl;
	//cout << baseConocimiento->ToString() << endl;

	BaseDeHechos *baseHechos = conector->obtenerBaseDeHechos();
	baseHechos->agregarHecho(new Hecho("sintoma", Argumento("rinitis"), VERDADERO));
	baseHechos->agregarHecho(new Hecho("sintoma", Argumento("estornudos"), VERDADERO));
	baseHechos->agregarHecho(new Hecho("sintoma", Argumento("reacciones_alergicas"), VERDADERO));
	baseHechos->agregarHecho(new Hecho("sintoma", Argumento("tos_seca"), VERDADERO));
	baseHechos->agregarHecho(new Hecho("sintoma", Argumento("sintoma_alergia"), VERDADERO));
	/*
	baseHechos->agregarHecho(new Hecho("sintoma", Argumento("estornudos"), VERDADERO));
	baseHechos->agregarHecho(new Hecho("sintoma", Argumento("dolor_de_cabeza"), VERDADERO));
	baseHechos->agregarHecho(new Hecho("sintoma", Argumento("febril_con_escalofrios"), VERDADERO));*/

	cout << "------------------BASE HECHOS-------------------" << endl;
	cout << baseHechos->ToString() << endl;

	MotorDeInferencia *motorInferencia = new MotorDeInferencia(baseHechos, baseConocimiento);

	Hecho *resultado = nullptr;
	//cout << "--------------Ejecutando encadenamiento atras-------------" << endl;
	//resultado = motorInferencia->ejecutar("enfermedad", ENCADENAMIENTO_ATRAS);
	cout << "Ejecutanco encadenamiento adelante" << endl;
	resultado = motorInferencia->ejecutar("enfermedad", ENCADENAMIENTO_ADELANTE);
	if (motorInferencia->getTerminoInferencia()) {
		string enfermedad = "";
		if (resultado->getEstado() == VERDADERO)
		{
			string enfermedad = resultado->getArgumento()[0].ToString();
			int i = 0;
			while (i == 0) {
				string::size_type pos = enfermedad.find("_",0);
				if (pos == string::npos) break;
				enfermedad.replace(pos,1," ");
			}
			cout << "Tiene la enfermedad: " << enfermedad << endl;
		}
		else
		{
			enfermedad = "Enfermedad desconocida";
			cout << "Tiene la enfermedad: " << enfermedad << endl;
		}
		cout << enfermedad << endl;
	}

	cout << "------------JUSTIFICACION-------------" << endl;
	cout << motorInferencia->getJustificacion() << endl;

	if (motorInferencia != nullptr)
		motorInferencia->setDetenerInferencia(true);

	delete archivo;
	delete baseConocimiento;
	delete motorInferencia;
	delete baseHechos;
	delete resultado;

	system("PAUSE");
    return 0;
}


