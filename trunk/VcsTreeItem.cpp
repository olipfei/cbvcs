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
