{
    TString zb_file_path = "/home/joseph/DATA/ZB_jburr_15thru17_with_missing_et_significance.root";
    TString physics_main_file_path = "/home/joseph/DATA/JETM10_15thru17_with_missing_et_significance.root";
        
    if ( !gSystem->AccessPathName( zb_file_path ) ){
        std::cout << "Could not access " << zb_file_path << std::endl;
        return 0;
    }else if (!gSystem->AccessPathName( physics_main_file_path ) ){
        std::cout << "Could not access " << physics_main_file_path << std::endl;
        return 0;
    }
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

    zb_chain->Process( computeL1XE30toZBEfficiency );
    correctL1XE30ToZB->Set_L1XE30_Efficiency_Fit_Objects((TObjArray*)computeL1XE30toZBEfficiency->Get_L1XE30_Efficiency_Fit_Objects());
    correctL1XE30ToZB->Set_HLT_ZB_L1ZB_MET_Distributions_by_Mubin((TObjArray*)computeL1XE30toZBEfficiency->Get_HLT_ZB_L1ZB_MET_Distributions_by_Mubin());
    jetm10_chain->Process( correctL1XE30ToZB );

    jetm10_chain->Process( computeL1XE50toL1XE30Efficiency );

    // need zb l1 zb met dist for normalization
    CorrectL1XE50DataAllWay->Set_HLT_ZB_L1ZB_MET_Distributions_by_Mubin((TObjArray*)computeL1XE30toZBEfficiency->Get_HLT_ZB_L1ZB_MET_Distributions_by_Mubin());
    CorrectL1XE50DataAllWay->Set_HLT_ZB_L1XE30_MET_Distributions_by_Mubin((TObjArray*)computeL1XE50toL1XE30Efficiency->Get_HLT_ZB_L1XE30_MET_Distributions_by_Mubin());
    CorrectL1XE50DataAllWay->Set_L1XE30_Efficiency_Fit_Objects((TObjArray*)computeL1XE30toZBEfficiency->Get_L1XE30_Efficiency_Fit_Objects());
    CorrectL1XE50DataAllWay->Set_L1XE50_Efficiency_Fit_Objects((TObjArray*)computeL1XE50toL1XE30Efficiency->Get_L1XE50_Efficiency_Fit_Objects());
    CorrectL1XE50DataAllWay->Set_L1XE30_Efficiency_Objects((TObjArray*)computeL1XE30toZBEfficiency->Get_L1XE30_Efficiency_Objects());
    CorrectL1XE50DataAllWay->Set_L1XE50_Efficiency_Objects((TObjArray*)computeL1XE50toL1XE30Efficiency->Get_L1XE50_Efficiency_Objects());
    CorrectL1XE50DataAllWay->Set_HLT_ZB_L1XE30_Corrected_to_ZB_MET_Distribution((TObjArray*)correctL1XE30ToZB->Get_HLT_ZB_L1XE30_Corrected_to_ZB_MET_Distribution());
    // then correct the l1xe50 data back to zerobias
    jetm10_chain->Process( CorrectL1XE50DataAllWay );

    TString filename("mu_analysis.root");
    CorrectL1XE50DataAllWay->Write( filename );
}
