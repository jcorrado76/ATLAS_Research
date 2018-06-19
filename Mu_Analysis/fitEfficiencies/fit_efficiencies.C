#include "fittingRoutine.h"

{
    TString filePath = "../computeL1XE30Efficiency/EfficiencyFits.root";
    
    FittingRoutine* MyFittingRoutine = new FittingRoutine();
    MyFittingRoutine->getTEfficiencyObjects( filePath );
    MyFittingRoutine->fit_efficiencies();
    MyFittingRoutine->writeFitsToFile();

}

