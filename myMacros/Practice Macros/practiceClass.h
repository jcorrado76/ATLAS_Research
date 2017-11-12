#include "TObject.h"
#include "TString.h"




class myClass : public TObject
{
    TString name;
    Float_t number;
public:
    myClass();
    void SetName( TString newName );
    void PrintName(void) const;
    void PrintNumber(void) const;
    ClassDef( myClass, 1)
};

#if !defined(__CLING__)
ClassImp(myClass)
#endif
