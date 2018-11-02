#define PlotMETDistsVersMu_cxx
#include "ComputeL1XE50toL1XE30Efficiency.h"
void ComputeL1XE50toL1XE30Efficiency::Begin(TTree *) // {{{
{
   TString option = GetOption();
   // fill Mu_Values
   for (int i = 0 ; i < Number_Mu_Bins + 1; i++){
       Mu_Values[i] = i * 10.;
   }
   Int_t n;
   Float_t muLow;
   Float_t muHigh;
   TString Name;
   TString Title;
   TString EfficiencyName;
   TString EfficiencyTitle;
   for (int i = 0 ; i < Number_Mu_Bins ; i++){
       muLow = Mu_Values[i];
       muHigh = Mu_Values[i+1];
       std::cout << "Mu between: " << muLow << " and " << muHigh << std::endl;
       Name.Form("metmu%.0fthru%.0f" , muLow , muHigh );
       EfficiencyName.Form("metmu%.0fthru%.0fEfficiency", muLow , muHigh );
       Title.Form("L1 XE 30 MET Distribution for %s With Actint Between %.0f and %.0f" ,Alg_Name.Data(), muLow , muHigh );
       EfficiencyTitle.Form("Efficiency of L1XE 50 As a Function of %s for Actint Between %.0f and %.0f", Alg_Name.Data() , muLow , muHigh );

       Met_Distributions_By_Mu_Bin[i] = new TH1F( Name , Title , met_dist_nbins , gevLow , gevHigh );
       L1XE50_Efficiency_Objects[i] = new TEfficiency( EfficiencyName , EfficiencyTitle , efficiency_nbins , gevLow , gevHigh );
       L1XE50_Efficiency_Fit_Objects[i] = new TF1();
   }
} // }}}
Bool_t ComputeL1XE50toL1XE30Efficiency::Process(Long64_t entry)//{{{
{
   fReader.SetLocalEntry(entry);
   // if the event has passed HLT_noalg_zb_L1ZB_passed, and is not one of the bad run numbers
   if ( isHLT_zb_L1XE30()  && isGoodRun() ){
       Float_t muLo , muHi;
       for ( int i = 0; i < Number_Mu_Bins ; i++ ){
           muLow = Mu_Values[ i ];
           muHigh = Mu_Values[ i + 1 ];
           if ( inMuRange( muLo , muHi ) ){
               for ( int j = 0 ; j < Number_Mu_Bins ; j++ ){
                   Met_Distributions_By_Mu_Bin[j]->Fill(*MET_Data , *HLT_noalg_L1XE30_prescale);
                   L1XE50_Efficiency_Objects[j]->Fill(*L1_MET > XE , *MET_Data);
               }
           }
       }
   }
   return kTRUE;
}//}}}
void ComputeL1XE50toL1XE30Efficiency::Terminate() // Plotting{{{
{
    // GENERATE FIT FUNCTIONS{{{
    TF1* mu0thru10FitFunction = generateFitFunction( MET_Algmu0thru10Efficiency );
    TF1* mu10thru20FitFunction = generateFitFunction( MET_Algmu10thru20Efficiency);
    TF1* mu20thru30FitFunction = generateFitFunction( MET_Algmu20thru30Efficiency);
    TF1* mu30thru40FitFunction = generateFitFunction( MET_Algmu30thru40Efficiency);
    TF1* mu40thru50FitFunction = generateFitFunction( MET_Algmu40thru50Efficiency);
    TF1* mu50thru60FitFunction = generateFitFunction( MET_Algmu50thru60Efficiency);
    TF1* mu60thru70FitFunction = generateFitFunction( MET_Algmu60thru70Efficiency);//}}}
    // FORMATTING ZB DATA {{{
    MET_Datamu0thru10->SetLineColor(1);
    MET_Datamu10thru20->SetLineColor(2);
    MET_Datamu20thru30->SetLineColor(3);
    MET_Datamu30thru40->SetLineColor(4);
    MET_Datamu40thru50->SetLineColor(12);
    MET_Datamu50thru60->SetLineColor(6);
    MET_Datamu60thru70->SetLineColor(9);
    // Make Copies for Normalization
    TH1F* MET_Datamu0thru10_Copy = (TH1F*) MET_Datamu0thru10->Clone();
    TH1F* MET_Datamu10thru20_Copy = (TH1F*) MET_Datamu10thru20->Clone();
    TH1F* MET_Datamu20thru30_Copy = (TH1F*) MET_Datamu20thru30->Clone();
    TH1F* MET_Datamu30thru40_Copy = (TH1F*) MET_Datamu30thru40->Clone();
    TH1F* MET_Datamu40thru50_Copy = (TH1F*) MET_Datamu40thru50->Clone();
    TH1F* MET_Datamu50thru60_Copy = (TH1F*) MET_Datamu50thru60->Clone();
    TH1F* MET_Datamu60thru70_Copy = (TH1F*) MET_Datamu60thru70->Clone();//}}}
    // normalize to 1 
    MET_Datamu0thru10_Copy->SetNormFactor(1.);
    MET_Datamu10thru20_Copy->SetNormFactor(1.);
    MET_Datamu20thru30_Copy->SetNormFactor(1.);
    MET_Datamu30thru40_Copy->SetNormFactor(1.);
    MET_Datamu40thru50_Copy->SetNormFactor(1.);
    MET_Datamu50thru60_Copy->SetNormFactor(1.);
    MET_Datamu60thru70_Copy->SetNormFactor(1.);//}}}
    // PLOT ZB DATA{{{
    TCanvas* zb_met_dists = new TCanvas("zb_met_plot","Plot of MET Distribution in Mu Slices");
    MET_Datamu0thru10_Copy->Draw();
    MET_Datamu10thru20_Copy->Draw("SAME");
    MET_Datamu20thru30_Copy->Draw("SAME");
    MET_Datamu30thru40_Copy->Draw("SAME");
    MET_Datamu40thru50_Copy->Draw("SAME");
    MET_Datamu50thru60_Copy->Draw("SAME");
    MET_Datamu60thru70_Copy->Draw("SAME");
    TLegend* met_dist_legend = new TLegend();
    met_dist_legend->AddEntry(MET_Datamu0thru10);
    met_dist_legend->AddEntry(MET_Datamu10thru20);
    met_dist_legend->AddEntry(MET_Datamu20thru30);
    met_dist_legend->AddEntry(MET_Datamu30thru40);
    met_dist_legend->AddEntry(MET_Datamu40thru50);
    met_dist_legend->AddEntry(MET_Datamu50thru60);
    met_dist_legend->AddEntry(MET_Datamu60thru70);
    met_dist_legend->Draw("SAME");
    gPad->SetLogy();
    gStyle->SetOptStat(0);
    zb_met_dists->Print("../Plots/CorrectedAndZB/ZB_MET_Distributions.png");
    //}}}
    // FORMATTING EFFICIENCY CURVES{{{
    MET_Algmu0thru10Efficiency->SetLineColor(1);
    MET_Algmu10thru20Efficiency->SetLineColor(2);
    MET_Algmu20thru30Efficiency->SetLineColor(3);
    MET_Algmu30thru40Efficiency->SetLineColor(4);
    MET_Algmu40thru50Efficiency->SetLineColor(12);
    MET_Algmu50thru60Efficiency->SetLineColor(6);
    MET_Algmu60thru70Efficiency->SetLineColor(9);
    // set marker style of efficiency curves
    MET_Algmu0thru10Efficiency->SetMarkerStyle(29);
    MET_Algmu10thru20Efficiency->SetMarkerStyle(20);
    MET_Algmu20thru30Efficiency->SetMarkerStyle(3);
    MET_Algmu30thru40Efficiency->SetMarkerStyle(4);
    MET_Algmu40thru50Efficiency->SetMarkerStyle(27);
    MET_Algmu50thru60Efficiency->SetMarkerStyle(22);
    MET_Algmu60thru70Efficiency->SetMarkerStyle(21);//}}}
    // PLOT EFFICIENCY CURVES {{{
    TCanvas* efficiency_plot = new TCanvas("efficiencyPlot", "MET Efficiency Slices in Mu");
    MET_Algmu10thru20Efficiency->Draw();
    MET_Algmu20thru30Efficiency->Draw("SAME");
    MET_Algmu30thru40Efficiency->Draw("SAME");
    MET_Algmu40thru50Efficiency->Draw("SAME");
    MET_Algmu50thru60Efficiency->Draw("SAME");
    MET_Algmu60thru70Efficiency->Draw("SAME");
    MET_Algmu0thru10Efficiency->Draw("SAME");
    TLegend* efficiency_legend = new TLegend();
    efficiency_legend->AddEntry(MET_Algmu0thru10Efficiency);
    efficiency_legend->AddEntry(MET_Algmu10thru20Efficiency);
    efficiency_legend->AddEntry(MET_Algmu20thru30Efficiency);
    efficiency_legend->AddEntry(MET_Algmu30thru40Efficiency);
    efficiency_legend->AddEntry(MET_Algmu40thru50Efficiency);
    efficiency_legend->AddEntry(MET_Algmu50thru60Efficiency);
    efficiency_legend->AddEntry(MET_Algmu60thru70Efficiency);
    efficiency_legend->Draw("SAME");
    gStyle->SetOptStat(0);//}}}
    efficiency_plot->Print("../Plots/ZB_MET_Efficiency.png");
    // WRITE TO FILE {{{
    TFile* Mu_Analysis_File = TFile::Open("mu_analysis.root", "UPDATE");
    TDirectory* l1xe30_jetm10_distributions = Mu_Analysis_File->mkdir("l1xe30_jetm10data");
    l1xe30_jetm10_distributions->cd();
    MET_Datamu0thru10->Write();
    MET_Datamu10thru20->Write();
    MET_Datamu20thru30->Write();
    MET_Datamu30thru40->Write();
    MET_Datamu40thru50->Write();
    MET_Datamu50thru60->Write();
    MET_Datamu60thru70->Write();

    TDirectory* efficiency_curves = Mu_Analysis_File->mkdir("l1xe50efficiencies");
    efficiency_curves->cd();
    MET_Algmu0thru10Efficiency->Write();
    MET_Algmu10thru20Efficiency->Write();
    MET_Algmu20thru30Efficiency->Write();
    MET_Algmu30thru40Efficiency->Write();
    MET_Algmu40thru50Efficiency->Write();
    MET_Algmu50thru60Efficiency->Write();
    MET_Algmu60thru70Efficiency->Write();

    Mu_Analysis_File->Close();//}}}
}//}}}
void ComputeL1XE50toL1XE30Efficiency::SlaveBegin(TTree * /*tree*/) // {{{
{
   TString option = GetOption();
} // }}}
void ComputeL1XE50toL1XE30Efficiency::SlaveTerminate(){}
void ComputeL1XE50toL1XE30Efficiency::Init(TTree *tree) //{{{
{
   fReader.SetTree(tree);
} //}}}
Bool_t ComputeL1XE50toL1XE30Efficiency::Notify() //{{{
{
   return kTRUE;
} //}}}
Bool_t ComputeL1XE50toL1XE30Efficiency::isGoodRun(){ //{{{
    return (*RunNumber != 330203 && *RunNumber != 331975 && *RunNumber != 334487);
} // }}}
Bool_t ComputeL1XE50toL1XE30Efficiency::isHLT_zb_L1ZB(){ //{{{
    return (*HLT_noalg_zb_L1ZB_passed);
} //}}}
Bool_t ComputeL1XE50toL1XE30Efficiency::isHLT_zb_L1XE30(){ //{{{
    return (*HLT_noalg_L1XE30_passed);
} //}}}
Bool_t ComputeL1XE50toL1XE30Efficiency::inMuRange( Float_t a , Float_t b ){ //{{{
    return ( *InTimePileup > a && *InTimePileup < b );
} //}}}
Double_t ComputeL1XE50toL1XE30Efficiency::fitFunction(Double_t *x , Double_t *par ){//{{{
    Float_t xx = x[0];
    Double_t l1cut = 30.0;
    Double_t fitval = (1./2.)*(1.+TMath::Erf((par[0]*x[0]+par[1]-l1cut)/(par[2]*TMath::Sqrt(2.))));
    return fitval;
}//}}}
TF1* ComputeL1XE50toL1XE30Efficiency::generateFitFunction(TEfficiency* teff_obj, float gevMax, float initial_slope, float initial_intercept, float initial_sigma ){//{{{
    TF1 *fitErrorFunction = new TF1("fitFunction",fitFunction,0.0,gevMax,3);
    fitErrorFunction->SetParameter(0, initial_slope);
    fitErrorFunction->SetParameter(1, initial_intercept);
    fitErrorFunction->SetParameter(2, initial_sigma);
    //initializing parameters reasonably is important because it is a maximum likelihood fit
    fitErrorFunction->SetParNames("Slope","Translation","Sigma");
    //"R" tells the fit function from BinomialEfficiency::Fit to use the range of the TF1 as the fitting range
    teff_obj->Fit( fitErrorFunction  , "R+");

    std::cout << "Value of fit for a: " << fitErrorFunction->GetParameter(0) << std::endl;
    std::cout << "Value of error on a: " << fitErrorFunction->GetParError(0) << std::endl;
    std::cout << "Value of fit for b: " << fitErrorFunction->GetParameter(1) << std::endl;
    std::cout << "Value of error on b: " << fitErrorFunction->GetParError(1) << std::endl;
    std::cout << "Value of fit for sigma: " << fitErrorFunction->GetParameter(2) << std::endl;
    std::cout << "Value of error on sigma: " << fitErrorFunction->GetParError(2) << std::endl;
    return fitErrorFunction;
}//}}}
