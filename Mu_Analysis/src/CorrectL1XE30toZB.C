#define CorrectL1XE30toZB_cxx
#include "../include/CorrectL1XE30toZB.h"
ClassImp(CorrectL1XE30toZB);
void CorrectL1XE30toZB::Begin(TTree * /*tree*/){//{{{
    TString option = GetOption();
    // initialize the boundaries of each mu bin
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
   for (int i = 0 ; i < Number_Mu_Bins ; i++){
       // initialize empty histograms, efficiency objects, and efficiency fit objects 
       muLow = Mu_Values[i];
       muHigh = Mu_Values[i+1];
       std::cout << "Mu between: " << muLow << " and " << muHigh << std::endl;
       Name.Form("metmu%.0fthru%.0f" , muLow , muHigh );
       delete gROOT->FindObject(Name);
       EfficiencyName.Form("metmu%.0fthru%.0fEfficiency", muLow , muHigh );
       delete gROOT->FindObject(EfficiencyName);
       Title.Form("ZeroBias MET Distribution for %s With Actint Between %.0f and %.0f" ,Alg_Name.Data(), muLow , muHigh );
       EfficiencyTitle.Form("Efficiency of L1XE 30 As a Function of %s for Actint Between %.0f and %.0f", Alg_Name.Data() , muLow , muHigh );
       Corrected_Name.Form("L1XE30CorrectedToZBmu%.0fthru%.0f" , muLow , muHigh );
       Corrected_Title.Form("L1XE30 Data Corrected back to Zerobias For Actint Between %.0f and %.0f" , muLow , muHigh );
       Met_Distributions_By_Mu_Bin[i] = new TH1F( Name , Title , nbins , gevLow , gevHigh );
       Normalized_Met_Distributions[i] = new TH1F( Corrected_Name , Corrected_Title , nbins , gevLow , gevHigh );
       L1XE30_Efficiency_Objects[i] = new TEfficiency( EfficiencyName , EfficiencyTitle , nbins , gevLow , gevHigh );
       L1XE30_Efficiency_Fit_Objects[i] = new TF1();
   }
    // TH1 OBJECTS DO NOT BELONG TO TFILE SCOPE. THEY WILL STAY
    TH1::AddDirectory(false);

    // Open the root file in update mode
    TFile* mu_analysis_file = TFile::Open("mu_analysis.root","UPDATE");
    // check to see if can open file{{{
    if (!mu_analysis_file->IsOpen()){
        std::cout << "mu_analysis.root not opened" << std::endl;
        return;
    }//}}}
    // get l1xe30 efficiency objects  {{{
    if ( mu_analysis_file->cd("l1xe30_efficiency_curves") ){
        std::cout << "Successfully switched to l1xe30_efficiency_curves" << std::endl;
        for ( int i = 0 ; i  < Number_Mu_Bins ; i++ ) {
           muLow = Mu_Values[i];
           muHigh = Mu_Values[i+1];
           // generate the name of the current efficiency object
           EfficiencyName.Form("metmu%.0fthru%.0fEfficiency", muLow , muHigh );
           // load the efficiency object into the array
            gDirectory->GetObject( EfficiencyName , L1XE30_Efficiency_Objects[i] );
        }
    }
//}}}
    // get l1xe30 efficiency fit objects {{{
    TString EfficiencyFitName;
    if ( mu_analysis_file->cd("l1xe30_efficiency_fits")){
            std::cout << "Successfully switched to l1xe30_efficiency_fits" << std::endl;
            for ( int i = 0 ; i  < Number_Mu_Bins ; i++ ) {
               muLow = Mu_Values[i];
               muHigh = Mu_Values[i+1];
                // all the fit functions have the same name , but different cycle number
               EfficiencyFitName.Form("fitFunction;%d", i+1 );
               // load the fit function object into fit function object array
                gDirectory->GetObject( EfficiencyFitName , L1XE30_Efficiency_Fit_Objects[i] );
            }
    }
    else{
        std::cout << "Unable to open efficiency_curves directory" << std::endl;
        return;
    }
//}}}
    // get the zerobias met distributions {{{
    if (gDirectory->cd("../zb_met_distributions") ){
        std::cout << "Successfully switched to zb_met_distributions" << std::endl;
        for (int i = 0 ; i < Number_Mu_Bins ; i++ ) {
           muLow = Mu_Values[i];
           muHigh = Mu_Values[i+1];
           Name.Form("metmu%.0fthru%.0f", muLow , muHigh );
           gDirectory->GetObject( Name , Met_Distributions_By_Mu_Bin[i] );
            // Is this necessary?
           Met_Distributions_By_Mu_Bin[i]->SetDirectory(0);
        }
    }
    else{
        std::cout << "Unable to open zb_met directory" << std::endl;
        return;
    }//}}}
    std::cout << "Successfully retrieved the zb met distributions" << std::endl;
}//}}}
Bool_t CorrectL1XE30toZB::Process(Long64_t entry)//{{{
{
   fReader.SetLocalEntry(entry);
   // still need to compute new error and pass it to this fill function somehow
   // if the entry is passnoalg L1XE30, and it one of the good runs
   if ( isHLT_zb_L1XE30() && isGoodRun() ){
       for ( int i = 0 ; i < Number_Mu_Bins ; i++ ) {
           if ( inMuRange( Mu_Values[i] , Mu_Values[i+1] )){
                Normalized_Met_Distributions[i]->Fill( *cell_met , ComputeWeight( L1XE30_Efficiency_Fit_Objects[i] ) );
            }
        }
   }
   return kTRUE;
}//}}}
void CorrectL1XE30toZB::Terminate(){//{{{
	// Relative Normalization{{{
    // Scale the corrected ones to the original zb ones
    for (int i = 0 ;i < Number_Mu_Bins ; i++ ) {
        Scale_Factors[i] = Met_Distributions_By_Mu_Bin[i]->GetBinContent( Normalization_Bin_Numbers[i] ) / Normalized_Met_Distributions[i]->GetBinContent( Normalization_Bin_Numbers[i] );
        Met_Distributions_By_Mu_Bin[i]->SetNormFactor( 1. );
        Normalized_Met_Distributions[i]->SetNormFactor( 1. );
        Normalized_Met_Distributions[i]->Scale( Scale_Factors[i] );
    }
    //}}}
    // plot corrected distributions {{{
    for (int i = 0 ; i < Number_Mu_Bins ; i++ ) {
        Met_Distributions_By_Mu_Bin[i]->SetLineColor( Colors[i] );
        Normalized_Met_Distributions[i]->SetLineColor( Colors[i] );
    }
    TCanvas* correctedCanvas = new TCanvas("correctedCanvas","Canvas with Mu Bin Distributions for L1XE30 Corrected to ZB");
	TLegend* correctedLegend = new TLegend(0.48,0.7,0.9,0.9);
    Normalized_Met_Distributions[0]->Draw();
    correctedLegend->AddEntry( Normalized_Met_Distributions[0] );
    for (int i = 1; i < Number_Mu_Bins ; i++ ) {
        Normalized_Met_Distributions[i]->Draw("SAME");
        correctedLegend->AddEntry( Normalized_Met_Distributions[i] );
    }
	correctedLegend->Draw("SAME");
    correctedCanvas->SetLogy();
    gStyle->SetOptStat(0);
    correctedCanvas->Print("../Plots/CorrectedAndZB/L1XE30CorrectedToZB.png");
    //}}}
	// PLOT ZERO BIAS DISTRIBUTIONS {{{
	TCanvas* zb_MET_Canvas = new TCanvas("zbCanvas","Canvas with zerobias data");
    TLegend* zbDistLegend = new TLegend(0.48,0.7,0.9,0.9);
    Met_Distributions_By_Mu_Bin[0]->Draw();
    zbDistLegend->AddEntry( Met_Distributions_By_Mu_Bin[0] );
    for (int i = 1; i < Number_Mu_Bins ; i++ ) {
        Met_Distributions_By_Mu_Bin[i]->Draw("SAME");
        zbDistLegend->AddEntry( Met_Distributions_By_Mu_Bin[i] );
    }
    zbDistLegend->Draw("SAME");
    zb_MET_Canvas->SetLogy();
    gStyle->SetOptStat(0);
    zb_MET_Canvas->Print("../Plots/CorrectedAndZB/Met_Distributions_By_Mu_Bin.png");
    //}}}
    // PLOT CORRECTED MET WITH THE ZB MET {{{
    TString Canvas_Name;
    TString Canvas_Title;
    TString plot_name;
    Double_t ymin = 0.0;
    Double_t ymax = 1.0;
    Double_t xmin = 0.0;
    Double_t xmax = 300.0;
    Double_t dy = (ymax-ymin) / 0.8;
    Double_t dx  =(xmax-xmin) / 0.8;
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
        Normalized_Met_Distributions[i]->Draw();
        Met_Distributions_By_Mu_Bin[i]->SetLineColor(3);
        Met_Distributions_By_Mu_Bin[i]->Draw("SAMES");
        pad1->Update();
        legend->AddEntry( Normalized_Met_Distributions[i] );
        legend->AddEntry( Met_Distributions_By_Mu_Bin[i] );
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
        plot_name.Form( "plots/CorrectedAndZB/zb_l1xe30met_corrected_mubin%d.png" , i+1 );
        mu_bin_canv->Print(plot_name);
    }
    //}}}
    // WRITE CORRECTED MET DISTRIBUTIONS TO FILE{{{
    // this is L1XE30 distribution corrected to ZB
    TFile* mu_analysis_file = TFile::Open("mu_analysis.root","UPDATE");
    std::cout << "Making a directory for corrected met distributions" << std::endl;
    TDirectory* corrected_directory = mu_analysis_file->mkdir("L1XE30CorrectedToZB");
    corrected_directory->cd();
    for (int i = 0 ; i < Number_Mu_Bins ; i++ ) {
        Normalized_Met_Distributions[i]->Write( "" , TObject::kOverwrite );
    }
    //}}}
    mu_analysis_file->Close();
}//}}}
void CorrectL1XE30toZB::SlaveTerminate(){}
void CorrectL1XE30toZB::Init(TTree *tree){fReader.SetTree(tree);}
void CorrectL1XE30toZB::SlaveBegin(TTree *){TString option = GetOption();}
