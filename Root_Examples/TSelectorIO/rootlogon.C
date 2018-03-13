
//ROOTLOGON.C

{

    std::cout << "Loaded TSelectorIO Env" << std::endl;

    gROOT->ProcessLine(".include /inclue");
    std::cout << "Added include directory to include path" << std::endl;

    //gROOT->ProcessLine(".L /myLib/sharedlib.so");
    std::cout << "Loaded Shared libraries" << std::endl;

    /* Can add directory to ACLIC by using:
     * gSystem->AddIncludePath(" -I/my/include/dir ");
     * gSystem->AddLinkedLibs(" /mu/lib/libshared.so");*/
}
    
