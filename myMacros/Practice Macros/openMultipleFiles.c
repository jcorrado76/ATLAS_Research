const int N = 50;
int count = 0;
int i1 = 1;
double temp1, temp2, temp3;
double arr1[N];
double arr2[N];
double arr3[N];


char filename1[350], filename2[350], filename3[350];
// open the files

while (i1<50)
{
  temp1 = 0.;
  temp2 = 0.;
  temp3 = 0.;

  sprintf(filename1,"../rootFiles_%d/test1.root",i1);

  TFile* f1 = new TFile(filename1,"READONLY");

  if (!f1 || f1->IsZombie())
  {
     printf("Cannot open %s!", filename1);
     return;
  }

  f1->cd("folder1");

  TH1D* h1 = (TH1D*)gDirectory->Get("histo");

  if (!h1)
  {
     printf("Cannot read histo!");
     return;
  }
  
  h1->GetXaxis()->SetRangeUser(0.45,2);
  temp1 = h1->Integral();
  // h1->Delete(); - NO, use delete h1, but histograms are owned by files,
  // so just don't delete it, will be done by delete f1.
  sprintf(filename2,"../rootFiles_%d/test2.root",i1);
  TFile* f2 = new TFile(filename2,"READONLY");
  if (!f2 || f2->IsZombie()) {
     printf("Cannot open %s!", filename2);
     return;
  }
  f2->cd("folder1");
  TH1D* h2 = (TH1D*)gDirectory->Get("histo");
  h2->GetXaxis()->SetRangeUser(0.45,2);
  temp2 = h2->Integral();
  // h2->Delete(); - NO, see above
  arr1[count] = temp1;
  arr2[count] = temp2;
  arr3[count] = temp3;
  i1 += 5;
count += 1;

delete f1;
delete f2;
}
