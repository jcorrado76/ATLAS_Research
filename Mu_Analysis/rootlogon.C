{
    std::cout << "Starting mu analysis environment" << std::endl;
    gSystem->AddIncludePath("-I$HOME/ATLAS_Research/Mu_Analysis/include");

    if (gSystem->CompileMacro("src/Jburr_Template_Selector.C",
            "k-",
            "libJburrTemplateSelector",
            "./lib") == 0) { return false; }

    if (gSystem->CompileMacro("src/ComputeL1XE30toZBEfficiency.C",
            "k-",
            "libComputeL1XE30toZBEfficiency",
            "./lib") == 0) { return false; }
    if (gSystem->CompileMacro("src/ComputeL1XE50toL1XE30Efficiency.C",
            "k-",
            "libComputeL1XE50toL1XE30Efficiency",
            "./lib") == 0) { return false; }
    if (gSystem->CompileMacro("src/CorrectL1XE30toZB.C",
            "k-",
            "libCorrectL1XE30toZB",
            "./lib") == 0) { return false; }
    if (gSystem->CompileMacro("src/CorrectL1XE50toZB.C",
            "k-",
            "libCorrectL1XE50toZB",
            "./lib") == 0) { return false; }
}

