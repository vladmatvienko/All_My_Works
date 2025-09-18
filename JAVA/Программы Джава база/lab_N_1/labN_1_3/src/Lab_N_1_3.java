import java.util.Scanner;
public class Lab_N_1_3 {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);

        System.out.print("X: ");
        double x = in.nextDouble();
        System.out.print("N: ");
        int n = in.nextInt();
        while (n > 15 | n < -15) {
            if (n > 15 | n < -15) {
                System.out.println("Ошибка, введите число меньше 15, но больше -15");
                System.out.print("N: ");
                n = in.nextInt();
            }
        }
        if (n == 0) {
            x = 1;
        }
        double i = x;
        if (n<-1){
            x = 1/x;
        }
        while (n < -1) {
            x = x / i;
            n = n + 1;
            System.out.println(n);
        }
        while (n > 1) {
            x = x * i;
            n = n - 1;
        }
        System.out.print(x);
    }
}