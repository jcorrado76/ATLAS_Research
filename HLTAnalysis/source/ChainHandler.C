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
    //TODO: replace branches
    run_handle.Init(tree);
    ls_handle.Init(tree);
    event_handle.Init(tree);
    trks_p4_handle.Init(tree);
    trks_d0_handle.Init(tree);
    trks_dz_handle.Init(tree);
    trks_pterr_handle.Init(tree);
    trks_d0err_handle.Init(tree);
    trks_dzerr_handle.Init(tree);
    trks_chi2_handle.Init(tree);
    trks_ndof_handle.Init(tree);
    trks_nlayers_handle.Init(tree);
    trks_high_purity_handle.Init(tree);
    tps_matched_handle.Init(tree);
    tps_pdgid_handle.Init(tree);
    tps_p4_handle.Init(tree);
    tps_d0_handle.Init(tree);
    tps_dz_handle.Init(tree);
    tps_tip_handle.Init(tree);
    tps_lip_handle.Init(tree);
    tps_charge_handle.Init(tree);
    tps_nhits_handle.Init(tree);

}

void ChainHandler::Init(TTree* const tree)
{
    Init(*tree);
}

void ChainHandler::GetEntry(const unsigned int entry)
{
    //TODO: replace branches
    run_handle.GetEntry(entry);
    ls_handle.GetEntry(entry);
    event_handle.GetEntry(entry);
    trks_p4_handle.GetEntry(entry);
    trks_d0_handle.GetEntry(entry);
    trks_dz_handle.GetEntry(entry);
    trks_pterr_handle.GetEntry(entry);
    trks_d0err_handle.GetEntry(entry);
    trks_dzerr_handle.GetEntry(entry);
    trks_chi2_handle.GetEntry(entry);
    trks_ndof_handle.GetEntry(entry);
    trks_nlayers_handle.GetEntry(entry);
    trks_high_purity_handle.GetEntry(entry);
    tps_matched_handle.GetEntry(entry);
    tps_pdgid_handle.GetEntry(entry);
    tps_p4_handle.GetEntry(entry);
    tps_d0_handle.GetEntry(entry);
    tps_dz_handle.GetEntry(entry);
    tps_tip_handle.GetEntry(entry);
    tps_lip_handle.GetEntry(entry);
    tps_charge_handle.GetEntry(entry);
    tps_nhits_handle.GetEntry(entry);

}

void ChainHandler::LoadAllBranches()
{
    //TODO: replace branches
    run_handle.Load();
    ls_handle.Load();
    event_handle.Load();
    trks_p4_handle.Load();
    trks_d0_handle.Load();
    trks_dz_handle.Load();
    trks_pterr_handle.Load();
    trks_d0err_handle.Load();
    trks_dzerr_handle.Load();
    trks_chi2_handle.Load();
    trks_ndof_handle.Load();
    trks_nlayers_handle.Load();
    trks_high_purity_handle.Load();
    tps_matched_handle.Load();
    tps_pdgid_handle.Load();
    tps_p4_handle.Load();
    tps_d0_handle.Load();
    tps_dz_handle.Load();
    tps_tip_handle.Load();
    tps_lip_handle.Load();
    tps_charge_handle.Load();
    tps_nhits_handle.Load();

}

// branch accessor methods:
//TODO: replace branch
const unsigned int& ChainHandler::run() {return run_handle.get();}
const unsigned int& ChainHandler::ls() {return ls_handle.get();}
const unsigned int& ChainHandler::event() {return event_handle.get();}
const std::vector<LorentzVectorD >& ChainHandler::trks_p4() {return trks_p4_handle.get();}
const std::vector<double>& ChainHandler::trks_d0() {return trks_d0_handle.get();}
const std::vector<double>& ChainHandler::trks_dz() {return trks_dz_handle.get();}
const std::vector<double>& ChainHandler::trks_pterr() {return trks_pterr_handle.get();}
const std::vector<double>& ChainHandler::trks_d0err() {return trks_d0err_handle.get();}
const std::vector<double>& ChainHandler::trks_dzerr() {return trks_dzerr_handle.get();}
const std::vector<double>& ChainHandler::trks_chi2() {return trks_chi2_handle.get();}
const std::vector<int>& ChainHandler::trks_ndof() {return trks_ndof_handle.get();}
const std::vector<int>& ChainHandler::trks_nlayers() {return trks_nlayers_handle.get();}
const std::vector<bool>& ChainHandler::trks_high_purity() {return trks_high_purity_handle.get();}
const std::vector<bool>& ChainHandler::tps_matched() {return tps_matched_handle.get();}
const std::vector<int>& ChainHandler::tps_pdgid() {return tps_pdgid_handle.get();}
const std::vector<LorentzVectorD >& ChainHandler::tps_p4() {return tps_p4_handle.get();}
const std::vector<double>& ChainHandler::tps_d0() {return tps_d0_handle.get();}
const std::vector<double>& ChainHandler::tps_dz() {return tps_dz_handle.get();}
const std::vector<double>& ChainHandler::tps_tip() {return tps_tip_handle.get();}
const std::vector<double>& ChainHandler::tps_lip() {return tps_lip_handle.get();}
const std::vector<int>& ChainHandler::tps_charge() {return tps_charge_handle.get();}
const std::vector<int>& ChainHandler::tps_nhits() {return tps_nhits_handle.get();}





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
