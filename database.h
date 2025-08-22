#ifndef ADDRESS_BOOK_DATABASE_H
#define ADDRESS_BOOK_DATABASE_H

#include <sqlite3.h>
#include <string>

class Database {
private:
    sqlite3* db;
public:
    Database();
    ~Database();
    void createTable();
    void addContact(const std::string& first_name, const std::string& last_name,
                    const std::string& phone, const std::string& email, const std::string& address);
    void viewContacts();
};

#endif //ADDRESS_BOOK_DATABASE_H
