#pragma once
#include <string.h>
#include <conio.h>
#include <iostream>
#include "Lists.h"
#include "CategoryList.h"

#include "G6067Input.h"

#define VIEW_MENU_MAIN 0
#define VIEW_MENU_CATEGORIES 1
#define VIEW_MENU_ITEMS 2

#define VIEW_CATEGORY_ADD 3
#define VIEW_CATEGORY_EDIT 4
#define VIEW_CATEGORY_DELETE 5

#define VIEW_MENU_ITEM_ADD 6
#define VIEW_MENU_ITEM_EDIT 7
#define VIEW_MENU_ITEM_DELETE 8

/* keys */
#define ESCAPE 27
#define ENTER 13

using namespace std;

class G6067Menu : G6067Input {
        /* constructors and destructors */
public:
        G6067Menu();
        ~G6067Menu();

        /* function prototypes */
public:
        bool run();

private:
        void displayView(int, Lists*);
        void displayEditorViews(int, Lists*);
        void displayCategoryEditorViews(int, Lists*);
        void displayMenuItemEditorViews(int, Lists*);

        int processInput(int, Lists*);
        int processInputMainMenu(int, string, Lists*);
        int processInputCategories(int, string, Lists*);
        int processInputMenuItems(int, string, Lists*);

        int processCategoryAdd(int, string, Lists*);
        int processCategoryChange(int, string, Lists*);
        int processCategoryDelete(int, string, Lists*);

        int processMenuItemAdd(int, string, Lists*);
        int processMenuItemChange(int, string, Lists*);
        int processMenuItemDelete(int, string, Lists*);
};
