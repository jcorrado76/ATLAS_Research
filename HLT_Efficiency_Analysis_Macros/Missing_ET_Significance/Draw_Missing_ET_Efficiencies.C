#define Draw_Missing_ET_Efficiencies_cxx
#include "Draw_Missing_ET_Efficiencies.h"
#include <TH2.h>
#include <TStyle.h>

void Draw_Missing_ET_Efficiencies::Begin(TTree *){
    TString option = GetOption();

    // initialize the tefficiency objects
    Ateff  = new TEfficiency( AlgAName + "_efficiency" , astring , muonNbins, metMin, metMax);
    Bteff  = new TEfficiency( AlgBName + "_efficiency" , bstring , muonNbins, metMin, metMax);
    Cteff  = new TEfficiency( CName ,  cstring , muonNbins, metMin, metMax);
}
void Draw_Missing_ET_Efficiencies::SlaveBegin(TTree *){TString option = GetOption();}
Bool_t Draw_Missing_ET_Efficiencies::Process(Long64_t entry)
{
   fReader.SetEntry(entry);
    myMuonTree->SetBranchAddress(AlgAName,&algAmuonMET);
    myMuonTree->SetBranchAddress(AlgBName,&algBmuonMET);

    isMuon = (*passmu26varmed > 0.1 || *passmu26med > 0.1);
    isClean = (*passcleancuts > 0.1) && ( *recalbroke < 0.1);
    passTransverseMassCut = Efficiency_Lib::passTransverseMassCut( *metoffrecal , *mexoffrecal , *meyoffrecal , *metoffrecalmuon , *mexoffrecalmuon , *meyoffrecalmuon );

    if ( isMuon && isClean && ( muonActint > actintCut ))
    {
        if ( Efficiency_Lib::passTransverseMassCut(metoffrecal,mexoffrecal,meyoffrecal,metoffrecalmuon,mexoffrecalmuon,meyoffrecalmuon) )
        {
            Float_t metnomu = Efficiency_Lib::computeMetNoMu(  mexoffrecal , meyoffrecal , mexoffrecalmuon , meyoffrecalmuon );
    Ateff->Fill( (algAmuonMET > AlgAIndividThresh ) && (muonMetl1 > metl1thresh) && ( muonActint > actintCut ), metnomu );
    Bteff->Fill( (algBmuonMET > AlgBIndividThresh ) && (muonMetl1 > metl1thresh) && ( muonActint > actintCut ), metnomu );
    Cteff->Fill( ( (algAmuonMET > CombinedThreshAlgA) && (algBmuonMET > CombinedThreshAlgB )
    && ( muonActint > actintCut ) && (muonMetl1 > metl1thresh) ), metnomu );
   return kTRUE;
}
void Draw_Missing_ET_Efficiencies::SlaveTerminate(){}
void Draw_Missing_ET_Efficiencies::Terminate(){}
