#ifndef FITTING_ROUTINE_H
#define FITTING_ROUTINE_H

#include <TFile.h>
#include <TF1.h>
#include <TEfficiency.h>
#include <TClonesArray.h>
#include <TString.h>

class FittingRoutine{
    private:
        TFile* EfficiencyFile = 0;
        TFile* FitFile = 0;
        TClonesArray* EfficiencyArray = 0;
        TClonesArray* FitArray = 0;
        Int_t numberSlices = 0;
        Int_t sliceNdx = 0;

    public:
        Double_t fit( Double_t *x , Double_t *par );
        TF1* generateFitFunction( Int_t sliceNdx );
        void fit_efficiencies();
        void getTEfficiencyArray( TString );
        void writeFitsToFile( TString fileName = "./EfficiencyFits.root" );

};
#endif //FITTING_ROUTINE_
