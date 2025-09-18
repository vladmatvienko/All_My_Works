import java.util.Scanner;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class Lab_N_2_2 {
    public static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        while (true) {
            int q = 0;
            int w = 0;
            int e = 0;
            int r = 0;
            boolean t = false;
            System.out.print("Пароль: ");
            String pass = sc.next();
            if (pass.length() < 8) {
                System.out.println("Пароль ненадежен. Повторите ввод.");
                continue;
            }
            for (int i = 0; i < pass.length(); i++) {
                String pass1 = pass.substring(i,i+1);
                Pattern p1 = Pattern.compile("[a-z]");
                Pattern p2 = Pattern.compile("[A-Z]");
                Pattern p3 = Pattern.compile("[0-9]");
                Pattern p4 = Pattern.compile("[/_]");
                Matcher m1 = p1.matcher(pass1);
                Matcher m2 = p2.matcher(pass1);
                Matcher m3 = p3.matcher(pass1);
                Matcher m4 = p4.matcher(pass1);
                if (m1.matches()){
                    q++;
                    continue;
                }
                else if ((m2.matches())){
                    w++;
                    continue;
                }
                else if ((m3.matches())){
                    e++;
                    continue;
                }
                else if ((m4.matches())){
                    r++;
                    continue;
                }
                else{
                    t = true;
                    break;
                }
            }
            if (t){continue;}
            if (q>0 & w>0 & e>0){
                System.out.println("Пароль надежен");
                break;
            }
        }
    }
}