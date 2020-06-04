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


tpSolape maxSolDyV(tpInter indinters[N], int p, int f){

	tpSolape solapeMax;

	if(p == f){	
		//El solape cuando solo hay un intervalo, es 0 (CERO)
		solapeMax.interA = indinters[p].ind;
		solapeMax.interB = indinters[p].ind;
		solapeMax.solape = 0;

		return solapeMax;

	}else if(p == f-1){	
		//Si hay dos intervalos, se calcula el solape
		solapeMax = calcularSolape(indinters[p], indinters[f]);
		return solapeMax;
	}else{
		//Calculo del solape mitad izq
		int medio = (p+f)/2;	
		solapeMax = maxSolDyV(indinters, p, medio);

		//Calculo solape mitad dcha
		tpSolape solapeTemp;
		if(medio+1 < f){
			solapeTemp = maxSolDyV(indinters, medio+1, f);

			if(solapeTemp.solape > solapeMax.solape){
				solapeMax = solapeTemp;
			}
		} 

		//Guardamos el maximo entre el de izq y el de la dcha
		double maximoMitades = solapeMax.solape; 

		//Calculamos el indice que masyor alcance tiene de la mitad izq
		int indiceMayorAlcance = p;
		for(int i = p+1; i <= medio; i++){
			if(indinters[i].fin > indinters[indiceMayorAlcance].fin){
				indiceMayorAlcance = i;
			}
		}

		//Con ese indice, buscamos el solape mas grande con los inters de la dcha
		for(int j = medio+1; j <= f; j++){
			tpSolape mayorSolape = calcularSolape(indinters[indiceMayorAlcance], indinters[j]);

			//Cogemos el que tenga mayor solape
			if(mayorSolape.solape > solapeMax.solape){
				solapeMax.interA = indinters[indiceMayorAlcance].ind;
				solapeMax.interB = j;
				solapeMax.solape = mayorSolape.solape;
			}
			
		}

		return solapeMax;
	}

}


