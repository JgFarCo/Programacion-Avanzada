package com.mechadeluel.mechaduel.interfaz;

import com.mechadeluel.mechaduel.modelo.MechaTanque;
import com.mechadeluel.mechaduel.modelo.MechaAtacante;
import com.mechadeluel.mechaduel.modelo.MechaVeloz;
import com.mechadeluel.mechaduel.modelo.Robot;
import java.util.Scanner;

public class ConsolaJuego {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        System.out.println("=== Sé Bienvenido a MECHA DUEL ===");
        System.out.println("Entrando a etapa de preparación...");

        System.out.println("Selecciona el arquetipo que deseas para tu mecha: ");
        System.out.println("1. Mecha Tanque (Especializado en resistencia y blindaje)");
        System.out.println("2. Mecha Veloz (Especializado en agilidad y turnos)");
        System.out.println("3. Mecha Atacante (Especializado en ofensiva y fuerza");
        System.out.print("Elige una opción (1, 2 o 3): ");
        int opcionArquetipo = scanner.nextInt();

        System.out.println("Asigna tus puntos para el combate (la suma de todos debe ser igual a 200");

        int atk, def, nrg, spd;
        while(true) {
            System.out.print("Ingresa el valor del ataque (ATK): ");
            atk = scanner.nextInt();
            System.out.print("Ingresa el valor de la defensa (DEF): ");
            def = scanner.nextInt();
            System.out.print("Ingresa el valor de la velocidad (SPD): ");
            spd = scanner.nextInt();
            System.out.print("Ingresa el valor de la energía (NRG): ");
            nrg = scanner.nextInt();

            if((atk + def + spd + nrg) == 200){
                break;
            }
            System.out.println("Ocurrió un error... la suma total debe ser 200. Intente otra vez. Use calculadora de ser necesario.\n");
        }

        Robot RobotTransmilenio;

        if(opcionArquetipo == 1) {
            RobotTransmilenio = new MechaTanque(atk, def, spd, nrg);
            System.out.println("\n¡Has ensamblado en un Mecha de tipo tanque!");
        }
        if(opcionArquetipo == 2) {
            RobotTransmilenio = new MechaVeloz(atk, def, spd, nrg);
            System.out.println("\n¡Has ensamblado en un Mecha de tipo veloz!");
        }
        if(opcionArquetipo == 3) {
            RobotTransmilenio = new MechaAtacante(atk, def, spd, nrg);
            System.out.println("\n¡Has ensamblado en un Mecha de tipo ataque!");
        }

        System.out.println("¡Ensamblaste tu robot con éxito! Tus HP iniciales: " + RobotTransmilenio.getHp());

        String mensajeHabilidad = RobotTransmilenio.ejecutarHabilidadEspecial();
        System.out.println("Habilidad del sistema: " + mensajeHabilidad);

        //aqui va el menu de combate y las opciones para la estrategia
    }
}
