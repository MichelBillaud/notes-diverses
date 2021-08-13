package reconnaisseur;

interface Reco {

    default Reco and(Reco other) {
        return new AndReco(this, other);
    }

    default Reco or(Reco other) {
        return new OrReco(this, other);
    }
    
    default Reco loop() {
        return new LoopReco(this);
    }
}
