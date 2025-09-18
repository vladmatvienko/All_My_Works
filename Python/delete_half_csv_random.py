import pandas as pd
import random

# Загрузка данных из CSV
input_file = 'jokes.csv'  # замените на путь к вашему файлу
df = pd.read_csv(input_file)

# Проверяем, что в датасете есть строки
if len(df) == 0:
    raise ValueError("Файл пустой.")

# Определяем количество строк для удаления (половина)
n_to_remove = len(df) // 2

# Получаем случайные индексы строк, которые нужно удалить
indices_to_remove = random.sample(list(df.index), n_to_remove)

# Удаляем эти строки
df_cleaned = df.drop(indices_to_remove)

# Сохраняем результат в новый файл
output_file = 'jokes.csv'
df_cleaned.to_csv(output_file, index=False)

print(f"Удалено {n_to_remove} строк. Результат сохранён в '{output_file}'.")