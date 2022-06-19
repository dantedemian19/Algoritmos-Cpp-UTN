#pragma once
#include "../CppLibrary/Menu.h"
#include "../CppLibrary/dynamicTypes.h"
#include "../CppLibrary/fileManager.h"
#include <ctime>
using std::istream; using std::ostream;

class program4 {
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
        void print() {
            cout << day << "/" << month << "/" << year << " ";
        };
    };
        class person {
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
                void print(){
                    cout << "\t nombre: " << name << "\n";
                    cout << "\t fecha de nacimiento: "; birthday.print(); cout << "\n";
                    cout << "\t desde que nacio: \n";
                    cout << "\t\t\t " << age.year << " anios" << "\n";
                    cout << "\t\t\t " << age.month << " meses" << "\n";
                    cout << "\t\t\t " << age.day << " dias" << "\n";
                }
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

        class memory {
        public:
            linkList<person> people;
            fileManager<person> file;
            int count = 0;
            float average = 0;
            int lessThanAvg = 0;
            int equalAvg = 0;
            int moreThanAvg = 0; 

            void update() {
                int i = 0;
                if (people.first != nullptr) {
                    average = (float) count / (float) people.getSize();
                    linkList<person>::nodeClass* cursor = people[i];
                    while (cursor != nullptr)
                    {
                        if (cursor->data.age.year < average) {
                            lessThanAvg+=1;
                        }
                        else if (cursor->data.age.year == average) {
                            equalAvg+=1;
                        }
                        else {
                            moreThanAvg+=1;
                        }
                        i += 1;
                        cursor = people[i];
                        
                    }
                }
            };
            void resetNumbers() {
                average = count = lessThanAvg = equalAvg = moreThanAvg = 0;
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
            int i = 0;
            data_memory.resetNumbers();
            linkList<person>::nodeClass* cursor = data_memory.people[i];
            if (cursor != nullptr) {
                while (cursor != nullptr)
                {
                    cursor->data.update();
                    cout << i + 1 << ") " << "________________________________________" << "\n";
                    cursor->data.print();
                    data_memory.count += cursor->data.age.year;
                    i += 1;
                    cursor = data_memory.people[i];
                }
                data_memory.update();
                cout << "__________________________________________" << "\n";
                cout << "\t promedio de edad: " << data_memory.average << " anios" << "\n";
                cout << "\t cantidad que hay mas viejos que el promedio: " << data_memory.moreThanAvg << "\n";
                cout << "\t cantidad que hay igual al promedio: " << data_memory.equalAvg << "\n";
                cout << "\t cantidad que hay mas jovenes que el promedio: " << data_memory.lessThanAvg << "\n";
                cout << "__________________________________________" << "\n";
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
            string menuTitle = "\n\t programa 4: ejercicio de promedios de edades \n";
            string menuText[menuOptions + 1] = {
                "start",
                " Ingresar datos de persona",
                " ver resultados",
                "end"
            };
            menu.declare(menuOptions, 1, menuTitle);
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
                    data_memory.file.inMemoryFile.purgeAll();
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