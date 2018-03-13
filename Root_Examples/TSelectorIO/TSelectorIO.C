#define TSelectorIO_cxx


#include "TSelectorIO.h"
#include <TH2.h>
#include <TStyle.h>

void TSelectorIO::Begin(TTree * /*tree*/)
{

   TString option = GetOption();
}

void TSelectorIO::SlaveBegin(TTree * /*tree*/)
{

   TString option = GetOption();

}

Bool_t TSelectorIO::Process(Long64_t entry)
{

   fReader.SetEntry(entry);

   return kTRUE;
}

void TSelectorIO::SlaveTerminate()
{
}

void TSelectorIO::Terminate()
{

    std::cout << "Successfully ran TSelectorIO" << std::endl;
}
