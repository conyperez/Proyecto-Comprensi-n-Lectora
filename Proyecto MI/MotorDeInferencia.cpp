#include "MotorDeInferencia.h"
#include "BaseDeConocimiento.h"
#include "Regla.h"
#include <list>
#include <string>

MotorDeInferencia::MotorDeInferencia(BaseDeHechos *bHechos, BaseDeConocimiento *bConocimiento) {
	baseConocimiento = bConocimiento;
	baseHechos = bHechos;
	
}

MotorDeInferencia::~MotorDeInferencia() { }

Hecho* MotorDeInferencia::encadenamientoHaciaAdelante(string hecho) {
	cout << "Ejecutando encadenamiento hacia adelanteeeeeeeeeeeee" << endl;
	list<Regla*> conjuntoConflicto;
	list<Regla*>::iterator z;
	Regla *reglaActual = nullptr;
	bool cambio = true;

	while (baseConocimiento->getReglasMarcadas() < baseConocimiento->getNumeroReglas() && cambio) {
		for (int x = 0; x < baseConocimiento->getNumeroReglas(); x++) {
			reglaActual = baseConocimiento->obtenerRegla(x);
			if (!reglaActual->getMarcada()) {   // Si la regla no esta marcada
											  // Se revisan las condiciones de las reglas que estan en la base de hechos
				bool reglaComprobable = true;
				for (int y = 0; y < reglaActual->getNumeroCondiciones(); y++) {
					Hecho *condicion = reglaActual->getCuerpo()[y];
					if (baseHechos->existeHecho(condicion)) {
						/*
						if (baseHechos.estadoHecho(condicion) != VERDADERO) {
							reglaComprobable = false;
						}
						*/
						int estadoRegla = baseHechos->estadoHecho(condicion);
						if (estadoRegla == FALSO) {
							if (!reglaActual->getMarcada()) {
								reglaActual->setMarcada(true);
								int valor = baseConocimiento->getReglasMarcadas();
								baseConocimiento->setReglasMarcadas(valor++);
							}
							reglaComprobable = false;
						}
						else if (estadoRegla == INDETERMINADO) {
							reglaComprobable = false;
						}
					}
					else {
						reglaComprobable = false;
					}
				}
				// Solo si la regla es verdadera se agrega al conjunto de conflicto
				if (reglaComprobable) {
					conjuntoConflicto.push_back(reglaActual);
				}
			}
		}
		Regla *reglaMasCondiciones = nullptr;
		int numeroCondiciones = 0;
		reglaActual = nullptr;
		for (z = conjuntoConflicto.begin(); z != conjuntoConflicto.end(); z++) {
			reglaActual = *z;
			if (reglaActual->getNumeroCondiciones() > numeroCondiciones) {
				reglaMasCondiciones = reglaActual;
				numeroCondiciones = reglaActual->getNumeroCondiciones();
			}
		}
		conjuntoConflicto.clear();  //Se eliminan todas las reglas del conjunto conflicto
									//La primera regla con mas condiciones se agrega a la base de hechos
		if (reglaMasCondiciones != nullptr) {
			reglaMasCondiciones->getCabeza()->setEstado(VERDADERO);
			baseHechos->agregarHecho(reglaMasCondiciones->getCabeza());
			reglaMasCondiciones->setMarcada(true);
			int valor = baseConocimiento->getReglasMarcadas();
			baseConocimiento->setReglasMarcadas(valor++);
			string cuerpoTexto = "";
			int tam = reglaMasCondiciones->getCuerpo().size();
			for (int s = 0; s < tam; s++) {
				cuerpoTexto += "     " + reglaMasCondiciones->getCuerpo()[s]->getArgumento()[0].ToString() + "\n"; 
			}
			justificacion += "A partir de:\n" + cuerpoTexto + "Se infiere: " + reglaMasCondiciones->getCabeza()->getRelacion() + "(" + reglaMasCondiciones->getCabeza()->getArgumento()[0].ToString() + ")\n\n";
			cout << reglaMasCondiciones->getCabeza()->getRelacion() + " " + reglaMasCondiciones->getCabeza()->getArgumento()[0].ToString() << endl;
			if (reglaMasCondiciones->getCabeza()->getRelacion() == hecho) {
				// Se infiere una conclusión
				cout << "Salio, infirio algo" << endl;
				return reglaMasCondiciones->getCabeza();
			}
		}
		else {
			// Se le pregunta al usuario por algun hecho sin verificar
			cout << "Faltan hechos" << endl;
			reglaActual = nullptr;
			bool existe = false;
			bool nuevoHecho = false;
			// Se recorre la base de conocimiento en busca de alguna condicion no verificada
			for (int v = 0; v < baseConocimiento->getNumeroReglas() && !nuevoHecho; v++) {
				reglaActual = baseConocimiento->obtenerRegla(v);
				// Se buscan hechos sin verificar de reglas no marcadas y que no esten en la base de hechos
				cout << "\tRevisando Regla " << v << endl;
				if (!reglaActual->getMarcada() && !baseHechos->existeHecho(reglaActual->getCabeza())) {
					cout << "\t\tRegla no marcada" << endl;
					Hecho *condicionRegla;
					// Se revisan las condiciones de la regla
					int tam = reglaActual->getCuerpo().size();
					for (int w = 0; w < tam && !nuevoHecho; w++) {
						cout << "\t\t\tRevisando condicion de la regla " << w << " existe: " << existe;
						condicionRegla = reglaActual->getCuerpo()[w];
						// No tiene que existir el hecho en la base de hechos
						if (!baseHechos->existeHecho(condicionRegla)) {
							//La condicion no puede ser part de otra regla
							Regla *encontrada;
							for (int u = 0; u < baseConocimiento->getNumeroReglas() && !existe; u++) {
								cout << "\t\t\t\tRevisando si es parte de otra regla" << endl;
								encontrada = baseConocimiento->obtenerRegla(u);
								if (encontrada->getCabeza()->operator==(condicionRegla)) {
									cout << "\t\t\t\t\tEs parte de otra regla" << endl;
									// La condicion es parte de otra regla por lo que no se pregunta al usuario
									existe = true;
								}
							}
							existe = false;
						}
					}
				}
			}
			if (!nuevoHecho) {
				// Si no hay un nuevo hecho entonces no se puede determinar
				cout << "No hay nada mas que preguntar" << endl;
				cambio = false;
			}
		}
	}
	return nullptr;
}

