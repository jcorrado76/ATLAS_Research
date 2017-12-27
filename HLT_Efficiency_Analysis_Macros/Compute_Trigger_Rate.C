#include"mincerMacros.h"

int Compute_Trigger_Rate(){

    //GLOBAL DEFINITION
    userInfo* parameters = new userInfo();
    parameters->Read_Parameter_File("./parameters.txt");
    TString zerobiasFileName = parameters->Get_ThreshFileName();
    
    //ZBTREE
    TString zerobiasFilePath = "../myData/"+ zerobiasFileName;
    TFile * zeroBiasFile = TFile::Open(zerobiasFilePath, "READ");
    TTree* zeroBiasTree = (TTree*)zeroBiasFile->Get("tree");
    Int_t zerobiasNentries = zeroBiasTree->GetEntries();


    int passrndm;
    float metl1;

    zeroBiasTree->SetBranchAddress("passrndm",&passrndm);
    zeroBiasTree->SetBranchAddress("metl1",&metl1);

    TH1D* MetL1Hist = new TH1D("h1","Process 2 Histogram", 1200, 0.,300.);
    TH1D* RandomHist = new TH1D("h2","Process 1 Histogram", 1200, 0.,300.);


    for ( int i = 0 ; i < zerobiasNentries ; i++ ){
        zeroBiasTree->GetEntry(i);
        if ( passrndm > 0.5 ){
            RandomHist->Fill( metl1 );
        }
    }

    std::cout << "Number of random (process 1) entries: " << RandomHist->GetEntries() << std::endl;

    for ( int j = 0 ; j < zerobiasNentries ; j++ ){
        zeroBiasTree->GetEntry(j);
        if ( passrndm > 0.5 && metl1 > 50.0 ){
            MetL1Hist->Fill( metl1 );
        }
    }

    std::cout << "Number of metl1 > 50.0 ( process 2 ) entries: " << MetL1Hist->GetEntries() << std::endl;

    std::cout << "Trigger rate = ( numb kept process 1 ) / ( numb kept process 2 ): " << ((MetL1Hist->GetEntries())/(RandomHist->GetEntries())) << std::endl;

    return 0;
}
