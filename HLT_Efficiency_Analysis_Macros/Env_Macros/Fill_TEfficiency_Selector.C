#define TEfficiency_Selector_cxx

#include "TEfficiency_Selector.h"
#include <TH2.h>
#include <TStyle.h>


std::cout << "Starting to fill TEfficiencies.." << std::endl;
Int_t NumMuonPassProcess1WithActintCut = 0;

Bool_t isMuon;
Bool_t isClean;

for (Int_t l = 0; i < muonNentries ; l++){
        myMuonTree->GetEntry(l);
        isMuon = (passmuvarmed > 0.1 || passmuon > 0.1 );
        isClean = (cleanCutsFlag > 0.1 ) && (recalBrokeFlag < 0.1 );
        if (isMuon && isClean && muonMetl1 > metl1thresh ){
                NumMuonPassProcess1++;
        }

        if (isMuon && isClean && (muonActint > actintcut) ){
                if (Efficiency_Lib::passTransverseMassCut( metoffrecal, mexoffrecal, meyoffrecal, metoffrecalmuon,mexoffrecalmuon,meyoffrecalmuon )){
                        Float_t metnomu = Efficiency_Lib::computeMetNoMu(mexoffrecal,meyoffrecal,mexoffrecalmuon,meyoffrecalmuon);
                        Ateff->Fill((algAmuonMET > AlgAIndividThresh ) /*&& (muonMetl1 > metl1thresh)*/ && ( muonActint >     actintCut ), metnomu);
                       Bteff->Fill((algBmuonMET > AlgBIndividThresh ) /*&& (muonMetl1 > metl1thresh)*/&& ( muonActint >     actintCut ), metnomu);
                     Cteff->Fill(((algAmuonMET > CombinedThreshAlgA) && (algBmuonMET > CombinedThreshAlgB) && ( muonActint > actintCut )/*&& (muonMetl1 > metl1thresh)*/), metnomu);
                      Dteff->Fill(/*(muonMetl1 >= metl1thresh) &&*/ ( muonActint > actintCut ), metnomu);
                }
        }
              }

void TEfficiency_Selector::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
}

void TEfficiency_Selector::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();
   TString astring = AlgAName + " > " + Form(" %.2f", AlgAIndividThresh );
   TString bstring = AlgBName + " > " + Form(" %.2f", AlgBIndividThresh );
   TString cstring = AlgAName+ " > " + Form(" %.2f", CombinedThreshAlgA) + " and " + AlgBName + " > " + Form(" %.2f", CombinedThreshAlgB);
   TString dstring = (TString) "L1 > " + Form(" %.2f" , metl1thresh);

   TEfficiency* Ateff  = new TEfficiency(astring , "Efficiency", muonNbins, metMin, metMax);
   TEfficiency* Bteff  = new TEfficiency(bstring , "Efficiency", muonNbins, metMin, metMax);
   TEfficiency* Cteff  = new TEfficiency(cstring,  "Efficiency", muonNbins, metMin, metMax);
   TEfficiency* Dteff  = new TEfficiency(dstring,  "Efficiency", muonNbins, metMin, metMax);//combined just L1 cut, 0 on others

   fOutput->Add( Ateff );
   fOutput->Add( Bteff );
   fOutput->Add( Cteff );
   fOutput->Add( Dteff );
}

Bool_t TEfficiency_Selector::Process(Long64_t entry)
{
   fReader.SetEntry(entry);

   Ateff->Fill((algAmuonMET > AlgAIndividThresh ) /*&& (muonMetl1 > metl1thresh)*/ && ( muonActint >     actintCut ), metnomu);
   Bteff->Fill((algBmuonMET > AlgBIndividThresh ) /*&& (muonMetl1 > metl1thresh)*/&& ( muonActint >     actintCut ), metnomu);
   Cteff->Fill(((algAmuonMET > CombinedThreshAlgA) && (algBmuonMET > CombinedThreshAlgB) && ( muonActint > actintCut )/*&& (muonMetl1 > metl1thresh)*/), metnomu);
   Dteff->Fill(/*(muonMetl1 >= metl1thresh) &&*/ ( muonActint > actintCut ), metnomu);
   return kTRUE;
}

void TEfficiency_Selector::SlaveTerminate()
{
}

void TEfficiency_Selector::Terminate()
{
}
