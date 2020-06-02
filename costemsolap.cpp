/********************************************************************************\
 * Programación 2. Trabajo Obligatorio
 * Autor: Javier Pardos Blesa
 * Ultima revisión: 2 de Junio de 2020
 * Resumen: Programa costemsolap.cpp que es el programa principal desde el que 
 *          se ejecuta el proyecto
\********************************************************************************/
#include "maxsolape.hpp"

using namespace std;

void probarFB(double intervalos [N][2], int cantidad){

	tpSolape solucion;

	solucion = maxSolFBruta(intervalos, cantidad);

	cout << "El solape de los intervalos es " << solucion.solape << endl;

}

void probarMS(double intervalos [N][2], int cantidad, int inicio, int fin){

	tpInter inters [N];
	crearvind(intervalos, inters, cantidad);
	
	cout << "---- SIN ORDENAR ----" << endl;
	for(int i=0; i<=4; i++){
		cout << "{ind: " << inters[i].ind <<", ini: " << inters[i].ini << ", fin: "<< inters[i].fin << "}" << endl;
	}

	mergesortIndInters(inters, inicio, fin);

	cout << "---- ORDENADOS ----" << endl;
	for(int i=0; i<=4; i++){
		cout << "{ind: " << inters[i].ind <<", ini: " << inters[i].ini << ", fin: "<< inters[i].fin << "}" << endl;
	}

}

int main(){

	//Intervalos para pruebas
	double intervalos [N][2] = { {1.5, 8.0}, {0.0, 4.5}, {2.0, 4.0}, {1.0, 6.0}, {3.5, 7.0} };

	//probarFB(intervalos, 5);	

	probarMS(intervalos, 5, 0, 4);

	return 0;
}