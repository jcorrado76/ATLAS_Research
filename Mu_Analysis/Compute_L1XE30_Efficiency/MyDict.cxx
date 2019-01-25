// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME MyDict

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "RConfig.h"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Since CINT ignores the std namespace, we need to do so in this file.
namespace std {} using namespace std;

// Header files passed as explicit arguments
#include "ComputeL1XE30toZBEfficiency.h"
#include "../BurrTemplateSelector/Jburr_Template_Selector.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_ComputeL1XE30toZBEfficiency(void *p = 0);
   static void *newArray_ComputeL1XE30toZBEfficiency(Long_t size, void *p);
   static void delete_ComputeL1XE30toZBEfficiency(void *p);
   static void deleteArray_ComputeL1XE30toZBEfficiency(void *p);
   static void destruct_ComputeL1XE30toZBEfficiency(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::ComputeL1XE30toZBEfficiency*)
   {
      ::ComputeL1XE30toZBEfficiency *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::ComputeL1XE30toZBEfficiency >(0);
      static ::ROOT::TGenericClassInfo 
         instance("ComputeL1XE30toZBEfficiency", ::ComputeL1XE30toZBEfficiency::Class_Version(), "ComputeL1XE30toZBEfficiency.h", 27,
                  typeid(::ComputeL1XE30toZBEfficiency), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::ComputeL1XE30toZBEfficiency::Dictionary, isa_proxy, 4,
                  sizeof(::ComputeL1XE30toZBEfficiency) );
      instance.SetNew(&new_ComputeL1XE30toZBEfficiency);
      instance.SetNewArray(&newArray_ComputeL1XE30toZBEfficiency);
      instance.SetDelete(&delete_ComputeL1XE30toZBEfficiency);
      instance.SetDeleteArray(&deleteArray_ComputeL1XE30toZBEfficiency);
      instance.SetDestructor(&destruct_ComputeL1XE30toZBEfficiency);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::ComputeL1XE30toZBEfficiency*)
   {
      return GenerateInitInstanceLocal((::ComputeL1XE30toZBEfficiency*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::ComputeL1XE30toZBEfficiency*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr ComputeL1XE30toZBEfficiency::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *ComputeL1XE30toZBEfficiency::Class_Name()
{
   return "ComputeL1XE30toZBEfficiency";
}

//______________________________________________________________________________
const char *ComputeL1XE30toZBEfficiency::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::ComputeL1XE30toZBEfficiency*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int ComputeL1XE30toZBEfficiency::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::ComputeL1XE30toZBEfficiency*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *ComputeL1XE30toZBEfficiency::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::ComputeL1XE30toZBEfficiency*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *ComputeL1XE30toZBEfficiency::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::ComputeL1XE30toZBEfficiency*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void ComputeL1XE30toZBEfficiency::Streamer(TBuffer &R__b)
{
   // Stream an object of class ComputeL1XE30toZBEfficiency.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(ComputeL1XE30toZBEfficiency::Class(),this);
   } else {
      R__b.WriteClassBuffer(ComputeL1XE30toZBEfficiency::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_ComputeL1XE30toZBEfficiency(void *p) {
      return  p ? new(p) ::ComputeL1XE30toZBEfficiency : new ::ComputeL1XE30toZBEfficiency;
   }
   static void *newArray_ComputeL1XE30toZBEfficiency(Long_t nElements, void *p) {
      return p ? new(p) ::ComputeL1XE30toZBEfficiency[nElements] : new ::ComputeL1XE30toZBEfficiency[nElements];
   }
   // Wrapper around operator delete
   static void delete_ComputeL1XE30toZBEfficiency(void *p) {
      delete ((::ComputeL1XE30toZBEfficiency*)p);
   }
   static void deleteArray_ComputeL1XE30toZBEfficiency(void *p) {
      delete [] ((::ComputeL1XE30toZBEfficiency*)p);
   }
   static void destruct_ComputeL1XE30toZBEfficiency(void *p) {
      typedef ::ComputeL1XE30toZBEfficiency current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::ComputeL1XE30toZBEfficiency

namespace {
  void TriggerDictionaryInitialization_MyDict_Impl() {
    static const char* headers[] = {
"ComputeL1XE30toZBEfficiency.h",
"../BurrTemplateSelector/Jburr_Template_Selector.h",
0
    };
    static const char* includePaths[] = {
"../BurrTemplateSelector/",
"/home/joseph/root_build/include",
"/home/joseph/ATLAS_Research/Mu_Analysis/Compute_L1XE30_Efficiency/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "MyDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate(R"ATTRDUMP(file_name@@@ComputeL1XE30toZBEfficiency.h)ATTRDUMP"))) __attribute__((annotate(R"ATTRDUMP(pattern@@@*)ATTRDUMP"))) __attribute__((annotate("$clingAutoload$ComputeL1XE30toZBEfficiency.h")))  ComputeL1XE30toZBEfficiency;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "MyDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "ComputeL1XE30toZBEfficiency.h"
#include "../BurrTemplateSelector/Jburr_Template_Selector.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"", payloadCode, "@",
"ComputeL1XE30toZBEfficiency", payloadCode, "@",
"ComputeL1XE30toZBEfficiency::Number_Mu_Bins", payloadCode, "@",
"ComputeL1XE30toZBEfficiency::fgIsA", payloadCode, "@",
nullptr};

    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("MyDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_MyDict_Impl, {}, classesHeaders, /*has no C++ module*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_MyDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_MyDict() {
  TriggerDictionaryInitialization_MyDict_Impl();
}
