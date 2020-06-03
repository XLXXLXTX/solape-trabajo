/********************************************************************************\
 * Programación 2. Trabajo Obligatorio
 * Autor: Javier Pardos Blesa
 * Ultima revisión: 2 de Junio de 2020
 * Resumen: Programa maxsolape.cpp que es el archivo donde se construyen los metodos  
 *          que se definen en maxsolape.hpp
\********************************************************************************/
#include <fstream>
#include "maxsolape.hpp"

using namespace std;

void seleccionarIntervalos(ofstream& fTemp, double tiempo, int intervalo){

	if( (intervalo%5 == 0) && (intervalo != 0) ){

		if(fTemp.is_open()){
			fTemp << intervalo << " " << tiempo << endl;

		}else{
			cerr << "El fichero " << NOMBRE_FICHERO_FB << " no se ha podido abrir para escritura." << endl;
		}
		
	}
}


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
	
	//------------------------------------------------------------
	time_t inicio = time(NULL);
	clock_t ticksRelojInicio = clock();

	double tiempoCheckpoint = 0;
	ofstream ficheroEscribir(NOMBRE_FICHERO_FB);
	//------------------------------------------------------------ 

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
	
	//------------------------------------------------------------
		clock_t ticksRelojFinal = clock();
		double diferencia = ticksRelojFinal - ticksRelojInicio;
		double tiempoTotalIntervalo = ( diferencia) / ( CLOCKS_PER_SEC);

		tiempoCheckpoint += tiempoTotalIntervalo * 1000000; 

		seleccionarIntervalos(ficheroEscribir, tiempoCheckpoint, i);

	//------------------------------------------------------------
	
	}

	//------------------------------------------------------------
	ficheroEscribir.close();
	//------------------------------------------------------------

	return intervaloSolapamiento;
}


void crearvind(double inters[N][2], tpInter indinters[N], int n){	

	for (int i = 0; i<n; ++i){

		indinters[i].ind = i;
		indinters[i].ini = inters[i][0];
		indinters[i].fin = inters[i][1];
	}

}

void merge(tpInter indinters[N], int p, int m, int f){

	tpInter vectorAux [f+1]; // ¿¿¿ Tendria que ser f+1 ???

	int h = p; // Indice "h" que recorre la primera parte del vector indinters[]
	int i = p; // Indice "i" que recorre el vector llamado vectorAux[]
	int j = m+1; // indice "j" que recorre la parte derecha del vector indinters[]

	while( (h <= m) && (j <= f) ){

		// Es menor el componente de la mitad izq que el de la der 
		if(indinters[h].ini <= indinters[j].ini){
			// por lo que se guardaen vectorAux, y se aumenta 
			// la componente "h" que recorre  la parte izq

			vectorAux[i] = indinters[h];
			h++;

		}else{
			vectorAux[i] = indinters[j];
			j++;
		}

		i++;
	}

	// Si se ha recorrido entera la mitad izq, se guarda la parte 
	// derecha en el vectoAux ya que estaba ordenada
	if(h > m){

		for(int k=j; k<=f; k++){
			vectorAux[i] = indinters[k];
			i++;
		}
	}else{
	// Si se ha recorrido la parte de la der, se guada la parte 
	// izquierda en el vectorAux ya que ya estaba ordenada 
		for(int k=h; k<=m; k++){
			vectorAux[i] = indinters[k];
			i++;
		}
	}


	// Finalmente se copia el vector ya ordenado, al vetor inicial
	for(int k=p; k<=f; k++){
		indinters[k] = vectorAux[k];
	}

}


void mergesortIndInters(tpInter indinters[N], int p, int f){

		if(p < f){
		int mitad = (f + p) / 2;

		// Ordenamos la mitad de la izq
		mergesortIndInters(indinters, p, mitad);
		// Ordenamos la mitad de la der
		mergesortIndInters(indinters, mitad+1, f);
		// Ahora que estan ambas mitades ordenadas, las tenemos 
		// que mezclar y ordenaralas 
		merge(indinters, p, mitad, f);
						
	}

}


/*
 * @@@@@@@@@REVISAR@@@@@@@@@
 *
 * FALLA AL DEVOLVER EL SOLAPE MAX
 *
 * @@@@@@@@@REVISAR@@@@@@@@@
 *
tpSolape maxSolDyV(tpInter indinters[N], int p, int f){

	tpSolape solapeMax;

	//El solape cuando solo hay un intervalo, es 0 (CERO)
	if(p == f){
		solapeMax.interA = indinters[p].ind;
		solapeMax.interB = indinters[p].ind;
		solapeMax.solape = 0;

		return solapeMax;

	}else if(p == f-1){
	//Si hay dos intervalos, se sacan con la funcion de calcularSolape(intervalo1, intervalo2)	
		solapeMax = calcularSolape(indinters[p], indinters[f]);
		return solapeMax;

	}else{

		int medio = (p+f)/2;
		solapeMax = maxSolDyV(indinters, p, medio);

		tpSolape solapeTemp;
		if(medio+1 < f){
			solapeTemp = maxSolDyV(indinters, medio+1, f);


			if(solapeTemp.solape > solapeMax.solape){
				solapeMax = solapeTemp;
			}
		} 


		double maximoMitad = solapeMax.solape; 
		int indiceMayorAlcance = p;
		for(int i = p+1; i <= medio; i++){
			if(indinters[i].fin > indinters[indiceMayorAlcance].fin){
				indiceMayorAlcance = i;
			}
		}


		for(int i = medio+1; i <= f; i++){
			tpSolape mayorSolape = calcularSolape(indinters[indiceMayorAlcance], indinters[f]);

			if(mayorSolape.solape > solapeMax.solape){
				solapeMax.interB = i;
				solapeMax.solape = mayorSolape.solape;
			}
		}

		if(maximoMitad < solapeMax.solape){
			solapeMax.interA = indinters[indiceMayorAlcance].ini;
		}

		return solapeMax;
	}

}

*/
