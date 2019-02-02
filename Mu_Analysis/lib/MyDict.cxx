// Do NOT change. Changes will be lost next time file is generated
// //do not change
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
#include "../include/ComputeL1XE30toZBEfficiency.h"
#include "../include/ComputeL1XE50toL1XE30Efficiency.h"
#include "../include/Jburr_Template_Selector.h"

// Header files passed via #pragma extra_include

namespace {
  void TriggerDictionaryInitialization_MyDict_Impl() {
    static const char* headers[] = {
"../include/CorrectL1XE30toZB.h",
"../include/CorrectL1XE50toZB.h",
"../include/ComputeL1XE30toZBEfficiency.h",
"../include/ComputeL1XE50toL1XE30Efficiency.h",
"../include/Jburr_Template_Selector.h",
0
    };
    static const char* includePaths[] = {
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
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "MyDict dictionary payload"

#ifndef G__VECTOR_HAS_CLASS_ITERATOR
  #define G__VECTOR_HAS_CLASS_ITERATOR 1
#endif

#define _BACKWARD_BACKWARD_WARNING_H
#include "../include/CorrectL1XE30toZB.h"
#include "../include/CorrectL1XE50toZB.h"
#include "../include/ComputeL1XE30toZBEfficiency.h"
#include "../include/ComputeL1XE50toL1XE30Efficiency.h"
#include "../include/Jburr_Template_Selector.h"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[]={
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
