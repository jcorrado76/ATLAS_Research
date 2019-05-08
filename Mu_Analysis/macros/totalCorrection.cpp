{
    //TString zb_file_path = "/home/joseph/DATA/ZB_jburr_15thru17_with_missing_et_significance.root";
    //TString physics_main_file_path = "/home/joseph/DATA/user_jburr_JETM10_151617.root";
    TString zb_file_path = "/home/joseph/DATA/jburr_2019_04_24_ZB.root";
    TString physics_main_file_path = "/home/joseph/DATA/jburr_2019_04_24_JETM10.root";
    // initialize tchains
    TChain* zb_chain = new TChain( "METTree" , "zb_chain" );
    TChain* jetm10_chain = new TChain( "METTree", "jetm10chain");

    // initialize analysis objects
    ComputeL1XE30toZBEfficiency* computeL1XE30toZBEfficiency = new ComputeL1XE30toZBEfficiency();
    CorrectL1XE30toZB* correctL1XE30ToZB = new CorrectL1XE30toZB();
    ComputeL1XE50toL1XE30Efficiency* computeL1XE50toL1XE30Efficiency = new ComputeL1XE50toL1XE30Efficiency();
    CorrectL1XE50toZB* CorrectL1XE50DataAllWay = new CorrectL1XE50toZB();

    // add data files to tchains
    zb_chain->Add( zb_file_path );
    jetm10_chain->Add( physics_main_file_path );

    std::cout << "Computing L1XE30 efficiency curves" << std::endl;
    zb_chain->Process( computeL1XE30toZBEfficiency );
    correctL1XE30ToZB->Set_L1XE30_Efficiency_Fit_Objects((TObjArray*)computeL1XE30toZBEfficiency->Get_L1XE30_Efficiency_Fit_Objects());
    correctL1XE30ToZB->Set_HLT_ZB_L1ZB_MET_Distributions_by_Mubin((TObjArray*)computeL1XE30toZBEfficiency->Get_HLT_ZB_L1ZB_MET_Distributions_by_Mubin());
    correctL1XE30ToZB->UpdateFitParameters();
    std::cout << "Correcting L1XE30 Data to ZB" << std::endl;
    jetm10_chain->Process( correctL1XE30ToZB );

    std::cout << "Computing L1XE50 versus l1xe30 efficiency curves" << std::endl;
    jetm10_chain->Process( computeL1XE50toL1XE30Efficiency );

    // need zb l1 zb met dist for normalization
    CorrectL1XE50DataAllWay->Set_HLT_ZB_L1ZB_MET_Distributions_by_Mubin((TObjArray*)computeL1XE30toZBEfficiency->Get_HLT_ZB_L1ZB_MET_Distributions_by_Mubin());
    CorrectL1XE50DataAllWay->Set_HLT_ZB_L1XE30_MET_Distributions_by_Mubin((TObjArray*)computeL1XE50toL1XE30Efficiency->Get_HLT_ZB_L1XE30_MET_Distributions_by_Mubin());
    CorrectL1XE50DataAllWay->Set_L1XE30_Efficiency_Fit_Objects((TObjArray*)computeL1XE30toZBEfficiency->Get_L1XE30_Efficiency_Fit_Objects());
    CorrectL1XE50DataAllWay->Set_L1XE50_Efficiency_Fit_Objects((TObjArray*)computeL1XE50toL1XE30Efficiency->Get_L1XE50_Efficiency_Fit_Objects());
    CorrectL1XE50DataAllWay->Set_L1XE30_Efficiency_Objects((TObjArray*)computeL1XE30toZBEfficiency->Get_L1XE30_Efficiency_Objects());
    CorrectL1XE50DataAllWay->Set_L1XE50_Efficiency_Objects((TObjArray*)computeL1XE50toL1XE30Efficiency->Get_L1XE50_Efficiency_Objects());
    CorrectL1XE50DataAllWay->Set_HLT_ZB_L1XE30_Corrected_to_ZB_MET_Distribution((TObjArray*)correctL1XE30ToZB->Get_HLT_ZB_L1XE30_Corrected_to_ZB_MET_Distribution());
    CorrectL1XE50DataAllWay->UpdateFitParameters();
    // then correct the l1xe50 data back to zerobias
    std::cout << "Correcting L1XE50 Data to ZB" << std::endl;
    jetm10_chain->Process( CorrectL1XE50DataAllWay );

    TString filename("jburr_2019_data_mu_analysis.root");
    CorrectL1XE50DataAllWay->Write( filename );
}
