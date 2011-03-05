#include <UnitTest++/UnitTest++.h>
#include <git.h>
#include <VcsTreeItem.h>
#include <icommandexecuter.h>

namespace
{

TEST(UpdateOp_FileListNonEmpty_IssuesShellCommand)
{
    class MockTreeItem : public VcsTreeItem
    {
        public:
            MockTreeItem() :
                VcsTreeItem(_("MockItem"), Item_Untracked) {}

            virtual void VisualiseState() const {}
    };

    class MockExecutor : public ICommandExecuter
    {
    public:
        mutable wxString m_LastCmd;

        virtual bool execute(const wxString& shellCommand,
                             wxArrayString& outCapture,
                             wxArrayString&  errCapture) const
        {
            m_LastCmd = shellCommand;
            return true;
        }

        virtual bool FileExists(const wxString& filePath) const {return false;}
        virtual void pushd(const wxString& shellCommand) {};
        virtual void popd() {};
    };

    MockExecutor exec;
    IVersionControlSystem* vcs = new git(_("/src/gitroot/test.cbp"), exec);
    std::vector<VcsTreeItem*> prjFiles;

    MockTreeItem ti;
    prjFiles.push_back(&ti);

    vcs->UpdateOp.execute(prjFiles);

    CHECK_EQUAL(0, exec.m_LastCmd.compare(_("git status --porcelain")));
}

TEST(UpdateOp_ModifiedFile_FileStatusUpdated)
{
    class MockTreeItem : public VcsTreeItem
    {
        public:
            MockTreeItem() :
                VcsTreeItem(_("/src/gitroot/modified"), Item_Untracked) {}

            virtual void VisualiseState() const {}
    };

    class MockExecutor : public ICommandExecuter
    {
        public:
            virtual bool execute(const wxString& shellCommand,
                                 wxArrayString& outCapture,
                                 wxArrayString&  errCapture) const
            {
                outCapture.Add(_(" M modified"));
                return true;
            }
            virtual bool FileExists(const wxString& filePath) const {return false;}
            virtual void pushd(const wxString& shellCommand) {};
            virtual void popd() {};
    };

    MockExecutor exec;
    IVersionControlSystem* vcs = new git(_("/src/gitroot/test.cbp"), exec);
    std::vector<VcsTreeItem*> prjFiles;

    MockTreeItem ti;
    prjFiles.push_back(&ti);

    vcs->UpdateOp.execute(prjFiles);

    CHECK_EQUAL(Item_Modified, ti.GetState());
}

TEST(UpdateOp_DeletedFile_FileStatusUpdated)
{
    class MockTreeItem : public VcsTreeItem
    {
        public:
            MockTreeItem() :
                VcsTreeItem(_("/src/gitroot/deleted"), Item_Untracked) {}

            virtual void VisualiseState() const {}
    };

    class MockExecutor : public ICommandExecuter
    {
        public:
            virtual bool execute(const wxString& shellCommand,
                                 wxArrayString& outCapture,
                                 wxArrayString&  errCapture) const
            {
                outCapture.Add(_("D  deleted"));
                return true;
            }
            virtual bool FileExists(const wxString& filePath) const {return false;}
            virtual void pushd(const wxString& shellCommand) {};
            virtual void popd() {};
    };

    MockExecutor exec;
    IVersionControlSystem* vcs = new git(_("/src/gitroot/test.cbp"), exec);
    std::vector<VcsTreeItem*> prjFiles;

    MockTreeItem ti;
    prjFiles.push_back(&ti);

    vcs->UpdateOp.execute(prjFiles);

    CHECK_EQUAL(Item_Removed, ti.GetState());
}

TEST(UpdateOp_AddedFile_FileStatusUpdated)
{
    class MockTreeItem : public VcsTreeItem
    {
        public:
            MockTreeItem() :
                VcsTreeItem(_("/src/gitroot/added"), Item_Untracked) {}

            virtual void VisualiseState() const {}
    };

    class MockExecutor : public ICommandExecuter
    {
        public:
            virtual bool execute(const wxString& shellCommand,
                                 wxArrayString& outCapture,
                                 wxArrayString&  errCapture) const
            {
                outCapture.Add(_("A  added"));
                return true;
            }

            virtual bool FileExists(const wxString& filePath) const {return false;}
            virtual void pushd(const wxString& shellCommand) {};
            virtual void popd() {};
   };

    MockExecutor exec;
    IVersionControlSystem* vcs = new git(_("/src/gitroot/test.cbp"), exec);
    std::vector<VcsTreeItem*> prjFiles;

    MockTreeItem ti;
    prjFiles.push_back(&ti);

    vcs->UpdateOp.execute(prjFiles);

    CHECK_EQUAL(Item_Added, ti.GetState());
}

TEST(UpdateOp_MissingFile_FileStatusUpdated)
{
    class MockTreeItem : public VcsTreeItem
    {
        public:
            MockTreeItem() :
                VcsTreeItem(_("/src/gitroot/missing"), Item_Untracked) {}

            virtual void VisualiseState() const {}
    };

    class MockExecutor : public ICommandExecuter
    {
        public:
            virtual bool execute(const wxString& shellCommand,
                                 wxArrayString& outCapture,
                                 wxArrayString&  errCapture) const
            {
                outCapture.Add(_(" D missing"));
                return true;
            }

            virtual bool FileExists(const wxString& filePath) const {return false;}
            virtual void pushd(const wxString& shellCommand) {};
            virtual void popd() {};
    };

    MockExecutor exec;
    IVersionControlSystem* vcs = new git(_("/src/gitroot/test.cbp"), exec);
    std::vector<VcsTreeItem*> prjFiles;

    MockTreeItem ti;
    prjFiles.push_back(&ti);

    vcs->UpdateOp.execute(prjFiles);

    CHECK_EQUAL(Item_Missing, ti.GetState());
}

TEST(UpdateOp_UntrackedFile_FileStatusUpdated)
{
    class MockTreeItem : public VcsTreeItem
    {
        public:
            MockTreeItem() :
                VcsTreeItem(_("/src/gitroot/untracked"), Item_Untracked) {}

            virtual void VisualiseState() const {}
    };

    class MockExecutor : public ICommandExecuter
    {
        public:
            virtual bool execute(const wxString& shellCommand,
                                 wxArrayString& outCapture,
                                 wxArrayString&  errCapture) const
            {
                outCapture.Add(_("?? untracked"));
                return true;
            }

            virtual bool FileExists(const wxString& filePath) const {return false;}
            virtual void pushd(const wxString& shellCommand) {};
            virtual void popd() {};
    };

    MockExecutor exec;
    IVersionControlSystem* vcs = new git(_("/src/gitroot/test.cbp"), exec);
    std::vector<VcsTreeItem*> prjFiles;

    MockTreeItem ti;
    prjFiles.push_back(&ti);

    vcs->UpdateOp.execute(prjFiles);

    CHECK_EQUAL(Item_Untracked, ti.GetState());
}

TEST(UpdateOp_UntrackedDirectory_FileStatusUpdated)
{
    class MockTreeItem : public VcsTreeItem
    {
        public:
            MockTreeItem() :
                VcsTreeItem(_("/src/gitroot/subdir/file"), Item_Untracked) {}

            virtual void VisualiseState() const {}
    };

    class MockExecutor : public ICommandExecuter
    {
        public:
            virtual bool execute(const wxString& shellCommand,
                                 wxArrayString& outCapture,
                                 wxArrayString&  errCapture) const
            {
                outCapture.Add(_("?? subdir/"));
                return true;
            }

            virtual bool FileExists(const wxString& filePath) const {return false;}
            virtual void pushd(const wxString& shellCommand) {};
            virtual void popd() {};
    };

    MockExecutor exec;
    IVersionControlSystem* vcs = new git(_("/src/gitroot/test.cbp"), exec);
    std::vector<VcsTreeItem*> prjFiles;

    MockTreeItem ti;
    prjFiles.push_back(&ti);

    vcs->UpdateOp.execute(prjFiles);

    CHECK_EQUAL(Item_Untracked, ti.GetState());
}

TEST(UpdateOp_FileUpToDate_FileStatusUpdated)
{
    class MockTreeItem : public VcsTreeItem
    {
        public:
            MockTreeItem() :
                VcsTreeItem(_("/src/gitroot/uptodate"), Item_Untracked) {}

            virtual void VisualiseState() const {}
    };

    class MockExecutor : public ICommandExecuter
    {
        public:
            virtual bool execute(const wxString& shellCommand,
                                 wxArrayString& outCapture,
                                 wxArrayString&  errCapture) const
            {
                return true;
            }

            virtual bool FileExists(const wxString& filePath) const { return true; }
            virtual void pushd(const wxString& shellCommand) {};
            virtual void popd() {};
    };

    MockExecutor exec;
    IVersionControlSystem* vcs = new git(_("/src/gitroot/test.cbp"), exec);
    std::vector<VcsTreeItem*> prjFiles;

    MockTreeItem ti;
    prjFiles.push_back(&ti);

    vcs->UpdateOp.execute(prjFiles);

    CHECK_EQUAL(Item_UpToDate, ti.GetState());
}

TEST(UpdateOp_RenamedFileInProject_FileStatusUpdated)
{
    class MockTreeItem : public VcsTreeItem
    {
        public:
            MockTreeItem() :
                VcsTreeItem(_("/src/gitroot/renamed"), Item_Untracked) {}

            virtual void VisualiseState() const {}
    };

    class MockExecutor : public ICommandExecuter
    {
        public:
            virtual bool execute(const wxString& shellCommand,
                                 wxArrayString& outCapture,
                                 wxArrayString&  errCapture) const
            {
                outCapture.Add(_("R  renamad -> renamed"));
                return true;
            }

            virtual bool FileExists(const wxString& filePath) const { return true; }
            virtual void pushd(const wxString& shellCommand) {};
            virtual void popd() {};
    };

    MockExecutor exec;
    IVersionControlSystem* vcs = new git(_("/src/gitroot/test.cbp"), exec);
    std::vector<VcsTreeItem*> prjFiles;

    MockTreeItem ti;
    prjFiles.push_back(&ti);

    vcs->UpdateOp.execute(prjFiles);

    CHECK_EQUAL(Item_Added, ti.GetState());
}

}
