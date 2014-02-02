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
#include <wx/filedlg.h>

#include "ggEditor.h"
#include "ggGlobals.h"

static const wxString g_editor_title = "GLSL Editor: ";

ggEditor::ggEditor( wxSharedPtr<wxFileConfig>& configFile )
    : wxFrame( nullptr, -1, g_program_name, wxPoint(-1, -1), wxSize(500, 400))
    , mTextControl( nullptr )
    , mIsNew( true )
    , mFilename( "" )
{          
    SetTitle(g_editor_title);

    mTextControl = new wxStyledTextCtrl( this );

    wxMenuBar *menuBar = new wxMenuBar();
    wxMenu* fileMenu = new wxMenu();
    fileMenu->Append(wxID_NEW, wxT("&New"));
    fileMenu->Append(wxID_OPEN, wxT("&Open"));
    fileMenu->Append(wxID_SAVE, wxT("&Save"));
    fileMenu->Append(wxID_EXIT, wxT("&Quit"));
    menuBar->Append(fileMenu, wxT("&File"));
    
    SetMenuBar(menuBar);

    Connect(wxID_NEW, wxEVT_COMMAND_MENU_SELECTED,
        wxCommandEventHandler(ggEditor::OnCommand));
    Connect(wxID_OPEN, wxEVT_COMMAND_MENU_SELECTED,
        wxCommandEventHandler(ggEditor::OnCommand));    
    Connect(wxID_SAVE, wxEVT_COMMAND_MENU_SELECTED,
        wxCommandEventHandler(ggEditor::OnCommand));
    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,
        wxCommandEventHandler(ggEditor::OnCommand));
}

ggEditor::~ggEditor()
{
}


void ggEditor::OnCommand(wxCommandEvent& evnt)
{    
    if( evnt.GetId() == wxID_NEW )
    {
        mTextControl->ClearAll();
        mIsNew = true;
        mFilename = "";
    }
    else if( evnt.GetId() == wxID_SAVE )
    {
        if ( mIsNew )
        {
            wxFileDialog openFileDialog(this, wxT("Select Filename"), wxString(""), mFilename, wxString("*.*"), wxFD_SAVE | wxFD_OVERWRITE_PROMPT);
            if (openFileDialog.ShowModal() == wxID_CANCEL)
            {
                return;
            }
            else
            {
                mFilename = openFileDialog.GetFilename();
            }
        }

        mTextControl->SaveFile( mFilename );
        mIsNew = false;
    }
    else if( evnt.GetId() == wxID_OPEN )
    {
        wxFileDialog openFileDialog(this, wxT("Select Filename"));
        if (openFileDialog.ShowModal() == wxID_CANCEL)
        {
            return;
        }
        else
        {
            mFilename = openFileDialog.GetFilename();
            mTextControl->LoadFile(mFilename);
            mIsNew = false;
        }
    }
    else if( evnt.GetId() == wxID_EXIT )
    {
        Close(false);
    }

    SetTitle(g_editor_title+ mFilename);
}

void ggEditor::OnClose(wxCloseEvent& evnt)
{

}