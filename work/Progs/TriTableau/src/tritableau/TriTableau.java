package tritableau;

import java.util.Comparator;

public class TriTableau {

    public static void main(String[] args) {
        Personne[] tableau = {
            new Personne("Joe", 32, 2500),
            new Personne("Bob", 23, 2200),
            new Personne("Anna", 24, 2300),
            new Personne("Charles", 54, 4400)
        };

        
        afficher("avant tri", tableau);
        trier_par_age(tableau);
        afficher("par age", tableau);
        trier_par_critere(tableau, (p1, p2) -> p2.salaire - p1.salaire);
        afficher("par salaire decroissant", tableau);
    }

    private static void trier_par_age(Personne[] tableau) {
        for (int i = 0; i < tableau.length; i++) {
            int best = i;
            for (int j = i + 1; j < tableau.length; j++) {
                if (tableau[j].age < tableau[best].age) {
                    best = j;
                }
            }
            Personne tmp = tableau[i];
            tableau[i] = tableau[best];
            tableau[best] = tmp;
        }
    }

       private static void trier_par_critere(Personne[] tableau, 
               Comparator<Personne> comparator) {
            for (int i = 0; i < tableau.length; i++) {
            int best = i;
            for (int j = i + 1; j < tableau.length; j++) {
                if (comparator.compare(tableau[j], tableau[best]) < 0) {
                    best = j;
                }
            }
            Personne tmp = tableau[i];
            tableau[i] = tableau[best];
            tableau[best] = tmp;
        }
           
           
       }
    private static void afficher(String message, Personne[] tableau) {
        System.out.format("* Affichage %s\n", message);
        for (Personne p : tableau) {
            System.out.format("%10s %5d %5d\n", p.nom, p.age, p.salaire);
        }
    }

    private static class Personne {

        String nom;
        int age, salaire;

        public Personne(String nom, int age, int salaire) {
            this.nom = nom;
            this.age = age;
            this.salaire = salaire;
        }

    }

}
