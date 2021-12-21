#include <iostream>
#include <conio.h>
#include <windows.h>
#include <ctime>
#include <cstdlib>
#include "BaseDeDatos.h"
#define FILAS1 16
#define COLUMNAS1 30
#define MINA 'X'
/* AYUDA MEMORIA
MATRIZ CIEGA= Todas las casillas=0, Menos las de las minas=X
MATRIZ USUARIO= Todas las casillas="spacebar", hasta que el ususario ingrese casillas y acciones
*/
#include <string>
#include "BaseDeDatos.h"
#include <fstream>
using namespace std;

void gotoxy(SHORT x,SHORT y) {
	COORD cp = {x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cp);
}
void menuPrincipal(int numerodeusuario,lista &l);
void intrucciones();
void despedida();
void Jugar(char nivel,int numerodeusuario,lista &l);
void minasAleatorias(char ciega[FILAS1][COLUMNAS1],int COLUMNAS);
void celdasVecinas(char ciega[FILAS1][COLUMNAS1],int FILAS,int COLUMNAS);
void encabezadoColumnas(int COLUMNAS);
void encabezadoFilas(char usuario[FILAS1][COLUMNAS1],int FILAS,int COLUMNAS);
void separadorFilas(int COLUMNAS);
void mostrarCasilla(int fila,int columna,char usuario[FILAS1][COLUMNAS1],char ciega[FILAS1][COLUMNAS1]);
void mostrarMinas(char ciega[FILAS1][COLUMNAS1],char usuario[FILAS1][COLUMNAS1],int FILAS, int COLUMNAS);
void marcarDesmarcar(char usuario[FILAS1][COLUMNAS1],int fila,int columna);
void Juego(int FILAS,int COLUMNAS,int numerodeusuario,lista &l);
void Color(int Background, int Text);
void cerosCercanos(char usuario[FILAS1][COLUMNAS1],char ciega[FILAS1][COLUMNAS1],int fila0,int columna0,int FILAS, int COLUMNAS,int &contadorgana);
//TP 2
void pantallaUsuario(lista &l,usuario us1);
void ingreso(lista &l);
void crearusuario(lista &l,usuario us1);
bool nombreValido(char nombre[]);
bool contraseniaValida(char contrasenia[]);
void encriptarcontrasenia(char contrasenia[]);
void ranking(lista &l);
void mejorPuntajeNivel(lista &l);
void rankingUsuario(lista &l);
void mejorPuntajeNivelUsuario(lista &l);
void cargarpuntuacion(lista &l,int numerodeusuario,float nuevospuntos,int nivel);
void ordenarpganadas(lista &l);
float porcentajepganadas(int usuario,lista l);
float porcentajeperdidas(int usuario,lista l);
float porcentajeabandonadas(int usuario,lista l);
void mostrarranking(lista &l);
void forswitch(int inicial,int final,lista &l);

int main(int argc, char *argv[]) {
	char entrada;
	usuario us1;
	lista listado;
	crearlista(listado);
	do{ //menú de bienvenida
		system("mode con: cols=150 lines=30");//Tamaño de la consola
		system("color 0F");//Color de la consola y la letras
		gotoxy(0,6);
		std::cout << R"(
			.______    __    __       _______.  ______     ___      .___  ___.  __  .__   __.      ___           _______.
			|   _  \  |  |  |  |     /       | /      |   /   \     |   \/   | |  | |  \ |  |     /   \         /       |
			|  |_)  | |  |  |  |    |   (----`|  ,----'  /  ^  \    |  \  /  | |  | |   \|  |    /  ^  \       |   (----`
			|   _  <  |  |  |  |     \   \    |  |      /  /_\  \   |  |\/|  | |  | |  . `  |   /  /_\  \       \   \                
			|  |_)  | |  `--'  | .----)   |   |  `----./  _____  \  |  |  |  | |  | |  |\   |  /  _____  \  .----)   |   
			|______/   \______/  |_______/     \______/__/     \__\ |__|  |__| |__| |__| \__| /__/     \__\ |_______/    
			
			
			)" << '\n';
		gotoxy(63,20);
		cout<<"Pulse Enter para continuar...\n\n\n\n\n\n\n\n\n\n";
		entrada=cin.get();
	}while(entrada!='\n');
	cargarlista(listado);
	pantallaUsuario(listado,us1);

	return 0;
}

void pantallaUsuario(lista &l,usuario us1){
	system("mode con: cols=70 lines=15");
	char entrada;
	bool salir=false;
	do{
		system("cls");
		system("color 0F");
		cout<<"\n\t\t\t   MENU DE INICIO\n";
		cout<<"\t\t------------------------------------";
		cout<<"\n\t\t    Escoja una de las OPCIONES: \n";
		cout<<"\n\t\t    1. Iniciar sesion";
		if(!llena(l)){//En caso de que se puedan seguir creando usuarios
			cout<<"\n\t\t    2. Crear usuario";
			cout<<"\n\t\t    3. Visualizar Ranking \n\t\t    S. Salir\n";
			cin>>entrada;
			if(entrada!='1' && entrada!='2' && entrada!='3' && entrada!='S' && entrada!='s'){
				cout<<"El valor alfanumérico "<<entrada<<" no es válido \a";
				Sleep(2000);
			}
			else{
				if(entrada=='1')//Entrada a ingresar
					ingreso(l);
				else{
					if(entrada=='2') //Entrada al nivel
						crearusuario(l,us1);
					else{
						if(entrada=='3')
							ranking(l);
						else{
							do{ //Salir de la aplicación
								system("mode con: cols=69 lines=20");
								system("cls");
								gotoxy(13,5);
								cout<<"¿Está seguro que quiere cerrar la aplicación?";
								gotoxy(24,7);
								cout<<"Y- Si      C- Cancelar\n\n\n\n\n";
								entrada=cin.get();
							}while(entrada!='y' && entrada!='Y' && entrada!='c' && entrada!='C');
							if(entrada=='y'){
								guardarlista(l);
								despedida();
								salir=true;
							}
						}
					}
				}
			}
		}
		else{
			cout<<"\n\t\t    2. Visualizar Ranking \n\t\t    S. Salir\n";
			cin>>entrada;
			if(entrada!='1' && entrada!='2' && entrada!='S' && entrada!='s'){
				cout<<"El valor alfanumerico "<<entrada<<" no es valido \a";
				Sleep(2000);
			}
			else{
				if(entrada=='1')//Entrada a ingresar
					ingreso(l);
				else{
					if(entrada=='2') //Entrada al nivel
						ranking(l);
					else{
						do{ //Salir de la aplicación
							system("mode con: cols=69 lines=20");
							system("cls");
							gotoxy(13,5);
							cout<<"¿Esta seguro que quiere cerrar la aplicacion?";
							gotoxy(24,7);
							cout<<"Y- Si      C- Cancelar\n\n\n\n\n";
							entrada=cin.get();
						}while(entrada!='y' && entrada!='Y' && entrada!='c' && entrada!='C');
						if(entrada=='y'){
							guardarlista(l);
							despedida();
							salir=true;
						}
					}
				}
			}
		}
	} while(!salir);
}

void ingreso(lista &l){
	char nombre[100],contrasenia[100];
	int invalidez=3,numerodeusuario;
	bool usuariovalido;
	do{
		usuariovalido=true;
		system("cls");
		cout<<"Tiene "<<invalidez<<" intento/os para ingresar correctamente su usuario"<<endl<<endl;
		cout<<"Nombre de Usuario: ";
		cin>>ws;
		gets(nombre);
		cout<<endl<<"Contrasena: ";
		cin>>ws;
		gets(contrasenia);
		encriptarcontrasenia(contrasenia);
		if(!buscarusuario(nombre,contrasenia,l,numerodeusuario)){
			cout<<endl<<"El usuario ingresado no existe. Verifica su nombre y/o contrasena\a";
			Sleep(3000);
			usuariovalido=false;
			invalidez--;
		}
	} while(!usuariovalido && invalidez!=0);
	if(usuariovalido)
		menuPrincipal(numerodeusuario,l);
	system("mode con: cols=70 lines=15");
}

