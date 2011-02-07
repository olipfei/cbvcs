#ifndef TREEITEMVECTOR_H
#define TREEITEMVECTOR_H

#include <vector>
#include "copyprotector.h"
#include "VcsTreeItem.h"

class ProjectFile;

class TreeItemVector : private CopyProtector
{
    public:
        /** Default constructor */
        TreeItemVector();
        /** Default destructor */
        virtual ~TreeItemVector();

        VcsTreeItem& CreateFileItem(ProjectFile* prjFile);
        VcsTreeItem& CreateProjectItem(wxString prjPath, ItemState& prjState);

        std::vector<VcsTreeItem*>& GetVector();
    protected:

    private:
        std::vector<VcsTreeItem*> m_TreeItems;
};

#endif // TREEITEMVECTOR_H
