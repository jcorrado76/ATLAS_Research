#include "ChainHandler.h"
#include <iostream>

// global object
ChainHandler ChainHandler_obj;

// implementation of ChainHandler
// ---------------------------------------------------------------------------------------------- //

//TODO: replace branches
ChainHandler::ChainHandler()
    : run_handle("run")
    , ls_handle("ls")
    , event_handle("event")
    , trks_p4_handle("trks_p4")
    , trks_d0_handle("trks_d0")
    , trks_dz_handle("trks_dz")
    , trks_pterr_handle("trks_pterr")
    , trks_d0err_handle("trks_d0err")
    , trks_dzerr_handle("trks_dzerr")
    , trks_chi2_handle("trks_chi2")
    , trks_ndof_handle("trks_ndof")
    , trks_nlayers_handle("trks_nlayers")
    , trks_high_purity_handle("trks_high_purity")
    , tps_matched_handle("tps_matched")
    , tps_pdgid_handle("tps_pdgid")
    , tps_p4_handle("tps_p4")
    , tps_d0_handle("tps_d0")
    , tps_dz_handle("tps_dz")
    , tps_tip_handle("tps_tip")
    , tps_lip_handle("tps_lip")
    , tps_charge_handle("tps_charge")
    , tps_nhits_handle("tps_nhits")
{
}

void ChainHandler::Init(TTree& tree)
{
    run_handle.Init(tree);
    ls_handle.Init(tree);
    event_handle.Init(tree);
    passrndm_handle.Init(tree) ;
    algA_handle.Init(tree) ;
    algB_handle.Init(tree) ;
    metl1_handle.Init(tree) ;
    passnoalgL1XE10_handle.Init(tree) ;
    passnoalgL1XE30_handle.Init(tree) ;
    passnoalgL1XE40_handle.Init(tree) ;
    passnoalgL1XE45_handle.Init(tree) ;
    thresh_actint_handle.Init(tree) ;
    passmuon_handle.Init(tree) ;
    passmuvarmed_handle.Init(tree) ;
    cleanCutsFlag_handle.Init(tree) ;
    recalBrokeFlag_handle.Init(tree) ;
    metoffrecal_handle.Init(tree) ;
    mexoffrecal_handle.Init(tree) ;
    meyoffrecal_handle.Init(tree) ;
    metoffrecalmuon_handle.Init(tree) ;
    mexoffrecalmuon_handle.Init(tree) ;
    meyoffrecalmuon_handle.Init(tree) ;
    metrefmuon_handle.Init(tree) ;
    mexrefmuon_handle.Init(tree) ;
    meyrefmuon_handle.Init(tree) ;
    algAmuon_handle.Init(tree) ;
    algBmuon_handle.Init(tree) ;
    metl1muon_handle.Init(tree) ;
    actintmuon_handle.Init(tree) ;

}

void ChainHandler::Init(TTree* const tree)
{
    Init(*tree);
}

void ChainHandler::GetEntry(const unsigned int entry)
{
    run_handle.GetEntry(entry);
    ls_handle.GetEntry(entry);
    event_handle.GetEntry(entry);
    passrndm_handle.GetEntry(entry) ;
    algA_handle.GetEntry(entry) ;
    algB_handle.GetEntry(entry) ;
    metl1_handle.GetEntry(entry) ;
    passnoalgL1XE10_handle.GetEntry(entry) ;
    passnoalgL1XE30_handle.GetEntry(entry) ;
    passnoalgL1XE40_handle.GetEntry(entry) ;
    passnoalgL1XE45_handle.GetEntry(entry) ;
    thresh_actint_handle.GetEntry(entry) ;
    passmuon_handle.GetEntry(entry) ;
    passmuvarmed_handle.GetEntry(entry) ;
    cleanCutsFlag_handle.GetEntry(entry) ;
    recalBrokeFlag_handle.GetEntry(entry) ;
    metoffrecal_handle.GetEntry(entry) ;
    mexoffrecal_handle.GetEntry(entry) ;
    meyoffrecal_handle.GetEntry(entry) ;
    metoffrecalmuon_handle.GetEntry(entry) ;
    mexoffrecalmuon_handle.GetEntry(entry) ;
    meyoffrecalmuon_handle.GetEntry(entry) ;
    metrefmuon_handle.GetEntry(entry) ;
    mexrefmuon_handle.GetEntry(entry) ;
    meyrefmuon_handle.GetEntry(entry) ;
    algAmuon_handle.GetEntry(entry) ;
    algBmuon_handle.GetEntry(entry) ;
    metl1muon_handle.GetEntry(entry) ;
    actintmuon_handle.GetEntry(entry) ;

}

void ChainHandler::LoadAllBranches()
{
    run_handle.Load();
    ls_handle.Load();
    event_handle.Load();
    passrndm_handle.Load();
    algA_handle.Load();
    algB_handle.Load();
    metl1_handle.Load();
    passnoalgL1XE10_handle.Load();
    passnoalgL1XE30_handle.Load();
    passnoalgL1XE40_handle.Load();
    passnoalgL1XE45_handle.Load();
    thresh_actint_handle.Load();
    passmuon_handle.Load();
    passmuvarmed_handle.Load();
    cleanCutsFlag_handle.Load();
    recalBrokeFlag_handle.Load();
    metoffrecal_handle.Load();
    mexoffrecal_handle.Load();
    meyoffrecal_handle.Load();
    metoffrecalmuon_handle.Load();
    mexoffrecalmuon_handle.Load();
    meyoffrecalmuon_handle.Load();
    metrefmuon_handle.Load();
    mexrefmuon_handle.Load();
    meyrefmuon_handle.Load();
    algAmuon_handle.Load();
    algBmuon_handle.Load();
    metl1muon_handle.Load();
    actintmuon_handle.Load();

}

