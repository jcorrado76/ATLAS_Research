#include "fitFunction.h"
double fitFunction(double *x , double *par ){
    /*
     * Parameter 0 - initial slope
     * Parameter 1 - initial intercept
     * Parameter 2 - initial sigma
     * Parameter 3 - L1XE
     */

    double fitval = (1./2.)*(1.+TMath::Erf((par[0]*x[0]+par[1]-par[3])/(par[2]*TMath::Sqrt(2.))));
    return fitval;
}
