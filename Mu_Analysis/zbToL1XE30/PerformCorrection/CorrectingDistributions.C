#define CorrectingDistributions_cxx
#include "CorrectingDistributions.h"

void CorrectingDistributions::Begin(TTree * /*tree*/)
{
    TString option = GetOption();

    // TH1 OBJECTS DO NOT BELONG TO TFILE SCOPE. THEY WILL STAY
    TH1::AddDirectory(false);

    // GET EFFICIENCY OBJECTS FROM FILE 
    mu_analysis_file = TFile::Open("mu_analysis.root","UPDATE");
    if (!mu_analysis_file->IsOpen()){
        std::cout << "mu_analysis.root not opened" << std::endl;
        return;
    }
    if ( mu_analysis_file->cd("l1xe30_efficiency_curves") ){
        std::cout << "Successfully switched to:" << std::endl;
        gDirectory->pwd();
        gDirectory->GetObject("metmu0thru10Efficiency",efficiencyObjectMu0thru10);
        gDirectory->GetObject("metmu10thru20Efficiency",efficiencyObjectMu10thru20);
        gDirectory->GetObject("metmu20thru30Efficiency",efficiencyObjectMu20thru30);
        gDirectory->GetObject("metmu30thru40Efficiency",efficiencyObjectMu30thru40);
        gDirectory->GetObject("metmu40thru50Efficiency",efficiencyObjectMu40thru50);
        gDirectory->GetObject("metmu50thru60Efficiency",efficiencyObjectMu50thru60);
        gDirectory->GetObject("metmu60thru70Efficiency",efficiencyObjectMu60thru70);

        EfficiencyFitMuBin1 = (TF1*)((efficiencyObjectMu0thru10->GetListOfFunctions())->At(0));
        EfficiencyFitMuBin2 = (TF1*)((efficiencyObjectMu10thru20->GetListOfFunctions())->At(0));
        EfficiencyFitMuBin3 = (TF1*)((efficiencyObjectMu20thru30->GetListOfFunctions())->At(0));
        EfficiencyFitMuBin4 = (TF1*)((efficiencyObjectMu30thru40->GetListOfFunctions())->At(0));
        EfficiencyFitMuBin5 = (TF1*)((efficiencyObjectMu40thru50->GetListOfFunctions())->At(0));
        EfficiencyFitMuBin6 = (TF1*)((efficiencyObjectMu50thru60->GetListOfFunctions())->At(0));
        EfficiencyFitMuBin7 = (TF1*)((efficiencyObjectMu60thru70->GetListOfFunctions())->At(0));
    }
    else{
        std::cout << "Unable to open efficiency_curves directory" << std::endl;
        return;
    }

    if (gDirectory->cd("../zb_met_distributions") ){
        std::cout << "Successfully switched to:" << std::endl;
        gDirectory->pwd();
        gDirectory->GetObject("metmu0thru10",zbMETMuBin0thru10);
        gDirectory->GetObject("metmu10thru20",zbMETMuBin10thru20);
        gDirectory->GetObject("metmu20thru30",zbMETMuBin20thru30);
        gDirectory->GetObject("metmu30thru40",zbMETMuBin30thru40);
        gDirectory->GetObject("metmu40thru50",zbMETMuBin40thru50);
        gDirectory->GetObject("metmu50thru60",zbMETMuBin50thru60);
        gDirectory->GetObject("metmu60thru70",zbMETMuBin60thru70);
    }
    else{
        std::cout << "Unable to open zb_met directory" << std::endl;
        return;
    }

    zbMETMuBin0thru10->SetDirectory(0);
    zbMETMuBin10thru20->SetDirectory(0);
    zbMETMuBin20thru30->SetDirectory(0);
    zbMETMuBin30thru40->SetDirectory(0);
    zbMETMuBin40thru50->SetDirectory(0);
    zbMETMuBin50thru60->SetDirectory(0);
    zbMETMuBin60thru70->SetDirectory(0);
    
    MET_Correctedmu0thru10 = new TH1D("correctedmetmu0thru10","Corrected Data for actint between 0 and 10", nbins , gevLow , gevHigh );
    MET_Correctedmu10thru20 = new TH1D("correctedmetmu10thru20","Corrected Data for actint between 10 and 20", nbins , gevLow , gevHigh );
    MET_Correctedmu20thru30 = new TH1D("correctedmetmu20thru30","Corrected Data for actint between 20 and 30", nbins , gevLow , gevHigh );
    MET_Correctedmu30thru40 = new TH1D("correctedmetmu30thru40","Corrected Data for actint between 30 to 40", nbins , gevLow , gevHigh );
    MET_Correctedmu40thru50 = new TH1D("correctedmetmu40thru50","Corrected Data for actint between 40 to 50", nbins , gevLow , gevHigh );
    MET_Correctedmu50thru60 = new TH1D("correctedmetmu50thru60","Corrected Data for actint between 50 and 60", nbins , gevLow , gevHigh );
    MET_Correctedmu60thru70 = new TH1D("correctedmetmu60thru70","Corrected Data for actint between 60 and 70", nbins , gevLow , gevHigh );

}


