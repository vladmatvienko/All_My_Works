import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class KartingCenterGUI {
    private JFrame frame;
    private JTextField usernameField;
    private JPasswordField passwordField;
    private DatabaseManager dbManager;

    public KartingCenterGUI() {
        dbManager = new DatabaseManager();
        initialize();
    }

    private void initialize() {
        frame = new JFrame("Karting Center Login");
        frame.setSize(1500, 700);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setLayout(new BorderLayout());

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(3, 2, 10, 10));
        panel.setBorder(BorderFactory.createEmptyBorder(200, 500, 200, 500));

        JLabel usernameLabel = new JLabel("Username:");
        usernameField = new JTextField();
        JLabel passwordLabel = new JLabel("Password:");
        passwordField = new JPasswordField();

        JButton loginButton = new JButton("Login");
        loginButton.setFont(new Font("Arial", Font.BOLD, 16));
        loginButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                String username = usernameField.getText();
                String password = new String(passwordField.getPassword());

                String role = dbManager.authenticateUser(username, password);

                if (role != null) {
                    JOptionPane.showMessageDialog(frame, "Welcome, " + role + "!");
                    frame.dispose(); // Закрываем окно регистрации
                    showRoleSpecificPage(role); // Открываем окно для соответствующей роли
                } else {
                    JOptionPane.showMessageDialog(frame, "Invalid username or password.", "Error", JOptionPane.ERROR_MESSAGE);
                }
            }
        });

        panel.add(usernameLabel);
        panel.add(usernameField);
        panel.add(passwordLabel);
        panel.add(passwordField);
        panel.add(new JLabel()); // Пустая ячейка
        panel.add(loginButton);

        frame.add(panel, BorderLayout.CENTER);
        frame.setVisible(true);
    }

    private void showRoleSpecificPage(String role) {
        switch (role) {
            case "Administrator":
                new AdminWindow();
                break;
            case "Guest":
                new GuestWindow();
                break;
            default:
                JOptionPane.showMessageDialog(frame, "Unknown role: " + role, "Error", JOptionPane.ERROR_MESSAGE);
        }
    }

    public static void main(String[] args) {
        EventQueue.invokeLater(() -> new KartingCenterGUI());
    }
}