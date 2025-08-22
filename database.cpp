#include "database.h"
#include <iostream>

Database::Database() {
    int rc = sqlite3_open("address_book.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return;
    }
    createTable();
}

Database::~Database() {
    sqlite3_close(db);
}

void Database::createTable() {
    const char* sql = "CREATE TABLE IF NOT EXISTS contacts ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "first_name TEXT NOT NULL, "
                      "last_name TEXT NOT NULL, "
                      "phone TEXT, "
                      "email TEXT, "
                      "address TEXT);";

    char* errmsg;
    int rc = sqlite3_exec(db, sql, nullptr, nullptr, &errmsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errmsg << std::endl;
        sqlite3_free(errmsg);
    }
}

void Database::addContact(const std::string& first_name, const std::string& last_name,
                          const std::string& phone, const std::string& email, const std::string& address) {
    std::string query = "INSERT INTO contacts (first_name, last_name, phone, email, address) "
                        "VALUES ('" + first_name + "', '" + last_name + "', '" + phone + "', '" + email + "', '" + address + "');";

    char* errmsg;
    int rc = sqlite3_exec(db, query.c_str(), nullptr, nullptr, &errmsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errmsg << std::endl;
        sqlite3_free(errmsg);
    }
}

void Database::viewContacts() {
    sqlite3_stmt* stmt;
    const std::string query = "SELECT * FROM contacts ORDER BY last_name, first_name;";

    int rc = sqlite3_prepare_v2(db, query.c_str(), -1, &stmt, nullptr);
    if (rc != SQLITE_OK) {
        std::cerr << "Failed to prepare statement: " << sqlite3_errmsg(db) << std::endl;
        return;
    }

    bool hasRecords = false;
    std::cout << "\n--- СПИСОК КОНТАКТОВ ---\n";

    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
        hasRecords = true;

        int id = sqlite3_column_int(stmt, 0);
        const char* first_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 1));
        const char* last_name = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 2));
        const char* phone = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 3));
        const char* email = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 4));
        const char* address = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 5));

        std::cout << "ID: " << id << "\n"
                  << "Имя: " << (first_name ? first_name : "N/A") << "\n"
                  << "Фамилия: " << (last_name ? last_name : "N/A") << "\n"
                  << "Телефон: " << (phone ? phone : "N/A") << "\n"
                  << "Email: " << (email ? email : "N/A") << "\n"
                  << "Адрес: " << (address ? address : "N/A") << "\n"
                  << "-----------------------\n";
    }

    if (rc != SQLITE_DONE) {
        std::cerr << "Error reading contacts: " << sqlite3_errmsg(db) << std::endl;
    }

    if (!hasRecords) {
        std::cout << "Контакты не найдены\n";
    }

    sqlite3_finalize(stmt);
}
