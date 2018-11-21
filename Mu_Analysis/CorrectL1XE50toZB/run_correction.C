{
    using namespace std;
    cout << "Starting to run correcting distributions" << endl;
    TChain* mychain = new TChain( "METTree" , "mychain" );
    mychain->Add("~/DATA/PhysicsMain/user.jburr.2017_11_17.JETM10/*");
    mychain->Process("CorrectL1XE50toZB.C+g");
    printf("Finished running macro");
}

