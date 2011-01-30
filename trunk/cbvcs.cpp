#include <sdk.h> // Code::Blocks SDK
#include <configurationpanel.h>
#include <cbproject.h>
#include <projectmanager.h>
#include <cbfunctor.h>
#include <logmanager.h>

#include "cbvcs.h"
#include "git.h"
#include "VcsFileItem.h"
#include "VcsProject.h"

// Register the plugin with Code::Blocks.
// We are using an anonymous namespace so we don't litter the global one.
namespace
{
PluginRegistrant<cbvcs> reg(_T("cbvcs"));
const int idAdd = wxNewId();
const int idRemove = wxNewId();
const int idRename = wxNewId();
const int idCommit = wxNewId();
const int idRevert = wxNewId();
const int idBranchCreate = wxNewId();
const int idBranchCheckout = wxNewId();
const int idBranchMerge = wxNewId();
const int idTagCreate = wxNewId();
const int idTagCheckout = wxNewId();
}


// events handling
BEGIN_EVENT_TABLE(cbvcs, cbPlugin)
    // add any events you want to handle here
    EVT_MENU( idAdd, cbvcs::OnAdd )
    EVT_MENU( idRemove, cbvcs::OnRemove )
    EVT_MENU( idCommit, cbvcs::OnCommit )
    EVT_MENU( idRevert, cbvcs::OnRevert )
END_EVENT_TABLE()

// constructor
cbvcs::cbvcs()
{
    // Make sure our resources are available.
    // In the generated boilerplate code we have no resources but when
    // we add some, it will be nice that this code is in place already ;)
    if(!Manager::LoadResource(_T("cbvcs.zip")))
    {
        NotifyMissingFile(_T("cbvcs.zip"));
    }
}

// destructor
cbvcs::~cbvcs()
// TODO (dushara#1#): Delete all vcs instances{
}

void cbvcs::OnAttach()
{
    // do whatever initialization you need for your plugin
    // NOTE: after this function, the inherited member variable
    // m_IsAttached will be TRUE...
    // You should check for it in other functions, because if it
    // is FALSE, it means that the application did *not* "load"
    // (see: does not need) this plugin...
    Manager::Get()->RegisterEventSink(cbEVT_PROJECT_OPEN, new cbEventFunctor<cbvcs, CodeBlocksEvent>(this, &cbvcs::OnProjectOpen));
    Manager::Get()->RegisterEventSink(cbEVT_PROJECT_CLOSE, new cbEventFunctor<cbvcs, CodeBlocksEvent>(this, &cbvcs::OnProjectClose));
}

void cbvcs::OnRelease(bool appShutDown)
{
    // do de-initialization for your plugin
    // if appShutDown is true, the plugin is unloaded because Code::Blocks is being shut down,
    // which means you must not use any of the SDK Managers
    // NOTE: after this function, the inherited member variable
    // m_IsAttached will be FALSE...
}

int cbvcs::Configure()
{
    //create and display the configuration dialog for your plugin
    cbConfigurationDialog dlg(Manager::Get()->GetAppWindow(), wxID_ANY, _("Your dialog title"));
    cbConfigurationPanel* panel = GetConfigurationPanel(&dlg);
    if (panel)
    {
        dlg.AttachConfigurationPanel(panel);
        PlaceWindow(&dlg);
        return dlg.ShowModal() == wxID_OK ? 0 : -1;
    }
    return -1;
}

void cbvcs::BuildMenu(wxMenuBar* menuBar)
{
    //The application is offering its menubar for your plugin,
    //to add any menu items you want...
    //Append any items you need in the menu...
    //NOTE: Be careful in here... The application's menubar is at your disposal.
    NotImplemented(_T("cbvcs::BuildMenu()"));
}

void cbvcs::CreateProjectMenu(wxMenu* menu, const FileTreeData* data)
{
    wxMenu* svn = new wxMenu(_("Svn"));

    wxMenu* branch = new wxMenu(_("Branch"));
    branch->Append(idBranchCreate, _("Create"), _("Create branch"));
    branch->Append(idBranchCheckout, _("Checkout"), _("Checkout branch"));
    branch->Append(idBranchMerge, _("Merge"), _("Merge branches"));

    wxMenu* tag = new wxMenu(_("Tag"));
    tag->Append(idTagCreate, _("Create"), _("Create a new tag"));
    tag->Append(idTagCheckout, _("Checkout"), _("Checkout a tag"));

    svn->Append(idCommit, _("Commit"), _("Commit this file"));
    svn->Append(idRevert, _("Revert"), _("Revert changes"));

    svn->AppendSubMenu(branch, _("Branch"));
    svn->AppendSubMenu(tag, _("Tag"));
    menu->AppendSubMenu(svn, _("Svn"));
}

