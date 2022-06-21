#pragma once
#include "../CppLibrary/Menu.h" 
#include "../CppLibrary/dynamicTypes.h" 

class program1 {
private:
    class input {// valores que ingresa el usuario
    public:
        int number = 0;// para numeros
        void clean() {// limpia los valores
            number = 0;
        };
    };
    class memory {
    public:
        int ages = 0;// para guardar la suma de las ededes ingresadas
        int quantity = 0;// para guardar la cantidad de edades ingresadas
    };
    class output {// valores que se le devuelven al usuario
    public:
        int average_age = 0;// promedio de edades puesto

        int option() {// devuelve el tipo de alumno en base al promedio de edades
            if (average_age <= 0) return 0;
            else if (average_age > 0 && average_age <= 12) return 1;
            else if (average_age > 12 && average_age <= 18) return 2;
            else if (average_age > 18) return 3;
            else return 0;
        };
    };

    menuClass menu;
    memory data_memory;

    void inputData() {
        input temp_input;
        do
        {
            cout << "\n";
            cout << "Ingrese edad: ";
            cin >> temp_input.number;
            cls();
        } while (temp_input.number <= 0 || temp_input.number > 1000);// verifica que el valor sea una edad, y descarta errores de memoria
        data_memory.quantity+=1;
        data_memory.ages += temp_input.number;
    };

    void showData() {
            output data_output;
            data_output.average_age = data_memory.ages / data_memory.quantity; // calculo del promedio de edades
            cout << "\n";
            cout << "El promedio de edad es: " << data_output.average_age << "\n";
            switch (data_output.option()) {
            case 1:
                cout << "\t" << " son alumnos de primaria" << "\n";
                break;
            case 2:
                cout << " son alumnos de secundaria" << "\n";
                break;
            case 3:
                cout << " son alumnos de universidad" << "\n";
                break;
            default:
                cout << "ingrese correctamente las edades, hubo un error" << "\n";
                break;
            }
            pause();
    };
    
    void showPremise(string title) {
        string premise[] = {
        "\t Para un conjunto de estudiantes de los que conocemos su edad debemos calcular el promedio y mostrar en la pantalla si se trata de alumnos de primaria, secundaria o universidad.\n",
        "\t Si el promedio es menos a 12 años son alumnos de primaria; si el promedio está entre 12 y 18 años se trata de alumnos de secundaria; para promedio mayores se trata de alumnos universitarios.\n"
        };
        int i = 0;
        cout << title;
        int size = sizeof(premise) / sizeof(premise[0]);
        while (i < size) {
            cout << "\n";
            cout << premise[i];
            i += 1;
        };
        cout << "\n\n";
        pause();
    };

    void main() {

        string menuTitle = "\n\t Programa 1: Calculo de promedios \n";
        string menuText[] = {
            "start",
            " Ingresar Alumno",
            " ver promedio y resultados",
            " ver enunciado",
            "end"
        };
        const int menuOptions = sizeof(menuText) / sizeof(menuText[0]) - 1;
        menu.declare(menuTitle,menuText,menuOptions);
        while (menu.w != menu.exit) {
            menu.menu();
            switch (menu.w)
            {
            case 1:
                inputData();
                break;
            case 2:
                showData();
                break;
            case menuOptions-1:
                showPremise(menuTitle);
                break;
            case menuOptions:
                            
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

