from PySide6.QtWidgets import QApplication, QStackedWidget, QMainWindow, QWidget, QHBoxLayout, QVBoxLayout, QLabel, QPushButton, QTabWidget, QComboBox, QLineEdit, QFileDialog, QMessageBox, QCheckBox, QListWidget, QListWidgetItem, QTableWidget, QTableWidgetItem, QHeaderView
from PySide6.QtGui import QIcon, QColor, QFont
from PySide6.QtCore import Qt, QSize

# Основные цвета интерфейса
PRIMARY_BACKGROUND = "#212121"
SIDEBAR_BACKGROUND = "#171717"
TEXT_COLOR = "white"
SECONDARY_TEXT_COLOR = "grey"
BUTTON_BACKGROUND = "#2f2f2f"
ICON_COLOR = "white"

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("AI Data Analysis")
        self.setGeometry(100, 100, 1200, 800)
        self.setCentralWidget(MainContainer())
        self.setStyleSheet(f"""
            QMainWindow {{
                background-color: {PRIMARY_BACKGROUND};
                color: {TEXT_COLOR};
            }}
        """)

class MainContainer(QWidget):
    def __init__(self):
        super().__init__()
        layout = QVBoxLayout(self)
        
        # Хедер
        header = Header()
        layout.addWidget(header)
        
        # Основное содержимое
        self.main_content = QStackedWidget()
        self.main_content.addWidget(AnalysisWindow())
        self.main_content.addWidget(DataRegistryWindow())
        layout.addWidget(self.main_content)
        
        # Подключение сигналов
        header.tab_widget.currentChanged.connect(self.switch_content)
        
    def switch_content(self, index):
        self.main_content.setCurrentIndex(index)

class Header(QWidget):
    def __init__(self):
        super().__init__()
        layout = QHBoxLayout(self)
        layout.setContentsMargins(10, 0, 10, 0)
        
        # Логотип
        logo_label = QLabel()
        logo_label.setPixmap(QIcon("logotype.png").pixmap(QSize(48, 48)))
        layout.addWidget(logo_label)
        
        # Текст логотипа
        logo_text = QLabel("AIData")
        logo_text.setFont(QFont("Arial", 14, QFont.Bold))
        logo_text.setStyleSheet(f"color: {TEXT_COLOR}; margin-left: 10px;")
        layout.addWidget(logo_text)
        
        # Табы
        self.tab_widget = QTabWidget()
        self.tab_widget.addTab(TabButton("Анализ"), "Анализ")
        self.tab_widget.addTab(TabButton("Генерация"), "Генерация")
        self.tab_widget.setStyleSheet(f"""
            QTabWidget {{
                background-color: {PRIMARY_BACKGROUND};
                padding-top: 5px;
            }}
            QTabBar::tab {{
                background-color: {BUTTON_BACKGROUND};
                color: {TEXT_COLOR};
                min-width: 120px;
                padding: 8px 0;
                border-radius: 8px;
            }}
            QTabBar::tab:selected {{
                background-color: {PRIMARY_BACKGROUND};
                color: {TEXT_COLOR};
            }}
        """)
        layout.addWidget(self.tab_widget, stretch=1)

class TabButton(QWidget):
    def __init__(self, text):
        super().__init__()
        layout = QHBoxLayout(self)
        layout.setContentsMargins(0, 0, 0, 0)
        label = QLabel(text)
        label.setAlignment(Qt.AlignCenter)
        layout.addWidget(label)

