#pragma once
#include "../CppLibrary/menu.h"
#include "1stProgram.h"
#include "2ndProgram.h"
#include "3thProgram.h"
#include "4thProgram.h"
#include "5thProgram.h"
#include "facturacion.h"

class cluster{
private:
    class programClass {
    public:
        program1 one;
        program2 two;
        program3 three;
        program4 four;
        program5 five;
        //cursed
        programFacturador facturador;
    };
    void cursedPrograms() {
        menuClass menu;
        programClass programs;
        const int menuOptions = 3;
        string menuTitle = "\n\t Programas: Algoritmos y Estructura de Datos 2022 K1091 Dante Alfonso \n";
        string menuText[menuOptions + 1] = {
            "start",
            " programa 1: programa de facturacion",
            " show meme",
            "end"
        };
        menu.declare(menuOptions, 0, menuTitle);
        while (menu.w != menu.exit) {
            menu.menu(menuText);
            wait(2);
            switch (menu.w)
            {
            case 1:
                programs.facturador.run();
                break;
            case menuOptions-1:
                menu.showGracia();
                break;
            case menuOptions:
                cls();
                break;
            default:
                errormens();
                break;
            }
        }
    }
	void main() {
        menuClass menu;
        programClass programs;
        const int menuOptions = 7;
        string menuTitle = "\n\t Programas: Algoritmos y Estructura de Datos 2022 K1091 Dante Alfonso \n";
        string menuText[menuOptions + 1] = {
            "start",
            " programa 1: ejercicio de promedios",
            " programa 2: ejercicio de lista de fechas",
            " programa 3: ejercicio con una lista de fechas",
            " programa 4: ejercicio de promedios de edades",
            " programa 5: ejercicio de ordenamiento",
            " programas cursed",
            "end"
        };
        menu.declare(menuOptions,0, menuTitle);
        while (menu.w != menu.exit) {
            menu.menu(menuText);
            wait();
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
            case 4:
                programs.four.run();
                break;
            case 5:
                programs.five.run();
                break;
            case menuOptions-1:
                cursedPrograms();
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