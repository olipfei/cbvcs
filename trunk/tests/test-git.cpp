#include <UnitTest++/UnitTest++.h>
#include <git.h>
#include <VcsTreeItem.h>
#include <icommandexecuter.h>

namespace
{
const wxString ProjectName = _("src/gitroot/projroot/project.cbp");
const wxString VcsRoot(_("src/gitroot"));

class GitRootTrueExecutor : public ICommandExecuter
{
    public:
        virtual bool execute(const wxString& shellCommand,
                             wxArrayString& outCapture,
                             wxArrayString& errCapture) const
        {
            if(!shellCommand.Cmp(_("git rev-parse --show-toplevel")))
            {
                outCapture.Add(_("src/gitroot"));
            }
            else
            {
                return false;
            }
            return true;
        }

        virtual bool FileExists(const wxString& filePath) const { return true; }
        virtual void pushd(const wxString& ) {};
        virtual void popd() {};
};

TEST(IsGitRoot_ProjectFileWithinGit_ReturnsTrue)
{
    GitRootTrueExecutor exec;

    CHECK_EQUAL(true, git::IsGitRepo(ProjectName, exec));
}

}
