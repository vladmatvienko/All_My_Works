import jdk.internal.icu.impl.CharacterIteratorWrapper;

import java.util.InputMismatchException;
import java.util.Scanner;
public class Main {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        Drob defaultDrob = new Drob();
        defaultDrob.setDenomenator(1);
        int defaultNum = defaultDrob.getNumerator();
        defaultDrob.setNumerator(1);
        int defaultDem = defaultDrob.getDenomenator();
        char op;
        char con;
        Drob firstDrob = new Drob();
        System.out.println("Введите числитель первой дроби");
        try {
            firstDrob.setNumerator(sc.nextInt());
        } catch (InputMismatchException e) {
            System.out.println("Введите число");
            System.exit(1);
        }
        int num1 = firstDrob.getNumerator();
        System.out.println("Введите знаменатель первой дроби");
        try {
            firstDrob.setDenomenator(sc.nextInt());
        } catch (InputMismatchException e) {
            System.out.println("Введите число");
            System.exit(1);
        }
        int den1 = firstDrob.getDenomenator();
        Drob secondDrob = new Drob();
        System.out.println("Введите числитель второй дроби");
        try {
            secondDrob.setNumerator(sc.nextInt());
        } catch (InputMismatchException e) {
            System.out.println("Введите число");
            System.exit(1);
        }
        int num2 = secondDrob.getNumerator();
        System.out.println("Введите знаменатель второй дроби");
        try {
            secondDrob.setDenomenator(sc.nextInt());
        } catch (InputMismatchException e) {
            System.out.println("Введите число");
            System.exit(1);
        }
        int den2 = secondDrob.getDenomenator();
        Drob lastDrob = new Drob();
        System.out.println("Выберите операцию, которую хотите выполнить(+, -, *, /): ");
        op = sc.next().charAt(0);
        if (den1 == den2) {
            switch (op) {
                case '+':
                    lastDrob.setTheSameDenom(den2);
                    lastDrob.setTheSameNumPLus(firstDrob, secondDrob);
                    break;
                case '-':
                    lastDrob.setTheSameDenom(den2);
                    lastDrob.setTheSameNumMinus(firstDrob, secondDrob);
                    break;
                case '*':
                    lastDrob.setMultiplying(firstDrob, secondDrob);
                    break;
                case '/':
                    lastDrob.setDivision(firstDrob, secondDrob);
                    break;
                default:
                    System.out.print("Ошибка! Введите правильную операцию!");
                    return;
            }
            lastDrob.print();
        } else {
            switch (op) {
                case '+':
                    lastDrob.setCommonDenom(firstDrob, secondDrob);
                    lastDrob.setCommonNumPlus(firstDrob, secondDrob);
                    break;
                case '-':
                    lastDrob.setCommonDenom(firstDrob, secondDrob);
                    lastDrob.setCommonNumMinus(firstDrob, secondDrob);
                    break;
                case '*':
                    lastDrob.setMultiplying(firstDrob, secondDrob);
                    break;
                case '/':
                    lastDrob.setDivision(firstDrob, secondDrob);
                    break;
                default:
                    System.out.print("Ошибка! Введите правильную операцию!");
                    return;
            }
            lastDrob.print();
        }
    }
}