class AnalysisWindow(QWidget):
    def __init__(self):
        super().__init__()
        layout = QVBoxLayout(self)
        
        # Заголовок
        title = QLabel("Анализ")
        title.setFont(QFont("Arial", 24, QFont.Bold))
        title.setStyleSheet(f"color: {TEXT_COLOR}; margin-top: 20px;")
        layout.addWidget(title, alignment=Qt.AlignLeft)
        
        # Описание
        description = QLabel(
            "Раздел «Анализ» предоставляет широкие возможности для исследования и обработки данных в удобной визуальной форме. "
            "Вы можете работать как с реестром записей, так и с дашбордом, получая глубокое понимание структуры и характеристик вашего датасета."
        )
        description.setWordWrap(True)
        description.setStyleSheet(f"color: {SECONDARY_TEXT_COLOR}; margin: 20px 40px;")
        layout.addWidget(description)
        
        # Форма загрузки файла
        form_layout = QHBoxLayout()
        layout.addLayout(form_layout)
        
        # Левая часть формы
        left_form = QVBoxLayout()
        form_layout.addLayout(left_form)
        
        file_path_label = QLabel("Укажите путь к csv-файлу базы данных")
        file_path_label.setStyleSheet(f"color: {SECONDARY_TEXT_COLOR};")
        left_form.addWidget(file_path_label)
        
        self.file_path_input = QLineEdit()
        self.file_path_input.setPlaceholderText("Путь к БД")
        self.file_path_input.setStyleSheet(f"""
            QLineEdit {{
                background-color: {BUTTON_BACKGROUND};
                color: {TEXT_COLOR};
                border: none;
                padding: 10px;
                border-radius: 8px;
                margin: 20px 0;
            }}
        """)
        left_form.addWidget(self.file_path_input)
        
        # Правая часть формы
        right_form = QVBoxLayout()
        form_layout.addLayout(right_form)
        
        self.columns_combobox = CustomComboBox("Выбор столбцов")
        right_form.addWidget(self.columns_combobox)
        
        self.delimiter_combobox = CustomComboBox("Разделитель")
        right_form.addWidget(self.delimiter_combobox)
        
        browse_button = RoundButton("Обзор", white_text=True)
        browse_button.clicked.connect(self.browse_file)
        right_form.addWidget(browse_button)
        
        # Кнопки действия
        buttons_layout = QHBoxLayout()
        layout.addLayout(buttons_layout)
        
        self.check_button = RoundButton("Проверить файл")
        self.check_button.clicked.connect(self.check_file)
        buttons_layout.addWidget(self.check_button)
        
        self.import_button = RoundButton("Импортировать", white_text=True)
        self.import_button.setEnabled(False)
        self.import_button.clicked.connect(self.import_file)
        buttons_layout.addWidget(self.import_button)
        
    def browse_file(self):
        file_path, _ = QFileDialog.getOpenFileName(self, "Выберите CSV файл", "", "CSV Files (*.csv)")
        if file_path:
            self.file_path_input.setText(file_path)
    
    def check_file(self):
        # Здесь должна быть логика проверки файла
        self.import_button.setEnabled(True)
        QMessageBox.information(self, "Успешно", "Файл успешно проверен!")
    
    def import_file(self):
        # Здесь должна быть логика импорта файла
        QMessageBox.information(self, "Успешно", "Данные успешно импортированы!")
        # Переключение на страницу реестра записей
        # Для примера просто закрываем окно
        self.window().close()

class CustomComboBox(QComboBox):
    def __init__(self, placeholder):
        super().__init__()
        self.setEditable(True)
        self.lineEdit().setReadOnly(True)
        self.lineEdit().setAlignment(Qt.AlignCenter)
        self.setStyleSheet(f"""
            QComboBox {{
                background-color: {BUTTON_BACKGROUND};
                color: {TEXT_COLOR};
                border: 1px solid {TEXT_COLOR};
                padding: 10px;
                border-radius: 8px;
                min-width: 200px;
            }}
            QComboBox::drop-down {{
                subcontrol-position: right center;
                width: 20px;
            }}
            QComboBox::down-arrow {{
                image: url(down_arrow.png); /* Заменить на реальный путь */
                width: 12px;
                height: 12px;
            }}
        """)
        self.addItem(placeholder)
        self.model().item(0).setEnabled(False)

