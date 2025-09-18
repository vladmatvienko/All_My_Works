import javafx.geometry.Insets;
import javafx.scene.control.*;
import javafx.scene.layout.VBox;

import java.sql.SQLException;

public class Dashboard {
    private VBox layout;

    public Dashboard(String role) {
        layout = new VBox(10);
        layout.setAlignment(Pos.TOP_CENTER);
        layout.setPadding(new Insets(20));

        Label titleLabel = new Label("Dashboard - " + role.toUpperCase());
        titleLabel.getStyleClass().add("title");

        DatabaseManager dbManager = null;
        try {
            dbManager = new DatabaseManager(role);
        } catch (SQLException e) {
            e.printStackTrace();
        }

        if ("admin".equalsIgnoreCase(role)) {
            addAdminControls(dbManager);
        } else if ("guest".equalsIgnoreCase(role)) {
            addGuestControls(dbManager);
        }
    }

    private void addAdminControls(DatabaseManager dbManager) {
        Button addUserButton = new Button("Add User");
        addUserButton.getStyleClass().add("button");

        Button deleteUserButton = new Button("Delete User");
        deleteUserButton.getStyleClass().add("button");

        layout.getChildren().addAll(addUserButton, deleteUserButton);
    }

    private void addGuestControls(DatabaseManager dbManager) {
        TextField searchField = new TextField();
        searchField.setPromptText("Search by Full Name");

        Button searchButton = new Button("Search");
        searchButton.getStyleClass().add("button");

        ListView<String> resultsList = new ListView<>();
        searchButton.setOnAction(e -> {
            try {
                var users = dbManager.searchByFullName(searchField.getText());
                resultsList.getItems().clear();
                for (var user : users) {
                    resultsList.getItems().add(user.toString());
                }
            } catch (SQLException ex) {
                ex.printStackTrace();
            }
        });

        layout.getChildren().addAll(searchField, searchButton, resultsList);
    }

    public VBox getLayout() {
        return layout;
    }
}