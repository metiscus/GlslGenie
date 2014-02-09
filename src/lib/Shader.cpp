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

#include <sstream>

#include "Object.h"
#include "ObjectData.h"
#include "ObjectPropertyBinding.h"
#include "GenericData.h"

#include <oglplus/all.hpp>

#include "Shader.h"
#define SHADER_CPP_PRIVATE
#include "ShaderData.h"

Shader::Shader()
    : Object( new ShaderData() )
{
    std::stringstream ss;
    ss<<"Shader("<<GetId()<<")";

    SetName(ss.str());
}

ShaderData* Shader::GetData()
{
    return (ShaderData*)Object::GetData();
}
