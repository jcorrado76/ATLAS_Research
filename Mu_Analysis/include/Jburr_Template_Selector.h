#ifndef Jburr_Template_Selector_h
#define Jburr_Template_Selector_h
// includes{{{
#include <TROOT.h>
#include <TEfficiency.h>
#include <TChain.h>
#include <TF1.h>
#include <TMath.h>
#include <TFile.h>
#include <TSelector.h>
#include <TTreeReader.h>
#include <TTreeReaderValue.h>
#include <TTreeReaderArray.h>
#include <TH2.h>
#include <TStyle.h>
#include <vector>
#include <TH1.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TPad.h>
#include <TDirectory.h>
#include <TGaxis.h>
#include <array>
#include <cmath>
#include <TObjArray.h>
// end includes}}}
//class definition {{{
class Jburr_Template_Selector : public TSelector {
public :
   // Member Variables {{{
   TTreeReader     fReader;
   TTree          *fChain =                                                     0;   //!pointer to the analyzed TTree or TChain
   const static Int_t Number_Mu_Bins =                                          7;   // 7 mu bins
   constexpr static Float_t gevLow =                                                       0.0;
   constexpr static Float_t gevHigh =                                                      300.0;
   constexpr static Float_t met_dist_binwidth =                                            5.0; // 5 GeV bins
   constexpr static Float_t efficiency_bin_width =                                         20.0; // 20 GeV bins
   float L1XE =                                                                  0.0;    
   const static Int_t met_dist_nbins =                                        (gevHigh - gevLow) / met_dist_binwidth; 
   const static Int_t efficiency_nbins =                                      (gevHigh - gevLow) / efficiency_bin_width;
   const static Int_t Number_Scale_Factor_Samples =             3; // number of points used in weighted average to compute relative normalization scale factor
   // collections
   TObjArray* HLT_ZB_L1ZB_MET_Distributions_by_Mubin = new TObjArray();
   TObjArray* HLT_ZB_L1XE30_MET_Distributions_by_Mubin = new TObjArray();
   TObjArray* HLT_ZB_L1XE50_MET_Distributions_by_Mubin = new TObjArray();

   TObjArray* HLT_ZB_L1XE30_Corrected_to_ZB_MET_Distribution = new TObjArray();
   TObjArray* HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution = new TObjArray();

   TObjArray* L1XE30_Efficiency_Objects = new TObjArray();
   TObjArray* L1XE50_Efficiency_Objects = new TObjArray();

   TObjArray* L1XE30_Efficiency_Fit_Objects = new TObjArray();
   TObjArray* L1XE50_Efficiency_Fit_Objects = new TObjArray();
   
   // styling options
   Float_t Mu_Values[Number_Mu_Bins+1] =                    { 0.0 };
   int Colors[Number_Mu_Bins] =                           {1,2,3,4,5,6,9};
   Int_t MarkerStyles[Number_Mu_Bins] =                     {29,20,3,4,27,22,21};
   Int_t lineWidth = 5;

   // left edge of interval to sample from for scale factors
   Int_t Normalization_Bin_Number[Number_Mu_Bins] =        {4,14,14,14,14,14,14};

   Double_t L1XE30Scale_Factors[Number_Mu_Bins][Number_Scale_Factor_Samples] =                  { 0.0 };
   Double_t L1XE30Scale_Factor_Errors[Number_Mu_Bins][Number_Scale_Factor_Samples] =                  { 0.0 };
   Double_t L1XE50Scale_Factors[Number_Mu_Bins][Number_Scale_Factor_Samples] =                  { 0.0 };
   Double_t L1XE50Scale_Factor_Errors[Number_Mu_Bins][Number_Scale_Factor_Samples] =                  { 0.0 };

   // keep track of the fit parameters and their errors
   // as well as the errors on each of the bin of the MET distributions for each mu bin
   Double_t RootZBErrVersMyErrL2Norm[Number_Mu_Bins][met_dist_nbins] = {0.0};
   Double_t ZBErrors[Number_Mu_Bins][met_dist_nbins] =    { 0.0 };
   Double_t L1XE30CorrectedToZBErrors[Number_Mu_Bins][met_dist_nbins] =    { 0.0 };
   Double_t L1XE50CorrectedToZBErrors[Number_Mu_Bins][met_dist_nbins] =    { 0.0 };
   Double_t L1XE30fitPars[Number_Mu_Bins][3];
   Double_t L1XE30fitParsErrs[Number_Mu_Bins][3];
   Double_t L1XE50fitPars[Number_Mu_Bins][3];
   Double_t L1XE50fitParsErrs[Number_Mu_Bins][3];

