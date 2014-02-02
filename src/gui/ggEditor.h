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

#include <wx/wx.h>
#include <wx/sharedptr.h>
#include <wx/fileconf.h>
#include <wx/stc/stc.h>

class ggEditor : public wxFrame
{
public:
    ggEditor( wxSharedPtr<wxFileConfig>& configFile );
    virtual ~ggEditor();

    virtual void OnCommand(wxCommandEvent& evnt);
    virtual void OnClose(wxCloseEvent& evnt);

private:
    bool mIsNew;
    wxString mFilename;
    wxStyledTextCtrl *mTextControl;
};