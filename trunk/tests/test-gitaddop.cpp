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

TEST(Execute_UntrackedFileWithinGit_IssuesGitAdd)
{
    class MockTreeItem : public VcsTreeItem
    {
        public:
            MockTreeItem() :
                VcsTreeItem(_("/src/gitroot/untracked"), Item_Untracked) {}

            virtual void VisualiseState() const {}
    };

    MockExecutor exec;
    IVersionControlSystem* vcs = new git(_("/src/gitroot/test.cbp"), exec);
    std::vector<VcsTreeItem*> prjFiles;

    MockTreeItem ti;
    prjFiles.push_back(&ti);

    vcs->AddOp.execute(prjFiles);

    CHECK_EQUAL(0, exec.m_LastCmd.compare(_("git add untracked")));
}

TEST(Execute_UntrackedFileOutsideGit_NoCmdsIssued)
{
    class MockTreeItem : public VcsTreeItem
    {
        public:
            MockTreeItem() :
                VcsTreeItem(_("/src/otherroot/untracked"), Item_Untracked) {}

            virtual void VisualiseState() const {}
    };

    MockExecutor exec;
    IVersionControlSystem* vcs = new git(_("/src/gitroot/test.cbp"), exec);
    std::vector<VcsTreeItem*> prjFiles;

    MockTreeItem ti;
    prjFiles.push_back(&ti);

    vcs->AddOp.execute(prjFiles);

    CHECK_EQUAL(true, exec.m_LastCmd.IsEmpty());
}

TEST(Execute_TrackedFile_NoCmdsIssued)
{
    class MockTreeItem : public VcsTreeItem
    {
        public:
            MockTreeItem() :
                VcsTreeItem(_("/src/gitroot/added"), Item_Untracked) {}

            virtual void VisualiseState() const {}
    };

    MockExecutor exec;
    IVersionControlSystem* vcs = new git(_("/src/gitroot/test.cbp"), exec);
    std::vector<VcsTreeItem*> prjFiles;

    MockTreeItem ti;
    ti.SetState(Item_UpToDate);
    prjFiles.push_back(&ti);

    vcs->AddOp.execute(prjFiles);

    CHECK_EQUAL(true, exec.m_LastCmd.IsEmpty());
}

}
