import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class DatabaseManager {
    private static final String DB_URL = "jdbc:postgresql://localhost:5432/karting_center";
    private static final String ADMIN_USER = "admin_user";
    private static final String ADMIN_PASSWORD = "admin_password";
    private static final String GUEST_USER = "guest_user";
    private static final String GUEST_PASSWORD = "guest_password";

    private Connection connection;

    // Конструктор для подключения к базе данных
    public DatabaseManager(String role) throws SQLException {
        if ("admin".equalsIgnoreCase(role)) {
            connection = DriverManager.getConnection(DB_URL, ADMIN_USER, ADMIN_PASSWORD);
        } else if ("guest".equalsIgnoreCase(role)) {
            connection = DriverManager.getConnection(DB_URL, GUEST_USER, GUEST_PASSWORD);
        } else {
            throw new IllegalArgumentException("Invalid role specified");
        }
    }

    // Закрытие соединения
    public void closeConnection() throws SQLException {
        if (connection != null && !connection.isClosed()) {
            connection.close();
        }
    }

    // 1. Удаление базы данных
    public void dropDatabase() throws SQLException {
        try (CallableStatement stmt = connection.prepareCall("{CALL drop_database()}")) {
            stmt.execute();
        }
    }

    // 2. Очистка таблицы
    public void clearTable() throws SQLException {
        try (CallableStatement stmt = connection.prepareCall("{CALL clear_table()}")) {
            stmt.execute();
        }
    }

    // 3. Добавление нового пользователя
    public void addUser(String username, String passwordHash, String role, String fullName, String email, String phoneNumber) throws SQLException {
        try (CallableStatement stmt = connection.prepareCall("{CALL add_user(?, ?, ?, ?, ?, ?)}")) {
            stmt.setString(1, username);
            stmt.setString(2, passwordHash);
            stmt.setString(3, role);
            stmt.setString(4, fullName);
            stmt.setString(5, email);
            stmt.setString(6, phoneNumber);
            stmt.execute();
        }
    }

    // 4. Поиск по текстовому полю (например, full_name)
    public List<User> searchByFullName(String fullName) throws SQLException {
        List<User> users = new ArrayList<>();
        try (CallableStatement stmt = connection.prepareCall("{? = CALL search_by_full_name(?)}")) {
            stmt.registerOutParameter(1, Types.OTHER); // Результат функции
            stmt.setString(2, fullName);
            stmt.execute();

            try (ResultSet rs = (ResultSet) stmt.getObject(1)) {
                while (rs.next()) {
                    User user = new User(
                            rs.getInt("user_id"),
                            rs.getString("username"),
                            rs.getString("role"),
                            rs.getString("email"),
                            rs.getString("phone_number")
                    );
                    users.add(user);
                }
            }
        }
        return users;
    }

    // 5. Обновление кортежа
    public void updateUser(int userId, String username, String passwordHash, String role, String fullName, String email, String phoneNumber) throws SQLException {
        try (CallableStatement stmt = connection.prepareCall("{CALL update_user(?, ?, ?, ?, ?, ?, ?)}")) {
            stmt.setInt(1, userId);
            stmt.setString(2, username);
            stmt.setString(3, passwordHash);
            stmt.setString(4, role);
            stmt.setString(5, fullName);
            stmt.setString(6, email);
            stmt.setString(7, phoneNumber);
            stmt.execute();
        }
    }

    // 6. Удаление по текстовому полю (например, email)
    public void deleteUserByEmail(String email) throws SQLException {
        try (CallableStatement stmt = connection.prepareCall("{CALL delete_user_by_email(?)}")) {
            stmt.setString(1, email);
            stmt.execute();
        }
    }

    // 7. Создание нового пользователя с заданным режимом доступа
    public void createNewUserWithRole(String username, String passwordHash, String role) throws SQLException {
        try (CallableStatement stmt = connection.prepareCall("{CALL create_new_user_with_role(?, ?, ?)}")) {
            stmt.setString(1, username);
            stmt.setString(2, passwordHash);
            stmt.setString(3, role);
            stmt.execute();
        }
    }

    // Вспомогательный класс для представления пользователя
    public static class User {
        private int userId;
        private String username;
        private String role;
        private String email;
        private String phoneNumber;

        public User(int userId, String username, String role, String email, String phoneNumber) {
            this.userId = userId;
            this.username = username;
            this.role = role;
            this.email = email;
            this.phoneNumber = phoneNumber;
        }

        @Override
        public String toString() {
            return "User{" +
                    "userId=" + userId +
                    ", username='" + username + '\'' +
                    ", role='" + role + '\'' +
                    ", email='" + email + '\'' +
                    ", phoneNumber='" + phoneNumber + '\'' +
                    '}';
        }
    }
}