#pragma once
#include "../CppLibrary/menu.h"
#include "1stProgram.h"
#include "2ndProgram.h"
#include "3thProgram.h"
#include "4thProgram.h"
#include "5thProgram.h"
#include "6thProgram.h"
#include "./cursed/facturacion.h"

class cluster{
private:
    class programClass {
    public:
        program1 one;
        program2 two;
        program3 three;
        program4 four;
        program5 five;
        program6 six;
        //cursed
        programFacturador facturador;
    };
    void cursedPrograms() {
        menuClass menu;
        programClass programs;
        string menuTitle = "\n\t Programas: Algoritmos y Estructura de Datos 2022 K1091 Dante Alfonso \n";
        string menuText[] = {
            "start",
            " programa 1: programa de facturacion",
            " show meme",
            "end"
        };
        const int menuOptions = sizeof(menuText) / sizeof(menuText[0]) - 1;
        menu.declare(menuTitle, menuText);
        while (menu.w != menu.exit) {
            menu.menu();
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
        string menuTitle = "\n\t Programas: Algoritmos y Estructura de Datos 2022 K1091 Dante Alfonso \n";
        string menuText[] = {
            "start",
            " programa 1: ejercicio de promedios",
            " programa 2: ejercicio de lista de fechas",
            " programa 3: ejercicio con una lista de fechas",
            " programa 4: ejercicio de promedios de edades",
            " programa 5: ejercicio de ordenamiento",
            " programa 6: ejercicio de corte de control y apareo",
            " programas cursed",
            "end"
        };
        const int menuOptions = sizeof(menuText) / sizeof(menuText[0]) - 1;
        menu.declare(menuTitle, menuText,0);
        while (menu.w != menu.exit) {
            menu.menu();
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
            case 6:
                programs.six.run();
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
        wait();
        }
    };
public:
    void run() {
        main();
    };
};