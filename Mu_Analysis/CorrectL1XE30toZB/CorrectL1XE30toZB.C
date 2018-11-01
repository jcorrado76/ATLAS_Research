#define CorrectL1XE30toZB_cxx
#include "CorrectL1XE30toZB.h"

void CorrectL1XE30toZB::Begin(TTree * /*tree*/)//{{{
    TString option = GetOption();
   for (int i = 0 ; i < Number_Mu_Bins + 1; i++){
       Mu_Values[i] = i * 10.;
   }
   Int_t n;
   Float_t muLow;
   Float_t muHigh;
   TString Name;
   TString Title;
   TString Corrected_Name;
   TString Corrected_Title;
   TString EfficiencyName;
   TString EfficiencyTitle;
   for (int i = 0 ; i < Number_Mu_Bins ; i++){
       muLow = Mu_Values[i];
       muHigh = Mu_Values[i+1];
       std::cout << "Mu between: " << muLow << " and " << muHigh << std::endl;
       Name.Form("metmu%.0fthru%.0f" , muLow , muHigh );
       EfficiencyName.Form("metmu%.0fthru%.0fEfficiency", muLow , muHigh );
       Title.Form("ZeroBias MET Distribution for %s With Actint Between %.0f and %.0f" ,Alg_Name.Data(), muLow , muHigh );
       EfficiencyTitle.Form("Efficiency of L1XE 30 As a Function of %s for Actint Between %.0f and %.0f", Alg_Name.Data() , muLow , muHigh );
       Corrected_Name.Form("L1XE30CorrectedToZBmu%.0fthru%.0f" , muLow , muHigh );
       Corrected_Title.Form("L1XE30 Data Corrected back to Zerobias For Actint Between %.0f and %.0f" , muLow , muHigh );
       ZB_MET_Distributions[i] = new TH1F( Name , Title , met_dist_nbins , gevLow , gevHigh );
       Corrected_MET_Distributions[i] = new TH1F( Corrected_Name , Corrected_Title , met_dist_nbins , gevLow , gevHigh );
       L1XE30_Efficiency_Objects[i] = new TEfficiency( EfficiencyName , EfficiencyTitle , efficiency_nbins , gevLow , gevHigh );
       L1XE30_Efficiency_Fit_Objects[i] = new TF1();
   }
    // TH1 OBJECTS DO NOT BELONG TO TFILE SCOPE. THEY WILL STAY
    TH1::AddDirectory(false);
    TFile* mu_analysis_file = TFile::Open("mu_analysis.root","UPDATE");
    // attempt to open file {{{
    if (!mu_analysis_file->IsOpen()){
        std::cout << "mu_analysis.root not opened" << std::endl;
        return;
    }//}}}
    // cd to the efficiency object directory{{{
    if ( mu_analysis_file->cd("l1xe30_efficiency_curves") ){
        std::cout << "Successfully switched to:" << std::endl;
        gDirectory->pwd();
        for ( int i = 0 ; i  < Number_Mu_Bins ; i++ ) {
           muLow = Mu_Values[i];
           muHigh = Mu_Values[i+1];
           EfficiencyName.Form("metmu%.0fthru%.0fEfficiency", muLow , muHigh );
            gDirectory->GetObject( EfficiencyName , L1XE30_Efficiency_Objects[i] );
        }
    }
