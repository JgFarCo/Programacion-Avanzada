#include "logicaJuego.h"
using namespace std; 

const char* ARCHIVO_BINARIO = "estado_juego.bin";

bool guardarEstado(const Juego* estado, const char* nombreArchivo)
{
    ofstream archivo(nombreArchivo, ios::binary | ios::out);
    if(!archivo) return false; 

    archivo.write((const char*)estado, sizeof(Juego));
    archivo.close();
    return true; 
}

bool cargarEstado(Juego* estado, const char* nombreArchivo)
{
    ifstream archivo(nombreArchivo, ios::binary | ios::in);
    if(!archivo) return false; 

    archivo.read((char*)estado, sizeof(Juego));
    archivo.close();
    return true;
}

void generarReporteFinal(const Juego* estado, bool gano)
{
    int puntaje = 0;
    if(gano)
    {
        puntaje += 100;
    }
    
    puntaje += (estado->jugador.oro * 2);
    puntaje += (estado->jugador.pv * 2);
    puntaje += (estado->jugador.ph * 5);

    cout << "\n==========================================" << endl;
    cout << "NOMBRE: " << estado->jugador.nombre << endl;
    if (gano) {
        cout << "ESTADO: ¡VICTORIA!" << endl;
    } else {
        cout << "ESTADO: DERROTA" << endl;
    }
    cout << "PUNTAJE TOTAL: " << puntaje << endl;
    cout << "==========================================\n" << endl;
}

void actualizarEnemigos(Juego* estado){
   int distanciaX = 0;
   int distanciaY = 0;
   int espacioX = 0;
   int espacioY = 0;

   for(int i = 0; i < estado->cantEnemigos; i++){

      if (!((estado->enemigos) + i)->vivo) continue;

      if(((estado->enemigos) + i)->tipo == 'A'){
          if( (((estado->enemigos) + i)->posX == estado->jugador.posX) && (((estado->enemigos) + i)->posY == estado->jugador.posY) ){
            estado->jugador.pv -= 10;
            cout << "Un arquero te disparó una flecha (-10 PV)" << endl;
          } else if( (((((estado->enemigos) + i)->posX) - 1) == estado->jugador.posX) && (((estado->enemigos) + i)->posY == estado->jugador.posY)){
            estado->jugador.pv -= 10;
            cout << "Un arquero te disparó una flecha (-10 PV)" << endl;
          } else if( (((((estado->enemigos) + i)->posX) + 1) == estado->jugador.posX) && (((estado->enemigos) + i)->posY == estado->jugador.posY)){
            estado->jugador.pv -= 10;
            cout << "Un arquero te disparó una flecha (-10 PV)" << endl;
          } else if( ((((estado->enemigos) + i)->posX) == estado->jugador.posX) && ((((estado->enemigos) + i)->posY - 1) == estado->jugador.posY)){
            estado->jugador.pv -= 10;
            cout << "Un arquero te disparó una flecha (-10 PV)" << endl;
          } else if( ((((estado->enemigos) + i)->posX) == estado->jugador.posX) && ((((estado->enemigos) + i)->posY + 1) == estado->jugador.posY)){
            estado->jugador.pv -= 10;
            cout << "Un arquero te disparó una flecha (-10 PV)" << endl;
          }
      } else if (((estado->enemigos) + i)->tipo == 'G'){
          if( (((estado->enemigos) + i)->posX == estado->jugador.posX) && (((estado->enemigos) + i)->posY == estado->jugador.posY) ){
            estado->jugador.pv -= 10;
            cout << "Un goblin te atacó (-10 PV)" << endl;
          }
      } else if (((estado->enemigos) + i)->tipo == 'J'){

         if( estado->contJefe % 2 == 0 && estado->contJefe != 0){

            int vX = ((estado->enemigos) + i)->posX;
            int vY = ((estado->enemigos) + i)->posY;

            distanciaX = (estado->jugador.posX + estado->salidaX) / 2;
            distanciaY = (estado->jugador.posY + estado->salidaY) / 2;

            espacioX = distanciaX - vX;
            espacioY = distanciaY - vY;

            int absX = (espacioX < 0) ? -espacioX : espacioX;
            int absY = (espacioY < 0) ? -espacioY : espacioY;

            // Elige cuál eje mover para acorralarte activamente
            if(absX >= absY && vX != distanciaX){
               if(distanciaX > vX) ((estado->enemigos) + i)->posX += 1;
               else if(distanciaX < vX) ((estado->enemigos) + i)->posX -= 1;
            } else if(vY != distanciaY){
               if(distanciaY > vY) ((estado->enemigos) + i)->posY += 1;
               else if(distanciaY < vY) ((estado->enemigos) + i)->posY -= 1;
            } else if(vX != distanciaX){
               if(distanciaX > vX) ((estado->enemigos) + i)->posX += 1;
               else if(distanciaX < vX) ((estado->enemigos) + i)->posX -= 1;
            }

            int nX = ((estado->enemigos) + i)->posX;
            int nY = ((estado->enemigos) + i)->posY;

            if (vX != nX || vY != nY) {
                if (*(*(estado->mapa + vX) + vY) == 'E') {
                    *(*(estado->mapa + vX) + vY) = '-';
                }
                if (*(*(estado->mapa + nX) + nY) == '-') {
                    *(*(estado->mapa + nX) + nY) = 'E';
                }
            }
         }

         if( (((estado->enemigos) + i)->posX == estado->jugador.posX) && (((estado->enemigos) + i)->posY == estado->jugador.posY) ){
            estado->jugador.pv -= 40;
            cout << "¡El Jefe te ha asestado un golpe feroz! (-40 PV)" << endl;
         }
      }
   }
}

