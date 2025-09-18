from PyQt5QtWidgets import QWidget, QVBoxLayout, QLabel, QLineEdit, QPushButton, QComboBox, QHBoxLayout, QApplication, QMainWindow, QTabWidget, QFrame, QFileDialog
from PyQt5.QtGui import QPixmap

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("AIData")
        self.setGeometry(100, 100, 1200, 800)
        self.setFixedSize(self.size())

        # Central Widget
        central_widget = QWidget()
        self.setCentralWidget(central_widget)

        # Main Layout
        main_layout = QVBoxLayout()
        central_widget.setLayout(main_layout)

        # Header
        header = QFrame()
        header.setStyleSheet("background-color: #2f2f2f;")
        header_layout = QHBoxLayout()
        header.setLayout(header_layout)

        # Logo
        logo_label = QLabel()
        pixmap = QPixmap("logotype.png").scaledToWidth(50)
        logo_label.setPixmap(pixmap)
        header_layout.addWidget(logo_label)

        # Tabs
        self.tab_widget = QTabWidget()
        self.tab_widget.addTab(AnalysisPage(), "Анализ")
        self.tab_widget.addTab(QWidget(), "Генерация")

        # Add to main layout
        main_layout.addWidget(header)
        main_layout.addWidget(self.tab_widget)

if __name__ == "__main__":
    app = QApplication([])
    window = MainWindow()
    window.show()
    app.exec_()

class AnalysisPage(QWidget):
    def __init__(self):
        super().__init__()

        # Layout
        layout = QVBoxLayout()
        self.setLayout(layout)

        # Title
        title_label = QLabel("Анализ")
        title_label.setStyleSheet("color: white; font-size: 24px; font-weight: bold;")
        layout.addWidget(title_label)

        # Description
        description_label = QLabel(
            "Раздел «Анализ» предоставляет широкие возможности для исследования и обработки данных в удобной визуальной форме. "
            "Вы можете работать как с реестром записей, так и с дашбордом, получая глубокое понимание структуры и характеристик вашего датасета."
        )
        description_label.setStyleSheet("color: white;")
        layout.addWidget(description_label)

        # File path section
        file_path_layout = QHBoxLayout()
        layout.addLayout(file_path_layout)

        file_path_label = QLabel("Укажите путь к csv-файлу базы данных")
        file_path_label.setStyleSheet("color: white;")
        file_path_layout.addWidget(file_path_label)

        self.file_path_input = QLineEdit()
        self.file_path_input.setPlaceholderText("Путь к БД")
        self.file_path_input.setStyleSheet("background-color: #2f2f2f; color: white; border-radius: 5px;")
        file_path_layout.addWidget(self.file_path_input)

        browse_button = QPushButton("Обзор")
        browse_button.setStyleSheet("background-color: white; color: black; border-radius: 10px;")
        browse_button.clicked.connect(self.browse_file)
        file_path_layout.addWidget(browse_button)

        # Separator
        separator = QFrame()
        separator.setFrameShape(QFrame.HLine)
        separator.setFrameShadow(QFrame.Sunken)
        separator.setStyleSheet("color: grey;")
        layout.addWidget(separator)

        # Column and delimiter selection
        selection_layout = QHBoxLayout()
        layout.addLayout(selection_layout)

        column_label = QLabel("Выбор столбцов:")
        column_label.setStyleSheet("color: white;")
        selection_layout.addWidget(column_label)

        self.column_combobox = QComboBox()
        self.column_combobox.addItem("Все столбцы")
        self.column_combobox.setStyleSheet("background-color: #2f2f2f; color: white; border-radius: 5px;")
        selection_layout.addWidget(self.column_combobox)

        delimiter_label = QLabel("Разделитель:")
        delimiter_label.setStyleSheet("color: white;")
        selection_layout.addWidget(delimiter_label)

        self.delimiter_combobox = QComboBox()
        self.delimiter_combobox.addItem(",")
        self.delimiter_combobox.addItem(";")
        self.delimiter_combobox.addItem("\t")
        self.delimiter_combobox.setStyleSheet("background-color: #2f2f2f; color: white; border-radius: 5px;")
        selection_layout.addWidget(self.delimiter_combobox)

        # Buttons
        button_layout = QHBoxLayout()
        layout.addLayout(button_layout)

        validate_button = QPushButton("Проверить файл")
        validate_button.setStyleSheet("background-color: white; color: black; border-radius: 10px;")
        validate_button.clicked.connect(self.validate_file)
        button_layout.addWidget(validate_button)

        self.import_button = QPushButton("Импортировать")
        self.import_button.setStyleSheet("background-color: grey; color: white; border-radius: 10px;")
        self.import_button.setEnabled(False)
        self.import_button.clicked.connect(self.import_file)
        button_layout.addWidget(self.import_button)

    def browse_file(self):
        """Открыть диалог выбора файла."""
        file_path, _ = QFileDialog.getOpenFileName(self, "Выберите CSV-файл", "", "CSV Files (*.csv)")
        if file_path:
            self.file_path_input.setText(file_path)

    def validate_file(self):
        """Проверить файл."""
        file_path = self.file_path_input.text()
        if not file_path:
            return

        # Здесь можно добавить логику для проверки файла (например, чтение первых строк)
        print(f"Проверяется файл: {file_path}")
        self.import_button.setEnabled(True)  # Активировать кнопку "Импортировать"
        self.import_button.setStyleSheet("background-color: white; color: black; border-radius: 10px;")

    def import_file(self):
        """Импортировать файл."""
        file_path = self.file_path_input.text()
        if not file_path:
            return

        print(f"Импортируется файл: {file_path}")
        # Здесь можно добавить логику для импорта файла
        # После импорта перейти на следующую страницу
        self.parent().parent().tab_widget.setCurrentIndex(1)  # Пример перехода на другую вкладку


app.setStyleSheet("""
    QMainWindow {
        background-color: #212121;
    }
    QLabel {
        color: white;
    }
    QPushButton {
        background-color: #2f2f2f;
        color: white;
        border-radius: 10px;
        padding: 10px 20px;
    }
    QPushButton:hover {
        background-color: white;
        color: black;
    }
    QLineEdit {
        background-color: #2f2f2f;
        color: white;
        border-radius: 5px;
        padding: 5px;
    }
    QComboBox {
        background-color: #2f2f2f;
        color: white;
        border-radius: 5px;
        padding: 5px;
    }
""")
