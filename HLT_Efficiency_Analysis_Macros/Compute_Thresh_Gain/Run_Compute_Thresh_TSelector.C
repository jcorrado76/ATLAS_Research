
//.x Run_PROOF_Print_7_Eff_TSelector.C

int Run_Compute_Thresh_TSelector(const TString AlgName) {
    userInfo* parameters = new userInfo();
    parameters->Read_Parameter_File("../parameter_files/HLTAnalysisParameters.txt");
    parameters->Set_AlgAName(AlgName);
    TProof* proof = TProof::Open("");
    proof->AddInput( parameters );
    TChain* mychain = new TChain( "tree" , "Individ Eff Thresh Chain" );
    mychain->Add("../../../MyData/PhysicsMain.L1KFmuontriggers.2016.f731f758_m1659m1710.Run309759.48Runs.root");
    mychain->SetProof();
    mychain->Process("Compute_Individ_50_Eff_Point.C+");
}

