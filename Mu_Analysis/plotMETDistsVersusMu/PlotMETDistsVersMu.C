#define PlotMETDistsVersMu_cxx


#include "PlotMETDistsVersMu.h"

void PlotMETDistsVersMu::Begin(TTree *) // {{{
{
   TString option = GetOption();
    MET_Datamu0thru10 = new TH1F("metmu0thru10","MET Data for actint between 0 and 10", nbins , gevLow , gevHigh );
    MET_Datamu10thru20 = new TH1F("metmu10thru20","MET Data for actint between 10 and 20", nbins , gevLow , gevHigh );
    MET_Datamu20thru30 = new TH1F("metmu20thru30","MET Data for actint between 20 and 30", nbins , gevLow , gevHigh );
    MET_Datamu30thru40 = new TH1F("metmu30thru40","MET Data for actint between 30 and 40", nbins , gevLow , gevHigh );
    MET_Datamu40thru50 = new TH1F("metmu40thru50","MET Data for actint between 40 and 50", nbins , gevLow , gevHigh );
    MET_Datamu50thru60 = new TH1F("metmu50thru60","MET Data for actint between 50 and 60", nbins , gevLow , gevHigh );
    MET_Datamu60thru70 = new TH1F("metmu60thru70","MET Data for actint between 60 and 70", nbins , gevLow , gevHigh );
    MET_Algmu0thru10Efficiency = new TEfficiency("metmu0thru10Efficiency","MET Alg Efficiency for actint between 0 and 10", nbins , gevLow , gevHigh );
    MET_Algmu10thru20Efficiency = new TEfficiency("metmu10thru20Efficiency","MET Alg Efficiency for actint between 10 and 20", nbins , gevLow , gevHigh );
    MET_Algmu20thru30Efficiency = new TEfficiency("metmu20thru30Efficiency","MET Alg Efficiency for actint between 20 and 30", nbins , gevLow , gevHigh );
    MET_Algmu30thru40Efficiency = new TEfficiency("metmu30thru40Efficiency","MET Alg Efficiency for actint between 30 and 40", nbins , gevLow , gevHigh );
    MET_Algmu40thru50Efficiency = new TEfficiency("metmu40thru50Efficiency","MET Alg Efficiency for actint between 40 and 50", nbins , gevLow , gevHigh );
    MET_Algmu50thru60Efficiency = new TEfficiency("metmu50thru60Efficiency","MET Alg Efficiency for actint between 50 and 60", nbins , gevLow , gevHigh );
    MET_Algmu60thru70Efficiency = new TEfficiency("metmu60thru70Efficiency","MET Alg Efficiency for actint between 60 and 70", nbins , gevLow , gevHigh );
} // }}}

void PlotMETDistsVersMu::SlaveBegin(TTree * /*tree*/) // {{{
{
   TString option = GetOption();
} // }}}

Bool_t PlotMETDistsVersMu::Process(Long64_t entry)//{{{
{
   fReader.SetLocalEntry(entry);

   if ( passedL1ZB()  && isGoodRun() ){
       if ( inMuRange( 0.0 , 10.0) ){
           MET_Datamu0thru10->Fill(*MET_Data, *HLT_noalg_zb_L1ZB_prescale);
           MET_Algmu0thru10Efficiency->Fill(*L1_MET > XE, *cell_met);
       }
       if ( inMuRange( 10.0, 20.0) ){
           MET_Datamu10thru20->Fill(*MET_Data, *HLT_noalg_zb_L1ZB_prescale);
           MET_Algmu10thru20Efficiency->Fill(*L1_MET > XE, *cell_met);
       }
       if ( inMuRange( 20.0 , 30.0) ){
           MET_Datamu20thru30->Fill(*MET_Data, *HLT_noalg_zb_L1ZB_prescale);
           MET_Algmu20thru30Efficiency->Fill(*L1_MET > XE, *cell_met);
       }
       if ( inMuRange( 30.0, 40.0) ){
           MET_Datamu30thru40->Fill(*MET_Data, *HLT_noalg_zb_L1ZB_prescale);
           MET_Algmu30thru40Efficiency->Fill(*L1_MET > XE, *cell_met);
       }
       if ( inMuRange( 40.0 , 50.0 ) ){
           MET_Datamu40thru50->Fill(*MET_Data, *HLT_noalg_zb_L1ZB_prescale);
           MET_Algmu40thru50Efficiency->Fill(*L1_MET > XE, *cell_met);
       }
       if ( inMuRange( 50.0 , 60.0 ) ){
           MET_Datamu50thru60->Fill(*MET_Data, *HLT_noalg_zb_L1ZB_prescale);
           MET_Algmu50thru60Efficiency->Fill(*L1_MET > XE, *cell_met);
       }
       if ( inMuRange( 60.0 , 70.0 ) ){
           MET_Datamu60thru70->Fill(*MET_Data, *HLT_noalg_zb_L1ZB_prescale);
           MET_Algmu60thru70Efficiency->Fill(*L1_MET > XE, *cell_met);
       }
   }
   return kTRUE;
}//}}}