void crearusuario(lista &l,usuario us1){
	system("mode con: cols=90 lines=25");
	system("cls");
	cout<<"El nombre debe poseer maximo 10 caracteres alfanumericos"<<endl<<endl;
	cout<<"Nombre de usuario: ";
	cin>>ws;
	gets(us1.nombre);
	if(nombreValido(us1.nombre) && !buscarnombre(us1.nombre,l)){
		cout<<endl<<"La contrasena debe ser alfanumerica"<<endl;
		cout<<"Solo permite los siguientes caracteres especiales: $ # % &"<<endl;
		cout<<"Debe poseer al menos una minuscula, una mayuscula y un caracter especial"<<endl;
		cout<<"Minimo caracteres=8      Maximo caracteres=12"<<endl<<endl;
		cout<<"Contrasena: ";
		cin>>ws;
		gets(us1.contrasenia);
		if(contraseniaValida(us1.contrasenia)){
			encriptarcontrasenia(us1.contrasenia);;
			l.usuarios[l.cantidadusuarios]=us1;
			inicializarpuntajes(l,l.cantidadusuarios);
			l.cantidadusuarios++;
			guardarlista(l);
		}
		else{
			cout<<endl<<"La contrasena ingresada no es valida. No se ha podido crear el usuario\a";
			Sleep(2000);
		}
	}
	else{
		if(nombreValido(us1.nombre)){
			cout<<endl<<"El nombre de usuario ya existe. No se ha podido crear el usuario\a";
			Sleep(3000);
		}
		else{
			cout<<endl<<"El nombre ingresado no es valido. No se ha podido crear el usuario\a";
			Sleep(3000);
		}
	}
	system("mode con: cols=70 lines=15");
}

void encriptarcontrasenia(char contrasenia[]){
	char caracteres[] = "abcdefghijklmnñopqrstuvwxyz$#%&ABCDEFGHIJKLMNÑOPQRSTUVWXYZ";
    for(int i=0;i<(int)strlen(contrasenia);i++){
        if(contrasenia[i]<'0' || contrasenia[i]>'9'){
			int j=0;
			while(contrasenia[i] != caracteres[j])
				j++;
			for(int k=0;k<4;k++){
				if(j>=54)
					j-=58;
				else 
					contrasenia[i] = caracteres[j+4];
			}
		}
    }
}
bool nombreValido(char nombre[]){//nombre para crear usuario es valido
	bool esValido=false;
	if((int)strlen(nombre)>0 && (int)strlen(nombre)<=10){
		esValido=true;
		int i=0;
		while(i<(int)strlen(nombre)&&esValido){
			if(nombre[i]==' ')
				esValido=false;
			i++;
		}
	}
	return esValido;
}

bool contraseniaValida(char contrasenia[]){//contraseña para crear usuario es valida
	bool esValida=false;
	int minuscula=0,mayuscula=0,especial=0;
	if((int)strlen(contrasenia)>=8 && (int)strlen(contrasenia)<=12){
		esValida=true;
		int i=0;
		while(i<(int)strlen(contrasenia) && esValida){
			if(contrasenia[i]<'a'&&contrasenia[i]>'z'&&contrasenia[i]<'A'
			   &&contrasenia[i]>'Z'&&contrasenia[i]!='$'&&contrasenia[i]!='#'
			   &&contrasenia[i]!='%'&&contrasenia[i]!='&'){
				esValida=false;
			}
			else{
				if(contrasenia[i]>='a'&&contrasenia[i]<='z')
					minuscula++;
				if(contrasenia[i]>='A'&&contrasenia[i]<='Z')
					mayuscula++;
				if(contrasenia[i]=='$'||contrasenia[i]=='#'||contrasenia[i]=='%'||contrasenia[i]=='&')
					especial++;
			}
			i++;
		}
		if(minuscula!=0&&mayuscula!=0&&especial!=0)
			esValida=true;
		else
			esValida=false;
	}
	return esValida;
}

void ranking(lista &l){
	char entrada;
	bool salir=false;
	do{
		system("cls");
		cout<<"\n\t\t\t      RANKING"<<endl;
		cout<<"\t--------------------------------------------------\n";
		cout<<"\tESCRIBE\t\t\tPara ver:\n\n";
		cout<<"\t  1\t\t-Mejor puntaje por nivel\n\n";
		cout<<"\t  2\t\t-Ranking de usuario\n\n";
		cout<<"\t  3\t\t-Mejor puntaje por usuario y nivel\n\n";
		cout<<"\t  V\t\t-Volver\n\n";
		cin>>entrada;
		if(entrada!='1'&&entrada!='2'&&entrada!='3'&&entrada!='v'&&entrada!='V'){
			cout<<"El valor alfanumerico "<<entrada<<" no es valido \a";
			Sleep(2000);
		}
		else{
			if(entrada=='1')
				mejorPuntajeNivel(l);
			else{
				if(entrada=='2')
					rankingUsuario(l);
				else{
					if(entrada=='3')
						mejorPuntajeNivelUsuario(l);
					else
						salir=true;
				}
			}
		}
	} while(!salir);
}
void mejorPuntajeNivel(lista &l){
	system("mode con: cols=50 lines=15");
	bool salir=false;
	char entrada;
	float maximo1;
	int usuariomaximo1=0;
	float maximo2;
	int usuariomaximo2=0;
	float maximo3;
	int usuariomaximo3=0;
	for(int i=0;i<l.cantidadusuarios;i++){//ordena todas las puntuaciones de cada usuario en cada nivel
		ordenarpuntuaciones(l,i,1);
		ordenarpuntuaciones(l,i,2);
		ordenarpuntuaciones(l,i,3);
	}
	maximo1=l.usuarios[0].rusuario[0].p[0].tiempo;
	maximo2=l.usuarios[0].rusuario[1].p[0].tiempo;
	maximo3=l.usuarios[0].rusuario[2].p[0].tiempo;
	for(int i=1;i<l.cantidadusuarios;i++){//recorre todos los usuarios para encontrar el valor maximo de puntos
		if(maximo1 > l.usuarios[i].rusuario[0].p[0].tiempo){
			maximo1=l.usuarios[i].rusuario[0].p[0].tiempo;
			usuariomaximo1=i;//almacena el usuario
		}
		if(maximo2 > l.usuarios[i].rusuario[1].p[0].tiempo){
			maximo2=l.usuarios[i].rusuario[1].p[0].tiempo;
			usuariomaximo2=i;
		}
		if(maximo3 > l.usuarios[i].rusuario[2].p[0].tiempo){
			maximo3=l.usuarios[i].rusuario[2].p[0].tiempo;
			usuariomaximo3=i;
		}
	}
	do{
		system("cls");
		gotoxy(1,0);
		cout<<"Nivel";
		gotoxy(14,0);
		cout<<"Nombre";
		gotoxy(35,0);
		cout<<"Puntos";
		gotoxy(3,1);
		cout<<"1";
		gotoxy(14,1);
		cout<<l.usuarios[usuariomaximo1].nombre;
		gotoxy(35,1);
		cout<<maximo1;
		gotoxy(3,2);
		cout<<"2";
		gotoxy(14,2);
		cout<<l.usuarios[usuariomaximo2].nombre;
		gotoxy(35,2);
		cout<<maximo2;
		gotoxy(3,3);
		cout<<"3";
		gotoxy(14,3);
		cout<<l.usuarios[usuariomaximo3].nombre;
		gotoxy(35,3);
		cout<<maximo3<<endl<<endl<<endl;
		cout<<"Ingrese 'S' para volver al menu"<<endl;
		cin>>entrada;
		if(entrada=='s' || entrada=='S')
			salir=true;
	}while(!salir);
	system("mode con: cols=70 lines=15");
}

