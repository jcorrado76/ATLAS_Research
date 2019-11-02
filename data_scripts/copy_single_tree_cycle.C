{
   const auto filename = "ZB_jburr_15thru17_with_missing_et_significance.root";
   TFile oldfile(filename);
   TTree *oldtree;
   oldfile.GetObject("METTree;62", oldtree);

   // Create a new file + a clone of old tree in new file
   TFile newfile(filename, "recreate");
   auto newtree = oldtree->CloneTree();

   newtree->Print();
   newfile.Write();
}
