#ifndef juego_h
#define juego_h

#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std; 

struct Personaje{
    int pv; 
    int ph; 
    char nombre[50]; 
    int posX; 
    int posY; 
    int oro; 
};

struct Enemigo{ //estructura para que tenga en cuenta el que haga lo de los enemigos
    char tipo; 
    int pv; 
    int recompensaEnPh; 
    int posX;
    int posY;
    bool vivo; 
};

struct Cofre{ //estructura para  que tenga en cuenta el que haga lo de los cofres
    int posX;
    int posY; 
    bool abierto; 
};

struct Juego
{
    int N; 
    Personaje jugador; 
    int salidaX;
    int salidaY; 
    char mapa[100][100];
    Enemigo enemigos[50];
    int cantEnemigos; 
    Cofre cofres[50]; 
    int cantCofres; 
    bool activo;  
    int contJefe; 
    char cadenaMapa[256]; 
}; 

void empezarJuego(); 
void mostrarTablero(const Juego* estado); 
void mostrarStats(const Juego* estado);
void moverJugador(const char* direccion, Juego* estado);

bool guardarEstado(const Juego* estado, const char* nombreArchivo);
bool cargarEstado(Juego* estado, const char* nombreArchivo); 

//para el que vaya a encargarse de los enemigos/ataques: 
void actualizarEnemigos(Juego* estado); // Ataque de arqueros y movimiento del jefe
void ejecutarAtaque(Juego* estado);    // Comando 'attack'

//para el que vaya a encargarse de logica de cofres y puntaje: 
void explorarCofre(Juego* estado);     // Comando 'seek'
void generarReporteFinal(const Juego* estado, bool gano);

//sustentacion
void guardarSemilla(Juego* estado);


#endif