void rankingUsuario(lista &l){
	system("mode con: cols=68 lines=7");
	int n;
	char entrada;
	bool salir=false;
	do{
		system("cls");
		cout<<"CANTIDAD USUARIOS="<<l.cantidadusuarios<<endl<<endl;
		cout<<"INGRESE EL NUMERO DE USUARIOS A VISUALIZAR: ";
		cin>>n;
		if(n>l.cantidadusuarios || n<=0){//n es un valor invalido
			if(n>l.cantidadusuarios){
				cout<<endl<<endl<<"El numero ingresado es mayor a la cantidad de usuarios\a";
				Sleep(3000);
			}
			else{
				cout<<endl<<endl<<"El numero ingresado es menor/igual a 0\a";
				Sleep(3000);
			}
			salir=true;
		}
		else{
			system("mode con: cols=75 lines=55");
			ordenarpganadas(l);
			if(n>50){
				do{
					system("cls");
					gotoxy(1,0);
					cout<<"USUARIO";
					gotoxy(18,0);
					Color(0,2);cout<<"%GANADAS";Color(0,7);
					gotoxy(30,0);
					Color(0,4);cout<<"%PERDIDAS";Color(0,7);
					gotoxy(43,0);
					Color(0,8);cout<<"%ABANDONADAS";Color(0,7);
					for(int i=0;i<50;i++){
						gotoxy(1,i+1);
						cout<<l.usuarios[i].nombre;
						gotoxy(21,i+1);
						cout<<l.usuarios[i].porcentajeganadas;
						gotoxy(33,i+1);
						cout<<porcentajeperdidas(i,l);
						gotoxy(48,i+1);
						cout<<porcentajeabandonadas(i,l);
					}
					cout<<endl<<"Ingrese 'S' o 'D'"<<endl;
					cout<<"S = Volver al menu      D = Pagina siguiente";
					cin>>entrada;
					if(entrada=='d' || entrada=='D'){
						do{
							system("cls");
							for(int i=50;i<n;i++){
								gotoxy(1,i-50);
								cout<<l.usuarios[i].nombre;
								gotoxy(21,i-50);
								cout<<l.usuarios[i].porcentajeganadas;
								gotoxy(33,i-50);
								cout<<porcentajeperdidas(i,l);
								gotoxy(48,i-50);
								cout<<porcentajeabandonadas(i,l);
							}
							cout<<endl<<"Ingrese 'S' o 'A'"<<endl;
							cout<<"S = Volver al menu      A = Pagina anterior";
							cin>>entrada;
						}while(entrada!='s'&& entrada!='S'&& entrada!='a' && entrada!='A');
					}
				}while(entrada!='s'&& entrada!='S');
				
			}
			else{
				do{
					system("cls");
					gotoxy(1,0);
					cout<<"USUARIO";
					gotoxy(18,0);
					Color(0,2);cout<<"%GANADAS";Color(0,7);
					gotoxy(30,0);
					Color(0,4);cout<<"%PERDIDAS";Color(0,7);
					gotoxy(43,0);
					Color(0,8);cout<<"%ABANDONADAS";Color(0,7);
					for(int i=0;i<n;i++){
						gotoxy(1,i+1);
						cout<<l.usuarios[i].nombre;
						gotoxy(21,i+1);
						cout<<l.usuarios[i].porcentajeganadas;
						gotoxy(33,i+1);
						cout<<porcentajeperdidas(i,l);
						gotoxy(48,i+1);
						cout<<porcentajeabandonadas(i,l);
					}
					cout<<endl<<endl<<endl;
					cout<<"Ingrese 'S' para volver al menu"<<endl;
					cin>>entrada;
				}while(entrada!='s'&& entrada!='S');
			}
		}
	}while(!salir && entrada!='s'&& entrada!='S');
	system("mode con: cols=70 lines=15");
}
void ordenarpganadas(lista &l){
	for(int i=0;i<l.cantidadusuarios;i++){//le asigna el porcentaje de ganadas a todos los usuarios
		l.usuarios[i].porcentajeganadas=porcentajepganadas(i,l);
	}
	usuario temporal;
	for (int i = 0;i < l.cantidadusuarios; i++){//ordena de manera descendente los usuario dependiendo el porcentaje de ganadas
		for (int j = 0; j< (l.cantidadusuarios)-1; j++){
			if (l.usuarios[j].porcentajeganadas < l.usuarios[j+1].porcentajeganadas){
				temporal = l.usuarios[j];
				l.usuarios[j] = l.usuarios[j+1]; 
				l.usuarios[j+1] = temporal;
			}
		}
	}
}
float porcentajepganadas(int usuario,lista l){
	int total=0,porganadas=0;
	total=(l.usuarios[usuario].pganadas)+(l.usuarios[usuario].pperdidas)+(l.usuarios[usuario].pabandonadas);//total de partidas
	porganadas=((l.usuarios[usuario].pganadas)*100)/total;//porcentaje
	return porganadas;
}
float porcentajeperdidas(int usuario,lista l){
	int total=0,porperdidas=0;
	total=(l.usuarios[usuario].pganadas)+(l.usuarios[usuario].pperdidas)+(l.usuarios[usuario].pabandonadas);//total de partidas
	porperdidas=((l.usuarios[usuario].pperdidas)*100)/total;//porcentaje
	return porperdidas;
}
float porcentajeabandonadas(int usuario,lista l){
	int total=0,porabandonadas=0;
	total=(l.usuarios[usuario].pganadas)+(l.usuarios[usuario].pperdidas)+(l.usuarios[usuario].pabandonadas);//total de partidas
	porabandonadas=((l.usuarios[usuario].pabandonadas)*100)/total;//porcentaje
	return porabandonadas;
}

