#include "CrossFrm.h"
#include <wx/aui/auibook.h>


BEGIN_EVENT_TABLE(test,wxFrame)

END_EVENT_TABLE()


test::test(wxWindow *parent, wxWindowID id, const wxString &title, const wxPoint& pos, const wxSize& size , long style )
        : wxFrame(parent, id, title, pos, size, style)
{
    m_Manager.SetManagedWindow(this);
    
    CreateStatusBar();
    
    wxAuiNotebook *m_Notebook = new wxAuiNotebook(this, wxID_ANY, wxDefaultPosition, wxSize(600, 450), 
		wxAUI_NB_DEFAULT_STYLE|wxNO_BORDER);
	wxPanel *m_Page1 = new wxPanel(m_Notebook, wxID_ANY);
	wxPanel *m_Page2 = new wxPanel(m_Notebook, wxID_ANY);
	m_Notebook->AddPage(m_Page1, _("Page1"));
	m_Notebook->AddPage(m_Page2, _("Page2"));
    
   wxToolBar *m_StdToolBar = new wxToolBar(this, wxID_ANY, wxDefaultPosition,
		wxDefaultSize, wxBORDER_NONE|wxTB_HORIZONTAL|wxTB_NODIVIDER|wxTB_FLAT);
	m_StdToolBar->SetToolBitmapSize(wxSize(16, 15));
	m_StdToolBar->AddTool(wxID_NEW, _("New"));//, wxBitmap(new_xpm));
	m_StdToolBar->AddTool(wxID_OPEN, _("Open"));//, wxBitmap(fileopen_xpm));
	m_StdToolBar->AddTool(wxID_SAVE, _("Save"));//, wxBitmap(filesave_xpm));
	m_StdToolBar->AddSeparator();
	m_StdToolBar->AddTool(wxID_ABOUT, _("About..."));//, wxBitmap(htmfoldr_xpm));
	m_StdToolBar->Realize();

    wxToolBar *m_AddToolBar = new wxToolBar(this, wxID_ANY, wxDefaultPosition,
		wxDefaultSize, wxBORDER_NONE|wxTB_HORIZONTAL|wxTB_NODIVIDER|wxTB_FLAT);
	m_AddToolBar->SetToolBitmapSize(wxSize(16, 15));
	m_AddToolBar->AddTool(wxID_CUT, _("Cut"));//, wxBitmap(cut_xpm));
	m_AddToolBar->AddTool(wxID_COPY, _("Copy"));//, wxBitmap(copy_xpm));
	m_AddToolBar->AddTool(wxID_FIND, _("Find"));//, wxBitmap(find_xpm));
	m_AddToolBar->Realize();

    wxTreeCtrl *m_InfoTree = new wxTreeCtrl(this, wxID_ANY, wxDefaultPosition, wxSize(170, 250),
		wxTR_HAS_BUTTONS|wxTR_LINES_AT_ROOT|wxTR_SINGLE);
	wxTreeItemId root = m_InfoTree->AddRoot(_("Document"));
	m_InfoTree->AppendItem(root, _("Item 1"));
	m_InfoTree->AppendItem(root, _("Item 2"));
	m_InfoTree->AppendItem(root, _("Item 3"));
	m_InfoTree->Expand(root);
	wxTreeCtrl *m_InfoTree1 = new wxTreeCtrl(this, wxID_ANY, wxDefaultPosition, wxSize(170, 250),
		wxTR_HAS_BUTTONS|wxTR_LINES_AT_ROOT|wxTR_SINGLE);	
    wxTreeItemId root1 = m_InfoTree->AddRoot(_("Document1"));
	m_InfoTree->AppendItem(root1, _("Item 1"));
	m_InfoTree->AppendItem(root1, _("Item 2"));
	m_InfoTree->AppendItem(root1, _("Item 3"));
	m_InfoTree->Expand(root1);
	wxTreeCtrl *m_InfoTree2 = new wxTreeCtrl(this, wxID_ANY, wxDefaultPosition, wxSize(170, 250),
		wxTR_HAS_BUTTONS|wxTR_LINES_AT_ROOT|wxTR_SINGLE);
	wxTreeItemId root2 = m_InfoTree->AddRoot(_("Document2"));
	m_InfoTree->AppendItem(root2, _("Item 1"));
	m_InfoTree->AppendItem(root2, _("Item 2"));
	m_InfoTree->AppendItem(root2, _("Item 3"));
	m_InfoTree->Expand(root2);


    m_Manager.AddPane(m_Notebook, wxAuiPaneInfo().CenterPane());
	m_Manager.AddPane(m_StdToolBar, wxAuiPaneInfo().ToolbarPane().Top().Floatable(false));
	m_Manager.AddPane(m_AddToolBar, wxAuiPaneInfo().ToolbarPane().Top().Position(2).
		Floatable(false));
	m_Manager.AddPane(m_InfoTree, wxAuiPaneInfo().Left().Layer(1).PinButton().
		MinimizeButton().MaximizeButton().Caption(wxT("Information")));
		m_Manager.AddPane(m_InfoTree1, wxAuiPaneInfo().Left().Layer(1).PinButton().
		MinimizeButton().MaximizeButton().Caption(wxT("Information")));
		m_Manager.AddPane(m_InfoTree2, wxAuiPaneInfo().Left().Layer(1).PinButton().
		MinimizeButton().MaximizeButton().Caption(wxT("Information")));

    
    

    m_Manager.Update();
}

test::~test()
{
    m_Manager.UnInit();
}