// branch accessor methods:
//implement ChainHandler methods to call Handle objects' get method
const unsigned int& ChainHandler::run() {return run_handle.get();}
const unsigned int& ChainHandler::ls() {return ls_handle.get();}
const unsigned int& ChainHandler::event() {return event_handle.get();}
const Int_t& ChainHandler::passrndm() {return passrndm_handle.get();}
const Float_t& ChainHandler::algA(){return algA_handle.get();};
const Float_t& ChainHandler::algB(){return algB_handle.get();};
const Float_t& ChainHandler::metl1(){return metl1_handle.get();};
const Float_t& ChainHandler::passnoalgL1XE10(){return passnoalgL1XE10_handle.get();};
const Float_t& ChainHandler::passnoalgL1XE30(){return passnoalgL1XE30_handle.get();};
const Float_t& ChainHandler::passnoalgL1XE40(){return passnoalgL1XE40_handle.get();};
const Float_t& ChainHandler::passnoalgL1XE45(){return passnoalgL1XE45_handle.get();};
const Float_t& ChainHandler::thresh_actint()(){return thresh_actint_handle.get();};
const Float_t& ChainHandler::passmuon(){return passmuon_handle.get();};
const Float_t& ChainHandler::passmuvarmed(){return passmuvarmed_handle.get();};
const Float_t& ChainHandler::cleanCutsFlag(){return cleanCutsFlag_handle.get();};
const Float_t& ChainHandler::recalBrokeFlag(){return recalBrokeFlag_handle.get();};
const Float_t& ChainHandler::metoffrecal(){return metoffrecal_handle.get();};
const Float_t& ChainHandler::mexoffrecal(){return mexoffrecal_handle.get();};
const Float_t& ChainHandler::meyoffrecal(){return meyoffrecal_handle.get();};
const Float_t& ChainHandler::metoffrecalmuon(){return metoffrecalmuon_handle.get();};
const Float_t& ChainHandler::mexoffrecalmuon(){return mexoffrecalmuon_handle.get();};
const Float_t& ChainHandler::meyoffrecalmuon(){return meyoffrecalmuon_handle.get();};
const Float_t& ChainHandler::metrefmuon(){return metrefmuon_handle.get();};
const Float_t& ChainHandler::mexrefmuon(){return mexrefmuon_handle.get();};
const Float_t& ChainHandler::meyrefmuon(){return meyrefmuon_handle.get();};
const Float_t& ChainHandler::algAmuon(){return algAmuon_handle.get();};
const Float_t& ChainHandler::algBmuon(){return algBmuon_handle.get();};
const Float_t& ChainHandler::metl1muon(){return metl1muon_handle.get();};
const Float_t& ChainHandler::actintmuon(){return actintmuon_handle.get();};


namespace trkeff
{
    const unsigned int& run() {return ChainHandler_obj .run();}
    const unsigned int& ls() {return ChainHandler_obj .ls();}
    const unsigned int& event() {return ChainHandler_obj .event();}
    const Int_t& get_passrndm(){return ChainHandler_obj.passrndm();}
    const Float_t& get_algA(){return ChainHandler_obj.algA();};
    const Float_t& get_algB(){return ChainHandler_obj.algB();};
    const Float_t& get_metl1(){return ChainHandler_obj.metl1();};
    const Float_t& get_passnoalgL1XE10(){return ChainHandler_obj.passnoalgL1XE10();};
    const Float_t& get_passnoalgL1XE30(){return ChainHandler_obj.passnoalgL1XE30();};
    const Float_t& get_passnoalgL1XE40(){return ChainHandler_obj.passnoalgL1XE40();};
    const Float_t& get_passnoalgL1XE45(){return ChainHandler_obj.passnoalgL1XE45();};
    const Float_t& get_thresh_actint(){return ChainHandler_obj.thresh_actint();};
    const Float_t& get_passmuon(){return ChainHandler_obj.passmuon();};
    const Float_t& get_passmuvarmed(){return ChainHandler_obj.passmuvarmed();};
    const Float_t& get_cleanCutsFlag(){return ChainHandler_obj.cleanCutsFlag();};
    const Float_t& get_recalBrokeFlag(){return ChainHandler_obj.recalBrokeFlag();};
    const Float_t& get_metoffrecal(){return ChainHandler_obj.metoffrecal();};
    const Float_t& get_mexoffrecal(){return ChainHandler_obj.mexoffrecal();};
    const Float_t& get_meyoffrecal(){return ChainHandler_obj.meyoffrecal();};
    const Float_t& get_metoffrecalmuon(){return ChainHandler_obj.metoffrecalmuon();};
    const Float_t& get_mexoffrecalmuon(){return ChainHandler_obj.mexoffrecalmuon();};
    const Float_t& get_meyoffrecalmuon(){return ChainHandler_obj.meyoffrecalmuon();};
    const Float_t& get_metrefmuon(){return ChainHandler_obj.metrefmuon();};
    const Float_t& get_mexrefmuon(){return ChainHandler_obj.mexrefmuon();};
    const Float_t& get_meyrefmuon(){return ChainHandler_obj.meyrefmuon();};
    const Float_t& get_algAmuon(){return ChainHandler_obj.algAmuon();};
    const Float_t& get_algBmuon(){return ChainHandler_obj.algBmuon();};
    const Float_t& get_metl1muon(){return ChainHandler_obj.metl1muon();};
    const Float_t& get_actintmuon(){return ChainHandler_obj.actintmuon();};

} // namespace trkeff
