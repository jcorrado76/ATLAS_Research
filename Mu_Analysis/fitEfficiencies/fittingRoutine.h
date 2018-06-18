#ifndef FITTING_ROUTINE_H
#define FITTING_ROUTINE_H

#include <TFile.h>
#include <TF1.h>
#include <TEfficiency.h>
#include <TClonesArray.h>

class FittingRoutine{
    private:
        TFile* EfficiencyFile = 0;
        TFile* FitFile = 0;
        TClonesArray* EfficiencyArray = 0;
        TClonesArray* FitArray = 0;

    public:
        Double_t fit( Double_t *x , Double_t *par );
        TF1* generateFitFunction();
        void fit_efficiencies();

};
#endif //FITTING_ROUTINE_
