import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.PasswordField;
import javafx.scene.control.TextField;
import javafx.scene.layout.VBox;

public class LoginScreen {
    private VBox layout;

    public LoginScreen() {
        layout = new VBox(10);
        layout.setAlignment(Pos.CENTER);
        layout.setPadding(new Insets(20));

        Label titleLabel = new Label("Karting Center Login");
        titleLabel.getStyleClass().add("title");

        TextField usernameField = new TextField();
        usernameField.setPromptText("Username");

        PasswordField passwordField = new PasswordField();
        passwordField.setPromptText("Password");

        Button adminLoginButton = new Button("Login as Admin");
        adminLoginButton.getStyleClass().add("button");
        adminLoginButton.setOnAction(e -> {
            String role = "admin";
            openDashboard(role);
        });

        Button guestLoginButton = new Button("Login as Guest");
        guestLoginButton.getStyleClass().add("button");
        guestLoginButton.setOnAction(e -> {
            String role = "guest";
            openDashboard(role);
        });

        layout.getChildren().addAll(titleLabel, usernameField, passwordField, adminLoginButton, guestLoginButton);
    }

    private void openDashboard(String role) {
        Dashboard dashboard = new Dashboard(role);
        Scene dashboardScene = new Scene(dashboard.getLayout(), 800, 600);
        dashboardScene.getStylesheets().add(getClass().getResource("styles.css").toExternalForm());

        Stage stage = new Stage();
        stage.setTitle("Dashboard - " + role.toUpperCase());
        stage.setScene(dashboardScene);
        stage.show();
    }

    public VBox getLayout() {
        return layout;
    }
}