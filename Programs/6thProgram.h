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
        linkList<person>::nodeClass* cursor = data_memory.people[i];
        data_memory.updatePeople();
        data_memory.people.quickSort(0, (data_memory.people.getSize() - 1));
        if (cursor != nullptr) {
            while (cursor != nullptr)
            {
                cout << i + 1 << ") " << "________________________________________" << "\n";
                cout << "\t\t"; cursor->data.print();
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
        bool showed = false;// for count if show data
        linkList<person>::nodeClass* cursor = data_memory.people[i];
        date ageComparator = { 0,0,0 };
        cout << "\t ingrese mayor a que edad desea filtar los datos: \n\t  ";
        cin >> ageComparator.year;
        if (cursor != nullptr) {
            while (cursor != nullptr)
            {
                cursor->data.update();
                if (cursor->data.age > ageComparator) {
                    cout << i + 1 << ") " << "________________________________________" << "\n";
                    cout << "\t\t"; cursor->data.print();
                    showed = true;
                }
                i += 1;
                cursor = data_memory.people[i];
            }
            if (!showed) {
                cout << "__________________________________________" << "\n";
                cout << "\t\t no hay personas mayores a " << ageComparator.year << " anios \n";
            }
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
        const int menuOptions = 4;
        string menuTitle = "\n\t programa 5: ejercicio de ordenamiento \n";
        string menuText[menuOptions + 1] = {
            "start",
            " Ingresar datos de persona",
            " ver todos los datos",
            " ver personas mayores a una edad",
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
            case 3:
                filterData();
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