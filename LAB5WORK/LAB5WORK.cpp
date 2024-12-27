#include <iostream>
#include <string>  // Для std::string
#include <stdexcept> // Для исключений
#include <cstring> // Для strncpy

class Author {
private:
    std::string name;
    std::string surname;
    std::string birthdate;

public:
    // Конструктор по умолчанию
    Author() : name(""), surname(""), birthdate("") {}

    // Конструктор копирования
    Author(const Author& other) : name(other.name), surname(other.surname), birthdate(other.birthdate) {
        std::cout << "Конструктор копирования для автора: " << name << " " << surname << std::endl;
    }

    // Оператор присваивания
    Author& operator=(const Author& other) {
        if (this == &other) return *this; // Защита от самоприсваивания
        name = other.name;
        surname = other.surname;
        birthdate = other.birthdate;
        std::cout << "Оператор присваивания для автора: " << name << " " << surname << std::endl;
        return *this;
    }

    // Метод для ввода данных автора
    void input() {
        std::cout << "Введите имя автора: ";
        std::getline(std::cin, name);
        std::cout << "Введите фамилию автора: ";
        std::getline(std::cin, surname);
        std::cout << "Введите дату рождения (DD.MM.YYYY): ";
        std::getline(std::cin, birthdate);
    }

    // Метод для вывода данных автора
    void print() const {
        std::cout << "Автор: " << name << " " << surname << ", Дата рождения: " << birthdate << std::endl;
    }

    // Геттеры
    const std::string& getName() const { return name; }
    const std::string& getSurname() const { return surname; }
    const std::string& getBirthdate() const { return birthdate; }
};

// Дружественная функция для вывода имени автора
void printAuthorName(const Author& author) {
    std::cout << "Имя автора: " << author.getName() << std::endl;
}

class Book {
private:
    std::string title;
    Author author;
    int year;
    int copiesAvailable;
    static int bookCount;  // Статическое поле для подсчета книг

public:
    // Конструктор по умолчанию
    Book() : title(""), year(0), copiesAvailable(0) {}

    // Конструктор копирования
    Book(const Book& other) : title(other.title), author(other.author), year(other.year), copiesAvailable(other.copiesAvailable) {
        std::cout << "Конструктор копирования для книги: " << title << std::endl;
    }

    // Оператор присваивания
    Book& operator=(const Book& other) {
        if (this == &other) return *this; // Защита от самоприсваивания
        title = other.title;
        author = other.author;
        year = other.year;
        copiesAvailable = other.copiesAvailable;
        std::cout << "Оператор присваивания для книги: " << title << std::endl;
        return *this;
    }

    // Статический метод для подсчета книг
    static int getBookCount() {
        return bookCount;
    }

    // Статический метод для увеличения количества книг
    static void increaseBookCount() {
        ++bookCount;
    }

    // Метод для ввода данных о книге
    void input() {
        std::cout << "Введите название книги: ";
        std::getline(std::cin, title);
        author.input();
        std::cout << "Введите год издания: ";
        std::cin >> year;
        std::cout << "Введите количество доступных копий: ";
        std::cin >> copiesAvailable;
        std::cin.ignore();  // Очищаем буфер после ввода чисел
    }

    // Метод для вывода данных о книге
    void print() const {
        std::cout << "Книга: " << title << ", Год: " << year << ", Доступных копий: " << copiesAvailable << std::endl;
        author.print();
    }

    // Метод для уменьшения количества копий книги
    void decreaseCopies() {
        if (copiesAvailable > 0) {
            --copiesAvailable;
            std::cout << "Копия успешно уменьшена. Осталось копий: " << copiesAvailable << std::endl;
        }
        else {
            throw std::out_of_range("Нет доступных экземпляров!"); // Исключение, если копий нет
        }
    }

    // Геттеры
    int getCopiesAvailable() const { return copiesAvailable; }
};

int Book::bookCount = 0;

int main() {
    setlocale(LC_ALL, "Rus");

    // Динамическое выделение памяти для книги
    Book* dynamicBook1 = new Book();
    dynamicBook1->input();  // Вводим данные о первой книге
    Book::increaseBookCount(); // Увеличиваем счетчик книг

    // Создаем копию книги с использованием конструктора копирования
    Book* dynamicBook2 = new Book(*dynamicBook1);  // Конструктор копирования

    // Создаем еще один объект книги и используем оператор присваивания
    Book* dynamicBook3 = new Book();
    *dynamicBook3 = *dynamicBook1;  // Оператор присваивания

    // Выводим информацию о всех книгах
    std::cout << "\nИнформация о первой книге:\n";
    dynamicBook1->print();

    std::cout << "\nИнформация о второй книге (скопирована через конструктор копирования):\n";
    dynamicBook2->print();

    std::cout << "\nИнформация о третьей книге (присвоена через оператор присваивания):\n";
    dynamicBook3->print();

    // Демонстрация работы с методом decreaseCopies и обработки исключений
    try {
        std::cout << "\nПопытка уменьшить копии книги:\n";
        dynamicBook1->decreaseCopies();  // Уменьшаем количество копий на 1
        dynamicBook1->decreaseCopies();  // Еще раз уменьшаем количество копий
        dynamicBook1->decreaseCopies();  // Еще раз
        dynamicBook1->decreaseCopies();  // Еще раз
        dynamicBook1->decreaseCopies();  // Еще раз
        dynamicBook1->decreaseCopies();  // Ошибка, копий больше нет
    }
    catch (const std::out_of_range& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }

    // Вывод общего количества книг
    std::cout << "Общее количество книг в системе: " << Book::getBookCount() << std::endl;

    // Освобождение памяти
    delete dynamicBook1;
    delete dynamicBook2;
    delete dynamicBook3;

    return 0;
}