void mejorPuntajeNivelUsuario(lista &l){
	system("mode con: cols=75 lines=83");
	mostrarranking(l);
	system("mode con: cols=70 lines=15");

}
void mostrarranking(lista &l){//
	int opcion;
	system("cls");
	for(int i=0;i<l.cantidadusuarios;i++){
		ordenarpuntuaciones(l,i,1);
		ordenarpuntuaciones(l,i,2);
		ordenarpuntuaciones(l,i,3);
	}
	if(l.cantidadusuarios<15)opcion=1;
	else{
		if(l.cantidadusuarios<30)opcion=2;
		else{
			if(l.cantidadusuarios<45)opcion=3;
			else{
				if(l.cantidadusuarios<60)opcion=4;
				else{
					if(l.cantidadusuarios<75)opcion=5;
					else{
						if(l.cantidadusuarios<90)opcion=6;
						else
							opcion=7;
					}
				}
			}
		}
	}
	switch(opcion){
	case 1:{
			char entrada;
			do{
				system("cls");
				cout<<"USUARIO        NIVEL         FECHA        MEJOR PUNTAJE"<<endl;
				cout<<"-------------------------------------------------------"<<endl;
				forswitch(0,l.cantidadusuarios,l);
				cout<<"Ingrese 'S' para volver al menu"<<endl;
				cin>>entrada;
			}while(entrada!='s'&& entrada!='S');
			break;
		}
	case 2:{
			char entrada;
			do{
				system("cls");
				cout<<"USUARIO        NIVEL         FECHA        MEJOR PUNTAJE"<<endl;
				cout<<"-------------------------------------------------------"<<endl;
				forswitch(0,15,l);
				cout<<endl<<"Ingrese 'S' o 'D'"<<endl;
				cout<<"S = Volver al menu      D = Pagina siguiente";
				cin>>entrada;
				if(entrada=='d' || entrada=='D'){
					do{
						system("cls");
						forswitch(15,l.cantidadusuarios,l);
						cout<<endl<<"Ingrese 'S' o 'A'"<<endl;
						cout<<"S = Volver al menu      A = Pagina anterior";
						cin>>entrada;
					}while(entrada!='s' && entrada!='S' && entrada!='a'&& entrada!='A');
				}
			}while(entrada!='s'&& entrada!='S');
			break;
		}
	case 3:{
			bool volver=false;
			char entrada;
			do{
				system("cls");
				cout<<"USUARIO        NIVEL         FECHA        MEJOR PUNTAJE"<<endl;
				cout<<"-------------------------------------------------------"<<endl;
				forswitch(0,15,l);
				cout<<endl<<"Ingrese 'S' o 'D'"<<endl;
				cout<<"S = Volver al menu      D = Pagina siguiente";
				cin>>entrada;
				if(entrada=='d'||entrada=='D'){
						do{
						system("cls");
						forswitch(15,30,l);
						cout<<endl<<"Ingrese 'S' o 'A' o 'D'"<<endl;
						cout<<"S = Volver al menu    A = Pagina anterior    D = Pagina siguiente";
						cin>>entrada;
						if(entrada=='a')volver=true;
						if(entrada=='d'){
							do{
								system("cls");
								forswitch(30,l.cantidadusuarios,l);
								cout<<endl<<"Ingrese 'S' o 'A'"<<endl;
								cout<<"S = Volver al menu      A = Pagina anterior";
								cin>>entrada;
							}while(entrada!='s'&& entrada!='S' && entrada!='a'&& entrada!='A');
						}
					}while(entrada!='s' && entrada!='S' && !volver);
				}
			}while(entrada!='s'&& entrada!='S');
			break;
		}
	case 4:{
			bool volver=false;
			bool volver1=false;
			char entrada;
			do{
				system("cls");
				cout<<"USUARIO        NIVEL         FECHA        MEJOR PUNTAJE"<<endl;
				cout<<"-------------------------------------------------------"<<endl;
				forswitch(0,15,l);
				cout<<endl<<"Ingrese 'S' o 'D'"<<endl;
				cout<<"S = Volver al menu      D = Pagina siguiente";
				cin>>entrada;
				if(entrada=='d'||entrada=='D'){
					do{
					system("cls");
					forswitch(15,30,l);
					cout<<endl<<"Ingrese 'S' o 'A' o 'D'"<<endl;
					cout<<"S = Volver al menu    A = Pagina anterior    D = Pagina siguiente";
					cin>>entrada;
					if(entrada=='a'||entrada=='A')volver=true;
					if(entrada=='d'||entrada=='D'){
						do{
							system("cls");
							forswitch(30,45,l);
							cout<<endl<<"Ingrese 'S' o 'A' o 'D'"<<endl;
							cout<<"S = Volver al menu    A = Pagina anterior    D = Pagina siguiente";
							cin>>entrada;
							if(entrada=='a'||entrada=='A')volver1=true;
							if(entrada=='d'||entrada=='D'){
								do{
									system("cls");
									forswitch(45,l.cantidadusuarios,l);
									cout<<endl<<"Ingrese 'S' o 'A'"<<endl;
									cout<<"S = Volver al menu      A = Pagina anterior";
									cin>>entrada;
								}while(entrada!='s'&& entrada!='S' && entrada!='a'&& entrada!='A');
							}
						}while(entrada!='s'&& entrada!='S' && !volver1);
					}
					}while(entrada!='s'&& entrada!='S' && !volver);
				}
			}while(entrada!='s'&& entrada!='S');
		break;
	}
	case 5:{
			bool volver=false;
			bool volver1=false;
			bool volver2=false;
			char entrada;
			do{
				system("cls");
				cout<<"USUARIO        NIVEL         FECHA        MEJOR PUNTAJE"<<endl;
				cout<<"-------------------------------------------------------"<<endl;
				forswitch(0,15,l);
				cout<<endl<<"Ingrese 'S' o 'D'"<<endl;
				cout<<"S = Volver al menu      D = Pagina siguiente";
				cin>>entrada;
				if(entrada=='d'){
					do{
					system("cls");
					forswitch(15,30,l);
					cout<<endl<<"Ingrese 'S' o 'A' o 'D'"<<endl;
					cout<<"S = Volver al menu    A = Pagina anterior    D = Pagina siguiente";
					cin>>entrada;
					if(entrada=='a'||entrada=='A')volver=true;
					if(entrada=='d'||entrada=='D'){
						do{
							system("cls");
							forswitch(30,45,l);
							cout<<endl<<"Ingrese 'S' o 'A' o 'D'"<<endl;
							cout<<"S = Volver al menu    A = Pagina anterior    D = Pagina siguiente";
							cin>>entrada;
							if(entrada=='a'||entrada=='A')volver1=true;
							if(entrada=='d'||entrada=='D'){
								do{
									system("cls");
									forswitch(45,60,l);
									cout<<endl<<"Ingrese 'S' o 'A' o 'D'"<<endl;
									cout<<"S = Volver al menu    A = Pagina anterior    D = Pagina siguiente";
									cin>>entrada;
									if(entrada=='a'||entrada=='A')volver2=true;
									if(entrada=='d'||entrada=='D'){
										do{
											system("cls");
											forswitch(60,l.cantidadusuarios,l);
											cout<<endl<<"Ingrese 'S' o 'A'"<<endl;
											cout<<"S = Volver al menu      A = Pagina anterior";
											cin>>entrada;
										}while(entrada!='s'&& entrada!='S'&& entrada!='a'&& entrada!='A');
									}
								}while(entrada!='s'&& entrada!='S' && !volver2);
							}
						}while(entrada!='s'&& entrada!='S' && !volver1);
					}
					}while(entrada!='s'&& entrada!='S' && !volver);
				}
			}while(entrada!='s'&& entrada!='S');
		break;
		}
	case 6:{
			bool volver=false;
			bool volver1=false;
			bool volver2=false;
			bool volver3=false;
			char entrada;
			do{
				system("cls");
				cout<<"USUARIO        NIVEL         FECHA        MEJOR PUNTAJE"<<endl;
				cout<<"-------------------------------------------------------"<<endl;
				forswitch(0,15,l);
				cout<<endl<<"Ingrese 'S' o 'D'"<<endl;
				cout<<"S = Volver al menu      D = Pagina siguiente";
				cin>>entrada;
				if(entrada=='d'||entrada=='D'){
					do{
					system("cls");
					forswitch(15,30,l);
					cout<<endl<<"Ingrese 'S' o 'A' o 'D'"<<endl;
					cout<<"S = Volver al menu    A = Pagina anterior    D = Pagina siguiente";
					cin>>entrada;
					if(entrada=='a'||entrada=='A')volver=true;
					if(entrada=='d'||entrada=='D'){
						do{
							system("cls");
							forswitch(30,45,l);
							cout<<endl<<"Ingrese 'S' o 'A' o 'D'"<<endl;
							cout<<"S = Volver al menu    A = Pagina anterior    D = Pagina siguiente";
							cin>>entrada;
							if(entrada=='a'||entrada=='A')volver1=true;
							if(entrada=='d'||entrada=='D'){
								do{
									system("cls");
									forswitch(45,60,l);
									cout<<endl<<"Ingrese 'S' o 'A' o 'D'"<<endl;
									cout<<"S = Volver al menu    A = Pagina anterior    D = Pagina siguiente";
									cin>>entrada;
									if(entrada=='a'||entrada=='A')volver2=true;
									if(entrada=='d'||entrada=='D'){
										do{
											system("cls");
											forswitch(60,75,l);
											cout<<endl<<"Ingrese 'S' o 'A' o 'D'"<<endl;
											cout<<"S = Volver al menu    A = Pagina anterior    D = Pagina siguiente";
											cin>>entrada;
											if(entrada=='a'||entrada=='A')volver3=true;
											if(entrada=='d'||entrada=='D'){
												do{
												system("cls");
												forswitch(75,l.cantidadusuarios,l);
												cout<<endl<<"Ingrese 'S' o 'A'"<<endl;
												cout<<"S = Volver al menu      A = Pagina anterior";
												cin>>entrada;
												}while(entrada!='s'&& entrada!='S'&& entrada!='a'&& entrada!='A');
											}
										}while(entrada!='s'&& entrada!='S'&& !volver3);
									}
								}while(entrada!='s'&& entrada!='S'&& !volver2);
							}
						}while(entrada!='s'&& entrada!='S' && !volver1);
					}
					}while(entrada!='s'&& entrada!='S' && !volver);
				}
			}while(entrada!='s'&& entrada!='S');
		break;
		}
	default:{
			bool volver=false;
			bool volver1=false;
			bool volver2=false;
			bool volver3=false;
			bool volver4=false;
			char entrada;
			do{
				system("cls");
				cout<<"USUARIO        NIVEL         FECHA        MEJOR PUNTAJE"<<endl;
				cout<<"-------------------------------------------------------"<<endl;
				forswitch(0,15,l);
				cout<<endl<<"Ingrese 'S' o 'D'"<<endl;
				cout<<"S = Volver al menu      D = Pagina siguiente";
				cin>>entrada;
				if(entrada=='d'||entrada=='D'){
					do{
					system("cls");
					forswitch(15,30,l);
					cout<<endl<<"Ingrese 'S' o 'A' o 'D'"<<endl;
					cout<<"S = Volver al menu    A = Pagina anterior    D = Pagina siguiente";
					cin>>entrada;
					if(entrada=='a'||entrada=='A')volver=true;
					if(entrada=='d'||entrada=='D'){
						do{
							system("cls");
							forswitch(30,45,l);
							cout<<endl<<"Ingrese 'S' o 'A' o 'D'"<<endl;
							cout<<"S = Volver al menu    A = Pagina anterior    D = Pagina siguiente";
							cin>>entrada;
							if(entrada=='a'||entrada=='A')volver1=true;
							if(entrada=='d'||entrada=='D'){
								do{
									system("cls");
									forswitch(45,60,l);
									cout<<endl<<"Ingrese 'S' o 'A' o 'D'"<<endl;
									cout<<"S = Volver al menu    A = Pagina anterior    D = Pagina siguiente";
									cin>>entrada;
									if(entrada=='a'||entrada=='A')volver2=true;
									if(entrada=='d'||entrada=='D'){
										do{
											system("cls");
											forswitch(60,75,l);
											cout<<endl<<"Ingrese 'S' o 'A' o 'D'"<<endl;
											cout<<"S = Volver al menu    A = Pagina anterior    D = Pagina siguiente";
											cin>>entrada;
											if(entrada=='a'||entrada=='A')volver3=true;
											if(entrada=='d'||entrada=='D'){
												do{
													system("cls");
													forswitch(75,90,l);
													cout<<endl<<"Ingrese 'S' o 'A' o 'D'"<<endl;
													cout<<"S = Volver al menu    A = Pagina anterior    D = Pagina siguiente";
													cin>>entrada;
													if(entrada=='a'||entrada=='A')volver4=true;
													if(entrada=='d'||entrada=='D'){
														do{
															system("cls");
															forswitch(90,l.cantidadusuarios,l);
															cout<<endl<<"Ingrese 'S' o 'A'"<<endl;
															cout<<"S = Volver al menu      A = Pagina anterior";
															cin>>entrada;
														}while(entrada!='s'&& entrada!='S'&& entrada!='a'&& entrada!='A');
													}
												}while(entrada!='s'&& entrada!='S'&& !volver4);
											}
										}while(entrada!='s'&& entrada!='S'&& !volver3);
									}
								}while(entrada!='s'&& entrada!='S' && !volver2);
							}
						}while(entrada!='s'&& entrada!='S' && !volver1);
					}
					}while(entrada!='s'&& entrada!='S' && !volver);
				}
			}while(entrada!='s'&& entrada!='S');
		}
	}
}
//EL ERROR QUE SE PRESENTA CUANDO SE QUIERE MOSTRAR LA FECHA SE ENCUENTRA O EN MOSTRARFECHA O EN EL FORSWITCH
//YA QUE CUANDO GUARDA LA FECHA EN CARGAR PUNTUACIONES, SE GUARDA DE MANERA CORRECTA
//LASTIMOSAMENTE NO PUDIMOS ENCONTRAR EL ERROR, POR LO QUE LA FUNCION MOSTRARANKING NO ACTUA CORRECTAMENTE
//DEJO COMENTADO EL MOSTRARFECHA PARA DEMOSTRAR QUE LO QUE NO FUNCIONA ES ESA FUNCION
//TAMBIEN SOMOS CONCIENTE DE QUE ESTETICAMENTE SUFRE CARENCIAS
void mostrarfecha(lista l,int i,int nivel){
	cout<<l.usuarios[i].rusuario[nivel].p[0].fecha1.dia<<"/";
	cout<<l.usuarios[i].rusuario[nivel].p[0].fecha1.mes<<"/";
	cout<<l.usuarios[i].rusuario[nivel].p[0].fecha1.anio;
}
void forswitch(int inicial,int final,lista &l){
	int acomodar=0;
	for(int i=inicial;i<final;i++){
		ordenarpuntuaciones(l,i,1);//Ordeno las puntuaciones de manera ascendente de cada usuario
		ordenarpuntuaciones(l,i,2);
		ordenarpuntuaciones(l,i,3);
		cout<<l.usuarios[i].nombre;
		cout<<"           1  ";
		mostrarfecha(l,i,0);
		cout<<"   "<<l.usuarios[i].rusuario[0].p[0].tiempo<<endl;
		cout<<"                 2                        ";
		mostrarfecha(l,i,1);
		cout<<l.usuarios[i].rusuario[1].p[0].tiempo<<endl;
		cout<<"                 3                        ";
		mostrarfecha(l,i,2);
		cout<<l.usuarios[i].rusuario[2].p[0].tiempo<<endl;
		cout<<"-------------------------------------------------------"<<endl;
		acomodar++;
	}
}
void menuPrincipal(int numerodeusuario,lista &l){
	system("mode con: cols=69 lines=20");
	char entrada;
	bool salir=false;
	do{ //menú principal
		system("cls"); //limpia la pantalla
		system("color 0F");
		cout<<"Ingrese un numero del 1 al 3 , \"I\" o \"S\"\n\n\n";
		cout<<"                      Selecciona el nivel de juego\n\n";
		cout<<"   Escribe         Nivel            Tablero            Minas\n\n";
		cout<<"      1            Facil              8x8               10\n\n";
		cout<<"      2            Intermedio        16x16              40\n\n";
		cout<<"      3            Dificil           16x30              99\n\n";
		cout<<"      I                      INSTRUCCIONES\n\n";
		cout<<"      S                      CERRAR SESION\n\n";
		cin>>entrada;
		if(entrada!='S' && entrada!='s' && entrada!='1' && entrada!='2' && entrada!='3' && entrada!='i' && entrada!='I'){//Valor no esperado
			cout<<"El valor alfanumerico "<<entrada<<" no es valido \a";
			Sleep(2000);
		}
		else{
			if(entrada=='I' || entrada=='i') //Entrada a las instrucciones
				intrucciones();
			else{
				if(entrada=='1' || entrada=='2' || entrada=='3') //Entrada al nivel
					Jugar(entrada,numerodeusuario,l);
				else{
					do{ //Cerrar Sesión y volver a la pantalla bienvenida
						system("cls");
						gotoxy(13,5);
						cout<<"¿Esta seguro que quiere cerrar sesion?";
						gotoxy(24,7);
						cout<<"Y- Si      C- Cancelar\n\n\n\n\n";
						entrada=cin.get();
					}while(entrada!='y' && entrada!='Y' && entrada!='c' && entrada!='C');
					if(entrada=='y')
						salir=true;
				}
			}
		}
	}while(!salir);
	system("mode con: cols=70 lines=15");
}
void Jugar(char nivel,int numerodeusuario,lista &l){ //Funcion que indica segun el nivel escogido, con cuantas filas y columnas se va a jugar
	int FILAS,COLUMNAS;
	switch(nivel){
		case '1':{
			system("mode con: cols=100 lines=35");
			FILAS=8;
			COLUMNAS=8;
			Juego(FILAS,COLUMNAS,numerodeusuario,l);break;
		}
		case '2':{
			FILAS=16;
			COLUMNAS=16;
			system("mode con: cols=150 lines=50");
			Juego(FILAS,COLUMNAS,numerodeusuario,l);break;
		}
		default:{
			FILAS=16;
			COLUMNAS=30;
			system("mode con: cols=195 lines=50");
			Juego(FILAS,COLUMNAS,numerodeusuario,l);
		}
	}
}
void Juego(int FILAS,int COLUMNAS,int numerodeusuario,lista &l){//Función que lleva a cabo todo lo relacionado al juego y el tablero
	char ciega[FILAS1][COLUMNAS1],usuario[FILAS1][COLUMNAS1];
	for(int i=0;i<FILAS;i++){//Llena las matrices con valores
		for(int j=0;j<COLUMNAS;j++){
			usuario[i][j]=' ';
			ciega[i][j]='0';
		}
	}
	minasAleatorias(ciega,COLUMNAS);
	celdasVecinas(ciega,FILAS,COLUMNAS);
	int contadorgana=0,fila,columna,senecesita,cont=0;
	char accion;
	bool ganopierde=false,perdio=false,gano=false,continuar,ACCION,salio=false;
	clock_t t;
	t=clock();//toma la hora en ese instante y lo guarda en la variable
	do{
		system("cls");
		cout<<"FILAS deben ser valores del 1 al "<<FILAS<<endl;
		cout<<"COLUMNAS deben ser valores del 1 al "<<COLUMNAS<<endl;
		cout<<"ACCION debe ser la letra \"M\" / \"D\" / \"C\" / \"S\""<<endl;
		gotoxy(COLUMNAS*4+9,8);
		cout<<"M= Marcar/Desmarcar";
		gotoxy(COLUMNAS*4+9,10);
		cout<<"D= Descubrir";
		gotoxy(COLUMNAS*4+9,12);
		cout<<"C= Cancelar jugada";
		gotoxy(COLUMNAS*4+9,14);
		cout<<"S= Salir del juego";
		gotoxy(0,4);
		encabezadoColumnas(COLUMNAS);
		encabezadoFilas(usuario,FILAS,COLUMNAS);
		cout<<endl;
		cout<<"Ingrese la fila: ";
		do {
			continuar = false;
			cin.clear();//Para deshacernos de la bandera de error.
			if(cont > 0) cin.ignore(1024, '\n');//Ya que la entrada de error queda "guardada", entonces cuando intente obtener una nueva entrada, leera la misma y fallara. 
			cin>>fila;
			cont++;
			if((cin.fail() && cin.rdstate()) || fila>FILAS || fila<1){//Si el ultimo cin fallo, retorna true, y rdstate retorna true si el estado de flujo es correcto.
				cout<<"\nEl valor ingresado no esta dentro del rango\n"<<"Por favor ingrese otra posicion";
				continuar = true;
				if(COLUMNAS==8){
					gotoxy(17,23);
					Sleep(1200);
					for(int c=0;c<8;c++){
						cout<<"                                             \n";
					}
					gotoxy(17,23);
				}else{
					gotoxy(17,39);
					Sleep(1200);
					for(int c=0;c<7;c++){
						cout<<"                                             \n";
					}
					gotoxy(17,39);
				}
			}
		} while (continuar);
		cout<<"\nIngrese la columna: ";
		do {
			continuar = false;
			cin.clear();//Para deshacernos de la bandera de error.
			if(cont > 0) cin.ignore(1024, '\n');//Ya que la entrada de error queda "guardada", entonces cuando intente obtener una nueva entrada, leera la misma y fallara.
			cin>>columna;
			cont++;
			if((cin.fail() && cin.rdstate()) || columna>COLUMNAS || columna<1){//Si el ultimo cin fallo, retorna true, y rdstate retorna true si el estado de flujo es correcto.
				cout<<"\nEl valor ingresado no esta dentro del rango\n"<<"Por favor ingrese otra posicion\n\n";
				continuar = true;
				if(COLUMNAS==8){
					gotoxy(20,25);
					Sleep(1200);
					for(int c=0;c<8;c++){
						cout<<"                                             \n";
					}
					gotoxy(20,25);
				}else{
					gotoxy(20,41);
					Sleep(1200);
					for(int c=0;c<7;c++){
						cout<<"                                             \n";
					}
					gotoxy(20,41);
				}
			}
		} while (continuar);
		do{
			ACCION=true;
			cout<<"\nIngrese la accion: ";
			cin>>accion;
			if(accion=='D' || accion=='d'){
				if(usuario[fila-1][columna-1]!=' '){
					if(usuario[fila-1][columna-1]=='M'){//Se fija si esta marcada
						cout<<endl<<"La celda ya ha sido marcada."<<endl;
						cout<<"Por favor ingrese otra posición..."<<endl;
						Sleep(1200);
					}
					else{//se fija si ya la descubrieron
						cout<<endl<<"La celda ya ha sido descubierta."<<endl;
						cout<<"Por favor ingrese otra posicion...";
						Sleep(1200);
					}
				}
				else{
					mostrarCasilla(fila,columna,usuario,ciega);
					contadorgana++;
					if(ciega[fila-1][columna-1]=='0')
						cerosCercanos(usuario,ciega,fila-1,columna-1,FILAS,COLUMNAS,contadorgana);
				}
			}
			else{
				if(accion=='M'|| accion=='m'){
					if(usuario[fila-1][columna-1]!=' ' && usuario[fila-1][columna-1]!='M'){//Se fija si ya la descubrieron
						cout<<endl<<"La celda ya ha sido descubierta."<<endl;
						cout<<"Por favor ingrese otra posicion..."<<endl;
						Sleep(1200);
					}
					else 
						marcarDesmarcar(usuario,fila,columna);
				}else if(accion!='s' && accion!='S' && accion!='c' && accion!='C'){//Si es una letra que no se espera
					cout<<endl<<"La accion no es correcta\n"<<"Por favor ingrese otra posicion\n\n";
					Sleep(1200);
					ACCION=false;
					if(COLUMNAS==8){
						gotoxy(0,26);
						for(int c=0;c<7;c++)cout<<"                                  \n";
						gotoxy(0,26);
					}else {
						gotoxy(0,42);
						for(int c=0;c<7;c++)cout<<"                                  \n";
						gotoxy(0,42);
					}
				}
			}
		}while(!ACCION);
		if(usuario[fila-1][columna-1]==MINA){//Pierde partida
			perdio=true;
			ganopierde=true;
		}
		if(COLUMNAS==8)senecesita=54; //Cantidad de movimientos que se necesitan para ganar=FILAS*COLUMNAS-cantidad de minas
		if(COLUMNAS==16)senecesita=216;
		if(COLUMNAS==30)senecesita=381;
		if(contadorgana>=senecesita){//Gana la partida
			t=clock()-t; //t Toma el valor de la hora actual menos su valor anterior
			ganopierde=true;
			gano=true;
		}
		if(accion=='s' || accion=='S'){
			system("mode con: cols=69 lines=20");
			do{ //Salir de la partida de juego
				system("cls");
				gotoxy(10,5);
				cout<<"¿Esta seguro que quiere volver al menu principal?";
				gotoxy(12,10);
				cout<<"En caso de aceptar perdera todo su progreso...";			
				gotoxy(24,7);
				cout<<"Y- Si      C- Cancelar\n\n\n\n\n";
				accion=cin.get();
			}while(accion!='y' && accion!='Y' && accion!='c' && accion!='C');
			if(accion=='y' || accion=='Y'){
				salio=true;
				l.usuarios[numerodeusuario].pabandonadas++;
				guardarlista(l);
			}
			else{
				switch(COLUMNAS){
				case 8:system("mode con: cols=100 lines=35");break;
				case 16:system("mode con: cols=150 lines=50");break;
				default:system("mode con: cols=195 lines=50");
				}
			}
		}
	}while(ganopierde==false && !salio);
	if(perdio==true){//Si salio del do while porque perdio
		l.usuarios[numerodeusuario].pperdidas++;
		char salida;
		guardarlista(l);
		do{
			system("cls");
			//cout<<numerodeusuario;
			mostrarMinas(ciega,usuario,FILAS,COLUMNAS);
			system("color CF");
			gotoxy(COLUMNAS*4+9,3);
			cout<<" _____ _____ _____ ____  _____ _____ _____ _____ ";
			gotoxy(COLUMNAS*4+9,4);
			cout<<"|  _  |   __| __  |     |     |   __|_   _|   __|";
			gotoxy(COLUMNAS*4+9,5);
			cout<<"|   __|   __|    -|  |  |-   -|__   | | | |   __|";
			gotoxy(COLUMNAS*4+9,6);
			cout<<"|__|  |_____|__|__|____/|_____|_____| |_| |_____|";
			gotoxy(COLUMNAS*4+14,11);
			cout<<"Presiona \"S\" para regresar al menu...";
			for(int i=0;i<FILAS*2;i++){
				cout<<endl;
			}
			cin>>salida;
		}while(salida!='s' && salida!='S');
	}
	else{
		if(gano==true){//Si salio del do while porque gano
			int minutos,segundos;
			int nivel;
			if(COLUMNAS==8)
				nivel=1;
			else{
				if(COLUMNAS==16)
					nivel=2;
				else
					nivel=3;
			}
			l.usuarios[numerodeusuario].pganadas++;
			cargarpuntuacion(l,numerodeusuario,t,nivel);
			char salida;
			guardarlista(l);
			do{
				system("cls");
				encabezadoColumnas(COLUMNAS);
				encabezadoFilas(usuario,FILAS,COLUMNAS);
				system("color AF");
				gotoxy(COLUMNAS*4+7,5);
				cout<<" _______ _______ _______ _______ _______ _______ _______ ";
				gotoxy(COLUMNAS*4+7,6);
				cout<<"|     __|   _   |    |  |   _   |     __|_     _|    ___|";
				gotoxy(COLUMNAS*4+7,7);
				cout<<"|    |  |       |       |       |__     | |   | |    ___|";
				gotoxy(COLUMNAS*4+7,8);
				cout<<"|_______|___|___|__|____|___|___|_______| |___| |_______|";
				minutos=(float(t)/CLOCKS_PER_SEC)/60;
				segundos=(int)(float(t)/CLOCKS_PER_SEC)%60;
				if(minutos == 0){
					gotoxy(COLUMNAS*4+7,10);
					cout<<"SU TIEMPO ES DE ";Color(10,0);cout<<segundos;Color(10,15);cout<<" SEGUNDOS";
				}
				else{
					if(minutos<10){
						if(segundos>=10){
							gotoxy(COLUMNAS*4+7,10);
							cout<<"SU TIEMPO ES DE ";Color(10,0);cout<<"0"<<minutos<<":"<<segundos;Color(10,15);cout<<" MINUTOS";
						}
						else{
							gotoxy(COLUMNAS*4+7,10);
							cout<<"SU TIEMPO ES DE ";Color(10,0);cout<<"0"<<minutos<<":0"<<segundos;Color(10,15);cout<<" MINUTOS";
						}
					}
					else{
						if(segundos>=10){
							gotoxy(COLUMNAS*4+7,10);
							cout<<"SU TIEMPO ES DE ";Color(10,0);cout<<minutos<<":"<<segundos;Color(10,15);cout<<" MINUTOS";
						}
						else{
							gotoxy(COLUMNAS*4+7,10);
							cout<<"SU TIEMPO ES DE ";Color(10,0);cout<<"0"<<minutos<<":0"<<segundos;Color(10,15);cout<<" MINUTOS";
						}
					}
				}
				gotoxy(COLUMNAS*4+7,12);
				cout<<"Presiona \"S\" para regresar al menu...";
				for(int i=0;i<FILAS*2;i++){
					cout<<endl;
				}
				cin>>salida;
			} while(salida!='s' && salida!='S');
		}
	}
	system("mode con: cols=69 lines=20");
}
void cargarpuntuacion(lista &l,int numerodeusuario,float nuevospuntos,int nivel){
	time_t now=time(0);
	tm * ltm=localtime(&now);
	int tiempofinal=(int)(float(nuevospuntos)/CLOCKS_PER_SEC);
	
	ordenarpuntuaciones(l,numerodeusuario,nivel);
	//Al ordenar las puntuaciones, se que el valor mas grande va a quedar en la ultima posicion
	//Comparo el nuevo tiempo con la ultima posicion
	if(tiempofinal < l.usuarios[numerodeusuario].rusuario[nivel-1].p[9].tiempo){
		l.usuarios[numerodeusuario].rusuario[nivel-1].p[9].tiempo=tiempofinal;
		l.usuarios[numerodeusuario].rusuario[nivel-1].p[9].fecha1.dia=ltm->tm_mday;
		l.usuarios[numerodeusuario].rusuario[nivel-1].p[9].fecha1.mes=1 + ltm->tm_mon;
		l.usuarios[numerodeusuario].rusuario[nivel-1].p[9].fecha1.anio=1900 + ltm->tm_year;
	}
}

