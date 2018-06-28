#include "fittingRoutine.h"
ClassImp(FittingRoutine);

Double_t FittingRoutine::myfunction(Double_t *x , Double_t *par ){
    Float_t xx = x[0];
    Double_t l1cut = 30.0;
    Double_t f = (1./2.)*(1.+TMath::Erf((par[0]*x[0]+par[1]-l1cut)/(par[2]*TMath::Sqrt(2.))));
    return f;
}

void FittingRoutine::myfunc()
{
   TF1 *fitErrorFunction = new TF1("myfunc",myfunction,0.0,105.0,3);
    //set the normalization to 1
    //set the x translation to 0
    //initialize sigma to 10
    fitErrorFunction->SetParameter(0, 1.);
    fitErrorFunction->SetParameter(1, 0.);
    fitErrorFunction->SetParameter(2, 10.);
    //initializing parameters reasonably is important because it is a maximum likelihood fit
    fitErrorFunction->SetParNames("Slope","Translation","Sigma");
}


TF1* FittingRoutine::generateFitFunction(){
    // initialize the TEfficiency object that will hold each TEfficiency on each iteration 
    TF1* fitErrorFunction = (TF1*)gROOT->GetFunction("myfunc");
    // get the efficiency from the tclones array
    currTEfficiencyObj = (TEfficiency*)TEfficiencyArray->ConstructedAt(sliceNdx);
    //"R" tells the fit function from BinomialEfficiency::Fit to use the range of the TF1 as the fitting range
    currTEfficiencyObj->Fit( fitErrorFunction  , "R" );

    std::cout << "Value of fit for a: " << fitErrorFunction->GetParameter(0) << std::endl;
    std::cout << "Value of error on a: " << fitErrorFunction->GetParError(0) << std::endl;
    std::cout << "Value of fit for b: " << fitErrorFunction->GetParameter(1) << std::endl;
    std::cout << "Value of error on b: " << fitErrorFunction->GetParError(1) << std::endl;
    std::cout << "Value of fit for sigma: " << fitErrorFunction->GetParameter(2) << std::endl;
    std::cout << "Value of error on sigma: " << fitErrorFunction->GetParError(2) << std::endl;
    return fitErrorFunction;
}

void FittingRoutine::fit_efficiencies(){
    printf("Number of objects in TEfficiency File: %d", numberSlices);
    TEfficiencyArray = new TClonesArray( "TEfficiency", numberSlices );
    FitArray = new TClonesArray( "TF1", numberSlices );
    for ( sliceNdx ; sliceNdx  < numberSlices ; sliceNdx++){
        printf("Current slice: %d" , sliceNdx);
        // get TEfficiency from file reading in
        currTEfficiencyObj = (TEfficiency*) TEfficiencyArray->ConstructedAt( sliceNdx );
        currFitFunc = generateFitFunction();
        // construct a fit object in output array 
        currFitFunc = (TF1*) FitArray->ConstructedAt( sliceNdx );
    }
}

void FittingRoutine::getTEfficiencyObjects( TString filePath ){
    // load TEfficiency objects into TClonesArray into memory; file path needs to be passed in from program.
    // open file READ mode 
    EfficiencyFile = TFile::Open( filePath, "READ" );
    // get the list of keys of all objects in file 
    TList* TFileKeyList = EfficiencyFile->GetListOfKeys();
    // compute how many keys in list 
    numberSlices = TFileKeyList->GetEntries();
    // create an iterator for the list
    TIter* keyIter = new TIter( TFileKeyList );
    TKey* key = 0;
    // while you can read in new keys from the iterator
    while ( (key = (TKey*) keyIter->Next()){
        // determine what the class contained in the key is 
        TClass* cl = gROOT->GetClass( key->GetClassName() );
        // if the class does not inherit from TEfficiency
        if ( !cl->InheritsFrom("TEfficiency")){
            // skip
            continue;
        }

        // get the pointer to tefficiency from key
        TEfficiency* teff = (TEfficiency*)key->ReadObj();
        // print the name of current tefficiency object for sanity check
        printf("TEfficiency Read: %s", teff->GetName());

        // push back to tclonesarray
        teff = (TEfficiency*) TEfficiencyArray->ConstructedAt(i);
    }

    // close the file
    EfficiencyFile->Close();

}

void FittingRoutine::writeFitsToFile( TString fileName ){
    FitFile = TFile::Open( fileName, "RECREATE" );
    // this will write each object separately to file
    FitArray->Write();
    FitFile->Close();
}

FittingRoutine::FittingRoutine()
    :EfficiencyFile(0),FitFile(0), TEfficiencyArray(0),FitArray(0), numberSlices(0), sliceNdx(0), currTEfficiencyObj(0), currFitFunc(0)
{}

FittingRoutine::~FittingRoutine(){}
