#include "TROOT.h"
#include <iostream>

Int_t logFilePractice()
{
    /* This macro will show the correct syntax for creating a logfile 
     */

    gROOT->ProcessLine(".> ./TEfficienciesPics/newLogFile.log");
    std::cout << "using algorithm METCELL" << std::endl;
    std::cout << "Threshold: " << 24.5 << std::endl;
    gROOT->ProcessLine(".>");
    return(0);
}
