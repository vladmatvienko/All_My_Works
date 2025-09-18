# KartingCenterGUI.py
import tkinter as tk
from tkinter import ttk, messagebox
from DatabaseManager import DatabaseManager

class KartingCenterApp:
    def __init__(self, root):
        self.root = root
        self.root.title("Картинг-центр")
        self.root.geometry("1500x700")

        # Инициализация менеджера базы данных
        self.db_manager = DatabaseManager()

        # Создание ролей и пользователей
        self.db_manager.create_database_roles()

        # Переменные для хранения состояния пользователя
        self.current_user_role = None
        self.current_user_username = None

        # Создание интерфейса входа
        self.create_login_screen()

    def create_login_screen(self):
        """Создание экрана входа."""
        self.clear_screen()

        tk.Label(self.root, text="Логин:", font=("Arial", 16)).place(x=50, y=50)
        self.username_entry = tk.Entry(self.root, font=("Arial", 16))
        self.username_entry.place(x=150, y=50)

        tk.Label(self.root, text="Пароль:", font=("Arial", 16)).place(x=50, y=100)
        self.password_entry = tk.Entry(self.root, show="*", font=("Arial", 16))
        self.password_entry.place(x=150, y=100)

        tk.Button(self.root, text="Войти", command=self.login, font=("Arial", 16), width=10).place(x=150, y=150)

    def login(self):
        """Обработка входа пользователя."""
        username = self.username_entry.get()
        password = self.password_entry.get()

        role = self.db_manager.authenticate_user(username, password)
        if role:
            self.current_user_role = role
            self.current_user_username = username
            messagebox.showinfo("Успех", f"Добро пожаловать, {username}!")
            if role == "Administrator":
                self.create_admin_screen()
            elif role == "Guest":
                self.create_guest_screen()
        else:
            messagebox.showerror("Ошибка", "Неверный логин или пароль.")

    def create_guest_screen(self):
        """Создание экрана гостя."""
        self.clear_screen()

        tk.Label(self.root, text="Окно гостя", font=("Arial", 20)).place(x=50, y=50)
        tk.Button(self.root, text="Посмотреть таблицу", command=self.view_table_guest_screen, font=("Arial", 16),  width=20).place(x=50, y=100)
        tk.Button(self.root, text="Назад", command=self.create_login_screen, font=("Arial", 16), width=10).place(x=50, y=150)

    def view_table_guest_screen(self):
        """Создание экрана просмотра таблицы для гостя."""
        self.clear_screen()

        tk.Label(self.root, text="Таблица пользователей", font=("Arial", 20)).place(x=50, y=50)

        # Текстовое поле для отображения данных
        text_area = tk.Text(self.root, font=("Arial", 14), wrap=tk.WORD, height=20, width=100)
        text_area.place(x=50, y=100)

        # Получение данных из таблицы
        users = self.db_manager.get_all_users()
        for user in users:
            text_area.insert(tk.END, f"ID: {user[0]}, Username: {user[1]}, Role: {user[3]}, Full Name: {user[4]}, Email: {user[5]}, Phone: {user[6]}\n")

        text_area.config(state=tk.DISABLED)

        # Кнопка для поиска строки
        tk.Button(self.root, text="Поиск строки", command=self.search_row_guest_screen, font=("Arial", 16), width=20).place(x=50, y=500)
        tk.Button(self.root, text="Назад", command=self.create_guest_screen, font=("Arial", 16), width=10).place(x=50, y=550)

    def search_row_guest_screen(self):
        """Создание экрана поиска строки для гостя."""
        self.clear_screen()

        tk.Label(self.root, text="Поиск строки", font=("Arial", 20)).place(x=50, y=50)

        tk.Label(self.root, text="Введите поле для поиска (например, username):", font=("Arial", 16)).place(x=50, y=100)
        self.search_field = tk.Entry(self.root, font=("Arial", 16))
        self.search_field.place(x=50, y=150)

        tk.Label(self.root, text="Введите значение для поиска:", font=("Arial", 16)).place(x=50, y=200)
        self.search_value = tk.Entry(self.root, font=("Arial", 16))
        self.search_value.place(x=50, y=250)

        tk.Button(self.root, text="Найти", command=self.search_row_guest, font=("Arial", 16), width=10).place(x=50, y=300)
        tk.Button(self.root, text="Назад", command=self.view_table_guest_screen, font=("Arial", 16), width=10).place(x=200, y=300)

    def search_row_guest(self):
        """Поиск строки в таблице для гостя."""
        field = self.search_field.get()
        value = self.search_value.get()

        query = f"SELECT * FROM users WHERE {field} = %s;"
        try:
            self.db_manager.cursor.execute(query, (value,))
            result = self.db_manager.cursor.fetchall()

            self.clear_screen()
            tk.Label(self.root, text="Результаты поиска", font=("Arial", 20)).place(x=50, y=50)

            text_area = tk.Text(self.root, font=("Arial", 14), wrap=tk.WORD, height=20, width=100)
            text_area.place(x=50, y=100)

            for row in result:
                text_area.insert(tk.END, f"ID: {row[0]}, Username: {row[1]}, Role: {row[3]}, Full Name: {row[4]}, Email: {row[5]}, Phone: {row[6]}\n")

            text_area.config(state=tk.DISABLED)

            tk.Button(self.root, text="Назад", command=self.view_table_guest_screen, font=("Arial", 16), width=10).place(x=50, y=550)
        except Exception as e:
            messagebox.showerror("Ошибка", f"Ошибка поиска: {e}")

    def clear_screen(self):
        """Очистка экрана."""
        for widget in self.root.winfo_children():
            widget.destroy()

    def login(self):
        """Обработка входа пользователя."""
        username = self.username_entry.get()
        password = self.password_entry.get()

        role = self.db_manager.authenticate_user(username, password)
        if role:
            self.current_user_role = role
            self.current_user_username = username
            messagebox.showinfo("Успех", f"Добро пожаловать, {username}!")
            if role == "Administrator":
                self.create_admin_screen()
            elif role == "Guest":
                self.create_guest_screen()
        else:
            messagebox.showerror("Ошибка", "Неверный логин или пароль.")

    def create_admin_screen(self):
        """Создание экрана администратора."""
        self.clear_screen()
        tk.Label(self.root, text="Окно администратора", font=("Arial", 20)).place(x=50, y=50)
        tk.Button(self.root, text="Посмотреть таблицу", command=self.view_table_screen, font=("Arial", 16), width=20).place(x=50, y=100)
        tk.Button(self.root, text="Создать базу данных", command=self.create_database_gui, font=("Arial", 16), width=20).place(x=50, y=150)
        tk.Button(self.root, text="Удалить базу данных", command=self.delete_database_gui, font=("Arial", 16), width=20).place(x=50, y=200)
        tk.Button(self.root, text="Создать роли", command=self.create_roles_gui, font=("Arial", 16), width=20).place( x=50, y=250)
        tk.Button(self.root, text="Назад", command=self.create_login_screen, font=("Arial", 16), width=10).place(x=50, y=300)

    def create_roles_gui(self):
        """Вызов создания ролей из GUI."""
        confirmation = messagebox.askyesno("Подтверждение", "Вы уверены, что хотите создать роли?")
        if confirmation:
            self.db_manager.create_database_roles()
            messagebox.showinfo("Успех", "Роли успешно созданы.")

    def clear_table_gui(self):
        """Вызов очистки таблицы из GUI."""
        confirmation = messagebox.askyesno("Подтверждение", "Вы уверены, что хотите очистить таблицу? Все данные будут удалены.")
        if confirmation:
            self.db_manager.clear_users_table()
            messagebox.showinfo("Успех", "Таблица успешно очищена.")
            self.view_table_screen()  # Обновляем экран просмотра таблицы

    def create_database_and_table_gui(self):
        """Вызов создания базы данных и таблицы из GUI."""
        self.db_manager.create_database_and_table()
        messagebox.showinfo("Успех", "База данных и таблица успешно созданы.")

    def view_table_screen(self):
        """Создание экрана просмотра таблицы."""
        self.clear_screen()

        tk.Label(self.root, text="Таблица пользователей", font=("Arial", 20)).place(x=50, y=50)

        # Создание таблицы (Treeview)
        columns = ("ID", "Username", "Role", "Full Name", "Email", "Phone")
        self.tree = ttk.Treeview(self.root, columns=columns, show="headings", height=20)
        self.tree.place(x=50, y=100)

        # Настройка заголовков столбцов
        for col in columns:
            self.tree.heading(col, text=col)
            self.tree.column(col, width=150, anchor="center")

        # Заполнение таблицы данными
        users = self.db_manager.get_all_users()
        for user in users:
            self.tree.insert("", "end", values=(user[0], user[1], user[3], user[4], user[5], user[6]))

        # Кнопки для управления данными
        tk.Button(self.root, text="Добавить строку", command=self.add_row_screen, font=("Arial", 16), width=20).place(x=50, y=500)
        tk.Button(self.root, text="Удалить строку", command=self.delete_row_screen, font=("Arial", 16), width=20).place(x=300, y=500)
        tk.Button(self.root, text="Поиск строки", command=self.search_row_screen, font=("Arial", 16), width=20).place(x=550, y=500)
        tk.Button(self.root, text="Обновить строку", command=self.update_row_screen, font=("Arial", 16), width=20).place(x=800, y=500)
        tk.Button(self.root, text="Назад", command=self.create_admin_screen, font=("Arial", 16), width=10).place(x=50, y=550)
        tk.Button(self.root, text="Обновить столбец", command=self.update_column_screen, font=("Arial", 16), width=20).place(x=1050, y=500)

    def add_row_screen(self):
        """Создание экрана добавления строки."""
        self.clear_screen()

        tk.Label(self.root, text="Добавление строки", font=("Arial", 20)).place(x=50, y=50)

        tk.Label(self.root, text="Имя пользователя:", font=("Arial", 16)).place(x=50, y=100)
        self.new_username = tk.Entry(self.root, font=("Arial", 16))
        self.new_username.place(x=250, y=100)

        tk.Label(self.root, text="Пароль:", font=("Arial", 16)).place(x=50, y=150)
        self.new_password = tk.Entry(self.root, font=("Arial", 16))
        self.new_password.place(x=250, y=150)

        tk.Label(self.root, text="Роль:", font=("Arial", 16)).place(x=50, y=200)
        self.new_role = tk.Entry(self.root, font=("Arial", 16))
        self.new_role.place(x=250, y=200)

        tk.Label(self.root, text="Полное имя:", font=("Arial", 16)).place(x=50, y=250)
        self.new_fullname = tk.Entry(self.root, font=("Arial", 16))
        self.new_fullname.place(x=250, y=250)

        tk.Label(self.root, text="Email:", font=("Arial", 16)).place(x=50, y=300)
        self.new_email = tk.Entry(self.root, font=("Arial", 16))
        self.new_email.place(x=250, y=300)

        tk.Label(self.root, text="Телефон:", font=("Arial", 16)).place(x=50, y=350)
        self.new_phonenumber = tk.Entry(self.root, font=("Arial", 16))
        self.new_phonenumber.place(x=250, y=350)

        tk.Button(self.root, text="Добавить", command=self.add_row, font=("Arial", 16), width=10).place(x=250, y=400)
        tk.Button(self.root, text="Назад", command=self.view_table_screen, font=("Arial", 16), width=10).place(x=400, y=400)

    def add_row(self):
        """Добавление строки в таблицу."""
        username = self.new_username.get()
        password = self.new_password.get()
        role = self.new_role.get()
        fullname = self.new_fullname.get()
        email = self.new_email.get()
        phonenumber = self.new_phonenumber.get()

        try:
            # Вызов метода добавления пользователя
            self.db_manager.add_user(username, password, role, fullname, email, phonenumber)
            messagebox.showinfo("Успех", "Строка успешно добавлена.")
            self.view_table_screen()  # Обновляем экран просмотра таблицы
        except Exception as e:
            messagebox.showerror("Ошибка", f"Ошибка добавления пользователя: {e}")

    def delete_row_screen(self):
        """Создание экрана удаления строки."""
        self.clear_screen()

        tk.Label(self.root, text="Удаление строки", font=("Arial", 20)).place(x=50, y=50)

        tk.Label(self.root, text="Введите ID пользователя для удаления:", font=("Arial", 16)).place(x=50, y=100)
        self.delete_user_id = tk.Entry(self.root, font=("Arial", 16))
        self.delete_user_id.place(x=50, y=150)

        tk.Button(self.root, text="Удалить", command=self.delete_row, font=("Arial", 16), width=10).place(x=50, y=200)
        tk.Button(self.root, text="Назад", command=self.view_table_screen, font=("Arial", 16), width=10).place(x=200, y=200)

    def delete_row(self):
        """Удаление строки из таблицы."""
        user_id = int(self.delete_user_id.get())
        self.db_manager.delete_user(user_id)
        messagebox.showinfo("Успех", "Строка успешно удалена.")
        self.view_table_screen()

    def search_row_screen(self):
        """Создание экрана поиска строки."""
        self.clear_screen()

        tk.Label(self.root, text="Поиск строки", font=("Arial", 20)).place(x=50, y=50)

        tk.Label(self.root, text="Введите поле для поиска (например, username):", font=("Arial", 16)).place(x=50, y=100)
        self.search_field = tk.Entry(self.root, font=("Arial", 16))
        self.search_field.place(x=50, y=150)

        tk.Label(self.root, text="Введите значение для поиска:", font=("Arial", 16)).place(x=50, y=200)
        self.search_value = tk.Entry(self.root, font=("Arial", 16))
        self.search_value.place(x=50, y=250)

        tk.Button(self.root, text="Найти", command=self.search_row, font=("Arial", 16), width=10).place(x=50, y=300)
        tk.Button(self.root, text="Назад", command=self.view_table_screen, font=("Arial", 16), width=10).place(x=200, y=300)

    def search_row(self):
        """Поиск строки в таблице."""
        field = self.search_field.get()
        value = self.search_value.get()

        query = f"SELECT * FROM users WHERE {field} = %s;"
        try:
            self.db_manager.cursor.execute(query, (value,))
            result = self.db_manager.cursor.fetchall()

            self.clear_screen()
            tk.Label(self.root, text="Результаты поиска", font=("Arial", 20)).place(x=50, y=50)

            text_area = tk.Text(self.root, font=("Arial", 14), wrap=tk.WORD, height=20, width=100)
            text_area.place(x=50, y=100)

            for row in result:
                text_area.insert(tk.END, f"ID: {row[0]}, Username: {row[1]}, Role: {row[3]}, Full Name: {row[4]}, Email: {row[5]}, Phone: {row[6]}\n")

            text_area.config(state=tk.DISABLED)

            tk.Button(self.root, text="Назад", command=self.view_table_screen, font=("Arial", 16), width=10).place(x=50, y=550)
        except Exception as e:
            messagebox.showerror("Ошибка", f"Ошибка поиска: {e}")

    def update_row_screen(self):
        """Создание экрана обновления строки."""
        self.clear_screen()

        tk.Label(self.root, text="Обновление строки", font=("Arial", 20)).place(x=50, y=50)

        tk.Label(self.root, text="Введите ID пользователя для обновления:", font=("Arial", 16)).place(x=50, y=100)
        self.update_user_id = tk.Entry(self.root, font=("Arial", 16))
        self.update_user_id.place(x=50, y=150)

        tk.Label(self.root, text="Имя пользователя:", font=("Arial", 16)).place(x=50, y=200)
        self.update_username = tk.Entry(self.root, font=("Arial", 16))
        self.update_username.place(x=250, y=200)

        tk.Label(self.root, text="Пароль:", font=("Arial", 16)).place(x=50, y=250)
        self.update_password = tk.Entry(self.root, font=("Arial", 16))
        self.update_password.place(x=250, y=250)

        tk.Label(self.root, text="Роль:", font=("Arial", 16)).place(x=50, y=300)
        self.update_role = tk.Entry(self.root, font=("Arial", 16))
        self.update_role.place(x=250, y=300)

        tk.Label(self.root, text="Полное имя:", font=("Arial", 16)).place(x=50, y=350)
        self.update_fullname = tk.Entry(self.root, font=("Arial", 16))
        self.update_fullname.place(x=250, y=350)

        tk.Label(self.root, text="Email:", font=("Arial", 16)).place(x=50, y=400)
        self.update_email = tk.Entry(self.root, font=("Arial", 16))
        self.update_email.place(x=250, y=400)

        tk.Label(self.root, text="Телефон:", font=("Arial", 16)).place(x=50, y=450)
        self.update_phonenumber = tk.Entry(self.root, font=("Arial", 16))
        self.update_phonenumber.place(x=250, y=450)

        tk.Button(self.root, text="Обновить", command=self.update_row, font=("Arial", 16), width=10).place(x=250, y=500)
        tk.Button(self.root, text="Назад", command=self.view_table_screen, font=("Arial", 16), width=10).place(x=400, y=500)

    def update_column_screen(self):
        """Создание экрана обновления одного столбца."""
        self.clear_screen()

        tk.Label(self.root, text="Обновление столбца", font=("Arial", 20)).place(x=50, y=50)

        tk.Label(self.root, text="Введите ID пользователя:", font=("Arial", 16)).place(x=50, y=100)
        self.update_user_id = tk.Entry(self.root, font=("Arial", 16))
        self.update_user_id.place(x=50, y=150)

        tk.Label(self.root, text="Введите имя столбца (например, username):", font=("Arial", 16)).place(x=50, y=200)
        self.column_name = tk.Entry(self.root, font=("Arial", 16))
        self.column_name.place(x=50, y=250)

        tk.Label(self.root, text="Введите новое значение:", font=("Arial", 16)).place(x=50, y=300)
        self.new_value = tk.Entry(self.root, font=("Arial", 16))
        self.new_value.place(x=50, y=350)

        tk.Button(self.root, text="Обновить", command=self.update_column, font=("Arial", 16), width=10).place(x=50, y=400)
        tk.Button(self.root, text="Назад", command=self.view_table_screen, font=("Arial", 16), width=10).place(x=200, y=400)

    def update_column(self):
        """Обновление одного столбца в таблице."""
        user_id = int(self.update_user_id.get())
        column_name = self.column_name.get()
        new_value = self.new_value.get()

        try:
            # Вызов метода обновления столбца
            self.db_manager.update_user_column(user_id, column_name, new_value)
            messagebox.showinfo("Успех", f"Столбец {column_name} успешно обновлен.")
            self.view_table_screen()  # Обновляем экран просмотра таблицы
        except Exception as e:
            messagebox.showerror("Ошибка", f"Ошибка обновления столбца: {e}")

    def update_row(self):
        """Обновление строки в таблице."""
        user_id = int(self.update_user_id.get())
        username = self.update_username.get()
        password = self.update_password.get()
        role = self.update_role.get()
        fullname = self.update_fullname.get()
        email = self.update_email.get()
        phonenumber = self.update_phonenumber.get()

        self.db_manager.update_user(user_id, username, password, role, fullname, email, phonenumber)
        messagebox.showinfo("Успех", "Строка успешно обновлена.")
        self.view_table_screen()

    def create_database_gui(self):
        """Вызов создания базы данных из GUI."""
        confirmation = messagebox.askyesno("Подтверждение", "Вы уверены, что хотите создать базу данных?")
        if confirmation:
            self.db_manager.create_database()
            messagebox.showinfo("Успех", "База данных успешно создана.")

    def delete_database_gui(self):
        """Вызов удаления базы данных из GUI."""
        confirmation = messagebox.askyesno("Подтверждение",
                                           "Вы уверены, что хотите удалить базу данных? Все данные будут потеряны.")
        if confirmation:
            self.db_manager.delete_database()
            messagebox.showinfo("Успех", "База данных успешно удалена.")

    def clear_screen(self):
        """Очистка экрана."""
        for widget in self.root.winfo_children():
            widget.destroy()

if __name__ == "__main__":
    root = tk.Tk()
    app = KartingCenterApp(root)
    root.mainloop()