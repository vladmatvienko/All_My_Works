import java.util.Arrays;
import java.util.Scanner;
import java.util.Stack;

class Main
{
    public static void main(String[] args) {for (int k = 0; k < g; k++) {
        if (array[k].equals("*")) {
            if (array[k + 2].equals("/") & array[k - 2].equals("/")) {
                oneDrob.setNumerator(Integer.parseInt(array[k - 3]));
                oneDrob.setDenumerator(Integer.parseInt(array[k - 1]));
                twoDrob.setNumerator(Integer.parseInt(array[k + 1]));
                twoDrob.setDenumerator(Integer.parseInt(array[k + 3]));
                lastDrob.setMultiply(oneDrob, twoDrob);
                lastDrob.print();
                array[k] = "";
                array[k + 1] = "";
                array[k + 2] = "";
                array[k + 3] = "";
                array[k - 1] = String.valueOf(lastDrob.getDenumerator());
                array[k - 2] = "/";
                array[k - 3] = String.valueOf(lastDrob.getNumerator());
                y = y + 4;
            }
        }
    }
        for (int k = 0; k < g; k++) {
            if (array[k].equals(":")) {
                if (array[k + 2].equals("/") & array[k - 2].equals("/")) {
                    oneDrob.setNumerator(Integer.parseInt(array[k - 3]));
                    oneDrob.setDenumerator(Integer.parseInt(array[k - 1]));
                    twoDrob.setNumerator(Integer.parseInt(array[k + 1]));
                    twoDrob.setDenumerator(Integer.parseInt(array[k + 3]));
                    lastDrob.setDivide(oneDrob, twoDrob);
                    lastDrob.print();
                    array[k] = "";
                    array[k + 1] = "";
                    array[k + 2] = "";
                    array[k + 3] = "";
                    array[k - 1] = String.valueOf(lastDrob.getDenumerator());
                    array[k - 2] = "/";
                    array[k - 3] = String.valueOf(lastDrob.getNumerator());
                    y = y + 4;
                }
            }
        }
        System.out.println(Arrays.toString(array));
        String[] array2 = new String[g - y];
        int u = 0;
        for (int k = 0; k < g; k++) {
            if (!array[k].equals("")) {
                array2[u] = array[k];
                u = u + 1;
            }
        }
        array = array2;
        for (int k = 0; k < g - y; k++) {
            if (array[k].equals("/")) {
                if (array[k - 2].equals("(") & array[k + 2].equals(")")) {
                    array[k + 2] = "";
                    array[k - 2] = "";
                    y = y + 2;
                }
            }
        }
        g = g - y;
        System.out.println(Arrays.toString(array));
    }
}