#pragma once
#include "../CppLibrary/Menu.h" 
using std::istream; using std::ostream;

struct program4 {
private:
    struct date {
    public:
        long int day = 0;
        long int month = 0;
        long int year = 0;
        void getToday() {
            tm today;
            time_t now = time(0);
            localtime_s(&today, &now);
            day = today.tm_mday;
            month = today.tm_mon + 1;
            year = today.tm_year + 1900;
        };
    };

    struct person {
    public:
        date birthday;
        date age;
        string name;
        void update() {
            age.getToday();
            age.year -= birthday.year;
            age.month -= birthday.month;
            age.day -= birthday.day;
            if (age.month < 0) age.month += 12;
            if (age.day < 0) {
                if (age.month = 2) {
                    age.day += 31;
                }
            }
        };
        bool isYoungerThan(person comparable) {
            if (age.year < comparable.age.year)          return true;
            else if (age.month < comparable.age.month && age.year == comparable.age.year)    return true;
            else if (age.day < comparable.age.day && age.year == comparable.age.year && age.month == comparable.age.month)       return true;
            else                                        return false;
        };
        bool isOlderThan(person comparable) {
            if (age.year > comparable.age.year)          return true;
            else if (age.month > comparable.age.month && age.year == comparable.age.year)    return true;
            else if (age.day > comparable.age.day && age.year == comparable.age.year && age.month == comparable.age.month)       return true;
            else                                        return false;
        };
        friend istream& operator>> (istream& in, person& data) {// to read from file
            in >> data.name;
            in >> data.birthday.day;
            in >> data.birthday.month;
            in >> data.birthday.year;
            return in;
        };
        friend ostream& operator << (ostream& out, person& data) { // to write into a file
            out << data.name << " " << data.birthday.day << " " << data.birthday.month << " " << data.birthday.year << "\n";
            return out;
        };
    };

    struct memory {
    public:
        linkClass<person> people;
        fileManager<person> file;
        person oldest;
        person younger;
        int preTwenties = 0;
        int twenties = 0;
        int thirties = 0;
        void update() {
            if (people.first != nullptr) {
                linkClass<person>::nodeClass* cursor = people.first;
                people.first->data.update();
                oldest = people.first->data;
                younger = people.first->data;
                preTwenties = twenties = thirties = 0;
                while (cursor != nullptr)
                {
                    cursor->data.update();
                    if (cursor->data.age.year <= 20)                    preTwenties += 1;
                    else if (cursor->data.age.year <= 30)               twenties += 1;
                    else if (cursor->data.age.year > 30)                thirties += 1;
                    if (oldest.isYoungerThan(cursor->data))             oldest = cursor->data;
                    if (younger.isOlderThan(cursor->data))              younger = cursor->data;
                    cursor = cursor->next;
                }
            }
        };
    };

    memory data_memory;

    bool verify(person data) {
        // if its ferbuary
        if (data.birthday.day > 29 && data.birthday.month == 2)
            return true;
        // if the month have 31 days
        else if (data.birthday.day > 31 && (data.birthday.month == 3 || data.birthday.month == 6 || data.birthday.month == 9 || data.birthday.month == 11))
            return true;
        //if the month have 30 days
        else if (data.birthday.day > 30)
            return true;
        // if its out of value
        else return false;
    };

    void inputData() {
        person data_input;
        while (1) {
            cout << "\t ingrese el nombre del alumno : ";
            cin >> data_input.name;
            if (data_input.name.length() == 0) {
                cls();
                cout << "\t (ingrese un valor valido)";
            }
            else break;
        }
        while (1) {
            cout << "\t ingrese el anio de nacimiento: ";
            cin >> data_input.birthday.year;
            if (data_input.birthday.year < 1) {
                cls();
                cout << "\t (ingrese un valor valido)";
            }
            else break;
        }
        while (1) {
            cout << "\t ingrese el mes de nacimiento en numero: ";
            cin >> data_input.birthday.month;
            if (data_input.birthday.month < 1 || data_input.birthday.month > 12) {
                cls();
                cout << "\t (ingrese un valor valido)";
            }
            else break;
        }
        while (1) {
            cout << "\t ingrese el dia de nacimiento: ";
            cin >> data_input.birthday.day;
            if (data_input.birthday.day < 1 || verify(data_input)) {
                cls();
                cout << "\t (ingrese un valor valido)";
            }
            else break;
        }
        data_memory.people.addToEnd(data_input);
        data_memory.file.write(data_input);
    };
    void showData() {
        data_memory.update();
        linkClass<person>::nodeClass* cursor = data_memory.people.first;
        int i = 1;
        if (cursor != nullptr) {
            while (cursor != nullptr)
            {
                cout << i << ") " << "________________________________________" << "\n";
                cout << "\t nombre: " << cursor->data.name << "\n";
                cout << "\t fecha de nacimiento: " << cursor->data.birthday.day << "/" << cursor->data.birthday.month << "/" << cursor->data.birthday.year << " ";
                cout << "\n\t desde que nacio: \n";
                cout << "\t\t\t " << cursor->data.age.year << " anios" << "\n";
                cout << "\t\t\t " << cursor->data.age.month << " meses" << "\n";
                cout << "\t\t\t " << cursor->data.age.day << " dias" << "\n";
                cursor = cursor->next;
                i += 1;
            }
            cout << "__________________________________________" << "\n";
            cout << "\t el mas viejo es: " << data_memory.oldest.name << " con " << data_memory.oldest.age.year << " anios" << "\n";
            cout << "\t el mas joven es: " << data_memory.younger.name << " con " << data_memory.younger.age.year << " anios" << "\n";
            cout << "\t la contidad de personas con 20 o menos es de: " << data_memory.preTwenties << "\n";
            cout << "\t la contidad de personas con 21 hasta 30 es de: " << data_memory.twenties << "\n";
            cout << "\t la contidad de personas con 30 o mas es de: " << data_memory.thirties << "\n";
            pause();
        }
        else cout << "\t\t no hay datos ingresados";
    };
    void main() {
        data_memory.file.declare("datap3", "txt");
        data_memory.file.readToMemory();
        data_memory.people = data_memory.file.inMemoryFile;
        menuClass menu;
        const int menuOptions = 3;
        string menuTitle = "\n\t programa 3: ejercicio con una lista de fechas \n";
        string menuText[menuOptions + 1] = {
            "start",
            " Ingresar datos de persona",
            " ver resultados",
            "end"
        };
        menu.declare(menuOptions, 1, menuTitle);
        menu.menu(menuText);
        while (menu.w != menu.exit) {
            menu.menu(menuText);
            switch (menu.w)
            {
            case 1:
                inputData();
                break;
            case 2:
                showData();
                break;
            case menuOptions:
                break;
            default:
                errormens();
                break;
            }
        }
    };
public:
    void run() {
        main();
    };
};