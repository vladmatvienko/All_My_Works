import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class TableViewWindow extends JFrame {
    private DatabaseManager dbManager;
    private JTable table;
    private DefaultTableModel tableModel;

    public TableViewWindow() {
        dbManager = new DatabaseManager();
        initialize();
    }

    private void initialize() {
        setTitle("Table View");
        setSize(1500, 700);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel(new BorderLayout());
        panel.setBorder(BorderFactory.createEmptyBorder(20, 20, 20, 20));

        // Таблица
        String[] columns = {"User ID", "Username", "Password", "Role", "Full Name", "Email", "Phone Number"};
        tableModel = new DefaultTableModel(columns, 0);
        table = new JTable(tableModel);
        JScrollPane scrollPane = new JScrollPane(table);
        panel.add(scrollPane, BorderLayout.CENTER);

        // Панель с кнопками
        JPanel buttonPanel = new JPanel(new GridLayout(1, 4, 10, 10));

        JButton addButton = new JButton("Add Row");
        addButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                addRow();
            }
        });

        JButton deleteButton = new JButton("Delete Row");
        deleteButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                deleteRow();
            }
        });

        JButton searchButton = new JButton("Search Row");
        searchButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                searchRow();
            }
        });

        JButton updateButton = new JButton("Update Row");
        updateButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                updateRow();
            }
        });

        buttonPanel.add(addButton);
        buttonPanel.add(deleteButton);
        buttonPanel.add(searchButton);
        buttonPanel.add(updateButton);

        panel.add(buttonPanel, BorderLayout.SOUTH);

        add(panel);
        loadTableData();
        setVisible(true);
    }

    private void loadTableData() {
        tableModel.setRowCount(0); // Очистить таблицу
        var rows = dbManager.getTableData();
        for (var row : rows) {
            tableModel.addRow(row);
        }
    }

    private void addRow() {
        JTextField usernameField = new JTextField();
        JTextField passwordField = new JTextField();
        JTextField roleField = new JTextField();
        JTextField fullNameField = new JTextField();
        JTextField emailField = new JTextField();
        JTextField phoneField = new JTextField();

        Object[] fields = {
                "Username:", usernameField,
                "Password:", passwordField,
                "Role:", roleField,
                "Full Name:", fullNameField,
                "Email:", emailField,
                "Phone Number:", phoneField
        };

        int result = JOptionPane.showConfirmDialog(this, fields, "Add New Row", JOptionPane.OK_CANCEL_OPTION);
        if (result == JOptionPane.OK_OPTION) {
            String username = usernameField.getText();
            String password = passwordField.getText();
            String role = roleField.getText();
            String fullName = fullNameField.getText();
            String email = emailField.getText();
            String phone = phoneField.getText();

            dbManager.addRow(username, password, role, fullName, email, phone);
            loadTableData();
            JOptionPane.showMessageDialog(this, "Row added successfully!");
        }
    }

    private void deleteRow() {
        String userId = JOptionPane.showInputDialog(this, "Enter User ID to delete:");
        if (userId != null && !userId.isEmpty()) {
            dbManager.deleteRow(Integer.parseInt(userId));
            loadTableData();
            JOptionPane.showMessageDialog(this, "Row deleted successfully!");
        }
    }

    private void searchRow() {
        String field = JOptionPane.showInputDialog(this, "Enter field to search (e.g., username):");
        String value = JOptionPane.showInputDialog(this, "Enter value to search for:");
        if (field != null && value != null && !field.isEmpty() && !value.isEmpty()) {
            var result = dbManager.searchRow(field, value);
            if (result.isEmpty()) {
                JOptionPane.showMessageDialog(this, "No results found.");
            } else {
                tableModel.setRowCount(0);
                for (var row : result) {
                    tableModel.addRow(row);
                }
            }
        }
    }

    private void updateRow() {
        String userId = JOptionPane.showInputDialog(this, "Enter User ID to update:");
        if (userId != null && !userId.isEmpty()) {
            JTextField usernameField = new JTextField();
            JTextField passwordField = new JTextField();
            JTextField roleField = new JTextField();
            JTextField fullNameField = new JTextField();
            JTextField emailField = new JTextField();
            JTextField phoneField = new JTextField();

            Object[] fields = {
                    "Username:", usernameField,
                    "Password:", passwordField,
                    "Role:", roleField,
                    "Full Name:", fullNameField,
                    "Email:", emailField,
                    "Phone Number:", phoneField
            };

            int result = JOptionPane.showConfirmDialog(this, fields, "Update Row", JOptionPane.OK_CANCEL_OPTION);
            if (result == JOptionPane.OK_OPTION) {
                String username = usernameField.getText();
                String password = passwordField.getText();
                String role = roleField.getText();
                String fullName = fullNameField.getText();
                String email = emailField.getText();
                String phone = phoneField.getText();

                dbManager.updateRow(Integer.parseInt(userId), username, password, role, fullName, email, phone);
                loadTableData();
                JOptionPane.showMessageDialog(this, "Row updated successfully!");
            }
        }
    }
}
