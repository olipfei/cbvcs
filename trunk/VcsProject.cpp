#include "VcsProject.h"

VcsProject::VcsProject(wxString Name, ItemState PrjState) :
    VcsTreeItem(Name, PrjState)
{
    //ctor
}

VcsProject::~VcsProject()
{
    //dtor
}

/*virtual*/ void VcsProject::VisualiseState() const
{

}
