#include "Efficiency_Library.h"

void Single_Frac_Steerer(){
    TString AlgAName("metcell");
    TString AlgBName("metmht");

    userInfo* parameters = new userInfo();
    parameters->Set_AlgAName( AlgAName );
    parameters->Set_AlgBName( AlgBName );
    parameters->Read_Parameter_File( "parameter_files/HLTAnalysisParameters.txt" );

    TString zbfilename = parameters->Get_ThreshFileName();

    TString zbfilepath = "../../ATLAS_DATA/ZeroBiasL1KF2016R307195R311481.51Runs.root";

    TFile* zeroBiasFile = TFile::Open( zbfilepath , "READ" );
    TTree* zeroBiasTree = (TTree*)zeroBiasFile->Get("tree");
    Int_t zerobiasNentries = zeroBiasTree->GetEntries();
    parameters->Set_PassnoalgNentries( zerobiasNentries );
    Float_t passrndmcut = parameters->Get_Passrndmcut();

 

    TString xlabel = "MET [GeV]";
    TString yaxis = "Events";
    Int_t nbins = parameters->Get_Nbins();
    Double_t metMin = parameters->Get_MetMin();
    Double_t metMax = parameters->Get_MetMax();
    Int_t NumbRndmProcess1 = 0; Int_t counter1 = 0; Int_t counter2 = 0; Int_t counter3 = 0;
    Int_t passrndm, numPassMuon,passmuon,passmuvarmed,cleanCutsFlag,recalBrokeFlag;
    Float_t algAMET,algBMET,metoffrecal,mexoffrecal,meyoffrecal,mexoffrecalmuon, zb_actint,
            meyoffrecalmuon, metl1,metcell,metrefmuon,mexrefmuon,meyrefmuon,metoffrecalmuon;
    Float_t algBMETx2thresh,algBMETx1thresh;

    zeroBiasTree->SetBranchAddress("passrndm", &passrndm);
    zeroBiasTree->SetBranchAddress(AlgAName,&algAMET);
    zeroBiasTree->SetBranchAddress(AlgBName,&algBMET);

    TH1F *algAMETHist = new TH1F(AlgAName, "algA", nbins, metMin, metMax);
    TH1F *algBMETHist = new TH1F(AlgBName, "algB", nbins, metMin, metMax);

    Int_t numPassnoalgPassProcess1AlgA = 0;

    Float_t returns = Efficiency_Lib::determineZeroBiasThresh( parameters, true );


    std::cout << "Returned to threeEfficiencies.C" << std::endl;

    NumbRndmProcess1 = 0 ;
	for (Int_t k = 0; k < zerobiasNentries; k++)
	{
	    zeroBiasTree->GetEntry(k);
        Bool_t isPassrndm = passrndm > passrndmcut;

	    if ( isPassrndm )
        {
    		algAMETHist->Fill(algAMET);
    		algBMETHist->Fill(algBMET);
            NumbRndmProcess1++;
	    }
	}

    parameters->Set_NumPassNoAlgPassProcess1(NumbRndmProcess1);

    const Int_t N_SOLNS = 10;

    Float_t AlgAInputArray[N_SOLNS] = {.0,.10,.20,.30,.40,.50,.60,.70,.80,.90};
    Float_t AlgBOutputArray[N_SOLNS];


    for ( int i = 0 ; i < N_SOLNS ; i++ )
    {

            Efficiency_Lib::bisection_one_frac_fixed( AlgAInputArray[i]  ,parameters , algAMETHist , algBMETHist, zeroBiasTree ); 

    }





}

