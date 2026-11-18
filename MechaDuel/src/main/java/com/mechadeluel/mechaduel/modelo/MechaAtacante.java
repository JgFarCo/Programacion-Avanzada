package com.mechadeluel.mechaduel.modelo;

public class MechaAtacante extends Robot {

    public MechaAtacante(int atk, int def, int spd, int nrg) {
        super(atk, def, spd, nrg);
    }

    @Override
    public String ejecutarHabilidadEspecial() {
        this.atk += 5;
        return "¡Arquetipo atacante activado! El ataque ha aumentado";
    }
}
