#define PlotMETDistsVersMu_cxx
#include "PlotMETDistsVersMu.h"
void PlotMETDistsVersMu::Begin(TTree *) // {{{
{
   TString option = GetOption();
   // fill Mu_Values
   for (int i = 0 ; i < Number_Mu_Bins + 1; i++){
       Mu_Values[i] = i * 10.;
   }
   int n;
   Float_t muLow;
   Float_t muHigh;
   TString Name;
   TString Title;
   TString EfficiencyName;
   TString EfficiencyTitle;
   for (int i = 0 ; i < Number_Mu_Bins-1 ; i++){
       muLow = Mu_Values[i+1];
       muHigh = Mu_Values[i+2];
       Name.Form("metmu%.0fthru%.0f" , muLow , muHigh );
       EfficiencyName.Form("metmu%.0fthru%.0fEfficiency", muLow , muHigh );
       Title.Form("ZeroBias MET Distribution for %s With Actint Between %.0f and %.0f" ,Alg_Name.Data(), muLow , muHigh );
       EfficiencyTitle.Form("Efficiency of L1XE 30 As a Function of %s for Actint Between %.0f and %.0f", Alg_Name.Data() , muLow , muHigh );

       MET_Distribution = new TH1F( Name , Title , met_dist_nbins , gevLow , gevHigh );
       Met_Distributions_By_Mu_Bin->push_back( MET_Distribution );

       MET_L1XE30Efficiency = new TEfficiency( EfficiencyName , EfficiencyTitle , efficiency_nbins , gevLow , gevHigh );
       L1XE30_Efficiency_Objects->push_back( MET_L1XE30Efficiency );

       MET_L1XE30EfficiencyFit = new TF1();
       L1XE30_Efficiency_Fit_Objects->push_back( MET_L1XE30EfficiencyFit );
   }
} // }}}
Bool_t PlotMETDistsVersMu::Process(Long64_t entry)//{{{
{
   fReader.SetLocalEntry(entry);

   // if the event has passed HLT_noalg_zb_L1ZB_passed, and is not one of the bad run numbers
   if ( isHLT_zb_L1ZB()  && isGoodRun() ){
       Float_t muLow, muHigh;
       for ( int i = 0; i < Number_Mu_Bins ; i++ ){
           muLow = Mu_Values[ i ];
           muHigh = Mu_Values[ i + 1 ];
           if ( inMuRange( muLow , muHigh ) ){
               for ( int j = 0 ; j < Number_Mu_Bins ; j++ ){
                   (Met_Distributions_By_Mu_Bin->at(j))->Fill(*MET_Data , *HLT_noalg_zb_L1ZB_prescale);
                   (L1XE30_Efficiency_Objects->at(j))->Fill(*L1_MET > XE , *MET_Data);
               }
           }
       }
   }
   return kTRUE;
}//}}}
void PlotMETDistsVersMu::Terminate() //{{{
{
   for ( int i = 0; i < Number_Mu_Bins ; i++ ){
       (L1XE30_Efficiency_Objects->at(i))->SetLineColor( Colors[i] );
       (L1XE30_Efficiency_Objects->at(i))->SetMarkerStyle( Colors[i] );
       (L1XE30_Efficiency_Fit_Objects->at(i)) = generateFitFunction( L1XE30_Efficiency_Objects->at(i) );
       (L1XE30_Efficiency_Fit_Objects->at(i))->SetLineColor( Colors[i] );
       (Met_Distributions_By_Mu_Bin->at(i))->SetLineColor( Colors[i] );
       Normalized_Met_Distributions->push_back( (TH1F*)(Met_Distributions_By_Mu_Bin->at(i))->Clone());
       (Normalized_Met_Distributions->at(i))->SetNormFactor(1.);
   }
    // WRITE TO FILE {{{
    TFile* Mu_Analysis_File = TFile::Open("mu_analysis.root", "RECREATE");
    TDirectory* zb_met_distributions = Mu_Analysis_File->mkdir("zb_met_distributions");
    zb_met_distributions->cd();
    for ( int  i = 0 ; i < Number_Mu_Bins ; i++ ){
        (Met_Distributions_By_Mu_Bin->at(i))->Write();
    }

    TDirectory* efficiency_curves = Mu_Analysis_File->mkdir("l1xe30_efficiency_curves");
    efficiency_curves->cd();
    for ( int  i = 0 ; i < Number_Mu_Bins ; i++ ){
        (L1XE30_Efficiency_Objects->at(i))->Write();
    }

    TDirectory* L1XE30_Efficiency_Fit_Objects_Dir = Mu_Analysis_File->mkdir("l1xe30_efficiency_fits");
    L1XE30_Efficiency_Fit_Objects_Dir->cd();
    for ( int  i = 0 ; i < Number_Mu_Bins ; i++ ){
        (L1XE30_Efficiency_Fit_Objects->at(i))->Write();
    }

    Mu_Analysis_File->Close();//}}}
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