Hecho* MotorDeInferencia::encadenamientoHaciaAtras(Hecho *hechoMeta) {
	cout << "META: " << endl;
	cout << "	Argumento: "<<hechoMeta->getArgumento().at(0).ToString()<<", Estado: "<<hechoMeta->getEstadoTexto()<< endl;
	string espacio = "";
	for (int x = 0; x < nivel; x++) {
		if (x < nivel - 1) {
			espacio = espacio + "|    ";
		}
		else {
			espacio = espacio + "|-";
		}
	}
	justificacion += espacio + hechoMeta->getArgumento()[0].ToString() + "\n";

	if (baseHechos->existeHecho(hechoMeta)) {
		cout << "EXISTE META EN LA BASE DE HECHOS" << endl;
		hechoMeta->setEstado(baseHechos->estadoHecho(hechoMeta));
		justificacion = justificacion.substr(0, justificacion.size() - 1) + " => " + hechoMeta->getEstadoTexto() + "\n";
		return hechoMeta;
	}
	cout << "  NO EXISTE META EN LA BASE DE HECHOS" << endl;
	BaseDeConocimiento conjuntoConflicto = BaseDeConocimiento();
	cout << "  Numero Reglas: " << baseConocimiento->getNumeroReglas() << endl;
	for (int x = 0; x < baseConocimiento->getNumeroReglas(); x++) {
		Regla *reglaActual = baseConocimiento->obtenerRegla(x);
		cout << "    Regla Actual: " << reglaActual->getCabeza()->getArgumento().at(0).ToString() << endl;
		if (reglaActual->getCabeza() == hechoMeta) {
			cout << "     Es igual al hecho meta" << endl;
			conjuntoConflicto.agregarRegla(reglaActual);
		}
	}
	cout << "\nConjunto conflicto tam: " << conjuntoConflicto.getNumeroReglas() << endl;
	if (conjuntoConflicto.getNumeroReglas() > 0) {
		Regla *reglaActual;
		Hecho *resultado = nullptr;
		int contadorFalso = 0;
		for (int x = 0; x < conjuntoConflicto.getNumeroReglas(); x++) {
			reglaActual = conjuntoConflicto.obtenerRegla(x);
			cout << " Regla actual CF: " << reglaActual->getCabeza()->getArgumento().at(0).ToString() << endl;
			bool verdadero = true;
			bool indeterminado = false;
			bool reglaFalsa = false;
			int tam = reglaActual->getCuerpo().size();
			for (int y = 0; y < tam && !reglaFalsa; y++) {
				if (baseHechos->existeHecho(reglaActual->getCuerpo()[y])) {
					cout << "  EXISTE HECHO EN LA BASE DE HECHOS: " << reglaActual->getCuerpo()[y]->getArgumento().at(0).ToString() << endl;
					cout << "  Estado: " << baseHechos->estadoHecho(reglaActual->getCuerpo()[y]) << endl;
					if (baseHechos->estadoHecho(reglaActual->getCuerpo()[y]) == FALSO) {
						reglaFalsa = true;
						verdadero = false;
						hechoMeta->setEstado(FALSO);
						justificacion = justificacion + espacio + "    |-" + reglaActual->getCuerpo()[y]->getArgumento()[0].ToString() + " => " + hechoMeta->getEstadoTexto() + "\n";
						baseHechos->agregarHecho(hechoMeta);
					}
				}
			}
			// Regla falsa
			tam = reglaActual->getCuerpo().size();
			for (int y = 0; y < tam && !reglaFalsa; y++) {
				nivel++;
				resultado = encadenamientoHaciaAtras(reglaActual->getCuerpo()[y]);
				nivel--;
				if (resultado->getEstado() == FALSO) {
					verdadero = false;
					y = reglaActual->getCuerpo().size();
					hechoMeta->setEstado(FALSO);
					baseHechos->agregarHecho(hechoMeta);
				}
				else if (resultado->getEstado() == INDETERMINADO) {
					indeterminado = true;
					y = reglaActual->getCuerpo().size();
				}
			}
			if (verdadero && !indeterminado) {
				hechoMeta->setEstado(VERDADERO);
				baseHechos->agregarHecho(hechoMeta);
				return hechoMeta;
			}
			else if (!verdadero && !indeterminado) {
				hechoMeta->setEstado(FALSO);
				baseHechos->agregarHecho(hechoMeta);
				contadorFalso++;
			}
			if (espacio.length() < 0 && x < conjuntoConflicto.getNumeroReglas() - 1) {
				justificacion += espacio + "    o" + "\n";
			}
		}
		if (contadorFalso == conjuntoConflicto.getNumeroReglas()) {
			hechoMeta->setEstado(FALSO);
			baseHechos->agregarHecho(hechoMeta);
			return hechoMeta;
		}
	}
	baseHechos->agregarHecho(hechoMeta);
	justificacion = justificacion.substr(0, justificacion.length() - 1) + " => " + hechoMeta->getEstadoTexto() + "\n";
	return hechoMeta;
}

