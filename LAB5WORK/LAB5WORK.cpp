#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <string>  // Для работы с std::string

class Author {
private:
    std::string name;
    std::string surname;
    std::string birthdate;

public:
    // Конструктор по умолчанию
    Author() : name(""), surname(""), birthdate("") {}

    // Конструктор с параметрами
    Author(const std::string& name, const std::string& surname, const std::string& birthdate)
        : name(name), surname(surname), birthdate(birthdate) {}

    // Дружественная функция для доступа к приватным данным
    friend void printAuthorInfo(const Author& author);

    // Метод для ввода данных автора
    void input() {
        std::cout << "Введите имя автора: ";
        std::getline(std::cin, name);
        std::cout << "Введите фамилию автора: ";
        std::getline(std::cin, surname);
        std::cout << "Введите дату рождения (DD.MM.YYYY): ";
        std::getline(std::cin, birthdate);
    }

    // Геттеры
    const std::string& getName() const { return name; }
    const std::string& getSurname() const { return surname; }
    const std::string& getBirthdate() const { return birthdate; }

    // Перегрузка оператора сравнения
    bool operator==(const Author& other) const {
        return name == other.name && surname == other.surname && birthdate == other.birthdate;
    }

    // Метод для вывода данных автора
    void print() const {
        std::cout << "Автор: " << name << " " << surname << ", Дата рождения: " << birthdate << std::endl;
    }
};

void printAuthorInfo(const Author& author) {
    std::cout << "Дружеская функция: " << author.name << " " << author.surname << std::endl;
}

class Category {
private:
    std::string name;
    std::string description;

public:
    // Конструктор по умолчанию
    Category() : name(""), description("") {}

    // Метод для ввода данных категории
    void input() {
        std::cout << "Введите название категории: ";
        std::getline(std::cin, name);
        std::cout << "Введите описание категории: ";
        std::getline(std::cin, description);
    }

    // Геттеры
    const std::string& getName() const { return name; }
    const std::string& getDescription() const { return description; }

    // Метод для вывода данных категории
    void print() const {
        std::cout << "Категория: " << name << ", Описание: " << description << std::endl;
    }
};

class Book {
private:
    std::string title;
    Author author;
    Category category;
    int year;
    int copiesAvailable;

public:
    // Конструктор по умолчанию
    Book() : title(""), year(0), copiesAvailable(0) {}

    // Конструктор копии
    Book(const Book& other)
        : title(other.title), author(other.author), category(other.category), year(other.year), copiesAvailable(other.copiesAvailable) {}

    // Оператор присваивания
    Book& operator=(const Book& other) {
        if (this != &other) {
            title = other.title;
            author = other.author;
            category = other.category;
            year = other.year;
            copiesAvailable = other.copiesAvailable;
        }
        return *this;
    }

    // Метод для ввода данных о книге
    void input() {
        std::cout << "Введите название книги: ";
        std::getline(std::cin, title);

        author.input();
        category.input();

        std::cout << "Введите год издания: ";
        std::cin >> year;
        std::cout << "Введите количество доступных копий: ";
        std::cin >> copiesAvailable;
        std::cin.ignore();  // Очищаем буфер после ввода чисел
    }

    // Методы доступа
    const std::string& getTitle() const { return title; }
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

    // Перегрузка оператора вывода
    void print() const {
        std::cout << "Книга: " << title << ", Год: " << year << ", Доступных копий: " << copiesAvailable << std::endl;
        author.print();
        category.print();
    }
};

class Reader {
private:
    std::string name;
    std::string surname;
    std::string cardNumber;

public:
    // Конструктор по умолчанию
    Reader() : name(""), surname(""), cardNumber("") {}

    // Метод для ввода данных о читателе
    void input() {
        std::cout << "Введите имя читателя: ";
        std::getline(std::cin, name);
        std::cout << "Введите фамилию читателя: ";
        std::getline(std::cin, surname);
        std::cout << "Введите номер читательского билета: ";
        std::getline(std::cin, cardNumber);
    }

    // Методы доступа
    const std::string& getName() const { return name; }
    const std::string& getSurname() const { return surname; }
    const std::string& getCardNumber() const { return cardNumber; }

    // Метод для вывода данных о читателе
    void print() const {
        std::cout << "Читатель: " << name << " " << surname << ", Номер карты: " << cardNumber << std::endl;
    }
};

class BookIssue {
private:
    Book* book;
    Reader* reader;
    std::string issueDate;
    std::string dueDate;

public:
    // Конструктор
    BookIssue(Book* book, Reader* reader, const std::string& issueDate, const std::string& dueDate)
        : book(book), reader(reader), issueDate(issueDate), dueDate(dueDate) {}

    // Метод для вывода данных о выдаче книги
    void print() const {
        std::cout << "Выдача книги: " << std::endl;
        book->print();
        reader->print();
        std::cout << "Дата выдачи: " << issueDate << ", Срок возврата: " << dueDate << std::endl;
    }
};

int main() {
    setlocale(LC_ALL, "Rus");

    // Тест: Создаем книгу с данными
    Book* dynamicBook = new Book();
    dynamicBook->input();  // Вводим данные о книге

    // Тест: Создаем читателя с данными
    Reader* dynamicReader = new Reader();
    dynamicReader->input();  // Вводим данные о читателе

    // Тест: Ввод данных о выдаче книги
    std::string issueDate, dueDate;
    std::cout << "Введите дату выдачи (DD.MM.YYYY): ";
    std::getline(std::cin, issueDate);
    std::cout << "Введите срок возврата (DD.MM.YYYY): ";
    std::getline(std::cin, dueDate);

    // Создание записи о выдаче книги
    BookIssue* issue = new BookIssue(dynamicBook, dynamicReader, issueDate, dueDate);
    issue->print();  // Выводим информацию о выдаче

    // Тест: Конструктор копии и оператор присваивания
    Book* copiedBook = new Book(*dynamicBook);  // Используем конструктор копии
    copiedBook->print();

    Book anotherBook;
    anotherBook = *dynamicBook;  // Используем оператор присваивания
    anotherBook.print();

    // Дружественная функция для авторов
    printAuthorInfo(dynamicBook->getAuthor());

    // Освобождение памяти
    delete dynamicReader;
    delete dynamicBook;
    delete issue;
    delete copiedBook;

    return 0;
}
