#include"TreeHandler.h"
#include<iostream>
#include"userInfo.h"


TreeHandler TreeHandler_Obj;




TreeHandler::TreeHandler(const userInfo* parameters )
    : run_handle("run"),
      ls_handle("ls"),
      event_handle("event"),
      passrndm_handle("passrndm"),
      algA_handle(parameters->Get_AlgAName()),
      algB_handle(parameters->Get_AlgBName()),
      metl1_handle("metl1"),
      passnoalgL1XE10_handle("passnoalgL1XE10"),
      passnoalgL1XE30_handle("passnoalgL1XE30"),
      passnoalgL1XE40_handle("passnoalgL1XE40"),
      passnoalgL1XE45_handle("passnoalgL1XE45"),
      actint_handle("actint"),
      passmuon_handle("passmuon"),
      passmuvarmed_handle("passmuvarmed"),
      cleanCutsFlag_handle("passcleancuts"),
      recalBrokeFlag_Handle("recalbroke"),
      metoffrecal_handle("metoffrecal"),
      mexoffrecal_handle("mexoffrecal"),
      meyoffrecal_handle("meyoffrecal"),
      metoffrecalmuon_handle("metoffrecalmuon"),
      mexoffrecalmuon_handle("mexoffrecalmuon"),
      meyoffrecalmuon_handle("meyoffrecalmuon"),
      metrefmuon_handle("metref"),
      mexrefmuon_handle("mexref"),
      meyrefmuon_handle("meyref")
{}

void TTreeReader::Init(TTree& tree)
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
    actint_handle.Init(tree) ;
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
}



void TTreeReader::Init(TTree* const tree)
{
    Init(*tree);
}


void TTreeReader::GetEntry(const unsigned int entry)
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
    actint_handle.GetEntry(entry) ;
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

}

void TTreeReader::LoadAllBranches()
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
    actint_handle.Load();
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

}



const unsigned int& TreeHandler::run() {return run_handle.get();}
const unsigned int& TreeHandler::ls() {return ls_handle.get();}
const unsigned int& TreeHandler::event() {return event_handle.get();}
const Int_t& TreeHandler::passrndm() {return passrndm_handle.get();}
const Float_t& TreeHandler::algA(){return algA_handle.get();};
const Float_t& TreeHandler::algB(){return algB_handle.get();};
const Float_t& TreeHandler::metl1(){return metl1_handle.get();};
const Float_t& TreeHandler::passnoalgL1XE10(){return passnoalgL1XE10_handle.get();};
const Float_t& TreeHandler::passnoalgL1XE30(){return passnoalgL1XE30_handle.get();};
const Float_t& TreeHandler::passnoalgL1XE40(){return passnoalgL1XE40_handle.get();};
const Float_t& TreeHandler::passnoalgL1XE45(){return passnoalgL1XE45_handle.get();};
const Float_t& TreeHandler::thresh_actint()(){return actint_handle.get();};
const Float_t& TreeHandler::passmuon(){return passmuon_handle.get();};
const Float_t& TreeHandler::passmuvarmed(){return passmuvarmed_handle.get();};
const Float_t& TreeHandler::cleanCutsFlag(){return cleanCutsFlag_handle.get();};
const Float_t& TreeHandler::recalBrokeFlag(){return recalBrokeFlag_handle.get();};
const Float_t& TreeHandler::metoffrecal(){return metoffrecal_handle.get();};
const Float_t& TreeHandler::mexoffrecal(){return mexoffrecal_handle.get();};
const Float_t& TreeHandler::meyoffrecal(){return meyoffrecal_handle.get();};
const Float_t& TreeHandler::metoffrecalmuon(){return metoffrecalmuon_handle.get();};
const Float_t& TreeHandler::mexoffrecalmuon(){return mexoffrecalmuon_handle.get();};
const Float_t& TreeHandler::meyoffrecalmuon(){return meyoffrecalmuon_handle.get();};
const Float_t& TreeHandler::metrefmuon(){return metrefmuon_handle.get();};
const Float_t& TreeHandler::mexrefmuon(){return mexrefmuon_handle.get();};
const Float_t& TreeHandler::meyrefmuon(){return meyrefmuon_handle.get();};

namespace TTreeReaderSpace
{
    const unsigned int& run() {return TreeHandler_Obj.run();}
    const unsigned int& ls() {return TreeHandler_Obj.ls();}
    const unsigned int& event() {return TreeHandler_Obj.event();}
    const Int_t& Get_passrndm(){return TreeHandler_Obj.passrndm();}
    const Float_t& Get_algA(){return TreeHandler_Obj.algA();};
    const Float_t& Get_algB(){return TreeHandler_Obj.algB();};
    const Float_t& Get_metl1(){return TreeHandler_Obj.metl1();};
    const Float_t& Get_passnoalgL1XE10(){return TreeHandler_Obj.passnoalgL1XE10();};
    const Float_t& Get_passnoalgL1XE30(){return TreeHandler_Obj.passnoalgL1XE30();};
    const Float_t& Get_passnoalgL1XE40(){return TreeHandler_Obj.passnoalgL1XE40();};
    const Float_t& Get_passnoalgL1XE45(){return TreeHandler_Obj.passnoalgL1XE45();};
    const Float_t& Get_thresh_actint(){return TreeHandler_Obj.actint();};
    const Float_t& Get_passmuon(){return TreeHandler_Obj.passmuon();};
    const Float_t& Get_passmuvarmed(){return TreeHandler_Obj.passmuvarmed();};
    const Float_t& Get_cleanCutsFlag(){return TreeHandler_Obj.cleanCutsFlag();};
    const Float_t& Get_recalBrokeFlag(){return TreeHandler_Obj.recalBrokeFlag();};
    const Float_t& Get_metoffrecal(){return TreeHandler_Obj.metoffrecal();};
    const Float_t& Get_mexoffrecal(){return TreeHandler_Obj.mexoffrecal();};
    const Float_t& Get_meyoffrecal(){return TreeHandler_Obj.meyoffrecal();};
    const Float_t& Get_metoffrecalmuon(){return TreeHandler_Obj.metoffrecalmuon();};
    const Float_t& Get_mexoffrecalmuon(){return TreeHandler_Obj.mexoffrecalmuon();};
    const Float_t& Get_meyoffrecalmuon(){return TreeHandler_Obj.meyoffrecalmuon();};
    const Float_t& Get_metrefmuon(){return TreeHandler_Obj.metrefmuon();};
    const Float_t& Get_mexrefmuon(){return TreeHandler_Obj.mexrefmuon();};
    const Float_t& Get_meyrefmuon(){return TreeHandler_Obj.meyrefmuon();};

} //namespace TTreeReaderSpace 










