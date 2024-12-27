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

class Book {
private:
    char title[200];
    Author author;
    Category category;
    int year;
    int copiesAvailable;
    static int bookCount;  // Статическое поле для подсчета книг

public:
    // Конструктор по умолчанию
    Book() : year(0), copiesAvailable(0) {
        strcpy(title, "");
    }

    // Статический метод для получения общего количества книг
    static int getBookCount() {
        return bookCount;
    }

    // Метод для ввода данных о книге
    void input() {
        std::cout << "Введите название книги: ";
        std::cin.getline(title, sizeof(title));

        author.input();
        category.input();

        std::cout << "Введите год издания: ";
        std::cin >> year;
        std::cout << "Введите количество доступных копий: ";
        std::cin >> copiesAvailable;
        std::cin.ignore();  // Очищаем буфер после ввода чисел

        // Используем this для доступа к полям объекта
        this->validateYear(); // Проверка года
    }

    // Метод для проверки года издания
    void validateYear() {
        int currentYear = 2024; // Текущий год, его можно динамически получить через <ctime>
        try {
            if (year < 1000 || year > currentYear) {
                throw std::invalid_argument("Неверный год издания! Год должен быть между 1000 и текущим.");
            }
        }
        catch (const std::invalid_argument& e) {
            std::cout << "Ошибка: " << e.what() << std::endl;
        }
    }

    // Методы доступа
    const char* getTitle() const { return title; }
    const Author& getAuthor() const { return author; }
    const Category& getCategory() const { return category; }
    int getYear() const { return year; }
    int getCopiesAvailable() const { return copiesAvailable; }

    // Метод для уменьшения количества доступных экземпляров
    void decreaseCopies() {
        if (copiesAvailable > 0) {
            --copiesAvailable;
        }
    }

    // Метод для увеличения количества доступных экземпляров
    void increaseCopies() {
        ++copiesAvailable;
    }

    // Метод для вывода информации о книге
    void print() const {
        std::cout << "Книга: " << title << ", Год: " << year << ", Доступных копий: " << copiesAvailable << std::endl;
        author.print();
        category.print();
    }

    // Статический метод, который увеличивает счетчик книг
    static void increaseBookCount() {
        ++bookCount;
    }

    // Деструктор для уменьшения количества книг
    ~Book() {
        --bookCount;
    }
};

// Инициализация статического поля
int Book::bookCount = 0;

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

