#ifndef TREEHANDLER_H
#define TREEHANDLER_H
#include"userInfo.h"
namespace TTreeReaderSpace{
    struct BranchType
    {
        //specify allowed values for a BranchType; you can say 'BranchType MyBranchType = CLASS'
        enum value_type { CLASS, BUILTIN, NOT_SET, static_size };
    }; 



    template <typename T>
    class BranchHandle
    {
        public:
            //constructor // prevent implicit conversion 
            explicit BranchHandle(const std::string& branch_name);
            //destructor  // can be overloaded 
            virtual ~BranchHandle(){}
            //set the branch's entry 
            void GetEntry(const unsigned int entry);
            //initialize the handle's branches using a TTree
            void Init(TTree& tree);
            //is the branch already loaded
            bool IsLoaded() const;
            //load the branch
            void Load();
            //clear the branch
            void Clear();
            //get the value of branch
            const T& Get();
            
        //private, except can be accessed by derived classes
        protected:
            //set the branch type private member (based on TBranch)
            void SetBranchType(const std::string& Branch_Class);

            //members
            bool                   m_is_loaded;
            unsigned int           m_entry;
            std::string            m_branch_name;
            T*                     m_object_ptr;
            T                      m_object;
            BranchType::value_type m_branch_type;
            //the TTree owns the branch (this is a reference pointer) 
            TBranch*               m_branch ;

        private:
            //no default constructor
            Handle() {}
    };


    //constructor for Handle template 
    template <typename T>
    Handle<T>::Handle(const std::string& branch_name)
        : m_is_loaded(false),
          m_entry(0),
          m_branch_name(branch_name),
          m_object_ptr(NULL),
          m_object(),
          m_branch_type(BranchType::NOT_SET),
          m_branch(NULL)
    {}

    template <typename T>
    void Handle<T>::GetEntry(const unsigned int entry)
    {
        Clear();
        m_entry = entry;
    }

    template <typename T>
    void Handle<T>::GetIsLoaded() const
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
            throw std::runtime_error("[TreeHandler] ERROR: Branch " + branch_name + " does not exist!");
        }
    }

    template <typename T>
    void Handle<T>::SetBranchType(const std::string& branch_class)
    {
        if (branch_class.find("edm::Wrapper") != std::string::npos)
        {
            m__branch_type = BranchType::BUILTIN;
        }
        else if 
        (
            branch_class.find("/B") != std::string::npos || //char
            branch_class.find("/b") != std::string::npos || //unsigned char 
            branch_class.find("/C") != std::string::npos || //char 
            branch_class.find("/c") != std::string::npos || //unsigned char 
            branch_class.find("/S") != std::string::npos || //short 
            branch_class.find("/s") != std::string::npos || //unsigned short
            branch_class.find("/I") != std::string::npos || //int
            branch_class.find("/i") != std::string::npos || //unsigned int 
            branch_class.find("/F") != std::string::npos || //float
            branch_class.find("/D") != std::string::npos || //double 
            branch_class.find("/L") != std::string::npos || //long 
            branch_class.find("/l") != std::string::npos || //unsigned long 
            branch_class.find("/o") != std::string::npos || //bool
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
        //no protection if  branch pointer is NULL
        //you can use this when branch doesn't exist, just don't call it 
        m_branch = tree.GetBranch(m_branch_name.c_str());
        if (m_branch)
        {
            if (m_branch_type == BranchType::NOT_SET)
            {
                std::string branch_class = m_branch->GetClassName();
                if (branch_class.empty()) // built in class types don't have ClassNames --> so we'll use title 
                {
                    branch_class = m_branch->GetTitle();
                }
                SetBranchType(branch_class);
            }
            switch(m_branch_type)
            {
                case BranchType::CLASS : m_branch->SetAddress(&m_object_ptr); break;
                case BranchType::BUILTIN : m_branch->SetAddress(&m_object); break;
                default: throw std::runtime_error("[TreeHandler] ERROR: Branch type not supported");
            }
        }
    }

    template <typename T>
    const T& Handle<T>::Get()
    {
        if (not IsLoaded())
        {
            Load();
        }
        switch (m_branch_type)
        {
            case BranchType::CLASS : return *m_object_ptr;
            case BranchType::BUILTIN : return m_object;
            default : throw std::runtime_error("[Treehandler] ERROR: Branch type not supported");
        }
    }
}; //TTREEREADER NAMESPACE


class TreeHandler
{
    public:
        TreeHandler(const userInfo* parameters );

