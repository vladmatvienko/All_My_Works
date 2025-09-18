public class Person {
    private String name;

    public Person(String name) {
        this.name = name;
    }

    public boolean equals(Person p) {
        return p.name.equals(this.name);
    }
}