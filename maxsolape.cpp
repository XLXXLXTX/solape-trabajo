/********************************************************************************\
 * Programación 2. Trabajo Obligatorio
 * Autor: Javier Pardos Blesa
 * Ultima revisión: 2 de Junio de 2020
 * Resumen: Programa maxsolape.cpp que es el archivo donde se construyen los metodos  
 *          que se definen en maxsolape.hpp
\********************************************************************************/
#include "maxsolape.hpp"

using namespace std;


tpSolape calcularSolape(tpInter intervalo1, tpInter intervalo2){
	tpSolape solape; 
	solape.interA = intervalo1.ind;
	solape.interB = intervalo2.ind;

	double minimo = min(intervalo1.fin, intervalo2.fin);
	double maximo = max(intervalo1.ini, intervalo2.ini);

	double diferencia = minimo - maximo;

	if(diferencia > 0){
		solape.solape = diferencia;
	}else{
		solape.solape = 0;
	}

	return solape;
}

tpSolape maxSolFBruta(double inters[N][2], int n){
	
	tpSolape intervaloSolapamiento;
	intervaloSolapamiento.solape = 0;

	for(int i=0; i<n; i++){

		tpInter intervalo1;
		intervalo1.ind = i;
		intervalo1.ini = inters[i][0];	//a1
		intervalo1.fin = inters[i][1];	//b1
		
		for(int j=0; j<n; j++){

			if(i != j){

				tpInter intervalo2;
				intervalo2.ind = j;
				intervalo2.ini = inters[j][0];	//a2
				intervalo2.fin = inters[j][1];	//b2

				tpSolape solapeTemp = calcularSolape(intervalo1, intervalo2);
				
				if(solapeTemp.solape > intervaloSolapamiento.solape){
					intervaloSolapamiento = solapeTemp;
				}
			}
			
		}

	}

	return intervaloSolapamiento;
}

/*
void crearvind(double inters[N][2], tpInter indinters[N], int n){

}
*/

/*
void mergesortIndInters(tpInter indinters[N], int p, int f){

}
*/

/*
tpSolape maxSolDyV(tpInter indinters[N], int p, int f){

}
*/