//}}}
    // switch to the efficiency fit object directory  {{{
    TString EfficiencyFitName;
    if ( mu_analysis_file->cd("l1xe30_efficiency_fits");
            std::cout << "Successfully switched to:" << std::endl;
            gDirectory->pwd();
            for ( int i = 0 ; i  < Number_Mu_Bins ; i++ ) {
               muLow = Mu_Values[i];
               muHigh = Mu_Values[i+1];
                // all the fit functions have the same name , but different cycle number 
               EfficiencyFitName.Form("fitFunction;%d", i+1 );
                gDirectory->GetObject( EfficiencyFitName , L1XE30_Efficiency_Fit_Objects[i] );
    }
    else{
        std::cout << "Unable to open efficiency_curves directory" << std::endl;
        return;
    }//}}}
    // switch to the MET distributions directory{{{
    if (gDirectory->cd("../zb_met_distributions") ){
        std::cout << "Successfully switched to:" << std::endl;
        gDirectory->pwd();
        for (int i = 0 ; i < Number_Mu_Bins ; i++ ) {
           muLow = Mu_Values[i];
           muHigh = Mu_Values[i+1];
           Name.Form("metmu%.0fthru%.0f", muLow , muHigh );
           gDirectory->GetObject( Name , ZB_MET_Distributions[i] );
            // Is this necessary?
           ZB_MET_Distributions[i]->SetDirectory(0);
        }
    }
    else{
        std::cout << "Unable to open zb_met directory" << std::endl;
        return;
    }//}}}
}//}}}
Bool_t CorrectL1XE30toZB::Process(Long64_t entry)//{{{
{
   fReader.SetLocalEntry(entry);
   // still need to compute new error and pass it to this fill function somehow 
   // if the entry is passnoalg L1XE30, and it one of the good runs
   if ( isPassnoAlgL1XE30() && isGoodRun() ){
       for ( int i = 0 ; i < Number_Mu_Bins ; i++ ) {
           if ( inMuRange( Mu_Values[i] , Mu_Values[i+1] )){
                ZB_MET_Distributions[i]->Fill( *cell_met , ComputeWeight( L1XE30_Efficiency_Fit_Objects[i] ) );
            }
        }
   }
   return kTRUE;
}//}}}
void CorrectL1XE30toZB::Terminate(){//{{{
	// Relative Normalization{{{
    // Scale the corrected ones to the original zb ones
    for (int i = 0 ;i < Number_Mu_Bins ; i++ ) {
        Scale_Factors[i] = ZB_MET_Distributions[i]->GetBinContent( Normalization_Bin_Numbers[i] ) / Corrected_MET_Distributions[i]->GetBinContent( Normalization_Bin_Numbers[i] );
        std::cout << Scale_Factors[i] << std::endl;
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
    TCanvas* correctedCanvas = new TCanvas("correctedCanvas","Canvas with Mu Bin Distributions for L1XE30 Corrected to ZB");
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
    correctedCanvas->Print("../Plots/CorrectedAndZB/L1XE30CorrectedToZB.png");
    //}}}
	// PLOT ZERO BIAS DISTRIBUTIONS {{{
	TCanvas* zb_MET_Canvas = new TCanvas("zbCanvas","Canvas with zerobias data");
    TLegend* zbDistLegend = new TLegend(0.48,0.7,0.9,0.9);
    ZB_MET_Distributions[0]->Draw();
    zbDistLegend->AddEntry( ZB_MET_Distributions[0] );
    for (int i = 1; i < Number_Mu_Bins ; i++ ) {
        ZB_MET_Distributions[i]->Draw("SAME");
        zbDistLegend->AddDirectory( ZB_MET_Distributions[i] );
    }
    zbDistLegend->Draw("SAME");
    zb_MET_Canvas->SetLogy();
    gStyle->SetOptStat(0);
    zb_MET_Canvas->Print("../Plots/CorrectedAndZB/ZB_MET_Distributions.png");
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
        Corrected_MET_Distributions[i]->Draw();
        ZB_MET_Distributions[i]->SetLineColor(3);
        ZB_MET_Distributions[i]->Draw("SAMES");
        pad1->Update();
        legend->AddEntry( Corrected_MET_Distributions[i] );
        legend->AddEntry( ZB_MET_Distributions[i] );
        legend->Draw("SAME");
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
        plot_name.Form( "../Plots/CorrectedAndZB/zb_met_corrected_mubin%d.png" , i+1 );
        mu_bin_canv->Print(plot_name);
    }
    //}}}
    // WRITE CORRECTED MET DISTRIBUTIONS TO FILE{{{
    // this is L1XE30 distribution corrected to ZB
    if ( !mu_analysis_file->cd("L1XE30CorrectedToZB") ){
        std::cout << "Corrected MET dist directory did not already exist. creating new one" << std::endl;
        mu_analysis_file->mkdir("L1XE30CorrectedToZB");
    }
    else{
        std::cout << "Successfully switched to correcting met distributions directory" << std::endl;
    }
    for (int i = 0 ; i < Number_Mu_Bins ; i++ ) {
        Corrected_MET_Distributions[i]->Write( "" , TObject::kOverwrite );
    }
    //}}}
    mu_analysis_file->Close();
}//}}}
void CorrectL1XE30toZB::SlaveTerminate(){}
void CorrectL1XE30toZB::Init(TTree *tree){fReader.SetTree(tree);}
void CorrectL1XE30toZB::SlaveBegin(TTree * /*tree*/)//{{{
{
   TString option = GetOption();
}//}}}
Bool_t CorrectL1XE30toZB::Notify(){return kTRUE;}
Double_t CorrectL1XE30toZB::ComputeWeight(TF1* fitFunc)//{{{
{
    Float_t numerator = *HLT_noalg_L1XE30_prescale;
    Double_t denominator = fitFunc->Eval( *cell_met ); 
    return numerator / denominator; 
}//}}}
Bool_t CorrectL1XE30toZB::isGoodRun(){//{{{
    return (*RunNumber != 330203 && *RunNumber != 331975 && *RunNumber != 334487);
}//}}}
Bool_t CorrectL1XE30toZB::passedL1ZB(){//{{{
    return (*HLT_noalg_zb_L1ZB_passed);
}//}}}
Bool_t CorrectL1XE30toZB::inMuRange( Float_t a , Float_t b ){ //{{{
    return ( *InTimePileup > a && *InTimePileup < b );
} //}}}
Bool_t CorrectL1XE30toZB::isPassnoAlgL1XE30(){ // {{{
    return (*HLT_noalg_L1XE30_passed);
} // }}}
