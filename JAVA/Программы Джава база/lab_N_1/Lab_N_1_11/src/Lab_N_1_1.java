import java.util.Scanner;
public class Lab_N_1_1 {
    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        System.out.print("Месяц рождения: ");
        int month = in.nextInt();
        while (month > 12 | month < 0) {
            if (month > 12 | month < 0) {
                System.out.println("Ошибка, введите число меньше 12");
                System.out.print("Месяц рождения: ");
                month = in.nextInt();
            }
        }
        System.out.print("День рождения: ");
        int raznost;
        int day = in.nextInt();
            if (month == 1 | month == 3 | month == 5 | month == 7 | month == 8 | month == 10 | month == 12) {
                while (day > 31 | day < 0) {
                    if (day > 31 | day < 0) {
                        System.out.println("Ошибка, введите число меньше 31");
                        System.out.print("День рождения: ");
                        day = in.nextInt();
                    }
                }
            }
            if (month == 4 | month == 6 | month == 9 | month == 11) {
                while (day > 30 | day < 0) {
                    if (day > 30 | day < 0) {
                        System.out.println("Ошибка, введите число меньше 30");
                        System.out.print("День рождения: ");
                        day = in.nextInt();
                    }
                }
            }
            if (month == 2) {
                while (day > 28 | day < 0) {
                    if (day > 28 | day < 0) {
                        System.out.println("Ошибка, введите число меньше 28");
                        System.out.print("День рождения: ");
                        day = in.nextInt();
                    }
                }
            }
            System.out.print("Год рождения: ");
            int year = in.nextInt();
            while (year > 2022 | year < 0) {
                if (year > 2022 | year < 0) {
                    System.out.println("Ошибка, введите число меньше 2022");
                    System.out.print("Год рождения: ");
                    year = in.nextInt();
                }
            }
            int today = 17, tomonth = 11, toyear = 2022;
            if (today + tomonth * 31 < day + month * 31) {
                year = toyear - year - 1;
            } else {
                year = toyear - year;
            }
            if (tomonth >= month) {
                raznost = tomonth - month;
            } else {
                raznost = month - tomonth;
                if (raznost == 0) {
                } else {
                    raznost = 12 - raznost;
                }
            }

            if (today >= day) {
                day = today - day;
            } else {
                day = day - today;
            }
            System.out.print(year);
            System.out.println(" Лет");
            System.out.print(raznost);
            System.out.println(" Месяцев");
            System.out.print(day);
            System.out.println(" Дней");
    }
}
