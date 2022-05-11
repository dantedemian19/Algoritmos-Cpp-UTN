#pragma once
#include "../CppLibrary/menu.h"
#include "1stProgram.h"

class cluster {
private:
    class programClass {
    public:
        program1 one;
    };
    

public:
	void main() {
        menuClass menu;
        programClass programs;
        const int menuOptions = 3;
        string menuTitle = "\n\t Programas: Algoritmos y Estructura de Datos 2022 K1091 Dante Alfonso \n";
        string menuText[menuOptions + 1] = {
            "start",
            " programa 1: ejercicio de promedios",
            " programa 2: ejercicio de lista de fechas",
            "end"
        };
        menu.declare(menuOptions,0, menuTitle);
        while (menu.w != menu.exit) {
            menu.menu(menuText);
            switch (menu.w)
            {
            case 1:
                wait();
                programs.one.run();
                break;
            case 2:
                
                pause();
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
};