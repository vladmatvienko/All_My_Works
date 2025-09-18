public class Drob {
    private int numerator;
    private int denomenator;
    public void setDenomenator(int denomenator) {
        if (denomenator == 0) {
            System.out.println("Знаменатель не может равняться 0");
            System.exit(1);
        } else {
            this.denomenator = denomenator;
        }
    }
    public void setNumerator(int numerator) {
        this.numerator = numerator;
    }
    public int getNumerator() {
        return numerator;
    }
    public int getDenomenator() {
        return denomenator;
    }
    public void setTheSameNumPLus(Drob first, Drob second) {
        this.numerator = first.getNumerator() + second.getNumerator();
    }
    public void setCommonNumPlus(Drob first, Drob second) {
        this.numerator = first.getNumerator() * second.getDenomenator() + second.getNumerator() * first.getDenomenator();
    }
    public void setCommonNumMinus(Drob first, Drob second) {
        this.numerator = (first.getNumerator() * second.getDenomenator()) - (first.getDenomenator() * second.getNumerator());
    }
    public void print() {
        System.out.println(numerator + "/" + denomenator);
    }
    public void setTheSameDenom(int denom) {
        this.denomenator = denom;
    }
    public void setTheSameNumMinus(Drob first, Drob second) {
        this.numerator = first.getNumerator() - second.getNumerator();
    }
    public void setCommonDenom(Drob first, Drob second) {
        this.denomenator = first.getDenomenator() * second.getDenomenator();

    }
    public void setMultiplying(Drob first, Drob second) {
        this.numerator = (first.getNumerator() * second.getNumerator());
        this.denomenator = (first.getDenomenator() * second.getDenomenator());
    }
    public void setDivision(Drob first, Drob second) {
        this.numerator = (first.getNumerator() * second.getDenomenator());
        this.denomenator = (first.getDenomenator() * second.getNumerator());
    }
}