#include "fittingRoutine.h"
#include <iostream>

{
    TString filePath = "../computeL1XE30Efficiency/EfficiencyFits.root";
    try{
        FittingRoutine* MyFittingRoutine = new FittingRoutine();
    }
    catch(...){
        std::cout << "Failed to initialize the fittingroutine object" << std::endl;
    }
    try{
        MyFittingRoutine->getTEfficiencyObjects( filePath );
    }
    catch(...){
        std::cout << "Failed to get the tefficiency objects from: " << filePath << std::endl;
    }
    try{
        MyFittingRoutine->fit_efficiencies();
    }
    catch(...){
        std::cout << "Something failed inside fit_efficiencies" << std::endl;
    }
    try{
        MyFittingRoutine->writeFitsToFile();
    }
    catch(...) {
        std::cout << "Failed to write new TF1 fits to file" << std::endl;
    }

}