        void Init(TTree* const tree);
        void Init(TTree& tree);
        void GetEntry(const unsigned int entry);
        void LoadAllBranches();


        const unsigned int& run();
        const unsigned int& ls();
        const unsigned int& event();
        const Int_t passrndm();
        const Float_t AlgA();
        const Float_t AlgB();
        const Float_t MetL1();
        const Float_t PassnoalgL1XE10();
        const Float_t PassnoalgL1XE30();
        const Float_t PassnoalgL1XE40();
        const Float_t PassnoalgL1XE45();
        const Float_t Actint();
        const Float_t Passmuon();
        const Float_t Passmuvarmed();
        const Float_t CleanCutsFlag();
        const Float_t RecalBrokeFlag();
        const Float_t metoffrecal();
        const Float_t mexoffrecal();
        const Float_t meyoffrecal();
        const Float_t metoffrecalmuon();
        const Float_t mexoffrecalmuon();
        const Float_t meyoffreclamuon();
        const Float_t metrefmuon();
        const Float_t mexrefmuon();
        const Float_t meyrefmuon();

 private:

        // handles
        TTreeReaderSpace ::Handle< unsigned int > run_handle;
        TTreeReaderSpace ::Handle< unsigned int > ls_handle;
        TTreeReaderSpace ::Handle< unsigned int > event_handle;
        TTreeReaderSpace ::Handle< Int_t        > passrndm_handle;
        TTreeReaderSpace ::Handle< Float_t      > algA_handle;
        TTreeReaderSpace ::Handle< Float_t      > algB_handle;
        TTreeReaderSpace ::Handle< Float_t      > metl1_handle;
        TTreeReaderSpace ::Handle< Float_t      > passnoalgL1XE10_handle;
        TTreeReaderSpace ::Handle< Float_t      > passnoalgL1XE30_handle;
        TTreeReaderSpace ::Handle< Float_t      > passnoalgL1XE40_handle;
        TTreeReaderSpace ::Handle< Float_t      > passnoalgL1XE45_handle;
        TTreeReaderSpace ::Handle< Float_t      > actint_handle;
        TTreeReaderSpace ::Handle< Float_t      > passmuon_handle;
        TTreeReaderSpace ::Handle< Float_t      > passmuvarmed_handle;
        TTreeReaderSpace ::Handle< Float_t      > cleanCutsFlag_handle;
        TTreeReaderSpace ::Handle< Float_t      > recalBrokeFlag_handle;
        TTreeReaderSpace ::Handle< Float_t      > metoffrecal_handle;
        TTreeReaderSpace ::Handle< Float_t      > mexoffrecal_handle;
        TTreeReaderSpace ::Handle< Float_t      > meyoffrecal_handle;
        TTreeReaderSpace ::Handle< Float_t      > metoffrecalmuon_handle;
        TTreeReaderSpace ::Handle< Float_t      > mexoffrecalmuon_handle;
        TTreeReaderSpace ::Handle< Float_t      > meyoffrecalmuon_handle;
        TTreeReaderSpace ::Handle< Float_t      > metrefmuon_handle;
        TTreeReaderSpace ::Handle< Float_t      > mexrefmuon_handle;
        TTreeReaderSpace ::Handle< Float_t      > meyrefmuon_handle;
};


namespace treeReaderSpace
{
    const unsigned int& Run();
    const unsigned int& Ls();
    const unsigned int& Event();
    const Int_t Get_passrndm();
    const Float_t Get_algA();
    const Float_t Get_algB();
    const Float_t Get_metl1();
    const Float_t Get_passnoalgL1XE10();
    const Float_t Get_passnoalgL1XE30();
    const Float_t Get_passnoalgL1XE40();
    const Float_t Get_passnoalgL1XE45();
    const Float_t Get_actint();
    const Float_t Get_passmuon();
    const Float_t Get_passmuvarmed();
    const Float_t Get_cleanCutsFlag();
    const Float_t Get_recalBrokeFlag();
    const Float_t Get_metoffrecal();
    const Float_t Get_mexoffrecal();
    const Float_t Get_meyoffrecal();
    const Float_t Get_metoffrecalmuon();
    const Float_t Get_mexoffrecalmuon();
    const Float_t Get_meyoffrecalmuon();
    const Float_t Get_metrefmuon();
    const Float_t Get_mexrefmuon();
    const Float_t Get_meyrefmuon();

} // namespace treeReaderSpace

};




#endif
