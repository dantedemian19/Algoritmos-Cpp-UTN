#pragma once

#include "task.h"

class student{
    private:
        string name = "";
        task progress[9][10];

    public:

        void print(){
            int i = 0, j = 0;
            string CodAreas = "\t\t CS\t CN\t PDL\t MA\t MS\t PL\t EF\t TX\t IG";
            cout<<"\t nombre: "<< name<<"\n";
            cout<<"\t"<<CodAreas<<"\n";
            while(i<9) {
                cout<<"\t"<<"\n";
                while(j<10){
                    cout<<"\t ";
                    if(i==2)cout<<" ";
                    cout<<progress[j][i];
                    j+=1;
                }
                i+=1;
            }
        };

        friend string operator = (string comparable){
            return (name==comparable  );
        };

        friend istream& operator>> (istream& in, student& data) {// to read from file
            in >> data.name;
            in >> data.birthday.day;
            in >> data.birthday.month;
            in >> data.birthday.year;
            return in;
        };
        friend ostream& operator << (ostream& out, person& data) { // to write into a file
            out << data.name << " " << data.birthday.day << " " << data.birthday.month << " " << data.birthday.year << "\n";
            return out;
        };
}