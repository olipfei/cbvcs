/***********************************************************************
 * AUTHOR: Dushara Jayasinghe <dushara>
 *   FILE: .//git.cpp
 *   DATE: Sun Feb 20 18:10:30 2011
 *  DESCR:
 ***********************************************************************/
#include "git.h"
#include "icommandexecuter.h"

extern const wxString GitRootDir;
const wxString GitRootDir(L"/src/gitroot");

/***********************************************************************
 *  Method: git::IsGitRepo
 *  Params: const wxString &project
 * Returns: bool
 * Effects:
 ***********************************************************************/
bool
git::IsGitRepo(const wxString &project, ICommandExecuter&)
{
    return true;
}


/***********************************************************************
 *  Method: git::git
 *  Params: const wxString &project, ICommandExecuter &cmdExecutor
 * Effects:
 ***********************************************************************/
git::git(const wxString &project, ICommandExecuter &cmdExecutor) :
    IVersionControlSystem(project, m_GitUpdate, m_GitAdd, m_GitRemove, m_GitCommit, m_GitRevert),
    m_GitRoot(GitRootDir),
    m_CmdExecutor(cmdExecutor),
    m_GitUpdate(*this, GitRootDir, m_CmdExecutor),
    m_GitAdd(*this, GitRootDir, m_CmdExecutor),
    m_GitRemove(*this, GitRootDir, m_CmdExecutor),
    m_GitCommit(*this, GitRootDir, m_CmdExecutor),
    m_GitRevert(*this, GitRootDir, m_CmdExecutor)
{

}


/***********************************************************************
 *  Method: git::~git
 *  Params:
 * Effects:
 ***********************************************************************/
git::~git()
{
}
