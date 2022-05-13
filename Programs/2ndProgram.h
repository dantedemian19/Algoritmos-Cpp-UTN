#pragma once
#include "../CppLibrary/Menu.h" 
#include "../CppLibrary/dynamicTypes.h"

class program2{
private:
    class date{
        public:
            int day;
            int month;
            int year;
    };

    class person{
        date birthday;
        date age;
        string name;
        void update(){
            
        };
    };
    class memory{
        linkClass<person> people;
        // date today =
        person oldest;
        person younger;
        void update(){
            linkClass<person>::nodeClass cursor = person->start;
            while (cursor!=nullptr)
            {
                cursor.data.update();
                if(){
                    
                }
            }
            
        };
    };
public:   
    void main() {
        const int menuOptions = 3;
        string menuTitle = "\n\t programa 2: ejercicio de lista de fechas \n";
        string menuText[menuOptions + 1] = {
            "start",
            " Ingresar datos de persona",
            " ver promedio y resultados",
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
                break;
            default:
                errormens();
                break;
            }
        }
    };
}