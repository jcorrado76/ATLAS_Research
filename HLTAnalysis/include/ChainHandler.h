
#ifndef CHAINHANDLER_H
#define CHAINHANDLER_H


#include "TMath.h"
#include "TBranch.h"
#include "TTree.h"
#include "TH1F.h"
#include "TFile.h"
#include "TBits.h"
#include "TString.h"
#include <vector>
#include <string>




namespace treeReaderSpace
{
    struct BranchType
    {
        enum value_type
        {
            CLASS,
            BUILTIN,
            NOT_SET,

            static_size
        };
    };

    template <typename T>
    class Handle
    {
        public:

            // construct:
            explicit Handle(const std::string& branch_name);

            // destroy:
            virtual ~Handle() {}

            // set the branch's entry
            void GetEntry(const unsigned int entry);

            // initialize the handle's branches
            void Init(TTree& tree);

            // is the branch already loaded
            bool IsLoaded() const;

            // load the branch
            void Load();

            // clear the branch
            void Clear();

            // get the value
            const T& get();

        protected:

            // set the branch type private member (based on the TBranch)
            void SetBranchType(const std::string& branch_class);

            // members:
            bool                   m_is_loaded;
            unsigned int           m_entry;
            std::string            m_branch_name;
            T*                     m_object_ptr;
            T                      m_object;
            BranchType::value_type m_branch_type;

            // the TTree owns the branch (this is only a reference pointer)
            TBranch*     m_branch;

        private:
            // no default constructor
            Handle() {}
    };

    template <typename T>
    /*explicit*/ Handle<T>::Handle(const std::string& branch_name)
        : m_is_loaded(false)
        , m_entry(0)
        , m_branch_name(branch_name)
        , m_object_ptr(NULL)
        , m_object()
        , m_branch_type(BranchType::NOT_SET)
        , m_branch(NULL)
    {
    }

    template <typename T>
    void Handle<T>::GetEntry(const unsigned int entry)
    {
        Clear();
        m_entry = entry;
    }

    template <typename T>
    bool Handle<T>::IsLoaded() const
    {
        return m_is_loaded;
    }

    template <typename T>
    void Handle<T>::Clear()
    {
        m_is_loaded = false;
    }

    template <typename T>
    void Handle<T>::Load()
    {
        if (m_branch)
        {
            m_branch->GetEntry(m_entry);
            m_is_loaded = true;
        }
        else
        {
            throw std::runtime_error("[ChainHandler] ERROR: branch " + m_branch_name + " does not exist!");
        }
    }

    template <typename T>
    void Handle<T>::SetBranchType(const std::string& branch_class)
    {
        if (branch_class.find("edm::Wrapper")!=std::string::npos)
        {
            m_branch_type = BranchType::BUILTIN;
        }
        else if
        (
            branch_class.find("/B")!=std::string::npos || // char
            branch_class.find("/b")!=std::string::npos || // unsigned char
            branch_class.find("/C")!=std::string::npos || // char
            branch_class.find("/c")!=std::string::npos || // unsigned char
            branch_class.find("/S")!=std::string::npos || // short
            branch_class.find("/s")!=std::string::npos || // unsigned short
            branch_class.find("/I")!=std::string::npos || // int
            branch_class.find("/i")!=std::string::npos || // unsigned int
            branch_class.find("/F")!=std::string::npos || // float
            branch_class.find("/D")!=std::string::npos || // double
            branch_class.find("/L")!=std::string::npos || // long
            branch_class.find("/l")!=std::string::npos || // unsigned long
            branch_class.find("/O")!=std::string::npos    // bool
        )
        {
            m_branch_type = BranchType::BUILTIN;
        }
        else
        {
            m_branch_type = BranchType::CLASS;
        }
    }

    template <typename T>
    void Handle<T>::Init(TTree& tree)
    {
        // no protection if the branch pointer is NULL
        // (so you can use this if the branch doesn't exist
        // as long as you don't call it).
        m_branch = tree.GetBranch(m_branch_name.c_str());
        if (m_branch)
        {
            if (m_branch_type == BranchType::NOT_SET)
            {
                std::string branch_class = m_branch->GetClassName();
                if (branch_class.empty())  // built in types don't have a ClassName --> using title
                {
                    branch_class = m_branch->GetTitle();
                }
                SetBranchType(branch_class);
            }
            switch (m_branch_type)
            {
                case BranchType::CLASS  : m_branch->SetAddress(&m_object_ptr); break;
                case BranchType::BUILTIN: m_branch->SetAddress(&m_object)    ; break;
                default: throw std::runtime_error("[ChainHandler] ERROR: branch type not supported!");
            }
        }
    }

    template <typename T>
    const T& Handle<T>::get()
    {
        if (not IsLoaded())
        {
            Load();
        }
        switch (m_branch_type)
        {
            case BranchType::CLASS  : return *m_object_ptr;
            case BranchType::BUILTIN: return m_object;
            default: throw std::runtime_error("[ChainHandler] ERROR: branch type not supported!");
        }
    }


} // namespace treeReaderSpace



