package com.mechadeluel.mechaduel.modelo;

import java.util.ArrayList;
import java.util.List;

public abstract class Robot {
    protected int hp;
    protected int atk;
    protected int def;
    protected int spd;
    protected int nrg;
    protected List<String> efectosEstado; //esto aca es para colocarle quemadura, regeneración, etc

    public Robot(int atk, int def, int spd, int nrg){
        if((atk + def + spd + nrg) != 200){
            throw new IllegalArgumentException("La suma de las estadísticas debe dar 200");
        }
        this.hp = 100;
        this.atk = atk;
        this.def = def;
        this.nrg = nrg;
        this.spd = spd;
        this.efectosEstado = new ArrayList<>();
    }

    public abstract String ejecutarHabilidadEspecial();

    public int getHp() { return hp; }
    public void setHp(int hp) { this.hp = Math.max(0, hp); }

    public int getAtk() {return atk; }
    public int getDef() {return def; }
    public int getSpd() {return spd; }
    public int getNrg() {return nrg; }
    public void setNrg(int nrg) { this.nrg = nrg;}

    public List<String> getEfectosEstado() {return efectosEstado; }
}
