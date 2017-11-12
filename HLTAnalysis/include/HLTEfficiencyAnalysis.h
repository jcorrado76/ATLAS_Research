#ifndef HLTEfficiencyAnalysis_H
#define HLTEfficiencyAnalysis_H


#include "mincerMacros.h"
#include "ChainHandler.h"


class HLTEfficiencyAnalysis
{
public:
    //constructor
    HLTEfficiencyAnalysis(
        const TString& algA ,
        const TString& algB);

    //destructor
    ~HLTEfficiencyAnalysis();

private:
    //analysis methods
    void Begin();
    void End();
    void DoAnalysis();
    void EvaluateIndividThresh();
    void AnalyzeMuon ();

    //TODO: decide between friend function and an object
    Bisection* bisection;

    //TEfficiencies
    TEfficiency* Ateff;
    TEfficiency* Bteff;
    TEfficiency* Cteff;
    TEfficiency* Dteff;

    //passnoalg hists
    TH1F *algAMETHist;
    TH1F *algBMETHist;
    TH1F *algCMETHist;

    //target passnoalg hists
    TH1F *algATarget;
    TH1F *algBTarget;
    TH1F *algCTarget;

};
#endif//HLTEfficiencyAnalysis_H
