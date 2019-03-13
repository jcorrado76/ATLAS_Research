#include "Parameter_Class.h"
ClassImp(userInfo)

const TString FileForThresh = "PhysicsMain.All.noalgXEtriggers.2016.f731f758._m1659m1710.48Runs.root";
//const TString FileForThresh = "ZeroBiasL1KF2016R307195R311481.51Runs.root";
const TString FileForSignal = "PhysicsMain.L1KFmuontriggers.2016.f731f758_m1659m1710.Run309759.48Runs.root";
Int_t Nbins = 1200;
Float_t metMin = 0.0;
Float_t metMax = 300.0;
//Float_t metl1Thresh = 50.0;
Float_t metl1Thresh = 0.0;
Float_t Frac = 0.0059;
//Float_t actinTCut = 35.0;
Float_t actinTCut = 0.0;
Int_t epson = 25;
//Int_t numbtokeep  = 1108;
Int_t numbtokeep  = 5600;
//Float_t passnoalgcut = 0.5;
Float_t m_passnoalgcut = 0.0;
//default constructor
userInfo::userInfo()
    :M_Nbins(Nbins),
    M_Metmin(metMin),
    M_Metmax(metMax),
    M_Metl1thresh(metl1Thresh),
    M_Frac(Frac),
    M_ThreshFileName( FileForThresh ),
    M_MuonFileName( FileForSignal ),
    M_ActintCut(actinTCut),
    M_Epsilon(epson),
    M_NumPassnoalgPassProcess1(0),
    M_NumMuonPassProcess1(0),
    M_NumPassnoalgProcess2AlgA(0),
    M_NumPassnoalgProcess2AlgB(0),
    M_NumPassnoalgProcess2AlgCombined(0),
    M_NumMuonPassProcess2AlgA(0),
    M_NumMuonPassProcess2AlgB(0),
    M_NumMuonPassProcess2Combined(0),
    M_AlgAIndividThresh(0),
    M_AlgBIndividThresh(0),
    M_AlgACombinedThresh(0),
    M_AlgBCombinedThresh(0),
    M_AlgAName(" [not entered yet] "),
    M_AlgBName(" [not entered yet] "),
    M_Name("parameters"),
    M_MuonNentries(0),
    M_PassnoAlgNentries(0),
    M_NumMuonKeptCombined(0),
    M_NumMuonDenominator(0),
    M_Now(TDatime()),
    M_Passnoalgcut(m_passnoalgcut),
    M_NumberEventsToKeep(numbtokeep),
    M_BisectionData(NULL)
{
    M_BinWidth = (metMax - metMin)/ M_Nbins;
    M_BisectionData = new TNtuple("logFileData" , "Bisection Data" ,
    "Individual Fraction:Combined Fraction: Numb Events Kept:AlgAThreshold:AlgBThreshold");
}

void userInfo::Fill_Bisection_Data(const Float_t input , const Float_t output, const Int_t numEvents,
                                   const Float_t threshA, const Float_t threshB )
{
    M_BisectionData->Fill( input , output, numEvents, threshA, threshB );
}


void userInfo::Read_Parameter_File( const TString FilePath ) {

    std::ifstream Parameter_File;
    Parameter_File.open(FilePath);
    if (!Parameter_File){
       std::cerr<<"Could not open parameter file";
    }


    std::string header1, header2,header3,FIELD,threshfile,signalfile, nbins, epsilon, numeventskeep, metmin,
        metmax, metl1thresh, actintcut,passnoalg, frac,passrndm;

    getline(Parameter_File,header1);
    getline(Parameter_File,header2);
    getline(Parameter_File,header3);

    getline(Parameter_File,FIELD);
    getline(Parameter_File,threshfile);
    getline(Parameter_File,FIELD);
    getline(Parameter_File,signalfile);
    getline(Parameter_File,FIELD);
    getline(Parameter_File,nbins);
    getline(Parameter_File,FIELD);
    getline(Parameter_File,metmin);
    getline(Parameter_File,FIELD);
    getline(Parameter_File,metmax);
    getline(Parameter_File,FIELD);
    getline(Parameter_File,metl1thresh);
    getline(Parameter_File,FIELD);
    getline(Parameter_File,frac);
    getline(Parameter_File,FIELD);
    getline(Parameter_File,actintcut);
    getline(Parameter_File,FIELD);
    getline(Parameter_File,epsilon);
    getline(Parameter_File,FIELD);
    getline(Parameter_File,numeventskeep);
    getline(Parameter_File,FIELD);
    getline(Parameter_File,passnoalg);
    getline(Parameter_File,FIELD);
    getline(Parameter_File,passrndm);

    M_ThreshFileName = threshfile;
    M_MuonFileName = signalfile;
    M_Nbins = atoi(nbins.c_str());
    M_Metmin = atof(metmin.c_str());
    M_Metmax = atof(metmax.c_str());
    M_Metl1thresh = atof(metl1thresh.c_str());
    M_Frac = atof(frac.c_str());
    M_ActintCut = atof(actintcut.c_str());
    M_Epsilon = atoi(epsilon.c_str());
    M_NumberEventsToKeep = atoi(numeventskeep.c_str());
    M_Passnoalgcut = atof(passnoalg.c_str());
    M_Passrndmcut = atof(passrndm.c_str());



}


