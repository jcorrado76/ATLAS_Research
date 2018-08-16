#define CorrectingDistributions_cxx
#include "CorrectingDistributions.h"

void CorrectingDistributions::Begin(TTree * /*tree*/)
{
    TString option = GetOption();

    // TH1 OBJECTS DO NOT BELONG TO TFILE SCOPE. THEY WILL STAY
    TH1::AddDirectory(false);

    // GET EFFICIENCY OBJECTS FROM FILE 
    mu_analysis_file = TFile::Open("../Root_Files/mu_analysis.root","UPDATE");
    mu_analysis_file->Print();
    if (mu_analysis_file->IsZombie()){
        printf("mu_analysis.root not opened");
        return;
    }
    TDirectory* efficiency_dir = mu_analysis_file->GetDirectory("efficiency_curves");
    efficiency_dir->GetObject("metmu0thru10Efficiency",efficiencyObjectMu0thru10);
    efficiency_dir->GetObject("metmu10thru20Efficiency",efficiencyObjectMu10thru20);
    efficiency_dir->GetObject("metmu20thru30Efficiency",efficiencyObjectMu20thru30);
    efficiency_dir->GetObject("metmu30thru40Efficiency",efficiencyObjectMu30thru40);
    efficiency_dir->GetObject("metmu40thru50Efficiency",efficiencyObjectMu40thru50);
    efficiency_dir->GetObject("metmu50thru60Efficiency",efficiencyObjectMu50thru60);
    efficiency_dir->GetObject("metmu60thru70Efficiency",efficiencyObjectMu60thru70);

    EfficiencyFitMuBin1 = (TF1*)((efficiencyObjectMu0thru10->GetListOfFunctions())->At(0));
    EfficiencyFitMuBin2 = (TF1*)((efficiencyObjectMu10thru20->GetListOfFunctions())->At(0));
    EfficiencyFitMuBin3 = (TF1*)((efficiencyObjectMu20thru30->GetListOfFunctions())->At(0));
    EfficiencyFitMuBin4 = (TF1*)((efficiencyObjectMu30thru40->GetListOfFunctions())->At(0));
    EfficiencyFitMuBin5 = (TF1*)((efficiencyObjectMu40thru50->GetListOfFunctions())->At(0));
    EfficiencyFitMuBin6 = (TF1*)((efficiencyObjectMu50thru60->GetListOfFunctions())->At(0));
    EfficiencyFitMuBin7 = (TF1*)((efficiencyObjectMu60thru70->GetListOfFunctions())->At(0));

    TDirectory* met_dir = mu_analysis_file->GetDirectory("zb_met");
    met_dir->GetObject("metmu0thru10",zbMETMuBin0thru10);
    met_dir->GetObject("metmu10thru20",zbMETMuBin10thru20);
    met_dir->GetObject("metmu20thru30",zbMETMuBin20thru30);
    met_dir->GetObject("metmu30thru40",zbMETMuBin30thru40);
    met_dir->GetObject("metmu40thru50",zbMETMuBin40thru50);
    met_dir->GetObject("metmu50thru60",zbMETMuBin50thru60);
    met_dir->GetObject("metmu60thru70",zbMETMuBin60thru70);

    MET_Correctedmu0thru10 = new TH1F("correctedmetmu0thru10","Corrected Data for actint between 0 and 10", nbins , gevLow , gevHigh );
    MET_Correctedmu10thru20 = new TH1F("correctedmetmu10thru20","Corrected Data for actint between 10 and 20", nbins , gevLow , gevHigh );
    MET_Correctedmu20thru30 = new TH1F("correctedmetmu20thru30","Corrected Data for actint between 20 and 30", nbins , gevLow , gevHigh );
    MET_Correctedmu30thru40 = new TH1F("correctedmetmu30thru40","Corrected Data for actint between 30 to 40", nbins , gevLow , gevHigh );
    MET_Correctedmu40thru50 = new TH1F("correctedmetmu40thru50","Corrected Data for actint between 40 to 50", nbins , gevLow , gevHigh );
    MET_Correctedmu50thru60 = new TH1F("correctedmetmu50thru60","Corrected Data for actint between 50 and 60", nbins , gevLow , gevHigh );
    MET_Correctedmu60thru70 = new TH1F("correctedmetmu60thru70","Corrected Data for actint between 60 and 70", nbins , gevLow , gevHigh );

}


