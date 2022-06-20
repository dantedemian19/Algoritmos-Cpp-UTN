#pragma once
#include<iostream>
#include<string.h>
#include "../cppLibrary/Menu.h"
#include "../CppLibrary/fileManager.h"
using std::endl;
/*

programa facturador: 

lee desde el teclado datos de hasta 50 articulos;
    codigo
    descripcion
    precio unitario

lee desde el teclado los articulos a facturar:
	codigo de los articulos comprados (ccdigo). cada codigo representa 
	una unidad.

    por cada articulo comprado, se debe mostrar la descripcion y el precio 
	del articulo  (precio unitario) ; y se debe calcular el total a pagar
	por la compra

*/

#define _CANTARTICULOS 30

class programFacturador {
/*

  str30 a;
  
  strcpy_s_s(a, "hola");
  
  //   a[0] = 'h'; a[1] = 'o';  a[2] = 'l'; a[3] = 'a'; a[4] = '\0'; 
  //  el resto de la variable tiene "basura"
  
  str30 b;
  cin>>b;   // ingreso la cadena "hola"
  
  //   b[0] = 'h'; b[1] = 'o'; b[2] = 'l'; b[3] = 'b'; a[4] = '\0'; 
  //  el resto de la variable tiene "basura"  
  
   b[0] = 'H';
   
   cout<<b<<endl;
*/

struct tRArticulo {
	string codigo = "0";
	string descripcion = "0";
	int precio = 0;
	int selled = 0;

	void operator = (tRArticulo that) {
		codigo = that.codigo;
		descripcion = that.descripcion;
		precio = that.precio;
		selled = that.selled;
	};

	friend istream& operator >> (istream& in,tRArticulo data) {// to read from file
		in >> data.codigo;
		in >> data.descripcion;
		in >> data.precio;
		in >> data.selled;
		return in;
	};

