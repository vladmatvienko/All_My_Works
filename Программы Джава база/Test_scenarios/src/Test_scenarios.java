import java.util.Scanner;
public class Test_scenarios {
    public static void main(String[] args) {
        System.out.print("Введите выражение:  ");
        Scanner in = new Scanner(System.in);
        while (!in.hasNext("quit")) {
            String s = in.next();
            int g = s.length();
            String[] array = new String[g];
            for (int k = 0; k < g; k++) {
                array[k] = String.copyValueOf(new char[]{s.charAt(k)});
            }
            System.out.print("Введите выражение, которое должно входить в первое:  ");
            String q = in.next();
            int w = q.length();
            String[] array1 = new String[w];
            for (int l = 0; l < w; l++) {
                array1[l] = String.copyValueOf(new char[]{q.charAt(l)});
            }
            int schet = 0;
            for (int k = 0; k < g - w + 1; k++) {
                int num = 0;
                String[] array2 = new String[w];
                for (int l = 0; l < w; l++) {
                    array2[l] = String.copyValueOf(new char[]{s.charAt(k + l)});
                }
                for (int l = 0; l < w; l++) {
                    if (array1[l].equals(array2[l])) {
                        num = num + 1;
                    }
                }
                if (num==w){
                    schet = schet + 1;
                }
            }
            System.out.print("Ответ: ");
            System.out.println(schet);
            System.out.print("Введите выражение:  ");
        }
        System.out.println("Завершение работы");
    }
}