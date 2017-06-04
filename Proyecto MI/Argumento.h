#pragma once
#ifndef ARGUMENTO_H
#define ARGUMENTO_H

#include <string>

using namespace std;

class Argumento {
public:
	Argumento(string);
	~Argumento();
	string getValor();
	void setValor(string);
	bool operator == (Argumento*);
	bool operator != (Argumento*);
	bool Equals(Argumento *obj);
	int GetHashCode();
	string ToString();

private:
	string argumento;

};
#endif // !ARGUMENTO_H

