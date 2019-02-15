{
    std::cout << "Starting mu analysis environment" << std::endl;
    // this is for ACLiC
    gSystem->AddIncludePath("-I/home/joseph/ATLAS_Research/Mu_Analysis/include");
    // shell variables are not expanded in this, nor with .include <path>
    // must give entire path explicitly like this
    gInterpreter->AddIncludePath("-I/home/joseph/ATLAS_Research/Mu_Analysis/include");

    //if (gSystem->CompileMacro("src/Jburr_Template_Selector.C",
            //"k-",
            //"libJburrTemplateSelector",
            //"./lib") == 0) { return false; }

    //if (gSystem->CompileMacro("src/ComputeL1XE30toZBEfficiency.C",
            //"k-",
            //"libComputeL1XE30toZBEfficiency",
            //"./lib") == 0) { return false; }
    //if (gSystem->CompileMacro("src/ComputeL1XE50toL1XE30Efficiency.C",
            //"k-",
            //"libComputeL1XE50toL1XE30Efficiency",
            //"./lib") == 0) { return false; }
    //if (gSystem->CompileMacro("src/CorrectL1XE30toZB.C",
            //"k-",
            //"libCorrectL1XE30toZB",
            //"./lib") == 0) { return false; }
    //if (gSystem->CompileMacro("src/CorrectL1XE50toZB.C",
            //"k-",
            //"libCorrectL1XE50toZB",
            //"./lib") == 0) { return false; }
}

