import java.lang.reflect.Array;
import java.util.Scanner;
public class Vvod {
    public static void main(String[] args) {
        System.out.println("Введите выражение без пробелов");
        Scanner in = new Scanner(System.in);
        while (!in.hasNext("quit")) {
            String s = "("+in.next()+")";
                int g;
                g = s.length();
                String[] array = new String[g];
                int t = 0;
                for (int k = 0; k < g; k++) {
                    String l = String.valueOf(s.charAt(k));
                    if (l.equals("1") | l.equals("2") | l.equals("3") | l.equals("4") | l.equals("5") | l.equals("6") | l.equals("7") | l.equals("8") | l.equals("9") | l.equals("0") | l.equals("+") | l.equals("-") | l.equals("/") | l.equals("*") | l.equals(":") | l.equals("(") | l.equals(")")) {
                        array[k] = String.copyValueOf(new char[]{s.charAt(k)});
                        t = t + 1;
                    } else {
                        System.out.println("Введено недопустимое значение");
                    }
                }
                int mud = 0;
            for (int j = 0; j < g; j++) {
                if (array[j].equals("-")) {
                    if (array[j + 1].equals("-")) {
                        mud = mud + 1;
                    }
                }
            }
                if (mud==0) {
                    int i = 0;
                    int q = 0;
                    if (t == g) {
                        for (int k = 0; k < g; k++) {
                            if (array[k].equals("+") | array[k].equals("/") | array[k].equals("*") | array[k].equals(":")) {
                                q = q + 1;
                                if ((array[k + 1].equals("1") | array[k + 1].equals("2") | array[k + 1].equals("3") | array[k + 1].equals("4") | array[k + 1].equals("5") | array[k + 1].equals("6") | array[k + 1].equals("7") | array[k + 1].equals("8") | array[k + 1].equals("9") | array[k + 1].equals("(") | array[k + 1].equals(")") | array[k + 1].equals("-")) & (array[k - 1].equals("0") | array[k - 1].equals("1") | array[k - 1].equals("2") | array[k - 1].equals("3") | array[k - 1].equals("4") | array[k - 1].equals("5") | array[k - 1].equals("6") | array[k - 1].equals("7") | array[k - 1].equals("8") | array[k - 1].equals("9") | array[k - 1].equals("(") | array[k - 1].equals(")"))) {
                                    i = i + 1;
                                }
                            }
                        }
                    }
                    int amountofnumbers = 0;
                    int amountofseparation = 0;
                    int amountofbracketleft = 0;
                    int amountofbracketright = 0;
                    int w = 0;
                    if (q == i) {
                        for (int j = 0; j < g; j++) {
                            if (array[j].equals("(")) {
                                amountofbracketleft = amountofbracketleft + 1;
                            }
                        }
                        for (int j = 0; j < g; j++) {
                            if (array[j].equals(")")) {
                                amountofbracketright = amountofbracketright + 1;
                            }
                        }
                        for (int j = 0; j < g; j++) {
                            if (array[j].equals("/")) {
                                amountofseparation = amountofseparation + 1;
                            }
                        }
                        for (int j = 0; j < g; j++) {
                            if (array[j].equals("0") | array[j].equals("1") | array[j].equals("2") | array[j].equals("3") | array[j].equals("4") | array[j].equals("5") | array[j].equals("6") | array[j].equals("7") | array[j].equals("8") | array[j].equals("9")) {
                                amountofnumbers = amountofnumbers + 1;
                            }
                        }

                        if (amountofnumbers / 2 == amountofseparation & amountofbracketleft == amountofbracketright) {
                            w = w + 1;
                        } else {
                            System.out.println("Неправильное построение выражения");
                        }
                    }else {
                        System.out.println("Неправильное построение выражения");
                    }
                    Drob oneDrob = new Drob();
                    Drob twoDrob = new Drob();
                    Drob lastDrob = new Drob();
                    if (w == 1) {
                        for (int k = 0; k < g; k++) {
                            if (array[k].equals("/")) {
                                if (array[k + 1].equals("-")) {
                                    String numb1 = array[k - 1];
                                    if (array[k - 2].equals("-")) {
                                        array[k + 1] = "";
                                        array[k - 2] = "";
                                    } else {
                                        array[k - 1] = "-";
                                        array[k] = numb1;
                                        array[k + 1] = "/";
                                    }
                                }
                            }
                        }
                        int hi = 0;
                        for (int k = 0; k < g; k++) {
                            if (!array[k].equals("")) {
                                hi = hi + 1;
                            }
                        }
                        String[] array3 = new String[hi];
                        hi = 0;
                        for (int k = 0; k < g; k++) {
                            if (!array[k].equals("")) {
                                array3[hi] = array[k];
                                hi = hi + 1;
                            }
                        }
                        array = array3;
                        g = array.length;
                        while (g > 4) {
                            int x = 4454545;
                            int i1 = 0;
                            int i2 = 0;
                            for (int a = 0; a < g; a++) {
                                if (array[a].equals("(")) {
                                    for (int b = 0; b < g; b++) {
                                        if (array[b].equals(")") & b - a <= x & b - a > 0) {
                                            x = b - a - 1;
                                            i1 = a + 1;
                                            i2 = b - 1;
                                        }
                                    }
                                }
                            }
                            int num = 0;
                            String[] array1 = new String[x];
                            if (x != 4454545) {
                                for (; i1 <= i2; i1++) {
                                    array1[num] = array[i1];
                                    array[i1] = "";
                                    num = num + 1;
                                }
                            }
                            int num1 = 0;
                            for (int a = 0; a < g; a++) {
                                if (array[a].equals("")) {
                                    num1 = num1 + 1;
                                }
                            }
                            i1 = i1 - num;
                            int y = 0;
                            if (x == 4454545) {
                                array1 = array;
                                x = array.length;
                            } else {
                                array[i2 + 1] = "";
                                array[i1 - 1] = "";
                            }
                            for (int k = 0; k < x; k++) {
                                if (array1[k].equals("*")) {
                                    if (array1[k + 2].equals("/") & array1[k - 2].equals("/")) {
                                        oneDrob.setNumerator(Integer.parseInt(array1[k - 3]));
                                        oneDrob.setDenumerator(Integer.parseInt(array1[k - 1]));
                                        twoDrob.setNumerator(Integer.parseInt(array1[k + 1]));
                                        twoDrob.setDenumerator(Integer.parseInt(array1[k + 3]));
                                        lastDrob.setMultiply(oneDrob, twoDrob);
                                        array1[k] = "";
                                        array1[k + 1] = "";
                                        array1[k + 2] = "";
                                        array1[k + 3] = "";
                                        array1[k - 1] = String.valueOf(lastDrob.getDenumerator());
                                        array1[k - 2] = "/";
                                        array1[k - 3] = String.valueOf(lastDrob.getNumerator());
                                        y = y + 4;
                                    }
                                }
                            }
                            String[] array2 = new String[x - y];
                            int u = 0;
                            for (int k = 0; k < x; k++) {
                                if (!array1[k].equals("")) {
                                    array2[u] = array1[k];
                                    u = u + 1;
                                }
                            }
                            array1 = array2;
                            x = x - y;
                            y = 0;
                            for (int k = 0; k < x; k++) {
                                if (array1[k].equals(":")) {
                                    if (array1[k + 2].equals("/") & array1[k - 2].equals("/")) {
                                        oneDrob.setNumerator(Integer.parseInt(array1[k - 3]));
                                        oneDrob.setDenumerator(Integer.parseInt(array1[k - 1]));
                                        twoDrob.setNumerator(Integer.parseInt(array1[k + 1]));
                                        twoDrob.setDenumerator(Integer.parseInt(array1[k + 3]));
                                        lastDrob.setDivide(oneDrob, twoDrob);
                                        array1[k] = "";
                                        array1[k + 1] = "";
                                        array1[k + 2] = "";
                                        array1[k + 3] = "";
                                        array1[k - 1] = String.valueOf(lastDrob.getDenumerator());
                                        array1[k - 2] = "/";
                                        array1[k - 3] = String.valueOf(lastDrob.getNumerator());
                                        y = y + 4;
                                    }
                                }
                            }
                            array2 = new String[x - y];
                            u = 0;
                            for (int k = 0; k < x; k++) {
                                if (!array1[k].equals("")) {
                                    array2[u] = array1[k];
                                    u = u + 1;
                                }
                            }
                            array1 = array2;
                            x = x - y;
                            y = 0;
                            for (int k = 0; k < x; k++) {
                                if (array1[k].equals("+")) {
                                    if (k >= 4) {
                                        if (array1[k - 4].equals("-")) {
                                            if (array1[k + 2].equals("/") & array1[k - 2].equals("/")) {
                                                twoDrob.setNumerator(Integer.parseInt(array1[k - 3]));
                                                twoDrob.setDenumerator(Integer.parseInt(array1[k - 1]));
                                                oneDrob.setNumerator(Integer.parseInt(array1[k + 1]));
                                                oneDrob.setDenumerator(Integer.parseInt(array1[k + 3]));
                                                lastDrob.setMinus(oneDrob, twoDrob);
                                                int n = lastDrob.getNumerator();
                                                if (n < 0) {
                                                    n = n * -1;
                                                    array1[k] = String.valueOf(lastDrob.getDenumerator());
                                                    array1[k + 1] = "";
                                                    array1[k + 2] = "";
                                                    array1[k + 3] = "";
                                                    array1[k - 1] = "/";
                                                    array1[k - 2] = String.valueOf(n);
                                                    array1[k - 3] = "-";
                                                    y = y + 3;
                                                } else {
                                                    array1[k] = "";
                                                    array1[k + 1] = "";
                                                    array1[k + 2] = "";
                                                    array1[k + 3] = "";
                                                    array1[k - 1] = String.valueOf(lastDrob.getDenumerator());
                                                    array1[k - 2] = "/";
                                                    array1[k - 3] = String.valueOf(lastDrob.getNumerator());
                                                    array1[k - 4] = "";
                                                    y = y + 5;
                                                }
                                            }
                                        }
                                    } else {
                                        if (array1[k + 2].equals("/") & array1[k - 2].equals("/")) {
                                            oneDrob.setNumerator(Integer.parseInt(array1[k - 3]));
                                            oneDrob.setDenumerator(Integer.parseInt(array1[k - 1]));
                                            twoDrob.setNumerator(Integer.parseInt(array1[k + 1]));
                                            twoDrob.setDenumerator(Integer.parseInt(array1[k + 3]));
                                            lastDrob.setPlus(oneDrob, twoDrob);
                                            array1[k] = "";
                                            array1[k + 1] = "";
                                            array1[k + 2] = "";
                                            array1[k + 3] = "";
                                            array1[k - 1] = String.valueOf(lastDrob.getDenumerator());
                                            array1[k - 2] = "/";
                                            array1[k - 3] = String.valueOf(lastDrob.getNumerator());
                                            y = y + 4;
                                        }
                                    }
                                }
                            }
                            array2 = new String[x - y];
                            u = 0;
                            for (int k = 0; k < x; k++) {
                                if (!array1[k].equals("")) {
                                    array2[u] = array1[k];
                                    u = u + 1;
                                }
                            }
                            array1 = array2;
                            x = x - y;
                            y = 0;
                            for (int k = 1; k < x; k++) {
                                if (array1[k].equals("-")) {
                                    if (k >= 4) {
                                        if (array1[k - 4].equals("-")) {
                                            if (array1[k + 2].equals("/") & array1[k - 2].equals("/")) {
                                                oneDrob.setNumerator(Integer.parseInt(array1[k - 3]));
                                                oneDrob.setDenumerator(Integer.parseInt(array1[k - 1]));
                                                twoDrob.setNumerator(Integer.parseInt(array1[k + 1]));
                                                twoDrob.setDenumerator(Integer.parseInt(array1[k + 3]));
                                                lastDrob.setPlus(oneDrob, twoDrob);
                                                array1[k] = "";
                                                array1[k + 1] = "";
                                                array1[k + 2] = "";
                                                array1[k + 3] = "";
                                                array1[k - 1] = String.valueOf(lastDrob.getDenumerator());
                                                array1[k - 2] = "/";
                                                array1[k - 3] = String.valueOf(lastDrob.getNumerator());
                                                y = y + 4;
                                            }
                                        }
                                    } else {
                                        if (k >= 2) {
                                            if (array1[k + 2].equals("/") & array1[k - 2].equals("/")) {
                                                oneDrob.setNumerator(Integer.parseInt(array1[k - 3]));
                                                oneDrob.setDenumerator(Integer.parseInt(array1[k - 1]));
                                                twoDrob.setNumerator(Integer.parseInt(array1[k + 1]));
                                                twoDrob.setDenumerator(Integer.parseInt(array1[k + 3]));
                                                lastDrob.setMinus(oneDrob, twoDrob);
                                                array1[k] = "";
                                                array1[k + 1] = "";
                                                array1[k + 2] = "";
                                                array1[k + 3] = "";
                                                array1[k - 1] = String.valueOf(lastDrob.getDenumerator());
                                                array1[k - 2] = "/";
                                                array1[k - 3] = String.valueOf(lastDrob.getNumerator());
                                                y = y + 4;
                                            }
                                        }
                                    }
                                }
                            }
                            array2 = new String[x - y];
                            u = 0;
                            for (int k = 0; k < x; k++) {
                                if (!array1[k].equals("")) {
                                    array2[u] = array1[k];
                                    u = u + 1;
                                }
                            }
                            array1 = array2;
                            int gh = i1 + array1.length - 1;
                            u = 0;
                            for (; i1 - 1 < gh; i1++) {
                                array[i1] = array1[u];
                                u = u + 1;
                            }
                            u = 0;
                            for (int k = 0; k < g; k++) {
                                if (!array[k].equals("")) {
                                    u = u + 1;
                                }
                            }
                            array2 = new String[u];
                            u = 0;
                            for (int k = 0; k < g; k++) {
                                if (!array[k].equals("")) {
                                    array2[u] = array[k];
                                    u = u + 1;
                                }
                            }
                            array = array2;
                            g = array.length;
                        }
                        for (int l = 2; l < 10; l++) {
                            for (int k = 2; k < 100000; k++) {
                                for (int j = 0; j < g; j++) {
                                    if (array[j].equals("/")) {
                                        int key1 = Integer.parseInt(array[j - 1]);
                                        int key2 = Integer.parseInt(array[j + 1]);
                                        if (key1 % k == 0 & key2 % k == 0) {
                                            array[j - 1] = String.valueOf(key1 / k);
                                            array[j + 1] = String.valueOf(key2 / k);
                                        }
                                    }
                                }
                            }
                        }
                        System.out.print("Ответ: ");
                        for (int k = 0; k < g; k++) {
                            System.out.print(array[k]);
                        }
                        System.out.println();
                        System.out.println("Введите следующее выражение без пробелов");
                    }
                }
                else{
                    System.out.println("Неправильное построение выражения");
                }
        }
        System.out.println("Завершение работы");
    }
}