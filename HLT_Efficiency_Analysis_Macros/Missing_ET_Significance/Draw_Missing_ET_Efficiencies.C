#define Draw_Missing_ET_Efficiencies_cxx
#include "Draw_Missing_ET_Efficiencies.h"
#include <TH2.h>
#include <TStyle.h>

/*
 * Draw efficiency curve for algorithm A individually, for missing et significance individually, 
 * and then the efficiency curve for using both of them combined
 */

void Draw_Missing_ET_Efficiencies::Begin(TTree *){
    TString option = GetOption();

    // initialize the tefficiency objects
    Ateff  = new TEfficiency( AlgAName + "_efficiency" , astring , muonNbins, metMin, metMax);
    Bteff  = new TEfficiency( AlgBName + "_efficiency" , bstring , muonNbins, metMin, metMax);
    Cteff  = new TEfficiency( AlgCName + "_efficiency" ,  cstring , muonNbins, metMin, metMax);
}
void Draw_Missing_ET_Efficiencies::SlaveBegin(TTree *){TString option = GetOption();}
Bool_t Draw_Missing_ET_Efficiencies::Process(Long64_t entry)
{
   fReader.SetEntry(entry);
    algAmuonMET = *metcell;
    algBmuonMET = *missing_et_significance;
    muonActint = *actint;
    muonMetl1 = *metl1;

    isMuon = (*passmu26varmed > 0.1 || *passmu26med > 0.1);
    isClean = (*passcleancuts > 0.1) && ( *recalbroke < 0.1);
    passTransverseMassCut = Efficiency_Lib::passTransverseMassCut( *metoffrecal , *mexoffrecal , 
            *meyoffrecal , *metoffrecalmuon , *mexoffrecalmuon , *meyoffrecalmuon );

    if ( isMuon && isClean && passTransverseMassCut && ( muonActint > actintCut ) )
    {
        metnomu = Efficiency_Lib::computeMetNoMu(  *mexoffrecal , *meyoffrecal , *mexoffrecalmuon , *meyoffrecalmuon );
        Ateff->Fill( ( algAmuonMET > AlgAIndividThresh ) && (muonMetl1 > metl1thresh) && ( muonActint > actintCut ), metnomu );
        Bteff->Fill( ( algBmuonMET > AlgBIndividThresh ) && (muonMetl1 > metl1thresh) && ( muonActint > actintCut ), metnomu );
        Cteff->Fill( ( (algAmuonMET > CombinedThreshAlgA) && (algBmuonMET > CombinedThreshAlgB )
        && ( muonActint > actintCut ) && (muonMetl1 > metl1thresh) ), metnomu );
    }
   return kTRUE;
}
void Draw_Missing_ET_Efficiencies::SlaveTerminate(){}
void Draw_Missing_ET_Efficiencies::Terminate(){
    const TString canvName = AlgAName + " and " + AlgBName + " Combined Efficiency" + ";Offline Recalibrated MET w/o Muon term [GeV];Efficiency";
    TCanvas* efficiencyCanvas = new TCanvas("Efficiency Canvas", "Efficiency Canvas");
    efficiencyCanvas->RangeAxis(0,0,500,1.0);
    efficiencyCanvas->SetTitle(canvName);

    Ateff->SetLineColor(kBlue);
    Bteff->SetLineColor(kGreen);
    Cteff->SetLineColor(kRed);

    Ateff->Draw();
    Bteff->Draw("same");
    Cteff->Draw("same");

    TLegend *legend = new TLegend(0.57,0.15,0.9, 0.4 ,"","NDC");
    legend->AddEntry(Ateff, astring);
    legend->AddEntry(Bteff, bstring);
    legend->AddEntry(Cteff, cstring);
    legend->Draw();
}
