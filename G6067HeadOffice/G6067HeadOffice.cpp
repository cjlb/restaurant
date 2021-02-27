#include "G6067HeadOffice.h"

G6067HeadOffice::G6067HeadOffice() {
}

G6067HeadOffice::~G6067HeadOffice() {
}

bool G6067HeadOffice::run() {
        Lists *data = new Lists();
        if (!data->getCategories()->loadFromStore()) {
                pressAnyKey();
                return false;
        }
        if (!data->getMenuItems()->loadFromStore()) {
                pressAnyKey();
                return false;
        }
        if (!data->getTransactions()->loadFromStore()) {
                pressAnyKey();
                return false;
        }
        bool quit = false;
        while (!quit) {
                displayView(data);
                quit = processAnalysisType(data);
        }
        // garbage collection
        delete data;
        return true;
}

bool G6067HeadOffice::displayView(Lists* data) {
        bool success = true;
        clearScreen();
        cout << "Display Sales by <C>ategory or <M>enu Item"
                " or <X> to exit: ";
        return success;
}

bool G6067HeadOffice::processAnalysisType(Lists* data) {
        bool quit = false;
        string input = getUserInput("");
        if (input.length() == 1) {
                if (input[0] == 'x' || input[0] == 'X') {
                        quit = true;
                }
                else {
                        /* if we are not quitting, */
                        /* get analysis range */
                        switch (input[0]) {
                        case 'c':
                        case 'C':
                                displayRangeMenu(
                                        "Display Category Sales for:");
                                processAnalysisRange(
                                        ANALYSIS_TYPE_CATEGORY,
                                        data);
                                break;
                        case 'm':
                        case 'M':
                                displayRangeMenu(
                                        "Display Item Sales for:");
                                processAnalysisRange(
                                        ANALYSIS_TYPE_ITEM,
                                        data);
                                break;
                        }
                }
        }
        return quit;
}

void G6067HeadOffice::displayRangeMenu(string prompt) {
        cout << std::endl
                << prompt << std::endl
                << "  <T>oday" << std::endl
                << "  <M>onth" << std::endl
                << "  <Y>ear" << std::endl
                << std::endl
                << "or <b> to go back: ";
        return;
}

bool G6067HeadOffice::processAnalysisRange(
        int analysisType, 
        Lists* data) {
        bool success = true;
        char analysisRange = '\0';
        string input = getUserInput("");
        if (input.length() == 1) {
                if (input[0] == 'b' || input[0] == 'B') {
                        /* do nothing, we will return to main prompt */
                }
                else {
                        switch (input[0]) {
                        case 'T':
                        case 't':
                                analyzeData(analysisType, 
                                        ANALYSIS_RANGE_TODAY, data);
                                break;
                        case 'M':
                        case 'm':
                                analyzeData(analysisType, 
                                        ANALYSIS_RANGE_MONTH, data);
                                break;
                        case 'Y':
                        case 'y':
                                analyzeData(analysisType, 
                                        ANALYSIS_RANGE_YEAR, data);
                                break;
                        }
                }
        }
        return success;
}

void G6067HeadOffice::analyzeData(
        int analysisType,
        int analysisRange,
        Lists* data) {
        /* display data*/
        clearScreen();
        switch (analysisType) {
        case ANALYSIS_TYPE_CATEGORY:
                cout << "Category Sales for: ";
                break;
        case ANALYSIS_TYPE_ITEM:
                cout << "Menu Item Sales for: ";
                break;
        }
        analyzeBy(analysisType, analysisRange, data);
        cout << std::endl;
        /* press any key*/
        pressAnyKey();
        return;
}

void G6067HeadOffice::analyzeBy(int type, int range, Lists* data) {
        switch (range) {
        case ANALYSIS_RANGE_TODAY:
                cout << "today" << std::endl << std::endl;
                break;
        case ANALYSIS_RANGE_MONTH:
        case 'm':
                cout << "this month" << std::endl << std::endl;
                break;
        case ANALYSIS_RANGE_YEAR:
                cout << "this year" << std::endl << std::endl;
                break;
        }
        cout << analyze(type, range, data);
}

