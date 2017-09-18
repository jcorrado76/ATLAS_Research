#include "TH1.h"

Float_t computeThresh(TH1F* target, Float_t numKeep)
{
    Int_t nbin = 0;
    target->GetBinWithContent(numKeep,nbin,0,-1,20000); //if firstx<=0{firstx=1}; if lastx<firstx{lastx=fXaxis.GetNbinsX()};
    Float_t thresh = (target->GetXaxis())->GetBinCenter(nbin);
    return(thresh);
}
