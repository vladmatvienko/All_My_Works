import tkinter as tk
from tkinter import filedialog, messagebox
import csv
from openpyxl import Workbook

def convert_csv_to_xlsx(csv_file, xlsx_file):
    try:
        # Создаем новую книгу Excel
        wb = Workbook()
        ws = wb.active

        # Читаем CSV и записываем данные в Excel
        with open(csv_file, 'r', encoding='utf-8') as file:
            reader = csv.reader(file)
            for row in reader:
                ws.append(row)

        # Сохраняем файл Excel
        wb.save(xlsx_file)
        return True
    except Exception as e:
        print(f"Ошибка: {e}")
        return False

def select_csv_file():
    file_path = filedialog.askopenfilename(
        title="Выберите CSV файл",
        filetypes=[("CSV files", "*.csv")]
    )
    if file_path:
        csv_entry.delete(0, tk.END)
        csv_entry.insert(0, file_path)

def save_xlsx_file():
    file_path = filedialog.asksaveasfilename(
        title="Сохранить как XLSX",
        defaultextension=".xlsx",
        filetypes=[("Excel files", "*.xlsx")]
    )
    if file_path:
        xlsx_entry.delete(0, tk.END)
        xlsx_entry.insert(0, file_path)

def convert_file():
    csv_file = csv_entry.get()
    xlsx_file = xlsx_entry.get()

    if not csv_file or not xlsx_file:
        messagebox.showwarning("Ошибка", "Укажите оба пути к файлам!")
        return

    success = convert_csv_to_xlsx(csv_file, xlsx_file)
    if success:
        messagebox.showinfo("Успех", "Конвертация завершена успешно!")
    else:
        messagebox.showerror("Ошибка", "Произошла ошибка при конвертации.")

# Создаем основное окно
root = tk.Tk()
root.title("Конвертер CSV в XLSX")
root.geometry("400x200")

# Метка и поле для CSV
tk.Label(root, text="CSV файл:").grid(row=0, column=0, padx=10, pady=10, sticky="e")
csv_entry = tk.Entry(root, width=40)
csv_entry.grid(row=0, column=1, padx=10, pady=10)
tk.Button(root, text="Обзор", command=select_csv_file).grid(row=0, column=2, padx=10, pady=10)

# Метка и поле для XLSX
tk.Label(root, text="XLSX файл:").grid(row=1, column=0, padx=10, pady=10, sticky="e")
xlsx_entry = tk.Entry(root, width=40)
xlsx_entry.grid(row=1, column=1, padx=10, pady=10)
tk.Button(root, text="Обзор", command=save_xlsx_file).grid(row=1, column=2, padx=10, pady=10)

# Кнопка конвертации
convert_button = tk.Button(root, text="Конвертировать", command=convert_file, bg="lightblue")
convert_button.grid(row=2, column=0, columnspan=3, pady=20)

# Запуск главного цикла
root.mainloop()