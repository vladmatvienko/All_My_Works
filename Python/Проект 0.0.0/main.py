import sys
from PyQt5.QtWidgets import (
    QApplication, QMainWindow, QWidget, QHBoxLayout, QVBoxLayout,
    QLabel, QPushButton, QLineEdit, QFileDialog, QTabWidget, QStackedWidget,
    QComboBox, QListWidget, QListWidgetItem, QDialog, QCheckBox
)
from PyQt5.QtGui import QIcon, QColor, QFont
from PyQt5.QtCore import Qt

# Цветовая палитра
COLOR_PALETTE = {
    'background': '#212121',
    'sidebar': '#171717',
    'text_primary': '#FFFFFF',
    'text_secondary': '#808080',
    'button_background': '#2F2F2F',
    'icon_text': '#FFFFFF'
}

class MainWindow(QMainWindow):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("AIData")
        self.setGeometry(100, 100, 1200, 800)
        self.setContentsMargins(0, 0, 0, 0)
        
        # Установка стиля
        self.setStyleSheet(f"""
            QMainWindow {{
                background-color: {COLOR_PALETTE['background']};
            }}
            QWidget {{
                color: {COLOR_PALETTE['text_primary']};
            }}
            QLabel {{
                color: {COLOR_PALETTE['text_primary']};
            }}
            QPushButton {{
                background-color: {COLOR_PALETTE['button_background']};
                border-radius: 12px;
                padding: 10px 20px;
                font-size: 14px;
            }}
            QPushButton#primary {{
                color: {COLOR_PALETTE['text_primary']};
            }}
            QPushButton#secondary {{
                border: 1px solid {COLOR_PALETTE['text_primary']};
                color: {COLOR_PALETTE['text_primary']};
            }}
            QTabBar::tab {{
                background-color: {COLOR_PALETTE['button_background']};
                color: {COLOR_PALETTE['text_secondary']};
                padding: 5px 15px;
                border-top-left-radius: 6px;
                border-top-right-radius: 6px;
            }}
            QTabBar::tab:selected {{
                color: {COLOR_PALETTE['text_primary']};
            }}
            QLineEdit {{
                background-color: {COLOR_PALETTE['button_background']};
                border-radius: 8px;
                padding: 5px 10px;
            }}
            QComboBox {{
                background-color: {COLOR_PALETTE['button_background']};
                border-radius: 8px;
                padding: 5px 10px;
            }}
        """)
        
        # Создание центрального виджета
        central_widget = QWidget()
        self.setCentralWidget(central_widget)
        
        # Основной макет
        main_layout = QVBoxLayout()
        central_widget.setLayout(main_layout)
        
        # Хедер
        header = QWidget()
        header.setObjectName("header")
        header_layout = QHBoxLayout()
        header.setLayout(header_layout)
        
        # Логотип
        logo_label = QLabel()
        logo_label.setPixmap(QIcon("logotype.png").pixmap(48, 48))
        header_layout.addWidget(logo_label)
        
        # Текст логотипа
        logo_text = QLabel("AIData")
        logo_text.setFont(QFont("Arial", 16, QFont.Bold))
        header_layout.addWidget(logo_text)
        header_layout.addStretch()
        
        # Табы
        tab_widget = QTabWidget()
        tab_widget.setObjectName("tabs")
        tab_widget.addTab(QWidget(), "Анализ")
        tab_widget.addTab(QWidget(), "Генерация")
        tab_widget.setCurrentIndex(0)
        
        main_layout.addWidget(header)
        main_layout.addWidget(tab_widget)
        
        # Настройка страниц
        self.stacked_widget = QStackedWidget()
        tab_widget.currentChanged.connect(self.stacked_widget.setCurrentIndex)
        main_layout.addWidget(self.stacked_widget)
        
        # Добавление страницы Анализа
        analysis_page = AnalysisPage()
        self.stacked_widget.addWidget(analysis_page)
        
        # Добавление страницы Генерации (заглушка)
        generation_page = QWidget()
        self.stacked_widget.addWidget(generation_page)

