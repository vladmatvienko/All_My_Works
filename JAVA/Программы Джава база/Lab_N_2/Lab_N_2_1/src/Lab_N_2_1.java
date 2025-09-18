import java.util.Scanner;
import java.util.regex.*;
public class Lab_N_2_1 {

     static void main(String[] args) {
        Scanner sc = new Scanner(System.in);
        System.out.print("Введите дату: ");
        String s1;
        s1 = sc.nextLine();
        String pattern = "(?:[0-9]{2}[\\/]){2}[0-9]{4}";
        Pattern p = Pattern.compile(pattern);
        Matcher m = p.matcher(s1);
        if (m.matches()) {
            int day = Integer.parseInt(s1.substring(0, 2));
            int month = Integer.parseInt(s1.substring(3, 5));
            if (((month == 1 | month == 3 | month == 5 | month == 7 | month == 8 | month == 10 | month == 12) & day <= 31) | ((month == 4 | month == 6 | month == 9 | month == 11) & day <= 30) | ((month == 2) & day <= 28)) {
                int year = Integer.parseInt(s1.substring(6, 10));
                if (year >= 1900 & year <= 9999) {
                    System.out.print("Введенное выражение является датой");
                }
            }
            else {
                    System.out.println("Введенное выражение не является датой");
                }
            }
        else{
        System.out.println("Введенное выражение не соответствует заданному формату даты dd/mm/yyyy");
        }
    }
}

