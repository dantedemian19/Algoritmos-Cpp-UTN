#pragma once
#include "../CppLibrary/Menu.h" 
#include "../CppLibrary/dynamicTypes.h"
#include <ctime>


void main() {

    const int menuOptions = 3;
    string menuTitle = "\n\t programa 2: ejercicio de lista de fechas \n";
    string menuText[menuOptions + 1] = {
        "start",
        " Ingresar Alumno",
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
