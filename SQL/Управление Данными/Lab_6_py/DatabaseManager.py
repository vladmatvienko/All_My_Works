# DatabaseManager.py
import psycopg2

class DatabaseManager:
    def __init__(self, dbname="postgres", user="postgres", password="postgres", host="localhost", port="5432"):
        self.conn = psycopg2.connect(dbname=dbname, user=user, password=password, host=host, port=port)
        self.conn.autocommit = True
        self.cursor = self.conn.cursor()

    def authenticate_user(self, username, password):
        """Аутентификация пользователя."""
        try:
            self.cursor.callproc("authenticate_user", (username, password))
            result = self.cursor.fetchone()
            return result[0] if result else None
        except Exception as e:
            print(f"Ошибка аутентификации: {e}")
            return None

    def create_users_table(self):
        """Создание таблицы users."""
        try:
            self.cursor.execute("CALL create_users_table()")
            print("Таблица users успешно создана.")
        except Exception as e:
            print(f"Ошибка создания таблицы: {e}")

    def add_user(self, username, password, role, fullname, email, phonenumber):
        """Добавление нового пользователя."""
        try:
            self.cursor.execute(
                "CALL add_user(%s, %s, %s, %s, %s, %s)",
                (username, password, role, fullname, email, phonenumber)
            )
            print("Пользователь успешно добавлен.")
        except Exception as e:
            print(f"Ошибка добавления пользователя: {e}")

    def delete_user(self, user_id):
        """Удаление пользователя."""
        try:
            self.cursor.execute("CALL delete_user(%s)", (user_id,))
            print("Пользователь успешно удален.")
        except Exception as e:
            print(f"Ошибка удаления пользователя: {e}")

    def update_user(self, user_id, username, password, role, fullname, email, phonenumber):
        """Обновление данных пользователя."""
        try:
            self.cursor.execute(
                "CALL update_user(%s, %s, %s, %s, %s, %s, %s)",
                (user_id, username, password, role, fullname, email, phonenumber)
            )
            print("Данные пользователя успешно обновлены.")
        except Exception as e:
            print(f"Ошибка обновления пользователя: {e}")

    def update_user_column(self, user_id, column_name, new_value):
        """Обновление одного столбца в таблице users."""
        try:
            self.cursor.execute(
                "CALL update_user_column(%s, %s, %s)",
                (user_id, column_name, new_value)
            )
            print(f"Столбец {column_name} успешно обновлен.")
        except Exception as e:
            print(f"Ошибка обновления столбца: {e}")

    def get_all_users(self):
        """Получение всех пользователей."""
        try:
            self.cursor.execute("SELECT * FROM users;")
            return self.cursor.fetchall()
        except Exception as e:
            print(f"Ошибка получения данных: {e}")
            return []

    def clear_users_table(self):
        """Очистка таблицы users."""
        try:
            self.cursor.execute("CALL clear_users_table()")
            print("Таблица users успешно очищена.")
        except Exception as e:
            print(f"Ошибка очистки таблицы: {e}")

    def create_database_and_table(self):
        """Создание базы данных и таблицы users."""
        try:
            self.cursor.execute("CALL create_database_and_table()")
            print("База данных и таблица успешно созданы.")
        except Exception as e:
            print(f"Ошибка создания базы данных или таблицы: {e}")

    def create_database(self):
        """Создание базы данных."""
        try:
            self.cursor.execute("CALL create_database()")
            print("База данных успешно создана.")
        except Exception as e:
            print(f"Ошибка создания базы данных: {e}")

    def delete_database(self):
        """Удаление базы данных."""
        try:
            self.cursor.execute("CALL delete_database()")
            print("База данных успешно удалена.")
        except Exception as e:
            print(f"Ошибка удаления базы данных: {e}")

    def create_database_roles(self):
        """Создание ролей и пользователей в базе данных."""
        try:
            self.cursor.execute("""
                DO $$
                DECLARE
                    user_record RECORD;
                BEGIN
                    FOR user_record IN (SELECT username, password, db_role FROM users) LOOP
                        EXECUTE format('CREATE USER %I WITH PASSWORD %L', user_record.username, user_record.password);
                        EXECUTE format('GRANT %I TO %I', user_record.db_role, user_record.username);
                    END LOOP;
                END $$;
            """)
            print("Роли и пользователи успешно созданы.")
        except Exception as e:
            print(f"Ошибка создания ролей: {e}")

    def close_connection(self):
        """Закрытие соединения с базой данных."""
        self.cursor.close()
        self.conn.close()
