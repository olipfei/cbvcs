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
#ifndef GIT_H
#define GIT_H

#include "git-update.h"
#include "gitaddop.h"
#include "gitremoveop.h"
#include "gitcommitop.h"
#include "gitrevertop.h"

class wxArrayString;

class git : public IVersionControlSystem
{
    public:
        static bool IsGitRepo(const wxString& project, ICommandExecuter&);
        git(const wxString& project, ICommandExecuter& cmdExecutor);
        virtual ~git();

        virtual bool move(std::vector<VcsTreeItem*>&) {return false;}

    protected:
        const wxString m_GitRoot;

    private:
        ICommandExecuter& m_CmdExecutor;
        GitUpdateOp m_GitUpdate;
        GitAddOp m_GitAdd;
        GitRemoveOp m_GitRemove;
        GitCommitOp m_GitCommit;
        GitRevertOp m_GitRevert;

        static wxString QueryRoot(const wxString&, ICommandExecuter&);
};

#endif // GIT_H
