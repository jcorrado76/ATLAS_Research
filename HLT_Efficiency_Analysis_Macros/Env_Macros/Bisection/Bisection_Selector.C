#define Bisection_Selector_cxx

#include "Bisection_Selector.h"
#include <TH2.h>
#include <TStyle.h>


/* This macro will be what occurs in a single iteration of the bisection. It
    will take in the names of the two algs, the individ fraction, and it will
    return 

    

This will be the body of each iteration of bisection.


   */

void Bisection_Selector::Begin(TTree * /*tree*/)
{

   TString option = GetOption();
}

void Bisection_Selector::SlaveBegin(TTree * /*tree*/)
{

}

Bool_t Bisection_Selector::Process(Long64_t entry)
{
   fReader.SetEntry(entry);

   return kTRUE;
}

void Bisection_Selector::SlaveTerminate()
{

}

void Bisection_Selector::Terminate()
{

}
