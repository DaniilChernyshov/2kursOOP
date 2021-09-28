// BooksDB.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <windows.h>
#include <string>

using namespace std;
class CharacterDirectory {
public:
    string name, surname;
    string alias;
    string mentionedIn;
    int dayOfBirth, monthOfBirth, yearOfBirth;
    int role;
    int id;

    void read() {
        cout << "  Name: ";
        std::cin.ignore();
        std::getline(std::cin, name);
        cout << "  Surname: ";
        std::getline(std::cin, surname);
        cout << "  Alias: ";
        std::getline(std::cin, alias);
        cout << "  Books character was mentioned in: ";
        std::getline(std::cin, mentionedIn);
        cout << "  Role (1 - Main, 2 - Secondary, 3 - Episode: ";
        cin >> role;
    }

    void print() {
        cout << "  Name: " << name << endl;
        cout << "  Surname: " << surname << endl;
        cout << "  Alias: " << alias << endl;
        cout << "  Books character was mentioned in: " << mentionedIn << endl;
        cout << "  Role: " << role << endl;
    }

    void readBooksMentionedIn() {
        cout << "  Books character was mentioned in: ";
        cin >> mentionedIn;
    }

    void readRole() {
        cout << "  Role: ";
        cin >> role;
    }
};

class BooksDirectory {
public:
    string name, author;
    string description;
    int dayOfRelease, monthOfRelease, yearOfRelease;
    int numberOfPages;
    int id;

    void read() {
        cout << "  Book name: ";
        std::cin.ignore();
        std::getline(std::cin, name);
        cout << "  Author: ";
        std::getline(std::cin, author);
        cout << "  Short description: ";
        std::getline(std::cin, description);
        cout << "  Date of release (DD.MM.YYYY): ";
        cin >> dayOfRelease >> monthOfRelease >> yearOfRelease;
        cout << "  Number of pages: ";
        cin >> numberOfPages;
    }

    void print() {
        cout << "  Book name: " << name << endl;
        cout << "  Author: " << author << endl;
        cout << "  Short description: " << description << endl;
        cout << "  Date of release (DD.MM.YYYY): " << dayOfRelease << ' ' << monthOfRelease << ' ' << yearOfRelease << endl;
        cout << "  Number of pages: " << numberOfPages << endl;
    }

    void readDescription() {
        cout << "  Description: ";
        cin >> description;
    }
    void readNumberOfPages() {
        cout << "  Insurance code: ";
        cin >> numberOfPages;
    }
};

class CharacterBase {
public:
    int id = 1;
    vector<CharacterDirectory> data;

    void add() {
        CharacterDirectory temp;
        temp.read();
        temp.id = id++;
        cout << "  ID: " << temp.id << endl;
        data.push_back(temp);
    }

    int search(int id) {
        for (int i = 0; i < data.size(); i++)
            if (data[i].id == id)
                return i;

        return -1;
    }

    void remove(int pos) {
        data.erase(data.begin() + pos);
    }

    void open(const string& filename)
    {
        fstream ifs;
        ifs.open(filename, fstream::in | fstream::binary);
        if (ifs.fail())
            return;
        while (ifs.peek() != -1)
        {
            CharacterDirectory character;
            std::getline(ifs, character.name);
            std::getline(ifs, character.surname);
            std::getline(ifs, character.alias);
            std::getline(ifs, character.mentionedIn);
            ifs.read((char*)&character.role, sizeof(character.role));
            //user.print();
            character.id = id++;
            data.push_back(character);
        }
    }

    void save(const string& filename)
    {
        fstream ofs;
        ofs.open(filename, fstream::out | fstream::binary);
        for (unsigned int i = 0; i < data.size(); ++i)
        {
            ofs << data[i].name << '\n';
            ofs << data[i].surname << '\n';
            ofs << data[i].alias << '\n';
            ofs << data[i].mentionedIn << '\n';
            ofs.write((char*)&data[i].role, sizeof(data[i].role));
        }
    }
};

class BookBase {
public:
    int id = 1;
    vector<BooksDirectory> data;

    void add() {
        BooksDirectory temp;
        temp.read();
        temp.id = id++;
        cout << "  ID: " << temp.id << endl;
        data.push_back(temp);
    }

    int search(int id) {
        for (int i = 0; i < data.size(); i++) {
            if (data[i].id == id) {
                return i;
            }
        }

        return -1;
    }

    void remove(int pos) {
        data.erase(data.begin() + pos);
    }

    void open(const string& filename)
    {
        fstream ifs;
        ifs.open(filename, fstream::in | fstream::binary);
        if (ifs.fail())
            return;
        while (ifs.peek() != -1)
        {
            BooksDirectory book;
            std::getline(ifs, book.name);
            std::getline(ifs, book.author);
            std::getline(ifs, book.description);
            ifs.read((char*)&book.dayOfRelease, sizeof(book.dayOfRelease));
            ifs.read((char*)&book.monthOfRelease, sizeof(book.monthOfRelease));
            ifs.read((char*)&book.yearOfRelease, sizeof(book.yearOfRelease));
            ifs.read((char*)&book.numberOfPages, sizeof(book.numberOfPages));
            book.id = id++;
            data.push_back(book);

        }
    }