string G6067HeadOffice::analyze(int type, int range, Lists* data) {
        std::vector<Transaction> items = data->getTransactions()->getItems();
        std::vector<AnalysisItem> results;
        Category *cats = data->getCategories()->getItems();
        MenuItem *menu = data->getMenuItems()->items;
        /* get current date */
        time_t now = time(0);
        std::tm *lnow = std::localtime(&now);
        int aid = -1;
        string aname = "";
        unsigned ii = 0;
        for (ii = 0; ii < items.size(); ii++) {
                Transaction tr = items[ii];
                // is transaction date = todays date
                time_t tp = tr.getTaxPoint();
                std::tm *ltm = std::localtime(&tp);
                if (dateMatches(range, ltm, lnow)) {
                        switch (type) {
                        case ANALYSIS_TYPE_CATEGORY:
                                aid = cats[menu[tr.getItemId()]
                                        .getCategoryId()].getId() - 1;
                                aname = cats[aid].getName();
                                break;
                        case ANALYSIS_TYPE_ITEM:
                                aid = tr.getItemId() - 1;
                                aname = menu[aid].getName();
                                break;
                        }
                        addToResults(
                                results,
                                aid,
                                aname,
                                tr.getQuantity(),
                                tr.getLineTotal());
                }
        }
        return processResults(type, results);
}

bool G6067HeadOffice::dateMatches(
        int range, 
        std::tm *aa, 
        std::tm *bb) {
        bool matches = false;
        switch (range) {
        case ANALYSIS_RANGE_TODAY:
                matches = (aa->tm_year == bb->tm_year &&
                        aa->tm_mon == bb->tm_mon &&
                        aa->tm_mday == aa->tm_mday);
                break;
        case ANALYSIS_RANGE_MONTH:
                matches = (aa->tm_year == bb->tm_year &&
                        aa->tm_mon == bb->tm_mon);
                break;
        case ANALYSIS_RANGE_YEAR:
                matches = (aa->tm_year == bb->tm_year);
                break;
        }
        return matches;
}

void G6067HeadOffice::addToResults(
        std::vector<AnalysisItem> &results,
        int id,
        string name,
        int qty,
        double price) {
        /* if this id already exists in vector add to it */
        /* otherwise push a new item*/
        bool exists = false;
        for (int ii = 0; ii < results.size(); ii++) {
                if (results[ii].getId() == id) {
                        exists = true;
                        results[ii].setQuantity(
                                results[ii].getQuantity() + qty);
                        results[ii].setPrice(
                                results[ii].getPrice() + price);
                        // and break out of loop
                        break;
                }
        }
        if (!exists) {
                AnalysisItem ai(id, name, qty, price);
                results.push_back(ai);
        }
        return;
}

string G6067HeadOffice::processResults(
        int type,
        std::vector<AnalysisItem> results) {
        std::ostringstream ss;
        string hdr = "";
        string ul = "";
        int maxl = 0;
        switch (type) {
        case ANALYSIS_TYPE_CATEGORY:
                hdr = "Category";
                maxl = MAX_CATEGORY_LEN;
                break;
        case ANALYSIS_TYPE_ITEM:
                hdr = "Menu Item";
                maxl = MAX_MENU_ITEM_LEN;
                break;
        }
        ul.append(maxl, '=');
        hdr.append(maxl - hdr.length() + 1, ' ');
        /* process results */
        ss << hdr
                << "Qty    "
                << "Price    "
                << std::endl;
        ss << ul << " "
                << "====== "
                << "======== "
                << std::endl;
        for (unsigned ii = 0; ii < results.size(); ii++) {
                AnalysisItem ai = results[ii];

                string padded = Item::padString(ai.getName(), maxl, ' ');
                ss << padded << " "
                        << std::internal << std::setfill(' ')
                        << std::setw(6) << ai.getQuantity()
                        << Item::rightJustifyDouble(ai.getPrice(), 8)
                        << std::endl;
        }
        return ss.str();
}