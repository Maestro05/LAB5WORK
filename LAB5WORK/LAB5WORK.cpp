#include <iostream>
#include <vector>
#include <string>
#include <stdexcept> // Для исключений

using namespace std;

// Базовый класс для всех элементов меню
class MenuItem {
public:
    string name;    // Название блюда
    double price;   // Цена блюда

    MenuItem(const string& name, double price)
        : name(name), price(price) {}

    // Конструктор копирования
    MenuItem(const MenuItem& other)
        : name(other.name), price(other.price) {}

    // Перегрузка оператора присваивания
    MenuItem& operator=(const MenuItem& other) {
        if (this == &other) {  // Проверка на самоприсваивание
            return *this;
        }
        name = other.name;
        price = other.price;
        return *this;
    }

    // Перегрузка оператора сравнения
    bool operator==(const MenuItem& other) const {
        return name == other.name && price == other.price;
    }

    // Метод для отображения информации
    virtual void display() const {
        cout << name << " - " << price << " руб.\n";
    }

    virtual ~MenuItem() {}

    // Дружественная функция для доступа к приватным данным
    friend void printMenuItemDetails(const MenuItem& item);
};

// Дружественная функция для доступа к приватным данным
void printMenuItemDetails(const MenuItem& item) {
    cout << "Детали блюда: " << item.name << ", Цена: " << item.price << endl;
}

// Класс для главного блюда
class MainDish : public MenuItem {
public:
    MainDish(const string& name, double price)
        : MenuItem(name, price) {}

    void display() const override {
        cout << "[Главное блюдо] ";
        MenuItem::display();
    }
};

// Класс для закусок
class Appetizer : public MenuItem {
public:
    Appetizer(const string& name, double price)
        : MenuItem(name, price) {}

    void display() const override {
        cout << "[Закуска] ";
        MenuItem::display();
    }
};

// Класс для напитков
class Drink : public MenuItem {
public:
    Drink(const string& name, double price)
        : MenuItem(name, price) {}

    void display() const override {
        cout << "[Напиток] ";
        MenuItem::display();
    }
};

// Класс для десертов
class Dessert : public MenuItem {
public:
    Dessert(const string& name, double price)
        : MenuItem(name, price) {}

    void display() const override {
        cout << "[Десерт] ";
        MenuItem::display();
    }
};

// Класс для обработки заказа
class Order {
public:
    vector<MenuItem*> items;  // Список заказанных позиций
    static int totalOrders;    // Статическое поле для подсчета общего количества заказов

    Order() {
        totalOrders++;  // Увеличиваем счетчик заказов при создании нового заказа
    }

    // Добавить элемент в заказ
    void addItem(MenuItem* item) {
        items.push_back(item);
    }

    // Вывести заказ
    void displayOrder() const {
        double total = 0;
        cout << "\nВаш заказ:\n";
        for (const auto& item : items) {
            item->display();
            total += item->price;
        }
        cout << "Общая сумма: " << total << " руб.\n";
    }

    // Статический метод для получения количества заказов
    static int getTotalOrders() {
        return totalOrders;
    }

    // Конструктор копирования
    Order(const Order& other) {
        totalOrders = other.totalOrders;  // Мы не копируем items, чтобы избежать дублирования
    }

    // Перегрузка оператора присваивания
    Order& operator=(const Order& other) {
        if (this == &other) {
            return *this;
        }
        totalOrders = other.totalOrders;
        return *this;
    }

    ~Order() {
        // Освобождаем память, если это необходимо
        for (auto item : items) {
            delete item;
        }
    }
};

// Инициализация статического поля
int Order::totalOrders = 0;

// Функции отображения меню
void displayMenu() {
    cout << "\nВыберите категорию меню:\n";
    cout << "1. Главное блюдо\n";
    cout << "2. Закуски\n";
    cout << "3. Напитки\n";
    cout << "4. Десерты\n";
    cout << "5. Завершить заказ\n";
    cout << "Введите номер категории: ";
}

