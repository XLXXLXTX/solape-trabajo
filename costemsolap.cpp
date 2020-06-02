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
int main(){

	//Intervalos para pruebas
	double intervalos [N][2] = { {1.5, 8.0}, {0.0, 4.5}, {2.0, 4.0}, {1.0, 6.0}, {3.5, 7.0} };

	probarFB(intervalos, 5);	

	return 0;
}