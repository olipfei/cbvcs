#ifndef VCSFILEOP_H
#define VCSFILEOP_H

#include <vector>

class VcsTreeItem;

class VcsFileOp
{
    public:
        VcsFileOp() {}
        virtual ~VcsFileOp() {}
        virtual void execute(std::vector<VcsTreeItem*>&) const = 0;
};

#endif // VCSFILEOP_H
