#include "vcsfactory.h"
#include "git.h"

/*static*/ IVersionControlSystem* VcsFactory::GetVcs(const wxString& ProjectPath)
{
    if(git::IsGitRepo(ProjectPath))
    {
        return new git(ProjectPath);
    }
    return 0;
}
