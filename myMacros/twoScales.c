void twoscales() 
{
	//create a canvas 
	TCanvas *myCanvas = new TCanvas("myCanvas", "different scales hists", 600, 400);


	//create, fill and draw h1
	gStyle->SetOptStat(kFALSE);
	TH1F *h1 = new TH1F("h1", "my histogram", 100, -3, 3);
	for (Int_t i = 0; i<10000; i++) h1->Fill(gRandom->Gaus(0, 1));
	h1->Draw();
	myCanvas->Update();

	//create integration hist filled with the bins integral of h1
	TH1F *hint1 = new TH1F("hint1", "h1 bins integral", 100, -3, 3);
	Float_t sum = 0;
	//ith bin of hint1 contains cumulative sum of previous i events
	for (Int_t i = 1; i <= 100; i++) {
		sum += h1->GetBinContent(i);
		hint1->SetBinContent(i, sum);
	}
	//scale hint1 to the pad coordinates
	Float_t rightmax = 1.1*hint1->GetMaximum();
	Float_t scale = gPad->GetUymax() / rightmax;
	hint1->SetLineColor(kRed);
	hint1->Scale(scale);
	hint1->Draw("same");
	//draw an axis on the right side
	TGaxis*axis = new TGaxis(gPad->GetUxmax(), gPad->GetUymin(),
		gPad->GetUxmax(), gPad->GetUymax(),
		0, rightmax, 510, "+L");
	axis->SetLineColor(kRed);
	axis->SetLabelColor(kRed);
	axis->Draw();
}