void PlotMETDistsVersMu::SlaveTerminate(){}

void PlotMETDistsVersMu::Terminate() // Plotting{{{
{
    // color the histograms so we can see difference 
    MET_Datamu0thru10->SetLineColor(1);
    MET_Datamu10thru20->SetLineColor(2);
    MET_Datamu20thru30->SetLineColor(3);
    MET_Datamu30thru40->SetLineColor(4);
    MET_Datamu40thru50->SetLineColor(12);
    MET_Datamu50thru60->SetLineColor(6);
    MET_Datamu60thru70->SetLineColor(9);

    // normalize to 1 
    MET_Datamu0thru10->SetNormFactor(1.);
    MET_Datamu10thru20->SetNormFactor(1.);
    MET_Datamu20thru30->SetNormFactor(1.);
    MET_Datamu30thru40->SetNormFactor(1.);
    MET_Datamu40thru50->SetNormFactor(1.);
    MET_Datamu50thru60->SetNormFactor(1.);
    MET_Datamu60thru70->SetNormFactor(1.);

    MET_Datamu0thru10->Draw();
    MET_Datamu10thru20->Draw("SAME");
    MET_Datamu20thru30->Draw("SAME");
    MET_Datamu30thru40->Draw("SAME");
    MET_Datamu40thru50->Draw("SAME");
    MET_Datamu50thru60->Draw("SAME");
    MET_Datamu60thru70->Draw("SAME");
    mycanv->SetTitle("MET Slices in Mu");
    gPad->SetLogy();
    TLegend* legend = new TLegend();
    legend->AddEntry(MET_Datamu0thru10);
    legend->AddEntry(MET_Datamu10thru20);
    legend->AddEntry(MET_Datamu20thru30);
    legend->AddEntry(MET_Datamu30thru40);
    legend->AddEntry(MET_Datamu40thru50);
    legend->AddEntry(MET_Datamu50thru60);
    legend->AddEntry(MET_Datamu60thru70);
    legend->Draw("SAME");
    gStyle->SetOptStat(0);

    TCanvas* mycanv = new TCanvas("efficiencyPlot", "MET Efficiency Slices in Mu");
    TF1* mu0thru10FitFunction = generateFitFunction( MET_Algmu0thru10Efficiency );
    TF1* mu10thru20FitFunction = generateFitFunction( MET_Algmu10thru20Efficiency);
    TF1* mu20thru30FitFunction = generateFitFunction( MET_Algmu20thru30Efficiency);
    TF1* mu30thru40FitFunction = generateFitFunction( MET_Algmu30thru40Efficiency);
    TF1* mu40thru50FitFunction = generateFitFunction( MET_Algmu40thru50Efficiency);
    TF1* mu50thru60FitFunction = generateFitFunction( MET_Algmu50thru60Efficiency);
    TF1* mu60thru70FitFunction = generateFitFunction( MET_Algmu60thru70Efficiency);

    // set line color of efficiency curves
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
    MET_Algmu60thru70Efficiency->SetMarkerStyle(21);
    // draw the efficiency curves
    MET_Algmu10thru20Efficiency->Draw();
    MET_Algmu20thru30Efficiency->Draw("SAME");
    MET_Algmu30thru40Efficiency->Draw("SAME");
    MET_Algmu40thru50Efficiency->Draw("SAME");
    MET_Algmu50thru60Efficiency->Draw("SAME");
    MET_Algmu60thru70Efficiency->Draw("SAME");
    MET_Algmu0thru10Efficiency->Draw("SAME");

    
    mycanv->SetTitle("MET Slices in Mu");
    //gPad->SetLogy();
    TLegend* legend = new TLegend();
    legend->AddEntry(MET_Algmu0thru10Efficiency);
    legend->AddEntry(MET_Algmu10thru20Efficiency);
    legend->AddEntry(MET_Algmu20thru30Efficiency);
    legend->AddEntry(MET_Algmu30thru40Efficiency);
    legend->AddEntry(MET_Algmu40thru50Efficiency);
    legend->AddEntry(MET_Algmu50thru60Efficiency);
    legend->AddEntry(MET_Algmu60thru70Efficiency);
    legend->Draw("SAME");
    gStyle->SetOptStat(0);


    TFile* Mu_Analysis_File = TFile::Open("../Root_Files/mu_analysis.root", "RECREATE");
    TDirectory* zb_met_distributions = MET_Dist_File->mkdir("zb_met");
    zb_met_distributions->cd();
    MET_Datamu0thru10->Write();
    MET_Datamu10thru20->Write();
    MET_Datamu20thru30->Write();
    MET_Datamu30thru40->Write();
    MET_Datamu40thru50->Write();
    MET_Datamu50thru60->Write();
    MET_Datamu60thru70->Write();

    TDirectory* efficiency_curves = MET_Dist_File->mkdir("efficiency_curves");
    efficiency_curves->cd();
    MET_Algmu0thru10Efficiency->Write();
    MET_Algmu10thru20Efficiency->Write();
    MET_Algmu20thru30Efficiency->Write();
    MET_Algmu30thru40Efficiency->Write();
    MET_Algmu40thru50Efficiency->Write();
    MET_Algmu50thru60Efficiency->Write();
    MET_Algmu60thru70Efficiency->Write();

    Mu_Analysis_File->Close();
}//}}}
void PlotMETDistsVersMu::Init(TTree *tree) //{{{
{
   fReader.SetTree(tree);
} //}}}
Bool_t PlotMETDistsVersMu::Notify() //{{{
{
   return kTRUE;
} //}}}
Bool_t PlotMETDistsVersMu::isGoodRun(){ //{{{
    return (*RunNumber != 330203 && *RunNumber != 331975 && *RunNumber != 334487);
} // }}}
Bool_t PlotMETDistsVersMu::passedL1ZB(){ //{{{
    return (*HLT_noalg_zb_L1ZB_passed);
} //}}}
Bool_t PlotMETDistsVersMu::isPassnoAlgXE30(){ //{{{
    return (*HLT_noalg_L1XE30_passed);
} //}}}
Bool_t PlotMETDistsVersMu::inMuRange( Float_t a , Float_t b ){ //{{{
    return ( *InTimePileup > a && *InTimePileup < b );
} //}}}
Double_t PlotMETDistsVersMu::fitFunction(Double_t *x , Double_t *par ){//{{{
    Float_t xx = x[0];
    Double_t l1cut = 30.0;
    Double_t fitval = (1./2.)*(1.+TMath::Erf((par[0]*x[0]+par[1]-l1cut)/(par[2]*TMath::Sqrt(2.))));
    return fitval;
}//}}}

TF1* PlotMETDistsVersMu::generateFitFunction(TEfficiency* teff_obj, float gevMax, float initial_slope, float initial_intercept, float initial_sigma ){//{{{
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
