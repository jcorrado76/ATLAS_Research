#include "userInfo.h"


{
userInfo logFileParams;

Int_t nbins = 1200;
Float_t metMin = 0.0;
Float_t metMax = 300.0;
Float_t metl1thresh = 50.0;
Float_t frac = 0.0059;
TString& zerobiasFileName = "PhysicsMain.All.noalgXEtriggers.2016.f731f758._m1659m1710.48Runs.root";
TString& muonFilename = "PhysicsMain.L1KFmuontriggers.2016.f731f758_m1659m1710.Run309759.48Runs.root";
Float_t actintCut = 35.0;


logFileParams.nbins = nbins;
logFileParams.metmin = metMin;
logFileParams.metmax = metMax;
logFileParams.metl1thresh = metl1thresh;
logFileParams.frac = frac;
logFileParams.zbFileName = zerobiasFileName;
logFileParams.muonFileName = muonFilename;
logFileParams.actintCut = actintCut;




}






//TODO: define th evariables in the userinfo struct in this file. Needs to import userinfo.h
