#include <projectfile.h>
#include "VcsFileItem.h"

VcsFileItem::VcsFileItem(ProjectFile* PrjFile) :
    VcsTreeItem(PrjFile->file.GetFullPath(), (ItemState) PrjFile->GetFileState()), m_PrjFile(PrjFile)
{
    //ctor
}

VcsFileItem::~VcsFileItem()
{
    //dtor
}

/*virtual*/ void VcsFileItem::VisualiseState() const
{
    m_PrjFile->SetFileState((FileVisualState)GetState());
}
