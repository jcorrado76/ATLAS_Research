{
/*
This code will find the integral between two x values of the histogram
instead of bin numbers
*/


//find bin number for a given value of x
int bin = h->GetXAxis()->FindBin(x);

TAxis *axis = h->GetXaxis();

//determine the lower bin value corresponding to lower abscissa
int bmin = axis->FindBin(xmin);

//determine the upper bin value corresponding to upper abscissa
int bmax = axis->FindBin(xmax);

double integral = h->Integral(bmin,bmax);

integral -= h->GetBinContent(bmin)*((xmin-axis)->GetBinLowEdge(bmin))/
            axis->GetBinWidth(bmin);

integral -= h->GetBinContent(bmax)*(axis->GetBinUpEdge(bmax)-xmax)/
            axis->GetBinWidth(bmax);


}
