import java.util.Scanner;
public class Lab_1_4 {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        System.out.print("Количество: ");
        int kolxy = in.nextInt();
        int counter = 1;
        while (kolxy <= 0) {
            if (kolxy <= 0) {
                System.out.println("Ошибка, введите число больше 0");
                System.out.print("Количество: ");
                kolxy = in.nextInt();
            }
        }
        System.out.print("Радиус: ");
        int R = in.nextInt();
        while (R < 0) {
            if (R < 0) {
                System.out.println("Ошибка, введите число больше или равное 0");
                System.out.print("Радиус: ");
                R = in.nextInt();
            }
        }
        int kol = 0;
        int N = 1;
        while (counter <= kolxy) {
            System.out.print("X");
            System.out.print(N);
            System.out.print(": ");
            int X = in.nextInt();
            System.out.print("Y");
            System.out.print(N);
            System.out.print(": ");
            int Y = in.nextInt();
            N = N + 1;
            counter = counter + 1;
            if (X * X + Y * Y <= R * R) {
                kol = kol + 1;
            }
        }
        System.out.print(kol);
        System.out.println(" точек попали в окружность");
    }
}