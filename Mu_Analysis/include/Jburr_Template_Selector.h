//////////////////////////////////////////////////////////
// This class has been automatically generated on
// Tue Jun 19 12:37:50 2018 by ROOT version 6.15/01
// from TTree METTree/METTree
// found on file: /home/joseph/ATLAS_DATA/totalJburrTuple.root
//////////////////////////////////////////////////////////
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
// end includes}}}
//class definition {{{
class Jburr_Template_Selector : public TSelector {
public :
   // Member Variables {{{
   TTreeReader     fReader;
   TTree          *fChain =                                                     0;   //!pointer to the analyzed TTree or TChain
   const static Int_t Number_Mu_Bins =                                          7;   // 7 mu bins
   TH1F* MET_Distribution =                                                     0;
   TEfficiency* MET_L1XE30Efficiency =                                          0;
   TEfficiency* MET_L1XE50Efficiency =                                          0;
   TF1* MET_L1XE30EfficiencyFit =                                               0;
   TF1* MET_L1XE50EfficiencyFit =                                               0;
   const Float_t gevLow =                                                       0.0;
   const Float_t gevHigh =                                                      300.0;
   const Float_t met_dist_binwidth =                                            1.0;
   const Float_t efficiency_bin_width =                                         20.0; //want 20 GeV bins
   const Int_t met_dist_nbins =                                        (gevHigh - gevLow) / met_dist_binwidth; 
   const Int_t efficiency_nbins =                                      (gevHigh - gevLow) / efficiency_bin_width;
   // collections
   TH1F* Met_Distributions_By_Mu_Bin[Number_Mu_Bins];
   TH1F* Normalized_Met_Distributions[Number_Mu_Bins];
   TEfficiency* L1XE30_Efficiency_Objects[Number_Mu_Bins];
   TEfficiency* L1XE50_Efficiency_Objects[Number_Mu_Bins];
   TF1* L1XE30_Efficiency_Fit_Objects[Number_Mu_Bins];
   TF1* L1XE50_Efficiency_Fit_Objects[Number_Mu_Bins];

   // names for objects in collections
    TString* Met_Distributions_By_Mu_Bin_Names[Number_Mu_Bins];
    TString* Normalized_Met_Distributions_Names[Number_Mu_Bins];
    TString* L1XE30_Efficiency_Objects_Names[Number_Mu_Bins];
    TString* L1XE50_Efficiency_Objects_Names[Number_Mu_Bins];
    TString* L1XE30_Efficiency_Fit_Objects_Names[Number_Mu_Bins];
    TString* L1XE50_Efficiency_Fit_Objects_Names[Number_Mu_Bins];
   
   Float_t Mu_Values[Number_Mu_Bins+1] =                    { 0.0 };
   Int_t Colors[Number_Mu_Bins] =                           {1,2,3,4,12,6,9};
   Int_t MarkerStyles[Number_Mu_Bins] =                     {29,20,3,4,27,22,21};
   Int_t Normalization_Bin_Numbers[Number_Mu_Bins] =        {40,52,60,56,55,52,40};
   Float_t Scale_Factors[Number_Mu_Bins] =                  { 0.0 };

   Float_t muLow;
   Float_t muHigh;
   TString Name;
   TString Title;
   TString Corrected_Name;
   TString Corrected_Title;
   TString EfficiencyName;
   TString EfficiencyTitle;

   constexpr static Float_t L1XE = 50.0; // L1 cut
   TString Alg_Name =                       "CELL MET";
   TString zb_alg_name =                    "cell.met"; 
   TString l1_alg_name =                    "L1.met";
   TString efficiency_yaxis =               "efficiency";
   TString met_dist_yaxis =                 "Number of Entries";
   TString efficiency_title =               zb_alg_name + " Efficiency";
   TString efficiency_xaxis =               zb_alg_name + " [GeV]";
   TString met_dist_xaxis =                 zb_alg_name + " [GeV]";
   // }}}
   // Readers to access the data (delete the ones you do not need){{{
   TTreeReaderValue<Float_t> MET_Data = {fReader, zb_alg_name };
   TTreeReaderValue<Float_t> L1_MET = {fReader, l1_alg_name};