void displayMainDishes() {
    cout << "\nГлавные блюда:\n";
    cout << "1. Борщ - 150 руб.\n";
    cout << "2. Стейк - 300 руб.\n";
    cout << "3. Пельмени - 180 руб.\n";
    cout << "4. Ризотто - 220 руб.\n";
}

void displayAppetizers() {
    cout << "\nЗакуски:\n";
    cout << "1. Салат Цезарь - 120 руб.\n";
    cout << "2. Оливье - 100 руб.\n";
    cout << "3. Блины с икрой - 150 руб.\n";
    cout << "4. Тосты с авокадо - 110 руб.\n";
}

void displayDrinks() {
    cout << "\nНапитки:\n";
    cout << "1. Кола - 50 руб.\n";
    cout << "2. Минеральная вода - 40 руб.\n";
    cout << "3. Сок апельсиновый - 70 руб.\n";
    cout << "4. Чай черный - 60 руб.\n";
}

void displayDesserts() {
    cout << "\nДесерты:\n";
    cout << "1. Торт Наполеон - 80 руб.\n";
    cout << "2. Мороженое - 60 руб.\n";
    cout << "3. Чизкейк - 120 руб.\n";
    cout << "4. Пирог с яблоками - 90 руб.\n";
}

int main() {
    setlocale(LC_ALL, "rus");

    // Создание объектов для меню
    MainDish* mainDishes[] = {
        new MainDish("Борщ", 150),
        new MainDish("Стейк", 300),
        new MainDish("Пельмени", 180),
        new MainDish("Ризотто", 220)
    };

    Appetizer* appetizers[] = {
        new Appetizer("Салат Цезарь", 120),
        new Appetizer("Оливье", 100),
        new Appetizer("Блины с икрой", 150),
        new Appetizer("Тосты с авокадо", 110)
    };

    Drink* drinks[] = {
        new Drink("Кола", 50),
        new Drink("Минеральная вода", 40),
        new Drink("Сок апельсиновый", 70),
        new Drink("Чай черный", 60)
    };

    Dessert* desserts[] = {
        new Dessert("Торт Наполеон", 80),
        new Dessert("Мороженое", 60),
        new Dessert("Чизкейк", 120),
        new Dessert("Пирог с яблоками", 90)
    };

    // Создание объекта заказа
    Order order;

    try {
        bool ordering = true;
        while (ordering) {
            displayMenu();

            int category;
            cin >> category;

            switch (category) {
            case 1: {
                displayMainDishes();
                int choice;
                cout << "Выберите главное блюдо (1-4): ";
                cin >> choice;
                if (choice >= 1 && choice <= 4) {
                    order.addItem(mainDishes[choice - 1]);
                }
                else {
                    throw invalid_argument("Некорректный выбор!");
                }
                break;
            }
            case 2: {
                displayAppetizers();
                int choice;
                cout << "Выберите закуску (1-4): ";
                cin >> choice;
                if (choice >= 1 && choice <= 4) {
                    order.addItem(appetizers[choice - 1]);
                }
                else {
                    throw invalid_argument("Некорректный выбор!");
                }
                break;
            }
            case 3: {
                displayDrinks();
                int choice;
                cout << "Выберите напиток (1-4): ";
                cin >> choice;
                if (choice >= 1 && choice <= 4) {
                    order.addItem(drinks[choice - 1]);
                }
                else {
                    throw invalid_argument("Некорректный выбор!");
                }
                break;
            }
            case 4: {
                displayDesserts();
                int choice;
                cout << "Выберите десерт (1-4): ";
                cin >> choice;
                if (choice >= 1 && choice <= 4) {
                    order.addItem(desserts[choice - 1]);
                }
                else {
                    throw invalid_argument("Некорректный выбор!");
                }
                break;
            }
            case 5:
                ordering = false;
                break;
            default:
                cout << "Некорректный выбор. Попробуйте снова.\n";
                break;
            }
        }

        order.displayOrder();

    }
    catch (const invalid_argument& e) {
        cout << "Ошибка: " << e.what() << endl;
    }

    cout << "Общее количество заказов: " << Order::getTotalOrders() << endl;

    return 0;
}
