#ifndef BASEDEDATOS_H
#define BASEDEDATOS_H
#define TF 100
#include <iostream>

using namespace std;

struct fecha{
	int dia,mes,anio;
};
struct puntuacion{
	float tiempo;
	fecha fecha1;
};
struct rankingnivel{
	puntuacion p[10];
	int cantidadpuntuaciones;
};
struct usuario{	
	char nombre[100], contrasenia[100];
	int pganadas=0, pperdidas=0, pabandonadas=0;
	float porcentajeganadas;
	rankingnivel rusuario[3];
};

struct lista{
	usuario usuarios[TF];
	int cantidadusuarios;
};

void crearlista(lista &l);
bool llena(const lista l);
bool buscarnombre(char elemento[],lista l);
bool buscarusuario(char nombre[],char contrasenia[],const lista l,int &numerodeusuario);
void cargarlista(lista &l);
void guardarlista(const lista l);
void ordenarpuntuaciones(lista &l,int numerodeusuario,int nivel);
void inicializarpuntajes(lista &l,int numerodeusuario);



#endif
