/*  cbvcs Code::Blocks version control system plugin

    Copyright (C) 2011 Dushara Jayasinghe.

    cbvcs is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    cbvcs is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with cbvcs.  If not, see <http://www.gnu.org/licenses/>.
*/

#include <wx/string.h>
#include "git.h"
#include "VcsTreeItem.h"
#include "icommandexecuter.h"

git::git(const wxString& project, ICommandExecuter& cmdExecutor) :
    IVersionControlSystem(project, m_GitUpdate, m_GitAdd, m_GitRemove, m_GitCommit, m_GitRevert),
    m_GitRoot(QueryRoot(project, cmdExecutor)),
    m_CmdExecutor(cmdExecutor),
    m_GitUpdate(*this, m_GitRoot, m_CmdExecutor),
    m_GitAdd(*this, m_GitRoot, m_CmdExecutor),
    m_GitRemove(*this, m_GitRoot, m_CmdExecutor),
    m_GitCommit(*this, m_GitRoot, m_CmdExecutor),
    m_GitRevert(*this, m_GitRoot, m_CmdExecutor)
{
}

git::~git()
{
    //dtor
}


/*static*/ wxString git::QueryRoot(const wxString& project, ICommandExecuter& shellUtils)
{
    wxArrayString Output, Errors;
    const wxString shellCommand = _("git rev-parse --show-toplevel");

    shellUtils.pushd(wxPathOnly(project));
    if(!shellUtils.execute(shellCommand, Output, Errors))
    {
        return _("");
    }
    shellUtils.popd();

    if(Output.Count() == 0)
    {
        return _("");
    }

    return Output[0];
}

/*static*/ bool git::IsGitRepo(const wxString& project, ICommandExecuter& shellUtils)
{
    wxArrayString Output, Errors;
    const wxString shellCommand = _("git rev-parse --show-toplevel");

    shellUtils.pushd(wxPathOnly(project));
    if(!shellUtils.execute(shellCommand, Output, Errors))
    {
        // TODO: Error dialog
        return false;
    }
    shellUtils.popd();

    return Output.Count() != 0;
}

#if 0

void GitRevertOp::execute(std::vector<VcsTreeItem*>& paths) const
{
}
#endif
