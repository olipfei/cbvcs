#ifndef VCSTREEITEM_H
#define VCSTREEITEM_H

#include <wx/string.h>
#include <globals.h>

enum ItemState
{
    Item_Untracked = fvsNormal,
    Item_UntrackedMissing = fvsMissing,
    Item_Added = fvsVcAdded,
    Item_Conflicted = fvsVcConflict,
    Item_Modified = fvsVcModified,
    Item_Removed = fvsVcNonControlled,
    Item_Missing = fvsVcMissing,
    Item_UpToDate = fvsVcUpToDate
};

class VcsTreeItem
{
    public:
        VcsTreeItem(wxString Name, ItemState State);
        virtual ~VcsTreeItem();
        ItemState GetState() const { return m_State; }
        void SetState(ItemState val) { m_State = val; }
        const wxString& GetName() { return m_Name; }
        const wxString GetRelativeName(const wxString& RootPath) const;
        void SetName(wxString val) { m_Name = val; }
        virtual void VisualiseState() const = 0;

    private:
        wxString m_Name;
        ItemState m_State;
};

#endif // VCSTREEITEM_H
