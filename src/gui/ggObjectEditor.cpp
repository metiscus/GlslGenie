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
#include "../lib/All.h"
#include "../lib/Object.h"
#include "../lib/ObjectData.h"
#include "ggFrame.h"
#include "ggObjectEditor.h"
#include <cassert>

class Object;

enum {
    ggID_CREATE_TEXTURE = 1,
    ggID_CREATE_SHADER  = 2,
    ggID_CREATE_PROGRAM = 3,
    ggID_CREATE_UNIFORM = 4,
};

ggObjectEditor::ggObjectEditor( ggFrame* parent, wxSharedPtr<wxFileConfig>& configFile )
    : wxFrame( nullptr, -1, wxT("Object Editor"), wxPoint(-1, -1), wxSize(500, 400))
    , mObjectList( nullptr )
    , mParent( parent )
{
    wxBoxSizer *topSizer = new wxBoxSizer(wxHORIZONTAL);
    mObjectList = new wxListBox(this, wxID_ANY, wxPoint(-1, -1), wxSize(200, 400));
    topSizer->Add(mObjectList, 1, wxEXPAND);
    mPropGrid = new wxPropertyGrid(this, wxID_ANY, wxPoint(-1, -1), wxSize(300, 400));
    topSizer->Add(mPropGrid, 1, wxEXPAND);
    SetSizer(topSizer);

    objectlist_t objectList = Object::GetObjectLists();

    for( int ii=0; ii<objectList.size(); ++ii )
    {
        Object *pObject = objectList[ii];

        wxString itemLabel(pObject->GetName());
        mObjectList->Insert( itemLabel, 0, pObject );
    }

    Connect( wxEVT_CLOSE_WINDOW, wxCloseEventHandler(ggObjectEditor::OnClose));
    Connect(wxEVT_COMMAND_LISTBOX_SELECTED, wxCommandEventHandler(ggObjectEditor::OnListBoxClick));
    Connect( wxEVT_PG_CHANGED, wxPropertyGridEventHandler(ggObjectEditor::OnPropChange) );

    BuildMenu();
}

ggObjectEditor::~ggObjectEditor()
{


}

void ggObjectEditor::OnListBoxClick(wxCommandEvent& evnt)
{
    UpdateObjects();
}

void ggObjectEditor::OnCommand(wxCommandEvent& evnt)
{
    switch (evnt.GetId())
    {
    case wxID_EXIT:
        {
            evnt.Skip();
            mParent->ToggleObjectEditor();
            break;
        }
    case ggID_CREATE_TEXTURE:
        {
            Texture *texture = new Texture();
            break;
        }
    case ggID_CREATE_SHADER:
        {
            UpdateObjects();           
            break;
        }
    case ggID_CREATE_PROGRAM:
        {
            UpdateObjects();           
            break;
        }
    case ggID_CREATE_UNIFORM:
        {
            UpdateObjects();           
            break;
        }
    }

    UpdateObjects();
}

void ggObjectEditor::OnClose(wxCloseEvent& evnt)
{
    evnt.Veto();
    mParent->ToggleObjectEditor();
}

void ggObjectEditor::OnPropChange(wxPropertyGridEvent& evnt)
{
    int selectedIndex = mObjectList->GetSelection();
    assert( selectedIndex >= 0 );
    if ( selectedIndex >= 0 )
    {
        wxString propName  = evnt.GetPropertyName();
        wxString propValue = evnt.GetPropertyValue().GetString();
        
        Object* pObject = (Object*)mObjectList->GetClientData(selectedIndex);
        assert(pObject);
        if ( pObject )
        {
            PropertyBindingList properties = pObject->GetProperties();
            bool foundIt = false;
            for( int ii=0; ii<properties.size(); ++ii )
            {
                if ( wxString(properties[ii]->GetName()) == propName )
                {
                    properties[ii]->SetValue(propValue.c_str().AsChar());
                    foundIt = true;
                    break;
                }
            }
            assert(foundIt);
        }
    }
}

void ggObjectEditor::UpdateObjects()
{
    int selectedIndex = mObjectList->GetSelection();
    if ( selectedIndex == -1 )
    {
        return;
    }

    Object* pObject = (Object*)mObjectList->GetClientData(selectedIndex);
    if ( pObject )
    {
        mPropGrid->Clear();
        wxString name = wxString(pObject->GetName());
        wxPGProperty *objProp = mPropGrid->Append( new wxPropertyCategory(name) );
        PropertyBindingList properties = pObject->GetProperties();
        for( int ii=0; ii<properties.size(); ++ii )
        {
            wxStringProperty *pProperty = new wxStringProperty(properties[ii]->GetName(), wxPG_LABEL, wxString(properties[ii]->GetValue()));
            mPropGrid->AppendIn( objProp, pProperty);
        }
    }
}

void ggObjectEditor::BuildMenu()
{
    wxMenuBar *menuBar = new wxMenuBar();
    wxMenu* fileMenu = new wxMenu();
    fileMenu->Append(wxID_EXIT, wxT("&Quit"));
    Connect(wxID_EXIT, wxEVT_COMMAND_MENU_SELECTED,
        wxCommandEventHandler(ggFrame::OnCommand));
    menuBar->Append(fileMenu, wxT("&File"));
    
    wxMenu* objMenu = new wxMenu();
    objMenu->Append(ggID_CREATE_TEXTURE, wxT("New Texture"));
    objMenu->Append(ggID_CREATE_SHADER, wxT("New Shader"));
    objMenu->Append(ggID_CREATE_PROGRAM, wxT("New Program"));
    objMenu->Append(ggID_CREATE_UNIFORM, wxT("New Uniform"));
    Connect(wxID_EXIT, ggID_CREATE_TEXTURE,
        wxCommandEventHandler(ggFrame::OnCommand));
    Connect(wxID_EXIT, ggID_CREATE_SHADER,
        wxCommandEventHandler(ggFrame::OnCommand));
    Connect(wxID_EXIT, ggID_CREATE_PROGRAM,
        wxCommandEventHandler(ggFrame::OnCommand));
    Connect(wxID_EXIT, ggID_CREATE_UNIFORM,
        wxCommandEventHandler(ggFrame::OnCommand));
    menuBar->Append(objMenu, wxT("Objects"));    


    SetMenuBar(menuBar);
}