    void save(const string& filename)
    {
        fstream of;
        of.open(filename, fstream::out | fstream::binary);
        for (unsigned int i = 0; i < data.size(); ++i)
        {
            of << data[i].name << '\n';
            of << data[i].author << '\n';
            of << data[i].description << '\n';
            of.write((char*)&data[i].dayOfRelease, sizeof(data[i].dayOfRelease));
            of.write((char*)&data[i].monthOfRelease, sizeof(data[i].monthOfRelease));
            of.write((char*)&data[i].yearOfRelease, sizeof(data[i].yearOfRelease));
            of.write((char*)&data[i].numberOfPages, sizeof(data[i].numberOfPages));
        }
    }
};

class CharacterInBookBase
{
public:
    vector<pair<int, int>> data;

    void addUserToNetwork(int character, int book)
    {
        data.push_back(make_pair(character, book));
    }

    void removeCharacter();

    void removeBook();
};

int main() {

    const string charDir = "Characters.dat";
    const string booksDir = "Books.dat";
    const string book_char = "char_book.txt";

    BookBase book_base;
    CharacterBase char_base;
    BookBase book_char_connection;

    book_char_connection.open(book_char);
    book_base.open(booksDir);
    char_base.open(charDir);

    int choice, option;
    bool exit = false;

    while (true) {
        cout << " Choose your operation:" << endl;
        cout << "~ (1) ADD_CHARACTER \n (2) ADD_BOOK \n (3) EDIT_BOOK \n (4) EDIT_CHARACTER \n (5) REMOVE_BOOK \n (6) REMOVE_CHARACTER \n (7) FIND_BOOK \n (8) FIND_CHARACTER \n (9) CHARACTER+BOOK CONNECTION \n (10) EXIT ~" << endl;
        cout << " \nOption: "; cin >> choice;

        switch (choice) {
        case 1: {
            char_base.add();
            break;
        }
        case 2: {
            book_base.add();
            break;
        }
        case 3: {
            cout << " Which data would you like to edit?" << endl;
            cout << " (1) Description (2) Number of pages" << endl;
            cout << "Option: "; cin >> option;

            switch (option) {
            case 1: {
                int id;
                cout << "  Book ID: "; cin >> id;
                int pos = book_base.search(id);

                if (pos != -1) {
                    book_base.data[pos].readDescription();
                    cout << "Data has been updated." << endl;
                }
                else
                    cout << "No book with such ID was found." << endl;

                break;
            }
            case 2: {
                int id;
                cout << "  Book ID: "; cin >> id;
                int pos = book_base.search(id);

                if (pos != -1)
                    book_base.data[pos].readNumberOfPages();
                else
                    cout << "No book with such ID was found." << endl;

                break;
            }
            }
            break;
        }
        case 4: {
            //
            //
        }
              break;
        case 5: {
            int id;
            cout << "  Book ID: "; cin >> id;
            int pos = book_base.search(id);

            if (pos != -1)
                book_base.remove(pos);
            else
                cout << "No book with such ID was found." << endl;
            break;
        }
        case 6: { // удаление пользователя и аккаунтов
            int id;
            cout << "  Character ID: "; cin >> id;
            int pos = char_base.search(id);
            if (pos != -1)
                char_base.remove(pos);
            else
                cout << "No character with such ID was found." << endl;
            break;
        }
        case 7: {
            int id;
            cout << "  Book ID: "; cin >> id;
            int pos = book_base.search(id);

            if (pos != -1)
                book_base.data[pos].print();
            else
                cout << "No book with such ID was found." << endl;
            break;
        }
        case 8: {
            int id;
            cout << "  Character ID:"; cin >> id;
            int pos = char_base.search(id);
            if (pos != -1)
                char_base.data[pos].print();
            else
                cout << "No character with such ID was found." << endl;

            break;
        }
        case 9: {
            int book_id;
            int char_id;
            cout << "  Book ID: "; cin >> book_id;
            int pos_book = book_base.search(book_id);
            cout << "  Character ID:  "; cin >> char_id;
            int pos_char = char_base.search(char_id);
            if (pos_book != -1 && pos_char != -1) {

                cout << "Connection was added to database." << endl;
                   fstream bookBase;
                   bookBase.open(book_char, fstream::in | fstream::out | fstream::app);
                   bookBase << "  Book ID =>>>>>>>>>>>> " << book_id << endl;
                   bookBase << "  Character ID =>>>>>>>>>>>>  " << char_id << endl;
                   bookBase << "//////////////////////////////////////////////" << endl;
                   bookBase.close();

            }
            else
                cout << "No character or book with such ID's were found." << endl;
            break;
        }

        case 10:
            exit = true;
            break;
        default:
            exit = true;
        }

        if (exit) {
            break;
        }

        cout << endl;
    }
    book_base.save(booksDir);
    char_base.save(charDir);
    return 0;
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
