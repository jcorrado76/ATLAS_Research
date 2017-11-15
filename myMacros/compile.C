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

    //compile and load source

    //compile each one; k means keep shared library after session end; call it "libHistTools", send to "lib"
    if (gSystem->CompileMacro("userInfo.C", (option + "k-").c_str(), "libUserInfo","lib") == 0) {return false;}
    if (gSystem->CompileMacro("threeEfficiencies.C", (option + "k-").c_str(), "libThreeEfficiencies","lib") == 0) {return false;}
    if (gSystem->CompileMacro("mincerMacros.C", (option + "k-").c_str(), "libMincerMacros","lib") == 0) {return false;}
    if (gSystem->CompileMacro("bisection.C", (option + "k-").c_str(), "libBisection","lib") == 0) {return false;}
    if (gSystem->CompileMacro("generateEfficiencies.C", (option + "k-").c_str(), "libGenEff","lib") == 0) {return false;}
    if (gSystem->CompileMacro("threeEfficienciesL1.C", (option + "k-").c_str(), "libThreeEffL1","lib") == 0) {return false;}
    //successfully compiled dependencies
    return true;

}

//clean up library directory

//usage: .L compile.C+; clean()

void clean()
{
    gSystem->Exec("rm lib/*");
}
