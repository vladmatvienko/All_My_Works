import java.util.Scanner;
public class Lab_N_1_2 {
    public static void main (String[] args) {
        Scanner in = new Scanner(System.in);
        System.out.print("День: ");
        int day = in.nextInt();
        while (day > 31) {
            if (day > 31) {
                System.out.println("Ошибка, введите число меньше 31");
                System.out.print("День: ");
                day = in.nextInt();
            }
        }
        System.out.print("Месяц: ");
        int month = in.nextInt();
        while (month > 12) {
            if (month > 12) {
                System.out.println("Ошибка, введите число меньше 12");
                System.out.print("Месяц: ");
            }
        }
        if (5 >= month) {
            if (month >= 3) {
                System.out.print("Весна");
            }
        }
        if (8 >= month) {
            if (month >= 6) {
                System.out.print("Лето");
            }
        }
        if (11 >= month) {
            if (month >= 9) {
                System.out.print("Осень");
            }
        }
        if (month==12|month==1|month==2)  {
            System.out.print("Зима");
        }
        }
    }