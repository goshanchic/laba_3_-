#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Структура для хранения информации о книге
struct Book {
    string title;
    string author;
    int year;
};

// Функция для добавления книги в файл
void addBookToFile() {
    ofstream file("E:\\projekt C++\\3 labe oop\\ConsoleApplication1\\books.txt", ios::app);
    if (!file) {
        cerr << "Ошибка открытия файла!" << endl;
        return;
    }

    while (true) {
        Book book;
        cout << "Введите название книги (или оставьте пустым, чтобы завершить): ";
        getline(cin, book.title);
        if (book.title.empty()) break;

        cout << "Введите автора книги: ";
        getline(cin, book.author);

        cout << "Введите год выпуска книги: ";
        cin >> book.year;
        cin.ignore();

        file << book.title << "|" << book.author << "|" << book.year << endl;
    }
    file.close();
}

// Функция для чтения книг из файла
vector<Book> readBooksFromFile() {
    ifstream file("E:\\projekt C++\\3 labe oop\\ConsoleApplication1\\books.txt");
    vector<Book> books;
    if (!file) {
        cerr << "Ошибка открытия файла!" << endl;
        return books;
    }

    string line;
    while (getline(file, line)) {
        size_t pos1 = line.find('|');
        size_t pos2 = line.rfind('|');
        if (pos1 == string::npos || pos2 == string::npos || pos1 == pos2) continue;

        Book book;
        book.title = line.substr(0, pos1);
        book.author = line.substr(pos1 + 1, pos2 - pos1 - 1);
        book.year = stoi(line.substr(pos2 + 1));
        books.push_back(book);
    }
    file.close();
    return books;
}

// Функция для поиска книги по названию
void searchBook() {
    cout << "Введите название книги для поиска: ";
    string title;
    getline(cin, title);

    vector<Book> books = readBooksFromFile();
    ofstream output("output.txt", ios::app);
    for (const auto& book : books) {
        if (book.title == title) {
            cout << "Найдено: " << book.title << " автор " << book.author << " (" << book.year << ")\n";
            output << "Найдено: " << book.title << " автор " << book.author << " (" << book.year << ")\n";
            return;
        }
    }
    cout << "Книга не найдена.\n";
    output << "Книга не найдена.\n";
    output.close();
}

// Функция для сортировки книг
void sortBooks() {
    cout << "Сортировать по (1) Автору или (2) Году выпуска? Введите 1 или 2: ";
    int choice;
    cin >> choice;
    cin.ignore();

    vector<Book> books = readBooksFromFile();

    if (choice == 1) {
        sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
            return a.author < b.author;
            });
    }
    else if (choice == 2) {
        sort(books.begin(), books.end(), [](const Book& a, const Book& b) {
            return a.year < b.year;
            });
    }
    else {
        cout << "Неверный выбор.\n";
        return;
    }

    ofstream file("E:\\projekt C++\\3 labe oop\\ConsoleApplication1\\books.txt");
    ofstream output("output.txt", ios::app);
    for (const auto& book : books) {
        file << book.title << "|" << book.author << "|" << book.year << endl;
        output << book.title << "|" << book.author << "|" << book.year << endl;
    }
    file.close();
    output.close();
    cout << "Книги отсортированы и сохранены.\n";
}

// Функция для фильтрации книг по году выпуска
void filterBooksByYear() {
    cout << "Введите год: ";
    int year;
    cin >> year;
    cin.ignore();

    vector<Book> books = readBooksFromFile();
    ofstream output("output.txt", ios::app);

    for (const auto& book : books) {
        if (book.year <= year) {
            cout << book.title << " автор " << book.author << " (" << book.year << ")\n";
            output << book.title << " автор " << book.author << " (" << book.year << ")\n";
        }
    }
    output.close();
}

// Функция для отображения меню
void displayMenu() {
    while (true) {
        cout << "\nМеню:\n";
        cout << "1. Добавить книгу\n";
        cout << "2. Найти книгу\n";
        cout << "3. Отсортировать книги\n";
        cout << "4. Показать книги до заданного года\n";
        cout << "5. Выход\n";
        cout << "Введите ваш выбор: ";

        int choice;
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            addBookToFile();
            break;
        case 2:
            searchBook();
            break;
        case 3:
            sortBooks();
            break;
        case 4:
            filterBooksByYear();
            break;
        case 5:
            return;
        default:
            cout << "Неверный выбор. Попробуйте еще раз.\n";
        }
    }
}

// Главная функция
int main() {
    displayMenu();
    return 0;
}
