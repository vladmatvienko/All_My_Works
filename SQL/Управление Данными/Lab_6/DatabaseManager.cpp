// DatabaseManager.cpp
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "C:/Program Files/PostgreSQL/17/include/libpq-fe.h"  // Библиотека PostgreSQL
#include "DatabaseManager.h"
#include <iostream>

DatabaseManager::DatabaseManager() : conn(nullptr) {}

DatabaseManager::~DatabaseManager() {
    if (conn) {
        PQfinish((PGconn*)conn); // Закрытие соединения
    }
}

bool DatabaseManager::connectToDatabase(const std::string& dbname, const std::string& user, const std::string& password) {
    std::string connInfo = "dbname=" + dbname + " user=" + user + " password=" + password;
    conn = PQconnectdb(connInfo.c_str());

    if (PQstatus((PGconn*)conn) != CONNECTION_OK) {
        std::cerr << "Connection to database failed: " << PQerrorMessage((PGconn*)conn) << std::endl;
        return false;
    }
    std::cout << "Connected to database successfully!" << std::endl;
    return true;
}

void DatabaseManager::createUsersTable() {
    const char* query = "CALL create_users_table();";
    PGresult* res = PQexec((PGconn*)conn, query);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Failed to create users table: " << PQerrorMessage((PGconn*)conn) << std::endl;
    } else {
        std::cout << "Users table created successfully!" << std::endl;
    }

    PQclear(res);
}

void DatabaseManager::addInitialUsers() {
    const char* query = "INSERT INTO users (username, password, role, fullname, email, phonenumber) "
                        "VALUES ('admin', 'admin123', 'Administrator', 'Admin User', 'admin@example.com', '1234567890'), "
                        "('guest', 'guest123', 'Guest', 'Guest User', 'guest@example.com', '0987654321');";
    PGresult* res = PQexec((PGconn*)conn, query);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Failed to add initial users: " << PQerrorMessage((PGconn*)conn) << std::endl;
    } else {
        std::cout << "Initial users added successfully!" << std::endl;
    }

    PQclear(res);
}

std::string DatabaseManager::authenticateUser(const std::string& username, const std::string& password) {
    std::string query = "SELECT * FROM authenticate_user('" + username + "', '" + password + "');";
    PGresult* res = PQexec((PGconn*)conn, query.c_str());

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        std::cerr << "Authentication failed: " << PQerrorMessage((PGconn*)conn) << std::endl;
        PQclear(res);
        return "";
    }

    if (PQntuples(res) == 0) {
        std::cerr << "Invalid username or password." << std::endl;
        PQclear(res);
        return "";
    }

    std::string role = PQgetvalue(res, 0, 0);
    PQclear(res);
    return role;
}

void DatabaseManager::clearUsersTable() {
    const char* query = "CALL clear_users_table();";
    PGresult* res = PQexec((PGconn*)conn, query);

    if (PQresultStatus(res) != PGRES_COMMAND_OK) {
        std::cerr << "Failed to clear users table: " << PQerrorMessage((PGconn*)conn) << std::endl;
    } else {
        std::cout << "Users table cleared successfully!" << std::endl;
    }

    PQclear(res);
}