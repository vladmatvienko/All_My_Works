import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class GuestWindow extends JFrame {
    public GuestWindow() {
        initialize();
    }

    private void initialize() {
        setTitle("Guest Dashboard");
        setSize(1500, 700);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setLocationRelativeTo(null);

        JPanel panel = new JPanel();
        panel.setLayout(new GridLayout(2, 1, 10, 10));
        panel.setBorder(BorderFactory.createEmptyBorder(200, 500, 200, 500));

        JButton viewTableButton = new JButton("View Table");
        viewTableButton.setFont(new Font("Arial", Font.BOLD, 16));
        viewTableButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                new GuestTableViewWindow();
            }
        });

        panel.add(viewTableButton);

        add(panel);
        setVisible(true);
    }
}