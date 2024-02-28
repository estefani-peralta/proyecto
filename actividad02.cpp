#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <sstream>
#include <algorithm>
//es especialmente útil cuando necesitas asignar memoria o trabajar con estructuras de datos y deseas asegurarte del espacio que están ocupando en la memoria.

using namespace std;

// Estructuras para representar libros, usuarios y bibliotecarios
struct Libro {
	string strTitulo;
	string strAutor;
	int nISBN;
	int nAnioPublicacion;
	string strEditorial;
	string strEstado; // Valores posibles: "disponible", "prestado", "reservado"
	int nPaginas;
};

struct Usuario {
	int nUserID;      // Identificador único para cada usuario
	string strNombre;
	string strApellido;
	string strEmail;
	int nEdad;         // Edad del usuario
};

struct Bibliotecario {
	int nEmployeeID;
	string strNombre;
	string strApellido;
	string strEmail;
	string strCargo;    // Nuevo campo para el cargo del bibliotecario
};

// Arreglos de elementos para generación aleatoria
string arrNombresAutores[] = {"Alejandro", "Emiliano", "Francisco", "Antonieta", "Cristobal ", "Valentina", "Magdalena", "Antonella"};
string arrApellidosAutores[] = {"Gutiérrez", "Dominguez", "Martínez", "Hernández", "Pausinis", "Fernández", "Carrasco", "Rodríguez"};

string arrNombres[] = {"Gabriela", "Isabella", "Valentina", "Fernando", "Benjamin", "jhonatan", "Leonardo", "Salvador"};
string arrApellidos[] = {"González", "Montanese", "Martínez", "Pausinis", "Rodríguez", "Villegas", "Fernandez", "Clemente"};

string arrEditoriales[] = {"Editorial Santillana", "Acantilado Editorial", "Editorial Alfaguara", "Editorial Planeta", "Anagrama Editorial", "Ediciones Sir", "Alianza Editorial", "Ediciones Siglo XXI"};

string arrCargos[] = {"Bibliotecario Infantil", "Asistente de Referencia", "Auxiliar de Biblioteca", "Encargado de Adquisiciones", "Coordinador de Programas Educativos"};

string arrEstados[] = {"Prestado", "Reservado", "Disponible"};
string arrTitulos[] = {"el viejo y el mar", "rebelión en la granja", "la isla del tesoro", "el corazon de la luz", "aprende programacion", "inteligencia artificial", "ciberseguridad esencial", "javaScript moderno", "arduino proyectos"};

// Función para generar aleatoriamente un elemento de un arreglo
string generarAleatorio(string arrElementos[], int nTamano) {
	return arrElementos[rand() % nTamano];
}

// Función para generar un correo electrónico con base en el nombre, apellido y edad
string generarEmail(string strNombre, string strApellido) {
	stringstream ss;
	ss << strNombre << strApellido << "@gmail.com";
	return ss.str();
}

// Función para verificar si un libro con el mismo título o autor ya existe
bool repetidoLibro(string strTitulo, string strAutor, Libro* libros, int nCantidad) {
	for (int i = 0; i < nCantidad; ++i) {
		if (strTitulo == libros[i].strTitulo || strAutor == libros[i].strAutor) {//se utiliza para verificar si el título o el autor de un libro coinciden con los valores proporcionados 
			return true; // Se encontró un libro con el mismo título o autor
		}
	}
	return false; // No se encontraron coincidencias
}