void ejecutarAtaque(Juego* estado){
    bool atacoEnemigo = false;
    for(int i = 0; i < estado->cantEnemigos; i++){
        if (!((estado->enemigos) + i)->vivo) continue;

        if(estado->jugador.posX == ((estado->enemigos) + i)->posX && estado->jugador.posY == ((estado->enemigos) + i)->posY){
            atacoEnemigo = true;
            ((estado->enemigos) + i)->pv -= estado->jugador.ph;
            
            if(((estado->enemigos) + i)->pv <= 0){
                ((estado->enemigos) + i)->vivo = false;
                cout << "¡El enemigo ha sido derrotado!" << endl;
                estado->jugador.ph += ((estado->enemigos) + i)->recompensaEnPh;
                // Deja la 'X' en la casilla del enemigo derrotado
                *(*(estado->mapa + estado->jugador.posX) + estado->jugador.posY) = 'X';
            } else {
                cout << "El enemigo sufrió daño pero aún sigue con vida. PV restantes: " << ((estado->enemigos) + i)->pv << endl;
            }
        }
    }
    if(!atacoEnemigo) {
        cout << "No hay enemigos en esta casilla para atacar." << endl;
    }
}

void empezarJuego()
{
    Juego estado;

    cout<<"A continuación ingrese las dimensiones que desea para el tablero de juego cuadrado (N= numero de filas y numero de columnas)."<<endl; 
    cout<<"N = "; 
    cin>>estado.N; 

    int ngoblins, narqueros, ncofres;
    cout<< "Ingrese número de goblins: "; cin>>ngoblins;
    cout<< "Ingrese número de arqueros: "; cin>>narqueros; 
    cout<< "Ingrese número de cofres: "; cin>>ncofres; 

    cout<<"Nombre de su personaje: ";
    cin>>estado.jugador.nombre;
    estado.jugador.pv = 100; 
    estado.jugador.ph = 20; 
    estado.jugador.oro = 0; 
    estado.contJefe = 0;

    for (int i = 0; i < estado.N; i++) {
        for (int j = 0; j < estado.N; j++) {
            *(*(estado.mapa + i) + j) = '-';
        }
    }

    srand((unsigned)time(NULL));

    int ladoSalida = rand() % 4; 
    if (ladoSalida == 0) {
        estado.salidaX = 0;
        estado.salidaY = rand() % estado.N;
    } else if (ladoSalida == 1) {
        estado.salidaX = estado.N - 1;
        estado.salidaY = rand() % estado.N;
    } else if (ladoSalida == 2) {
        estado.salidaX = rand() % estado.N;
        estado.salidaY = 0;
    } else {
        estado.salidaX = rand() % estado.N;
        estado.salidaY = estado.N - 1;
    }

    *(*(estado.mapa + estado.salidaX) + estado.salidaY) = '#'; 

    int ladoComienzoJugador;
    do { 
        ladoComienzoJugador = rand() % 4; 
    } while(ladoComienzoJugador == ladoSalida); 

    if (ladoComienzoJugador == 0) {
        estado.jugador.posX = 0;
        estado.jugador.posY = rand() % estado.N;
    } else if (ladoComienzoJugador == 1) {
        estado.jugador.posX = estado.N - 1;
        estado.jugador.posY = rand() % estado.N;
    } else if (ladoComienzoJugador == 2) {
        estado.jugador.posX = rand() % estado.N;
        estado.jugador.posY = 0;
    } else {
        estado.jugador.posX = rand() % estado.N;
        estado.jugador.posY = estado.N - 1;
    }

    *(*(estado.mapa + estado.jugador.posX) + estado.jugador.posY) = '@'; 

    // Generación de enemigos con Aritmética de Punteros
    estado.cantEnemigos = ngoblins + narqueros + 1; 

    for(int i = 0; i < estado.cantEnemigos; i++) {
        (estado.enemigos + i)->posX = rand() % estado.N;
        (estado.enemigos + i)->posY = rand() % estado.N;
        (estado.enemigos + i)->vivo = true;

        if((i + 1) == estado.cantEnemigos) {
            (estado.enemigos + i)->tipo = 'J';
            (estado.enemigos + i)->pv = 60;
            (estado.enemigos + i)->recompensaEnPh = 5;
        } else {
            if (i % 2 == 0) {
                (estado.enemigos + i)->tipo = 'G';
                (estado.enemigos + i)->pv = 30;
                (estado.enemigos + i)->recompensaEnPh = 2;
            } else {
                (estado.enemigos + i)->tipo = 'A';
                (estado.enemigos + i)->pv = 20;
                (estado.enemigos + i)->recompensaEnPh = 3;
            }
        }

        if(((estado.enemigos + i)->posX == estado.jugador.posX && (estado.enemigos + i)->posY == estado.jugador.posY) || 
           ((estado.enemigos + i)->posX == estado.salidaX && (estado.enemigos + i)->posY == estado.salidaY)) {
            i--;
        }
    }

    for(int i = 0; i < estado.cantEnemigos; i++) {
        *(*(estado.mapa + (estado.enemigos + i)->posX) + (estado.enemigos + i)->posY) = 'E';
    }

    // Generación de cofres
    estado.cantCofres = 0;
    int x, y;

    for(int i = 0; i < ncofres; i++)
    {
        x = rand() % estado.N;
        y = rand() % estado.N;
        
        if(*(*(estado.mapa + x) + y) != '-')
        {
             x = rand() % estado.N;
             y = rand() % estado.N;
        }
        
        if(*(*(estado.mapa + x) + y) == '-')
        {
            *(*(estado.mapa + x) + y) = '?';
            (estado.cofres + i)->posX = x;
            (estado.cofres + i)->posY = y;
            (estado.cofres + i)->abierto = false;
            estado.cantCofres++;
        }
    }

    estado.activo = true; 

    guardarEstado(&estado, ARCHIVO_BINARIO); 
    
    if(estado.activo) cout << "Se pudo iniciar el juego con éxito\n" << endl; 
    mostrarTablero(&estado); 
}

