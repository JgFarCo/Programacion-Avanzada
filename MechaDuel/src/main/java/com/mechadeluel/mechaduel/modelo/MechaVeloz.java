package com.mechadeluel.mechaduel.modelo;

public class MechaVeloz extends Robot {

    public MechaVeloz(int atk, int def, int spd, int nrg) {
        super(atk, def, spd, nrg);
    }

    @Override
    public String ejecutarHabilidadEspecial() {
        this.spd += 10;
        return "¡Arquetipo de velocidad activado! La velocidad ha aumentado";
    }
}
