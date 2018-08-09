{
    using namespace std;
    cout << "Starting to run correcting distributions" << endl;
    TChain* mychain = new TChain( "METTree" , "mychain" );
    mychain->Add("~/DATA/PhysicsMain/user.jburr.2017_11_17.JETM10/user*");
    mychain->Process("CorrectingDistributions.C+g");
    cout << "Finished running macro" << endl;
}

