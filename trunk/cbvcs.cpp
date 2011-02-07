#include <sdk.h> // Code::Blocks SDK
#include <configurationpanel.h>
#include <cbproject.h>
#include <cbeditor.h>
#include <projectmanager.h>
#include <cbfunctor.h>
#include <logmanager.h>

#include "cbvcs.h"
#include "IVersionControlSystem.h"
#include "VcsFileItem.h"
#include "vcsfactory.h"
#include "treeitemvector.h"
#include "vcsprojecttracker.h"

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
    Manager::Get()->RegisterEventSink(cbEVT_PROJECT_SAVE, new cbEventFunctor<cbvcs, CodeBlocksEvent>(this, &cbvcs::OnProjectSave));
    Manager::Get()->RegisterEventSink(cbEVT_EDITOR_SAVE, new cbEventFunctor<cbvcs, CodeBlocksEvent>(this, &cbvcs::OnEditorSave));
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
    wxMenu* VcsMenu = new wxMenu(_("Git"));

    wxMenu* branch = new wxMenu(_("Branch"));
    branch->Append(idBranchCreate, _("Create"), _("Create branch"));
    branch->Append(idBranchCheckout, _("Checkout"), _("Checkout branch"));
    branch->Append(idBranchMerge, _("Merge"), _("Merge branches"));

    wxMenu* tag = new wxMenu(_("Tag"));
    tag->Append(idTagCreate, _("Create"), _("Create a new tag"));
    tag->Append(idTagCheckout, _("Checkout"), _("Checkout a tag"));

    VcsMenu->Append(idCommit, _("Commit"), _("Commit this file"));
    VcsMenu->Append(idRevert, _("Revert"), _("Revert changes"));

    VcsMenu->AppendSubMenu(branch, _("Branch"));
    VcsMenu->AppendSubMenu(tag, _("Tag"));
    menu->AppendSubMenu(VcsMenu, _("Git"));
}

void cbvcs::CreateFolderMenu(wxMenu* menu)
{
    wxMenu* VcsMenu = new wxMenu(_("Git"));

    VcsMenu->Append(idAdd, _("Add"), _("Add this file"));
    VcsMenu->Append(idRemove, _("Remove"), _("Remove this file"));
    VcsMenu->Append(idCommit, _("Commit"), _("Commit this file"));
    VcsMenu->Append(idRevert, _("Revert"), _("Revert changes"));

    menu->AppendSubMenu(VcsMenu, _("Git"));
}

void cbvcs::CreateFileMenu(wxMenu* menu, const FileTreeData* data)
{
    ProjectFile* file = data->GetProjectFile();

    if(file->GetFileState() == (FileVisualState)Item_UntrackedMissing )
    {
        return;
    }

    wxMenu* VcsMenu = new wxMenu(_("Git"));

    if(file->GetFileState() == (FileVisualState)Item_Untracked )
    {
        VcsMenu->Append(idAdd, _("Add"), _("Add this file"));
    }
    else if(file->GetFileState() == (FileVisualState)Item_Added
       || file->GetFileState() == (FileVisualState)Item_Removed)
    {
        VcsMenu->Append(idCommit, _("Commit"), _("Commit this file"));
        VcsMenu->Append(idRevert, _("Revert"), _("Revert changes"));
    }
    else if(file->GetFileState() == (FileVisualState)Item_UpToDate
       || file->GetFileState() == (FileVisualState)Item_Modified)
    {
        VcsMenu->Append(idRemove, _("Remove"), _("Remove this file"));
        VcsMenu->Append(idRename, _("Rename"), _("Rename this file"));

        if(file->GetFileState() == (FileVisualState)Item_Modified)
        {
            VcsMenu->Append(idCommit, _("Commit"), _("Commit this file"));
            VcsMenu->Append(idRevert, _("Revert"), _("Revert changes"));
        }
    }
    else if(file->GetFileState() == (FileVisualState)Item_Missing)
    {
        VcsMenu->Append(idRemove, _("Remove"), _("Remove this file"));
        VcsMenu->Append(idRevert, _("Revert"), _("Revert changes"));
    }

    menu->AppendSubMenu(VcsMenu, _("Git"));
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

vcsProjectTracker* cbvcs::GetVcsInstance(const FileTreeData *data)
{
    if ( !data )
        return 0;

    cbProject* prj = data->GetProject();
    if(!prj)
    {
        return 0;
    }

    const wxString& prj_file = prj->GetFilename();

    std::map<const wxString, vcsProjectTracker*>::const_iterator it
        = m_ProjectVcs.find(prj_file);

    vcsProjectTracker* vcsTracker;
    if(it == m_ProjectVcs.end())
    {
        return 0;
    }
    else
    {
        vcsTracker = (*it).second;
    }

    return vcsTracker;
}

void cbvcs::GetFileItem(TreeItemVector& treeVector, const wxTreeCtrl& tree, const wxTreeItemId& treeItem)
{
    FileTreeData* ftd = static_cast<FileTreeData*>( tree.GetItemData( treeItem ) );

    if(ftd->GetKind() == FileTreeData::ftdkFile)
    {
        treeVector.CreateFileItem(ftd->GetProjectFile());
    }
}

void cbvcs::GetDescendents(TreeItemVector& treeVector, const wxTreeCtrl& tree, const wxTreeItemId& start)
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
            GetDescendents(treeVector, tree, child);
        }
        else
        {
            GetFileItem(treeVector, tree, child);
        }
        child = tree.GetNextChild(start, cookie);
    }
}

