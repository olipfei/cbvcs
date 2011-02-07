#ifndef VCSPROJECT_H
#define VCSPROJECT_H

#include "VcsTreeItem.h"


class VcsProject : public VcsTreeItem
{
    public:
        /** Default constructor */
        VcsProject(wxString Name, ItemState& prjState);
        /** Default destructor */
        virtual ~VcsProject();

        virtual void VisualiseState() const;
    protected:
    private:
        ItemState& m_PrjState;
};

#endif // VCSPROJECT_H