// Función para inicializar libros aleatoriamente
void inicializarLibros(Libro* pt, int nCantidad, int nMinPaginas, int nMaxPaginas) {
	int nNumTitulos = sizeof(arrTitulos) / sizeof(arrTitulos[0]);//calcula el número de elementos en un arreglo llamado arrTitulos y almacena ese valor en la variable nNumTitulos
	
	for (int i = 0; i < nCantidad; ++i) {
		string strTitulo;//Estas variables se utilizan para almacenar temporalmente el título y el autor de algún tipo de entidad (como un libro, usuario, etc.)
		string strAutor;
		do {
			strTitulo = arrTitulos[rand() % nNumTitulos];
			string strNombreAutor = generarAleatorio(arrNombresAutores, sizeof(arrNombresAutores) / sizeof(arrNombresAutores[0]));
			string strApellidoAutor = generarAleatorio(arrApellidosAutores, sizeof(arrApellidosAutores) / sizeof(arrApellidosAutores[0]));
			strAutor = strNombreAutor + " " + strApellidoAutor;//Combina el nombre y el apellido para formar el autor del libro.
		} while (repetidoLibro(strTitulo, strAutor, pt, i));
		
		pt[i].strTitulo = strTitulo;
		pt[i].strAutor = strAutor;
		pt[i].nISBN = i + 1;//// Asigna un número de ISBN único basado en el índice del libro
		pt[i].nAnioPublicacion = rand() % 35 + 1990;// Asigna un año de publicación aleatorio entre 1990 y 2024
		pt[i].strEditorial = generarAleatorio(arrEditoriales, sizeof(arrEditoriales) / sizeof(arrEditoriales[0]));
		pt[i].strEstado = generarAleatorio(arrEstados, sizeof(arrEstados) / sizeof(arrEstados[0]));
		pt[i].nPaginas = rand() % (nMaxPaginas - nMinPaginas + 1) + nMinPaginas;//Asigna un número de páginas aleatorio entre nMinPaginas y nMaxPaginas.
	}
}

// Función para imprimir información de un libro
void imprimir(const Libro* libro) {
	cout << setw(30) << left << libro->strTitulo << setw(28) << left << libro->strAutor << setw(15) << left << libro->nISBN << setw(15) << left << libro->nAnioPublicacion
		<< setw(30) << left << libro->strEditorial << setw(25) << left << libro->strEstado << setw(10) << left << libro->nPaginas << endl;
}

// Sobrecarga de función para imprimir información de un libro
void imprimir(const Libro& libro) {
	imprimir(&libro);
}

// Función para imprimir información de varios libros
void imprimir(const Libro* libros, int nCantidad, bool imprimirEncabezado = true) {
	if (imprimirEncabezado) {
		cout << "Imprimiendo datos del Libro:" << endl;
		cout << setw(35) << left << "TITULO" << setw(22) << left << "AUTOR" << setw(7) << left << "ISBN" << setw(28) << left << "AÑO DE PUBLICACION"
			<< setw(25) << left << "EDITORIAL" << setw(23) << left << "DISPONIBILIDAD" << setw(10) << left << "PAGINAS" << endl;
	}
	
	if (nCantidad > 0) {
		imprimir(&libros[0]);  // Imprimir el primer libro
		imprimir(libros + 1, nCantidad - 1, false);  // Llamada recursiva para el resto de los libros
	}
}

// Función para inicializar usuarios aleatoriamente
void inicializarUsuarios(Usuario* pt, int nCantidad) {
	for (int i = 0; i < nCantidad; ++i) {
		pt[i].nUserID = i + 1;// Asigna un ID único al usuario basado en el índice del usuario más 1. Esto asume que los índices comienzan desde 0.
		pt[i].strNombre = generarAleatorio(arrNombres, sizeof(arrNombres) / sizeof(arrNombres[0]));
		pt[i].strApellido = generarAleatorio(arrApellidos, sizeof(arrApellidos) / sizeof(arrApellidos[0]));
		pt[i].nEdad = rand() % 13 + 18;  // Generar edades entre 18 y 30
		pt[i].strEmail = generarEmail(pt[i].strNombre, pt[i].strApellido);

	}
}




// Función para imprimir información de un usuario
void imprimir(const Usuario* usuario) {
	cout << setw(5) << left << usuario->nUserID << setw(15) << left << usuario->strNombre << setw(15) << left << usuario->strApellido << setw(10) << left << usuario->nEdad << setw(30) << left << usuario->strEmail << endl;
}

// Sobrecarga de función para imprimir información de un usuario
void imprimir(const Usuario& usuario) {
	imprimir(&usuario);
}