void mostrarTablero(const Juego* estado)
{
    for (int i = 0; i < estado->N; i++) {
        cout << (i + 1) << " |";
        for (int j = 0; j < estado->N; j++) {
            cout << " " << *(*(estado->mapa + i) + j) << " ";
        }
        cout << "|\n";
    }
}

void mostrarStats(const Juego* estado) {
    cout << "Informe de estadísticas:\n";
    cout << "PV: " << estado->jugador.pv << "\n";
    cout << "PH: " << estado->jugador.ph << "\n";
    cout << "Oro: " << estado->jugador.oro << "\n";
}

void moverJugador(const char* direccion, Juego* estado)
{
    string mover = direccion; 
    int x = estado->jugador.posX;
    int y = estado->jugador.posY;
    int ox = x; 
    int oy = y; 

    if(mover == "up") x--; 
    else if(mover == "down") x++; 
    else if(mover == "right") y++; 
    else if(mover == "left") y--; 
    else {
        cout << "Movimiento no válido\n" << endl; 
        return; 
    }

    if(x < 0 || x >= estado->N || y < 0 || y >= estado->N)
    {
        cout << "El movimiento deseado está fuera del mapa\n" << endl; 
        return; 
    }

    if(*(*(estado->mapa + x) + y) != '#')
    {
        estado->jugador.posX = x; 
        estado->jugador.posY = y; 
        
        // Conserva 'X' si habías matado un enemigo en la casilla anterior, de lo contrario '-'
        if (*(*(estado->mapa + ox) + oy) != 'X') {
            *(*(estado->mapa + ox) + oy) = '-'; 
        }

        *(*(estado->mapa + x) + y) = '@'; 

        estado->contJefe++;
        actualizarEnemigos(estado);

        if (estado->jugador.pv <= 0) {
            cout << "\n¡Has sido derrotado!" << endl;
            generarReporteFinal(estado, false);
            estado->activo = false;
        }

        guardarEstado(estado, ARCHIVO_BINARIO);
        mostrarTablero(estado);
    }
    else {
        cout << "¡Has llegado a la salida!" << endl;
        generarReporteFinal(estado, true);
        estado->activo = false;
        guardarEstado(estado, ARCHIVO_BINARIO);
    }
}

