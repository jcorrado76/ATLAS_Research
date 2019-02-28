#define Draw_Puc_Cell_Met_Sig_Efficiencies_cxx
#include "Draw_Puc_Cell_Met_Sig_Efficiencies.h"

void Draw_Puc_Cell_Met_Sig_Efficiencies::Begin(TTree *){
    TString option = GetOption();

   puc_efficiency = new TEfficiency( AlgPucName + "_efficiency" , puc_efficiency_title , muonNbins, metMin, metMax);
   cell_efficiency = new TEfficiency( AlgCellName + "_efficiency" , cell_efficiency_title , muonNbins , metMin , metMax );
   missing_et_efficiency_one = new TEfficiency( AlgMissingEtName + "_efficiency" , met_significance_efficiency_title_one , muonNbins , metMin , metMax );
   missing_et_efficiency_two = new TEfficiency( AlgMissingEtName + "_efficiency" , met_significance_efficiency_title_two , muonNbins , metMin , metMax );
   missing_et_efficiency_three = new TEfficiency( AlgMissingEtName + "_efficiency" , met_significance_efficiency_title_three , muonNbins , metMin , metMax );
}
void Draw_Puc_Cell_Met_Sig_Efficiencies::SlaveBegin(TTree *){TString option = GetOption();}
Bool_t Draw_Puc_Cell_Met_Sig_Efficiencies::Process(Long64_t entry)
{
   fReader.SetEntry(entry);

    isMuon = (*passmu26varmed > 0.1 || *passmu26med > 0.1);
    isClean = (*passcleancuts > 0.1) && ( *recalbroke < 0.1);
    passTransverseMassCut = Efficiency_Lib::passTransverseMassCut( *metoffrecal , *mexoffrecal , *meyoffrecal , *metoffrecalmuon , *mexoffrecalmuon , *meyoffrecalmuon );

    if ( isMuon && isClean && passTransverseMassCut && ( *metl1 > metl1thresh ) && ( *actint > actintCut ) )
    {
        metnomu = Efficiency_Lib::computeMetNoMu(  *mexoffrecal , *meyoffrecal , *mexoffrecalmuon , *meyoffrecalmuon );
        cell_efficiency->Fill( ( *metcell > cell_efficiency_thresh ) && ( *metl1 > metl1thresh ) && ( *actint > actintCut ) , metnomu );
        puc_efficiency->Fill( ( *mettopoclpuc > puc_efficiency_thresh ) && ( *metl1 > metl1thresh ) && ( *actint > actintCut ) , metnomu );
        missing_et_efficiency_one->Fill( ( *missing_et_significance > met_significance_thresh_one ) && ( *metl1 > metl1thresh ) && ( *actint > actintCut ) , metnomu );
        missing_et_efficiency_two->Fill( ( *missing_et_significance > met_significance_thresh_two ) && ( *metl1 > metl1thresh ) && ( *actint > actintCut ) , metnomu );
        missing_et_efficiency_three->Fill( ( *missing_et_significance > met_significance_thresh_three ) && ( *metl1 > metl1thresh ) && ( *actint > actintCut ) , metnomu );
    }
   return kTRUE;
}
void Draw_Puc_Cell_Met_Sig_Efficiencies::SlaveTerminate(){}
void Draw_Puc_Cell_Met_Sig_Efficiencies::Terminate(){
    const TString canvName = "Efficiency of metcell, mettopoclpuc and et significance at several thresholds;Offline Recalibrated MET w/o Muon term [GeV];Efficiency";
    TCanvas* efficiencyCanvas = new TCanvas("Efficiency Canvas", "Efficiency Canvas");
    gStyle->SetOptTitle(0);
    efficiencyCanvas->RangeAxis(0,0,500,1.0);
    efficiencyCanvas->SetTitle(canvName);

    cell_efficiency->SetLineColor(kBlue);
    puc_efficiency->SetLineColor(kGreen);
    missing_et_efficiency_one->SetLineColor(kRed);
    missing_et_efficiency_two->SetLineColor(kMagenta);
    missing_et_efficiency_three->SetLineColor(kCyan);

    cell_efficiency->Draw();
    puc_efficiency->Draw("SAME");
    missing_et_efficiency_one->Draw("SAME");
    missing_et_efficiency_two->Draw("SAME");
    missing_et_efficiency_three->Draw("SAME");

    TLegend *legend = new TLegend(0.57,0.15,0.9, 0.4 ,"","NDC");
    legend->AddEntry(cell_efficiency, cell_efficiency_title);
    legend->AddEntry(puc_efficiency, puc_efficiency_title);
    legend->AddEntry(missing_et_efficiency_one, met_significance_efficiency_title_one);
    legend->AddEntry(missing_et_efficiency_two, met_significance_efficiency_title_two);
    legend->AddEntry(missing_et_efficiency_three, met_significance_efficiency_title_three);
    legend->Draw();

    TString canvas_title = "Plot of metcell, mettopoclpuc, and ETmiss at different thresholds";
    TPaveText *title  = new TPaveText(0.8,0.8,1,1);
    title->AddText( canvas_title );
    title->Draw();

    TImage *img = TImage::Create();
    img->FromPad( efficiencyCanvas );
    img->WriteImage("Missing_ET_Significance/metcell_mettopoclpuc_etmiss_3_5_7.png");
}
void Draw_Puc_Cell_Met_Sig_Efficiencies::Init(TTree *tree){fReader.SetTree(tree);}
Bool_t Draw_Puc_Cell_Met_Sig_Efficiencies::Notify(){return kTRUE;}
