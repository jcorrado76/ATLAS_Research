
//.x Run_PROOF_Print_7_Eff_TSelector.C

{
    userInfo* parameters = new userInfo()
    TProof* proof = TProof::Open("");
    proof->AddInput( parameters );
    TChain* mychain = new TChain( "tree" , "Individ Eff Thresh Chain" );
    mychain->Add("../../../MyData/PhysicsMain.L1KFmuontriggers.2016.f731f758_m1659m1710.Run309759.48Runs.root");
    mychain->SetProof();
    mychain->Process("Compute_Individ_50_Eff_Point.C+");
}

