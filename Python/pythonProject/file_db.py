import os
import shutil

class FileDatabase:
    def __init__(self, filepath):
        self.filepath = filepath

    def create_db(self):
        if not os.path.exists(self.filepath):
            open(self.filepath, 'w').close()

    def open_db(self):
        if not os.path.exists(self.filepath):
            raise FileNotFoundError("Database does not exist.")

    def add_record(self, record):
        with open(self.filepath, 'r') as file:
            for line in file:
                if line.startswith(record.split(',')[0]):  # Проверка уникальности ID
                    raise ValueError("Duplicate key found.")
        with open(self.filepath, 'a') as file:
            file.write(record + '\n')

    def delete_record(self, key, field_index=0):
        temp_filepath = self.filepath + '.tmp'
        with open(self.filepath, 'r') as file, open(temp_filepath, 'w') as temp_file:
            for line in file:
                fields = line.strip().split(',')
                if fields[field_index] != key:
                    temp_file.write(line)
        os.replace(temp_filepath, self.filepath)

    def search(self, value, field_index=0):
        results = []
        with open(self.filepath, 'r') as file:
            for line in file:
                fields = line.strip().split(',')
                if fields[field_index] == value:
                    results.append(line.strip())
        return results

    def backup(self, backup_path):
        shutil.copy(self.filepath, backup_path)

    def restore(self, backup_path):
        shutil.copy(backup_path, self.filepath)