class AnalysisPage(QWidget):
    def __init__(self):
        super().__init__()
        self.init_ui()
        
    def init_ui(self):
        layout = QVBoxLayout()
        self.setLayout(layout)
        
        # Заголовок
        title = QLabel("Анализ")
        title.setFont(QFont("Arial", 24, QFont.Bold))
        layout.addWidget(title, alignment=Qt.AlignLeft)
        
        # Описание
        description = QLabel(
            "Раздел «Анализ» предоставляет широкие возможности для исследования и обработки данных в удобной визуальной форме. "
            "Вы можете работать как с реестром записей, так и с дашбордом, получая глубокое понимание структуры и характеристик вашего датасета."
        )
        description.setWordWrap(True)
        layout.addWidget(description, alignment=Qt.AlignLeft)
        layout.addSpacing(30)
        
        # Форма загрузки файла
        form_layout = QHBoxLayout()
        layout.addLayout(form_layout)
        
        # Левая часть формы
        left_form = QVBoxLayout()
        form_layout.addLayout(left_form)
        
        # Подпись для пути
        path_label = QLabel("Укажите путь к csv-файлу базы данных")
        left_form.addWidget(path_label)
        
        # Поле ввода пути
        self.path_input = QLineEdit()
        self.path_input.setPlaceholderText("Путь к БД")
        self.path_input.setObjectName("path_input")
        left_form.addWidget(self.path_input)
        
        # Кнопки функционала
        buttons_layout = QHBoxLayout()
        left_form.addLayout(buttons_layout)
        
        self.check_button = QPushButton("Проверить файл")
        self.check_button.setObjectName("secondary")
        self.check_button.clicked.connect(self.check_file)
        buttons_layout.addWidget(self.check_button)
        
        self.import_button = QPushButton("Импортировать")
        self.import_button.setObjectName("primary")
        self.import_button.setEnabled(False)
        self.import_button.clicked.connect(self.import_file)
        buttons_layout.addWidget(self.import_button)
        
        # Правая часть формы
        right_form = QVBoxLayout()
        form_layout.addLayout(right_form)
        
        # Выбор столбцов
        self.columns_combobox = QComboBox()
        self.columns_combobox.setObjectName("columns_combobox")
        self.columns_combobox.addItem("Выбор столбцов")
        self.columns_combobox.currentIndexChanged.connect(self.open_column_selector)
        right_form.addWidget(self.columns_combobox)
        
        # Выбор разделителя
        self.delimiter_combobox = QComboBox()
        self.delimiter_combobox.setObjectName("delimiter_combobox")
        self.delimiter_combobox.addItem("Разделитель")
        self.delimiter_combobox.addItems([",", ";", "|", "\t"])
        right_form.addWidget(self.delimiter_combobox)
        
        # Кнопка Обзор
        browse_button = QPushButton("Обзор")
        browse_button.setObjectName("secondary")
        browse_button.clicked.connect(self.browse_file)
        right_form.addWidget(browse_button)
        
        # Модальное окно выбора столбцов
        self.column_selector = ColumnSelector()
        self.column_selector.accepted.connect(self.update_columns)
        
    def browse_file(self):
        file_path, _ = QFileDialog.getOpenFileName(self, "Выберите CSV файл", "", "CSV Files (*.csv)")
        if file_path:
            self.path_input.setText(file_path)
    
    def check_file(self):
        file_path = self.path_input.text()
        if not file_path:
            return
        
        try:
            with open(file_path, 'r') as f:
                first_line = f.readline()
                columns = first_line.strip().split(',')
                self.columns_combobox.clear()
                self.columns_combobox.addItem("Выбор столбцов")
                for col in columns:
                    self.columns_combobox.addItem(col)
                self.import_button.setEnabled(True)
        except Exception as e:
            print(f"Ошибка проверки файла: {e}")
    
    def import_file(self):
        # Здесь должна быть логика импорта данных
        print("Файл импортирован!")
        # Переключение на другую страницу после импорта
        # В текущей задаче эта логика не реализована
    
    def open_column_selector(self):
        if self.columns_combobox.currentIndex() == 0:
            return
        self.column_selector.show()
    
    def update_columns(self):
        selected_columns = self.column_selector.selected_columns()
        print(f"Выбранные столбцы: {selected_columns}")

class ColumnSelector(QDialog):
    def __init__(self):
        super().__init__()
        self.setWindowTitle("Выберите столбец")
        self.setModal(True)
        self.setStyleSheet(f"""
            QDialog {{
                background-color: {COLOR_PALETTE['background']};
                border-radius: 12px;
                padding: 20px;
            }}
        """)
        
        layout = QVBoxLayout()
        self.setLayout(layout)
        
        title = QLabel("Выберите столбец")
        title.setFont(QFont("Arial", 18, QFont.Bold))
        layout.addWidget(title, alignment=Qt.AlignCenter)
        
        self.list_widget = QListWidget()
        self.list_widget.setSelectionMode(QListWidget.NoSelection)
        layout.addWidget(self.list_widget)
        
        button = QPushButton("Выбрать")
        button.setObjectName("primary")
        button.clicked.connect(self.accept)
        layout.addWidget(button, alignment=Qt.AlignRight)
        
        # Добавление тестовых элементов
        for i in range(5):
            item = QListWidgetItem(f"Столбец {i+1}")
            checkbox = QCheckBox()
            item.setSizeHint(checkbox.sizeHint())
            self.list_widget.addItem(item)
            self.list_widget.setItemWidget(item, checkbox)
    
    def selected_columns(self):
        selected = []
        for index in range(self.list_widget.count()):
            item = self.list_widget.item(index)
            checkbox = self.list_widget.itemWidget(item)
            if checkbox.isChecked():
                selected.append(item.text())
        return selected

if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = MainWindow()
    window.show()
    sys.exit(app.exec_())