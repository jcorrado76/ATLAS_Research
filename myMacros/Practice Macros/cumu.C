{
	#include <cassert>
	#include <cmath>
	#include "TH1.h"
	#include "TH1D.h"
	#include "TCanvas.h"
	#include "TRandom.h"
    #include <iostream>


/* this macro shows the template for generate a right hand
cumulative histogram */

	//initialize a new histogram
	TH1* h = new TH1D("histo", "histo", 200, -5., 5.);
	//change seed for generating pseudo random numbers
	gRandom->SetSeed();
	//fil histogram with 10000 random events from gaussian
	h->FillRandom("gaus", 10000);
	//create cumulative distribution function out of histogram h
	TH1* cumu = h->GetCumulative();
	TH1* cumuReverse = h->GetCumulative(kFALSE);
	Double_t * integral = h->GetIntegral();
    std::cout << "cumu->GetNbinsX(): " << cumu->GetNbinsX() << std::endl;
    std::cout << "h->GetEntries(): " << h->GetEntries() << std::endl;
	for (Int_t i = 1; i <= cumu->GetNbinsX(); i++)
	{
        std::cout << "i: " << i << std::endl;
        std::cout << "integral[i]: " << integral[i] << std::endl;
        std::cout << "cumu->GetBinContent(i)" << cumu->GetBinContent(i) << std::endl;
				std::cout << "cumuReverse->GetBinContent(i): " << cumuReverse->GetBinContent(i) << std::endl;
		assert(std::abs(integral[i])*h->GetEntries() - cumu->GetBinContent(i) < 1e-7);
	}
	TCanvas* c = new TCanvas;
	c->Divide(1, 3);
	c->cd(1);
	h->Draw();
	c->cd(2);
	cumu->Draw();
	c->cd(3);
	cumuReverse->Draw();
	c->Update();

}
