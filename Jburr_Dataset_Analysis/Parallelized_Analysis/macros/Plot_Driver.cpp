#include <TChain.h>
#include <TTree.h>
#include <TProof.h>
#include <TList.h>
#include <TH1F.h>
#include <TROOT.h>
#include <TFile.h>
#include <iostream>
#include "Plot_Driver.h"
#include "Jburr_Selector.h"
#include "Mincer_Selector.h"


void Plot_Driver(){

    TString mincer_zbpath= "$DATA/ZeroBiasL1KF2016R307195R311481.51Runs.root";
    TString jburr_zbpath = "$work/../Jburr_Dataset_Analysis/data/totalntuple16.root";

    if ( gSystem->AccessPathName( mincer_zbpath ) ){
         
        TFile* mincer_file = TFile::Open( mincer_zbpath );

    }
    else{
        std::cout << "Could not access filename " << std::endl;
        std::cout << "Filename:\n" << mincer_zbpath << std::endl;
    }

    if ( gSystem->AccessPathName( jburr_zbpath ) ){
         
        TFile* jburr_file = TFile::Open( jburr_zbpath );

    }
    else{
        std::cout << "Could not access filename " << std::endl;
        std::cout << "Filename:\n" << jburr_zbpath << std::endl;
    }

    Jburr_Selector* jburr_analysis = new Jburr_Selector();
    Mincer_Selector* mincer_analysis = new Mincer_Selector();

    TChain* mincerchain = new TChain( "tree" , "Mincer_Chain" );
    mincerchain->Add( mincer_zbpath );
    TChain* jburrchain = new TChain( "METTree" , "Jburr_Chain" );
    jburrchain->Add( jburr_zbpath );

    TProof* proof = TProof::Open("");

    mincerchain->SetProof();
    mincerchain->Process(mincer_analysis);
    TList* minceroutput = mincer_analysis->GetOutputList();


    jburrchain->SetProof();
    jburrchain->Process(jburr_analysis);
    TList* jburroutput = jburr_analysis->GetOutputList();

    
    TH1F* mincerhist = dynamic_cast<TH1F*>(minceroutput->FindObject("histo1"));
    TH1F* jburrhist = dynamic_cast<TH1F*>(jburroutput->FindObject("histo1"));


    mincerhist->Draw();
    jburrhist->Draw("SAME");
}