// Función para imprimir información de varios usuarios
void imprimir(const Usuario* usuarios, int nCantidad, bool imprimirEncabezado = true) {
	if (imprimirEncabezado) {
		cout << "Imprimiendo datos del usuario:" << endl;
		cout << setw(5) << left << "ID" << setw(15) << left << "NOMBRE" << setw(15) << left << "APELLIDO" << setw(10) << left << "EDAD" << setw(30) << left << "EMAIL" << endl;
	}
	
	if (nCantidad > 0) {
		imprimir(&usuarios[0]);  // Imprimir el primer usuario
		imprimir(usuarios + 1, nCantidad - 1, false);  // Llamada recursiva para el resto de los usuarios
	}
}

// Función para inicializar bibliotecarios aleatoriamente
void inicializarBibliotecarios(Bibliotecario* pt, int nCantidad) {
	for (int i = 0; i < nCantidad; ++i) {
		pt[i].nEmployeeID = i + 1;
		pt[i].strNombre = generarAleatorio(arrNombres, sizeof(arrNombres) / sizeof(arrNombres[0]));
		pt[i].strApellido = generarAleatorio(arrApellidos, sizeof(arrApellidos) / sizeof(arrApellidos[0]));
		pt[i].strEmail = generarEmail(pt[i].strNombre, pt[i].strApellido); //crear una dirección de correo electrónico basada en el nombre y apellido del empleado. Esta dirección se asigna al atributo strEmail
		pt[i].strCargo = generarAleatorio(arrCargos, sizeof(arrCargos) / sizeof(arrCargos[0]));// Asigna aleatoriamente un cargo al empleado seleccionándolo de la colección arrCargos
	}
}

// Función para imprimir información de un bibliotecario
void imprimir(const Bibliotecario* bibliotecario) {
	cout << setw(8) << left << bibliotecario->nEmployeeID << setw(15) << left << bibliotecario->strNombre << setw(15) << left << bibliotecario->strApellido << setw(30) << left << bibliotecario->strEmail
		<< setw(30) << left << bibliotecario->strCargo << endl;
}

// Sobrecarga de función para imprimir información de un bibliotecario
void imprimir(const Bibliotecario& bibliotecario) {
	imprimir(&bibliotecario);
}

// Función para imprimir información de varios bibliotecarios
void imprimir(const Bibliotecario* bibliotecarios, int nCantidad, bool imprimirEncabezado = true) {
	if (imprimirEncabezado) {
		cout << "Imprimiendo datos de bibliotecarios:" << endl;
		cout << setw(8) << left << "ID Emp" << setw(15) << left << "Nombre" << setw(15) << left << "Apellido" << setw(30) << left << "Email" << setw(30) << left << "Cargo" << endl;
	}
	
	if (nCantidad > 0) {
		imprimir(&bibliotecarios[0]);  // Imprimir el bibliotecario actual
		imprimir(bibliotecarios + 1, nCantidad - 1, false);  // Llamada recursiva para el siguiente bibliotecario
	}
}

// Función para llenar datos de libros, usuarios y bibliotecarios
void llenarDatos(Libro* libros, Usuario* usuarios, Bibliotecario* bibliotecarios, int nCantidad) {
	inicializarLibros(libros, nCantidad, 200, 300);
	inicializarUsuarios(usuarios, nCantidad);
	inicializarBibliotecarios(bibliotecarios, nCantidad);
	
	cout << "Datos inicializados." << endl;
}

// funcion para  buscar  por el titulo del libro 
void buscarYListarLibrosPorTitulo(const Libro* libros, int size, const string& titulo, int index = 0) {
	if (index < size) {
		// Convertir la subcadena a minúsculas para realizar una búsqueda sin distinción de mayúsculas
		string tituloLower = titulo;
		transform(tituloLower.begin(), tituloLower.end(), tituloLower.begin(), ::tolower); 
		// Convertir el título del libro actual a minúsculas
		string libroLower = libros[index].strTitulo;
		transform(libroLower.begin(), libroLower.end(), libroLower.begin(), ::tolower); // Convertir a minúsculas
		// Buscar si la subcadena está presente en cualquier parte del título del libro
		if (libroLower.find(tituloLower) != string::npos) {
			// Si la subcadena se encuentra en el título del libro, imprimir los detalles del libro
			imprimir(libros[index]);
		}
		// Llamar recursivamente a la función para el siguiente libro en el array
		buscarYListarLibrosPorTitulo(libros, size, titulo, index + 1);
	} else {
		// Si no se encontraron libros con la subcadena en el título, imprimir un mensaje informativo
		cout << "No se encontraron libros con similitud en el título \"" << titulo << "\"." << endl;
	}
}


