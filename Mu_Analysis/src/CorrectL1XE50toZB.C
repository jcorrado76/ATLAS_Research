#define CorrectL1XE50toZB_cxx
#include "CorrectL1XE50toZB.h"
#include <math.h>
ClassImp(CorrectL1XE50toZB);
void CorrectL1XE50toZB::Begin(TTree *)//{{{
{
    TString option = GetOption();
    // TH1 OBJECTS DO NOT BELONG TO TFILE SCOPE. THEY WILL STAY
    // TODO: remove all of this
    TH1::AddDirectory(false);
    TFile* mu_analysis_file = TFile::Open("run_files/mu_analysis.root","UPDATE");
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
                gDirectory->GetObject( Name , Met_Distributions_By_Mu_Bin[i] );
                Met_Distributions_By_Mu_Bin[i]->SetDirectory(0);
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
   // still need to compute new error and pass it to this fill function somehow
   if ( isHLT_zb_L1XE50() && isGoodRun() ){
       for ( int i = 0 ; i < Number_Mu_Bins ; i++ ) {
           if ( inMuRange( Mu_Values[i] , Mu_Values[i+1] )){
                HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution[i]->Fill( *cell_met , ComputeWeight( L1XE30_Efficiency_Fit_Objects[i], L1XE50_Efficiency_Fit_Objects[i] ) );
            }
        }
   }
   return kTRUE;
}//}}}
void CorrectL1XE50toZB::Terminate(){//{{{
	// Relative Normalization{{{
    for ( int i = 0 ; i < Number_Mu_Bins ; i++ ){
        std::cout << "Nentries in mubin " << i << " met distribution: " << 
            Met_Distributions_By_Mu_Bin[i]->GetEntries() << std::endl;
        Scale_Factors[i] = Met_Distributions_By_Mu_Bin[i]->GetBinContent( Normalization_Bin_Numbers[i] ) / 
            HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution[i]->GetBinContent( Normalization_Bin_Numbers[i] );
        if (isnan( Scale_Factors[i] )){
            std::cout << "Scale factor " << i << ": " << Scale_Factors[i] << " is NaN" << std::endl;
            std::cout << "MET Counts in mubin " << i << ": " << 
                Met_Distributions_By_Mu_Bin[i]->GetBinContent( Normalization_Bin_Numbers[i] ) << 
                " in normalization bin number: " << Normalization_Bin_Numbers[i] << std::endl;
            std::cout << "Counts in the Normalized MET distribution bin: " << 
                HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution[i]->GetBinContent( Normalization_Bin_Numbers[i] ) << std::endl;
        }
        std::cout << "Scale factor: " << i << " = " << Scale_Factors[i] << std::endl;
        Met_Distributions_By_Mu_Bin[i]->SetNormFactor( 1. );
        HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution[i]->SetNormFactor( 1. );
        HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution[i]->Scale( Scale_Factors[i] );
    }
    //}}}
    /*
    // plot corrected distributions {{{
    for (int i = 0 ; i < Number_Mu_Bins ; i++ ) {
        HLT_ZB_L1ZB_MET_Distributions_by_Mubin[i]->SetLineColor( Colors[i] );
        HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution[i]->SetLineColor( Colors[i] );
    }
    TCanvas* correctedCanvas = new TCanvas("correctedCanvas","Canvas with Mu Bin Distributions for L1XE50 Corrected to ZB");
	TLegend* correctedLegend = new TLegend(0.48,0.7,0.9,0.9);
    HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution[0]->Draw();
    correctedLegend->AddEntry( HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution[0] );
    for (int i = 1; i < Number_Mu_Bins ; i++ ) {
        HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution[i]->Draw("SAME");
        correctedLegend->AddEntry( HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution[i] );
    }
	correctedLegend->Draw("SAME");
    correctedCanvas->SetLogy();
    gStyle->SetOptStat(0);
    correctedCanvas->Print("plots/CorrectedAndZB/L1XE50CorrectedToZB.png");

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
    zb_MET_Canvas->Print("plots/CorrectedAndZB/Met_Distributions_By_Mu_Bin.png");

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
        HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution[i]->Draw();
        Met_Distributions_By_Mu_Bin[i]->SetLineColor(3);
        Met_Distributions_By_Mu_Bin[i]->Draw("SAMES");
        pad1->Update();
        legend->AddEntry( HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution[i] );
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
        plot_name.Form( "plots/CorrectedAndZB/zb_l1xe50met_corrected_mubin%d.png" , i+1 );
        mu_bin_canv->Print(plot_name);
    }

    // WRITE CORRECTED MET DISTRIBUTIONS TO FILE{{{
    TFile* mu_analysis_file = TFile::Open("run_files/mu_analysis.root","UPDATE");
    TDirectory* corrected_directory = mu_analysis_file->mkdir("L1XE50CorrectedToZB");
    corrected_directory->cd();
    for (int i = 0 ; i < Number_Mu_Bins ; i++ ) {
        Name.Form("l1xe50correctedToZBMETmubin%d" , i );
        HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution[i]->Write( Name , TObject::kOverwrite );
    }
    mu_analysis_file->Close();
    //}}}
    */
}//}}}
