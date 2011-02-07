#include <logmanager.h>
#include "VcsProject.h"

VcsProject::VcsProject(wxString Name, ItemState& prjState) :
    VcsTreeItem(Name, prjState),
    m_PrjState(prjState)
{
    Manager::Get()->GetLogManager()->Log( _("Project Item:") + Name );
}

VcsProject::~VcsProject()
{
    //dtor
}

/*virtual*/ void VcsProject::VisualiseState() const
{
    m_PrjState = GetState();
}
