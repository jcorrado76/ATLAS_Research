#include "userInfo.h"
ClassImp(userInfo)

TString zerobiasFileName = "PhysicsMain.All.noalgXEtriggers.2016.f731f758._m1659m1710.48Runs.root";
TString muonFilename = "PhysicsMain.L1KFmuontriggers.2016.f731f758_m1659m1710.Run309759.48Runs.root";
Int_t Nbins = 1200;
Float_t metMin = 0.0;
Float_t metMax = 300.0;
Float_t metl1Thresh = 50.0;
Float_t Frac = 0.0059;
Float_t actinTCut = 35.0;
Int_t epson = 25;
Int_t numbtokeep  = 1108;

//default constructor
userInfo::userInfo():
    nbins(Nbins),
    metmin(metMin),
    metmax(metMax),
    metl1thresh(metl1Thresh),
    frac(Frac),
    passNoAlgFile(zerobiasFileName),
    muonFileName(muonFilename),
    actintCut(actinTCut),
    epsilon(epson),
    NumPassnoalgPassProcess1(0),
    NumMuonPassProcess1(0),
    NumPassnoalgProcess2AlgA(0),
    NumPassnoalgProcess2AlgB(0),
    NumPassnoalgProcess2AlgCombined(0),
    NumMuonPassProcess2AlgA(0),
    NumMuonPassProcess2AlgB(0),
    NumMuonPassProcess2Combined(0),
    algAIndividThresh(0),
    algBIndividThresh(0),
    algACombinedThresh(0),
    algBCombinedThresh(0),
    algAName(" [not entered yet] "),
    algBName(" [not entered yet] "),
    muonNentries(0),
    passnoAlgNentries(0),
    numMuonKeptCombined(0),
    numMuonDenominator(0),
    now(TDatime()),
    numberEventsToKeep(numbtokeep){}

void userInfo::Print(Option_t *option) const{
    std::cout << "Printing the data members for the userInfo struct: \n" << std::endl;

    now.Print();
    std::cout << "Alg A Name: " << algAName << std::endl;
    std::cout << "Alg B Name: " << algBName << std::endl;
    std::cout << "nbins: " << nbins << std::endl;
    std::cout << "MetMin: " << metmin << std::endl;
    std::cout << "MetMax: " << metmax << std::endl;
    std::cout << "METL1 thresh used: " << metl1thresh << std::endl;
    std::cout << "Process 2 target frac: " << frac << std::endl;
    std::cout << "Passnoalg File: " << passNoAlgFile << std::endl;
    std::cout << "Muon File: " << muonFileName << std::endl;
    std::cout << "Number of passnoalg events that passed process1: " << NumPassnoalgPassProcess1 << std::endl;
    std::cout << "Numb passnoalg passed process2 for alg A: " << NumPassnoalgProcess2AlgA << std::endl;
    std::cout << "Numb passnoalg passed process2 for alg B: " << NumPassnoalgProcess2AlgB << std::endl;
    std::cout << "Numb passnoalg passed process2 for combined alg: " << NumPassnoalgProcess2AlgCombined << std::endl;

    std::cout << "Thresholds needed to keep trigger rate individually: " << std::endl;
    std::cout << "Individ Threshold needed on " + algAName + ": " << algAIndividThresh << std::endl;
    std::cout << "Individ Threshold needed on " + algBName + ": " << algBIndividThresh << std::endl;
    std::cout << "\nThresholds needed to keep the proper trigger rate when combined: " << std::endl;
    std::cout << "Combined Threshold needed on " + algAName + ": " << algACombinedThresh << std::endl;
    std::cout << "Combined Threshold needed on " + algBName + ": " << algBCombinedThresh << std::endl;
    std::cout << "Muon Nentries: " << muonNentries << std::endl;
    std::cout << "Passnoalg Nentries: " << passnoAlgNentries << std::endl;
    std::cout << "Number of entries kept using combined thresholds: " <<  numMuonKeptCombined << std::endl;
    std::cout << "Numb passed process 2 for " + algAName + " separately: "
    << NumMuonPassProcess2AlgA << std::endl;
    std::cout << "Numb passed process 2 for " + algBName + " separately: "
    << NumMuonPassProcess2AlgB << std::endl;
    std::cout << "Numb passed process 2 Combined: "
    << NumMuonPassProcess2Combined << std::endl;
    std::cout << "Nentries Efficiency Denominator: " << numMuonDenominator << std::endl;
    std::cout << "Epsilon tolerance on number events used for bisection: " << epsilon << std::endl;
    std::cout << "Actint cut: " << actintCut << "\n" << std::endl;

}