vcsProjectTracker* cbvcs::GetSelectedItemInfo(const wxTreeCtrl*& tree, wxTreeItemId& selItem, const FileTreeData*& ftData)
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

void cbvcs::PerformGroupAction(vcsProjectTracker& prjTracker,
                               const VcsFileOp& fileOp,
                               const wxTreeCtrl& tree,
                               wxTreeItemId& treeItem,
                               const FileTreeData& data)
{
    TreeItemVector files;

    if(data.GetKind() == FileTreeData::ftdkFile)
    {
        ProjectFile* f = data.GetProjectFile();
        if ( f )
        {
            files.CreateFileItem(f);
            fileOp.execute(files.GetVector());
        }
    }
    else if(data.GetKind() == FileTreeData::ftdkFolder)
    {
        GetDescendents(files, tree, treeItem);
        fileOp.execute(files.GetVector());
    }
    else if(data.GetKind() == FileTreeData::ftdkProject)
    {
        cbProject* prj = data.GetProject();

        files.CreateProjectItem(prj->GetFilename(), prjTracker.GetProjectState());
        GetDescendents(files, tree, treeItem);
        fileOp.execute(files.GetVector());
    }
    else
    {
        return;
    }

    IVersionControlSystem& vcs = prjTracker.GetVcs();
    vcs.UpdateOp.execute(files.GetVector());
}

void cbvcs::OnAdd( wxCommandEvent& /*event*/ )
{
    const wxTreeCtrl* tree;
    wxTreeItemId treeItem;
    const FileTreeData* itemData;
    vcsProjectTracker* prjTracker;

    prjTracker = GetSelectedItemInfo(tree, treeItem, itemData);
    if(!prjTracker)
    {
        return;
    }

    PerformGroupAction(*prjTracker, prjTracker->GetVcs().AddOp, *tree, treeItem, *itemData);
}

void cbvcs::OnRemove( wxCommandEvent& /*event*/ )
{
    const wxTreeCtrl* tree;
    wxTreeItemId treeItem;
    const FileTreeData* itemData;
    vcsProjectTracker* prjTracker;

    prjTracker = GetSelectedItemInfo(tree, treeItem, itemData);
    if(!prjTracker)
    {
        return;
    }

    PerformGroupAction(*prjTracker, prjTracker->GetVcs().RemoveOp, *tree, treeItem, *itemData);
}

void cbvcs::OnCommit( wxCommandEvent& /*event*/ )
{
    const wxTreeCtrl* tree;
    wxTreeItemId treeItem;
    const FileTreeData* itemData;
    vcsProjectTracker* prjTracker;

    prjTracker = GetSelectedItemInfo(tree, treeItem, itemData);
    if(!prjTracker)
    {
        return;
    }

    PerformGroupAction(*prjTracker, prjTracker->GetVcs().CommitOp, *tree, treeItem, *itemData);
}

void cbvcs::OnRevert( wxCommandEvent& /*event*/ )
{
    const wxTreeCtrl* tree;
    wxTreeItemId treeItem;
    const FileTreeData* itemData;
    vcsProjectTracker* prjTracker;

    prjTracker = GetSelectedItemInfo(tree, treeItem, itemData);
    if(!prjTracker)
    {
        return;
    }

    PerformGroupAction(*prjTracker, prjTracker->GetVcs().RevertOp, *tree, treeItem, *itemData);
}

