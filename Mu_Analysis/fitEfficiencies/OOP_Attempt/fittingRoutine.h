#ifndef FITTING_ROUTINE_H
#define FITTING_ROUTINE_H

#include <TFile.h>
#include <TF1.h>
#include <TEfficiency.h>
#include <TClonesArray.h>
#include <TString.h>
#include <TKey.h>
#include <TClass.h>

class FittingRoutine{
    private:
        TFile* EfficiencyFile;
        TFile* FitFile;
        Int_t numberSlices;
        Int_t sliceNdx;
        TEfficiency* currTEfficiencyObj;
        TF1* currFitFunc;
        TClonesArray* TEfficiencyArray;
        TClonesArray* FitArray;

    public:
        FittingRoutine();
        ~FittingRoutine();
        Double_t fit( Double_t *x , Double_t *par );
        TF1* generateFitFunction();
        void fit_efficiencies();
        void getTEfficiencyObjects( TString filePath = "../computeL1XE30Efficiency/EfficiencyFits.root");
        void writeFitsToFile( TString fileName = "./EfficiencyFits.root" );
        static Double_t myfunction(Double_t *x , Double_t *par );
        void myfunc();
        
        ClassDef(FittingRoutine,0);
        


};
#endif //FITTING_ROUTINE_
