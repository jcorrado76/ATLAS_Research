#ifndef MINCERMACROS_H
#define MINCERMACROS_H

#include "userInfo.h"

//TODO: definitely needs better name for this macro. actually make decriptive of what these helpers do

//comptues the met offrecallibrated without muon term value
Float_t computeMetNoMu( const Float_t mexoffrecal , const Float_t meyoffrecal , const Float_t mexoffrecalmuon , const Float_t meyoffrecalmuon );

//returns whether event passed W cut
Bool_t passTransverseMassCut( const Float_t metoffrecal , const Float_t mexoffrecal  , const Float_t meyoffrecal ,
    const Float_t metoffrecalmuon , const Float_t mexoffrecalmuon , const Float_t meyoffrecalmuon );



Bool_t IsMuon( const Float_t passmuon , const Float_t passmuvarmed );

Bool_t IsClean( const Float_t cleancutsflag , const Float_t recalbrokeflag);

//compute threshold to keep numberEventsToKeep on right hand cumu sum hist
Float_t computeThresh(const TH1F* target, const Float_t numberEventsToKeep);


//determine thresh to keep appropriate frac of process 1 events
Float_t determineZeroBiasThresh( const TString& algName, Int_t & numPass , const Float_t frac = 0.00590,
    const TString& threshFileName = "PhysicsMain.All.noalgXEtriggers.2016.f731f758._m1659m1710.48Runs.root");


//simply counts how many muon events passed algs at thresholds
Float_t determineMuonEventsKeptCombined( const TString& algA, const Float_t threshA,const TString& algB, Float_t threshB,
const TString& muonFileName = "PhysicsMain2016.Muons.noalgL1XE45R3073065R311481Runs9B.root");


//determines thresholds to use on two algorithms such that keeps proper fraction of process 1 events when used together
Float_t bisection(TH1F* algAHist , TH1F* algBHist, const Float_t binWidth, Float_t &  individAThreshFinal , Float_t  & individBThreshFinal,
    const Int_t numPassedProcess1WithActintCut = 0 , Float_t frac = 0.00590, TNtuple* logFileData = NULL, TTree* passnoalgTree = NULL);



#endif //MINCERMACROS_H
