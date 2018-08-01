{
    TChain* mychain = new TChain( "METTree" , "mychain" );
    mychain->Add("~/DATA/Jburr*");
    mychain->Process("CorrectingDistributions.C+g");
}

