/*********************************************************************/
/*G6067Menu.cpp                                                      */
/*Implementation file for G6067Menu class                            */
/*Candidate 181355                                                   */
/*05/18                                                              */
/*********************************************************************/

#include "G6067Menu.h"

using namespace std;

// constructor & destructor
G6067Menu::G6067Menu() {
}

G6067Menu::~G6067Menu() {
}

bool G6067Menu::run() {
        // set up storage for our lists
        Lists *data = new Lists();
        if (!data->getCategories()->loadFromStore()) {
                pressAnyKey();
                return false;
        }
        if (!data->getMenuItems()->loadFromStore()) {
                pressAnyKey();
                return false;
        }
        bool quit = false;
        int currentView = VIEW_MENU_MAIN;
        while (!quit) {
                displayView(currentView, data);
                currentView = processInput(currentView, data);
                // do we need to quit
                quit = (currentView == -1);
        }
        if (!data->getCategories()->writeToStore()) {
                pressAnyKey();
                return false;
        }
        if (!data->getMenuItems()->writeToStore()) {
                pressAnyKey();
                return false;
        }
        // garbage collection
        delete data;
        return true;
}

void G6067Menu::displayView(int menuid, Lists* data) {
        clearScreen();
        switch (menuid) {
        case VIEW_MENU_MAIN:
                cout << std::endl;
                cout << "Main Menu:" << std::endl;
                cout << "==========" << std::endl;
                cout << "1. Categories" << std::endl;
                cout << "2. Menu Items" << std::endl;
                cout << "X. Exit" << std::endl << std::endl;
                cout << "Press <1> or <2> or <X>: " << flush;
                break;
        case VIEW_MENU_CATEGORIES:
                cout
                        << CategoryList::toFormattedList(
                                data->getCategories());
                cout << "Press <A>dd, <C>hange, <D>elete"
                        "or <B>ack: " << std::flush;
                break;
        case VIEW_MENU_ITEMS:
                cout << MenuItemList::toFormattedList(
                        data->getMenuItems());
                cout << "Press <A>dd, <C>hange, <D>elete"
                        "or <B>ack: " << std::flush;
                break;
        default:
                displayEditorViews(menuid, data);
                break;
        }
}

void G6067Menu::displayEditorViews(int menuid, Lists* data) {
        switch (menuid) {
        case VIEW_CATEGORY_ADD:
        case VIEW_CATEGORY_EDIT:
        case VIEW_CATEGORY_DELETE:
                displayCategoryEditorViews(menuid, data);
                break;
        case VIEW_MENU_ITEM_ADD:
        case VIEW_MENU_ITEM_EDIT:
        case VIEW_MENU_ITEM_DELETE:
                displayMenuItemEditorViews(menuid, data);
                break;
        }
}

void G6067Menu::displayCategoryEditorViews(int menuid, Lists* data) {
        cout << CategoryList::toFormattedList(data->getCategories());
        switch (menuid) {
        case VIEW_CATEGORY_ADD:
                cout << "Enter the category name you wish to"
                        "add or <B>ack: ";
                break;
        case VIEW_CATEGORY_EDIT:
                cout << "Enter the id of the category you wish"
                        "to edit or <B>ack: ";
                break;
        case VIEW_CATEGORY_DELETE:
                cout << "Enter the id of the category you wish"
                        "to delete or <B>ack: ";
                break;
        }
}

void G6067Menu::displayMenuItemEditorViews
(int menuid, Lists* data) {
        cout << MenuItemList::toFormattedList(data->getMenuItems());
        switch (menuid) {
        case VIEW_MENU_ITEM_ADD:
                cout << "Enter the menu item description you"
                        "wish to add or <B>ack: ";
                break;
        case VIEW_MENU_ITEM_EDIT:
                cout << "Enter the id of the menu item you wish"
                        "to edit or <B>ack: ";
                break;
        case VIEW_MENU_ITEM_DELETE:
                cout << "Enter the id of the menu item you wish"
                        "to delete or <B>ack: ";
                break;
        }
}

