#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include <cstdlib>  // Для функций стандартного ввода
#include <stdexcept> // Для исключений
#include <ctime> // Для получения текущего года
#include <string> // Для работы с std::string

class Author {
private:
    std::string name;
    std::string surname;
    std::string birthdate;

public:
    // Конструктор по умолчанию
    Author() : name(""), surname(""), birthdate("") {}

    // Метод для ввода данных автора
    void input() {
        std::cout << "Введите имя автора: ";
        std::getline(std::cin, name);
        std::cout << "Введите фамилию автора: ";
        std::getline(std::cin, surname);
        std::cout << "Введите дату рождения (DD.MM.YYYY): ";
        std::getline(std::cin, birthdate);
    }

    // Методы доступа
    const std::string& getName() const { return name; }
    const std::string& getSurname() const { return surname; }
    const std::string& getBirthdate() const { return birthdate; }

    // Метод для вывода данных автора
    void print() const {
        std::cout << "Автор: " << name << " " << surname << ", Дата рождения: " << birthdate << std::endl;
    }
};

// Дружественная функция для вывода имени автора
void printAuthorName(const Author& author) {
    std::cout << "Имя автора: " << author.getName() << std::endl;
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

    // Методы доступа
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
    static int bookCount;  // Статическое поле для подсчета книг

public:
    // Конструктор по умолчанию
    Book() : title(""), year(0), copiesAvailable(0) {}

    // Статический метод для получения общего количества книг
    static int getBookCount() {
        return bookCount;
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
    const std::string& getTitle() const { return title; }
    const Author& getAuthor() const { return author; }
    const Category& getCategory() const { return category; }
    int getYear() const { return year; }
    int getCopiesAvailable() const { return copiesAvailable; }

    // Метод для уменьшения количества доступных экземпляров
    void decreaseCopies() {
        std::cout << "Текущее количество копий: " << copiesAvailable << std::endl;
        if (copiesAvailable > 0) {
            --copiesAvailable;
            std::cout << "Копия успешно уменьшена. Осталось копий: " << copiesAvailable << std::endl;
        }
        else {
            throw std::out_of_range("Нет доступных экземпляров!");
        }
    }

    // Метод для увеличения количества доступных экземпляров
    void increaseCopies() {
        ++copiesAvailable;
        std::cout << "Копий увеличено. Осталось копий: " << copiesAvailable << std::endl;
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

    // Динамическое выделение памяти для книги
    Book* dynamicBook = new Book();
    dynamicBook->input();  // Вводим данные о книге
    Book::increaseBookCount(); // Увеличиваем счетчик книг

    // Динамическое выделение памяти для читателя
    Reader* dynamicReader = new Reader();
    dynamicReader->input();  // Вводим данные о читателе

    // Ввод данных о выдаче книги
    std::string issueDate, dueDate;
    std::cout << "Введите дату выдачи (DD.MM.YYYY): ";
    std::getline(std::cin, issueDate);
    std::cout << "Введите срок возврата (DD.MM.YYYY): ";
    std::getline(std::cin, dueDate);

    // Создание записи о выдаче книги
    BookIssue* issue = new BookIssue(dynamicBook, dynamicReader, issueDate, dueDate);
    issue->print();  // Выводим информацию о выдаче

    // Вывод общего количества книг
    std::cout << "Общее количество книг в системе: " << Book::getBookCount() << std::endl;

    // Попытка уменьшить количество копий
    try {
        dynamicBook->decreaseCopies();  // Попытка уменьшить копии на 1
    }
    catch (const std::out_of_range& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }

    // Освобождение памяти
    delete dynamicReader;
    delete dynamicBook;
    delete issue;

    return 0;
}
