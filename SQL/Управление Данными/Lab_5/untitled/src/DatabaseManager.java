import java.sql.*;
import java.util.ArrayList;
import java.util.List;

public class DatabaseManager {
    private static final String DB_URL = "jdbc:postgresql://localhost:5432/postgres";
    private static final String DB_USER = "postgres";
    private static final String DB_PASSWORD = "postgres";

    // Метод для проверки логина пользователя
    public String authenticateUser(String username, String password) {
        String role = null;
        String sql = "{CALL authenticate_user(?, ?, ?)}"; // Вызов хранимой процедуры

        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);
             CallableStatement stmt = conn.prepareCall(sql)) {

            stmt.setString(1, username);
            stmt.setString(2, password);
            stmt.registerOutParameter(3, Types.VARCHAR); // Роль пользователя

            stmt.execute();
            role = stmt.getString(3); // Получаем роль из хранимой процедуры

        } catch (SQLException e) {
            e.printStackTrace();
        }

        return role;
    }

    public List<Object[]> getTableData() {
        List<Object[]> data = new ArrayList<>();
        String sql = "SELECT * FROM users";

        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);
             Statement stmt = conn.createStatement();
             ResultSet rs = stmt.executeQuery(sql)) {

            while (rs.next()) {
                Object[] row = {
                        rs.getInt("userid"),
                        rs.getString("username"),
                        rs.getString("password"),
                        rs.getString("role"),
                        rs.getString("fullname"),
                        rs.getString("email"),
                        rs.getString("phonenumber")
                };
                data.add(row);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return data;
    }

    public void addRow(String username, String password, String role, String fullName, String email, String phone) {
        String sql = "CALL add_user(?, ?, ?, ?, ?, ?)";

        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);
             CallableStatement stmt = conn.prepareCall(sql)) {

            stmt.setString(1, username);
            stmt.setString(2, password);
            stmt.setString(3, role);
            stmt.setString(4, fullName);
            stmt.setString(5, email);
            stmt.setString(6, phone);

            stmt.execute();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void deleteRow(int userId) {
        String sql = "CALL delete_user(?)";

        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);
             CallableStatement stmt = conn.prepareCall(sql)) {

            stmt.setInt(1, userId);
            stmt.execute();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public List<Object[]> searchRow(String field, String value) {
        List<Object[]> data = new ArrayList<>();
        String sql = "SELECT * FROM users WHERE " + field + " = ?";

        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);
             PreparedStatement stmt = conn.prepareStatement(sql)) {

            stmt.setString(1, value);
            ResultSet rs = stmt.executeQuery();

            while (rs.next()) {
                Object[] row = {
                        rs.getInt("userid"),
                        rs.getString("username"),
                        rs.getString("password"),
                        rs.getString("role"),
                        rs.getString("fullname"),
                        rs.getString("email"),
                        rs.getString("phonenumber")
                };
                data.add(row);
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }

        return data;
    }
    public void createDatabaseAndTable() {
        String sql = "CALL create_database_and_table()";

        try (Connection conn = DriverManager.getConnection("jdbc:postgresql://localhost:5432/", DB_USER, DB_PASSWORD);
             CallableStatement stmt = conn.prepareCall(sql)) {

            stmt.execute();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void dropDatabase() {
        String sqlDisconnect = "SELECT pg_terminate_backend(pg_stat_activity.pid) " +
                "FROM pg_stat_activity " +
                "WHERE pg_stat_activity.datname = 'karting_center'";

        String sqlDrop = "DROP DATABASE IF EXISTS karting_center";

        try (Connection conn = DriverManager.getConnection("jdbc:postgresql://localhost:5432/", DB_USER, DB_PASSWORD);
             Statement stmt = conn.createStatement()) {

            // Завершаем все активные подключения к базе данных
            stmt.execute(sqlDisconnect);

            // Удаляем базу данных
            stmt.execute(sqlDrop);

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void clearUsersTable() {
        String sql = "CALL clear_users_table()";

        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);
             CallableStatement stmt = conn.prepareCall(sql)) {

            stmt.execute();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }

    public void updateRow(int userId, String username, String password, String role, String fullName, String email, String phone) {
        String sql = "CALL update_user(?, ?, ?, ?, ?, ?, ?)";

        try (Connection conn = DriverManager.getConnection(DB_URL, DB_USER, DB_PASSWORD);
             CallableStatement stmt = conn.prepareCall(sql)) {

            stmt.setInt(1, userId);
            stmt.setString(2, username);
            stmt.setString(3, password);
            stmt.setString(4, role);
            stmt.setString(5, fullName);
            stmt.setString(6, email);
            stmt.setString(7, phone);

            stmt.execute();
        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}