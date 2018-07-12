void ray() {
   TCanvas *c1 = new TCanvas("c1");
   TF1 *f1 = new TF1("f1","0.7*x*x*x+x*x",0,4);
   f1->Draw();
   TF1 *f2 = new TF1("f2","x*x*x-x*x",0,4);
   f2->Draw("lsame");
   c1->Update();
   const Int_t np = 10, npf = 20;
   
   //first fill area below a sub-range of f2
   Double_t x[np+3], y[np+3];
   Double_t xmin = 2; Double_t xmax = 3;
   Double_t dx = (xmax-xmin)/(np-1);
   for (Int_t i=0;i<np;i++) {
      x[i] = xmin + dx*i;
      y[i] = f2->Eval(x[i]);
   }
   x[np]   = x[np-1]; y[np]   = c1->GetUymin();
   x[np+1] = x[0];    y[np+1] = y[np];
   x[np+2] = x[0];    y[np+2] = y[0];
   TGraph *gr = new TGraph(np+3,x,y);
   gr->SetFillStyle(3008);
   gr->SetFillColor(2);
   gr->Draw("lf");
   
   //second fill area between f1 and f2
   Double_t xf[2*npf+1], yf[2*npf+1];
   Double_t xfmin = 1.5; Double_t xfmax = 3.5;
   Double_t dxf = (xfmax-xfmin)/(npf-1);
   for (Int_t i=0;i<npf;i++) {
      xf[i] = xfmin + dxf*i;
      yf[i] = f2->Eval(xf[i]);
      xf[npf+i] = xfmax - dxf*i;
      yf[npf+i] = f1->Eval(xf[npf+i]);
   }
   xf[2*npf] = xf[0]; yf[2*npf] = yf[0];
   TGraph *grf = new TGraph(2*npf+1,xf,yf);
   grf->SetFillStyle(3024);
   grf->SetFillColor(4);
   grf->Draw("lf");
}
