package com.example.sampleproject;

import java.io.IOException;

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

    @FXML
    void addCard(ActionEvent event) throws IOException, InterruptedException {
    	FXMLLoader loader = new FXMLLoader();
        loader.setLocation(getClass().getResource("Card.fxml"));
        
    	Pane newPane = (Pane)loader.load();
    	
    	CardController cardController = loader.getController();
    	cardController.setCardParameters("6", "bubi", this, newPane);

    	firstPlayerPane.getChildren().add(newPane);

    	firstPlayerScroll = new ScrollPane();
    	firstPlayerScroll.setContent(firstPlayerPane);
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
