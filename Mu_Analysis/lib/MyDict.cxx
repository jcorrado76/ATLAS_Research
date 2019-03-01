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
#include "../include/CorrectL1XE30toZB.h"
#include "../include/CorrectL1XE50toZB.h"
#include "../include/fitFunction.h"
#include "../include/ComputeL1XE30toZBEfficiency.h"
#include "../include/ComputeL1XE50toL1XE30Efficiency.h"
#include "../include/Jburr_Template_Selector.h"

// Header files passed via #pragma extra_include

namespace ROOT {
   static void *new_Jburr_Template_Selector(void *p = 0);
   static void *newArray_Jburr_Template_Selector(Long_t size, void *p);
   static void delete_Jburr_Template_Selector(void *p);
   static void deleteArray_Jburr_Template_Selector(void *p);
   static void destruct_Jburr_Template_Selector(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::Jburr_Template_Selector*)
   {
      ::Jburr_Template_Selector *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::Jburr_Template_Selector >(0);
      static ::ROOT::TGenericClassInfo 
         instance("Jburr_Template_Selector", ::Jburr_Template_Selector::Class_Version(), "Jburr_Template_Selector.h", 27,
                  typeid(::Jburr_Template_Selector), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::Jburr_Template_Selector::Dictionary, isa_proxy, 4,
                  sizeof(::Jburr_Template_Selector) );
      instance.SetNew(&new_Jburr_Template_Selector);
      instance.SetNewArray(&newArray_Jburr_Template_Selector);
      instance.SetDelete(&delete_Jburr_Template_Selector);
      instance.SetDeleteArray(&deleteArray_Jburr_Template_Selector);
      instance.SetDestructor(&destruct_Jburr_Template_Selector);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::Jburr_Template_Selector*)
   {
      return GenerateInitInstanceLocal((::Jburr_Template_Selector*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::Jburr_Template_Selector*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

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
         instance("ComputeL1XE30toZBEfficiency", ::ComputeL1XE30toZBEfficiency::Class_Version(), "ComputeL1XE30toZBEfficiency.h", 4,
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

namespace ROOT {
   static void *new_CorrectL1XE30toZB(void *p = 0);
   static void *newArray_CorrectL1XE30toZB(Long_t size, void *p);
   static void delete_CorrectL1XE30toZB(void *p);
   static void deleteArray_CorrectL1XE30toZB(void *p);
   static void destruct_CorrectL1XE30toZB(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::CorrectL1XE30toZB*)
   {
      ::CorrectL1XE30toZB *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::CorrectL1XE30toZB >(0);
      static ::ROOT::TGenericClassInfo 
         instance("CorrectL1XE30toZB", ::CorrectL1XE30toZB::Class_Version(), "CorrectL1XE30toZB.h", 5,
                  typeid(::CorrectL1XE30toZB), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::CorrectL1XE30toZB::Dictionary, isa_proxy, 4,
                  sizeof(::CorrectL1XE30toZB) );
      instance.SetNew(&new_CorrectL1XE30toZB);
      instance.SetNewArray(&newArray_CorrectL1XE30toZB);
      instance.SetDelete(&delete_CorrectL1XE30toZB);
      instance.SetDeleteArray(&deleteArray_CorrectL1XE30toZB);
      instance.SetDestructor(&destruct_CorrectL1XE30toZB);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::CorrectL1XE30toZB*)
   {
      return GenerateInitInstanceLocal((::CorrectL1XE30toZB*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::CorrectL1XE30toZB*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_ComputeL1XE50toL1XE30Efficiency(void *p = 0);
   static void *newArray_ComputeL1XE50toL1XE30Efficiency(Long_t size, void *p);
   static void delete_ComputeL1XE50toL1XE30Efficiency(void *p);
   static void deleteArray_ComputeL1XE50toL1XE30Efficiency(void *p);
   static void destruct_ComputeL1XE50toL1XE30Efficiency(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::ComputeL1XE50toL1XE30Efficiency*)
   {
      ::ComputeL1XE50toL1XE30Efficiency *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::ComputeL1XE50toL1XE30Efficiency >(0);
      static ::ROOT::TGenericClassInfo 
         instance("ComputeL1XE50toL1XE30Efficiency", ::ComputeL1XE50toL1XE30Efficiency::Class_Version(), "ComputeL1XE50toL1XE30Efficiency.h", 14,
                  typeid(::ComputeL1XE50toL1XE30Efficiency), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::ComputeL1XE50toL1XE30Efficiency::Dictionary, isa_proxy, 4,
                  sizeof(::ComputeL1XE50toL1XE30Efficiency) );
      instance.SetNew(&new_ComputeL1XE50toL1XE30Efficiency);
      instance.SetNewArray(&newArray_ComputeL1XE50toL1XE30Efficiency);
      instance.SetDelete(&delete_ComputeL1XE50toL1XE30Efficiency);
      instance.SetDeleteArray(&deleteArray_ComputeL1XE50toL1XE30Efficiency);
      instance.SetDestructor(&destruct_ComputeL1XE50toL1XE30Efficiency);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::ComputeL1XE50toL1XE30Efficiency*)
   {
      return GenerateInitInstanceLocal((::ComputeL1XE50toL1XE30Efficiency*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::ComputeL1XE50toL1XE30Efficiency*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_CorrectL1XE50toZB(void *p = 0);
   static void *newArray_CorrectL1XE50toZB(Long_t size, void *p);
   static void delete_CorrectL1XE50toZB(void *p);
   static void deleteArray_CorrectL1XE50toZB(void *p);
   static void destruct_CorrectL1XE50toZB(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::CorrectL1XE50toZB*)
   {
      ::CorrectL1XE50toZB *ptr = 0;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::CorrectL1XE50toZB >(0);
      static ::ROOT::TGenericClassInfo 
         instance("CorrectL1XE50toZB", ::CorrectL1XE50toZB::Class_Version(), "CorrectL1XE50toZB.h", 7,
                  typeid(::CorrectL1XE50toZB), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::CorrectL1XE50toZB::Dictionary, isa_proxy, 4,
                  sizeof(::CorrectL1XE50toZB) );
      instance.SetNew(&new_CorrectL1XE50toZB);
      instance.SetNewArray(&newArray_CorrectL1XE50toZB);
      instance.SetDelete(&delete_CorrectL1XE50toZB);
      instance.SetDeleteArray(&deleteArray_CorrectL1XE50toZB);
      instance.SetDestructor(&destruct_CorrectL1XE50toZB);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::CorrectL1XE50toZB*)
   {
      return GenerateInitInstanceLocal((::CorrectL1XE50toZB*)0);
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal((const ::CorrectL1XE50toZB*)0x0); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr Jburr_Template_Selector::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *Jburr_Template_Selector::Class_Name()
{
   return "Jburr_Template_Selector";
}

//______________________________________________________________________________
const char *Jburr_Template_Selector::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Jburr_Template_Selector*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int Jburr_Template_Selector::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::Jburr_Template_Selector*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *Jburr_Template_Selector::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Jburr_Template_Selector*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *Jburr_Template_Selector::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::Jburr_Template_Selector*)0x0)->GetClass(); }
   return fgIsA;
}

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
atomic_TClass_ptr CorrectL1XE30toZB::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *CorrectL1XE30toZB::Class_Name()
{
   return "CorrectL1XE30toZB";
}

//______________________________________________________________________________
const char *CorrectL1XE30toZB::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CorrectL1XE30toZB*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int CorrectL1XE30toZB::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CorrectL1XE30toZB*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *CorrectL1XE30toZB::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CorrectL1XE30toZB*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *CorrectL1XE30toZB::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CorrectL1XE30toZB*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr ComputeL1XE50toL1XE30Efficiency::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *ComputeL1XE50toL1XE30Efficiency::Class_Name()
{
   return "ComputeL1XE50toL1XE30Efficiency";
}

//______________________________________________________________________________
const char *ComputeL1XE50toL1XE30Efficiency::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::ComputeL1XE50toL1XE30Efficiency*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int ComputeL1XE50toL1XE30Efficiency::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::ComputeL1XE50toL1XE30Efficiency*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *ComputeL1XE50toL1XE30Efficiency::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::ComputeL1XE50toL1XE30Efficiency*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *ComputeL1XE50toL1XE30Efficiency::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::ComputeL1XE50toL1XE30Efficiency*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr CorrectL1XE50toZB::fgIsA(0);  // static to hold class pointer

//______________________________________________________________________________
const char *CorrectL1XE50toZB::Class_Name()
{
   return "CorrectL1XE50toZB";
}

//______________________________________________________________________________
const char *CorrectL1XE50toZB::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CorrectL1XE50toZB*)0x0)->GetImplFileName();
}

//______________________________________________________________________________
int CorrectL1XE50toZB::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::CorrectL1XE50toZB*)0x0)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *CorrectL1XE50toZB::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CorrectL1XE50toZB*)0x0)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *CorrectL1XE50toZB::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::CorrectL1XE50toZB*)0x0)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void Jburr_Template_Selector::Streamer(TBuffer &R__b)
{
   // Stream an object of class Jburr_Template_Selector.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(Jburr_Template_Selector::Class(),this);
   } else {
      R__b.WriteClassBuffer(Jburr_Template_Selector::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_Jburr_Template_Selector(void *p) {
      return  p ? new(p) ::Jburr_Template_Selector : new ::Jburr_Template_Selector;
   }
   static void *newArray_Jburr_Template_Selector(Long_t nElements, void *p) {
      return p ? new(p) ::Jburr_Template_Selector[nElements] : new ::Jburr_Template_Selector[nElements];
   }
   // Wrapper around operator delete
   static void delete_Jburr_Template_Selector(void *p) {
      delete ((::Jburr_Template_Selector*)p);
   }
   static void deleteArray_Jburr_Template_Selector(void *p) {
      delete [] ((::Jburr_Template_Selector*)p);
   }
   static void destruct_Jburr_Template_Selector(void *p) {
      typedef ::Jburr_Template_Selector current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::Jburr_Template_Selector

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

//______________________________________________________________________________
void CorrectL1XE30toZB::Streamer(TBuffer &R__b)
{
   // Stream an object of class CorrectL1XE30toZB.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(CorrectL1XE30toZB::Class(),this);
   } else {
      R__b.WriteClassBuffer(CorrectL1XE30toZB::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_CorrectL1XE30toZB(void *p) {
      return  p ? new(p) ::CorrectL1XE30toZB : new ::CorrectL1XE30toZB;
   }
   static void *newArray_CorrectL1XE30toZB(Long_t nElements, void *p) {
      return p ? new(p) ::CorrectL1XE30toZB[nElements] : new ::CorrectL1XE30toZB[nElements];
   }
   // Wrapper around operator delete
   static void delete_CorrectL1XE30toZB(void *p) {
      delete ((::CorrectL1XE30toZB*)p);
   }
   static void deleteArray_CorrectL1XE30toZB(void *p) {
      delete [] ((::CorrectL1XE30toZB*)p);
   }
   static void destruct_CorrectL1XE30toZB(void *p) {
      typedef ::CorrectL1XE30toZB current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::CorrectL1XE30toZB

//______________________________________________________________________________
void ComputeL1XE50toL1XE30Efficiency::Streamer(TBuffer &R__b)
{
   // Stream an object of class ComputeL1XE50toL1XE30Efficiency.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(ComputeL1XE50toL1XE30Efficiency::Class(),this);
   } else {
      R__b.WriteClassBuffer(ComputeL1XE50toL1XE30Efficiency::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_ComputeL1XE50toL1XE30Efficiency(void *p) {
      return  p ? new(p) ::ComputeL1XE50toL1XE30Efficiency : new ::ComputeL1XE50toL1XE30Efficiency;
   }
   static void *newArray_ComputeL1XE50toL1XE30Efficiency(Long_t nElements, void *p) {
      return p ? new(p) ::ComputeL1XE50toL1XE30Efficiency[nElements] : new ::ComputeL1XE50toL1XE30Efficiency[nElements];
   }
   // Wrapper around operator delete
   static void delete_ComputeL1XE50toL1XE30Efficiency(void *p) {
      delete ((::ComputeL1XE50toL1XE30Efficiency*)p);
   }
   static void deleteArray_ComputeL1XE50toL1XE30Efficiency(void *p) {
      delete [] ((::ComputeL1XE50toL1XE30Efficiency*)p);
   }
   static void destruct_ComputeL1XE50toL1XE30Efficiency(void *p) {
      typedef ::ComputeL1XE50toL1XE30Efficiency current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::ComputeL1XE50toL1XE30Efficiency

//______________________________________________________________________________
void CorrectL1XE50toZB::Streamer(TBuffer &R__b)
{
   // Stream an object of class CorrectL1XE50toZB.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(CorrectL1XE50toZB::Class(),this);
   } else {
      R__b.WriteClassBuffer(CorrectL1XE50toZB::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_CorrectL1XE50toZB(void *p) {
      return  p ? new(p) ::CorrectL1XE50toZB : new ::CorrectL1XE50toZB;
   }
   static void *newArray_CorrectL1XE50toZB(Long_t nElements, void *p) {
      return p ? new(p) ::CorrectL1XE50toZB[nElements] : new ::CorrectL1XE50toZB[nElements];
   }
   // Wrapper around operator delete
   static void delete_CorrectL1XE50toZB(void *p) {
      delete ((::CorrectL1XE50toZB*)p);
   }
   static void deleteArray_CorrectL1XE50toZB(void *p) {
      delete [] ((::CorrectL1XE50toZB*)p);
   }
   static void destruct_CorrectL1XE50toZB(void *p) {
      typedef ::CorrectL1XE50toZB current_t;
      ((current_t*)p)->~current_t();
   }
} // end of namespace ROOT for class ::CorrectL1XE50toZB

namespace {
  void TriggerDictionaryInitialization_MyDict_Impl() {
    static const char* headers[] = {
"../include/CorrectL1XE30toZB.h",
"../include/CorrectL1XE50toZB.h",
"../include/fitFunction.h",
"../include/ComputeL1XE30toZBEfficiency.h",
"../include/ComputeL1XE50toL1XE30Efficiency.h",
"../include/Jburr_Template_Selector.h",
0
    };
    static const char* includePaths[] = {
"/home/joseph/root_build/include",
"../include",
"/home/joseph/root_build/include",
"/home/joseph/ATLAS_Research/Mu_Analysis/lib/",
0
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "MyDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_Autoloading_Map;
class __attribute__((annotate("$clingAutoload$Jburr_Template_Selector.h")))  __attribute__((annotate("$clingAutoload$../include/CorrectL1XE30toZB.h")))  Jburr_Template_Selector;
class __attribute__((annotate("$clingAutoload$ComputeL1XE30toZBEfficiency.h")))  __attribute__((annotate("$clingAutoload$../include/CorrectL1XE30toZB.h")))  ComputeL1XE30toZBEfficiency;
class __attribute__((annotate("$clingAutoload$../include/CorrectL1XE30toZB.h")))  CorrectL1XE30toZB;
class __attribute__((annotate("$clingAutoload$ComputeL1XE50toL1XE30Efficiency.h")))  __attribute__((annotate("$clingAutoload$../include/CorrectL1XE50toZB.h")))  ComputeL1XE50toL1XE30Efficiency;
class __attribute__((annotate("$clingAutoload$../include/CorrectL1XE50toZB.h")))  CorrectL1XE50toZB;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "MyDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "../include/CorrectL1XE30toZB.h"
#include "../include/CorrectL1XE50toZB.h"
#include "../include/fitFunction.h"
#include "../include/ComputeL1XE30toZBEfficiency.h"
#include "../include/ComputeL1XE50toL1XE30Efficiency.h"
#include "../include/Jburr_Template_Selector.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
"ComputeL1XE30toZBEfficiency", payloadCode, "@",
"ComputeL1XE50toL1XE30Efficiency", payloadCode, "@",
"CorrectL1XE30toZB", payloadCode, "@",
"CorrectL1XE50toZB", payloadCode, "@",
"Jburr_Template_Selector", payloadCode, "@",
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
