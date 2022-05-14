#pragma once
#include "../CppLibrary/Menu.h" 
#include "../CppLibrary/dynamicTypes.h"
#include <ctime>

class program2{
private:
    class date{
        public:
            int day = 0;
            int month = 0;
            int year = 0;
        void getToDay(){
            time_t now = time(0);
            tm *ltm = localtime(&now);
            day = ltm->tm_mday;
            month = ltm->tm_mon + 1;
            year = ltm->tm_year + 1900;
        };
    };

    class person{
        date birthday;
        date age;
        string name;
        void update(){
            age.year = today.year - birthday.year;
            age.month = today.month - birthday.month;
            age.day = today.day - birthday.day;
        };
        bool isYoungerThan(person comparable){
            if(age==comparable.age){
                return false;
            }else
            if(age.year < comparable.age.year)          return true;
            else if(age.month< comparable.age.month)    return true;
            else if(age.day < comparable.age.day)       return true;
            else                                        return false;
        };
        bool isOlderThan(person comparable){
            if(age==comparable.age){
                return false;
            }else
            if(age.year > comparable.age.year)          return true;
            else if(age.month> comparable.age.month)    return true;
            else if(age.day > comparable.age.day)       return true;
            else                                        return false;
        };
    };

    class memory{
        linkClass<person> people;
        date today = {1,1,2021};
        person oldest;
        person younger;
        void update(){
            linkClass<person>::nodeClass cursor = person->start;
            oldest.update();
            today.getToDay();
            younger.update();
            while (cursor!=nullptr)
            {
                cursor.data.update();
                if(oldest.isYoungerThan(cursor.data)) oldest = cursor.data;
                if(younger.isOlderThan(cursor.data)) younger = cursor.data;
                cursor = cursor.next;
            }
        };
    };

    memory data_memory;
    fileManager<person> file;
    
    void inputData() {
        person data_input;
        while(data_input.name.length()==0){
            cout << "Ingrese el nombre del alumno: ";
            cin >> data_input.name;
        }
        while(data_input.birthday.year<1){
            cout << "Ingrese el dia de nacimiento: ";
            cin >> data_input.birthday.day;
        }
        while(data_input.birthday.month<1 || data_input.birthday.month>=12){
            cout << "Ingrese el mes de nacimiento en numero: ";
            cin >> data_input.birthday.month;
        }
        while (data_input.birthday.day<1 || ((data_input.birthday.day>31&&data_input.birthday.month!=2)||(data_input.birthday.day>29&&data_input.birthday.month==2))){
            cout << "Ingrese el dia de nacimiento: ";
            cin >> data_input.birthday.day;
        } 
        data_memory.people.addToEnd(data_input);
        file.update(data_input);
    };  
    void showData() {
        data_memory.update();
        linkClass::nodeClass cursor = data_memory.people.start;
        int i = 1;
        while (cursor!=nullptr)
        {
            cout << i << ") " << "________________________________________"<<"\n"; 
            cout <<"\t name: "<< cursor.data.name << "\n" 
            cout <<"\t fecha de nacimiento: "cursor.data.birthday.day << "/" << cursor.data.birthday.month << "/" << cursor.data.birthday.year << " " ;
            cout <<"\t desde que nacio: \m";
            cout << "\t \t"<< cursor.data.age.year << " anios" << "\n";
            cout << "\t \t"<< cursor.data.age.month << " meses" << "\n";
            cout << "\t \t"<< cursor.data.age.day << " dias" << "\n";
            cursor = cursor.next;
        }
        cout << "el mas Viejo es: " << data_memory.oldest.name << " con " << data_memory.oldest.age.year << " años" << endl;
        cout << "el mas Joven es: " << data_memory.younger.name << " con " << data_memory.younger.age.year << " años" << endl;

    };
    void main() {
        file.declare("datap2","txt");
        file.readToMemory();
        data_memory.people = file.inMemoryFile;
        file.inMemoryFile.purgeAll();
        const int menuOptions = 3;
        string menuTitle = "\n\t programa 2: ejercicio de lista de fechas \n";
        string menuText[menuOptions + 1] = {
            "start",
            " Ingresar datos de persona",
            " ver promedio y resultados",
            "end"
        };
        menu.declare(menuOptions, 1, menuTitle);
        menu.setText(menuText);
        menu.menu();
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
}