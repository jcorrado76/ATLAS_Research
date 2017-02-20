

{
	#include <cassert>
	#include <cmath>
	#include "TH1.h"
	#include "TH1D.h"
	#include "TCanvas.h"
	#include "TRandom.h"
	TH1* h = new TH1D("histo", "histo", 200, -5., 5.);
	gRandom->SetSeed();
	h->FillRandom("gaus", 10000);
	TH1* cumu = h->GetCumulative();
	Double_t * integral = h->GetIntegral();
	for (Int_t i = 1; i <= cumu->GetNbinsX(); i++)
	{
		
		assert(std::abs(integral[i])*h->GetEntries() - cumu->GetBinContent(i) < 1e-7);
	}
	TCanvas* c = new TCanvas;
	c->Divide(1, 2);
	c->cd(1);
	h->Draw();
	c->cd(2);
	cumu->Draw();
	c->Update();


}