// main.cpp : Defines the entry point for the console application.
//

#include "G6067HeadOffice.h"

int main() {
        G6067HeadOffice *office = new G6067HeadOffice();
        office->run();
        delete office;
        return 0;
}