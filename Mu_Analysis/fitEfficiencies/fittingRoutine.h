
class FittingRoutine{
    private:

        TFile* EfficiencyFile = 0;
        TFile* FitFile = 0;
        TClonesArray* EfficiencyArray = 0;
        TClonesArray* FitArray = 0;

    public:

        Double_t fit( Double_t *x , Double_t *par );

        TF1* generateFitFunction();

        void fit_efficiencies(){
            // suppose there exists a root file containing a TClonesArray of Efficiency Curves
            TFile* efficiencyCurveFile = TFile::Open("efficiencyCurves.root");
            // how many efficiency curves to fit
            Int_t numberSlices = 7;
            // initialize TClonesArray to hold the efficiency curves
            TClonesArray* efficiencyArray = new TClonesArray( "TEfficiency", numberSlices );
            // initialize TClonesArray to hold the fit objects 
            TClonesArray* efficiencyFitArray = new TClonesArray( "TF1", numberSlices );

            for ( int i = 0 ; i < numberSlices ; i++){


                
            }


        }

};«»
