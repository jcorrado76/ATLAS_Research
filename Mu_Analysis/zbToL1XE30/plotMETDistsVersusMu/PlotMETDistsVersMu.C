#define PlotMETDistsVersMu_cxx


#include "PlotMETDistsVersMu.h"

void PlotMETDistsVersMu::Begin(TTree *) // {{{
{
   TString option = GetOption();
   // definition of the TH1Fs and TEfficiency objects
    MET_Datamu0thru10 = new TH1D("metmu0thru10","ZB MET Data for actint between 0 and 10", met_dist_nbins , gevLow , gevHigh );
    MET_Datamu10thru20 = new TH1D("metmu10thru20","ZB MET Data for actint between 10 and 20", met_dist_nbins , gevLow , gevHigh );
    MET_Datamu20thru30 = new TH1D("metmu20thru30","ZB MET Data for actint between 20 and 30", met_dist_nbins , gevLow , gevHigh );
    MET_Datamu30thru40 = new TH1D("metmu30thru40","ZB MET Data for actint between 30 and 40", met_dist_nbins , gevLow , gevHigh );
    MET_Datamu40thru50 = new TH1D("metmu40thru50","ZB MET Data for actint between 40 and 50", met_dist_nbins , gevLow , gevHigh );
    MET_Datamu50thru60 = new TH1D("metmu50thru60","ZB MET Data for actint between 50 and 60", met_dist_nbins , gevLow , gevHigh );
    MET_Datamu60thru70 = new TH1D("metmu60thru70","ZB MET Data for actint between 60 and 70", met_dist_nbins , gevLow , gevHigh );
    MET_Algmu0thru10Efficiency = new TEfficiency("metmu0thru10Efficiency","MET Alg Efficiency for actint between 0 and 10", efficiency_nbins , gevLow , gevHigh );
    MET_Algmu10thru20Efficiency = new TEfficiency("metmu10thru20Efficiency","MET Alg Efficiency for actint between 10 and 20", efficiency_nbins , gevLow , gevHigh );
    MET_Algmu20thru30Efficiency = new TEfficiency("metmu20thru30Efficiency","MET Alg Efficiency for actint between 20 and 30", efficiency_nbins , gevLow , gevHigh );
    MET_Algmu30thru40Efficiency = new TEfficiency("metmu30thru40Efficiency","MET Alg Efficiency for actint between 30 and 40", efficiency_nbins , gevLow , gevHigh );
    MET_Algmu40thru50Efficiency = new TEfficiency("metmu40thru50Efficiency","MET Alg Efficiency for actint between 40 and 50", efficiency_nbins , gevLow , gevHigh );
    MET_Algmu50thru60Efficiency = new TEfficiency("metmu50thru60Efficiency","MET Alg Efficiency for actint between 50 and 60", efficiency_nbins , gevLow , gevHigh );
    MET_Algmu60thru70Efficiency = new TEfficiency("metmu60thru70Efficiency","MET Alg Efficiency for actint between 60 and 70", efficiency_nbins , gevLow , gevHigh );
} // }}}
Bool_t PlotMETDistsVersMu::Process(Long64_t entry)//{{{
{
   fReader.SetLocalEntry(entry);

   // if the event has passed HLT_noalg_zb_L1ZB_passed, and is not one of the bad run numbers
   if ( isHLT_zb_L1ZB()  && isGoodRun() ){
        // for mu range 0 to 10
       if ( inMuRange( 0.0 , 10.0) ){
            // fill the met distribution for this slice of mu, weighting it by the prescale that was used
           MET_Datamu0thru10->Fill(*MET_Data, *HLT_noalg_zb_L1ZB_prescale);
            // then fill the efficiency 
           MET_Algmu0thru10Efficiency->Fill(*L1_MET > XE, *MET_Data);
       }
       if ( inMuRange( 10.0, 20.0) ){
           MET_Datamu10thru20->Fill(*MET_Data, *HLT_noalg_zb_L1ZB_prescale);
           MET_Algmu10thru20Efficiency->Fill(*L1_MET > XE, *MET_Data);
       }
       if ( inMuRange( 20.0 , 30.0) ){
           MET_Datamu20thru30->Fill(*MET_Data, *HLT_noalg_zb_L1ZB_prescale);
           MET_Algmu20thru30Efficiency->Fill(*L1_MET > XE, *MET_Data);
       }
       if ( inMuRange( 30.0, 40.0) ){
           MET_Datamu30thru40->Fill(*MET_Data, *HLT_noalg_zb_L1ZB_prescale);
           MET_Algmu30thru40Efficiency->Fill(*L1_MET > XE, *MET_Data);
       }
       if ( inMuRange( 40.0 , 50.0 ) ){
           MET_Datamu40thru50->Fill(*MET_Data, *HLT_noalg_zb_L1ZB_prescale);
           MET_Algmu40thru50Efficiency->Fill(*L1_MET > XE, *MET_Data);
       }
       if ( inMuRange( 50.0 , 60.0 ) ){
           MET_Datamu50thru60->Fill(*MET_Data, *HLT_noalg_zb_L1ZB_prescale);
           MET_Algmu50thru60Efficiency->Fill(*L1_MET > XE, *MET_Data);
       }
       if ( inMuRange( 60.0 , 70.0 ) ){
           MET_Datamu60thru70->Fill(*MET_Data, *HLT_noalg_zb_L1ZB_prescale);
           MET_Algmu60thru70Efficiency->Fill(*L1_MET > XE, *MET_Data);
       }
   }
   return kTRUE;
}//}}}
void PlotMETDistsVersMu::Terminate() // Plotting{{{
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
    // WRITE TO FILE {{{
    TFile* Mu_Analysis_File = TFile::Open("./mu_analysis.root", "RECREATE");
    TDirectory* zb_met_distributions = Mu_Analysis_File->mkdir("zb_met");
    zb_met_distributions->cd();
    MET_Datamu0thru10->Write();
    MET_Datamu10thru20->Write();
    MET_Datamu20thru30->Write();
    MET_Datamu30thru40->Write();
    MET_Datamu40thru50->Write();
    MET_Datamu50thru60->Write();
    MET_Datamu60thru70->Write();

    TDirectory* efficiency_curves = Mu_Analysis_File->mkdir("efficiency_curves");
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
void PlotMETDistsVersMu::SlaveBegin(TTree * /*tree*/) // {{{
{
   TString option = GetOption();
} // }}}
void PlotMETDistsVersMu::SlaveTerminate(){}
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
Bool_t PlotMETDistsVersMu::isHLT_zb_L1ZB(){ //{{{
    return (*HLT_noalg_zb_L1ZB_passed);
} //}}}
Bool_t PlotMETDistsVersMu::isHLT_zb_L1XE30(){ //{{{
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
TEfficiency* PlotMETDistsVersMu::GetEfficiency(){
    return(MET_Algmu20thru30Efficiency);
}