void cbvcs::OnProjectOpen( CodeBlocksEvent& event )
{
    cbProject* prj = event.GetProject();

    if(!prj)
    {
        return;
    }

    const wxString prjFilename = prj->GetFilename();

    std::map<const wxString, vcsProjectTracker*>::const_iterator it
        = m_ProjectVcs.find(prjFilename);

    IVersionControlSystem* vcs;
    vcsProjectTracker* prjTracker;

    if(it == m_ProjectVcs.end())
    {
        vcs = VcsFactory::GetVcs(prjFilename);
        if(!vcs)
        {
            Manager::Get()->GetLogManager()->Log( _("cbvcs: Project not controlled") );
            return;
        }
        prjTracker = new vcsProjectTracker(vcs, prjFilename);
        m_ProjectVcs[prjFilename] = prjTracker;
    }
    else
    {
        prjTracker = (*it).second;
        vcs = &prjTracker->GetVcs();
    }

    TreeItemVector files;
    files.CreateProjectItem(prjFilename, prjTracker->GetProjectState());

    for ( int i = 0; i < prj->GetFilesCount(); ++i )
    {
        ProjectFile* pf = prj->GetFile( i );
        files.CreateFileItem(pf);
    }

    vcs->UpdateOp.execute(files.GetVector());
}

void cbvcs::OnProjectClose( CodeBlocksEvent& event )
{
    cbProject* prj = event.GetProject();

    if(!prj)
    {
        return;
    }

    const wxString prj_file = prj->GetFilename();

    std::map<const wxString, vcsProjectTracker*>::iterator it
        = m_ProjectVcs.find(prj_file);

    if(it == m_ProjectVcs.end())
    {
        return;
    }
    else
    {
        vcsProjectTracker* prjTracker = (*it).second;
        delete prjTracker;
        m_ProjectVcs.erase(it);
        Manager::Get()->GetLogManager()->Log( _("vcs successful removal") );
    }
}

void cbvcs::OnProjectSave( CodeBlocksEvent& event )
{
    cbProject* prj = event.GetProject();

    if(!prj)
    {
        Manager::Get()->GetLogManager()->Log( _("null") );
        return;
    }

    const wxString prjFilename = prj->GetFilename();

    std::map<const wxString, vcsProjectTracker*>::iterator it
        = m_ProjectVcs.find(prjFilename);

    if(it == m_ProjectVcs.end())
    {
        Manager::Get()->GetLogManager()->Log( _("Couldn't find project " + prjFilename) );
        return;
    }
    else
    {
        vcsProjectTracker* prjTracker = (*it).second;
        TreeItemVector files;
        files.CreateProjectItem(prjFilename, prjTracker->GetProjectState());
        prjTracker->GetVcs().UpdateOp.execute(files.GetVector());
    }
}

void cbvcs::OnEditorSave( CodeBlocksEvent& event )
{
    cbEditor* ed = (cbEditor*) event.GetEditor();

    if(!ed)
    {
        Manager::Get()->GetLogManager()->Log(_("Editor NULL"));
        return;
    }

    cbProject* prj = Manager::Get()->GetProjectManager()->GetActiveProject();

    if(!prj)
    {
        Manager::Get()->GetLogManager()->Log(_("Prj NULL"));
        return;
    }

    ProjectFile* SavedFile = prj->GetFileByFilename(ed->GetFilename(), false, true);
    if(!SavedFile)
    {
        // File not part of project. Just ignore
        Manager::Get()->GetLogManager()->Log(ed->GetFilename() + _(" Not in project"));
        return;
    }

    const wxString& PrjFilename = prj->GetFilename();

    std::map<const wxString, vcsProjectTracker*>::iterator it
        = m_ProjectVcs.find(PrjFilename);

    if(it == m_ProjectVcs.end())
    {
        return;
    }
    else
    {
        std::vector<VcsTreeItem*>UpdateList;
        vcsProjectTracker* prjTracker = (*it).second;

        VcsFileItem vcsItem(SavedFile);
        UpdateList.push_back(&vcsItem);
        prjTracker->GetVcs().UpdateOp.execute(UpdateList);
    }
}
