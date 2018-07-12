Double_t FillFunc(double x)
{
   Double_t y = TMath::Min(500./x, 200.);
   return y;
}

void fa2(){
   TCanvas *c = new TCanvas("c","c", 700, 500);
   c->DrawFrame( 0, 0., 50, 250);

   TF1 *f1 = new TF1("f1","500/x", 0, 50);
   f1->SetLineWidth(2);
   f1->SetLineColor(2);

   TLine *l1 = new TLine(0, 200, 50, 200);
   l1->SetLineWidth(2);

   TLine *l2 = new TLine(40, 0, 40, 250);
   l2->SetLineWidth(2);

   c->SetGrid();
   f1->Draw("same");
   l1->Draw();
   l2->Draw();

   TF1 *fafill = new TF1("fafill","FillFunc(x)",0.,40.);

   fafill->SetFillColor(kRed-3);
   fafill->SetFillStyle(1001);
   fafill->Draw("SAME C");
}
