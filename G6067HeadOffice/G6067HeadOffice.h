#pragma once

#define ANALYSIS_RANGE_TODAY 1
#define ANALYSIS_RANGE_MONTH 2
#define ANALYSIS_RANGE_YEAR  3

#define ANALYSIS_TYPE_CATEGORY 1
#define ANALYSIS_TYPE_ITEM     2

#include <fstream>
#include <ios>
#include <iomanip>

#include "G6067Input.h"
#include "AnalysisItem.h"

class G6067HeadOffice : public G6067Input {
public:
        G6067HeadOffice();
        ~G6067HeadOffice();

        bool run();

        bool displayView(Lists*);
        bool processAnalysisType(Lists*);
        bool processAnalysisRange(int, Lists*);
        void displayRangeMenu(string prompt);

        void analyzeData(int analysisType, int analysisRange, 
                Lists* data);
        void analyzeBy(int type, int range, Lists* data);
        string analyze(int type, int range, Lists* data);
        bool dateMatches(int range, std::tm *aa, std::tm *bb);

        void addToResults(
                std::vector<AnalysisItem> &,
                int,
                string,
                int,
                double);
        string processResults(int, std::vector<AnalysisItem> results);
};
