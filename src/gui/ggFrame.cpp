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
#include <Windows.h>
#include <vector>
#include <string>

ggFrame::ggFrame() 
    : wxFrame( nullptr, -1, wxString("Unknown Devices 2.0.0"), wxPoint(-1, -1), wxSize(500, 400))
    , mGLFrame( nullptr )
{    
    mGLFrame = new ggGLFrame(this);
    
    Show();
}

ggFrame::~ggFrame()
{

}