void explorarCofre(Juego* estado)
{
    int x = estado->jugador.posX;
    int y = estado->jugador.posY;
    bool cofreEncontrado = false;

    for (int i = 0; i < estado->cantCofres; i++) {
        if ((estado->cofres + i)->posX == x && (estado->cofres + i)->posY == y) {
            cofreEncontrado = true;
            cout << "Buscando cofre..." << endl;
            if (!(estado->cofres + i)->abierto) {
                char chance[] = {'O','P','P','T','O','T','P','O','O','O'};
                int numrand = rand() % 10;
                char f = chance[numrand];

                if (f == 'O') {
                    numrand = (rand() % 2 + 1) * 10;
                    estado->jugador.oro += numrand;
                    cout << "¡Recibiste " << numrand << " de oro!" << endl;
                }
                if (f == 'P') {
                    numrand = (rand() % 2 + 1) * 5;
                    estado->jugador.pv += numrand;
                    cout << "¡Recibiste una poción! Recuperaste " << numrand << " de vida!" << endl;
                }
                if (f == 'T') {
                    numrand = (rand() % 2 + 1) * 5;
                    estado->jugador.pv -= numrand;
                    cout << "¡Cofre trampa, perdiste " << numrand << " de vida!" << endl;
                }

                (estado->cofres + i)->abierto = true;
                guardarEstado(estado, ARCHIVO_BINARIO);
            }
            else {
                cout << "Ya buscaste en este cofre." << endl;
            }
            break;
        }
    }

    if (!cofreEncontrado) {
        cout << "No hay un cofre aquí." << endl;
    }
}

void guardarSemilla(Juego* estado)
{
    int pos=0;
    estado->cadenaMapa[pos++]=(char)('A'+estado->N-1);
    int contVacios=0;  
    for(int i=0; i<estado->N; i++)
    {
        for(int j=0; j<estado->N; j++)
        {
            char casilla=*(*(estado->mapa+i)+j);
            if(casilla =='-')
            {
                contVacios++;

                if (contVacios == 26) {
                    estado->cadenaMapa[pos++] = 'Z';
                    contVacios = 0;
            }
            else
            {
                if(contVacios>0)
                {
                    estado->cadenaMapa[pos++]=(char)('A'+contVacios-1);
                    contVacios=0;
                }
                if(casilla=='#')
                {
                    estado->cadenaMapa[pos++]='S';
                }
                else if(casilla=='@')
                {
                    estado->cadenaMapa[pos++]='J';
                }
                else if(casilla=='E')
                {
                    estado->cadenaMapa[pos++]='E';
                }
                else if(casilla=='?')
                {
                    estado->cadenaMapa[pos++]='?';
                }
            }
        }
    }
    if(contVacios>0)
    {
        estado->cadenaMapa[pos++] = (char)('A' + contVacios - 1); 
    }

    estado->cadenaMapa[pos] = '\0';
}

int main(int argc, char* argv[]){
    if(argc < 2)
    {
        cout << "Uso: ./juego <comando> [opciones]\n";
        return 1;
    }
    string comando = argv[1];

    if (comando == "start") {
        empezarJuego();
    }
    else if (comando == "board") {
        Juego estado;
        if (cargarEstado(&estado, ARCHIVO_BINARIO)) {
            mostrarTablero(&estado);
        }
    } 
    else if (comando == "stats") {
        Juego estado;
        if (cargarEstado(&estado, ARCHIVO_BINARIO)) {
            mostrarStats(&estado);
        }
    } 
    else if (comando == "move") {
        if (argc >= 3)
        {
            Juego estado; 
            if(cargarEstado(&estado, ARCHIVO_BINARIO))
            {
                moverJugador(argv[2], &estado); 
            }
        } else {
            cout << "Uso: ./juego move [up|down|left|right]\n"; 
        }
    } 
    else if (comando == "seek") {
        Juego estado;
        if (cargarEstado(&estado, ARCHIVO_BINARIO)) {
            explorarCofre(&estado); 
        }
    } 
    else if (comando == "attack") {
        Juego estado;
        if (cargarEstado(&estado, ARCHIVO_BINARIO)) {
            cout << "[Modulo Enemigos]: Se ejecutará el ataque al enemigo...\n";
            ejecutarAtaque(&estado); 
            guardarEstado(&estado, ARCHIVO_BINARIO);
        }
    }

    return 0;
}