	friend ostream& operator << (ostream& out,tRArticulo data) { // to write into a file
		out << data.codigo << " " << data.descripcion << " " << data.precio << " " << data.selled << "\n";
		return out;
	};
};

typedef tRArticulo tVecArt[_CANTARTICULOS];
	
private:
	void inicializarArt(tVecArt v, int& c) {
		for (int i = 0; i < c; i++) {
			v[i].codigo = "0";
			v[i].descripcion = "0";
			v[i].precio = 0;
			v[i].selled = 0;
		}
		c = 0;
		fileManager<tRArticulo> file;
		file.declare("datafacturacion", "txt");
		file.readToMemory();
		for (int i = 0; i < _CANTARTICULOS; i++) {
			if (file.inMemoryFile[i] != nullptr) {
				v[i] = file.inMemoryFile[i]->data;
				c += 1;
			}
		}
	};

void pedirArt(tVecArt v, int& c) {
	// carga el vector de los articulos
	//	int precio;
	//	str6 codigo;
	//	str30 descripcion;

	tRArticulo art;
	fileManager<tRArticulo> file;
	file.declare("datafacturacion", "txt");
	cout << "Cargar los articulos......." << endl;
	cout << "Ingresar codigo ('0'=fin)" << endl;
	cin >> art.codigo;
	while ((c < _CANTARTICULOS) && (art.codigo[0] != '0')) {
		cout << "Ingresar descripcion" << endl;
		cin >> art.descripcion;
		cout << "Ingresar precio" << endl;
		cin >> art.precio;
		v[c] = art;
		file.write(v[c]);
		c++;
		cout << "Ingresar codigo ('0''=fin)" << endl;
		cin >> art.codigo;
	}
	cout << "fin de la carga de los articulos......." << endl;
};

int buscarArt(tVecArt vecArt, string codigo, int desde, int cantidad) {
	// recibe un vector, un codigo a buscar, desde donde se busca y la cantidad
	// devuelve la posicion del dato en el vector si existe 0 -1 si no esto
	int i = desde;
	while ((i < cantidad) && (vecArt[i].codigo != codigo))
		i++;
	if (i == cantidad)  // no existe 
		i = -1;       // va a devolver -1
	return i;
};

void createInvoice(tVecArt vecArt, int cantArt) {
	int total;  // total de la factura
	string codigo;
	int totalArt;  // cantidad de articulos facturados
	int indiceArt;  // para buscar en el vector de articulos
	total = 0;
	totalArt = 0;
	int cantidad = 0;
	cout << "Facturar......." << endl;
	cout << "Ingresar codigo ('0'=fin)" << endl;
	cin >> codigo;
	while (codigo[0] != '0') {
		indiceArt = buscarArt(vecArt, codigo, 0, cantArt);
		// buscar devuelve -1 si el articulo no existe o la posicion del articulo
		if (indiceArt > -1) {   // el articulo existe
			  // cuenta los articulos vendidos
			cout << "articulo=" << totalArt;
			cout << " | codigo=" << vecArt[indiceArt].codigo;
			cout << " | descripcion=" << vecArt[indiceArt].descripcion;
			cout << " | precio=" << vecArt[indiceArt].precio;
			cout << " | total=" << total;
			cout << endl;
			while (1) {
				cantidad = 0;
				cout << "Ingresar cantidad a comprar: ('0' = no comprar)" << endl;
				cin >> cantidad;
				if (cantidad >= 0) break;
				else cout << "Cantidad no valida" << endl;
			}
			if (cantidad != 0) {
				total += vecArt[indiceArt].precio * cantidad;  // acumula el total a pagar
				totalArt += cantidad;  // cuenta los articulos vendidos
				vecArt[indiceArt].selled += cantidad; // cuenta cuantas unidades se vendieron
			}
		}
		else  cout << "No existe el articulo!!" << endl;
		cout << "Ingresar codigo ('0'=fin)" << endl;
		cin >> codigo;
	}
	if (totalArt > 0) {
		cout << "total de la factura=" << total;
		cout << " | cantidad de articulos=" << totalArt;
		cout << endl;
	}
	else cout << "No hay articulos!!" << endl;
	cout << "fin de facturar....." << endl;
	pause();
};

void showManySelled(tVecArt vecArt, int cantArt) {
	string codigo;
	int indiceArt;
	while (1) {
		cout << "Ingresar codigo ('0'=fin)" << endl;
		cin >> codigo;
		indiceArt = buscarArt(vecArt, codigo, 0, cantArt);
		if (codigo[0] != '0') {
			if (indiceArt > -1) {   // el articulo existe
			  // cuenta los articulos vendidos
				cout << " | codigo=" << vecArt[indiceArt].codigo;
				cout << " | descripcion=" << vecArt[indiceArt].descripcion;
				cout << " | precio=" << vecArt[indiceArt].precio;
				cout << " | cantidad vendida= " << vecArt[indiceArt].selled;
				cout << endl;
			}
			else cout << "No hay articulos!!" << endl;
		}
		else break;
	}
};

void showAll(tVecArt vecArt, int cantArt) {
	int i = 0;
	while (i < cantArt) {
		cout << "_______________________________________ \n";
		cout << " | codigo=" << vecArt[i].codigo;
		cout << " | descripcion=" << vecArt[i].descripcion;
		cout << " | precio=" << vecArt[i].precio;
		cout << " | cantidad vendida= " << vecArt[i].selled;
		cout << "\n";
		i += 1;
	}
	pause();
};

void orderArt(tVecArt vecArt, int cantArt) {
	int i = 0;
	int j = 0;
	tRArticulo temp;
	i = j;
	while (i < cantArt) {
		if (vecArt[i].codigo[0] != '0')
			while (j < cantArt) {
				if (vecArt[i].selled > vecArt[j].selled && vecArt[j].codigo[0] != '0') {
					temp = vecArt[i];
					vecArt[i] = vecArt[j];
					vecArt[j] = temp;
				}
				j += 1;
			}
		j = 0;
		i += 1;
	}
};

void showMoreSelled(tVecArt vecArt, int& cantArt) {
	int i = 0;
	tVecArt temp ;
	while (i < cantArt) { if (vecArt[i].codigo[0] != '0') temp[i] = vecArt[i] ;  i += 1;}
	orderArt(temp, cantArt);
	showAll(temp, cantArt);
}

int main() {
	tVecArt vecArt;  // vector de los articulos
	int cantArt = _CANTARTICULOS;
	inicializarArt(vecArt, cantArt);  // limpiar el vectro para sacar la ' basura'
	menuClass menu;
	string menuTitle = "\n\t programa: ejercicio con una lista de articulos \n";
	string menuText[] = {
		" start",
		" cargar articulos",
		" facturar articulos",
		" ver articulo",
		" filtrar por cantidad vendida",
		" mostrar todos los articulos",
		" end"
	};
	const int menuOptions = sizeof(menuText) / sizeof(menuText[0]) - 1;
	menu.declare(menuTitle, menuText);
	while (menu.w != menu.exit) {
		menu.menu();
		switch (menu.w) {
		case 1:
			pedirArt(vecArt, cantArt);  // carga los datos de los articulos
			break;
		case 2:
			createInvoice(vecArt, cantArt);  // realiza una factura
			break;
		case 3:
			showManySelled(vecArt, cantArt);
			break;
		case 4:
			showMoreSelled(vecArt, cantArt);
			break;
		case 5:
			showAll(vecArt, cantArt);
			break;
		case menuOptions:
			break;
		default:
			cout << "\n opcion no valida" << endl;
			pause();
			break;
		}
	}

	return 0;
};

public:
	void run() {
		main();
	};
};