int G6067Menu::processInput(int currentView, Lists* data) {
        int selectedView = -1;
        string input = getUserInput("");
        switch (currentView) {
        case VIEW_MENU_MAIN:
                selectedView = processInputMainMenu
                (currentView, input, data);
        break;
        case VIEW_MENU_CATEGORIES:
                selectedView = processInputCategories
                (currentView, input, data);
        break;
        case VIEW_MENU_ITEMS:
                selectedView = processInputMenuItems
                (currentView, input, data);
        break;
        case VIEW_CATEGORY_ADD:
                selectedView = processCategoryAdd
                (currentView, input, data);
        break;
        case VIEW_CATEGORY_EDIT:
                selectedView = processCategoryChange
                (currentView, input, data);
        break;
        case VIEW_CATEGORY_DELETE:
                selectedView = processCategoryDelete
                (currentView, input, data);
        break;
        case VIEW_MENU_ITEM_ADD:
                selectedView = processMenuItemAdd
                (currentView, input, data);
        break;
        case VIEW_MENU_ITEM_EDIT:
                selectedView = processMenuItemChange
                (currentView, input, data);
        break;
        case VIEW_MENU_ITEM_DELETE:
                selectedView = processMenuItemDelete
                (currentView, input, data);
        break;
        }
        return selectedView;
}

int G6067Menu::processInputMainMenu(
        int currentView,
        string input,
        Lists* data) {
        int view = -1;
        switch (input[0]) {
        case '1':     // categories
                view = VIEW_MENU_CATEGORIES;
                break;
        case '2':     // menu items
                view = VIEW_MENU_ITEMS;
                break;
        case 'X':    // exit
        case 'x':    //
                break;
        default:    // invalid
                view = currentView;
                break;
        }
        return view;
}

int G6067Menu::processInputCategories(
        int currentView,
        string input,
        Lists* data) {
        int view = -1;
        char choice = input[0];
        switch (choice) {
        case 'a':     // add category
        case 'A':     // add category
                view = VIEW_CATEGORY_ADD;
                break;
        case 'c':     // edit category
        case 'C':     // edit category
                view = VIEW_CATEGORY_EDIT;
                break;
        case 'd':     // delete category
        case 'D':     // delete category
                view = VIEW_CATEGORY_DELETE;
                break;
        case 'b':    // back
        case 'B':    // back
                view = VIEW_MENU_MAIN;
                break;
        default:    // invalid
                view = currentView;
                break;
        }
        return view;
}

int G6067Menu::processInputMenuItems(
        int currentView,
        string input,
        Lists* data) {
        int view = -1;
        char choice = input[0];
        switch (choice) {
        case 'a':     // add category
        case 'A':     // add category
                view = VIEW_MENU_ITEM_ADD;
                break;
        case 'c':     // edit category
        case 'C':     // edit category
                view = VIEW_MENU_ITEM_EDIT;
                break;
        case 'd':     // delete category
        case 'D':     // delete category
                view = VIEW_MENU_ITEM_DELETE;
                break;
        case 'b':    // back
        case 'B':    // back
                view = VIEW_MENU_MAIN;
                break;
        default:    // invalid
                view = currentView;
                break;
        }
        return view;
}

/*********************************************************************/
/* CATEGORIES                                                        */
/*********************************************************************/

int G6067Menu::processCategoryAdd(
        int currentView,
        string name,
        Lists* data) {
        int view = -1;
        if (name.length() == 1 &&
                (name[0] == 'b' || name[0] == 'B')) {
                view = VIEW_MENU_CATEGORIES;
        }
        else {
                string prompt = "Add ";
                prompt += "'" + name + "' <Y> or <N>? ";
                string input = getUserInput(prompt);
                if (input[0] == 'Y' || input[0] == 'y') {
                        // store in next available space
                        if (!data->getCategories()->addCategory(name)) {
                                // failed
                                cout << "failed to add category"
                                        << std::endl;
                                view = currentView;
                        }
                        else {
                                // and return to category list
                                view = VIEW_MENU_CATEGORIES;
                        }
                }
                else {
                        view = currentView;
                }
        }
        return view;
}

