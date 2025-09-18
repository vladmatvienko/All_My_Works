import openpyxl
class FileDatabase:
    """Класс для работы с текстовой базой данных"""

    def __init__(self):
        """Инициализация внутреннего хранилища и пути к файлу"""
        self.data = []  # Список для хранения записей базы данных
        self.file_path = None  # Путь к текущему файлу базы данных

    def load(self, file_path):
        """Загрузка базы данных из файла"""
        self.data = []  # Очищаем текущую базу
        try:
            with open(file_path, "r") as file:
                for line in file:
                    fields = line.strip().split("|")  # Делим строку по символу "|"
                    record = {
                        "key": fields[0],       # Поле ключа (строка)
                        "name": fields[1],      # Поле имени (строка)
                        "age": int(fields[2]),  # Поле возраста (число)
                        "salary": float(fields[3]),  # Поле зарплаты (вещественное число)
                    }
                    self.data.append(record)  # Добавляем запись в базу
            self.file_path = file_path  # Сохраняем путь к текущему файлу
        except Exception as e:
            raise ValueError(f"Ошибка загрузки базы данных: {e}")

    def save(self):
        """Сохранение базы данных в файл"""
        if not self.file_path:
            raise ValueError("Файл базы данных не указан!")
        with open(self.file_path, "w") as file:
            for record in self.data:
                # Форматируем запись для сохранения
                line = f"{record['key']}|{record['name']}|{record['age']}|{record['salary']}\n"
                file.write(line)

    def add_record(self, record):
        """Добавление новой записи с проверкой уникальности ключа"""
        if any(r["key"] == record["key"] for r in self.data):
            raise ValueError("Ключевое поле должно быть уникальным.")
        self.data.append(record)  # Добавляем новую запись
        self.data.sort(key=lambda x: x["key"])  # Сортируем данные по ключу

    def delete_record(self, key):
        """Удаление записи по ключу"""
        self.data = [record for record in self.data if record["key"] != key]

    def clear(self):
        """Очистка всей базы данных"""
        self.data = []

    def search(self, key):
        """Поиск записи по ключу"""
        return [record for record in self.data if record["key"] == key]

    def edit_record(self, key, updated_record):
        """Редактирование записи по ключу"""
        for i, record in enumerate(self.data):
            if record["key"] == key:
                self.data[i] = updated_record
                return
        raise ValueError("Запись с указанным ключом не найдена!")

    def create_backup(self):
        """Создание резервной копии базы данных"""
        if not self.file_path:
            raise ValueError("Файл базы данных не указан!")
        if any(f == ".bak" for f in self.file_path):
            backup_path = self.file_path  # Путь к файлу резервной копии
        else:
            backup_path = self.file_path + ".bak"  # Путь к файлу резервной копии
        with open(backup_path, "w") as backup_file:
            for record in self.data:
                # Форматируем каждую запись для резервного копирования
                line = f"{record['key']}|{record['name']}|{record['age']}|{record['salary']}\n"
                backup_file.write(line)

    def restore_backup(self):
        """Восстановление базы данных из резервной копии"""
        self.data = []  # Очищаем текущие записи
        backup_path = self.file_path + ".bak"  # Путь к резервной копии
        with open(backup_path, "r") as file:
            for line in file:
                # Разделяем строку по символу "|", чтобы получить поля записи
                fields = line.strip().split("|")
                # Преобразуем значения в нужные типы и создаём словарь записи
                record = {
                    "key": fields[0],  # Ключевое поле (целое число)
                    "name": fields[1],  # Имя (строка)
                    "age": int(fields[2]),  # Возраст (целое число)
                    "salary": float(fields[3]),  # Зарплата (вещественное число)
                }
                self.data.append(record)  # Добавляем запись в список данных
        self.file_path = backup_path.removesuffix(".bak")  # Сохраняем путь к открытому файлу

    def export_to_excel(self, file_path):
        """Экспорт базы данных в файл Excel"""
        workbook = openpyxl.Workbook()
        sheet = workbook.active
        sheet.title = "Database"
        # Добавляем заголовки
        sheet.append(["Key", "Name", "Age", "Salary"])
        # Добавляем данные из базы
        for record in self.data:
            sheet.append([record["key"], record["name"], record["age"], record["salary"]])
        workbook.save(file_path)