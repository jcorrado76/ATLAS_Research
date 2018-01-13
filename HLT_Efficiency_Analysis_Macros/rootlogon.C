//The macro, rootlogon.C is executed when root starts, unless -n is passed
//
//this macro will start up the ATLAS research environment, including my helper
//macros, and my custom class that records the parameters of bisection

{
    std::cout << "Started ATLAS_Research Environmnet" << std::endl;

    //set up include path
    TString include_path = gSystem->GetIncludePath();

    //add include directory to include path
    if (!include_path.Contains("-I./include"))
    {
        gSystem->AddIncludePath("-I./include");
    }
    std::cout << "Added local include directory to the include path" << std::endl;
    
    /*CompileMacroSyntax {{{
            k option - keep shared library after session end 
            - option - use flat builddir structure 
            3rd arg specifies name of lib
            4th arg specifies location of generated lib
            (requires - option as well)
            }}}*/

    if (gSystem->CompileMacro("Env_Macros/Parameter_Class.C" , 
                              "k-"         , 
                              "libUserInfo",
                              "./lib")
                    == 0) {return false;}

    if (gSystem->CompileMacro("Env_Macros/Efficiency_Library.C",
                              "k-"                  , 
                              "libHelpers"          ,
                              "./lib") 
                    == 0) {return false;}

    if (gSystem->CompileMacro("Env_Macros/Bisection/[DEPRECT.]Histo_Bisection.C",
                              "k-"                  , 
                              "libBisection"          ,
                              "./lib") 
                    == 0) {return false;}

    if (gSystem->CompileMacro("Env_Macros/Bisection_Single_Frac/Bisection_One_Frac_Fixed.C",
                              "k-"                  , 
                              "libBisectionOneFracFixed"          ,
                              "./lib") 
                    == 0) {return false;}
    
    std::cout << "Environment successfully compiled" << std::endl;
}




