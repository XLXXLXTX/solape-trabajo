/********************************************************************************\
 * Programación 2. Trabajo Obligatorio
 * Autor: Javier Pardos Blesa
 * Ultima revisión: 2 de Junio de 2020
 * Resumen: Programa costemsolap.cpp que es el programa principal desde el que 
 *          se ejecuta el proyecto
\********************************************************************************/
#include <cstring>

#include "maxsolape.hpp"

using namespace std;

void generarIntervalosAleatorios (double matrizDatos[][2], int n){

	srand (time(NULL));

	int numeroIntervalos = n; 

	double matrizIntervalos[numeroIntervalos][2];

	for(int i=0; i<numeroIntervalos; i++){
		
		double a1 = ( (rand() % 1001) ) / 10.0; 
		double a2 = ( (rand() % 1001) ) / 10.0;
		
		matrizDatos[i][0] = min(a1, a2);
		matrizDatos[i][1] = max(a1, a2);
	}
}


void crearGrafica (const char nombrefichero [], const char nombreSalida []){
	
	char instPt1 [] = "gnuplot -e \"set terminal gif; set style data lines; plot '";
	char instPt2 [] =  "'\"> ";

	char comando [250];

	strcpy(comando, instPt1);
	strcat(comando, nombrefichero);
	strcat(comando, instPt2);
 	strcat(comando, nombreSalida);

	system(comando);
}


void probarFB(double intervalos [N][2], int cantidad){

	tpSolape solucion;

	solucion = maxSolFBruta(intervalos, cantidad);

	crearGrafica(NOMBRE_FICHERO_FB, NOMBRE_SALIDA_FB);

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

/*
 *
void probarDyV(double intervalos [N][2], int cantidad, int inicio, int fin){

	tpInter inters [N];
	crearvind(intervalos, inters, cantidad);

	tpSolape solapeDyV = maxSolDyV(inters, inicio, fin);

	cout << "El solape de los intervalos es " << solapeDyV.solape << " | interA: " << solapeDyV.interA << " interB: " << solapeDyV.interB << endl;

}
*/


int main(){

	//Intervalos para pruebas
	//double intervalos [N][2] = { {1.5, 8.0}, {0.0, 4.5}, {2.0, 4.0}, {1.0, 6.0}, {3.5, 7.0} };

	double intervalos [N][2];
	generarIntervalosAleatorios(intervalos, 4000);
	
	probarFB(intervalos,4000);	

	//probarMS(intervalos, 5, 0, 4);

	//probarDyV(intervalos, 5, 0, 4);

	return 0;
}