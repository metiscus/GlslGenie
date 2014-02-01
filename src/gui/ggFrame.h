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

#include <wx/wx.h>
#include <wx/glcanvas.h>
#include <wx/sharedptr.h>
#include <wx/fileconf.h>

class ggFrame : public wxFrame
{
public:
    ggFrame( wxSharedPtr<wxFileConfig>& configFile );
    virtual ~ggFrame();

    virtual void Update();
    virtual void OnIdle(wxIdleEvent& evnt);
    virtual void OnResize(wxSizeEvent& evnt);
    virtual void OnQuit(wxCommandEvent& evnt);

private:
    wxPanel *mOglPanel;
    wxPanel *mCommandPanel;
    wxGLCanvas *mOglCanvas;
    wxGLContext *mOglContext;
    oglplus::Context mGL;
    wxSharedPtr<wxFileConfig> mConfigFile;

    void BuildMenu();
    void ReadConfig();
};