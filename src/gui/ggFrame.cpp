/*
        This file is part of GlslGenie

    GlslGenie is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    GlslGenie is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with GlslGenie.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "ggFrame.h"
#include "ggGlobals.h"
#include "ggProperties.h"

ggFrame::ggFrame( wxSharedPtr<wxFileConfig>& configFile )
    : wxFrame( nullptr, -1, g_program_name, wxPoint(-1, -1), wxSize(500, 400))
    , mOglCanvas( nullptr )
    , mOglContext( nullptr )
    , mConfigFile( configFile )
    , mPropGrid( nullptr )
{          
    static int glFlags[] = {
        WX_GL_RGBA,
        WX_GL_DOUBLEBUFFER,
        WX_GL_DEPTH_SIZE, 24,
        0
    };    

    wxBoxSizer *topSizer = new wxBoxSizer(wxHORIZONTAL);

    mOglCanvas = new wxGLCanvas( this, wxID_ANY, glFlags, wxDefaultPosition, wxSize(500,400) );
    mOglContext = new wxGLContext( mOglCanvas );
    mOglContext->SetCurrent(*mOglCanvas);
    topSizer->Add(mOglCanvas, 1, wxEXPAND);

    if(glewInit() != GLEW_OK) 
        abort();   


    mPropGrid = new wxPropertyGrid( this, wxID_ANY, wxDefaultPosition, wxSize(300, 400), wxPG_NO_INTERNAL_BORDER );
    BuildPropertyGrid();
    topSizer->Add(mPropGrid, 0, wxEXPAND);
    Connect( wxEVT_PG_CHANGED, wxPropertyGridEventHandler(ggFrame::OnPropChange) );

    SetSizerAndFit( topSizer );

    Connect( wxEVT_SIZE, wxSizeEventHandler(ggFrame::OnResize) );
    SetExtraStyle(wxWS_EX_PROCESS_IDLE);
    wxIdleEvent::SetMode(wxIDLE_PROCESS_SPECIFIED);
    Connect( wxEVT_IDLE, wxIdleEventHandler(ggFrame::OnIdle) );
    Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler(ggFrame::OnClose));

    BuildMenu();

    Show();

    wxRect windowSize;
    windowSize.SetWidth( mConfigFile->ReadLong(g_window_width_str, 500) );
    windowSize.SetHeight( mConfigFile->ReadLong(g_window_height_str, 400) );
    windowSize.SetLeft( mConfigFile->ReadLong(g_window_x_str, -1) );
    windowSize.SetBottom( mConfigFile->ReadLong(g_window_y_str, -1) );
    
    SetSize(windowSize);
}

ggFrame::~ggFrame()
{
}

void ggFrame::Update()
{
    // clear the buffer
    mGL.ClearColor(
        mConfigFile->ReadDouble(prop_camera_clear + "." + prop_camera_clear_red, 0.0),
        mConfigFile->ReadDouble(prop_camera_clear + "." + prop_camera_clear_green, 0.0),
        mConfigFile->ReadDouble(prop_camera_clear + "." + prop_camera_clear_blue, 0.0),
        mConfigFile->ReadDouble(prop_camera_clear + "." + prop_camera_clear_alpha, 0.0)
    );
    mGL.Clear().ColorBuffer();

    // set the projection up
    oglplus::CamMatrixf camera = oglplus::CamMatrixf::Perspective(
        mConfigFile->ReadDouble(prop_camera_proj + "." + prop_camera_proj_left, -1.0),
        mConfigFile->ReadDouble(prop_camera_proj + "." + prop_camera_proj_right, 1.0),
        mConfigFile->ReadDouble(prop_camera_proj + "." + prop_camera_proj_bottom, -1.0),
        mConfigFile->ReadDouble(prop_camera_proj + "." + prop_camera_proj_top, 1.0),
        mConfigFile->ReadDouble(prop_camera_proj + "." + prop_camera_proj_near, 1.0),
        mConfigFile->ReadDouble(prop_camera_proj + "." + prop_camera_proj_far, 10.0)
    );
    
    mOglCanvas->SwapBuffers();
}

void ggFrame::OnIdle(wxIdleEvent& evnt)
{
    Update();
    evnt.RequestMore();
}

void ggFrame::OnResize(wxSizeEvent& evnt)
{
    int w, h, x, y;
    wxRect rect = evnt.GetRect();
    y = rect.GetBottom();
    x = rect.GetLeft();
    h = rect.GetHeight();
    w = rect.GetWidth();
    mGL.Viewport( x, y, w, h );
    evnt.Skip();
}

void ggFrame::OnCommand(wxCommandEvent& evnt)
{    
    if( evnt.GetId() == wxID_EXIT )
    {
        Close(false);
    }
}

void ggFrame::OnClose(wxCloseEvent& evnt)
{
    UpdateConfig();
    Destroy();
}

void ggFrame::OnPropChange(wxPropertyGridEvent& evnt)
{
    mConfigFile->Write(evnt.GetPropertyName(), evnt.GetPropertyValue().GetReal());
    mConfigFile->Flush(); 
}

void ggFrame::BuildMenu()
{
    wxMenuBar *menuBar = new wxMenuBar();
    wxMenu* fileMenu = new wxMenu();
    fileMenu->Append(wxID_EXIT, wxT("&Quit"));
    menuBar->Append(fileMenu, wxT("&File"));
    SetMenuBar(menuBar);

    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,
        wxCommandEventHandler(ggFrame::OnCommand));
}

void ggFrame::UpdateConfig()
{
    wxRect windowSize = GetRect();
    mConfigFile->Write(g_window_width_str, windowSize.GetWidth());
    mConfigFile->Write(g_window_height_str, windowSize.GetHeight());
    mConfigFile->Write(g_window_x_str, windowSize.GetLeft());
    mConfigFile->Write(g_window_y_str, windowSize.GetBottom());
    mConfigFile->Flush();    
}

void ggFrame::BuildPropertyGrid()
{
    mPropGrid->EnableCategories(true);
    wxPGProperty *cameraProp = mPropGrid->Append( new wxPropertyCategory("Camera"));
    

    wxPGProperty *projMat = mPropGrid->AppendIn( cameraProp, new wxStringProperty(prop_camera_proj, wxPG_LABEL, "<composed>"));
    mPropGrid->AppendIn( projMat, new wxFloatProperty(prop_camera_proj_left, wxPG_LABEL, mConfigFile->ReadDouble(prop_camera_proj + "." + prop_camera_proj_left, -1.0)));
    mPropGrid->AppendIn( projMat, new wxFloatProperty(prop_camera_proj_right, wxPG_LABEL, mConfigFile->ReadDouble(prop_camera_proj + "." + prop_camera_proj_right, 1.0)));
    mPropGrid->AppendIn( projMat, new wxFloatProperty(prop_camera_proj_bottom, wxPG_LABEL, mConfigFile->ReadDouble(prop_camera_proj + "." + prop_camera_proj_bottom, -1.0)));
    mPropGrid->AppendIn( projMat, new wxFloatProperty(prop_camera_proj_top, wxPG_LABEL, mConfigFile->ReadDouble(prop_camera_proj + "." + prop_camera_proj_top, 1.0)));
    mPropGrid->AppendIn( projMat, new wxFloatProperty(prop_camera_proj_near, wxPG_LABEL, mConfigFile->ReadDouble(prop_camera_proj + "." + prop_camera_proj_near, 1.0)));
    mPropGrid->AppendIn( projMat, new wxFloatProperty(prop_camera_proj_far, wxPG_LABEL, mConfigFile->ReadDouble(prop_camera_proj + "." + prop_camera_proj_far, 10.0)));
    
    wxPGProperty *clearColor = mPropGrid->AppendIn( cameraProp, new wxStringProperty(prop_camera_clear, wxPG_LABEL, "<composed>"));
    mPropGrid->AppendIn( clearColor, new wxFloatProperty(prop_camera_clear_red, wxPG_LABEL, mConfigFile->ReadDouble(prop_camera_clear + "." + prop_camera_clear_red, 0.0)));
    mPropGrid->AppendIn( clearColor, new wxFloatProperty(prop_camera_clear_green, wxPG_LABEL, mConfigFile->ReadDouble(prop_camera_clear + "." + prop_camera_clear_green, 0.0)));
    mPropGrid->AppendIn( clearColor, new wxFloatProperty(prop_camera_clear_blue, wxPG_LABEL, mConfigFile->ReadDouble(prop_camera_clear + "." + prop_camera_clear_blue, 0.0)));
    mPropGrid->AppendIn( clearColor, new wxFloatProperty(prop_camera_clear_alpha, wxPG_LABEL, mConfigFile->ReadDouble(prop_camera_clear + "." + prop_camera_clear_alpha, 0.0)));
}