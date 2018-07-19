void fit_efficiency_builtin(){
   //canvas only needed for this documentation
   TCanvas* c1 = new TCanvas("example","",600,400);
   c1->SetFillStyle(1001);
   c1->SetFillColor(kWhite);
   //create one-dimensional TEfficiency object with fixed bin size
   TEfficiency* pEff = new TEfficiency("eff","my efficiency;x;#epsilon",20,0,10);
   TRandom3 rand3;
   bool bPassed;
   double x;
   for(int i=0; i<10000; ++i)
   {
      //simulate events with variable under investigation
      x = rand3.Uniform(10);
      //check selection: bPassed = DoesEventPassSelection(x)
      bPassed = rand3.Rndm() < TMath::Gaus(x,5,4);
      pEff->Fill(bPassed,x);
   }
   //create a function for fitting and do the fit
   TF1* f1 = new TF1("f1","gaus",0,10);
   f1->SetParameters(1,5,2);
   pEff->Fit(f1);
   //create a threshold function
   TF1* f2 = new TF1("thres","0.8",0,10);
   f2->SetLineColor(kRed);
   //add it to the list of functions
   //use add first because the parameters of the last function will be displayed
   pEff->GetListOfFunctions()->AddFirst(f2);
   pEff->Draw("AP");
}
