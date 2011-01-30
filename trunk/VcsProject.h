#ifndef VCSPROJECT_H
#define VCSPROJECT_H

#include "VcsTreeItem.h"


class VcsProject : public VcsTreeItem
{
    public:
        /** Default constructor */
        VcsProject(wxString Name, ItemState PrjState);
        /** Default destructor */
        virtual ~VcsProject();

        virtual void VisualiseState() const;
    protected:
    private:
};

#endif // VCSPROJECT_H
