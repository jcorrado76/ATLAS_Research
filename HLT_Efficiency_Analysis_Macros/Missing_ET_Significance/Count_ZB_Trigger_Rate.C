#define Count_ZB_Trigger_Rate_cxx
#include "Count_ZB_Trigger_Rate.h"

void Count_ZB_Trigger_Rate::Begin(TTree * /*tree*/)
{
   TString option = GetOption();
}

void Count_ZB_Trigger_Rate::SlaveBegin(TTree * /*tree*/)
{
   TString option = GetOption();
}

Bool_t Count_ZB_Trigger_Rate::Process(Long64_t entry)
{
   fReader.SetEntry(entry);
    isRndm = *passrndm;
    isClean = (*passcleancuts > 0.1) && ( *recalbroke < 0.1);
    passTransverseMassCut = Efficiency_Lib::passTransverseMassCut( *metoffrecal , *mexoffrecal , *meyoffrecal , *metoffrecalmuon , *mexoffrecalmuon , *meyoffrecalmuon );
    isL1 = *metl1 > metl1thresh;
    isPassnoalg = *passnoalgL1XE10 > passnoalgcut || *passnoalgL1XE30 > passnoalgcut ||
        *passnoalgL1XE40 > passnoalgcut || *passnoalgL1XE45 > passnoalgcut;

    if (passTransverseMassCut){
        pass_transverse_mass++;
    }
    if ( isClean ){
        pass_clean_cuts++;
    }
    if ( ( isRndm || isPassnoalg ) && isL1 && isClean && passTransverseMassCut && ( *actint > actintCut ) )
    {
        if ( *mettopoclpuc > puc_efficiency_thresh ){
            pass_puc++;
        }
        if ( *metcell > cell_efficiency_thresh ){
            pass_cell++;
        }
        if ( *missing_et_significance > met_significance_thresh_one ){
            pass_etmiss_7++;
        }
        if ( *missing_et_significance > met_significance_thresh_two ){
            pass_etmiss_5++;
        }
        if ( *missing_et_significance > met_significance_thresh_three ){
            pass_etmiss_3++;
        }
    }
   return kTRUE;
}

void Count_ZB_Trigger_Rate::SlaveTerminate(){}
void Count_ZB_Trigger_Rate::Terminate()
{
    std::cout << "Number of events passing cell: " << pass_cell << std::endl;
    std::cout << "Number of events passing puc: " << pass_puc << std::endl;
    std::cout << "Number of events passing etmiss > 7.12: " << pass_etmiss_7 << std::endl;
    std::cout << "Number of events passing etmiss > 5: " << pass_etmiss_5 << std::endl;
    std::cout << "Number of events passing etmiss > 3: " << pass_etmiss_3 << std::endl;
    std::cout << "Number of events passing transverse mass cut: " << pass_transverse_mass << std::endl;
    std::cout << "Number of events passing clean cuts: " << pass_clean_cuts << std::endl;
}