void buscarUsuarioPorNombreApellido(const Usuario* usuarios, int size, const string &nombreApellido, int index = 0) {
	if (index < size) {
		//// Concatenar el nombre y apellido del usuario actual
		string nombreCompleto = usuarios[index].strNombre + " " + usuarios[index].strApellido;
		transform(nombreCompleto.begin(), nombreCompleto.end(), nombreCompleto.begin(), ::tolower);
		//  // Convertir la subcadena a minúsculas
		string nombreApellidoLower = nombreApellido;
		transform(nombreApellidoLower.begin(), nombreApellidoLower.end(), nombreApellidoLower.begin(), ::tolower);
		// Buscar si la subcadena está presente en cualquier parte del nombre completo del usuario
		if (nombreCompleto.find(nombreApellidoLower) != string::npos) {
			cout << "Usuario encontrado:" << endl;
			imprimir(usuarios[index]);
		}
		// Llamar recursivamente a la función para el siguiente usuario en el array
		buscarUsuarioPorNombreApellido(usuarios, size, nombreApellido, index + 1);
	} else {
		cout << "No se encontraron usuarios con el nombre o apellido \"" << nombreApellido << "\"." << endl;
	}
}


void buscarBibliotecarioPorNombreApellido(const Bibliotecario* bibliotecarios, int size, const string& nombreApellido, int index = 0) {
	if (index < size) {
		// Construir el nombre completo del bibliotecario actual
		string nombreCompleto = bibliotecarios[index].strNombre + " " + bibliotecarios[index].strApellido;
		// Convertir el nombre completo a minúsculas para realizar una búsqueda sin distinción de mayúsculas
		transform(nombreCompleto.begin(), nombreCompleto.end(), nombreCompleto.begin(), ::tolower);
		// Convertir el nombre y apellido proporcionados a minúsculas
		string nombreApellidoLower = nombreApellido;
		transform(nombreApellidoLower.begin(), nombreApellidoLower.end(), nombreApellidoLower.begin(), ::tolower);
		// Buscar si la subcadena está presente en cualquier parte del nombre completo del bibliotecario
		if (nombreCompleto.find(nombreApellidoLower) != string::npos) {
			// Si la subcadena se encuentra en el nombre completo, imprimir los detalles del bibliotecario
			cout << "Bibliotecario encontrado:" << endl;
			imprimir(bibliotecarios[index]);
		}
		// Llamar recursivamente a la función para el siguiente bibliotecario en el array
		buscarBibliotecarioPorNombreApellido(bibliotecarios, size, nombreApellido, index + 1);
	} else {
		// Si no se encontraron bibliotecarios con el nombre o apellido proporcionado, imprimir un mensaje informativo
		cout << "No se encontraron bibliotecarios con el nombre o apellido \"" << nombreApellido << "\"." << endl;
	}
}




// Función para mostrar el submenu de listados
void submenuListados(const Libro* libros, const Usuario* usuarios, const Bibliotecario* bibliotecarios, int nCantidad) {
	char cOpcionListados;
	do {
		cout << "\nSUBMENU LISTADOS:" << endl;
		cout << "A) Listado de Libros" << endl;
		cout << "B) Listado Usuarios" << endl;
		cout << "C) Listado Bibliotecarios" << endl;
		cout << "X) Salir" << endl;
		
		cout << "Ingrese la opción deseada: ";
		cin >> cOpcionListados;
		//  // Procesar la opción seleccionada
		switch (toupper(cOpcionListados)) {
		case 'A':
			imprimir(libros, nCantidad);
			break;
		case 'B':
			imprimir(usuarios, nCantidad);
			break;
		case 'C':
			imprimir(bibliotecarios, nCantidad);
			break;
		case 'X':
			cout << "Volviendo al menú principal." << endl;
			break;
		default:
			cout << "Opción no válida. Intente de nuevo." << endl;
		}
		
	} while (toupper(cOpcionListados) != 'X');//// Repetir el bucle hasta que se seleccione 'X'
}

