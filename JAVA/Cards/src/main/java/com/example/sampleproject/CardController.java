package com.example.sampleproject;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;

import javafx.fxml.FXML;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;
import javafx.scene.input.MouseEvent;
import javafx.scene.layout.FlowPane;
import javafx.scene.layout.Pane;
import javafx.scene.text.Text;

public class CardController {
	Pane cardPane;
	
	GameWindowController gameWindow;

    @FXML
    private String nominal;

    @FXML
    private String mask;

    @FXML
    private ImageView imgBuffer;

    @FXML
    private Pane imgPane;

   // @FXML
   // private Text smth;

    public void setCardParameters(String nominal, String mask, GameWindowController gameWindow, Pane cardPane) throws FileNotFoundException {
        String PictureofCard = nominal+mask+".jpg";
        this.mask = mask;
        this.nominal = nominal;
    	this.gameWindow = gameWindow;
    	this.cardPane = cardPane;
    	File img = new File("C:\\Users\\vlado\\Desktop\\SampleProject\\Cards\\src\\main\\resources\\com\\example\\sampleproject\\"+PictureofCard);
    	InputStream isImage = (InputStream) new FileInputStream(img);
    	imgBuffer = new ImageView(new Image(isImage));
    	imgBuffer.setFitWidth(80);
    	imgBuffer.setPreserveRatio(true);
    	//imgBuffer.setSmooth(true);
    	
    	//cardPane.getChildren().add(imgBuffer);
    	
    	//imgPane = new Pane();
    	imgPane.getChildren().setAll(imgBuffer);
    	
    }

    public String getNominal() {
    	return this.nominal;
    }

    public String getMask() {
    	return this.mask;
    }
    
    @FXML
    void replaceCardToTable(MouseEvent event) throws IOException {
    	gameWindow.addCardOnTable(this);
    	cardPane.setVisible(false);
    	FlowPane firstPlayerPane = (FlowPane) cardPane.getParent();
    	firstPlayerPane.getChildren().remove(cardPane);
    }
}