Hecho* MotorDeInferencia::ejecutar(string objetivo, int encadenamiento) {
	if (encadenamiento == ENCADENAMIENTO_ATRAS) {
		Regla *regla = new Regla();
		list<Regla*> reglasRestantes;
		list<Regla*>::iterator it;
		terminoInferencia = false;
		justificacion = "";

		cout << "------------EJECUTAR------------" << endl;
		cout << "Objetivo: " << objetivo << endl;

		cout << "Agregando reglas restantes: " << endl;
		for (int i = 0; i < baseConocimiento->getNumeroReglas(); i++) {
			if (baseConocimiento->obtenerRegla(i)->getCabeza()->getRelacion() == objetivo) {
				cout << i << ". " << baseConocimiento->obtenerRegla(i)->getCabeza()->getRelacion() << endl;
				reglasRestantes.push_back(baseConocimiento->obtenerRegla(i));
			}
		}

		while (reglasRestantes.size() > 0) {
			cout << "Reglas restantes tam: " << reglasRestantes.size() << endl;
			for (it = reglasRestantes.begin(); it != reglasRestantes.end(); it++) {
				regla = *it;
				regla->setHechosConfirmados(0);
				cout << "  Numero Condiciones: " << regla->getNumeroCondiciones() << endl;
				for (int j = 0; j < regla->getNumeroCondiciones(); j++) {					
					if (baseHechos->existeHecho(regla->getCuerpo()[j])) {
						int valor = regla->getHechosConfirmados();
						cout << "    Existe: " << regla->getCuerpo()[j]->getArgumento().at(0).ToString() << endl;
						valor++;
						regla->setHechosConfirmados(valor);
						cout << "     Hechos confirmados: " << regla->getHechosConfirmados() << endl;
					}
				}
			}
			cout << "\nRevisar porcentaje:" << endl;
			Regla *reglaMaximo = nullptr;
			double valorMaximo = -1;
			for (it = reglasRestantes.begin(); it != reglasRestantes.end(); it++) {
				regla = *it;
				cout << "   Regla: " << regla->getCabeza()->getArgumento().at(0).ToString() << endl;
				cout << "    Porcentaje: " << regla->getPorcentajeHechosConfirmados() << endl;
				if (valorMaximo < regla->getPorcentajeHechosConfirmados()) {
					reglaMaximo = regla;
					valorMaximo = regla->getPorcentajeHechosConfirmados();
				}
			}
			nivel = 0;
			cout << "---------- ENCADENAMIENTO HACIA ATRAS ------------" << endl;
			Hecho *hechoResultado = encadenamientoHaciaAtras(reglaMaximo->getCabeza());
			if (hechoResultado->getEstado() == VERDADERO) {
				terminoInferencia = true;
				return hechoResultado;
			}
			if (reglaMaximo != nullptr) {
				reglasRestantes.remove(reglaMaximo);
			}
		}
		terminoInferencia = true;
		Hecho *indeterminado =  new Hecho(objetivo, Argumento("X"),INDETERMINADO);
		return indeterminado; //No se encontró
	}
	else {
		cout << "------------EJECUTAR------------" << endl;
		cout << "Objetivo: " << objetivo << endl;
		Hecho *hechoResultado = encadenamientoHaciaAdelante(objetivo);
		if (hechoResultado != nullptr && hechoResultado->getEstado() == VERDADERO) {
			terminoInferencia = true;
			return hechoResultado;
		}
	}
	terminoInferencia = true;
	Hecho *indeterminado = new Hecho(objetivo, Argumento("X"), INDETERMINADO);
	return indeterminado; // No se encontro
}

bool MotorDeInferencia::getRespondioUsuario() {
	return respuesta;
}

void MotorDeInferencia::setRespondioUsuario(bool value) {
	respondioUsuario = true;
	respuesta = value;
}

string MotorDeInferencia::getTextoPregunta() {
	if (textoPregunta != "" && textoPregunta.length() > 0) {
		return textoPregunta.replace(textoPregunta.begin(), textoPregunta.end(), "_", "");
	}
	return NULL;
}

void MotorDeInferencia::setTextPregunta(string value) {
	textoPregunta = value;
}

void MotorDeInferencia::setDetenerInferencia(bool value) {
	detenerInferencia = value;
}

bool MotorDeInferencia::getTerminoInferencia() {
	return terminoInferencia;
}

string MotorDeInferencia::getJustificacion() {
	return justificacion;
}
