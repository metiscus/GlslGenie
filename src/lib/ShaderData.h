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

#ifndef SHADER_CPP_PRIVATE
#error Do not include this file directly, include Shader.h instead.
#endif

#pragma once

#include <GL/glew.h>
#include <oglplus/all.hpp>

#include <string>
#include <fstream>

#include "ObjectData.h"


class ShaderData 
    : public ObjectData
    , public ObjectPropertyCallbackInterface
{
public:
    ShaderData();
    virtual ~ShaderData();
    virtual void ClearData();
    virtual bool LoadFromFile( std::ifstream& filename );
    virtual bool WriteToFile( std::ofstream& filename );
    virtual PropertyBindingList GetProperties();
    virtual void DataChanged( ObjectPropertyBinding *ptr );

    oglplus::Shader *mShader;

private:
    std::string mFilename;
    ObjectPropertyBinding mFilenameBinding;

    GenericData mShaderType;
    ObjectPropertyBinding mShaderTypeBinding;
};