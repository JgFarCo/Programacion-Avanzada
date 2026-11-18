package com.mechadeluel.mechaduel.modelo;

public class MechaTanque extends Robot {

    public MechaTanque(int atk, int def, int spd, int nrg) {
        super(atk, def, spd, nrg);
    }

    @Override
    public String ejecutarHabilidadEspecial() {
        //aca use polimorfismo, esto funciona tipo arquetipos para darle mas fuerza en algo a un robot
        this.def += 10 //defensa extra
        return "¡Arquetipo tanque activado! La defensa ha aumentado.";
    }
}
