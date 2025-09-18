import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

public class GuestTableViewWindow extends JFrame {
    private DatabaseManager dbManager;
    private JTable table;
    private DefaultTableModel tableModel;

    public GuestTableViewWindow() {
        dbManager = new DatabaseManager();
        initialize();
    }

    private void initialize() {
        setTitle("Table View (Guest)");
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
        JPanel buttonPanel = new JPanel(new GridLayout(1, 1, 10, 10));

        JButton searchButton = new JButton("Search Row");
        searchButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                searchRow();
            }
        });

        buttonPanel.add(searchButton);

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
}
