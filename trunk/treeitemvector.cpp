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
#include "treeitemvector.h"
#include "VcsFileItem.h"
#include "VcsProject.h"

TreeItemVector::TreeItemVector()
{
    //ctor
}

TreeItemVector::~TreeItemVector()
{
    while(m_TreeItems.size())
    {
        VcsTreeItem* item = m_TreeItems.back();
        m_TreeItems.pop_back();
        delete item;
    }
}

VcsTreeItem& TreeItemVector::CreateFileItem(ProjectFile* prjFile)
{
    VcsFileItem* vcsItem = new VcsFileItem(prjFile);
    m_TreeItems.push_back(vcsItem);

    return *vcsItem;
}

VcsTreeItem& TreeItemVector::CreateProjectItem(wxString prjPath, ItemState& prjState)
{
    VcsProject* vcsItem = new VcsProject(prjPath, prjState);
    m_TreeItems.push_back(vcsItem);

    return *vcsItem;
}

std::vector<VcsTreeItem*>& TreeItemVector::GetVector()
{
    return m_TreeItems;
}