void userInfo::Print(Option_t *option) const{
    std::cout << "Printing the data members for the userInfo struct: " << std::endl;
    M_Now.Print();
    std::cout << "ALGA: " << M_AlgAName << std::endl;
    std::cout << "ALGB: " << M_AlgBName << std::endl;
    std::cout << "NBINS: " << M_Nbins << std::endl;
    std::cout << "BINWIDTH: " << M_BinWidth << std::endl;
    std::cout << "METMIN: " << M_Metmin << std::endl;
    std::cout << "METMAX: " << M_Metmax << std::endl;
    std::cout << "PROCESS 1 L1 THRESH: " << M_Metl1thresh << std::endl;
    std::cout << "Actint cut: " << M_ActintCut << std::endl;
    std::cout << "Trigger rate: " << M_Frac << std::endl;
    std::cout << "Thresh File: " << M_ThreshFileName << std::endl;
    std::cout << "Muon File: " << M_MuonFileName << std::endl;
    std::cout << "Muon Nentries: " << M_MuonNentries << std::endl;
    std::cout << "Passnoalg Nentries: " << M_PassnoAlgNentries << std::endl;

    std::cout << "Number of passnoalg events that passed process1: " << M_NumPassnoalgPassProcess1 << std::endl;
    std::cout << "Numb passnoalg passed process2 for alg A: " << M_NumPassnoalgProcess2AlgA << std::endl;
    std::cout << "Numb passnoalg passed process2 for alg B: " << M_NumPassnoalgProcess2AlgB << std::endl;
    std::cout << "Numb passnoalg passed process2 for combined alg: " << M_NumPassnoalgProcess2AlgCombined << std::endl;

    std::cout << "Thresholds needed to keep trigger rate individually: " << std::endl;
    std::cout << "Individ Threshold needed on " + M_AlgAName + ": " << M_AlgAIndividThresh << std::endl;
    std::cout << "Individ Threshold needed on " + M_AlgBName + ": " << M_AlgBIndividThresh << std::endl;

    std::cout << "Thresholds needed to keep the proper trigger rate when combined: " << std::endl;
    std::cout << "Combined Threshold needed on " + M_AlgAName + ": " << M_AlgACombinedThresh << std::endl;
    std::cout << "Combined Threshold needed on " + M_AlgBName + ": " << M_AlgBCombinedThresh << std::endl;



    std::cout << "NIndividPassProcess2AlgA: " << M_NumMuonPassProcess2AlgA << std::endl;
    std::cout << "NIndividPassProcess2AlgB: " << M_NumMuonPassProcess2AlgB << std::endl;
    std::cout << "Numb passed process 2 Combined: "
    << M_NumMuonPassProcess2Combined << std::endl;
    std::cout << "Number muon events kept combined, as computed by external macro: " 
    <<  M_NumMuonKeptCombined << std::endl;
    std::cout << "Nentries Efficiency Denominator: " << M_NumMuonDenominator << std::endl;
    std::cout << "Epsilon tolerance on number events used for bisection: " << M_Epsilon << std::endl;


}


