#define TEfficiency_Selector_cxx

#include "Fill_TEfficiency_Selector.h"

void TEfficiency_Selector::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
   std::cout << "Starting to fill TEfficiencies.." << std::endl;
   actintCut = M_Parameters->Get_ActintCut();
   AlgAName = M_Parameters->Get_AlgAName();
   AlgBName = M_Parameters->Get_AlgBName();
   AlgAIndividThresh = M_Parameters->Get_IndividAlgAThresh();
   AlgBIndividThresh = M_Parameters->Get_IndividAlgBThresh();
   AlgACombinedThresh = M_Parameters->Get_CombinedAlgAThresh();
   AlgBCombinedThresh = M_Parameters->Get_CombinedAlgBThresh();
   metl1thresh = M_Parameters->Get_MetL1Thresh();
   muonNbins = M_Parameters->Get_Nbins();
   metMin = M_Parameters->Get_MetMin();
   metMax = M_Parameters->Get_MetMax();
       
}

void TEfficiency_Selector::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();
   astring = AlgAName + " > " + Form(" %.2f", AlgAIndividThresh );
   bstring = AlgBName + " > " + Form(" %.2f", AlgBIndividThresh );
   cstring = AlgAName + " > " + Form(" %.2f", AlgACombinedThresh) + 
       " and " + AlgBName + " > " + Form(" %.2f", AlgBCombinedThresh);
   dstring = (TString) "L1 > " + Form(" %.2f" , metl1thresh);

   Ateff  = new TEfficiency(astring.Data() , "Efficiency", muonNbins, metMin, metMax);
   Bteff  = new TEfficiency(bstring.Data() , "Efficiency", muonNbins, metMin, metMax);
   Cteff  = new TEfficiency(cstring.Data(),  "Efficiency", muonNbins, metMin, metMax);
   Dteff  = new TEfficiency(dstring.Data(),  "Efficiency", muonNbins, metMin, metMax);//combined just L1 cut, 0 on others
}

Bool_t TEfficiency_Selector::Process(Long64_t entry)
{
   fReader.SetEntry(entry);
    if ( IsMuon() && IsClean() && PassActintCut() && PassTransverseMassCut() ){
           Float_t metnomu = ComputeMetnomu();
           Ateff->Fill(( *algAmuonMET > AlgAIndividThresh ) && ( PassL1Cut() )          && ( PassActintCut() )                               , metnomu);
           Bteff->Fill(( *algBmuonMET > AlgBIndividThresh ) && ( PassL1Cut() )          && ( PassActintCut() )                               , metnomu);
           Cteff->Fill(( *algAmuonMET > AlgACombinedThresh) && ( *algBmuonMET > AlgBCombinedThresh) && ( PassL1Cut() ) && ( PassActintCut() )  , metnomu);
           Dteff->Fill( PassL1Cut() && PassActintCut() , metnomu);
    }
   return kTRUE;
}

void TEfficiency_Selector::SlaveTerminate(){}
void TEfficiency_Selector::Terminate(){}

Bool_t TEfficiency_Selector::IsMuon(){
        return( *passmu24varmed > 0.1 || *passmu24med > 0.1 );
}

Bool_t TEfficiency_Selector::IsClean(){
        return( *passcleancuts > 0.1 && *recalbroke < 0.1 );
}

Bool_t TEfficiency_Selector::PassActintCut(){
        return( *actint > actintCut );
} 

Bool_t TEfficiency_Selector::PassTransverseMassCut(){
        return( passTransverseMassCut( *metoffrecal , *mexoffrecal  , *meyoffrecal ,
                                *metoffrecalmuon , *mexoffrecalmuon , *meyoffrecalmuon ) );
}

Bool_t TEfficiency_Selector::PassL1Cut(){
        return( *metl1 > metl1thresh );
}

Float_t TEfficiency_Selector::ComputeMetnomu(){
        return( computeMetNoMu( *mexoffrecal , *meyoffrecal , *mexoffrecalmuon , *meyoffrecalmuon ) );
}
