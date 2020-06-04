/********************************************************************************\
 * Programación 2. Trabajo Obligatorio
 * Autor: Javier Pardos Blesa
 * Ultima revisión: 2 de Junio de 2020
 * Resumen: Programa costemsolap.cpp que es el programa principal desde el que 
 *          se ejecuta el proyecto
\********************************************************************************/
#include <cstring>
#include <fstream>

#include "maxsolape.hpp"

const int NUM_CONJUNTOS = 4000;
const int MIN_CONJUNTO = 100;
const int MAX_CONJUNTO = 4000;

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

void analisisDyV(double conjuntoIntervalos[N][2], int sizeConjunto, ofstream& ficheroDyV, int numConjunto){

	tpInter indinters[sizeConjunto];
			
	crearvind(conjuntoIntervalos, indinters, sizeConjunto);

	clock_t ticksRelojInicioDYV = clock();

	maxSolDyV(indinters, 0, sizeConjunto-1);

	clock_t ticksRelojFinalDYV = clock();

	double diferenciaDYV = ticksRelojFinalDYV - ticksRelojInicioDYV;
	double tiempoTotalConjuntoDYV = diferenciaDYV / ( CLOCKS_PER_SEC / 1000);

	ficheroDyV << numConjunto << " " << tiempoTotalConjuntoDYV << endl;
}


void analisisFB(double conjuntoIntervalos[N][2], int sizeConjunto, ofstream& ficheroFB, int numConjunto){

	clock_t ticksRelojInicioFB = clock();

	maxSolFBruta(conjuntoIntervalos, sizeConjunto);

	clock_t ticksRelojFinalFB = clock();

	double diferenciaFB = ticksRelojFinalFB - ticksRelojInicioFB;
	double tiempoTotalConjuntoFB = diferenciaFB / ( CLOCKS_PER_SEC / 1000);

	ficheroFB << numConjunto << " " << tiempoTotalConjuntoFB << endl;
}


int main(){

	clock_t ticksRelojInicioMain = clock();

	ofstream ficheroFB(NOMBRE_FICHERO_FB);
	ofstream ficheroDyV(NOMBRE_FICHERO_DYV);

	if( (ficheroFB.is_open()) && (ficheroDyV.is_open()) ){

		srand (time(NULL));

		int sizeConjunto = 100;

		for(int i=1; i<= NUM_CONJUNTOS; i++){

			double conjuntoIntervalos [sizeConjunto][2];

			generarIntervalosAleatorios(conjuntoIntervalos, sizeConjunto);

			//-------ANALISIS FB-------//
			analisisFB(conjuntoIntervalos, sizeConjunto, ficheroFB, i);

			//-------ANALISIS DYV-------//
			analisisDyV(conjuntoIntervalos, sizeConjunto, ficheroDyV, i);
			
			sizeConjunto++;
		}

		ficheroFB.close();
		ficheroDyV.close();

		crearGrafica(NOMBRE_FICHERO_FB, NOMBRE_SALIDA_FB);
		crearGrafica(NOMBRE_FICHERO_DYV, NOMBRE_SALIDA_DYV);


	}else{
		cerr << "ERROR: No se ha podido abrir alguno de los archivos: " << NOMBRE_FICHERO_FB << " o " << NOMBRE_FICHERO_DYV;
	}

	ficheroFB.close();
	ficheroDyV.close();

	clock_t ticksRelojFinalMain = clock();

	double diferenciaMain = ticksRelojFinalMain - ticksRelojInicioMain;
	double tiempoTotalConjuntoMain = diferenciaMain / ( CLOCKS_PER_SEC / 1000);

	cout << "El programa ha tardado " << tiempoTotalConjuntoMain/60000 << " minutos en ejecutarse." << endl;

	return 0;
}