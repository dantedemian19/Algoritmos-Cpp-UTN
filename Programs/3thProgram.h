#pragma once
#include "../CppLibrary/Menu.h" 

class program3{
    private:

        void main(){
            const int menuOptions = 3;
            string menuTitle = "\n\t programa 3: ejercicio  \n";
            string menuText[menuOptions + 1] = {
                "start",
                " ",
                " ",
                "end"
            };
            menu.declare(menuOptions, 1, menuTitle);
            menu.setText(menuText);
        };
    public:
        void run(){
            main();
        }

}

