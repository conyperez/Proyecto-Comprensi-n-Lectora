#ifndef REGLA_H
#define REGLA_H

#include "Hecho.h"
#include <vector>

class Regla {

public:
	Regla();
	Regla(Hecho *head, vector<Hecho*> boddy);
	~Regla();
	Hecho* getCabeza() const;
	void setCabeza(Hecho *head);
	vector<Hecho*> getCuerpo() const;
	void setCuerpo(vector<Hecho*> boddy);
	bool getMarcada();
	void setMarcada(bool marca);
	int getNumeroCondiciones();
	int getHechosConfirmados();
	void setHechosConfirmados(int confirmados);
	double getPorcentajeHechosConfirmados();
	bool operator == (Regla *r2);
	bool operator != (Regla *r2);
	bool Equals(Regla *r1);
	int GetHashCode();
	string ToString();
	Regla(const Regla &r);
	Regla& operator=(const Regla &r);

private:
	Hecho* cabeza;
	vector<Hecho*> cuerpo;
	bool marcada = false;
	int hechosConfirmados = 0;
};
#endif // !REGLA_H

