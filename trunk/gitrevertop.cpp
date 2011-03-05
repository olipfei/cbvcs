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
#include "gitrevertop.h"

/***********************************************************************
 *  Method: GitRevertOp::execute
 *  Params: std::vector<VcsTreeItem *> &
 * Returns: void
 * Effects:
 ***********************************************************************/
void
GitRevertOp::ExecuteImplementation(std::vector<VcsTreeItem*>& pathList) const
{
    wxString pathString;
    std::vector<VcsTreeItem*>::const_iterator i;

    for(i=pathList.begin(); i!= pathList.end(); i++)
    {
        wxString relativeFilename = (*i)->GetRelativeName(m_VcsRootDir);
        if(relativeFilename.length() == 0)
        {
            continue;
        }
        pathString += _(" ") + relativeFilename;
    }

    wxArrayString outCapture, errCapture;
    m_ShellUtils.execute(_("git checkout HEAD -f") + pathString, outCapture, errCapture);
}