void cbvcs::CreateFolderMenu(wxMenu* menu)
{
    wxMenu* svn = new wxMenu(_("Svn"));

    svn->Append(idAdd, _("Add"), _("Add this file"));
    svn->Append(idRemove, _("Remove"), _("Remove this file"));
    svn->Append(idRename, _("Rename"), _("Rename this file"));
    svn->Append(idCommit, _("Commit"), _("Commit this file"));
    svn->Append(idRevert, _("Revert"), _("Revert changes"));

    menu->AppendSubMenu(svn, _("Svn"));
}

void cbvcs::CreateFileMenu(wxMenu* menu, const FileTreeData* data)
{
    ProjectFile* file = data->GetProjectFile();

    if(file->GetFileState() == fvsVcNonControlled)
    {
        return;
    }

    wxMenu* svn = new wxMenu(_("Svn"));

    if(file->GetFileState() == fvsNormal )
    {
        svn->Append(idAdd, _("Add"), _("Add this file"));
    }
    else
    {
        svn->Append(idRemove, _("Remove"), _("Remove this file"));
        svn->Append(idRename, _("Rename"), _("Rename this file"));
        svn->Append(idCommit, _("Commit"), _("Commit this file"));
        svn->Append(idRevert, _("Revert"), _("Revert changes"));
    }

    menu->AppendSubMenu(svn, _("Svn"));
}

void cbvcs::BuildModuleMenu(const ModuleType type, wxMenu* menu, const FileTreeData* data)
{
    if ( !menu || !IsAttached())
        return;

    if(type != mtProjectManager)
    {
        return;
    }

    if(data->GetKind() == FileTreeData::ftdkFile)
    {
        CreateFileMenu(menu, data);
    }
    else if(data->GetKind() == FileTreeData::ftdkFolder)
    {
        CreateFolderMenu(menu);
        // same menu as File but maybe traverse the tree
    }
    else if(data->GetKind() == FileTreeData::ftdkProject)
    {
        CreateProjectMenu(menu, data);
    }
}

bool cbvcs::BuildToolBar(wxToolBar* toolBar)
{
    //The application is offering its toolbar for your plugin,
    //to add any toolbar items you want...
    //Append any items you need on the toolbar...
    NotImplemented(_T("cbvcs::BuildToolBar()"));

    // return true if you add toolbar items
    return false;
}

IVersionControlSystem* cbvcs::GetVcsInstance(const FileTreeData *data)
{
    if ( !data )
        return 0;

    cbProject* prj = data->GetProject();
    if(!prj)
    {
        return 0;
    }

    const wxString& prj_file = prj->GetFilename();

    std::map<const wxString, IVersionControlSystem*>::const_iterator it
        = m_ProjectVcs.find(prj_file);

    if(it == m_ProjectVcs.end())
    {
        return 0;
    }
    else
    {
        return (*it).second;
    }
}

VcsTreeItem* cbvcs::GetFileItem(const wxTreeCtrl& tree, const wxTreeItemId& treeItem)
{
    FileTreeData* ftd = static_cast<FileTreeData*>( tree.GetItemData( treeItem ) );

    if(ftd->GetKind() == FileTreeData::ftdkFile)
    {
        ProjectFile* path = ftd->GetProjectFile();
        return new VcsFileItem(path);
    }

    return 0;
}

void cbvcs::GetDescendents(std::vector<VcsTreeItem*>& dst, const wxTreeCtrl& tree, const wxTreeItemId& start)
{
    wxTreeItemIdValue cookie;

    if(!tree.ItemHasChildren(start))
    {
        return ;
    }

    wxTreeItemId child = tree.GetFirstChild(start, cookie);
    while(child.IsOk())
    {
        if(tree.ItemHasChildren(child))
        {
            GetDescendents(dst, tree, child);
        }
        else
        {
            VcsTreeItem* vcsItem = GetFileItem(tree, child);
            if(vcsItem != 0)
            {
                dst.push_back(vcsItem);
            }
        }
        child = tree.GetNextChild(start, cookie);
    }
}

IVersionControlSystem* cbvcs::GetSelectedItemInfo(const wxTreeCtrl*& tree, wxTreeItemId& selItem, const FileTreeData*& ftData)
{
    tree = Manager::Get()->GetProjectManager()->GetTree();
    if(!tree)
    {
        return 0;
    }

    selItem = tree->GetSelection();
    if ( !selItem.IsOk() )
    {
        return 0;
    }

    ftData = static_cast<FileTreeData*>( tree->GetItemData( selItem ) );

    if ( !ftData )
    {
        return 0;
    }

    return GetVcsInstance(ftData);
}

void cbvcs::DeleteTreeItems(std::vector<VcsTreeItem*>& TreeItems)
{
    while(TreeItems.size())
    {
        VcsTreeItem* Item = TreeItems.back();
        TreeItems.pop_back();
        delete Item;
    }
}

