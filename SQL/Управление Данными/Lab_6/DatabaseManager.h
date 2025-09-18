#ifndef DATABASEMANAGER_H
#define DATABASEMANAGER_H

#include <string>

class DatabaseManager {
public:
    DatabaseManager();
    ~DatabaseManager();

    bool connectToDatabase(const std::string& dbname, const std::string& user, const std::string& password);
    void createUsersTable();
    void addInitialUsers();
    std::string authenticateUser(const std::string& username, const std::string& password);
    void clearUsersTable();

private:
    void* conn; // Указатель на соединение с базой данных
};

#endif // DATABASEMANAGER_H