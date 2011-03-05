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
#include "gitremoveop.h"

/***********************************************************************
 *  Method: GitRemoveOp::execute
 *  Params: std::vector<VcsTreeItem *> &
 * Returns: void
 * Effects:
 ***********************************************************************/
void
GitRemoveOp::ExecuteImplementation(std::vector<VcsTreeItem*>& itemPaths) const
{
    wxString UptodateFiles;
    wxString CachedFiles;

    std::vector<VcsTreeItem*>::const_iterator i;

    for(i=itemPaths.begin(); i!= itemPaths.end(); i++)
    {
        VcsTreeItem* Item = *i;

        wxString relativeFilename = Item->GetRelativeName(m_VcsRootDir);
        if(relativeFilename.length() == 0)
        {
            continue;
        }

        if(Item->GetState() == Item_UpToDate
           || Item->GetState() == Item_Missing)
        {
            UptodateFiles += _(" ") + relativeFilename;
        }
        else if(Item->GetState() == Item_Added
                || Item->GetState() == Item_Modified)
        {
            CachedFiles += _(" ") + relativeFilename;
        }
    }

    wxArrayString outCapture;
    wxArrayString errCapture;

    if(UptodateFiles.length())
    {
        m_ShellUtils.execute(_("git rm") + UptodateFiles, outCapture, errCapture);
    }

    if(CachedFiles.length())
    {
        m_ShellUtils.execute(_("git rm --cached") + CachedFiles, outCapture, errCapture);
    }
}


