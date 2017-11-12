#define zbAnalysis_cxx
// The class definition in zbAnalysis.h has been generated automatically
// by the ROOT utility TTree::MakeSelector(). This class is derived
// from the ROOT class TSelector. For more information on the TSelector
// framework see $ROOTSYS/README/README.SELECTOR or the ROOT User Manual.


// The following methods are defined in this file:
//    Begin():        called every time a loop on the tree starts,
//                    a convenient place to create your histograms.
//    SlaveBegin():   called after Begin(), when on PROOF called only on the
//                    slave servers.
//    Process():      called for each event, in this function you decide what
//                    to read and fill your histograms.
//    SlaveTerminate: called at the end of the loop on the tree, when on PROOF
//                    called only on the slave servers.
//    Terminate():    called at the end of the loop on the tree,
//                    a convenient place to draw/fit your histograms.
//
// To use this file, try the following session on your Tree T:
//
// root> T->Process("zbAnalysis.C")
// root> T->Process("zbAnalysis.C","some options")
// root> T->Process("zbAnalysis.C+")
//


#include "zbAnalysis.h"
#include <TH2.h>
#include <TStyle.h>
#include "userInfo.h"


//TODO: figure out how to pass algName to this macro.
//dedicate this macro to be the parallel version of determineZeroBiasThresh; make separate bisection one
userInfo* logFileParams = new userInfo();

void zbAnalysis::Begin(TTree * /*tree*/)
{
   // The Begin() function is called at the start of the query.
   // When running with PROOF Begin() is only called on the client.
   // The tree argument is deprecated (on PROOF 0 is passed).

   TString option = GetOption();
}

void zbAnalysis::SlaveBegin(TTree * /*tree*/)
{
   // The SlaveBegin() function is called after the Begin() function.
   // When running with PROOF SlaveBegin() is called on each slave server.
   // The tree argument is deprecated (on PROOF 0 is passed).


   //IF YOU NEEDED TO RETURN A HISTOGRAM, INITIALIZE IT HERE
   TString option = GetOption();

   Int_t nbins = 1200;
   Float_t metMin = 0.0;
   Float_t metMax = 300.0;
   Float_t metl1, zb_actint;
   Int_t passnoalgL1XE10, passnoalgL1XE30, passnoalgL1XE40, passnoalgL1XE45;
   //algName is a member variable that needs to be set before use
   TH1F *indeterminateHist = new TH1F(algName, algName, nbins, metMin, metMax);
   fChain->SetBranchAddress(algName,&algMET);
   fChain->SetBranchAddress("metl1",&metl1);
   fChain->SetBranchAddress("passnoalgL1XE10",&passnoalgL1XE10);
   fChain->SetBranchAddress("passnoalgL1XE30",&passnoalgL1XE30);
   fChain->SetBranchAddress("passnoalgL1XE40",&passnoalgL1XE40);
   fChain->SetBranchAddress("passnoalgL1XE45",&passnoalgL1XE45);
   fChain->SetBranchAddress("actint",&zb_actint);



}

Bool_t zbAnalysis::Process(Long64_t entry)
{
   // The Process() function is called for each entry in the tree (or possibly
   // keyed object in the case of PROOF) to be processed. The entry argument
   // specifies which entry in the currently loaded tree is to be processed.
   // When processing keyed objects with PROOF, the object is already loaded
   // and is available via the fObject pointer.
   //
   // This function should contain the \"body\" of the analysis. It can contain
   // simple or elaborate selection criteria, run algorithms on the data
   // of the event and typically fill histograms.
   //
   // The processing can be stopped by calling Abort().
   //
   // Use fStatus to set the return value of TTree::Process().
   //
   // The return value is currently not used.


   //what do you do every entry?
   //call to TH1F->Fill(val) here
   //do I need a "GetEntry(entry)" here? or does this line take care of it?
   fReader.SetEntry(entry);

   if ( ( metl1 > metL1Thresh ) && ( zb_actint > actintCut ) &&
       ( passnoalgL1XE10 > 0.5 || passnoalgL1XE30 > 0.5 || passnoalgL1XE40 > 0.5 || passnoalgL1XE45 > 0.5 ) )
   {
       indeterminateHist->Fill(algMET);
   }

   return kTRUE;
}

void zbAnalysis::SlaveTerminate()
{
   // The SlaveTerminate() function is called after all entries or objects
   // have been processed. When running with PROOF SlaveTerminate() is called
   // on each slave server.

}

void zbAnalysis::Terminate()
{
   // The Terminate() function is the last function to be called during
   // a query. It always runs on the client, it can be used to present
   // the results graphically or save the results to file.

}
