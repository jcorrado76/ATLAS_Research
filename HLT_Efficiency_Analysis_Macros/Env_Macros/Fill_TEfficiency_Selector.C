#define TEfficiency_Selector_cxx

#include "TEfficiency_Selector.h"

void TEfficiency_Selector::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
   std::cout << "Starting to fill TEfficiencies.." << std::endl;
   ACTINT_CUT = ;
}

void TEfficiency_Selector::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();
   TString astring = AlgAName + " > " + Form(" %.2f", AlgAIndividThresh );
   TString bstring = AlgBName + " > " + Form(" %.2f", AlgBIndividThresh );
   TString cstring = AlgAName + " > " + Form(" %.2f", CombinedThreshAlgA) + " and " + AlgBName + " > " + Form(" %.2f", CombinedThreshAlgB);
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
    if ( IsMuon() && IsClean() && PassActintCut() && PassTransverseMassCut() ){
           Float_t metnomu = ComputeMetnomu();
           Ateff->Fill((algAmuonMET > AlgAIndividThresh ) && ( PassL1Cut() )          && ( PassActintCut() )                               , metnomu);
           Bteff->Fill((algBmuonMET > AlgBIndividThresh ) && ( PassL1Cut() )          && ( PassActintCut() )                               , metnomu);
           Cteff->Fill((algAmuonMET > CombinedThreshAlgA) && (algBmuonMET > CombinedThreshAlgB) && ( PassL1Cut() ) && ( PassActintCut() )  , metnomu);
           Dteff->Fill((muonMetl1 >= metl1thresh)         && ( muonActint > actintCut )                                                    , metnomu);
    }
   return kTRUE;
}

void TEfficiency_Selector::SlaveTerminate()
{
}

void TEfficiency_Selector::Terminate()
{
}
