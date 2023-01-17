/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package testsstreams;

/**
 *
 * @author billaud
 */
public class Produit {
    String designation;
    int quantite;
    double prixUnitaire;

    public Produit(String designation, int quantite, double prixUnitaire) {
        this.designation = designation;
        this.quantite = quantite;
        this.prixUnitaire = prixUnitaire;
    }

    public String getDesignation() {
        return designation;
    }

    public int getQuantite() {
        return quantite;
    }

    public double getPrixUnitaire() {
        return prixUnitaire;
    }
    
    
}