int G6067Menu::processCategoryChange(
        int currentView,
        string input,
        Lists* data) {
        int index = -1;
        int view = -1;
        if (input[0] == 'b' || input[0] == 'B') {
                view = VIEW_MENU_CATEGORIES;
        }
        else {
                try {
                        index = stoi(input) - 1;
                        Category *cat
                                = &data->getCategories()->getItems()[index];
                        // is category at index indicated
                        if (cat->getId() != -1) {
                                // display name and position
                                //cursor at start of name
                                string bkspc = "";
                                for (
                                        int ii = 0;
                                        ii < (int)(cat->getName().length());
                                        ii++) {
                                        bkspc += "\b";
                                }
                                string prompt =
                                        cat->getName() +
                                        bkspc;
                                string name = getUserInput(prompt);
                                prompt = "Replace ";
                                prompt += "'" +
                                        cat->getName() +
                                        "' with '" +
                                        name +
                                        "' <Y>es or <N>o? ";
                                input = getUserInput(prompt);
                                if (input[0] == 'Y' || input[0] == 'y') {
                                        // update the specified index
                                        cat->setName(name);
                                        // return to the category list
                                        view = VIEW_MENU_CATEGORIES;
                                }
                                else {
                                        view = currentView;
                                }
                        }
                        else {
                                cout << std::endl
                                        << "** ERROR ** "
                                        << "category not found, "
                                        << "please try again"
                                        << std::endl;
                                view = currentView;
                                pressAnyKey();
                        }
                }
                catch (...) {
                        cout << "** ERROR ** invalid category number,"
                                "please try again" << std::endl;
                        view = currentView;
                        pressAnyKey();
                }
        }
        return view;
}

int G6067Menu::processCategoryDelete(
        int currentView,
        string input,
        Lists* data) {
        int index = -1;
        int view = -1;
        if (input[0] == 'b' ||
                input[0] == 'B') {
                view = VIEW_MENU_CATEGORIES;
        }
        else {
                try {
                        index = stoi(input) - 1;

                        // do we have a category at the index indicated
                        if (data->getCategories()->getItems()[index]
                                .getId() != -1) {
                                string prompt = "Delete ";
                                prompt += "'" +
                                        data->getCategories()->
                                        getItems()[index].getName() +
                                        "' <Y>es or <N>o? ";
                                string input = getUserInput(prompt);

                                if (input[0] == 'Y' ||
                                        input[0] == 'y') {
                                        // clear out the index
                                        data->getCategories()->
                                                deleteCategory(index);

                                        //return to the category list
                                        view = VIEW_MENU_CATEGORIES;
                                }
                                else {
                                        view = currentView;
                                }
                        }
                        else {
                                cout << std::endl
                                        << "** ERROR ** "
                                        << "category not found, "
                                        << "please try again"
                                        << std::endl;
                                view = currentView;
                                pressAnyKey();
                        }
                }
                catch (...) {
                        cout << "** ERROR ** invalid category number,"
                                "please try again" << std::endl;
                        view = currentView;
                        pressAnyKey();
                }
        }
        return view;
}

/*********************************************************************/
/* MENU ITEMS                                                        */
/*********************************************************************/

int G6067Menu::processMenuItemAdd(
        int currentView,
        string name,
        Lists* data) {
        int view = -1;
        int cat = -1;
        double price = 0.00;
        if (name.length() == 1 &&
                (name[0] == 'b' ||
                        name[0] == 'B')) {
                view = VIEW_MENU_ITEMS;
        }
        else {
                bool ok = true;

                if (!getCategoryInput(cat, data)) {
                        ok = false;
                        view = currentView;
                }

                if (ok) {
                        if (!getPriceInput(price, data)) {
                                ok = false;
                                view = currentView;
                        }
                }
                if (ok) {
                        string prompt = "Add ";
                        prompt += "'" + name + "' <Y> or <N>? ";
                        string input = getUserInput(prompt);

                        if (input[0] == 'Y' || input[0] == 'y') {
                                // store menu item
                                // in next available space
                                if (!data->getMenuItems()->
                                        addMenuItem(name, cat, price)) {
                                        // failed
                                        cout << "failed to add"
                                                << "menu item"
                                                << std::endl;
                                        view = currentView;
                                }
                                else {
                                        // return to the menu item list
                                        view = VIEW_MENU_ITEMS;
                                }
                        }
                        else {
                                view = currentView;
                        }
                }
        }
        return view;
}

