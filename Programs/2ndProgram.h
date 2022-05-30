#pragma once
#include "../CppLibrary/Menu.h" 
#include "../CppLibrary/dynamicTypes.h"
#include "../CppLibrary/fileManager.h"
#include <ctime>
using std::istream; using std::ostream;

class program2{
private:
    class date{
        public:
            long int day = 0;
            long int month = 0;
            long int year = 0;
        void getToday(){
            tm today;
            time_t now = time(0);
            localtime_s(&today, &now);
            day = today.tm_mday;
            month = today.tm_mon + 1;
            year = today.tm_year + 1900;
        };
    };

    class person{
    public:
        date birthday;
        date age;
        string name;
        void update() {
            age.getToday();
            age.year -= birthday.year;
            age.month -= birthday.month;
            age.day -= birthday.day;
            if (age.month < 0) {
                age.month += 12;
                age.year -= 1;
            }
            if (age.day < 0) {
                if (age.month == 2) {
                    age.day += 29;
                }
                else if (age.month == (3, 6, 9, 11)) {
                    age.day += 31;
                }
                else age.day += 30;
                age.month -= 1;
            }
        };
        bool isYoungerThan(person comparable){
            if(age.year < comparable.age.year)          return true;
            else if(age.month < comparable.age.month && age.year == comparable.age.year)    return true;
            else if(age.day < comparable.age.day && age.year == comparable.age.year && age.month == comparable.age.month)       return true;
            else                                        return false;
        };
        bool isOlderThan(person comparable){
            if(age.year > comparable.age.year)          return true;
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

    class memory{
    public:
        linkClass<person> people;
        fileManager<person> file;
        person oldest;
        person younger;
        void update(){
            if (people.first != nullptr) {
                linkClass<person>::nodeClass* cursor = people.first;
                people.first->data.update();
                oldest = people.first->data;
                younger = people.first->data;
                while (cursor != nullptr)
                {
                    cursor->data.update();
                    if (oldest.isYoungerThan(cursor->data)) oldest = cursor->data;
                    if (younger.isOlderThan(cursor->data)) younger = cursor->data;
                    cursor = cursor->next;
                }
            }
        };
    };

    memory data_memory;
    
    bool verify(person data) {
        if (data.birthday.day > 29 && data.birthday.month == 2)
            return true;

        else if (data.birthday.day > 31 && (data.birthday.month == 3 || data.birthday.month == 6 || data.birthday.month == 9 || data.birthday.month == 11))
            return true;

        else if (data.birthday.day > 30)
            return true;

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
        linkClass<person>::nodeClass* cursor = data_memory.people.first;
        int i = 1;
        if (cursor != nullptr) {
            data_memory.people.first->data.update();
            data_memory.oldest = cursor->data;
            data_memory.younger = cursor->data;
            while (cursor != nullptr)
            {
                cursor->data.update();
                cout << i << ") " << "________________________________________" << "\n";
                cout << "\t nombre: " << cursor->data.name << "\n";
                cout << "\t fecha de nacimiento: " << cursor->data.birthday.day << "/" << cursor->data.birthday.month << "/" << cursor->data.birthday.year << " ";
                cout << "\n\t desde que nacio: \n";
                cout << "\t\t\t " << cursor->data.age.year << " anios" << "\n";
                cout << "\t\t\t " << cursor->data.age.month << " meses" << "\n";
                cout << "\t\t\t " << cursor->data.age.day << " dias" << "\n";
                if (cursor->data.isOlderThan(data_memory.oldest))   data_memory.oldest = cursor->data;
                if (cursor->data.isYoungerThan(data_memory.younger))    data_memory.younger = cursor->data;
                cursor = cursor->next;
                i += 1;
            }
            cout << "\t el mas viejo es: " << data_memory.oldest.name << " con " << data_memory.oldest.age.year << " anios" << "\n";
            cout << "\t el mas joven es: " << data_memory.younger.name << " con " << data_memory.younger.age.year << " anios" << "\n";
            pause();
        }
        else cout << " no hay datos ingresados";
    };
    void main() {
        data_memory.file.declare("datap2","txt");
        data_memory.file.readToMemory();
        data_memory.people = data_memory.file.inMemoryFile;
        menuClass menu;
        const int menuOptions = 3;
        string menuTitle = "\n\t programa 2: ejercicio de lista de fechas \n";
        string menuText[menuOptions + 1] = {
            "start",
            " Ingresar datos de persona",
            " ver promedio y resultados",
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
                data_memory.people.purgeAll();
                data_memory.file.inMemoryFile.purgeAll();
                break;
            default:
                errormens();
                break;
            }
        }
    };
public:   
    void run(){
        main();
    };
};