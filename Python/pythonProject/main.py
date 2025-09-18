import customtkinter as ctk
from tkinter import filedialog, messagebox
from file_db import FileDatabase


class ModernDatabaseApp:
    def __init__(self, root):
        self.db = None
        self.root = root
        self.root.title("File Database")
        ctk.set_appearance_mode("dark")  # Режим "тёмная тема"
        ctk.set_default_color_theme("blue")  # Цветовая тема: "blue", "dark-blue", "green"

        self.setup_ui()

    def setup_ui(self):
        # Основной фрейм
        self.frame = ctk.CTkFrame(self.root)
        self.frame.pack(padx=20, pady=20, fill="both", expand=True)

        # Заголовок
        self.label = ctk.CTkLabel(self.frame, text="Файловая База Данных", font=("Roboto", 18, "bold"))
        self.label.pack(pady=(0, 20))

        # Кнопки для работы с БД
        self.create_button = ctk.CTkButton(self.frame, text="Создать БД", command=self.create_db, width=200)
        self.create_button.pack(pady=10)

        self.open_button = ctk.CTkButton(self.frame, text="Открыть БД", command=self.open_db, width=200)
        self.open_button.pack(pady=10)

        self.add_button = ctk.CTkButton(self.frame, text="Добавить запись", command=self.add_record, width=200)
        self.add_button.pack(pady=10)

        self.search_button = ctk.CTkButton(self.frame, text="Поиск", command=self.search, width=200)
        self.search_button.pack(pady=10)

        self.delete_button = ctk.CTkButton(self.frame, text="Удалить запись", command=self.delete_record, width=200)
        self.delete_button.pack(pady=10)

        self.backup_button = ctk.CTkButton(self.frame, text="Создать резервную копию", command=self.backup_db,
                                           width=200)
        self.backup_button.pack(pady=10)

        self.restore_button = ctk.CTkButton(self.frame, text="Восстановить из резервной копии", command=self.restore_db,
                                            width=200)
        self.restore_button.pack(pady=10)

        # Выход
        self.exit_button = ctk.CTkButton(self.frame, text="Выход", command=self.root.quit, width=200, fg_color="red")
        self.exit_button.pack(pady=(10, 0))

    def create_db(self):
        filepath = filedialog.asksaveasfilename(title="Создать файл БД", defaultextension=".txt")
        if filepath:
            self.db = FileDatabase(filepath)
            self.db.create_db()
            messagebox.showinfo("Успех", "БД создана.")

    def open_db(self):
        filepath = filedialog.askopenfilename(title="Открыть файл БД", filetypes=[("Text Files", "*.txt")])
        if filepath:
            self.db = FileDatabase(filepath)
            self.db.open_db()
            messagebox.showinfo("Успех", "БД открыта.")

    def add_record(self):
        if not self.db:
            messagebox.showerror("Ошибка", "Сначала откройте или создайте БД.")
            return

        record_window = ctk.CTkToplevel(self.root)
        record_window.title("Добавить запись")
        record_window.geometry("400x300")

        label = ctk.CTkLabel(record_window, text="Введите запись (ID, Name, Age, Address):", anchor="w")
        label.pack(pady=10, padx=20)

        entry = ctk.CTkEntry(record_window, width=300)
        entry.pack(pady=10)

        def save_record():
            record = entry.get()
            if record:
                try:
                    self.db.add_record(record)
                    messagebox.showinfo("Успех", "Запись добавлена.")
                    record_window.destroy()
                except ValueError as e:
                    messagebox.showerror("Ошибка", str(e))
            else:
                messagebox.showerror("Ошибка", "Запись не может быть пустой.")

        save_button = ctk.CTkButton(record_window, text="Сохранить", command=save_record)
        save_button.pack(pady=10)

    def search(self):
        if not self.db:
            messagebox.showerror("Ошибка", "Сначала откройте или создайте БД.")
            return

        search_window = ctk.CTkToplevel(self.root)
        search_window.title("Поиск")
        search_window.geometry("400x300")

        label = ctk.CTkLabel(search_window, text="Введите значение для поиска:", anchor="w")
        label.pack(pady=10, padx=20)

        entry = ctk.CTkEntry(search_window, width=300)
        entry.pack(pady=10)

        def perform_search():
            value = entry.get()
            if value:
                results = self.db.search(value)
                if results:
                    result_text = "\n".join(results)
                else:
                    result_text = "Ничего не найдено."
                result_label = ctk.CTkLabel(search_window, text=f"Результаты поиска:\n{result_text}", wraplength=350)
                result_label.pack(pady=10)
            else:
                messagebox.showerror("Ошибка", "Введите значение для поиска.")

        search_button = ctk.CTkButton(search_window, text="Найти", command=perform_search)
        search_button.pack(pady=10)

    def delete_record(self):
        if not self.db:
            messagebox.showerror("Ошибка", "Сначала откройте или создайте БД.")
            return

        key = ctk.CTkInputDialog(text="Введите значение для удаления:", title="Удаление").get_input()
        if key:
            self.db.delete_record(key)
            messagebox.showinfo("Успех", "Запись удалена.")

    def backup_db(self):
        if not self.db:
            messagebox.showerror("Ошибка", "Сначала откройте или создайте БД.")
            return

        backup_path = filedialog.asksaveasfilename(title="Создать резервную копию", defaultextension=".bak")
        if backup_path:
            self.db.backup(backup_path)
            messagebox.showinfo("Успех", "Резервная копия создана.")

    def restore_db(self):
        if not self.db:
            messagebox.showerror("Ошибка", "Сначала откройте или создайте БД.")
            return

        backup_path = filedialog.askopenfilename(title="Восстановить из резервной копии",
                                                 filetypes=[("Backup Files", "*.bak")])
        if backup_path:
            self.db.restore(backup_path)
            messagebox.showinfo("Успех", "БД восстановлена.")


if __name__ == "__main__":
    root = ctk.CTk()
    app = ModernDatabaseApp(root)
    root.geometry("400x600")
    root.mainloop()