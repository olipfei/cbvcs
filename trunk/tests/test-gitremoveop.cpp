#include <UnitTest++/UnitTest++.h>
#include <git.h>
#include <VcsTreeItem.h>
#include <icommandexecuter.h>

namespace
{
class MockExecutor : public ICommandExecuter
{
    public:
        mutable wxString m_LastCmd;

        virtual bool execute(const wxString& shellCommand,
                             wxArrayString& outCapture,
                             wxArrayString& errCapture) const
        {
            m_LastCmd = shellCommand;
            return true;
        }

        virtual bool FileExists(const wxString& filePath) const { return true; }
        virtual void pushd(const wxString& ) {};
        virtual void popd() {};
};

TEST(Execute_UpToDateFileWithinGit_IssuesGitRm)
{
    class MockTreeItem : public VcsTreeItem
    {
        public:
            MockTreeItem() :
                VcsTreeItem(_("/src/gitroot/uptodate"), Item_UpToDate) {}

            virtual void VisualiseState() const {}
    };

    MockExecutor exec;
    IVersionControlSystem* vcs = new git(_("/src/gitroot/test.cbp"), exec);
    std::vector<VcsTreeItem*> prjFiles;

    MockTreeItem ti;
    prjFiles.push_back(&ti);

    vcs->RemoveOp.execute(prjFiles);

    CHECK_EQUAL(0, exec.m_LastCmd.compare(_("git rm uptodate")));
}

TEST(Execute_MissingFileWithinGit_IssuesGitRm)
{
    class MockTreeItem : public VcsTreeItem
    {
        public:
            MockTreeItem() :
                VcsTreeItem(_("/src/gitroot/missing"), Item_Missing) {}

            virtual void VisualiseState() const {}
    };

    MockExecutor exec;
    IVersionControlSystem* vcs = new git(_("/src/gitroot/test.cbp"), exec);
    std::vector<VcsTreeItem*> prjFiles;

    MockTreeItem ti;
    prjFiles.push_back(&ti);

    vcs->RemoveOp.execute(prjFiles);

    CHECK_EQUAL(0, exec.m_LastCmd.compare(_("git rm missing")));
}

TEST(Execute_AddedFileWithinGit_IssuesGitRmCached)
{
    class MockTreeItem : public VcsTreeItem
    {
        public:
            MockTreeItem() :
                VcsTreeItem(_("/src/gitroot/added"), Item_Added) {}

            virtual void VisualiseState() const {}
    };

    MockExecutor exec;
    IVersionControlSystem* vcs = new git(_("/src/gitroot/test.cbp"), exec);
    std::vector<VcsTreeItem*> prjFiles;

    MockTreeItem ti;
    prjFiles.push_back(&ti);

    vcs->RemoveOp.execute(prjFiles);

    CHECK_EQUAL(0, exec.m_LastCmd.compare(_("git rm --cached added")));
}

TEST(Execute_ModifiedFileWithinGit_IssuesGitRmCached)
{
    class MockTreeItem : public VcsTreeItem
    {
        public:
            MockTreeItem() :
                VcsTreeItem(_("/src/gitroot/modified"), Item_Modified) {}

            virtual void VisualiseState() const {}
    };

    MockExecutor exec;
    IVersionControlSystem* vcs = new git(_("/src/gitroot/test.cbp"), exec);
    std::vector<VcsTreeItem*> prjFiles;

    MockTreeItem ti;
    prjFiles.push_back(&ti);

    vcs->RemoveOp.execute(prjFiles);

    CHECK_EQUAL(0, exec.m_LastCmd.compare(_("git rm --cached modified")));
}

TEST(Execute_RemovedFileWithinGit_NoCommandsIssued)
{
    class MockTreeItem : public VcsTreeItem
    {
        public:
            MockTreeItem() :
                VcsTreeItem(_("/src/gitroot/removed"), Item_Removed) {}

            virtual void VisualiseState() const {}
    };

    MockExecutor exec;
    IVersionControlSystem* vcs = new git(_("/src/gitroot/test.cbp"), exec);
    std::vector<VcsTreeItem*> prjFiles;

    MockTreeItem ti;
    prjFiles.push_back(&ti);

    vcs->RemoveOp.execute(prjFiles);

    CHECK_EQUAL(true, exec.m_LastCmd.IsEmpty());
}

}
