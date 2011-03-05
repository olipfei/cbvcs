/***********************************************************************
 * AUTHOR: Dushara Jayasinghe <dushara>
 *   FILE: .//VcsTreeItem.cpp
 *   DATE: Tue Feb 15 21:14:16 2011
 *  DESCR: 
 ***********************************************************************/
#include "VcsTreeItem.h"

/***********************************************************************
 *  Method: VcsTreeItem::VcsTreeItem
 *  Params: wxString Name, ItemState State
 * Effects: 
 ***********************************************************************/
VcsTreeItem::VcsTreeItem(wxString Name, ItemState State)
{
}


/***********************************************************************
 *  Method: VcsTreeItem::~VcsTreeItem
 *  Params: 
 * Effects: 
 ***********************************************************************/
VcsTreeItem::~VcsTreeItem()
{
}


/***********************************************************************
 *  Method: VcsTreeItem::GetRelativeName
 *  Params: const wxString &RootPath
 * Returns: const wxString
 * Effects: 
 ***********************************************************************/
const wxString
VcsTreeItem::GetRelativeName(const wxString &RootPath) const
{
    const wxString dummy;

    return dummy;
}