   Float_t muLow;
   Float_t muHigh;
   TString Name;
   TString Title;
   TString Corrected_Name;
   TString Corrected_Title;
   TString EfficiencyName;
   TString EfficiencyTitle;

   TString Alg_Name =                       "CELL MET";
   TString zb_alg_name =                    "cell.met"; 
   TString l1_alg_name =                    "L1.met";
   TString efficiency_yaxis =               "efficiency";
   TString met_dist_yaxis =                 "Number of Entries";
   TString efficiency_title =               zb_alg_name + " Efficiency";
   TString efficiency_xaxis =               zb_alg_name + " [GeV]";
   TString met_dist_xaxis =                 zb_alg_name + " [GeV]";
   TString plots_dir =                      "plots/";
   // }}}
   // Member Functions {{{
   // Default Constructor {{{
   Jburr_Template_Selector(){ 
       for (int i = 0 ; i < Number_Mu_Bins; i++){
           Mu_Values[i] = i * 10.;
           Mu_Values[i+1] = (i+1) * 10.;
        }
   }//}}}
   ~Jburr_Template_Selector() { }
   virtual Int_t   Version() const { return 2; }
   virtual void    Begin(TTree *tree);
   virtual void    SlaveBegin(TTree *tree);
   virtual void    Init(TTree *tree);
   Bool_t  Notify();
   virtual Bool_t  Process(Long64_t entry);
   virtual Int_t   GetEntry(Long64_t entry, Int_t getall = 0) { return fChain ? fChain->GetTree()->GetEntry(entry, getall) : 0; }
   virtual void    SetOption(const char *option) { fOption = option; }
   virtual void    SetObject(TObject *obj) { fObject = obj; }
   virtual void    SetInputList(TList *input) { fInput = input; }
   virtual TList  *GetOutputList() const { return fOutput; }
   virtual void    SlaveTerminate();
   virtual void    Terminate();
   Bool_t isGoodRun();
   Bool_t isHLT_zb_L1ZB();
   Bool_t isHLT_zb_L1XE30();
   Bool_t isHLT_zb_L1XE50();
   Bool_t inMuRange( Float_t , Float_t );
   // getters{{{
   TObjArray* Get_HLT_ZB_L1ZB_MET_Distributions_by_Mubin() const { return HLT_ZB_L1ZB_MET_Distributions_by_Mubin; }
   TObjArray* Get_HLT_ZB_L1XE30_MET_Distributions_by_Mubin() const { return HLT_ZB_L1XE30_MET_Distributions_by_Mubin; }
    TObjArray* Get_HLT_ZB_L1XE30_Corrected_to_ZB_MET_Distribution() const { return HLT_ZB_L1XE30_Corrected_to_ZB_MET_Distribution; }
    TObjArray* Get_HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution() const { return HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution; }
    TObjArray* Get_L1XE30_Efficiency_Objects() const { return L1XE30_Efficiency_Objects; }
    TObjArray* Get_L1XE50_Efficiency_Objects() const { return L1XE50_Efficiency_Objects; }
    TObjArray* Get_L1XE30_Efficiency_Fit_Objects() const { return L1XE30_Efficiency_Fit_Objects; }
    TObjArray* Get_L1XE50_Efficiency_Fit_Objects() const { return L1XE50_Efficiency_Fit_Objects; }
    Int_t GetNumberMuBins() const {return Number_Mu_Bins; }//}}}
    // setters{{{
   void Set_HLT_ZB_L1ZB_MET_Distributions_by_Mubin(TObjArray* const other){ HLT_ZB_L1ZB_MET_Distributions_by_Mubin = other; }
   void Set_HLT_ZB_L1XE30_MET_Distributions_by_Mubin(TObjArray* const other){ HLT_ZB_L1XE30_MET_Distributions_by_Mubin = other ; }
   void Set_HLT_ZB_L1XE30_Corrected_to_ZB_MET_Distribution(TObjArray* const other){ HLT_ZB_L1XE30_Corrected_to_ZB_MET_Distribution = other ; }
   void Set_HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution(TObjArray* const other){ HLT_ZB_L1XE50_Corrected_to_ZB_MET_Distribution = other ; }
   void Set_L1XE30_Efficiency_Objects(TObjArray* const other){ L1XE30_Efficiency_Objects = other ; }
   void Set_L1XE50_Efficiency_Objects(TObjArray* const other){ L1XE50_Efficiency_Objects = other ; }
   void Set_L1XE30_Efficiency_Fit_Objects(TObjArray* const other){ L1XE30_Efficiency_Fit_Objects = other ; }
   void Set_L1XE50_Efficiency_Fit_Objects(TObjArray* const other){ L1XE50_Efficiency_Fit_Objects = other; }//}}}
   TF1* generateFitFunction(TEfficiency* teff_obj, float L1XE = 0.0 , int i = 0 , float initial_slope = 0.1 , 
           float initial_intercept = 0.0, float initial_sigma = 10.0,  Bool_t verbose=false );
   Double_t ComputeWeight(TF1* fitFunc, TF1* fitFunc2 = NULL);
   static double L1XE30fitFunction(double *x , double *par );
   static double L1XE50fitFunction(double *x , double *par );
   double TeffFitErr( Double_t , Double_t , Double_t, Double_t, Double_t, Double_t, Double_t, Double_t);
   ClassDef(Jburr_Template_Selector,0);//}}}
   // Readers to access the data (delete the ones you do not need){{{
   TTreeReaderValue<UInt_t> RunNumber = {fReader, "RunNumber"};
   TTreeReaderValue<ULong64_t> EventNumber = {fReader, "EventNumber"};
   TTreeReaderValue<Float_t> InTimePileup = {fReader, "ActualInteractionsPerCrossing"};
   //TTreeReaderValue<Float_t> InTimePileup = {fReader, "InTimePileup"};

