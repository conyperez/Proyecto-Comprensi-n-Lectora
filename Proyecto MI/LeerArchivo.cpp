#include "LeerArchivo.h"
#include "Hecho.h"
#include "Regla.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <list>

using namespace std;

LeerArchivo::LeerArchivo() {
	conector = Conector::obtenerConector();
}

LeerArchivo::~LeerArchivo() { }

void LeerArchivo::lectura() {
	ifstream archivo("C:\\Users\\Constanza\\Desktop\\Prueba.txt");
	if (archivo.fail()) {
		cout << "No se pudo abrir el archivo" << endl;
		exit(1);
	}

	const int size = 999999;
	char texto[size];
	string text;
	list<Regla> listaRegla;

	while (!archivo.eof()) { // Se lee cada regla (una por linea)
		archivo >> texto;
		// Separacion de la cabeza y el cuerpo de la regla.
		// Cabeza de la Regla
		char *palabra, *nextToken;
		palabra = strtok_s(texto, ":", &nextToken); //Divide la cabeza del cuerpo
		char *cabeza = palabra;
		//if (palabra) cout << "Cabeza: " << cabeza << endl;

		// Cuerpo de la Regla, se almacena en una lista
		list<char*> hechos;
		bool entrar = true;
		while (palabra) {
			palabra = strtok_s(NULL, ",", &nextToken);
			if (entrar) {
				text = palabra;
				text = text.substr(1, text.size());
				palabra = (char *)alloca(text.size() + 1);
				memcpy(palabra, text.c_str(), text.size() + 1);
				entrar = false;
			}
			//if (palabra) cout << "Cuerpo: " << palabra << endl;
			hechos.push_back(palabra);
		}

		// Se separa la constante del argumento del Hecho Cabeza  constante(argumento)
		char *constante = strtok_s(cabeza, "(", &nextToken);
		//if (constante) cout << "Cabeza\n   Constante: " << constante << endl;

		char *charCabezaConstante = constante;
		string tmpCabezaConst = charCabezaConstante;

		char *argumento;
		Hecho *hechoCabeza;
		entrar = true;
		while (constante && entrar) {
			constante = strtok_s(NULL, ")", &nextToken);
			argumento = constante;
			//if (constante) cout << "   Argumento: " << argumento << endl;
			string argu = argumento;
			Argumento argumento(argu);
			hechoCabeza = new Hecho(tmpCabezaConst, argumento);	// SE DEBE ALMACENAR EL HECHO (CABEZA)
			hechoCabeza->setPermanente(true);
			//conector->agregarHecho(hechoCabeza);
			entrar = false;
		}		

		// Se separa la constante del argumento de cada hecho del cuerpo de la regla
		string predicado;
		//cout << "Cuerpo" << endl;
		list<char*>::iterator it;
		int i = 0, tam = hechos.size();
		bool acceder = true;
		vector<Hecho*> vectHecho;
		for (it = hechos.begin(); it != hechos.end() && acceder; it++) {
			if (acceder == false) break;
			char *constante = strtok_s(*it, "(", &nextToken);
			//if (constante) cout << "  Hecho\n   Constante: " << constante << endl;

			predicado = constante;
			string hechoC = constante;
			entrar = true;
			while (constante && entrar) {
				constante = strtok_s(NULL, ")", &nextToken);
				char *argumento = constante;
				//if (constante) cout << "   Argumento: " << argumento << endl;
				string hechoA = argumento;
				Argumento arg(hechoA);
				entrar = false;
				Hecho *newHecho = new Hecho(hechoC, arg);	// SE DEBE ALMACENAR CADA HECHO DE LA REGLA
				newHecho->setPermanente(true);
				//conector->agregarHecho(newHecho);
				vectHecho.push_back(newHecho);
			}
			i++;
			if (i == tam - 1) {
				acceder = false;
			}
		}
		// SE DEBE ALMACENAR LA REGLA A LA BASE DE CONOCIMIENTO
		conector->agregarRegla(new Regla(hechoCabeza, vectHecho));
		
		//cout << endl << endl;
	}
	archivo.close();
}