#ifndef MINCERMACROS_H
#define MINCERMACROS_H

#include "userInfo.h"
//#include "ZBKFThresh.h"
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
Float_t determineZeroBiasThresh( userInfo* parameters , const Bool_t verbose = false );


//simply counts how many muon events passed algs at thresholds
Float_t determineMuonEventsKeptCombined( const TString& algA, const Float_t threshA,const TString& algB, Float_t threshB,
const TString& muonFileName = "PhysicsMain2016.Muons.noalgL1XE45R3073065R311481Runs9B.root", Float_t metl1thresh = 0.0);


//determines thresholds to use on two algorithms such that keeps proper fraction of process 1 events when used together
Float_t bisection(  userInfo* parameters , TH1F* algAHist , TH1F* algBHist, TTree* passnoalgTree );



#endif //MINCERMACROS_H