//getters
Int_t userInfo::Get_Nbins() const { return(nbins); }
Float_t userInfo::Get_MetL1Thresh() const { return( metl1thresh); }
Float_t userInfo::Get_ActintCut() const { return( actintCut);}
Float_t userInfo::Get_Frac() const { return (frac); }
Float_t userInfo::Get_MetMin() const {return (metmin);}
Float_t userInfo::Get_MetMax() const { return (metmax);}
Int_t userInfo::Get_Epsilon() const {return(epsilon);}
TDatime userInfo::Get_Date() const { now.Print();return(now);}
TString userInfo::Get_AlgAName() const { return (algAName);}
TString userInfo::Get_AlgBName() const { return (algBName);}
Int_t userInfo::Get_MuonNentries() const { return(muonNentries);}
Int_t userInfo::Get_ThreshNentries() const { return (passnoAlgNentries) ; }
Int_t userInfo::Get_NumberEventsToKeep() const { return (numberEventsToKeep) ;}
Float_t userInfo::Get_IndividAlgAThresh() const { return (AlgAIndividThresh);}
Float_t userInfo::Get_IndividAlgBThresh() const { return (AlgBIndividThresh);} 
TString userInfo::Get_ThreshFileName() const { return (ThreshFileName);}
TString userInfo::Get_MuonFileName() const { return(MuonFileName);}


//setters
void userInfo::Set_AlgAName( const TString algA ) { algAName = algA; };
void userInfo::Set_AlgBName( const TString algB ) { algBName = algB; };
void userInfo::Set_ThresholdFile( const TString file ) { zerobiasFileName = file; };
void userInfo::Set_MuonFile( const TString file ){ muonFilename = file;} ;
void userInfo::Set_NumPassNoAlgPassProcess1( const Float_t num ) {NumPassnoalgPassProcess1 = num;};
void userInfo::Set_NumPassNoAlgPassProcess2AlgA( const Float_t num ) {NumPassnoalgProcess2AlgA = num;};
void userInfo::Set_NumPassNoAlgPassProcess2AlgB( const Float_t num ) {NumPassnoalgProcess2AlgB = num;};
void userInfo::Set_NumPassNoAlgPassProcess2Combined( const Float_t num ) {NumPassnoalgProcess2AlgCombined = num;};
void userInfo::Set_NumMuonPassProcess2AlgA( const Float_t num ) {NumMuonPassProcess2AlgA = num;};
void userInfo::Set_NumMuonPassProcess2AlgB( const Float_t num ) {NumMuonPassProcess2AlgB = num;};
void userInfo::Set_NumMuonPassProcess2Combined( const Float_t num ) {NumMuonPassProcess2Combined = num;};
void userInfo::Set_AlgAIndividThresh( const Float_t thresh ) { algAIndividThresh = thresh; };
void userInfo::Set_AlgBIndividThresh( const Float_t thresh ) { algBIndividThresh = thresh; };
void userInfo::Set_AlgACombinedThresh( const Float_t thresh ) { algACombinedThresh = thresh; };
void userInfo::Set_AlgBCombinedThresh( const Float_t thresh ) { algBCombinedThresh = thresh; };
void userInfo::Set_MuonNentries( const Int_t num ) { muonNentries = num; };
void userInfo::Set_PassnoalgNentries( const Int_t num ) { passnoAlgNentries = num; };
void userInfo::Set_NumMuonKeptCombinedAtThresh( const Int_t num ) { numMuonKeptCombined = num; };
void userInfo::Set_NumTotal( const Int_t num ) { numMuonDenominator = num; };
void userInfo::Set_ActintCut( const Float_t thresh ) { actintCut = thresh; };
void userInfo::Set_Epsilon( const Int_t epson ) { epsilon = epson; };









