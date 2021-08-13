package testsstreams;

import java.util.ArrayList;
import java.util.Comparator;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.OptionalDouble;
import java.util.function.Function;
import java.util.function.ToDoubleFunction;
import java.util.stream.Collector;
import java.util.stream.Collectors;

/**
 *
 * @author billaud
 */
public class TestsStreams {

    /**
     * @param args the command line arguments
     */
    private static class Paire {

        int total = 0;
        int nombre = 0;

        void accepter(int n) {
            total += n;
            nombre += 1;
        }

        Paire combiner(Paire autre) {
            total += autre.total;
            nombre += autre.nombre;
            return this;
        }

        double extraireResultat() {
            return (double) total / nombre;
        }

    };

    public static void main(String[] args) {
        testsPersonnes();
        testsEtudiants();
        testsStock();

        List<Integer> liste = List.of(30, 40);
        int s = liste.parallelStream()
                .mapToInt(x -> x * x)
                .sum();
        System.out.println("reduction = " + s);

        int c = liste.parallelStream()
                .reduce(0, (acc, v) -> acc + 1, Integer::sum);
        System.out.println("reduction = " + s);

        Collector<Integer, Paire, Double> moyenneur = Collector.of(
                Paire::new,
                Paire::accepter,
                Paire::combiner,
                Paire::extraireResultat
        );
        double moyenne = liste.stream().collect(moyenneur);;
        System.out.println("moyenne" + moyenne);
    }

    private static void testsPersonnes() {
        List<Personne> personnes = List.of(
                new Personne("Charles", "De Gaulle", 22, 11, 1890),
                new Personne("Georges", "Pompidou", 5, 7, 1911),
                new Personne("Valéry", "Giscard d'Estaing", 2, 1, 1926),
                new Personne("François", "Mitterrand", 26, 10, 1916),
                new Personne("Jacques", "Chirac", 29, 11, 1932),
                new Personne("Nicolas", "Sarkozy", 28, 1, 1955),
                new Personne("François", "Hollande", 12, 8, 1954),
                new Personne("Emmanuel", "Macron", 21, 12, 1977)
        );

        System.out.println("* Les collections ont une méthode forEach");
        System.out.println("- Affichage nom et prénom");
        personnes
                .forEach(p -> System.out.println(
                p.getPrenom() + " " + p.getNom()));

        System.out.println("* La méthode stream() fournit un objet (Stream) "
                + "qui a aussi une méthode forEach()"
        );
        personnes.stream()
                .forEach(p -> System.out.println(
                p.getPrenom() + " " + p.getNom()));

        System.out.println("* On peut appliquer des traitements à un stream. "
                + "sorted() produit un autre stream()."
        );
        System.out.println("- liste triée par prénom");
        personnes.stream()
                .sorted(Comparator.comparing(Personne::getPrenom))
                .forEach(p -> System.out.println(
                p.getPrenom() + " " + p.getNom()));
        System.out.println("l'opération filter sélectionne");
        personnes.stream()
                .filter(p -> p.getAnnee() >= 1950)
                .sorted(Comparator.comparing(Personne::getPrenom))
                .forEach(p -> System.out.println(p.getPrenom() + " " + p.getNom()));
        System.out.println("l'opération map applique une transformation");
        Function<Personne, String> anneePrenomNom
                = p -> String.format("%d\t%s %s",
                        p.getAnnee(), p.getPrenom(), p.getNom());
        personnes.stream()
                .sorted(Comparator.comparing(Personne::getAnnee))
                .map(anneePrenomNom)
                .forEach(System.out::println);

        ArrayList<Personne> tmp = new ArrayList(personnes);
        tmp.sort(Comparator.comparing(Personne::getPrenom));

        String prenom = "Albert";

        boolean trouve = personnes.stream()
                .anyMatch(s -> s.getPrenom().equals(prenom));
        System.out.println("trouve = " + trouve);

        personnes.stream()
                .mapToInt(Personne::getAnnee)
                .average();

        Optional<Personne> findFirst = personnes.stream()
                .filter(p -> p.getAnnee() == 1923)
                .findFirst();
        ;

    }

    private static void testsStock() {

        // soit à calculer la valeur d'un stock d'objets
        // pour chaque objet, on a sa désignation, la quantité en stock et son prix unitaire
        List<Produit> stock = List.of(
                new Produit("Truc", 12, 3.50),
                new Produit("Machin", 10, 21.00)
        );

        // l'expression suivante calcule la valeur pour un produit donné
        ToDoubleFunction<Produit> valeur;
        valeur = p -> p.prixUnitaire * p.getQuantite();

        stock.stream().mapToDouble(valeur).sum();

        Optional<Produit> produitLePlusCher
                = stock.stream()
                        .max(Comparator.comparingDouble(Produit::getPrixUnitaire));
        System.out.println("max" + produitLePlusCher.get().designation);

    }

    private static void testsEtudiants() {
        List<Etudiant> etudiants = List.of(
                new Etudiant("Anna", 14.5),
                new Etudiant("Bob", 12),
                new Etudiant("Charlie", 8.0),
                new Etudiant("Dora", 17)
        );

        OptionalDouble moyenne = etudiants.stream()
                .mapToDouble(Etudiant::getNote)
                .average();

        Map<String, Double> parnom = etudiants.stream()
                .collect(Collectors.toMap(Etudiant::getNom, Etudiant::getNote));
       
        Map<Double, List<Etudiant>> collect = etudiants.stream()
                .collect(Collectors.groupingBy(Etudiant::getNote));
        
        
        etudiants.stream()
                .collect(Collectors.groupingBy(Etudiant::getNote, 
                        Collectors.mapping(Etudiant::getNom, 
                                Collectors.toSet())));
        
                      
                        
    }

}
