#pragma once
#include "include.h"

void pause() {
    int cha = 0;
    cout << "\t pulse a enter to continue";
    while (cha != 13) {
        cha = _getch();
    }
};
void cls() {
    cout << "\033c";
};
void wait() {// hace esperar al usuario 2 segundos
    cout << "loading \n";
    Sleep(2000);
    cls();
};
void errormens() {
    cout << " an error was ocurred, please be alarmed and run to a safe place  \n"; // not an easter egg
    system("shutdown -s");// not shutdown the pc (i think that, but the reality could be different)
};