   TTreeReaderValue<Float_t> L1_met = {fReader, "L1.met"};
   TTreeReaderValue<Float_t> cell_met = {fReader, "cell.met"};
   TTreeReaderValue<Float_t> mht_met = {fReader, "mht.met"};
   TTreeReaderValue<Float_t> pufit_met = {fReader, "pufit.met"};
   TTreeReaderValue<Float_t> topocl_met = {fReader, "topocl.met"};

   TTreeReaderValue<Float_t> L1_sumet = {fReader, "L1.sumet"};
   TTreeReaderValue<Float_t> cell_sumet = {fReader, "cell.sumet"};
   TTreeReaderValue<Float_t> mht_sumet = {fReader, "mht.sumet"};
   TTreeReaderValue<Float_t> pufit_sumet = {fReader, "pufit.sumet"};
   TTreeReaderValue<Float_t> topocl_sumet = {fReader, "topocl.sumet"};

   TTreeReaderValue<Bool_t> L1_XE50_passed = {fReader, "L1_XE50.passed"};
   TTreeReaderValue<Bool_t> L1_XE55_passed = {fReader, "L1_XE55.passed"};
   TTreeReaderValue<Bool_t> L1_XE60_passed = {fReader, "L1_XE60.passed"};

   TTreeReaderValue<Float_t> L1_XE50_prescale = {fReader, "L1_XE50.prescale"};
   TTreeReaderValue<Float_t> L1_XE55_prescale = {fReader, "L1_XE55.prescale"};
   TTreeReaderValue<Float_t> L1_XE60_prescale = {fReader, "L1_XE60.prescale"};

   TTreeReaderValue<Float_t> HLT_noalg_zb_L1ZB_prescale = {fReader, "HLT_noalg_zb_L1ZB.prescale"};
   TTreeReaderValue<Float_t> HLT_noalg_L1XE10_prescale = {fReader, "HLT_noalg_L1XE10.prescale"};
   TTreeReaderValue<Float_t> HLT_noalg_L1XE20_prescale = {fReader, "HLT_noalg_L1XE20.prescale"};
   TTreeReaderValue<Float_t> HLT_noalg_L1XE30_prescale = {fReader, "HLT_noalg_L1XE30.prescale"};
   TTreeReaderValue<Float_t> HLT_noalg_L1XE40_prescale = {fReader, "HLT_noalg_L1XE40.prescale"};
   TTreeReaderValue<Float_t> HLT_noalg_L1XE45_prescale = {fReader, "HLT_noalg_L1XE45.prescale"};

   TTreeReaderValue<Bool_t> HLT_noalg_zb_L1ZB_passed = {fReader, "HLT_noalg_zb_L1ZB.passed"};
   TTreeReaderValue<Bool_t> HLT_noalg_L1XE10_passed = {fReader, "HLT_noalg_L1XE10.passed"};
   TTreeReaderValue<Bool_t> HLT_noalg_L1XE20_passed = {fReader, "HLT_noalg_L1XE20.passed"};
   TTreeReaderValue<Bool_t> HLT_noalg_L1XE30_passed = {fReader, "HLT_noalg_L1XE30.passed"};
   TTreeReaderValue<Bool_t> HLT_noalg_L1XE40_passed = {fReader, "HLT_noalg_L1XE40.passed"};
   TTreeReaderValue<Bool_t> HLT_noalg_L1XE45_passed = {fReader, "HLT_noalg_L1XE45.passed"};
   //}}}
};
// end class definition }}}
#endif