   TTreeReaderValue<UInt_t> RunNumber = {fReader, "RunNumber"};
   TTreeReaderValue<ULong64_t> EventNumber = {fReader, "EventNumber"};
   TTreeReaderValue<UInt_t> LumiBlock = {fReader, "LumiBlock"};
   TTreeReaderValue<UInt_t> NPrimaryVertices = {fReader, "NPrimaryVertices"};
   TTreeReaderValue<Float_t> InTimePileup = {fReader, "InTimePileup"};
   TTreeReaderValue<Float_t> OutOfTimePileup = {fReader, "OutOfTimePileup"};
   TTreeReaderValue<Bool_t> HInvEle_pass = {fReader, "HInvEle.pass"};
   TTreeReaderValue<Bool_t> HInvMuon_pass = {fReader, "HInvMuon.pass"};
   TTreeReaderValue<Bool_t> TTBarenujj_pass = {fReader, "TTBarenujj.pass"};
   TTreeReaderValue<Bool_t> TTBarenumunu_pass = {fReader, "TTBarenumunu.pass"};
   TTreeReaderValue<Bool_t> TTBarmunujj_pass = {fReader, "TTBarmunujj.pass"};
   TTreeReaderValue<Bool_t> Wenu_pass = {fReader, "Wenu.pass"};
   TTreeReaderValue<Bool_t> Wmunu_pass = {fReader, "Wmunu.pass"};
   TTreeReaderValue<Bool_t> Zee_pass = {fReader, "Zee.pass"};
   TTreeReaderValue<Bool_t> Zmumu_pass = {fReader, "Zmumu.pass"};
   TTreeReaderValue<Float_t> Z_pt = {fReader, "Z.pt"};
   TTreeReaderValue<Float_t> Z_eta = {fReader, "Z.eta"};
   TTreeReaderValue<Float_t> Z_phi = {fReader, "Z.phi"};
   TTreeReaderValue<Float_t> Z_mass = {fReader, "Z.mass"};
   TTreeReaderValue<Float_t> W_pt = {fReader, "W.pt"};
   TTreeReaderValue<Float_t> W_mt = {fReader, "W.mt"};
   TTreeReaderValue<Float_t> L1_mpx = {fReader, "L1.mpx"};
   TTreeReaderValue<Float_t> L1_mpy = {fReader, "L1.mpy"};
   TTreeReaderValue<Float_t> L1_sumet = {fReader, "L1.sumet"};
   TTreeReaderValue<Float_t> L1_met = {fReader, "L1.met"};
   TTreeReaderValue<Float_t> L1_phi = {fReader, "L1.phi"};
   TTreeReaderValue<Float_t> cell_mpx = {fReader, "cell.mpx"};
   TTreeReaderValue<Float_t> cell_mpy = {fReader, "cell.mpy"};
   TTreeReaderValue<Float_t> cell_sumet = {fReader, "cell.sumet"};
   TTreeReaderValue<Float_t> cell_met = {fReader, "cell.met"};
   TTreeReaderValue<Float_t> cell_phi = {fReader, "cell.phi"};
   TTreeReaderValue<Float_t> mht_mpx = {fReader, "mht.mpx"};
   TTreeReaderValue<Float_t> mht_mpy = {fReader, "mht.mpy"};
   TTreeReaderValue<Float_t> mht_sumet = {fReader, "mht.sumet"};
   TTreeReaderValue<Float_t> mht_met = {fReader, "mht.met"};
   TTreeReaderValue<Float_t> mht_phi = {fReader, "mht.phi"};
   TTreeReaderValue<Float_t> pufit_mpx = {fReader, "pufit.mpx"};
   TTreeReaderValue<Float_t> pufit_mpy = {fReader, "pufit.mpy"};
   TTreeReaderValue<Float_t> pufit_sumet = {fReader, "pufit.sumet"};
   TTreeReaderValue<Float_t> pufit_met = {fReader, "pufit.met"};
   TTreeReaderValue<Float_t> pufit_phi = {fReader, "pufit.phi"};
   TTreeReaderValue<Float_t> topocl_mpx = {fReader, "topocl.mpx"};
   TTreeReaderValue<Float_t> topocl_mpy = {fReader, "topocl.mpy"};
   TTreeReaderValue<Float_t> topocl_sumet = {fReader, "topocl.sumet"};
   TTreeReaderValue<Float_t> topocl_met = {fReader, "topocl.met"};
   TTreeReaderValue<Float_t> topocl_phi = {fReader, "topocl.phi"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_Loose_FinalTrk_mpx = {fReader, "CalAntiKt4EMTopoMissingET_Loose.FinalTrk.mpx"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_Loose_FinalTrk_mpy = {fReader, "CalAntiKt4EMTopoMissingET_Loose.FinalTrk.mpy"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_Loose_FinalTrk_sumet = {fReader, "CalAntiKt4EMTopoMissingET_Loose.FinalTrk.sumet"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_Loose_FinalTrk_met = {fReader, "CalAntiKt4EMTopoMissingET_Loose.FinalTrk.met"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_Loose_FinalTrk_phi = {fReader, "CalAntiKt4EMTopoMissingET_Loose.FinalTrk.phi"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_Loose_FinalTrkNoMu_mpx = {fReader, "CalAntiKt4EMTopoMissingET_Loose.FinalTrkNoMu.mpx"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_Loose_FinalTrkNoMu_mpy = {fReader, "CalAntiKt4EMTopoMissingET_Loose.FinalTrkNoMu.mpy"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_Loose_FinalTrkNoMu_sumet = {fReader, "CalAntiKt4EMTopoMissingET_Loose.FinalTrkNoMu.sumet"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_Loose_FinalTrkNoMu_met = {fReader, "CalAntiKt4EMTopoMissingET_Loose.FinalTrkNoMu.met"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_Loose_FinalTrkNoMu_phi = {fReader, "CalAntiKt4EMTopoMissingET_Loose.FinalTrkNoMu.phi"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_FinalTrk_mpx = {fReader, "CalAntiKt4EMTopoMissingET.FinalTrk.mpx"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_FinalTrk_mpy = {fReader, "CalAntiKt4EMTopoMissingET.FinalTrk.mpy"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_FinalTrk_sumet = {fReader, "CalAntiKt4EMTopoMissingET.FinalTrk.sumet"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_FinalTrk_met = {fReader, "CalAntiKt4EMTopoMissingET.FinalTrk.met"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_FinalTrk_phi = {fReader, "CalAntiKt4EMTopoMissingET.FinalTrk.phi"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_FinalTrkNoMu_mpx = {fReader, "CalAntiKt4EMTopoMissingET.FinalTrkNoMu.mpx"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_FinalTrkNoMu_mpy = {fReader, "CalAntiKt4EMTopoMissingET.FinalTrkNoMu.mpy"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_FinalTrkNoMu_sumet = {fReader, "CalAntiKt4EMTopoMissingET.FinalTrkNoMu.sumet"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_FinalTrkNoMu_met = {fReader, "CalAntiKt4EMTopoMissingET.FinalTrkNoMu.met"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_FinalTrkNoMu_phi = {fReader, "CalAntiKt4EMTopoMissingET.FinalTrkNoMu.phi"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_Fwd35_FinalTrk_mpx = {fReader, "CalAntiKt4EMTopoMissingET_Fwd35.FinalTrk.mpx"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_Fwd35_FinalTrk_mpy = {fReader, "CalAntiKt4EMTopoMissingET_Fwd35.FinalTrk.mpy"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_Fwd35_FinalTrk_sumet = {fReader, "CalAntiKt4EMTopoMissingET_Fwd35.FinalTrk.sumet"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_Fwd35_FinalTrk_met = {fReader, "CalAntiKt4EMTopoMissingET_Fwd35.FinalTrk.met"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_Fwd35_FinalTrk_phi = {fReader, "CalAntiKt4EMTopoMissingET_Fwd35.FinalTrk.phi"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_Fwd35_FinalTrkNoMu_mpx = {fReader, "CalAntiKt4EMTopoMissingET_Fwd35.FinalTrkNoMu.mpx"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_Fwd35_FinalTrkNoMu_mpy = {fReader, "CalAntiKt4EMTopoMissingET_Fwd35.FinalTrkNoMu.mpy"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_Fwd35_FinalTrkNoMu_sumet = {fReader, "CalAntiKt4EMTopoMissingET_Fwd35.FinalTrkNoMu.sumet"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_Fwd35_FinalTrkNoMu_met = {fReader, "CalAntiKt4EMTopoMissingET_Fwd35.FinalTrkNoMu.met"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_Fwd35_FinalTrkNoMu_phi = {fReader, "CalAntiKt4EMTopoMissingET_Fwd35.FinalTrkNoMu.phi"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_Fwd40_FinalTrk_mpx = {fReader, "CalAntiKt4EMTopoMissingET_Fwd40.FinalTrk.mpx"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_Fwd40_FinalTrk_mpy = {fReader, "CalAntiKt4EMTopoMissingET_Fwd40.FinalTrk.mpy"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_Fwd40_FinalTrk_sumet = {fReader, "CalAntiKt4EMTopoMissingET_Fwd40.FinalTrk.sumet"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_Fwd40_FinalTrk_met = {fReader, "CalAntiKt4EMTopoMissingET_Fwd40.FinalTrk.met"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_Fwd40_FinalTrk_phi = {fReader, "CalAntiKt4EMTopoMissingET_Fwd40.FinalTrk.phi"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_Fwd40_FinalTrkNoMu_mpx = {fReader, "CalAntiKt4EMTopoMissingET_Fwd40.FinalTrkNoMu.mpx"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_Fwd40_FinalTrkNoMu_mpy = {fReader, "CalAntiKt4EMTopoMissingET_Fwd40.FinalTrkNoMu.mpy"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_Fwd40_FinalTrkNoMu_sumet = {fReader, "CalAntiKt4EMTopoMissingET_Fwd40.FinalTrkNoMu.sumet"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_Fwd40_FinalTrkNoMu_met = {fReader, "CalAntiKt4EMTopoMissingET_Fwd40.FinalTrkNoMu.met"};
   TTreeReaderValue<Float_t> CalAntiKt4EMTopoMissingET_Fwd40_FinalTrkNoMu_phi = {fReader, "CalAntiKt4EMTopoMissingET_Fwd40.FinalTrkNoMu.phi"};
   TTreeReaderValue<Bool_t> HLT_xe110_pufit_L1XE50_passed = {fReader, "HLT_xe110_pufit_L1XE50.passed"};
   TTreeReaderValue<Float_t> HLT_xe110_pufit_L1XE50_prescale = {fReader, "HLT_xe110_pufit_L1XE50.prescale"};
   TTreeReaderValue<UInt_t> HLT_xe110_pufit_L1XE50_passBits = {fReader, "HLT_xe110_pufit_L1XE50.passBits"};
   TTreeReaderValue<Bool_t> L1_XE50_passed = {fReader, "L1_XE50.passed"};
   TTreeReaderValue<Float_t> L1_XE50_prescale = {fReader, "L1_XE50.prescale"};
   TTreeReaderValue<UInt_t> L1_XE50_passBits = {fReader, "L1_XE50.passBits"};
   TTreeReaderValue<Bool_t> HLT_xe120_mht_xe80_L1XE50_passed = {fReader, "HLT_xe120_mht_xe80_L1XE50.passed"};
   TTreeReaderValue<Float_t> HLT_xe120_mht_xe80_L1XE50_prescale = {fReader, "HLT_xe120_mht_xe80_L1XE50.prescale"};
   TTreeReaderValue<UInt_t> HLT_xe120_mht_xe80_L1XE50_passBits = {fReader, "HLT_xe120_mht_xe80_L1XE50.passBits"};
   TTreeReaderValue<Bool_t> HLT_xe100_pufit_L1XE50_passed = {fReader, "HLT_xe100_pufit_L1XE50.passed"};
   TTreeReaderValue<Float_t> HLT_xe100_pufit_L1XE50_prescale = {fReader, "HLT_xe100_pufit_L1XE50.prescale"};
   TTreeReaderValue<UInt_t> HLT_xe100_pufit_L1XE50_passBits = {fReader, "HLT_xe100_pufit_L1XE50.passBits"};
   TTreeReaderValue<Bool_t> HLT_xe110_pufit_L1XE55_passed = {fReader, "HLT_xe110_pufit_L1XE55.passed"};
   TTreeReaderValue<Float_t> HLT_xe110_pufit_L1XE55_prescale = {fReader, "HLT_xe110_pufit_L1XE55.prescale"};
   TTreeReaderValue<UInt_t> HLT_xe110_pufit_L1XE55_passBits = {fReader, "HLT_xe110_pufit_L1XE55.passBits"};
   TTreeReaderValue<Bool_t> HLT_xe120_mht_xe80_L1XE55_passed = {fReader, "HLT_xe120_mht_xe80_L1XE55.passed"};
   TTreeReaderValue<Float_t> HLT_xe120_mht_xe80_L1XE55_prescale = {fReader, "HLT_xe120_mht_xe80_L1XE55.prescale"};
   TTreeReaderValue<UInt_t> HLT_xe120_mht_xe80_L1XE55_passBits = {fReader, "HLT_xe120_mht_xe80_L1XE55.passBits"};
   TTreeReaderValue<Bool_t> L1_XE55_passed = {fReader, "L1_XE55.passed"};
   TTreeReaderValue<Float_t> L1_XE55_prescale = {fReader, "L1_XE55.prescale"};
   TTreeReaderValue<UInt_t> L1_XE55_passBits = {fReader, "L1_XE55.passBits"};
   TTreeReaderValue<Bool_t> L1_XE60_passed = {fReader, "L1_XE60.passed"};
   TTreeReaderValue<Float_t> L1_XE60_prescale = {fReader, "L1_XE60.prescale"};
   TTreeReaderValue<UInt_t> L1_XE60_passBits = {fReader, "L1_XE60.passBits"};
   TTreeReaderValue<Bool_t> HLT_noalg_zb_L1ZB_passed = {fReader, "HLT_noalg_zb_L1ZB.passed"};
   TTreeReaderValue<Float_t> HLT_noalg_zb_L1ZB_prescale = {fReader, "HLT_noalg_zb_L1ZB.prescale"};
   TTreeReaderValue<UInt_t> HLT_noalg_zb_L1ZB_passBits = {fReader, "HLT_noalg_zb_L1ZB.passBits"};
   TTreeReaderValue<Bool_t> HLT_j40_L1ZB_passed = {fReader, "HLT_j40_L1ZB.passed"};
   TTreeReaderValue<Float_t> HLT_j40_L1ZB_prescale = {fReader, "HLT_j40_L1ZB.prescale"};
   TTreeReaderValue<UInt_t> HLT_j40_L1ZB_passBits = {fReader, "HLT_j40_L1ZB.passBits"};
   TTreeReaderValue<Bool_t> HLT_noalg_L1XE10_passed = {fReader, "HLT_noalg_L1XE10.passed"};
   TTreeReaderValue<Float_t> HLT_noalg_L1XE10_prescale = {fReader, "HLT_noalg_L1XE10.prescale"};
   TTreeReaderValue<UInt_t> HLT_noalg_L1XE10_passBits = {fReader, "HLT_noalg_L1XE10.passBits"};
   TTreeReaderValue<Bool_t> HLT_noalg_L1XE20_passed = {fReader, "HLT_noalg_L1XE20.passed"};
   TTreeReaderValue<Float_t> HLT_noalg_L1XE20_prescale = {fReader, "HLT_noalg_L1XE20.prescale"};
   TTreeReaderValue<UInt_t> HLT_noalg_L1XE20_passBits = {fReader, "HLT_noalg_L1XE20.passBits"};
   TTreeReaderValue<Bool_t> HLT_noalg_L1XE30_passed = {fReader, "HLT_noalg_L1XE30.passed"};
   TTreeReaderValue<Float_t> HLT_noalg_L1XE30_prescale = {fReader, "HLT_noalg_L1XE30.prescale"};
   TTreeReaderValue<UInt_t> HLT_noalg_L1XE30_passBits = {fReader, "HLT_noalg_L1XE30.passBits"};
   TTreeReaderValue<Bool_t> HLT_noalg_L1XE40_passed = {fReader, "HLT_noalg_L1XE40.passed"};
   TTreeReaderValue<Float_t> HLT_noalg_L1XE40_prescale = {fReader, "HLT_noalg_L1XE40.prescale"};
   TTreeReaderValue<UInt_t> HLT_noalg_L1XE40_passBits = {fReader, "HLT_noalg_L1XE40.passBits"};
   TTreeReaderValue<Bool_t> HLT_noalg_L1XE45_passed = {fReader, "HLT_noalg_L1XE45.passed"};
   TTreeReaderValue<Float_t> HLT_noalg_L1XE45_prescale = {fReader, "HLT_noalg_L1XE45.prescale"};
   TTreeReaderValue<UInt_t> HLT_noalg_L1XE45_passBits = {fReader, "HLT_noalg_L1XE45.passBits"};
   TTreeReaderValue<Bool_t> HLT_2e12_lhvloose_nod0_L12EM10VH_passed = {fReader, "HLT_2e12_lhvloose_nod0_L12EM10VH.passed"};
   TTreeReaderValue<Float_t> HLT_2e12_lhvloose_nod0_L12EM10VH_prescale = {fReader, "HLT_2e12_lhvloose_nod0_L12EM10VH.prescale"};
   TTreeReaderValue<UInt_t> HLT_2e12_lhvloose_nod0_L12EM10VH_passBits = {fReader, "HLT_2e12_lhvloose_nod0_L12EM10VH.passBits"};
   TTreeReaderValue<Bool_t> HLT_2e15_lhvloose_nod0_L12EM13VH_passed = {fReader, "HLT_2e15_lhvloose_nod0_L12EM13VH.passed"};
   TTreeReaderValue<Float_t> HLT_2e15_lhvloose_nod0_L12EM13VH_prescale = {fReader, "HLT_2e15_lhvloose_nod0_L12EM13VH.prescale"};
   TTreeReaderValue<UInt_t> HLT_2e15_lhvloose_nod0_L12EM13VH_passBits = {fReader, "HLT_2e15_lhvloose_nod0_L12EM13VH.passBits"};
   TTreeReaderValue<Bool_t> HLT_2e17_lhvloose_nod0_passed = {fReader, "HLT_2e17_lhvloose_nod0.passed"};
   TTreeReaderValue<Float_t> HLT_2e17_lhvloose_nod0_prescale = {fReader, "HLT_2e17_lhvloose_nod0.prescale"};
   TTreeReaderValue<UInt_t> HLT_2e17_lhvloose_nod0_passBits = {fReader, "HLT_2e17_lhvloose_nod0.passBits"};
   TTreeReaderValue<Bool_t> HLT_2e17_lhvloose_nod0_L12EM15VHI_passed = {fReader, "HLT_2e17_lhvloose_nod0_L12EM15VHI.passed"};
   TTreeReaderValue<Float_t> HLT_2e17_lhvloose_nod0_L12EM15VHI_prescale = {fReader, "HLT_2e17_lhvloose_nod0_L12EM15VHI.prescale"};
   TTreeReaderValue<UInt_t> HLT_2e17_lhvloose_nod0_L12EM15VHI_passBits = {fReader, "HLT_2e17_lhvloose_nod0_L12EM15VHI.passBits"};
   TTreeReaderValue<Bool_t> HLT_2e24_lhvloose_nod0_passed = {fReader, "HLT_2e24_lhvloose_nod0.passed"};
   TTreeReaderValue<Float_t> HLT_2e24_lhvloose_nod0_prescale = {fReader, "HLT_2e24_lhvloose_nod0.prescale"};
   TTreeReaderValue<UInt_t> HLT_2e24_lhvloose_nod0_passBits = {fReader, "HLT_2e24_lhvloose_nod0.passBits"};
   TTreeReaderValue<Bool_t> HLT_2mu14_passed = {fReader, "HLT_2mu14.passed"};
   TTreeReaderValue<Float_t> HLT_2mu14_prescale = {fReader, "HLT_2mu14.prescale"};
   TTreeReaderValue<UInt_t> HLT_2mu14_passBits = {fReader, "HLT_2mu14.passBits"};
   TTreeReaderValue<Bool_t> HLT_e24_lhmedium_nod0_ivarloose_passed = {fReader, "HLT_e24_lhmedium_nod0_ivarloose.passed"};
   TTreeReaderValue<Float_t> HLT_e24_lhmedium_nod0_ivarloose_prescale = {fReader, "HLT_e24_lhmedium_nod0_ivarloose.prescale"};
   TTreeReaderValue<UInt_t> HLT_e24_lhmedium_nod0_ivarloose_passBits = {fReader, "HLT_e24_lhmedium_nod0_ivarloose.passBits"};
   TTreeReaderValue<Bool_t> HLT_e24_lhtight_nod0_ivarloose_passed = {fReader, "HLT_e24_lhtight_nod0_ivarloose.passed"};
   TTreeReaderValue<Float_t> HLT_e24_lhtight_nod0_ivarloose_prescale = {fReader, "HLT_e24_lhtight_nod0_ivarloose.prescale"};
   TTreeReaderValue<UInt_t> HLT_e24_lhtight_nod0_ivarloose_passBits = {fReader, "HLT_e24_lhtight_nod0_ivarloose.passBits"};
   TTreeReaderValue<Bool_t> HLT_e26_lhtight_nod0_ivarloose_passed = {fReader, "HLT_e26_lhtight_nod0_ivarloose.passed"};
   TTreeReaderValue<Float_t> HLT_e26_lhtight_nod0_ivarloose_prescale = {fReader, "HLT_e26_lhtight_nod0_ivarloose.prescale"};
   TTreeReaderValue<UInt_t> HLT_e26_lhtight_nod0_ivarloose_passBits = {fReader, "HLT_e26_lhtight_nod0_ivarloose.passBits"};
   TTreeReaderValue<Bool_t> HLT_e26_lhtight_nod0_ivarloose_L1EM22VHIM_passed = {fReader, "HLT_e26_lhtight_nod0_ivarloose_L1EM22VHIM.passed"};
   TTreeReaderValue<Float_t> HLT_e26_lhtight_nod0_ivarloose_L1EM22VHIM_prescale = {fReader, "HLT_e26_lhtight_nod0_ivarloose_L1EM22VHIM.prescale"};
   TTreeReaderValue<UInt_t> HLT_e26_lhtight_nod0_ivarloose_L1EM22VHIM_passBits = {fReader, "HLT_e26_lhtight_nod0_ivarloose_L1EM22VHIM.passBits"};
   TTreeReaderValue<Bool_t> HLT_e26_lhtight_smooth_ivarloose_passed = {fReader, "HLT_e26_lhtight_smooth_ivarloose.passed"};
   TTreeReaderValue<Float_t> HLT_e26_lhtight_smooth_ivarloose_prescale = {fReader, "HLT_e26_lhtight_smooth_ivarloose.prescale"};
   TTreeReaderValue<UInt_t> HLT_e26_lhtight_smooth_ivarloose_passBits = {fReader, "HLT_e26_lhtight_smooth_ivarloose.passBits"};
   TTreeReaderValue<Bool_t> HLT_e28_lhtight_nod0_ivarloose_passed = {fReader, "HLT_e28_lhtight_nod0_ivarloose.passed"};
   TTreeReaderValue<Float_t> HLT_e28_lhtight_nod0_ivarloose_prescale = {fReader, "HLT_e28_lhtight_nod0_ivarloose.prescale"};
   TTreeReaderValue<UInt_t> HLT_e28_lhtight_nod0_ivarloose_passBits = {fReader, "HLT_e28_lhtight_nod0_ivarloose.passBits"};
   TTreeReaderValue<Bool_t> HLT_e28_lhtight_nod0_ivarloose_L1EM24VHIM_passed = {fReader, "HLT_e28_lhtight_nod0_ivarloose_L1EM24VHIM.passed"};
   TTreeReaderValue<Float_t> HLT_e28_lhtight_nod0_ivarloose_L1EM24VHIM_prescale = {fReader, "HLT_e28_lhtight_nod0_ivarloose_L1EM24VHIM.prescale"};
   TTreeReaderValue<UInt_t> HLT_e28_lhtight_nod0_ivarloose_L1EM24VHIM_passBits = {fReader, "HLT_e28_lhtight_nod0_ivarloose_L1EM24VHIM.passBits"};
   TTreeReaderValue<Bool_t> HLT_e60_lhmedium_nod0_passed = {fReader, "HLT_e60_lhmedium_nod0.passed"};
   TTreeReaderValue<Float_t> HLT_e60_lhmedium_nod0_prescale = {fReader, "HLT_e60_lhmedium_nod0.prescale"};
   TTreeReaderValue<UInt_t> HLT_e60_lhmedium_nod0_passBits = {fReader, "HLT_e60_lhmedium_nod0.passBits"};
   TTreeReaderValue<Bool_t> HLT_e60_lhmedium_nod0_L1EM24VHI_passed = {fReader, "HLT_e60_lhmedium_nod0_L1EM24VHI.passed"};
   TTreeReaderValue<Float_t> HLT_e60_lhmedium_nod0_L1EM24VHI_prescale = {fReader, "HLT_e60_lhmedium_nod0_L1EM24VHI.prescale"};
   TTreeReaderValue<UInt_t> HLT_e60_lhmedium_nod0_L1EM24VHI_passBits = {fReader, "HLT_e60_lhmedium_nod0_L1EM24VHI.passBits"};
   TTreeReaderValue<Bool_t> HLT_e60_medium_passed = {fReader, "HLT_e60_medium.passed"};
   TTreeReaderValue<Float_t> HLT_e60_medium_prescale = {fReader, "HLT_e60_medium.prescale"};
   TTreeReaderValue<UInt_t> HLT_e60_medium_passBits = {fReader, "HLT_e60_medium.passBits"};
   TTreeReaderValue<Bool_t> HLT_mu20_mu8noL1_passed = {fReader, "HLT_mu20_mu8noL1.passed"};
   TTreeReaderValue<Float_t> HLT_mu20_mu8noL1_prescale = {fReader, "HLT_mu20_mu8noL1.prescale"};
   TTreeReaderValue<UInt_t> HLT_mu20_mu8noL1_passBits = {fReader, "HLT_mu20_mu8noL1.passBits"};
   TTreeReaderValue<Bool_t> HLT_mu22_mu8noL1_passed = {fReader, "HLT_mu22_mu8noL1.passed"};
   TTreeReaderValue<Float_t> HLT_mu22_mu8noL1_prescale = {fReader, "HLT_mu22_mu8noL1.prescale"};
   TTreeReaderValue<UInt_t> HLT_mu22_mu8noL1_passBits = {fReader, "HLT_mu22_mu8noL1.passBits"};
   TTreeReaderValue<Bool_t> HLT_mu24_imedium_passed = {fReader, "HLT_mu24_imedium.passed"};
   TTreeReaderValue<Float_t> HLT_mu24_imedium_prescale = {fReader, "HLT_mu24_imedium.prescale"};
   TTreeReaderValue<UInt_t> HLT_mu24_imedium_passBits = {fReader, "HLT_mu24_imedium.passBits"};
   TTreeReaderValue<Bool_t> HLT_mu24_ivarloose_passed = {fReader, "HLT_mu24_ivarloose.passed"};
   TTreeReaderValue<Float_t> HLT_mu24_ivarloose_prescale = {fReader, "HLT_mu24_ivarloose.prescale"};
   TTreeReaderValue<UInt_t> HLT_mu24_ivarloose_passBits = {fReader, "HLT_mu24_ivarloose.passBits"};
   TTreeReaderValue<Bool_t> HLT_mu24_ivarmedium_passed = {fReader, "HLT_mu24_ivarmedium.passed"};
   TTreeReaderValue<Float_t> HLT_mu24_ivarmedium_prescale = {fReader, "HLT_mu24_ivarmedium.prescale"};
   TTreeReaderValue<UInt_t> HLT_mu24_ivarmedium_passBits = {fReader, "HLT_mu24_ivarmedium.passBits"};
   TTreeReaderValue<Bool_t> HLT_mu26_imedium_passed = {fReader, "HLT_mu26_imedium.passed"};
   TTreeReaderValue<Float_t> HLT_mu26_imedium_prescale = {fReader, "HLT_mu26_imedium.prescale"};
   TTreeReaderValue<UInt_t> HLT_mu26_imedium_passBits = {fReader, "HLT_mu26_imedium.passBits"};
   TTreeReaderValue<Bool_t> HLT_mu26_ivarmedium_passed = {fReader, "HLT_mu26_ivarmedium.passed"};
   TTreeReaderValue<Float_t> HLT_mu26_ivarmedium_prescale = {fReader, "HLT_mu26_ivarmedium.prescale"};
   TTreeReaderValue<UInt_t> HLT_mu26_ivarmedium_passBits = {fReader, "HLT_mu26_ivarmedium.passBits"};
   TTreeReaderValue<Bool_t> HLT_mu40_passed = {fReader, "HLT_mu40.passed"};
   TTreeReaderValue<Float_t> HLT_mu40_prescale = {fReader, "HLT_mu40.prescale"};
   TTreeReaderValue<UInt_t> HLT_mu40_passBits = {fReader, "HLT_mu40.passBits"};
   TTreeReaderValue<Bool_t> HLT_mu50_passed = {fReader, "HLT_mu50.passed"};
   TTreeReaderValue<Float_t> HLT_mu50_prescale = {fReader, "HLT_mu50.prescale"};
   TTreeReaderValue<UInt_t> HLT_mu50_passBits = {fReader, "HLT_mu50.passBits"};
   TTreeReaderArray<float> CalMuons_pt = {fReader, "CalMuons.pt"};
   TTreeReaderArray<float> CalMuons_eta = {fReader, "CalMuons.eta"};
   TTreeReaderArray<float> CalMuons_phi = {fReader, "CalMuons.phi"};
   TTreeReaderArray<float> CalMuons_m = {fReader, "CalMuons.m"};
   TTreeReaderArray<float> CalElectrons_pt = {fReader, "CalElectrons.pt"};
   TTreeReaderArray<float> CalElectrons_eta = {fReader, "CalElectrons.eta"};
   TTreeReaderArray<float> CalElectrons_phi = {fReader, "CalElectrons.phi"};
   TTreeReaderArray<float> CalElectrons_m = {fReader, "CalElectrons.m"};
   TTreeReaderArray<float> CalAntiKt4EMTopoJets_pt = {fReader, "CalAntiKt4EMTopoJets.pt"};
   TTreeReaderArray<float> CalAntiKt4EMTopoJets_eta = {fReader, "CalAntiKt4EMTopoJets.eta"};
   TTreeReaderArray<float> CalAntiKt4EMTopoJets_phi = {fReader, "CalAntiKt4EMTopoJets.phi"};
   TTreeReaderArray<float> CalAntiKt4EMTopoJets_m = {fReader, "CalAntiKt4EMTopoJets.m"};
   //}}}
   // Member Functions {{{
   // Default Constructor {{{
   Jburr_Template_Selector(){ 
       for (int i = 0 ; i < Number_Mu_Bins + 1; i++){
           Mu_Values[i] = i * 10.;
           Name.Form("zb_met_dist_mubin%d" , i );
           Title.Form("ZeroBias MET Distribution for %s With Actint Between %.0f and %.0f" ,Alg_Name.Data(), muLow , muHigh );
           EfficiencyName.Form("metL1XE30EfficiencyMubin%d", i);
           EfficiencyTitle.Form("Efficiency of L1XE 30 As a Function of %s for Actint bin %d", Alg_Name.Data() , i);
           Met_Distributions_By_Mu_Bin[i] = new TH1F( Name , Title , met_dist_nbins , gevLow , gevHigh );
           Normalized_Met_Distributions[i] = new TH1F( Corrected_Name , Corrected_Title , met_dist_nbins , gevLow , gevHigh );
           L1XE30_Efficiency_Objects[i] = new TEfficiency( EfficiencyName , EfficiencyTitle , efficiency_nbins , gevLow , gevHigh );
           EfficiencyName.Form("metL1XE30EfficiencyMubin%d", i);           
           EfficiencyTitle.Form("Efficiency of L1XE 50 As a Function of %s for Actint bin %d", Alg_Name.Data() , i);
           L1XE50_Efficiency_Objects[i] = new TEfficiency( EfficiencyName , EfficiencyTitle , efficiency_nbins , gevLow , gevHigh );
           L1XE30_Efficiency_Fit_Objects[i] = new TF1();
           L1XE50_Efficiency_Fit_Objects[i] = new TF1();

            // set line colors on the TH1F objects 
           Met_Distributions_By_Mu_Bin[i]->SetLineColor( Colors[i] );
           Normalized_Met_Distributions[i]->SetLineColor( Colors[i] );

           L1XE30_Efficiency_Objects[i]->SetLineColor( Colors[i] );
           L1XE30_Efficiency_Objects[i]->SetMarkerStyle( Colors[i] );
           L1XE30_Efficiency_Fit_Objects[i]->SetLineColor( Colors[i] );
   }//}}}
   }
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
   // TODO: make sure you add default val for l1cut parameter once you figured out workaround for making it an argument
   static Double_t fitFunction(Double_t *x , Double_t *par );
   TF1* generateFitFunction(TEfficiency* teff_obj, float gevMax = 300.0, float initial_slope = 0.1 , float initial_intercept = 0.0, float initial_sigma = 10.0, Bool_t verbose=false );
   Double_t ComputeWeight(TF1* fitFunc, TF1* fitFunc2 = NULL);//}}}
   ClassDef(Jburr_Template_Selector,0);
};
// end class definition }}}
#endif
