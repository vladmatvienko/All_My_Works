import tkinter as tk
from tkinter import messagebox, filedialog, simpledialog
from tkinter.ttk import Treeview, Style
from DB import FileDatabase
class DatabaseApp:
    """Графический интерфейс для работы с базой данных"""

    def __init__(self, root):
        """Инициализация интерфейса"""
        self.db = FileDatabase()  # Создаем объект базы данных

        # Основное окно
        root.title("Файловая база данных")
        root.geometry("1100x600")
        root.configure(bg="#2D2D2D")

        # Стиль таблицы
        style = Style()
        style.configure("Treeview", background="#FFFFFF", foreground="black", fieldbackground="#FFFFFF")
        style.configure("Treeview.Heading", font=("Helvetica", 12, "bold"), background="#6A0DAD", foreground="black")

        # Таблица для отображения записей
        self.tree = Treeview(root, columns=("key", "name", "age", "salary"), show="headings")
        self.tree.heading("key", text="Ключ")
        self.tree.heading("name", text="Имя")
        self.tree.heading("age", text="Возраст")
        self.tree.heading("salary", text="Зарплата")
        self.tree.pack(fill=tk.BOTH, expand=True)

        # Панель кнопок
        button_frame = tk.Frame(root, bg="#2D2D2D")
        button_frame.pack(fill=tk.X, padx=10, pady=10)

        # Кнопки первого ряда
        button_params = {"bg": "#4B0082", "fg": "white", "font": ("Helvetica", 10, "bold"), "width": 20}
        tk.Button(button_frame, text="Создать", command=self.create_database, **button_params).grid(row=0, column=0, padx=5, pady=5)
        tk.Button(button_frame, text="Открыть", command=self.open_database, **button_params).grid(row=0, column=1, padx=5, pady=5)
        tk.Button(button_frame, text="Сохранить", command=self.save_database, **button_params).grid(row=0, column=2, padx=5, pady=5)
        tk.Button(button_frame, text="Добавить запись", command=self.add_record, **button_params).grid(row=0, column=3, padx=5, pady=5)
        tk.Button(button_frame, text="Редактировать запись", command=self.edit_record_gui, **button_params).grid(row=0, column=4, padx=5, pady=5)
        tk.Button(button_frame, text="Восстановить backup", command=self.restore_backup, **button_params).grid(row=0, column=5, padx=5, pady=5)

        # Кнопки второго ряда
        tk.Button(button_frame, text="Удалить по ключу", command=self.delete_record, **button_params).grid(row=1, column=0, padx=5, pady=5)
        tk.Button(button_frame, text="Очистить", command=self.clear_database, **button_params).grid(row=1, column=1, padx=5, pady=5)
        tk.Button(button_frame, text="Найти по ключу", command=self.search_record, **button_params).grid(row=1, column=2, padx=5, pady=5)
        tk.Button(button_frame, text="Экспорт в Excel", command=self.export_to_excel, **button_params).grid(row=1, column=3, padx=5, pady=5)
        tk.Button(button_frame, text="Создать backup", command=self.create_backup, **button_params).grid(row=1, column=4, padx=5, pady=5)
        tk.Button(button_frame, text="¯\_(ツ)_/¯", command=self.clear_database, **button_params).grid(row=1, column=5, padx=5, pady=5)

    def edit_record_gui(self):
        """Редактирование записи через интерфейс"""
        def submit_edit():
            try:
                updated_record = {
                    "key": key_entry.get().strip(),
                    "name": name_entry.get().strip(),
                    "age": int(age_entry.get()),
                    "salary": float(salary_entry.get())
                }
                self.db.edit_record(key, updated_record)
                self.refresh_table()
                edit_window.destroy()
                messagebox.showinfo("Успех", "Запись отредактирована!")
            except ValueError as e:
                messagebox.showerror("Ошибка", f"Некорректные данные: {e}")

        key = simpledialog.askstring("Редактировать запись", "Введите ключ записи для редактирования:")
        if key:
            results = self.db.search(key)
            if results:
                record = results[0]
                edit_window = tk.Toplevel()
                edit_window.title("Редактировать запись")
                edit_window.geometry("400x300")
                edit_window.configure(bg="#2D2D2D")

                tk.Label(edit_window, text="Ключ", bg="#2D2D2D", fg="white", font=("Helvetica", 12)).pack(pady=5)
                key_entry = tk.Entry(edit_window, font=("Helvetica", 12))
                key_entry.insert(0, record["key"])
                key_entry.pack(pady=5)

                tk.Label(edit_window, text="Имя", bg="#2D2D2D", fg="white", font=("Helvetica", 12)).pack(pady=5)
                name_entry = tk.Entry(edit_window, font=("Helvetica", 12))
                name_entry.insert(0, record["name"])
                name_entry.pack(pady=5)

                tk.Label(edit_window, text="Возраст", bg="#2D2D2D", fg="white", font=("Helvetica", 12)).pack(pady=5)
                age_entry = tk.Entry(edit_window, font=("Helvetica", 12))
                age_entry.insert(0, record["age"])
                age_entry.pack(pady=5)

                tk.Label(edit_window, text="Зарплата", bg="#2D2D2D", fg="white", font=("Helvetica", 12)).pack(pady=5)
                salary_entry = tk.Entry(edit_window, font=("Helvetica", 12))
                salary_entry.insert(0, record["salary"])
                salary_entry.pack(pady=5)

                tk.Button(edit_window, text="Сохранить", command=submit_edit, bg="#4B0082", fg="white", font=("Helvetica", 12)).pack(pady=10)
            else:
                messagebox.showinfo("Ошибка", "Запись с указанным ключом не найдена!")

    def create_database(self):
        """Создание новой базы данных"""
        file_path = filedialog.asksaveasfilename(defaultextension=".txt", filetypes=[("Text files", "*.txt")])
        if file_path:
            open(file_path, "w").close()  # Создаем пустой файл
            self.db.file_path = file_path
            self.db.clear()
            self.refresh_table()
            messagebox.showinfo("Успех", "Новая база данных создана!")

    def open_database(self):
        """Открытие существующей базы данных"""
        file_path = filedialog.askopenfilename(filetypes=[("Text files", "*.txt")])
        if file_path:
            try:
                self.db.load(file_path)
                self.refresh_table()
                messagebox.showinfo("Успех", "База данных загружена!")
            except Exception as e:
                messagebox.showerror("Ошибка", f"Не удалось открыть базу данных: {e}")

    def save_database(self):
        """Сохранение изменений в базу данных"""
        try:
            self.db.save()
            messagebox.showinfo("Успех", "База данных сохранена!")
        except Exception as e:
            messagebox.showerror("Ошибка", f"Не удалось сохранить базу данных: {e}")

    def add_record(self):
        """Добавление новой записи"""

        def submit_record():
            try:
                key = key_entry.get().strip()
                name = name_entry.get().strip()
                age = int(age_entry.get())
                salary = float(salary_entry.get())
                self.db.add_record({"key": key, "name": name, "age": age, "salary": salary})
                self.refresh_table()
                add_window.destroy()
                messagebox.showinfo("Успех", "Запись добавлена!")
            except ValueError as e:
                messagebox.showerror("Ошибка", f"Некорректные данные: {e}")

        add_window = tk.Toplevel()
        add_window.title("Добавить запись")
        add_window.geometry("400x300")
        add_window.configure(bg="#2D2D2D")

        tk.Label(add_window, text="Ключ", bg="#2D2D2D", fg="white", font=("Helvetica", 12)).pack(pady=5)
        key_entry = tk.Entry(add_window, font=("Helvetica", 12))
        key_entry.pack(pady=5)

        tk.Label(add_window, text="Имя", bg="#2D2D2D", fg="white", font=("Helvetica", 12)).pack(pady=5)
        name_entry = tk.Entry(add_window, font=("Helvetica", 12))
        name_entry.pack(pady=5)

        tk.Label(add_window, text="Возраст", bg="#2D2D2D", fg="white", font=("Helvetica", 12)).pack(pady=5)
        age_entry = tk.Entry(add_window, font=("Helvetica", 12))
        age_entry.pack(pady=5)

        tk.Label(add_window, text="Зарплата", bg="#2D2D2D", fg="white", font=("Helvetica", 12)).pack(pady=5)
        salary_entry = tk.Entry(add_window, font=("Helvetica", 12))
        salary_entry.pack(pady=5)

        tk.Button(add_window, text="Добавить", command=submit_record, bg="#4B0082", fg="white",
                  font=("Helvetica", 12)).pack(pady=10)

    def delete_record(self):
        """Удаление записи по ключу"""
        key = simpledialog.askstring("Удалить запись", "Введите ключ записи для удаления:")
        if key:
            self.db.delete_record(key)
            self.refresh_table()
            messagebox.showinfo("Успех", "Запись удалена!")

    def clear_database(self):
        """Очистка базы данных"""
        if messagebox.askyesno("Подтвердить", "Вы уверены, что хотите очистить всю базу данных?"):
            self.db.clear()
            self.refresh_table()
            messagebox.showinfo("Успех", "База данных очищена!")

    def search_record(self):
        """Поиск записи по ключу"""
        key = simpledialog.askstring("Поиск записи", "Введите ключ для поиска:")
        if key:
            results = self.db.search(key)
            if results:
                result_window = tk.Toplevel()  # Создаем новое окно для отображения результата
                result_window.title("Результат поиска")
                result_window.geometry("400x300")
                result_window.configure(bg="#2D2D2D")

                # Отображаем найденные записи
                tk.Label(result_window, text="Результаты поиска:", bg="#2D2D2D", fg="white",
                         font=("Helvetica", 14)).pack(pady=10)
                text_box = tk.Text(result_window, wrap="word", bg="#FFFFFF", fg="#000000", font=("Helvetica", 12),
                                   height=10, width=50)
                text_box.pack(pady=10)

                for record in results:
                    result_text = (
                        f"Ключ: {record['key']}\n"
                        f"Имя: {record['name']}\n"
                        f"Возраст: {record['age']}\n"
                        f"Зарплата: {record['salary']}\n\n"
                    )
                    text_box.insert(tk.END, result_text)  # Добавляем текст в текстовое поле
                text_box.config(state="disabled")  # Запрещаем редактирование текста
            else:
                messagebox.showinfo("Результат поиска", "Записей не найдено!")

    def create_backup(self):
        """Создание резервной копии базы данных"""
        try:
            self.db.create_backup()
            messagebox.showinfo("Успех", "Резервная копия создана!")
        except Exception as e:
            messagebox.showerror("Ошибка", f"Не удалось создать резервную копию: {e}")

    def restore_backup(self):
        """Восстановление базы данных из резервной копии"""
        try:
            self.db.restore_backup()
            self.refresh_table()
            messagebox.showinfo("Успех", "База данных восстановлена из резервной копии!")
        except Exception as e:
            messagebox.showerror("Ошибка", f"Не удалось восстановить базу данных: {e}")

    def export_to_excel(self):
        """Экспорт базы данных в Excel"""
        file_path = filedialog.asksaveasfilename(defaultextension=".xlsx", filetypes=[("Excel files", "*.xlsx")])
        if file_path:
            try:
                self.db.export_to_excel(file_path)
                messagebox.showinfo("Успех", "Данные экспортированы в Excel!")
            except Exception as e:
                messagebox.showerror("Ошибка", f"Не удалось экспортировать данные: {e}")

    def refresh_table(self):
        """Обновление содержимого таблицы"""
        self.tree.delete(*self.tree.get_children())
        for record in self.db.data:
            self.tree.insert("", tk.END, values=(record["key"], record["name"], record["age"], record["salary"]))