#include "Argumento.h"

Argumento::Argumento(string newArgumento)
{
	argumento = newArgumento;
}

Argumento::~Argumento() { }

string Argumento::getValor()
{
	return argumento;
}

void Argumento::setValor(string newArgumento)
{
	argumento = newArgumento;
}

bool Argumento::operator!=(Argumento *arg)
{
	if (argumento == arg->argumento) {
		return false;
	}
	return false;
}

int Argumento::GetHashCode()
{
	// return argumento.GetHashCode();
	return 0;
}

string Argumento::ToString()
{
	return argumento;
}

bool Argumento::operator == (Argumento *c2)
{
	if (this == nullptr && c2 == nullptr)
		return true;
	else if ((this == nullptr && c2 != nullptr) || (this != nullptr && c2 == nullptr))
		return false;
	else if (this->getValor() == c2->getValor())
		return true;
	return false;
}


bool Argumento::Equals(Argumento *obj)
{
	if (this == obj)
	{
		return true;
	}
	return false;
}