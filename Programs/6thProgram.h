#pragma once
// headers
#include "../CppLibrary/Menu.h"
#include "../CppLibrary/dynamicTypes.h"
#include "../CppLibrary/fileManager.h"

// data classes
#include "./Classes/person.h"

class program6 {
private:
    class memory {
    public:
        linkList<person> people;
        fileManager<person> file;

        void updatePeople() {
            int i = 0;
            linkList<person>::nodeClass* cursor = people[i];
            while (cursor != nullptr)
            {
                cursor->data.update();
                i += 1;
                cursor = people[i];
            }
        };
    };

    memory data_memory;

    bool verify(person data) {
        // if its ferbuary
        if (data.birthday.day > 29 && data.birthday.month == 2)
            return true;
        // if the month have 31 days
        else if (data.birthday.day > 31 && data.birthday.month == (3, 6, 9, 11))
            return true;
        //if the month have 30 days
        else if (data.birthday.day > 30)
            return true;
        // if its out of value
        else return false;
    };

    void inputData() {
        person data_input;
        cout << "\n";
        while (1) {
            cout << "\t ingrese el nombre del alumno : ";
            cin >> data_input.name;
            if (data_input.name.length() == 0) {
                cls();
                cout << "\n\t (ingrese un valor valido)";
            }
            else break;
        }
        while (1) {
            cout << "\t ingrese el anio de nacimiento: ";
            cin >> data_input.birthday.year;
            if (data_input.birthday.year < 1) {
                cls();
                cout << "\n\t (ingrese un valor valido)";
            }
            else break;
        }
        while (1) {
            cout << "\t ingrese el mes de nacimiento en numero: ";
            cin >> data_input.birthday.month;
            if (data_input.birthday.month < 1 || data_input.birthday.month > 12) {
                cls();
                cout << "\n\t (ingrese un valor valido)";
            }
            else break;
        }
        while (1) {
            cout << "\t ingrese el dia de nacimiento: ";
            cin >> data_input.birthday.day;
            if (data_input.birthday.day < 1 || verify(data_input)) {
                cls();
                cout << "\n\t (ingrese un valor valido)";
            }
            else break;
        }
        data_memory.people.addToEnd(data_input);
        data_memory.file.write(data_input);
    };

    void showData() {
        int i = 0;
        linkList<person>::nodeClass* cursor = data_memory.people[i];
        data_memory.updatePeople();
        data_memory.people.quickSort(0, (data_memory.people.getSize() - 1));
        cout << "\n";
        if (cursor != nullptr) {
            while (cursor != nullptr)
            {
                cout << i + 1 << ") " << "________________________________________" << "\n";
                cursor->data.print();
                i += 1;
                cursor = data_memory.people[i];
            }
            cout << "__________________________________________" << "\n";
            pause();
        }
        else cout << "\t\t no hay datos ingresados";
    };

    void filterData() {
        int i = 0;
        linkList<person>::nodeClass* cursor = data_memory.people[i];
        data_memory.updatePeople();
        data_memory.people.quickSort(0, (data_memory.people.getSize() - 1));
        date ageComparator = cursor -> data.age;// for compare age of every group with the same age.year
        int counter =0 ;// for count how many are in one group
        cout << "\n";
        if (cursor != nullptr) {
            while (cursor != nullptr)
            {
                cursor->data.update();
                cout << i + 1 << ") " << "________________________________________" << "\n";
                cursor->data.print();
                counter += 1;
                i += 1;
                cursor = data_memory.people[i];
                if (cursor == nullptr || cursor->data.age.year != ageComparator.year) {
                    cout << "__________________________________________" << "\n";
                    cout << "\t" << "los que tienen " << ageComparator.year << " anios son " << counter << " personas"<<"\n";
                    counter = 0;
                    if (cursor != nullptr) ageComparator = cursor->data.age;
                }  
            };
            cout << "__________________________________________" << "\n";
            pause();
            }
        else cout << "\t\t no hay datos ingresados";
    };

    void showPremise(string title) {
        string premise[] = {
            "\t Procesar un conjunto de personas de las cuales conocemos su nombre y fecha de nacimiento.",
            "\t Se debe : ",
            "\t\t 1) Mostrar por pantalla nos nombres y las fechas de nacimiento ordenado por edad.",
            "\t\t 2) Mostrar por pantalla la cantidad de personas por edad."
        };
        int i = 0;
        cout << title;
        int size = sizeof(premise) / sizeof(premise[0]);
        while (i < size) {
            cout << "\n";
            cout << premise[i];
            i+=1;
        };
        cout << "\n\n";
        pause();
    };

    void main() {
        data_memory.file.declare("datap3", "txt");
        data_memory.file.readToMemory();
        data_memory.people = data_memory.file.inMemoryFile;
        menuClass menu;
        string menuTitle = "\n\t programa 6: ejercicio de ordenamiento \n";
        string menuText[] = {
            "start",
            " Ingresar datos de persona",
            " ver todas las personas",
            " ver cantidad de personas por edad",
            " ver enunciado",
            "end"
        };
        const int menuOptions = sizeof(menuText) / sizeof(menuText[0]) - 1;
        menu.declare(menuTitle, menuText, menuOptions);
        while (menu.w != menu.exit) {
            menu.menu();
            switch (menu.w)
            {
            case 1:
                inputData();
                break;
            case 2:
                showData();
                break;
            case 3:
                filterData();
                break;
            case menuOptions - 1:
                showPremise(menuTitle);
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