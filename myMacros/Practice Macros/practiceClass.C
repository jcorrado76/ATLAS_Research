#include "practiceClass.h"
#include <iostream>
#include "TObject.h"
#include "TString.h"

#ifdef MAKECINT
#pragma link C++ myClass practiceClass.h
#endif

/* THIS WORKS, AND COMPILES WITH THE HEADER FILE */

Float_t myNumber = 1.0;

    myClass::myClass(){
        std::cout << "Intializing instance of myClass" << std::endl;
        number = myNumber;
    }
    void myClass::SetName( TString newName ) { name = newName ;}
    void myClass::PrintName(void) const {std::cout << "My name is: " << name << std::endl;}
    void myClass::PrintNumber(void) const {std::cout << "The number is: " << number << std::endl;}
