#pragma once
#include "consoleComands.h"
#include "include.h"

// keyboard id's
#define space 32
#define up 72
#define down 80
#define entr 13
#define esc 27
#define back 8


class menuClass {
    private:
        string name = "";
        int program = 0;
        bool enter = false;
        string namef = "";
    public:
        int w = 1, exit = 0;
        void detection();
        void menu(string menuText[]);
        void declare(int numberOfOptions, int numberProgram, string nameOfMenu);
};

void advice() {
    //advice for users
    cout << " pulse W o UP para subir y S o DOWN para bajar \n";
    Sleep(1000);
    cout << " pulse ESC or DEL para salir \n";
    Sleep(1000);
    cout << " pulse F o ENTER para acceder o aceptar \n";
    Sleep(500);
    pause();
    cls();
    //advice
};

void menuClass::detection() { // mueve el cursor dependiendo la decision del usuario
    int c = 0;
    // keyboard detection
    while (c != 's' && c != 'w' && c != 'f' && c != entr && c != up && c != down && c != esc && c != back) {
        c = _getch();
    }
    if (c == 'w' || c == up) {// if the user press up or W
        if (w > 1) {
            w = w - 1;
        }
        else {
            w = exit;
        }
    }
    if (c == 's' || c == down) {// if the user press down or S
        if (w < exit) {
            w = w + 1;
        }
        else {
            w = 1;
        }
    }
    if (c == 'f' || c == entr) {// if the user press enter or F
        enter = !enter;
    }
    if (c == back || c == esc) {// if the user press DELETE or ESC
        w = exit;
        enter = !enter;
    }
};
void menuClass::menu(string menuText[]) {// its a easy menu
        enter = false;
        while (!enter) {
            cls();//cursor appears only in selected option 
            cout << "  " << name << "  \n";
            for (int i = 1; i <= exit; i += 1) {
                if (i != exit) {
                    if (w == i) { cout << "  >>"; } cout << "\t" << menuText[i] << "\n";
                }
                else { if (w == i) { cout << "  >>"; } cout << "\t" << " back" << "\n"; }
            }
            //detection of the cursor
            detection();
            //detection of the cursor
        }
        cls();
};

void menuClass::declare(int numberOfOptions, int numberProgram, string nameOfMenu) {
    exit    = numberOfOptions;
    program = numberProgram;
    name    = nameOfMenu;
};