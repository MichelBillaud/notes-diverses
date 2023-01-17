
package testsstreams;

import java.time.LocalDate;

class Personne {
    private final String nom;
    private final String prenom;
    private final LocalDate naissance;

    public Personne(String prenom, String nom, int jour, int mois, int annee) {
        this.nom = nom;
        this.prenom = prenom;
        this.naissance = LocalDate.of(annee, mois, jour);        
    }

    public String getNom() {
        return nom;
    }

    public String getPrenom() {
        return prenom;
    }

    public int getAnnee() {
        return naissance.getYear();
    }
    
    public int getMois() {
        return naissance.getMonthValue();
    }
    public int getJour() {
        return naissance.getDayOfMonth();
    }
   
    
}
