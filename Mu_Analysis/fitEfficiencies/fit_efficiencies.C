#include "fittingRoutine.h"
#include <iostream>

void fit_efficiencies(){
    TString filePath = "../computeL1XE30Efficiency/EfficiencyFits.root";
    std::cout << "Entered fit_Efficiencies\n" << std::endl;
    //try{
        std::cout << "Entered initialization of MyFittingRoutine\n" << std::endl;
        FittingRoutine* MyFittingRoutine = new FittingRoutine();
    //}
    //catch(...){
    //    std::cout << "Failed to initialize the fittingroutine object" << std::endl;
    //}
    try{
        std::cout << "Entered get TEfficiency objects\n" << std::endl;
        MyFittingRoutine->getTEfficiencyObjects( filePath );
    }
    catch(...){
        std::cout << "Failed to get the tefficiency objects from: " << filePath << std::endl;
    }
    try{
        std::cout << "Entered fit efficiencies \n" << std::endl;
        MyFittingRoutine->fit_efficiencies();
    }
    catch(...){
        std::cout << "Something failed inside fit_efficiencies" << std::endl;
    }
    try{
        std::cout << "Entered Write fits to file \n" << std::endl;
        MyFittingRoutine->writeFitsToFile();
    }
    catch(...) {
        std::cout << "Failed to write new TF1 fits to file" << std::endl;
    }

}

