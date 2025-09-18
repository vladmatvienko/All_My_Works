package io;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Arrays;
import java.util.Scanner;

public class ggg {
    static String[] Answers;
    static String[] Questions;
    public void AmountOfAnswers(String[] args) throws FileNotFoundException {
        String a = "Ответы.txt";
        String b = "Вопросы.txt";
        for (int t = 0; t < 2; t++) {
            if (t == 0) {
                String filePath = "C:\\Users\\vlado\\Desktop\\Video-testing\\Video-testing\\src\\main\\java\\VideoLibrary\\" + HelloApplication.VideoName[HelloApplication.ID] + a;
                File file = new File(filePath);
                Scanner scanner = new Scanner(file);

                String line = scanner.nextLine();
                String[] words = line.split("");
                int Key1 = 0;
                int i1 = 0;
                while (Key1 < words.length) {
                    if (words[Key1].equals(",")) {
                        i1 = i1 + 1;
                    }
                    Key1 = Key1 + 1;
                }
                String[] truewords = new String[i1 + 1];
                int Key = 0;
                int i = 0;
                String wordy1 = "";
                while (Key < words.length) {
                    if (words[Key].equals(",")) {
                        truewords[i] = wordy1;
                        wordy1 = "";
                        i = i + 1;
                    } else if (Key == words.length - 1) {
                        wordy1 = wordy1 + words[Key];
                        truewords[i] = wordy1;
                    } else {
                        wordy1 = wordy1 + words[Key];
                    }
                    Key = Key + 1;
                }
                Answers = truewords;
            } else {
                String filePath = "C:\\Users\\vlado\\Desktop\\Video-testing\\Video-testing\\src\\main\\java\\VideoLibrary\\" + HelloApplication.VideoName[HelloApplication.ID] + b;
                File file = new File(filePath);
                Scanner scanner = new Scanner(file);

                String line = scanner.nextLine();
                String[] words = line.split("");
                int Key1 = 0;
                int i1 = 0;
                while (Key1 < words.length) {
                    if (words[Key1].equals(",")) {
                        i1 = i1 + 1;
                    }
                    Key1 = Key1 + 1;
                }
                String[] truewords = new String[i1 + 1];
                int Key = 0;
                int i = 0;
                String wordy1 = "";
                while (Key < words.length) {
                    if (words[Key].equals(",")) {
                        truewords[i] = wordy1;
                        wordy1 = "";
                        i = i + 1;
                    } else if (Key == words.length - 1) {
                        wordy1 = wordy1 + words[Key];
                        truewords[i] = wordy1;
                    } else {
                        wordy1 = wordy1 + words[Key];
                    }
                    Key = Key + 1;
                }
                Questions = truewords;
            }
        }
    }
}