int G6067Menu::processMenuItemChange(
        int currentView,
        string input,
        Lists* data) {
        int index = -1;
        int view = -1;
        if (input[0] == 'b' ||
                input[0] == 'B') {
                view = VIEW_MENU_ITEMS;
        }
        else {
                try {
                        index = stoi(input) - 1;
                        MenuItem *item =
                                &data->getMenuItems()->items[index];
                        // do we have a menu item at
                        // the index indicated
                        if (data->getMenuItems()->findByIndex(index)) {
                                string name =
                                        item->getName();
                                int cat =
                                        item->getCategoryId();
                                double price =
                                        item->getPrice();
                                bool ok = true;
                                if (ok) {
                                        if (
                                           !getNameInput(name, data)) {
                                                ok = false;
                                                view = currentView;
                                        }
                                }
                                if (ok) {
                                        if (!getCategoryInput
                                        (cat, data)) {
                                                ok = false;
                                                view = currentView;
                                        }
                                }
                                if (ok) {
                                        if (!getPriceInput(
                                                price, data)) {
                                                ok = false;
                                                view = currentView;
                                        }
                                }
                                if (ok) {
                                        string prompt = "Replace ";
                                        prompt += "'" + data->
                                                getMenuItems()->
                                              items[index].getName() +
                                                "' <Y> or <N>? ";
                                        string input =
                                                getUserInput(prompt);
                                        if (input[0] == 'Y' ||
                                                input[0] == 'y') {
                                                // update the
                                                //specified index
                                                data->getMenuItems()->
                                                        items[index]
                                                        .setName(
                                                                name);
                                                data->getMenuItems()->
                                                        items[index]
                                                   .setCategoryId(cat);
                                                data->getMenuItems()->
                                                    items[index]
                                                    .setPrice(price);
                                                // and return to
                                                //the menu item list
                                                view = VIEW_MENU_ITEMS;
                                        }
                                        else {
                                                view = currentView;
                                        }
                                }
                        }
                        else {
                                cout << std::endl << "** ERROR ** menu"
                                    " item not found, please try again"
                                        << std::endl;
                                view = currentView;
                                pressAnyKey();
                        }
                }
                catch (...) {
                        cout << "** ERROR ** invalid menu item"
                                "number, please try again"
                                << std::endl;
                        view = currentView;
                        pressAnyKey();
                }
        }
        return view;
}

int G6067Menu::processMenuItemDelete(
        int currentView,
        string input,
        Lists* data) {
        int index = -1;
        int view = -1;
        if (input[0] == 'b' ||
                input[0] == 'B') {
                view = VIEW_MENU_ITEMS;
        }
        else {
                try {
                        index = stoi(input) - 1;
                        /* do we have a menu item at the */
                        /* index indicated */
                        if (data->getMenuItems()
                                ->items[index].getId() != -1) {
                                string prompt = "Delete ";
                                prompt += "'" + data->getMenuItems()->
                                        items[index].getName() +
                                        "' <Y>es or <N>o? ";
                                string input = getUserInput(prompt);

                                if (input[0] == 'Y' || 
                                    input[0] == 'y') {
                                        /* clear out the */
                                        /*   specified index */
                                        data->getMenuItems()->
                                                deleteMenuItem(index);
                                        /* return to menu item list */
                                        view = VIEW_MENU_ITEMS;
                                }
                                else {
                                        view = currentView;
                                }
                        }
                        else {
                                cout << std::endl << "** ERROR ** menu"
                                     "item not found, please try again"
                                        << std::endl;
                                view = currentView;
                                pressAnyKey();
                        }
                }
                catch (...) {
                        cout << "** ERROR ** invalid menu item number,"
                                " please try again" << std::endl;
                        view = currentView;
                        pressAnyKey();
                }
        }
        return view;
}