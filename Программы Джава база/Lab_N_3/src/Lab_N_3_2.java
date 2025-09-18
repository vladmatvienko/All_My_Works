import java.util.Scanner;
public class Lab_N_3_2 {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int array[] = new int[0];
        int i = 0;
        int g = 1;
        int exception = 0;
        System.out.print("Число к удалению: ");
        if (in.hasNextInt()) {
            exception = in.nextInt();
            System.out.print("Введите член массива: ");
        } else {
            System.out.println("Ошибка, массив и число к удалению должны быть целыми");
        }
        if (in.hasNextInt()) {
            while (!in.hasNext("quit") & in.hasNextInt()) {
                System.out.print("Введите член массива: ");
                int array1[] = array;
                if (in.hasNextInt()) {
                    array = new int[g];
                    array[i] = in.nextInt();
                    for (int k = 0; k < g - 1; k++) {
                        array[k] = array1[k];
                    }
                    g = g + 1;
                    i++;
                }
            }
            for (int elem : array)
                System.out.print(elem + " ");
            System.out.println(" ");
            if (in.hasNext("quit")) {
                int p = 1;
                i = 0;
                int array2[] = new int[0];
                for (int k = 0; k < g - 1; k++) {
                    if (array[k] != exception) {
                        int array1[] = array2;
                        array2 = new int[p];
                        array2[i] = array[k];
                        for (int z = 0; z < p - 1; z++) {
                            array2[z] = array1[z];
                        }
                        p = p + 1;
                        i++;
                    }
                }
                for (int elem : array2)
                    System.out.print(elem + " ");
            }
        }
    }
}