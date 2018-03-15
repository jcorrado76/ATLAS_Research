#include <TH1F.h>
#include <TList.h>
#include <TFile.h>
#include <TCanvas.h>

void HistListDiffRunNumbers(){

    //for each run number in which there is a difference, create a histogram of the event numbers of both mincer's and
    //jburr's events and see what the overlap by event number is. This would show if either of them included the same
    //file twice, and in which events within a run there is a difference
    
    TFile* mincerfile = TFile::Open("$DATA/ZeroBiasL1KF2016R307195R311481.51Runs.root","READ");  
    TFile* jburrfile = TFile::Open("data/totalntuple16.root","READ");
    TFile* nonzerorunNumFile = TFile::Open("NonZeroRunNumbers.root","READ");

    TTree* mincertree = (TTree*) mincerfile->Get("tree");
    TTree* burrtree = (TTree*) jburrfile->Get("METTree");
    TNtuple* NonZeroRunNumbers = (TNtuple*) nonzerorunNumFile->Get("ntuple");

    UInt_t RunNumber;
    Int_t MincerEventNumMinimum = -2.1474832e9;
    Int_t MincerEventNumMaximum = 2.1474833e9;
    Int_t JburrEventNumMinimum = 32452;
    Int_t JburrEventNumMaximum = 7.040243e9;

    Int_t runLow = 307195;
    Int_t runHigh = 311481;
    Int_t nbins = 10000;

    Int_t mincerRunNumber, jburrRunNumber;
    Int_t mincerEventNumber;
    ULong64_t jburrEventNumber;
    Int_t mincerpassrndm;
    Bool_t jburrpassrndm;

    TList* mincerhistlist = new TList();
    TList* staggeredmincerhistlist = new TList();
    TList* burrhistlist = new TList();
    TList* canvaslist = new TList();
    TList* diffhistlist = new TList();

    TH1F* mincerhist = 0;    
    TH1F* mincerstaggeredhist = 0;
    TH1F* burrhist = 0;  
    TH1F* diffhist = 0;
    TCanvas* canv = 0;

    Float_t TargetRunNumber = 0;

    NonZeroRunNumbers->SetBranchAddress("Run_Number",&TargetRunNumber);
    mincertree->SetBranchAddress("eventnum",&mincerEventNumber);
    mincertree->SetBranchAddress("runnum",&mincerRunNumber);
    mincertree->SetBranchAddress("passrndm",&mincerpassrndm);
    burrtree->SetBranchAddress("EventNumber",&jburrEventNumber);
    burrtree->SetBranchAddress("HLT_noalg_zb_L1ZB.passed",&jburrpassrndm);
    burrtree->SetBranchAddress("RunNumber",&RunNumber);

    TString mincerhistname = "mincerhist";
    TString mincerstaggeredhistname = "staggered_mincerhist";
    TString burrhistname = "burrhist";
    TString diffhistname = "diffhist";
    TString canvname = "canv";

    Int_t mincerentries = mincertree->GetEntries();
    Int_t burrentries = burrtree->GetEntries();
   
    for ( Int_t j = 0 ; j < NonZeroRunNumbers->GetEntries() ; j++ ){
        //for each nonzero run number, fill 2 histograms with events distributed by event number 
        //append each hist to the corresponding tlist
        //then make the difference hist ; add to corresponding tlist
        //then make the canvas of the staggered version of the hist and add to corresponding tlist 

        NonZeroRunNumbers->GetEntry(j);


        mincerhistname += j;
        burrhistname += j;
        canvname += j;
        mincerstaggeredhistname += j;
        diffhistname += j;

        mincerhist = new TH1F( mincerhistname , mincerhistname , nbins , MincerEventNumMinimum, MincerEventNumMaximum);
        mincerstaggeredhist = new TH1F( mincerstaggeredhistname , mincerstaggeredhistname, nbins , MincerEventNumMinimum, MincerEventNumMaximum);
        burrhist = new TH1F( burrhistname , burrhistname , nbins , JburrEventNumMinimum, JburrEventNumMaximum);
        diffhist = new TH1F( diffhistname , diffhistname , nbins, MincerEventNumMinimum , MincerEventNumMaximum);
        canv = new TCanvas(canvname , canvname);

        for ( Int_t i = 0 ; i < mincerentries ; i++){
            mincertree->GetEntry(i);
            if (mincerpassrndm > 0.5 && mincerRunNumber == TargetRunNumber ){
            mincerhist->Fill( mincerEventNumber );
            mincerstaggeredhist->Fill( mincerEventNumber + 10. );
            }
        }

        for ( Int_t i = 0 ; i < burrentries; i++){
            burrtree->GetEntry(i);
            if (jburrpassrndm && RunNumber == TargetRunNumber ){
            burrhist->Fill( jburrEventNumber );
            }
        }

        diffhist->Add(mincerhist,burrhist,1.,-1.);

        mincerstaggeredhist->SetLineColor(kRed);
        burrhist->SetLineColor(kBlue);

        mincerstaggeredhist->Draw();
        burrhist->Draw();

        
        mincerhistlist->Add(mincerhist);
        burrhistlist->Add(burrhist);
        staggeredmincerhistlist->Add(mincerstaggeredhist);
        canvaslist->Add(canv);
        diffhistlist->Add(diffhist);

        mincerhistname = "mincerhist";
        mincerstaggeredhistname = "staggered_mincerhist";
        burrhistname = "burrhist";
        diffhistname = "diffhist";
        canvname = "canv";

    }



    //create a new file containing the Tlists of jburr hists, mincer hists, diff hists, and combined tcanvases
    TFile* outfile = TFile::Open("HistList.root", "RECREATE");
    mincerhistlist->Write("MincerHistList", option = 1);
    burrhistlist->Write("BurrHistList" , option = 1);
    staggeredmincerhistlist->Write("StaggeredMincerHistList", option =1 );
    canvaslist->Write("CanvasList", option =1 );
    diffhistlist->Write("DiffHistList", option=1);

}