void submenuBusquedas(const Libro* libros, const Usuario* usuarios, const Bibliotecario* bibliotecarios, int nCantidad) {
	char cOpcionBusquedas;
	do {
		// Mostrar las opciones del submenu de búsquedas
		cout << "\nSUBMENU BUSQUEDAS:" << endl;
		cout << "A) Búsqueda de Libro (Titulo)" << endl;
		cout << "B) Búsqueda de Usuario (Nombre y Apellido)" << endl;
		cout << "C) Búsqueda de Bibliotecario (Nombre y Apellido)" << endl;
		cout << "X) Salir" << endl;
		
		// Solicitar la opción al usuario
		cout << "Ingrese la opción deseada: ";
		cin >> cOpcionBusquedas;
		cOpcionBusquedas = toupper(cOpcionBusquedas); // Convertir a mayúsculas para ser case-insensitive
		
		// Realizar acciones según la opción seleccionada
		switch (cOpcionBusquedas) {
		case 'A':
		{//  // Búsqueda de libros por título
			string tituloBuscado;
			cout << "Ingrese el título del libro a buscar: ";
			cin.ignore();//// Ignorar el salto de línea anterior
			getline(cin, tituloBuscado);
			buscarYListarLibrosPorTitulo(libros, nCantidad, tituloBuscado);
		}
		break;
		case 'B':
		{
			string nombreOApellidoBuscado;
			cout << "Ingrese el nombre o apellido del usuario a buscar: ";
			cin >> nombreOApellidoBuscado;
			buscarUsuarioPorNombreApellido(usuarios, nCantidad, nombreOApellidoBuscado);
			break;
		}
		case 'C':
		{
			string nombreOApellidoBuscadoE;
			cout << "Ingrese el nombre del bibliotecario a buscar: ";
			cin >> nombreOApellidoBuscadoE;
			buscarBibliotecarioPorNombreApellido(bibliotecarios, nCantidad, nombreOApellidoBuscadoE);
		}
		break;
		case 'X':
			cout << "Volviendo al menú principal." << endl;
			break;
		default:
			cout << "Opción no válida. Intente de nuevo." << endl;
		}
		
	} while (cOpcionBusquedas != 'X'); // Continuar el bucle hasta que se seleccione la opción 'X'
}



// Función principal
int main() {
	const int nTMA = 8;
	
	srand(time(0)); // Inicializar la semilla del generador de números aleatorios
	
	// Declarar arreglos de estructuras para libros, usuarios y bibliotecarios
	Libro libros[nTMA];
	Usuario usuarios[nTMA];
	Bibliotecario bibliotecarios[nTMA];
	
	int nOpcion; // Variable para almacenar la opción del menú
	
	do {
		// Mostrar las opciones del menú principal
		cout << "\nMENU PRINCIPAL:" << endl;
		cout << "1) llenado de  Datos" << endl;
		cout << "2) Listados" << endl;
		cout << "3) Busquedas" << endl;
		cout << "0) Salir" << endl;
		
		// Solicitar la opción al usuario
		cout << "Ingrese la opción deseada: ";
		cin >> nOpcion;
		
		// Realizar acciones según la opción seleccionada
		switch (nOpcion) {
		case 1:
			llenarDatos(libros, usuarios, bibliotecarios, nTMA);
			break;
		case 2:
			submenuListados(libros, usuarios, bibliotecarios, nTMA);
			break;
		case 3:
			submenuBusquedas(libros, usuarios, bibliotecarios, nTMA);
			break;
		case 4:
			cout << "Saliendo del programa. Hasta luego." << endl;
			break;
		default:
			cout << "Opción no válida. Intente de nuevo." << endl;
		}
		
	} while (nOpcion != 0); // Continuar el bucle hasta que se seleccione la opción 0 (Salir)
	
	return 0;
}
