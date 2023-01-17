package testsstreams;

/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/**
 *
 * @author billaud
 */
public class Etudiant {
    final String nom;
    final double note;

    public Etudiant(String nom, double note) {
        this.nom = nom;
        this.note = note;
    }

    public String getNom() {
        return nom;
    }

    public double getNote() {
        return note;
    }
    
}
