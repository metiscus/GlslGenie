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

#include "GenericData.h"

#include <sstream>

#include "Object.h"
#include "ObjectData.h"
#include "ObjectPropertyBinding.h"
#include "GenericData.h"

#include <oglplus/all.hpp>

#include "Shader.h"

class ShaderData 
    : public ObjectData
    , public ObjectPropertyCallbackInterface
{
public:
    ShaderData() 
        : mFilenameBinding( "Filename", ObjectPropertyBinding::STRING, this )
        , mShaderType(GenericData::INT)
        , mShaderTypeBinding( "Type(0:frag, 1:vert)", ObjectPropertyBinding::INT, this )
        , mShader( nullptr )
    {
        mFilenameBinding.Bind( &mFilename );
        mShaderTypeBinding.Bind( &mShaderType );
    }

    virtual ~ShaderData()
    {
        ;
    }

    virtual void ClearData()
    {

    }

    virtual bool LoadFromFile( std::ifstream& filename )
    {
        return false;
    }

    virtual bool WriteToFile( std::ofstream& filename )
    {
        return false;
    }

    virtual PropertyBindingList GetProperties()
    {
        PropertyBindingList ret;
        ret.push_back(&mFilenameBinding);
        ret.push_back(&mShaderTypeBinding);
        return ret;
    }

    virtual void DataChanged( ObjectPropertyBinding *ptr )
    {
        if( ptr == &mFilenameBinding )
        {

        }
        else if (ptr == &mShaderTypeBinding)
        {
            if( mShader )
                delete mShader;
            
            if( mShaderTypeBinding.GetValue() == "0" )
            {
                mShader = new oglplus::FragmentShader();
                //mShader->Source()
            }
            else if ( mShaderTypeBinding.GetValue() == "1" )
            {
                mShader = new oglplus::VertexShader();
            }

            if( mShader )
            {

            }
        }
    }

private:
    std::string mFilename;
    ObjectPropertyBinding mFilenameBinding;

    GenericData mShaderType;
    ObjectPropertyBinding mShaderTypeBinding;

    oglplus::Shader *mShader;
};

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