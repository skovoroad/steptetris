#pragma once

#include <cstdlib>

class IO
{
public:
    IO() {
        system("stty -echo"); 
        system("stty raw"); 
    }

    ~IO() {
        system("stty cooked");  
        system("stty echo");   
    }

    char lastInput() {
        return getchar();
    }

    void clearOutput() const {
        system("clear");
    }
};


