#ifndef LEERARCHIVO_H
#define LEERARCHIVO_H
#include "Conector.h"

class LeerArchivo
{
public:
	LeerArchivo();
	~LeerArchivo();
	void lectura();

private:
	Conector *conector;
};

#endif // LEERARCHIVO_H

