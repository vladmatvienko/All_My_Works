import javafx.application.Application;
import javafx.scene.Scene;
import javafx.stage.Stage;

public class Main extends Application {
    @Override
    public void start(Stage primaryStage) {
        // Создаем главное окно
        LoginScreen loginScreen = new LoginScreen();
        Scene scene = new Scene(loginScreen.getLayout(), 400, 300);

        // Применяем CSS для стилизации
        scene.getStylesheets().add(getClass().getResource("styles.css").toExternalForm());

        primaryStage.setTitle("Karting Center");
        primaryStage.setScene(scene);
        primaryStage.show();
    }

    public static void main(String[] args) {
        launch(args);
    }
}