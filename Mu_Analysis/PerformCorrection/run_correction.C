{
    TChain* mychain = new TChain( "METTree" , "mychain" );
    mychain->Add("~/Downloads/user.jburr.2017_11_17.JETM10/*");
    mychain->Process("CorrectingDistributions.C+");
}

