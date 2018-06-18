#include "fittingRoutine.h"

{
    TString filePath = "";
    
    FittingRoutine* MyFittingRoutine = new FittingRoutine();
    MyFittingRoutine->getTEfficiencyArray( filePath );
    MyFittingRoutine->fit_efficiencies();
    MyFittingRoutine->writeFitsToFile();

}