class ChainHandler
{
    public:
        ChainHandler();

        // methods:
        void Init(TTree* const tree);
        void Init(TTree& tree);
        void GetEntry(const unsigned int entry);
		void LoadAllBranches();


        // branch accessors
        const unsigned int& run();
        const unsigned int& ls();
        const unsigned int& event();
        const Int_t passrndm();
        const Float_t algA();
        const Float_t algB();
        const Float_t metl1();
        const Float_t passnoalgL1XE10();
        const Float_t passnoalgL1XE30();
        const Float_t passnoalgL1XE40();
        const Float_t passnoalgL1XE45();
        const Float_t thresh_actint();
        const Float_t passmuon();
        const Float_t passmuvarmed();
        const Float_t cleanCutsFlag();
        const Float_t recalBrokeFlag();
        const Float_t metoffrecal();
        const Float_t mexoffrecal();
        const Float_t meyoffrecal();
        const Float_t metoffrecalmuon();
        const Float_t mexoffrecalmuon();
        const Float_t meyoffrecalmuon();
        const Float_t metrefmuon();
        const Float_t mexrefmuon();
        const Float_t meyrefmuon();
        const Float_t algAmuon();
        const Float_t algBmuon();
        const Float_t metl1muon();
        const Float_t actintmuon();


    private:

        // handles
        treeReaderSpace ::Handle< unsigned int > run_handle;
        treeReaderSpace ::Handle< unsigned int > ls_handle;
        treeReaderSpace ::Handle< unsigned int > event_handle;
        treeReaderSpace ::Handle< Int_t        > passrndm_handle;
        treeReaderSpace ::Handle< Float_t      > algA_handle;
        treeReaderSpace ::Handle< Float_t      > algB_handle;
        treeReaderSpace ::Handle< Float_t      > metl1_handle;
        treeReaderSpace ::Handle< Float_t      > passnoalgL1XE10_handle;
        treeReaderSpace ::Handle< Float_t      > passnoalgL1XE30_handle;
        treeReaderSpace ::Handle< Float_t      > passnoalgL1XE40_handle;
        treeReaderSpace ::Handle< Float_t      > passnoalgL1XE45_handle;
        treeReaderSpace ::Handle< Float_t      > thresh_actint_handle;
        treeReaderSpace ::Handle< Float_t      > passmuon_handle;
        treeReaderSpace ::Handle< Float_t      > passmuvarmed_handle;
        treeReaderSpace ::Handle< Float_t      > cleanCutsFlag_handle;
        treeReaderSpace ::Handle< Float_t      > recalBrokeFlag_handle;
        treeReaderSpace ::Handle< Float_t      > metoffrecal_handle;
        treeReaderSpace ::Handle< Float_t      > mexoffrecal_handle;
        treeReaderSpace ::Handle< Float_t      > meyoffrecal_handle;
        treeReaderSpace ::Handle< Float_t      > metoffrecalmuon_handle;
        treeReaderSpace ::Handle< Float_t      > mexoffrecalmuon_handle;
        treeReaderSpace ::Handle< Float_t      > meyoffrecalmuon_handle;
        treeReaderSpace ::Handle< Float_t      > metrefmuon_handle;
        treeReaderSpace ::Handle< Float_t      > mexrefmuon_handle;
        treeReaderSpace ::Handle< Float_t      > meyrefmuon_handle;
        treeReaderSpace ::Handle< Float_t      > algAmuon_handle;
        treeReaderSpace ::Handle< Float_t      > algBmuon_handle;
        treeReaderSpace ::Handle< Float_t      > metl1muon_handle;
        treeReaderSpace ::Handle< Float_t      > actintmuon_handle;
};


namespace treeReaderSpace
{
    const unsigned int& run();
    const unsigned int& ls();
    const unsigned int& event();
    const Int_t get_passrndm();
    const Float_t get_algA();
    const Float_t get_algB();
    const Float_t get_metl1();
    const Float_t get_passnoalgL1XE10();
    const Float_t get_passnoalgL1XE30();
    const Float_t get_passnoalgL1XE40();
    const Float_t get_passnoalgL1XE45();
    const Float_t get_thresh_actint();
    const Float_t get_passmuon();
    const Float_t get_passmuvarmed();
    const Float_t get_cleanCutsFlag();
    const Float_t get_recalBrokeFlag();
    const Float_t get_metoffrecal();
    const Float_t get_mexoffrecal();
    const Float_t get_meyoffrecal();
    const Float_t get_metoffrecalmuon();
    const Float_t get_mexoffrecalmuon();
    const Float_t get_meyoffrecalmuon();
    const Float_t get_metrefmuon();
    const Float_t get_mexrefmuon();
    const Float_t get_meyrefmuon();
    const Float_t get_algAmuon();
    const Float_t get_algBmuon();
    const Float_t get_metl1muon();
    const Float_t get_actintmuon();

} // namespace treeReaderSpace


#ifndef __CINT__
extern ChainHandler ChainHandler_obj;
#endif


#endif // CHAINHANDLER_H
