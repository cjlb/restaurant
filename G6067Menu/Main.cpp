// Main.cpp : Defines the entry point for the console application.
//

#include "G6067Menu.h"

int main() {
        G6067Menu *menu = new G6067Menu();
        menu->run();
        delete menu;
        return 0;
}