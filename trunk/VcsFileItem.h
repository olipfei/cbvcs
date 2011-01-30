#ifndef VCSFILEITEM_H
#define VCSFILEITEM_H

#include "VcsTreeItem.h"

class ProjectFile;

class VcsFileItem : public VcsTreeItem
{
    public:
        /** Default constructor */
        VcsFileItem(ProjectFile* PrjFile);
        /** Default destructor */
        virtual ~VcsFileItem();

        virtual void VisualiseState() const;
    protected:
    private:
        ProjectFile* m_PrjFile;
};

#endif // VCSFILEITEM_H
