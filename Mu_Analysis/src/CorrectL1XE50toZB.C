#define CorrectL1XE50toZB_cxx
#include "CorrectL1XE50toZB.h"
ClassImp(CorrectL1XE50toZB);
void CorrectL1XE50toZB::Begin(TTree * /*tree*/)//{{{
{
    TString option = GetOption();
   for (int i = 0 ; i < Number_Mu_Bins + 1; i++){
       Mu_Values[i] = i * 10.;
   }
   Float_t muLow;
   Float_t muHigh;
   TString Name;
   TString Title;
   TString Corrected_Name;
   TString Corrected_Title;
   TString EfficiencyName;
   TString EfficiencyTitle;
   // initialize empty histograms, efficiency objects, etc.
   for (int i = 0 ; i < Number_Mu_Bins ; i++){
       muLow = Mu_Values[i];
       muHigh = Mu_Values[i+1];
       std::cout << "Mu between: " << muLow << " and " << muHigh << std::endl;
       Name.Form("metmu%.0fthru%.0f" , muLow , muHigh );
       Title.Form("L1XE 50 MET Distribution for %s With Actint Between %.0f and %.0f" ,Alg_Name.Data(), muLow , muHigh );

       EfficiencyName.Form("metmu%.0fthru%.0fL1XE30Efficiency", muLow , muHigh );
       EfficiencyTitle.Form("Efficiency of L1XE 30 As a Function of %s for Actint Between %.0f and %.0f", Alg_Name.Data() , muLow , muHigh );

       Corrected_Name.Form("L1XE50CorrectedToZBmu%.0fthru%.0f" , muLow , muHigh );
       Corrected_Title.Form("L1XE50 Data Corrected back to Zerobias For Actint Between %.0f and %.0f" , muLow , muHigh );

       ZB_MET_Distributions[i] = new TH1F( Name , Title , nbins , gevLow , gevHigh );
       Corrected_MET_Distributions[i] = new TH1F( Corrected_Name , Corrected_Title , nbins , gevLow , gevHigh );

       L1XE30_Efficiency_Objects[i] = new TEfficiency( EfficiencyName , EfficiencyTitle , nbins , gevLow , gevHigh );
       L1XE30_Efficiency_Fit_Objects[i] = new TF1();

       EfficiencyName.Form("metmu%.0fthru%.0fL1XE50Efficiency", muLow , muHigh );
       EfficiencyTitle.Form("Efficiency of L1XE 50 As a Function of %s for Actint Between %.0f and %.0f", Alg_Name.Data() , muLow , muHigh );

       L1XE50_Efficiency_Objects[i] = new TEfficiency( EfficiencyName , EfficiencyTitle , nbins , gevLow , gevHigh );
       L1XE50_Efficiency_Fit_Objects[i] = new TF1();
   }
    // TH1 OBJECTS DO NOT BELONG TO TFILE SCOPE. THEY WILL STAY
    TH1::AddDirectory(false);
    TFile* mu_analysis_file = TFile::Open("mu_analysis.root","UPDATE");
    if (!mu_analysis_file->IsOpen()){
        std::cout << "mu_analysis.root not opened" << std::endl;
        return;
    }
    // retrieve l1xe50 efficiency curves{{{
    if ( mu_analysis_file->cd("l1xe50_efficiency_curves") ){
        std::cout << "Successfully switched to:" << std::endl;
        gDirectory->pwd();
        for ( int i = 0 ; i  < Number_Mu_Bins ; i++ ) {
           muLow = Mu_Values[i];
           muHigh = Mu_Values[i+1];
           EfficiencyName.Form("metmu%.0fthru%.0fEfficiency", muLow , muHigh );
            gDirectory->GetObject( EfficiencyName , L1XE50_Efficiency_Objects[i] );
        }
    }
    else{
        std::cout << "Unable to open l1xe50 efficiency curves directory" << std::endl;
    }//}}}
    // retrieve l1xe30 efficiency fits{{{
    TString EfficiencyFitName;
    if ( mu_analysis_file->cd("l1xe30_efficiency_fits")){
            std::cout << "Successfully switched to:" << std::endl;
            gDirectory->pwd();
            for ( int i = 0 ; i  < Number_Mu_Bins ; i++ ) {
               muLow = Mu_Values[i];
               muHigh = Mu_Values[i+1];
                // all the fit functions have the same name , but different cycle number
               EfficiencyFitName.Form("fitFunction;%d", i+1 );
                gDirectory->GetObject( EfficiencyFitName , L1XE30_Efficiency_Fit_Objects[i] );
            }
    }
    else{
        std::cout << "Unable to open l1xe30 efficiency fits directory" << std::endl;
        return;
    }//}}}
    // retrieve l1xe50 efficiency fits {{{
    if ( mu_analysis_file->cd("l1xe50_efficiency_fits")){
            std::cout << "Successfully switched to:" << std::endl;
            gDirectory->pwd();
            for ( int i = 0 ; i  < Number_Mu_Bins ; i++ ) {
               muLow = Mu_Values[i];
               muHigh = Mu_Values[i+1];
                // all the fit functions have the same name , but different cycle number
               EfficiencyFitName.Form("fitFunction;%d", i+1 );
                gDirectory->GetObject( EfficiencyFitName , L1XE50_Efficiency_Fit_Objects[i] );
            }
    }
    else{
        std::cout << "Unable to open L1XE50 efficiency fits directory" << std::endl;
        return;
    }//}}}
    // retrieve ZB distributions{{{
    if (mu_analysis_file->cd("zb_met_distributions") ){
        std::cout << "Successfully switched to:" << std::endl;
        gDirectory->pwd();
            for ( int i = 0 ; i  < Number_Mu_Bins ; i++ ) {
               muLow = Mu_Values[i];
               muHigh = Mu_Values[i+1];
                // all the fit functions have the same name , but different cycle number
               Name.Form("metmu%.0fthru%.0f", muLow , muHigh );
                gDirectory->GetObject( Name , ZB_MET_Distributions[i] );
                ZB_MET_Distributions[i]->SetDirectory(0);
            }
        std::cout << "Successfully got all of the zb met distributions" << std::endl;
    }
    else{
        std::cout << "Unable to open zerobias MET distribution directory" << std::endl;
        return;
    }//}}}
}//}}}
Bool_t CorrectL1XE50toZB::Process(Long64_t entry)//{{{
{
   fReader.SetLocalEntry(entry);
   // just make sure this is the correct flag L1XE30
   // still need to compute new error and pass it to this fill function somehow
   // if the entry is passnoalg L1XE30, and it one of the good runs
   if ( isPassnoAlgL1XE50() && isGoodRun() ){
       for ( int i = 0 ; i < Number_Mu_Bins ; i++ ) {
           if ( inMuRange( Mu_Values[i] , Mu_Values[i+1] )){
                Corrected_MET_Distributions[i]->Fill( *cell_met , ComputeWeight( L1XE30_Efficiency_Fit_Objects[i], L1XE50_Efficiency_Fit_Objects[i] ) );
            }
        }
   }
   return kTRUE;
}//}}}
void CorrectL1XE50toZB::SlaveTerminate(){}
void CorrectL1XE50toZB::Terminate(){//{{{
	// Relative Normalization{{{
    // BinWidth = 1.0 GeV

    for ( int i = 0 ; i < Number_Mu_Bins ; i++ ){
        Scale_Factors[i] = ZB_MET_Distributions[i]->GetBinContent( Normalization_Bin_Numbers[i] ) / Corrected_MET_Distributions[i]->GetBinContent( Normalization_Bin_Numbers[i] );
        ZB_MET_Distributions[i]->SetNormFactor( 1. );
        Corrected_MET_Distributions[i]->SetNormFactor( 1. );
        Corrected_MET_Distributions[i]->Scale( Scale_Factors[i] );
    }

    //}}}
    // plot corrected distributions {{{
    for (int i = 0 ; i < Number_Mu_Bins ; i++ ) {
        ZB_MET_Distributions[i]->SetLineColor( Colors[i] );
        Corrected_MET_Distributions[i]->SetLineColor( Colors[i] );
    }
    TCanvas* correctedCanvas = new TCanvas("correctedCanvas","Canvas with Mu Bin Distributions for L1XE50 Corrected to ZB");
	TLegend* correctedLegend = new TLegend(0.48,0.7,0.9,0.9);
    Corrected_MET_Distributions[0]->Draw();
    correctedLegend->AddEntry( Corrected_MET_Distributions[0] );
    for (int i = 1; i < Number_Mu_Bins ; i++ ) {
        Corrected_MET_Distributions[i]->Draw("SAME");
        correctedLegend->AddEntry( Corrected_MET_Distributions[i] );
    }
	correctedLegend->Draw("SAME");
    correctedCanvas->SetLogy();
    gStyle->SetOptStat(0);
    correctedCanvas->Print("plots/CorrectedAndZB/L1XE50CorrectedToZB.png");

    //}}}
	// PLOT ZERO BIAS DISTRIBUTIONS {{{
    TCanvas* zb_MET_Canvas = new TCanvas("zbCanvas","Canvas with zerobias data");
    TLegend* zbDistLegend = new TLegend(0.48,0.7,0.9,0.9);
    ZB_MET_Distributions[0]->Draw();
    zbDistLegend->AddEntry( ZB_MET_Distributions[0] );
    for (int i = 1; i < Number_Mu_Bins ; i++ ) {
        ZB_MET_Distributions[i]->Draw("SAME");
        zbDistLegend->AddEntry( ZB_MET_Distributions[i] );
    }
    zbDistLegend->Draw("SAME");
    zb_MET_Canvas->SetLogy();
    gStyle->SetOptStat(0);
    zb_MET_Canvas->Print("plots/CorrectedAndZB/ZB_MET_Distributions.png");

    //}}}
    Double_t ymin = 0.0;
    Double_t ymax = 1.0;
    Double_t xmin = 0.0;
    Double_t xmax = 300.0;
    Double_t dy = (ymax-ymin) / 0.8;
    Double_t dx  =(xmax-xmin) / 0.8;

    TString Canvas_Name;
    TString Canvas_Title;
    TString plot_name;

    for (int i = 0 ; i < Number_Mu_Bins ; i++ ){
        Canvas_Name.Form( "c%d", i+1 );
        Canvas_Title.Form( "met_mubin%d", i+1 );
        TCanvas* mu_bin_canv = new TCanvas( Canvas_Name , Canvas_Title );
        TPad* pad1 = new TPad( "pad1" , "" , 0 , 0 ,1 , 1 );
        TPad* pad2 = new TPad( "pad2" , "" , 0 , 0 ,1 , 1 );
        TLegend* legend = new TLegend(0.48,0.7,0.9,0.9);
        pad2->SetFillStyle(4000); // transparent
        pad1->Draw();
        pad1->cd();
        Corrected_MET_Distributions[i]->Draw();
        ZB_MET_Distributions[i]->SetLineColor(3);
        ZB_MET_Distributions[i]->Draw("SAMES");
        pad1->Update();
        legend->AddEntry( Corrected_MET_Distributions[i] );
        legend->AddEntry( ZB_MET_Distributions[i] );
        legend->Draw("SAME");
        pad1->SetLogy();
        pad1->Modified();
        mu_bin_canv->cd();
        pad2->Range( xmin-0.1 * dx , ymin - 0.1*dy , xmax+0.1*dx , ymax+0.1*dy);
        pad2->Draw();
        pad2->cd();
        L1XE30_Efficiency_Objects[i]->Draw("SAMES");
        TGaxis *axis = new TGaxis( xmax,ymin,xmax,ymax,ymin,ymax,510, "+L");
        axis->SetLineColor(kRed);
        axis->SetTextColor(kRed);
        axis->Draw("SAME");
        plot_name.Form( "plots/CorrectedAndZB/zb_l1xe50met_corrected_mubin%d.png" , i+1 );
        mu_bin_canv->Print(plot_name);
    }

    // WRITE CORRECTED MET DISTRIBUTIONS TO FILE{{{
    TFile* mu_analysis_file = TFile::Open("mu_analysis.root","UPDATE");
    TDirectory* corrected_directory = mu_analysis_file->mkdir("L1XE50CorrectedToZB");
    corrected_directory->cd();
    for (int i = 0 ; i < Number_Mu_Bins ; i++ ) {
        Corrected_MET_Distributions[i]->Write( "" , TObject::kOverwrite );
    }
    mu_analysis_file->Close();
    //}}}
}//}}}
void CorrectL1XE50toZB::Init(TTree *tree){fReader.SetTree(tree);}
void CorrectL1XE50toZB::SlaveBegin(TTree * /*tree*/)//{{{
{
   TString option = GetOption();
}//}}}
