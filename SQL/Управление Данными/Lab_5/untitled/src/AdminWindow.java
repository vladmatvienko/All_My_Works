import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class AdminWindow extends JFrame {
    private DatabaseManager dbManager;

    public AdminWindow() {
        dbManager = new DatabaseManager();
        initialize();
    }

    private void initialize() {
        setTitle("Administrator Dashboard");
        setSize(1500, 700);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(5, 1, 10, 10)); // Увеличиваем количество строк для новой кнопки
        panel.setBorder(BorderFactory.createEmptyBorder(200, 500, 200, 500));

        JButton viewTableButton = new JButton("View Table");
        viewTableButton.setFont(new Font("Arial", Font.BOLD, 16));
        viewTableButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                new TableViewWindow();
            }
        });

        JButton createDatabaseButton = new JButton("Create Database");
        createDatabaseButton.setFont(new Font("Arial", Font.BOLD, 16));
        createDatabaseButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                dbManager.createDatabaseAndTable();
                JOptionPane.showMessageDialog(AdminWindow.this, "Database and table created successfully!");
            }
        });

        JButton deleteDatabaseButton = new JButton("Delete Database");
        deleteDatabaseButton.setFont(new Font("Arial", Font.BOLD, 16));
        deleteDatabaseButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int confirm = JOptionPane.showConfirmDialog(AdminWindow.this, "Are you sure you want to delete the database?", "Confirm Delete", JOptionPane.YES_NO_OPTION);
                if (confirm == JOptionPane.YES_OPTION) {
                    dbManager.dropDatabase();
                    JOptionPane.showMessageDialog(AdminWindow.this, "Database deleted successfully!");
                }
            }
        });

        JButton clearTableButton = new JButton("Clear Table");
        clearTableButton.setFont(new Font("Arial", Font.BOLD, 16));
        clearTableButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                int confirm = JOptionPane.showConfirmDialog(AdminWindow.this, "Are you sure you want to clear the table?", "Confirm Clear", JOptionPane.YES_NO_OPTION);
                if (confirm == JOptionPane.YES_OPTION) {
                    dbManager.clearUsersTable();
                    JOptionPane.showMessageDialog(AdminWindow.this, "Table cleared successfully!");
                }
            }
        });

        panel.add(viewTableButton);
        panel.add(createDatabaseButton);
        panel.add(deleteDatabaseButton);
        panel.add(clearTableButton);

        add(panel);
        setVisible(true);
    }
}