class RoundButton(QPushButton):
    def __init__(self, text, white_text=False):
        super().__init__(text)
        self.setStyleSheet(f"""
            QPushButton {{
                background-color: {'white' if white_text else BUTTON_BACKGROUND};
                color: {'black' if white_text else TEXT_COLOR};
                border: {'1px solid white' if white_text else 'none'};
                padding: 12px 24px;
                border-radius: 24px;
                font-weight: bold;
            }}
            QPushButton:hover {{
                background-color: {'#e0e0e0' if white_text else '#3d3d3d'};
            }}
        """)

class DataRegistryWindow(QWidget):
    def __init__(self):
        super().__init__()
        layout = QHBoxLayout(self)
        
        # Сайдбар
        sidebar = Sidebar()
        layout.addWidget(sidebar)
        
        # Основное содержимое
        main_content = QTabWidget()
        main_content.addTab(DataTable(), "Реестр записей")
        main_content.addTab(Dashboard(), "Дашборд")
        main_content.setStyleSheet(f"""
            QTabWidget {{
                background-color: {PRIMARY_BACKGROUND};
            }}
            QTabBar::tab {{
                background-color: {PRIMARY_BACKGROUND};
                color: {SECONDARY_TEXT_COLOR};
                min-width: 120px;
                padding: 8px 0;
            }}
            QTabBar::tab:selected {{
                color: {TEXT_COLOR};
                font-weight: bold;
            }}
        """)
        layout.addWidget(main_content, stretch=1)

class Sidebar(QWidget):
    def __init__(self):
        super().__init__()
        self.setStyleSheet(f"background-color: {SIDEBAR_BACKGROUND};")
        layout = QVBoxLayout(self)
        layout.setSpacing(0)
        
        # Вкладки
        tabs = ["Удаление строк с пропусками", "Заполнение пропусков", "Нормализация данных", 
                "Стандартизация данных", "Удаление выбросов через IQR-метод", 
                "Фильтрация строк по условию", "One-Hot Encoding для категориальных переменных", 
                "Сортировка по заранее заданному массиву-порядку", 
                "Фильтрация по заранее заданному массиву-фильтру"]
        
        for tab in tabs:
            item = QListWidgetItem(tab)
            item.setBackground(QColor(SIDEBAR_BACKGROUND))
            item.setForeground(QColor(TEXT_COLOR))
            list_widget = QListWidget()
            list_widget.addItem(item)
            list_widget.setStyleSheet(f"""
                QListWidget {{
                    background-color: {SIDEBAR_BACKGROUND};
                    color: {TEXT_COLOR};
                    border: none;
                }}
                QListWidget::item:selected {{
                    background-color: {PRIMARY_BACKGROUND};
                }}
            """)
            layout.addWidget(list_widget)

class DataTable(QWidget):
    def __init__(self):
        super().__init__()
        layout = QVBoxLayout(self)
        
        # Таблица
        self.table = QTableWidget()
        self.table.setColumnCount(5)
        self.table.setHorizontalHeaderLabels(["id", "biba", "boba", "buba", "int_char"])
        self.table.setStyleSheet(f"""
            QTableWidget {{
                background-color: {PRIMARY_BACKGROUND};
                color: {TEXT_COLOR};
                gridline-color: {SECONDARY_TEXT_COLOR};
            }}
            QHeaderView {{
                background-color: {PRIMARY_BACKGROUND};
                color: {TEXT_COLOR};
            }}
        """)
        self.table.horizontalHeader().setSectionResizeMode(QHeaderView.Stretch)
        layout.addWidget(self.table)

class Dashboard(QWidget):
    def __init__(self):
        super().__init__()
        layout = QVBoxLayout(self)
        layout.addWidget(QLabel("Дашборд"))

if __name__ == "__main__":
    app = QApplication([])
    window = MainWindow()
    window.show()
    app.exec()