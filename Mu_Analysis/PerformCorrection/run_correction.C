{
    using namespace std;
    cout << "Starting to run correcting distributions" << endl;
    TChain* mychain = new TChain( "METTree" , "mychain" );
    mychain->Add("~/DATA/PhysicsMain/JburrJETM10*");
    mychain->Process("CorrectingDistributions.C+g");
    cout << "Finished running macro" << endl;
}

