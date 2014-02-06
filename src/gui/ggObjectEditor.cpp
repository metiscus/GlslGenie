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
#include "../lib/Object.h"
#include "ggObjectEditor.h"

class Object;

ggObjectEditor::ggObjectEditor( wxSharedPtr<wxFileConfig>& configFile )
    : wxFrame( nullptr, -1, wxT("Object Editor"), wxPoint(-1, -1), wxSize(500, 400))
    , mObjectList( nullptr )
{
    wxBoxSizer *topSizer = new wxBoxSizer(wxHORIZONTAL);
    mObjectList = new wxListBox(this, wxID_ANY, wxPoint(-1, -1), wxSize(200, 400));
    topSizer->Add(mObjectList, 1, wxEXPAND);
    mPropGrid = new wxPropertyGrid(this, wxID_ANY, wxPoint(-1, -1), wxSize(300, 400));
    topSizer->Add(mPropGrid, 1, wxEXPAND);
    SetSizer(topSizer);

    Show();

    objectlist_t objectList = Object::GetObjectLists();

    for( int ii=0; ii<objectList.size(); ++ii )
    {
        Object *pObject = objectList[ii];
        
        wxString name = wxString(pObject->GetName());
        mPropGrid->Clear();
        wxPGProperty *objProp = mPropGrid->Append( new wxPropertyCategory(name) );
        PropertyBindingList properties = pObject->GetProperties();
        for( int ii=0; ii<properties.size(); ++ii )
        {
            wxStringProperty *pProperty = new wxStringProperty(properties[ii]->GetName(), wxPG_LABEL, wxString(properties[ii]->GetValue()));
            mPropGrid->AppendIn( objProp, pProperty);
        }

        wxString itemLabel(pObject->GetName());
        mObjectList->Insert( itemLabel, 0, pObject );
    }

}

ggObjectEditor::~ggObjectEditor()
{

}

void ggObjectEditor::OnIdle(wxIdleEvent& evnt)
{

}

void ggObjectEditor::OnResize(wxSizeEvent& evnt)
{

}

void ggObjectEditor::OnCommand(wxCommandEvent& evnt)
{

}

void ggObjectEditor::OnClose(wxCloseEvent& evnt)
{

}

void ggObjectEditor::OnPropChange(wxPropertyGridEvent& evnt)
{

}
