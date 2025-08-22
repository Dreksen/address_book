#include <iostream>
#include "database.h"
#include <limits>

void showMenu() {
    std::cout << "\n--- АДРЕСНАЯ КНИГА ---\n";
    std::cout << "1. Добавить контакт\n";
    std::cout << "2. Показать все контакты\n";
    std::cout << "3. Выход\n";
    std::cout << "Выберите действие: ";
}

void addContactMenu(Database& db) {
    std::string first_name, last_name, phone, email, address;

    std::cout << "\nВведите имя: ";
    std::getline(std::cin >> std::ws, first_name);

    std::cout << "Введите фамилию: ";
    std::getline(std::cin >> std::ws, last_name);

    std::cout << "Введите телефон: ";
    std::getline(std::cin >> std::ws, phone);

    std::cout << "Введите email: ";
    std::getline(std::cin >> std::ws, email);

    std::cout << "Введите адрес: ";
    std::getline(std::cin >> std::ws, address);

    db.addContact(first_name, last_name, phone, email, address);
    std::cout << "Контакт успешно добавлен!\n";
}

int main() {
    Database db;
    int choice = 0;

    while(true) {
        showMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch(choice) {
            case 1:
                addContactMenu(db);
                break;
            case 2:
                db.viewContacts();
                break;
            case 3:
                std::cout << "Выход из программы...\n";
                return 0;
            default:
                std::cout << "Неверный выбор! Попробуйте снова.\n";
        }
    }
    return 0;
}
