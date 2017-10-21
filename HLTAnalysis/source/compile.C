//usage: .x compile.C+

#include "TString.h"
#include "TSystem.h"
#include "TROOT.h"
#include <string>

bool compile(const std::string& option = "")
{
    //set up include path
    TString include_path = gSystem->GetIncludePath();
    if (!include_path.Contains("-Iinclude"))
    {
        gSystem->AddIncludePath("-Iinclude");
    }
}
