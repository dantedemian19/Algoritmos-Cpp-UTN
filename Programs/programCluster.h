#pragma once
#include "../CppLibrary/menu.h"
#include "1stProgram.h"
#include "2ndProgram.h"
#include "3thProgram.h"

class cluster{
private:
    class programClass {
    public:
        program1 one;
        program2 two;
        program3 three;
    };

	void main() {
        menuClass menu;
        programClass programs;
        const int menuOptions = 4;
        string menuTitle = "\n\t Programas: Algoritmos y Estructura de Datos 2022 K1091 Dante Alfonso \n";
        string menuText[menuOptions + 1] = {
            "start",
            " programa 1: ejercicio de promedios",
            " programa 2: ejercicio de lista de fechas",
            " programa 3: ejercicio con una lista de fechas",
            "end"
        };
        menu.declare(menuOptions,0, menuTitle);
        while (menu.w != menu.exit) {
            menu.menu(menuText);
            wait(2);
            switch (menu.w)
            {
            case 1:
                programs.one.run();
                break;
            case 2:
                programs.two.run();
                break;
            case 3:
                programs.three.run();
                break;
            case menuOptions:
                cls();
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