#define Jburr_Template_Selector_cxx
#include "Jburr_Template_Selector.h"

void Jburr_Template_Selector::Begin(TTree * /*tree*/){TString option = GetOption();}
void Jburr_Template_Selector::SlaveBegin(TTree * /*tree*/){TString option = GetOption();}
Bool_t Jburr_Template_Selector::Process(Long64_t entry){return kTRUE;}
void Jburr_Template_Selector::SlaveTerminate(){}
void Jburr_Template_Selector::Terminate(){}
Bool_t Jburr_Template_Selector::isGoodRun(){ //{{{
    return (*RunNumber != 330203 && *RunNumber != 331975 && *RunNumber != 334487);
} // }}}
Bool_t Jburr_Template_Selector::passedL1ZB(){ //{{{
    return (*HLT_noalg_zb_L1ZB_passed);
} //}}}
Bool_t Jburr_Template_Selector::isPassnoAlgXE30(){ //{{{
    return (*HLT_noalg_L1XE30_passed);
} //}}}
Bool_t Jburr_Template_Selector::inMuRange( Float_t a , Float_t b ){ //{{{
    return ( *InTimePileup > a && *InTimePileup < b );
} //}}}
