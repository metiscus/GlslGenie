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
#include "ggGLFrame.h"
#include <Windows.h>
#include <vector>
#include <string>

ggGLFrame::ggGLFrame( wxFrame* parent )
    : wxFrame( parent, -1, wxString("Unknown Devices 2.0.0"), wxPoint(-1, -1), wxSize(500, 400))
    , mGLCanvas( nullptr )
    , mGLContext( nullptr )
{    
    static int conf[] = {
        WX_GL_RGBA,
        WX_GL_DOUBLEBUFFER,
        WX_GL_DEPTH_SIZE, 24,
        0
    };
    mGLCanvas = new wxGLCanvas( this, wxID_ANY, conf, wxDefaultPosition, wxSize(-1, -1) );
    mGLContext = new wxGLContext( mGLCanvas );
}

ggGLFrame::~ggGLFrame()
{

}

void ggGLFrame::Update()
{

}

void ggGLFrame::OnIdle(wxIdleEvent& evnt)
{


}

void ggGLFrame::OnResize(wxSizeEvent& evnt)
{

}