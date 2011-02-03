#ifndef VCSFACTORY_H
#define VCSFACTORY_H

class IVersionControlSystem;
class wxString;

class VcsFactory
{
    public:
        static IVersionControlSystem* GetVcs(const wxString& ProjectPath);
};

#endif // VCSFACTORY_H
