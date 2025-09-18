import pandas as pd

def csv_to_xlsx(csv_file, xlsx_file):
    # Чтение CSV-файла
    df = pd.read_csv(csv_file, delimiter=',')  # можно изменить разделитель при необходимости

    # Сохранение в формате XLSX
    df.to_excel(xlsx_file, index=False, engine='openpyxl')
    print(f"Файл успешно сохранён как {xlsx_file}")

# Пример использования
if __name__ == "__main__":
    csv_file = 'Табличка.csv'      # замените на путь к вашему CSV-файлу
    xlsx_file = 'Табличка.xlsx'   # имя выходного файла Excel

    csv_to_xlsx(csv_file, xlsx_file)