void cbvcs::PerformGroupAction(IVersionControlSystem& vcs,
                               const VcsFileOp& fileOp,
                               const wxTreeCtrl& tree,
                               wxTreeItemId& treeItem,
                               const FileTreeData& data)
{
    std::vector<VcsTreeItem*>files;

    if(data.GetKind() == FileTreeData::ftdkFile)
    {
        ProjectFile* f = data.GetProjectFile();
        if ( f )
        {
            VcsFileItem* vcsItem = new VcsFileItem(f);
            files.push_back(vcsItem);
            fileOp.execute(files);
        }
    }
    else if(data.GetKind() == FileTreeData::ftdkFolder)
    {
        GetDescendents(files, tree, treeItem);
        fileOp.execute(files);
    }
    else if(data.GetKind() == FileTreeData::ftdkProject)
    {
        cbProject* prj = data.GetProject();
        // XXX FileNameFromPath is obsolete
        VcsProject* vcsItem = new VcsProject(wxFileNameFromPath(prj->GetFilename()), Item_Modified);
        files.push_back(vcsItem);
        GetDescendents(files, tree, treeItem);
        fileOp.execute(files);
    }
    else
    {
        return;
    }

    vcs.UpdateOp.execute(files);
    Manager::Get()->GetLogManager()->Log( _("Delete Items") );
    DeleteTreeItems(files);
    Manager::Get()->GetLogManager()->Log( _("Group complete"));
}

void cbvcs::OnAdd( wxCommandEvent& /*event*/ )
{
    const wxTreeCtrl* tree;
    wxTreeItemId treeItem;
    const FileTreeData* itemData;
    IVersionControlSystem* vcs;

    vcs = GetSelectedItemInfo(tree, treeItem, itemData);
    if(!vcs)
    {
        return;
    }

    PerformGroupAction(*vcs, vcs->AddOp, *tree, treeItem, *itemData);
}

void cbvcs::OnRemove( wxCommandEvent& /*event*/ )
{
    const wxTreeCtrl* tree;
    wxTreeItemId treeItem;
    const FileTreeData* itemData;
    IVersionControlSystem* vcs;

    vcs = GetSelectedItemInfo(tree, treeItem, itemData);
    if(!vcs)
    {
        return;
    }

    PerformGroupAction(*vcs, vcs->RemoveOp, *tree, treeItem, *itemData);
}

void cbvcs::OnCommit( wxCommandEvent& /*event*/ )
{
    const wxTreeCtrl* tree;
    wxTreeItemId treeItem;
    const FileTreeData* itemData;
    IVersionControlSystem* vcs;

    vcs = GetSelectedItemInfo(tree, treeItem, itemData);
    if(!vcs)
    {
        return;
    }

    PerformGroupAction(*vcs, vcs->CommitOp, *tree, treeItem, *itemData);
}

void cbvcs::OnRevert( wxCommandEvent& /*event*/ )
{
    const wxTreeCtrl* tree;
    wxTreeItemId treeItem;
    const FileTreeData* itemData;
    IVersionControlSystem* vcs;

    vcs = GetSelectedItemInfo(tree, treeItem, itemData);
    if(!vcs)
    {
        return;
    }

    PerformGroupAction(*vcs, vcs->RevertOp, *tree, treeItem, *itemData);
}

void cbvcs::OnProjectOpen( CodeBlocksEvent& event )
{
    cbProject* prj = event.GetProject();

    if(!prj)
    {
        return;
    }

    IVersionControlSystem* vcs;
    const wxString& prj_file = prj->GetFilename();

    std::map<const wxString, IVersionControlSystem*>::const_iterator it
        = m_ProjectVcs.find(prj_file);

    if(it == m_ProjectVcs.end())
    {
        vcs = new git(prj_file);
        m_ProjectVcs[prj_file] = vcs;
    }
    else
    {
        vcs = (*it).second;
    }

    std::vector<VcsTreeItem*>files;

    for ( int i = 0; i < prj->GetFilesCount(); ++i )
    {
        ProjectFile* pf = prj->GetFile( i );
        VcsFileItem* vcsItem = new VcsFileItem(pf);
        files.push_back(vcsItem);
    }

    vcs->UpdateOp.execute(files);
}

void cbvcs::OnProjectClose( CodeBlocksEvent& event )
{
    cbProject* prj = event.GetProject();

    if(!prj)
    {
        return;
    }

    const wxString& prj_file = prj->GetFilename();

    std::map<const wxString, IVersionControlSystem*>::iterator it
        = m_ProjectVcs.find(prj_file);

    if(it == m_ProjectVcs.end())
    {
        return;
    }
    else
    {
        IVersionControlSystem* vcs = (*it).second;
        delete vcs;
        m_ProjectVcs.erase(it);
        Manager::Get()->GetLogManager()->Log( _("git() successful removal") );
    }
}
