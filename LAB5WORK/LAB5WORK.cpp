// LAB5WORK.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdlib>  // Для функций стандартного ввода
#include <stdexcept> // Для исключений
#include <ctime> // Для получения текущего года

class Author {
private:
    char name[100];
    char surname[100];
    char birthdate[11];

public:
    // Конструктор по умолчанию
    Author() {
        strcpy(name, "");
        strcpy(surname, "");
        strcpy(birthdate, "");
    }

    // Метод для ввода данных автора
    void input() {
        std::cout << "Введите имя автора: ";
        std::cin.getline(name, sizeof(name));
        std::cout << "Введите фамилию автора: ";
        std::cin.getline(surname, sizeof(surname));
        std::cout << "Введите дату рождения (DD.MM.YYYY): ";
        std::cin.getline(birthdate, sizeof(birthdate));
    }

    // Геттеры
    const char* getName() const { return name; }
    const char* getSurname() const { return surname; }
    const char* getBirthdate() const { return birthdate; }

    // Метод для вывода данных автора
    void print() const {
        std::cout << "Автор: " << name << " " << surname << ", Дата рождения: " << birthdate << std::endl;
    }
};

class Category {
private:
    char name[50];
    char description[200];

public:
    // Конструктор по умолчанию
    Category() {
        strcpy(name, "");
        strcpy(description, "");
    }

    // Метод для ввода данных категории
    void input() {
        std::cout << "Введите название категории: ";
        std::cin.getline(name, sizeof(name));
        std::cout << "Введите описание категории: ";
        std::cin.getline(description, sizeof(description));
    }

    // Геттеры
    const char* getName() const { return name; }
    const char* getDescription() const { return description; }

    // Метод для вывода данных категории
    void print() const {
        std::cout << "Категория: " << name << ", Описание: " << description << std::endl;
    }
};
class Reader {
private:
    char name[100];
    char surname[100];
    char cardNumber[20];

public:
    // Конструктор по умолчанию
    Reader() {
        strcpy(name, "");
        strcpy(surname, "");
        strcpy(cardNumber, "");
    }

    // Метод для ввода данных о читателе
    void input() {
        std::cout << "Введите имя читателя: ";
        std::cin.getline(name, sizeof(name));
        std::cout << "Введите фамилию читателя: ";
        std::cin.getline(surname, sizeof(surname));
        std::cout << "Введите номер читательского билета: ";
        std::cin.getline(cardNumber, sizeof(cardNumber));
    }

    // Методы доступа
    const char* getName() const { return name; }
    const char* getSurname() const { return surname; }
    const char* getCardNumber() const { return cardNumber; }

    // Метод для вывода данных о читателе
    void print() const {
        std::cout << "Читатель: " << name << " " << surname << ", Номер карты: " << cardNumber << std::endl;
    }
};

class BookIssue {
private:
    Book* book;
    Reader* reader;
    char issueDate[11];
    char dueDate[11];

public:
    // Конструктор
    BookIssue(Book* book, Reader* reader, const char* issueDate, const char* dueDate)
        : book(book), reader(reader) {
        strncpy(this->issueDate, issueDate, sizeof(this->issueDate) - 1);
        strncpy(this->dueDate, dueDate, sizeof(this->dueDate) - 1);
    }

    // Метод для вывода данных о выдаче книги
    void print() const {
        std::cout << "Выдача книги: " << std::endl;
        book->print();
        reader->print();
        std::cout << "Дата выдачи: " << issueDate << ", Срок возврата: " << dueDate << std::endl;
    }
};

int main()
{
    setlocale(LC_ALL, "rus");
}