//getters
Int_t userInfo::Get_Nbins() const { return(M_Nbins); }
Float_t userInfo::Get_MetL1Thresh() const { return( M_Metl1thresh); }
Float_t userInfo::Get_ActintCut() const { return( M_ActintCut);}
Float_t userInfo::Get_Frac() const { return (M_Frac); }
Float_t userInfo::Get_MetMin() const {return (M_Metmin);}
Float_t userInfo::Get_MetMax() const { return (M_Metmax);}
Int_t userInfo::Get_Epsilon() const {return(M_Epsilon);}
TDatime userInfo::Get_Date() const { M_Now.Print();return(M_Now);}
TString userInfo::Get_AlgAName() const { return (M_AlgAName);}
TString userInfo::Get_AlgBName() const { return (M_AlgBName);}
Int_t userInfo::Get_MuonNentries() const { return(M_MuonNentries);}
Int_t userInfo::Get_ThreshNentries() const { return (M_PassnoAlgNentries) ; }
Int_t userInfo::Get_NumberEventsToKeep() const { return (M_NumberEventsToKeep) ;}
Float_t userInfo::Get_IndividAlgAThresh() const { return (M_AlgAIndividThresh);}
Float_t userInfo::Get_IndividAlgBThresh() const { return (M_AlgBIndividThresh);}
TString userInfo::Get_ThreshFileName() const { return (M_ThreshFileName);}
TString userInfo::Get_MuonFileName() const { return(M_MuonFileName);}
Int_t userInfo::Get_NumThreshPassProcess1() const { return (M_NumPassnoalgPassProcess1); }
Float_t userInfo::Get_BinWidth() const { return(M_BinWidth); }
Float_t userInfo::Get_CombinedAlgAThresh()  const { return (M_AlgACombinedThresh); }
Float_t userInfo::Get_CombinedAlgBThresh()  const {return (M_AlgBCombinedThresh); }
Float_t userInfo::Get_Passnoalgcut() const {return (M_Passnoalgcut);}
Float_t userInfo::Get_Passrndmcut() const { return (M_Passrndmcut);}
const char *userInfo::GetName() const { return (M_Name);}


//setters
void userInfo::Set_AlgAName( const TString algA ) { M_AlgAName = algA; };
void userInfo::Set_AlgBName( const TString algB ) { M_AlgBName = algB; };
void userInfo::Set_ThresholdFile( const TString file ) { M_ZerobiasFileName = file; };
void userInfo::Set_MuonFile( const TString file ){ M_MuonFilename = file;} ;
void userInfo::Set_NumPassNoAlgPassProcess1( const Float_t num ) {M_NumPassnoalgPassProcess1 = num;};
void userInfo::Set_NumPassNoAlgPassProcess2AlgA( const Float_t num ) {M_NumPassnoalgProcess2AlgA = num;};
void userInfo::Set_NumPassNoAlgPassProcess2AlgB( const Float_t num ) {M_NumPassnoalgProcess2AlgB = num;};
void userInfo::Set_NumPassNoAlgPassProcess2Combined( const Float_t num ) {M_NumPassnoalgProcess2AlgCombined = num;};
void userInfo::Set_NumMuonPassProcess1( const Float_t num ) {M_NumMuonPassProcess1 = num;};
void userInfo::Set_NumMuonPassProcess2AlgA( const Float_t num ) {M_NumMuonPassProcess2AlgA = num;};
void userInfo::Set_NumMuonPassProcess2AlgB( const Float_t num ) {M_NumMuonPassProcess2AlgB = num;};
void userInfo::Set_NumMuonPassProcess2Combined( const Float_t num ) {M_NumMuonPassProcess2Combined = num;};
void userInfo::Set_AlgAIndividThresh( const Float_t thresh ) { M_AlgAIndividThresh = thresh; };
void userInfo::Set_AlgBIndividThresh( const Float_t thresh ) { M_AlgBIndividThresh = thresh; };
void userInfo::Set_AlgACombinedThresh( const Float_t thresh ) { M_AlgACombinedThresh = thresh; };
void userInfo::Set_AlgBCombinedThresh( const Float_t thresh ) { M_AlgBCombinedThresh = thresh; };
void userInfo::Set_MuonNentries( const Int_t num ) { M_MuonNentries = num; };
void userInfo::Set_PassnoalgNentries( const Int_t num ) { M_PassnoAlgNentries = num; };
void userInfo::Set_NumMuonKeptCombinedAtThresh( const Int_t num ) { M_NumMuonKeptCombined = num; };
void userInfo::Set_NumTotal( const Int_t num ) { M_NumMuonDenominator = num; };
void userInfo::Set_ActintCut( const Float_t thresh ) { M_ActintCut = thresh; };
void userInfo::Set_Epsilon( const Int_t epson ) { M_Epsilon = epson; };
