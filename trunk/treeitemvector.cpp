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