Bool_t CorrectingDistributions::Process(Long64_t entry)
{
   fReader.SetLocalEntry(entry);

   // just make sure this is the correct flag L1XE30
   // still need to compute new error and pass it to this fill function somehow 

   // if the entry is passnoalg L1XE30, and it one of the good runs
   if ( isPassnoAlgL1XE30() && isGoodRun() ){
       if ( inMuRange( 0.0 , 10.0) ){
           MET_Correctedmu0thru10->Fill(*cell_met, ComputeWeight(EfficiencyFitMuBin1));
       }
       if ( inMuRange( 10.0, 20.0) ){
           MET_Correctedmu10thru20->Fill(*cell_met,ComputeWeight( EfficiencyFitMuBin2));
       }
       if ( inMuRange( 20.0 , 30.0) ){
           MET_Correctedmu20thru30->Fill(*cell_met,ComputeWeight(EfficiencyFitMuBin3));
       }
       if ( inMuRange( 30.0, 40.0) ){
           MET_Correctedmu30thru40->Fill(*cell_met,ComputeWeight(EfficiencyFitMuBin4));
       }
       if ( inMuRange( 40.0 , 50.0 ) ){
           MET_Correctedmu40thru50->Fill(*cell_met,ComputeWeight(EfficiencyFitMuBin5));
       }
       if ( inMuRange( 50.0 , 60.0 ) ){
           MET_Correctedmu50thru60->Fill(*cell_met,ComputeWeight(EfficiencyFitMuBin6));
       }
       if ( inMuRange( 60.0 , 70.0 ) ){
           MET_Correctedmu60thru70->Fill(*cell_met,ComputeWeight(EfficiencyFitMuBin7));
       }
   }

   return kTRUE;
}
Double_t CorrectingDistributions::ComputeWeight(TF1* fitFunc)//{{{
{
    Float_t numerator = *HLT_noalg_L1XE30_prescale;
    Double_t denominator = fitFunc->Eval( *cell_met ); 
    return numerator / denominator; 
}//}}}
void CorrectingDistributions::SlaveTerminate(){}
void CorrectingDistributions::Terminate(){

    // normalize to 1 {{{
    MET_Correctedmu0thru10->SetNormFactor(1.);
    MET_Correctedmu10thru20->SetNormFactor(1.);
    MET_Correctedmu20thru30->SetNormFactor(1.);
    MET_Correctedmu30thru40->SetNormFactor(1.);
    MET_Correctedmu40thru50->SetNormFactor(1.);
    MET_Correctedmu50thru60->SetNormFactor(1.);
    MET_Correctedmu60thru70->SetNormFactor(1.);
    zbMETMuBin0thru10->SetNormFactor(1.);
    zbMETMuBin10thru20->SetNormFactor(1.);
    zbMETMuBin20thru30->SetNormFactor(1.);
    zbMETMuBin30thru40->SetNormFactor(1.);
    zbMETMuBin40thru50->SetNormFactor(1.);
    zbMETMuBin50thru60->SetNormFactor(1.);
    zbMETMuBin60thru70->SetNormFactor(1.);
    //}}}

    // plot corrected distributions {{{
    TCanvas* correctedCanvas = new TCanvas("correctedCanvas","Canvas with corrected data");
    MET_Correctedmu0thru10->SetLineColor(2);
    MET_Correctedmu10thru20->SetLineColor(3);
    MET_Correctedmu20thru30->SetLineColor(4);
    MET_Correctedmu30thru40->SetLineColor(44);
    MET_Correctedmu40thru50->SetLineColor(6);
    MET_Correctedmu50thru60->SetLineColor(7);
    MET_Correctedmu60thru70->SetLineColor(8);
	TLegend* correctedLegend = new TLegend();
	correctedLegend->AddEntry(MET_Correctedmu0thru10);
	correctedLegend->AddEntry(MET_Correctedmu10thru20);
	correctedLegend->AddEntry(MET_Correctedmu20thru30);
	correctedLegend->AddEntry(MET_Correctedmu30thru40);
	correctedLegend->AddEntry(MET_Correctedmu40thru50);
	correctedLegend->AddEntry(MET_Correctedmu50thru60);
	correctedLegend->AddEntry(MET_Correctedmu60thru70);

    MET_Correctedmu0thru10->Draw();
    MET_Correctedmu10thru20->Draw("SAME");
    MET_Correctedmu20thru30->Draw("SAME");
    MET_Correctedmu30thru40->Draw("SAME");
    MET_Correctedmu40thru50->Draw("SAME");
    MET_Correctedmu50thru60->Draw("SAME");
    MET_Correctedmu60thru70->Draw("SAME");
	correctedLegend->Draw("SAME");
    correctedCanvas->SetLogy();
    //}}}

	// PLOT ZERO BIAS DISTRIBUTIONS {{{
	TCanvas* zb_MET_Canvas = new TCanvas("zbCanvas","Canvas with zerobias data");
    zbMETMuBin0thru10->SetLineColor(2);
    zbMETMuBin10thru20->SetLineColor(3);
    zbMETMuBin20thru30->SetLineColor(4);
    zbMETMuBin30thru40->SetLineColor(44);
    zbMETMuBin40thru50->SetLineColor(6);
    zbMETMuBin50thru60->SetLineColor(7);
    zbMETMuBin60thru70->SetLineColor(8);
    zbMETMuBin0thru10->Draw();
    zbMETMuBin10thru20->Draw("SAME");
    zbMETMuBin20thru30->Draw("SAME");
    zbMETMuBin30thru40->Draw("SAME");
    zbMETMuBin40thru50->Draw("SAME");
    zbMETMuBin50thru60->Draw("SAME");
    zbMETMuBin60thru70->Draw("SAME");
    TLegend* zbDistLegend = new TLegend();
    zbDistLegend->AddEntry(zbMETMuBin0thru10);
    zbDistLegend->AddEntry(zbMETMuBin10thru20);
    zbDistLegend->AddEntry(zbMETMuBin20thru30);
    zbDistLegend->AddEntry(zbMETMuBin30thru40);
    zbDistLegend->AddEntry(zbMETMuBin40thru50);
    zbDistLegend->AddEntry(zbMETMuBin50thru60);
    zbDistLegend->AddEntry(zbMETMuBin60thru70);
    zbDistLegend->Draw("SAME");
    zb_MET_Canvas->SetLogy();
    //}}}

    // PLOT CORRECTED MET WITH THE ZB MET {{{
    TCanvas* c1 = new TCanvas("c1","metmubin1");
    MET_Correctedmu0thru10->Draw();
    zbMETMuBin0thru10->Draw("SAME");
    TCanvas* c2 = new TCanvas("c2","metmubin2");
    MET_Correctedmu10thru20->Draw();
    zbMETMuBin10thru20->Draw("SAME");
    TCanvas* c3 = new TCanvas("c3","metmubin3");
    MET_Correctedmu20thru30->Draw();
    zbMETMuBin20thru30->Draw("SAME");
    TCanvas* c4 = new TCanvas("c4","metmubin4");
    MET_Correctedmu30thru40->Draw();
    zbMETMuBin30thru40->Draw("SAME");
    TCanvas* c5 = new TCanvas("c5","metmubin5");
    MET_Correctedmu40thru50->Draw();
    zbMETMuBin40thru50->Draw("SAME");
    TCanvas* c6 = new TCanvas("c6","metmubin6");
    MET_Correctedmu50thru60->Draw();
    zbMETMuBin50thru60->Draw("SAME");
    TCanvas* c7 = new TCanvas("c7","metmubin7");
    MET_Correctedmu60thru70->Draw();
    zbMETMuBin60thru70->Draw("SAME");
    //}}}

    TDirectory* corrected_met_distributions = mu_analysis_file->GetDirectory("corrected_met");
    if (!corrected_met_distributions){
        std::cout << "Corrected MET dist directory did not already exist. creating new one" << std::endl;
        corrected_met_distributions = mu_analysis_file->mkdir("corrected_met");
    }
    if (corrected_met_distributions->cd()){
        std::cout << "Successfully switched to correcting met distributions directory" << std::endl;
    }
    MET_Correctedmu0thru10->Write();
    MET_Correctedmu10thru20->Write();
    MET_Correctedmu20thru30->Write();
    MET_Correctedmu30thru40->Write();
    MET_Correctedmu40thru50->Write();
    MET_Correctedmu50thru60->Write();
    MET_Correctedmu60thru70->Write();
    mu_analysis_file->Close();
}
void CorrectingDistributions::Init(TTree *tree){fReader.SetTree(tree);}
void CorrectingDistributions::SlaveBegin(TTree * /*tree*/)//{{{
{
   TString option = GetOption();
}//}}}
Bool_t CorrectingDistributions::Notify(){return kTRUE;}
Bool_t CorrectingDistributions::isGoodRun(){//{{{
    return (*RunNumber != 330203 && *RunNumber != 331975 && *RunNumber != 334487);
}//}}}
Bool_t CorrectingDistributions::passedL1ZB(){//{{{
    return (*HLT_noalg_zb_L1ZB_passed);
}//}}}
Bool_t CorrectingDistributions::inMuRange( Float_t a , Float_t b ){ //{{{
    return ( *InTimePileup > a && *InTimePileup < b );
} //}}}
Bool_t CorrectingDistributions::isPassnoAlgL1XE30(){ // {{{
    return (*HLT_noalg_L1XE30_passed);
} // }}}
