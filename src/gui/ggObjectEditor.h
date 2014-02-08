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
#pragma once

#include <GL/glew.h>
#include <oglplus/all.hpp>

#include <map>

#include <wx/wx.h>
#include <wx/variant.h>
#include <wx/glcanvas.h>
#include <wx/sharedptr.h>
#include <wx/fileconf.h>
#include <wx/propgrid/propgrid.h>

class Object;
class ggFrame;

class ggObjectEditor : public wxFrame
{
public:
    ggObjectEditor( ggFrame* parent, wxSharedPtr<wxFileConfig>& configFile );
    virtual ~ggObjectEditor();

    virtual void OnCommand(wxCommandEvent& evnt);
    virtual void OnListBoxClick(wxCommandEvent& evnt);
    virtual void OnClose(wxCloseEvent& evnt);
    virtual void OnPropChange(wxPropertyGridEvent& evnt);
    void UpdateObjects();
    void BuildMenu();

protected:
    void AddObjectToList(Object* object);
    void MakeObjectCurrent(Object* object);

private:
    wxSharedPtr<wxFileConfig> mConfigFile;
    wxPropertyGrid *mPropGrid;
    wxListBox *mObjectList;
    wxStatusBar *mStatusBar;
    ggFrame *mParent;
};