void minasAleatorias(char ciega[FILAS1][COLUMNAS1],int COLUMNAS){//Según el nivel va a  recorrer el for hasta determinado numero de minas
	int filarand,columnarand;
	srand(time(NULL));
	switch(COLUMNAS){
	case 8:
		for(int i=0;i<10;i++){
			filarand=rand()%8;
			columnarand=rand()%8;
			if(ciega[filarand][columnarand]==MINA)
				i--;
			else
				ciega[filarand][columnarand]=MINA;
		}
		break;
	case 16:
		for(int i=0;i<40;i++){
			filarand=rand()%16;
			columnarand=rand()%16;
			if(ciega[filarand][columnarand]==MINA)
				i--;
			else
				ciega[filarand][columnarand]=MINA;
		}
		break;
	default:
		for(int i=0;i<99;i++){
			filarand=rand()%16;
			columnarand=rand()%30;
			if(ciega[filarand][columnarand]==MINA)
				i--;
			else
				ciega[filarand][columnarand]=MINA;
		}
	}
}
void celdasVecinas(char ciega[FILAS1][COLUMNAS1],int FILAS,int COLUMNAS){//Recorre la matriz ciega y cuando se encuentra una mina
	int filaInicial,filaFinal,columnaInicial,columnaFinal;				 //dependiendo su posición recorre las celdas adyacentes, y las que no sean minas le suma 1 a su valor
	for(int i=0;i<FILAS;i++){
		for(int j=0;j<COLUMNAS;j++){
			if(ciega[i][j]==MINA){
				if(i==0)filaInicial=i;
				else filaInicial=i-1;
				if(j==0)columnaInicial=j;
				else columnaInicial=j-1;
				if(i==FILAS-1)filaFinal=i;
				else filaFinal=i+1;
				if(j==COLUMNAS-1)columnaFinal=j;
				else columnaFinal=j+1;
				for(int k=filaInicial;k<=filaFinal;k++){
					for(int l=columnaInicial;l<=columnaFinal;l++){
						if(ciega[k][l]!=MINA)
							ciega[k][l]+=1;
					}
				}
			}
		}
	}
}
void encabezadoColumnas(int COLUMNAS){//Muestra el numero de columnas(encabezado)
	cout<<"    1";
	for(int i=1;i<COLUMNAS;i++){
		if(i<=9)
			cout<<"   "<<i+1;
		else
			cout<<"  "<<i+1;
	}
	cout<<endl;
}
void separadorFilas(int COLUMNAS){//Divide las Filas
	cout<<"  ";
	for(int i=0;i<COLUMNAS;i++){
		cout<<"+---";
	}
	cout<<"+";
}
void encabezadoFilas(char usuario[FILAS1][COLUMNAS1],int FILAS,int COLUMNAS){
	separadorFilas(COLUMNAS);
	for(int i=0;i<FILAS;i++){
		cout<<endl<<i+1;
		for(int j=0;j<COLUMNAS;j++){
			if(i<9){
				switch(usuario[i][j]){//Selecciona el color dependiendo su valor
				case '0':cout<<" | ";Color(0,12);cout<</*" "*/usuario[i][j];Color(0, 7);break;
				case '1':cout<<" | ";Color(0,10);cout<<usuario[i][j];Color(0, 7);break;
				case '2':cout<<" | ";Color(0,9);cout<<usuario[i][j];Color(0, 7);break;
				case '3':cout<<" | ";Color(0,5);cout<<usuario[i][j];Color(0, 7);break;
				case '4':cout<<" | ";Color(0,4);cout<<usuario[i][j];Color(0, 7);break;
				case '5':cout<<" | ";Color(0,2);cout<<usuario[i][j];Color(0, 7);break;
				case '6':cout<<" | ";Color(0,3);cout<<usuario[i][j];Color(0, 7);break;
				case '7':cout<<" | ";Color(0,6);cout<<usuario[i][j];Color(0, 7);break;
				case '8':cout<<" | ";Color(0,7);cout<<usuario[i][j];Color(0, 7);break;
				default:cout<<" | "<<usuario[i][j];
				}
			}
			else{//Cuando el numero de fila posee 2 digitos hay q modificar el patron en su primera columna
				if(j==0){
					switch(usuario[i][j]){
					case '0':cout<<"| ";Color(0,12);cout<<usuario[i][j];Color(0, 7);break;
					case '1':cout<<"| ";Color(0,10);cout<<usuario[i][j];Color(0, 7);break;
					case '2':cout<<"| ";Color(0,9);cout<<usuario[i][j];Color(0, 7);break;
					case '3':cout<<"| ";Color(0,5);cout<<usuario[i][j];Color(0, 7);break;
					case '4':cout<<"| ";Color(0,4);cout<<usuario[i][j];Color(0, 7);break;
					case '5':cout<<"| ";Color(0,2);cout<<usuario[i][j];Color(0, 7);break;
					case '6':cout<<"| ";Color(0,3);cout<<usuario[i][j];Color(0, 7);break;
					case '7':cout<<"| ";Color(0,6);cout<<usuario[i][j];Color(0, 7);break;
					case '8':cout<<"| ";Color(0,7);cout<<usuario[i][j];Color(0, 7);break;
					default:cout<<"| "<<usuario[i][j];
					}
				}
				else{
					switch(usuario[i][j]){
					case '0':cout<<" | ";Color(0,12);cout<<usuario[i][j];Color(0, 7);break;
					case '1':cout<<" | ";Color(0,10);cout<<usuario[i][j];Color(0, 7);break;
					case '2':cout<<" | ";Color(0,9);cout<<usuario[i][j];Color(0, 7);break;
					case '3':cout<<" | ";Color(0,5);cout<<usuario[i][j];Color(0, 7);break;
					case '4':cout<<" | ";Color(0,4);cout<<usuario[i][j];Color(0, 7);break;
					case '5':cout<<" | ";Color(0,2);cout<<usuario[i][j];Color(0, 7);break;
					case '6':cout<<" | ";Color(0,3);cout<<usuario[i][j];Color(0, 7);break;
					case '7':cout<<" | ";Color(0,6);cout<<usuario[i][j];Color(0, 7);break;
					case '8':cout<<" | ";Color(0,7);cout<<usuario[i][j];Color(0, 7);break;
					default:cout<<" | "<<usuario[i][j];
					}
				}
			}
		}
		cout<<" |"<<endl;
		separadorFilas(COLUMNAS);
	}
	cout<<endl;
}
void mostrarCasilla(int fila,int columna,char usuario[FILAS1][COLUMNAS1],char ciega[FILAS1][COLUMNAS1]){//Segun la casilla indicada por el usuario, la matriz que se visualiza toma el valor de la ciega
	fila=fila-1;
	columna=columna-1;
	usuario[fila][columna]=ciega[fila][columna];
}
void marcarDesmarcar(char usuario[FILAS1][COLUMNAS1],int fila,int columna){//Marcar o desmarcar cuando el usuario oprima la acción M
	if(usuario[fila-1][columna-1]=='M')
		usuario[fila-1][columna-1]=' ';
	else
		usuario[fila-1][columna-1]='M';
}
void mostrarMinas(char ciega[FILAS1][COLUMNAS1],char usuario[FILAS1][COLUMNAS1],int FILAS, int COLUMNAS){//Recorre la matriz ciega y donde se encuentra una X pasa esa posicion a la matriz que se ve
	for(int i=0;i<FILAS;i++){
		for(int j=0;j<COLUMNAS;j++){
			if(ciega[i][j]==MINA)
				usuario[i][j]=ciega[i][j];
		}
	}
	encabezadoColumnas(COLUMNAS);
	encabezadoFilas(usuario,FILAS,COLUMNAS);
}
void intrucciones(){//Menu de instrucciones
	char letra;
	do{
		system("cls");
		system("mode con: cols=100 lines=25");
		cout<<" El juego consiste en despejar todas las celdas del tablero que no contengan una mina."<<endl<<endl;
		cout<<" Usted tendra que seleccionar la fila, columna y una accion."<<endl;
		cout<<" Las acciones posibles son:"<<endl;
		cout<<" D= Sirve para despejar la celda."<<endl;
		cout<<" M= Sirve para indicar donde cree que hay una mina o para sacar la marca que usted ha puesto."<<endl;
		cout<<" C= Sirve para reingresar otra posicion antes de ejecutar una accion"<<endl<<endl;
		cout<<" Cada celda tendra un numero que indica las minas que tiene alrededor."<<endl<<endl;
		cout<<" Restricciones:"<<endl;
		cout<<" 1) Solo puede descubrir celdas que esten en blanco y dentro del rango del tablero."<<endl;
		cout<<" 2) Solo puede marcar celdas que esten en blanco."<<endl;
		cout<<" 3) Solo puede desmarcar celdas que esten marcadas."<<endl<<endl;
		cout<<" Al finalizar el juego se le mostrara su tiempo."<<endl;
		cout<<"            ¡¡¡INTENTA SUPERARLO!!!"<<endl<<endl;
		cout<<"Ingrese \"S\" para regresar al menu..."<<endl;
		cin>>letra;
	}while(letra!='s' && letra !='S');
	system("mode con: cols=69 lines=20");
}
void Color(int fondo, int letra){ // Función para cambiar el color del fondo y/o pantalla		
	int X= letra + (fondo * 16);		
	SetConsoleTextAttribute(GetStdHandle (STD_OUTPUT_HANDLE),X);
}
void cerosCercanos(char usuario[FILAS1][COLUMNAS1],char ciega[FILAS1][COLUMNAS1],int fila0,int columna0,int FILAS, int COLUMNAS, int &contadorgana){//Función que muestra las casillas adyacentes a una de valor=0
	int filaInicial,filaFinal,columnaInicial,columnaFinal;
	if(fila0==0)filaInicial=fila0;
	else filaInicial=fila0-1;
	if(columna0==0)columnaInicial=columna0;
	else columnaInicial=columna0-1;
	if(fila0==FILAS-1)filaFinal=fila0;
	else filaFinal=fila0+1;
	if(columna0==COLUMNAS-1)columnaFinal=columna0;
	else columnaFinal=columna0+1;
	for(int i=filaInicial;i<=filaFinal;i++){
		for(int j=columnaInicial;j<=columnaFinal;j++){
			if(usuario[i][j]==' ' && ciega[i][j]!=MINA){
				mostrarCasilla(i+1,j+1,usuario,ciega);
				contadorgana++;
				if(usuario[i][j]=='0')
					cerosCercanos(usuario,ciega,i,j,FILAS,COLUMNAS,contadorgana);
			}
		}
	}
}
void despedida(){//Mensaje que se muestra si se acepta la opcion de salida
	system("cls");
	Color(0,3);
	for(int i=0;i<7;i++){
		gotoxy(15,i+5);
		for(int j=0;j<39;j++){
			if(i==0 || i==6){
				if(j==0||j==38)
					cout<<"+";
				else{
					if(j%2==0)
						cout<<"-";
					else
						cout<<" ";
				}
			}
			if(i==1 || i==3 || i==5){
				if(j==0||j==38)
					cout<<"|";
				else
					cout<<" ";
			}
		}
		cout<<endl;
	}
	gotoxy(15,7);
	cout<<"|";
	gotoxy(27,7);
	cout<<"¡¡ A D I O S !!";
	gotoxy(53,7);
	cout<<"|";
	gotoxy(15,9);
	cout<<"|";
	gotoxy(24,9);
	cout<<"ESPERO VUELVAS PRONTO";
	gotoxy(53,9);
	cout<<"|";
	gotoxy(0,11);
	Sleep(3000);
	system("cls");
	Color(0,7);
}
	

/*	+ - - - - - - - - - - - - - - - - - - +
	|                                     |
	|             ¡¡A D I O S!!           |  
	|                                     |
	|        ESPERO VUELVAS PRONTO...     |
	|                                     |
	+ - - - - - - - - - - - - - - - - - - +

	  1   2   3	  4	  5	  6	  7   8   9   10  11  12  13  14  15  16
	+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
  1 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
	+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
  2 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
	+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
  3 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
	+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
  4 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
	+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
  5 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
	+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
  6 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
	+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
  7 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
	+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
  8 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
	+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
  9 |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
	+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
  10|   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
	+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
  11|   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |   |
	+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+---+
	*/
