
/*

You only need practiceClass.C and practiceClassMain.C; no header files needed when you use ACLiC

You have to load .L practiceClass.C+
then .x practiceClassMain.C()

when you want to read the object out of the root file,
you have to initialize an empty ptr to the custom class, and then get object into that pointer
*/

void practiceClassMain(){

class myClass;
gROOT->ProcessLine(".L ~/Documents/root/myMacros/practiceClass.C++");

myClass *instance = new myClass;
instance->SetName("Joseph");

instance->PrintName();
instance->PrintNumber();
}