Bool_t CorrectingDistributions::Process(Long64_t entry)//{{{
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
}//}}}
Double_t CorrectingDistributions::ComputeWeight(TF1* fitFunc)//{{{
{
    Float_t numerator = *HLT_noalg_L1XE30_prescale;
    Double_t denominator = fitFunc->Eval( *cell_met ); 
    return numerator / denominator; 
}//}}}
void CorrectingDistributions::SlaveTerminate(){}
void CorrectingDistributions::Terminate(){
	// Relative Normalization{{{
    // BinWidth = 1.0 GeV
    Int_t normalization_bin1 = 40; // 
    Int_t normalization_bin2 = 52; //
    Int_t normalization_bin3 = 60; //
    Int_t normalization_bin4 = 56; //
    Int_t normalization_bin5 = 55; //
    Int_t normalization_bin6 = 52; //
    Int_t normalization_bin7 = 40; //
    // Scale the corrected ones to the original zb ones
    Double_t scale_factor1 = zbMETMuBin0thru10->GetBinContent( normalization_bin1 ) / MET_Correctedmu0thru10->GetBinContent( normalization_bin1 );
    std::cout << scale_factor1 << std::endl;
    Double_t scale_factor2 = zbMETMuBin10thru20->GetBinContent( normalization_bin2 ) / MET_Correctedmu10thru20->GetBinContent( normalization_bin2 );
    std::cout << scale_factor2 << std::endl;
    Double_t scale_factor3 = zbMETMuBin20thru30->GetBinContent( normalization_bin3 ) / MET_Correctedmu20thru30->GetBinContent( normalization_bin3 );
    std::cout << scale_factor3 << std::endl;
    Double_t scale_factor4 = zbMETMuBin30thru40->GetBinContent( normalization_bin4 ) / MET_Correctedmu30thru40->GetBinContent( normalization_bin4 );
    std::cout << scale_factor4 << std::endl;
    Double_t scale_factor5 = zbMETMuBin40thru50->GetBinContent( normalization_bin5 ) / MET_Correctedmu40thru50->GetBinContent( normalization_bin5 );
    std::cout << scale_factor5 << std::endl;
    Double_t scale_factor6 = zbMETMuBin50thru60->GetBinContent( normalization_bin6 ) / MET_Correctedmu50thru60->GetBinContent( normalization_bin6 );
    std::cout << scale_factor6 << std::endl;
    Double_t scale_factor7 = zbMETMuBin60thru70->GetBinContent( normalization_bin7 ) / MET_Correctedmu60thru70->GetBinContent( normalization_bin7 );
    std::cout << scale_factor7 << std::endl;

    zbMETMuBin0thru10->SetNormFactor(1.);
    zbMETMuBin10thru20->SetNormFactor(1.);
    zbMETMuBin20thru30->SetNormFactor(1.);
    zbMETMuBin30thru40->SetNormFactor(1.);
    zbMETMuBin40thru50->SetNormFactor(1.);
    zbMETMuBin50thru60->SetNormFactor(1.);
    zbMETMuBin60thru70->SetNormFactor(1.);

    MET_Correctedmu0thru10->SetNormFactor(1.);
    MET_Correctedmu10thru20->SetNormFactor(1.);
    MET_Correctedmu20thru30->SetNormFactor(1.);
    MET_Correctedmu30thru40->SetNormFactor(1.);
    MET_Correctedmu40thru50->SetNormFactor(1.);
    MET_Correctedmu50thru60->SetNormFactor(1.);
    MET_Correctedmu60thru70->SetNormFactor(1.);

    MET_Correctedmu0thru10->Scale( scale_factor1 );
    MET_Correctedmu10thru20->Scale( scale_factor2 );
    MET_Correctedmu20thru30->Scale( scale_factor3 );
    MET_Correctedmu30thru40->Scale( scale_factor4 );
    MET_Correctedmu40thru50->Scale( scale_factor5 );
    MET_Correctedmu50thru60->Scale( scale_factor6 );
    MET_Correctedmu60thru70->Scale( scale_factor7 );

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
    MET_Correctedmu0thru10->Draw();
    MET_Correctedmu10thru20->Draw("SAME");
    MET_Correctedmu20thru30->Draw("SAME");
    MET_Correctedmu30thru40->Draw("SAME");
    MET_Correctedmu40thru50->Draw("SAME");
    MET_Correctedmu50thru60->Draw("SAME");
    MET_Correctedmu60thru70->Draw("SAME");
	TLegend* correctedLegend = new TLegend(0.48,0.7,0.9,0.9);
	correctedLegend->AddEntry(MET_Correctedmu0thru10);
	correctedLegend->AddEntry(MET_Correctedmu10thru20);
	correctedLegend->AddEntry(MET_Correctedmu20thru30);
	correctedLegend->AddEntry(MET_Correctedmu30thru40);
	correctedLegend->AddEntry(MET_Correctedmu40thru50);
	correctedLegend->AddEntry(MET_Correctedmu50thru60);
	correctedLegend->AddEntry(MET_Correctedmu60thru70);
	correctedLegend->Draw("SAME");
//    correctedCanvas->SetLogy();
    gStyle->SetOptStat(0);
    correctedCanvas->Print("../Plots/CorrectedAndZB/Plot_Corrected_Distributions.png");
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
    TLegend* zbDistLegend = new TLegend(0.48,0.7,0.9,0.9);
    zbDistLegend->AddEntry(zbMETMuBin0thru10);
    zbDistLegend->AddEntry(zbMETMuBin10thru20);
    zbDistLegend->AddEntry(zbMETMuBin20thru30);
    zbDistLegend->AddEntry(zbMETMuBin30thru40);
    zbDistLegend->AddEntry(zbMETMuBin40thru50);
    zbDistLegend->AddEntry(zbMETMuBin50thru60);
    zbDistLegend->AddEntry(zbMETMuBin60thru70);
    zbDistLegend->Draw("SAME");
    zb_MET_Canvas->SetLogy();
    gStyle->SetOptStat(0);
    //zb_MET_Canvas->Print("../Plots/CorrectedAndZB/ZB_MET_Distributions.png");
    //}}}


    Double_t ymin = 0.0;
    Double_t ymax = 1.0;
    Double_t xmin = 0.0;
    Double_t xmax = 300.0;
    Double_t dy = (ymax-ymin) / 0.8;
    Double_t dx  =(xmax-xmin) / 0.8;
    // PLOT CORRECTED MET WITH THE ZB MET {{{
    TCanvas* c1 = new TCanvas("c1","metmubin1");
    TPad *pad1 = new TPad("pad1","",0,0,1,1);
    TPad *pad2 = new TPad("pad2","",0,0,1,1);
    TLegend* l1 = new TLegend(0.48,0.7,0.9,0.9);
    pad2->SetFillStyle(4000); // will be transparent
    pad1->Draw();
    pad1->cd();
    MET_Correctedmu0thru10->Draw();
    zbMETMuBin0thru10->SetLineColor(3);
    zbMETMuBin0thru10->Draw("SAMES");
    pad1->Update();
    l1->AddEntry(MET_Correctedmu0thru10);
    l1->AddEntry(zbMETMuBin0thru10);
    l1->Draw("SAME");
    pad1->SetLogy();
    pad1->Modified();
    c1->cd();
    pad2->Range( xmin-0.1 * dx , ymin - 0.1*dy , xmax+0.1*dx , ymax+0.1*dy);
    pad2->Draw();
    pad2->cd();
    efficiencyObjectMu0thru10->Draw("SAMES");
    TGaxis *axis = new TGaxis( xmax,ymin,xmax,ymax,ymin,ymax,510, "+L");
    axis->SetLineColor(kRed);
    axis->SetTextColor(kRed);
    axis->Draw("SAME");
    c1->Print("../Plots/CorrectedAndZB/zb_met_corrected_mubin1.png");

    TCanvas* c2 = new TCanvas("c2","metmubin2");
    pad1 = new TPad("pad1","",0,0,1,1);
    pad2 = new TPad("pad2","",0,0,1,1);
    TLegend* l2 = new TLegend(0.48,0.7,0.9,0.9);
    pad2->SetFillStyle(4000);
    pad1->Draw();
    pad1->cd();
    MET_Correctedmu10thru20->Draw();
    zbMETMuBin10thru20->SetLineColor(2);
    zbMETMuBin10thru20->Draw("SAMES");
    pad1->Update();
    l2->AddEntry(MET_Correctedmu10thru20);
    l2->AddEntry(zbMETMuBin10thru20);
    l2->Draw("SAME");
    pad1->SetLogy();
    pad1->Modified();
    c2->cd();
    pad2->Range( xmin-0.1 * dx , ymin - 0.1*dy , xmax+0.1*dx , ymax+0.1*dy);
    pad2->Draw();
    pad2->cd();
    efficiencyObjectMu10thru20->Draw("SAMES");
    axis = new TGaxis( xmax,ymin,xmax,ymax,ymin,ymax,510, "+L");
    axis->SetLineColor(kRed);
    axis->SetTextColor(kRed);
    axis->Draw("SAME");
    c2->Print("../Plots/CorrectedAndZB/zb_met_corrected_mubin2.png");

    TCanvas* c3 = new TCanvas("c3","metmubin3");
    pad1 = new TPad("pad1","",0,0,1,1);
    pad2 = new TPad("pad2","",0,0,1,1);
    TLegend* l3 = new TLegend(0.48,0.7,0.9,0.9);
    pad2->SetFillStyle(4000);
    pad1->Draw();
    pad1->cd();
    MET_Correctedmu20thru30->Draw();
    pad1->Update();
    zbMETMuBin20thru30->SetLineColor(3);
    zbMETMuBin20thru30->Draw("SAME");
    l3->AddEntry(MET_Correctedmu20thru30);
    l3->AddEntry(zbMETMuBin20thru30);
    l3->Draw("SAME");
    pad1->SetLogy();
    pad1->Modified();
    c3->cd();
    pad1->SetLogy();
    pad2->Range( xmin-0.1 * dx , ymin - 0.1*dy , xmax+0.1*dx , ymax+0.1*dy);
    pad2->Draw();
    pad2->cd();
    efficiencyObjectMu20thru30->Draw("SAMES");
    axis = new TGaxis( xmax,ymin,xmax,ymax,ymin,ymax,510, "+L");
    axis->SetLineColor(kRed);
    axis->SetTextColor(kRed);
    axis->Draw("SAME");
    c3->Print("../Plots/CorrectedAndZB/zb_met_corrected_mubin3.png");

    TCanvas* c4 = new TCanvas("c4","metmubin4");
    pad1 = new TPad("pad1","",0,0,1,1);
    pad2 = new TPad("pad2","",0,0,1,1);
    TLegend* l4 = new TLegend(0.48,0.7,0.9,0.9);
    pad2->SetFillStyle(4000);
    pad1->Draw();
    pad1->cd();
    MET_Correctedmu30thru40->Draw();
    zbMETMuBin30thru40->SetLineColor(3);
    pad1->Update();
    zbMETMuBin30thru40->Draw("SAME");
    l4->AddEntry(MET_Correctedmu30thru40);
    l4->AddEntry(zbMETMuBin30thru40);
    l4->Draw("SAME");
    pad1->SetLogy();
    pad2->Range( xmin-0.1 * dx , ymin - 0.1*dy , xmax+0.1*dx , ymax+0.1*dy);
    pad2->Draw();
    pad2->cd();
    efficiencyObjectMu30thru40->Draw("SAMES");
    axis = new TGaxis( xmax,ymin,xmax,ymax,ymin,ymax,510, "+L");
    axis->SetLineColor(kRed);
    axis->SetTextColor(kRed);
    axis->Draw("SAME");
    c4->Print("../Plots/CorrectedAndZB/zb_met_corrected_mubin4.png");

    TCanvas* c5 = new TCanvas("c5","metmubin5");
    TLegend* l5 = new TLegend(0.48,0.7,0.9,0.9);
    pad1 = new TPad("pad1","",0,0,1,1);
    pad2 = new TPad("pad2","",0,0,1,1);
    pad2->SetFillStyle(4000);
    pad1->Draw();
    pad1->cd();
    MET_Correctedmu40thru50->Draw();
    zbMETMuBin40thru50->SetLineColor(3);
    pad1->Update();
    zbMETMuBin40thru50->Draw("SAME");
    l5->AddEntry(MET_Correctedmu40thru50);
    l5->AddEntry(zbMETMuBin40thru50);
    l5->Draw("SAME");
    pad1->SetLogy();
    pad2->Range( xmin-0.1 * dx , ymin - 0.1*dy , xmax+0.1*dx , ymax+0.1*dy);
    pad2->Draw();
    pad2->cd();
    efficiencyObjectMu40thru50->Draw("SAMES");
    axis = new TGaxis( xmax,ymin,xmax,ymax,ymin,ymax,510, "+L");
    axis->SetLineColor(kRed);
    axis->SetTextColor(kRed);
    axis->Draw("SAME");
    c5->Print("../Plots/CorrectedAndZB/zb_met_corrected_mubin5.png");

    TCanvas* c6 = new TCanvas("c6","metmubin6");
    pad1 = new TPad("pad1","",0,0,1,1);
    pad2 = new TPad("pad2","",0,0,1,1);
    pad2->SetFillStyle(4000);
    pad1->Draw();
    pad1->cd();
    TLegend* l6 = new TLegend(0.48,0.7,0.9,0.9);
    MET_Correctedmu50thru60->SetLineColor(3);
    MET_Correctedmu50thru60->Draw();
    pad1->Update();
    zbMETMuBin50thru60->SetLineColor(2);
    zbMETMuBin50thru60->Draw("SAME");
    l6->AddEntry(MET_Correctedmu50thru60);
    l6->AddEntry(zbMETMuBin50thru60);
    l6->Draw("SAME");
    pad1->SetLogy();
    pad2->Range( xmin-0.1 * dx , ymin - 0.1*dy , xmax+0.1*dx , ymax+0.1*dy);
    pad2->Draw();
    pad2->cd();
    efficiencyObjectMu50thru60->Draw("SAMES");
    axis = new TGaxis( xmax,ymin,xmax,ymax,ymin,ymax,510, "+L");
    axis->SetLineColor(kRed);
    axis->SetTextColor(kRed);
    axis->Draw("SAME");
    c6->Print("../Plots/CorrectedAndZB/zb_met_corrected_mubin6.png");

    TCanvas* c7 = new TCanvas("c7","metmubin7");
    pad1 = new TPad("pad1","",0,0,1,1);
    pad2 = new TPad("pad2","",0,0,1,1);
    pad2->SetFillStyle(4000);
    pad1->Draw();
    pad1->cd();
    TLegend* l7 = new TLegend(0.48,0.7,0.9,0.9);
    MET_Correctedmu60thru70->Draw();
    zbMETMuBin60thru70->SetLineColor(2);
    zbMETMuBin60thru70->Draw("SAME");
    pad1->Update();
    l7->AddEntry(MET_Correctedmu60thru70);
    l7->AddEntry(zbMETMuBin60thru70);
    l7->Draw("SAME");
    pad1->SetLogy();
    pad2->Range( xmin-0.1 * dx , ymin - 0.1*dy , xmax+0.1*dx , ymax+0.1*dy);
    pad2->Draw();
    pad2->cd();
    efficiencyObjectMu60thru70->Draw("SAMES");
    axis = new TGaxis( xmax,ymin,xmax,ymax,ymin,ymax,510, "+L");
    axis->SetLineColor(kRed);
    axis->SetTextColor(kRed);
    axis->Draw("SAME");
    c7->Print("../Plots/CorrectedAndZB/zb_met_corrected_mubin7.png");
    //}}}

    // WRITE CORRECTED MET DISTRIBUTIONS TO FILE{{{
    if ( !mu_analysis_file->cd("corrected_met") ){
        std::cout << "Corrected MET dist directory did not already exist. creating new one" << std::endl;
        mu_analysis_file->mkdir("corrected_met");
    }
    else{
        std::cout << "Successfully switched to correcting met distributions directory" << std::endl;
    }
    MET_Correctedmu0thru10->Write("",TObject::kOverwrite);
    MET_Correctedmu10thru20->Write("",TObject::kOverwrite);
    MET_Correctedmu20thru30->Write("",TObject::kOverwrite);
    MET_Correctedmu30thru40->Write("",TObject::kOverwrite);
    MET_Correctedmu40thru50->Write("",TObject::kOverwrite);
    MET_Correctedmu50thru60->Write("",TObject::kOverwrite);
    MET_Correctedmu60thru70->Write("",TObject::kOverwrite);
    //}}}
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
