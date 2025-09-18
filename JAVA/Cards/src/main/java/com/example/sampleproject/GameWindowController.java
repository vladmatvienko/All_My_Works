package com.example.sampleproject;

import java.io.IOException;
import java.util.Arrays;
import java.util.Random;

import javafx.event.ActionEvent;
import javafx.fxml.FXML;
import javafx.fxml.FXMLLoader;
import javafx.scene.control.Button;
import javafx.scene.control.ScrollPane;
import javafx.scene.layout.FlowPane;
import javafx.scene.layout.GridPane;
import javafx.scene.layout.Pane;
public class GameWindowController {

    @FXML
    private Button addCardButton;

    @FXML
    private GridPane deskAttackCardPane;

    @FXML
    private GridPane deskAnswerCardPane;
    
    @FXML
    private ScrollPane firstPlayerScroll;

    @FXML
    private ScrollPane secondPlayerScroll;

    @FXML
    private FlowPane firstPlayerPane;

    @FXML
    private FlowPane secondPlayerPane;

    public String[] MASSIVE = {"2","1","1","1","1","1","1","1","1","1","1","1"};// Массив карт которые добавляются в игру (Я не уверен, что оно работает, но мне по крайней мере одинаковые карты не попадались)
    public int Num = 0;// Номер карты
    @FXML
    void addCard(ActionEvent event) throws IOException, InterruptedException {
        FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("Card.fxml"));
        Pane newPane = (Pane) loader.load();
        if (HelloApplication.AmountOfCardsFirstPlayer < 6) {
            int SomeNumber = 0;
            while (SomeNumber == 0) {
                String[] nominal = new String[]{"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Валет", "Дама", "Король", "Туз"};
                String[] mask = new String[]{"Бубны", "Червы", "Крести", "Пики"};
                Random random = new Random();
                int index_1 = random.nextInt(nominal.length);
                int index_2 = random.nextInt(mask.length);
                String OneCard = nominal[index_1] + mask[index_2];//Создание карты
                int Num1 = 0;//Просто переменная
                for (int k = 0; k <= 5; k++) {
                    if (MASSIVE[k].equals(OneCard)) {
                        Num1 = Num1 + 1;
                        System.out.println(Num1);
                    }
                }//Сравнивание карт в массиве и сгенерированной карты
                if (Num1 == 0) {
                    MASSIVE[Num] = OneCard;
                    Num = Num + 1;
                    CardController cardController = loader.getController();
                    cardController.setCardParameters(nominal[index_1], mask[index_2], this, newPane);
                    firstPlayerPane.getChildren().add(newPane);
                    firstPlayerScroll = new ScrollPane();
                    firstPlayerScroll.setContent(firstPlayerPane);
                    SomeNumber = 1;
                }//Если карта проходит по условию, то тогда добавляется в игру
            }//Цикл сделал, что бы при нажатии кнопки по любому что-нибудь да впихнулось
            System.out.println(Arrays.toString(MASSIVE));// это что б посмотреть что ваще в массив записалось
            HelloApplication.AmountOfCardsFirstPlayer++;
        } else if (HelloApplication.AmountOfCardsFirstPlayer >= 6 && HelloApplication.AmountOfCardsFirstPlayer < 12) {
            int SomeNumber = 0;
            while (SomeNumber == 0) {
                String[] nominal = new String[]{"1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Валет", "Дама", "Король", "Туз"};
                String[] mask = new String[]{"Бубны", "Червы", "Крести", "Пики"};
                Random random = new Random();
                int index_1 = random.nextInt(nominal.length);
                int index_2 = random.nextInt(mask.length);
                String OneCard = nominal[index_1] + mask[index_2];//Создание карты
                int Num1 = 0;//Просто переменная
                for (int k = 0; k <= 5; k++) {
                    if (MASSIVE[k].equals(OneCard)) {
                        Num1 = Num1 + 1;
                        System.out.println(Num1);
                    }
                }//Сравнивание карт в массиве и сгенерированной карты
                if (Num1 == 0) {
                    MASSIVE[Num] = OneCard;
                    Num = Num + 1;
                    CardController cardController = loader.getController();
                    cardController.setCardParameters(nominal[index_1], mask[index_2], this, newPane);
                    secondPlayerPane.getChildren().add(newPane);
                    secondPlayerScroll = new ScrollPane();
                    secondPlayerScroll.setContent(secondPlayerPane);
                    SomeNumber = 1;
                }//Если карта проходит по условию, то тогда добавляется в игру
            }//Цикл сделал, что бы при нажатии кнопки по любому что-нибудь да впихнулось
            System.out.println(Arrays.toString(MASSIVE));// это что б посмотреть что ваще в массив записалось
            HelloApplication.AmountOfCardsFirstPlayer++;
        } else if (HelloApplication.AmountOfCardsFirstPlayer == 12) {
            addCardButton.setVisible(false);
        }
    }

    public void addCardOnTable(CardController card) throws IOException {
    	FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("Card.fxml"));
        
    	Pane newPane = (Pane)loader.load();
    	
    	CardController cardController = loader.getController();
    	cardController.setCardParameters(card.getNominal(), card.getMask(), this, newPane);
    	

        deskAttackCardPane.add(newPane, deskAttackCardPane.getChildren().size(), 0);
    }
}
