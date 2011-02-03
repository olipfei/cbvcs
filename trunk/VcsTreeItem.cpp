#include <logmanager.h>
#include "VcsTreeItem.h"

VcsTreeItem::VcsTreeItem(wxString Name, ItemState State) :
    m_Name(Name),
    m_State(State)
{
    //ctor
}

VcsTreeItem::~VcsTreeItem()
{
    //dtor
}

const wxString VcsTreeItem::GetRelativeName(const wxString& RootPath) const
{
    wxString RelativeName;

    if(m_Name.StartsWith(RootPath, &RelativeName))
    {
        // strip first '/'
        RelativeName = RelativeName(1, RelativeName.length());
    }

    return RelativeName;
}
