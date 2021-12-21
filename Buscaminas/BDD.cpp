#include <iostream>
#include "BaseDeDatos.h"
#include <string>
#include <fstream>
#include <cstring>
#include <windows.h>
using namespace std;

void crearlista(lista &l){
	l.cantidadusuarios=0;
}
bool llena(const lista l){
	return (l.cantidadusuarios==TF-1);
}

bool buscarnombre(char elemento[],const lista l){
	bool encontro=false;
	int i=0;
	while(!encontro && i<l.cantidadusuarios){
		if(strcmp(elemento,l.usuarios[i].nombre)==0)
			encontro=true;
		i++;
	}
	return encontro;
}
bool buscarusuario(char nombre[],char contrasenia[],const lista l,int &numerodeusuario){
	bool encontro=false;
	int i=0;
	while(!encontro && i<l.cantidadusuarios){
		if(strcmp(l.usuarios[i].nombre,nombre)==0){
			if(strcmp(l.usuarios[i].contrasenia,contrasenia)==0)
				encontro=true;
		}
		i++;
	}
	if(encontro)
		numerodeusuario=i-1;
	return encontro;
}
void cargarlista(lista &l){//Toda la informacion del archivo la vuelca en el array de usuarios
	bool llego;
	ifstream Archivo;
	usuario nombreleido;
	Archivo.open("BDD.dat",ios::binary);

	if(Archivo.fail()){
		cout<<"fallo al abrir el archivo\n\n";
	}else {
		while(!llego){
			Archivo.read((char*) &nombreleido,sizeof(usuario));
			if(Archivo.eof())llego=true;
			else{
				l.usuarios[l.cantidadusuarios]=nombreleido;
				l.cantidadusuarios++;
			}
			cout<<endl<<nombreleido.nombre;
		}
	}
	Archivo.close();
}
void guardarlista(lista l){//Toda la informacion del array de usuarios la vuelca en el archivo
	ofstream Archivo;
	int i=0;
	Archivo.open("BDD.dat", ios::binary);
		if(Archivo.fail())
			cout<<"fallo al abrir el archivo\n\n";
		else{
			while(i<l.cantidadusuarios){
				usuario j=l.usuarios[i];
				Archivo.write((char*) &j, sizeof(usuario));
				i++;
			}
		}
	Archivo.close();
}
void ordenarpuntuaciones(lista &l,int numerodeusuario,int nivel){//ordena las puntuaciones de manera acscendente
	float temporaltiempo;
	fecha temporalfecha;
	for (int i = 0;i < 10; i++){
		for (int j = 0; j< 9; j++){
			if (l.usuarios[numerodeusuario].rusuario[nivel-1].p[j].tiempo > l.usuarios[numerodeusuario].rusuario[nivel-1].p[j+1].tiempo){
				temporaltiempo = l.usuarios[numerodeusuario].rusuario[nivel-1].p[j].tiempo; 
				l.usuarios[numerodeusuario].rusuario[nivel-1].p[j].tiempo = l.usuarios[numerodeusuario].rusuario[nivel-1].p[j+1].tiempo; 
				l.usuarios[numerodeusuario].rusuario[nivel-1].p[j+1].tiempo = temporaltiempo;
				temporalfecha = l.usuarios[numerodeusuario].rusuario[nivel-1].p[j].fecha1;
				cout<<l.usuarios[i].rusuario[nivel].p[0].fecha1.dia<<"/";
				cout<<l.usuarios[i].rusuario[nivel].p[0].fecha1.mes<<"/";
				cout<<l.usuarios[i].rusuario[nivel].p[0].fecha1.anio<<endl<<endl;
				
				l.usuarios[numerodeusuario].rusuario[nivel-1].p[j].fecha1 = l.usuarios[numerodeusuario].rusuario[nivel-1].p[j+1].fecha1; 
				l.usuarios[numerodeusuario].rusuario[nivel-1].p[j+1].fecha1 = temporalfecha;
			}
		}
	}
	system("pause");
}
void inicializarpuntajes(lista &l,int numerodeusuario){//Al crear un usuario se inican todas sus puntuaciones en un numero muy grande, para cuando se gane una partida siempre se obtenga un puntaje menor
	for(int i=0;i<10;i++){
		l.usuarios[numerodeusuario].rusuario[0].p[i].tiempo=900000000000000;
	}
	l.usuarios[numerodeusuario].rusuario[0].cantidadpuntuaciones=10;
	for(int i=0;i<10;i++){
		l.usuarios[numerodeusuario].rusuario[1].p[i].tiempo=900000000000000;
	}
	l.usuarios[numerodeusuario].rusuario[1].cantidadpuntuaciones=10;
	for(int i=0;i<10;i++){
		l.usuarios[numerodeusuario].rusuario[2].p[i].tiempo=900000000000000;
	}
	l.usuarios[numerodeusuario].rusuario[2].cantidadpuntuaciones=10;
}
