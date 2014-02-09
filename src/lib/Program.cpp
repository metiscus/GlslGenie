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

#include <vector>
#include <sstream>

#include "Object.h"
#include "ObjectData.h"
#include "ObjectPropertyBinding.h"
#include "GenericData.h"

#include <oglplus/all.hpp>

#include "Program.h"
#include "Shader.h"
#define SHADER_CPP_PRIVATE
#include "ShaderData.h"

class ProgramData 
    : public ObjectData
    , public ObjectPropertyCallbackInterface
{
public:
    ProgramData() 
        : mProgram( nullptr )
        , mVertexShaderId( GenericData::INT )
        , mVertexShaderBinding( "Vertex Shader", ObjectPropertyBinding::INT, this )
        , mFragmentShaderId( GenericData::INT )
        , mFragmentShaderBinding( "Fragment Shader", ObjectPropertyBinding::INT, this )
    {
        mProgram = new oglplus::Program();
        mVertexShaderBinding.Bind( &mVertexShaderId );
        mFragmentShaderBinding.Bind( &mFragmentShaderId );
    }

    virtual ~ProgramData()
    {
        delete mProgram;
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
        ret.push_back(&mVertexShaderBinding);
        ret.push_back(&mFragmentShaderBinding);
        return ret;
    }

    virtual void DataChanged( ObjectPropertyBinding *ptr )
    {
        guid_t shaderObjectId = Object::InvalidGuid;
        if( ptr == &mVertexShaderBinding )
        {
            mVertexShaderId.GetData( shaderObjectId );
        }
        else if ( ptr == &mFragmentShaderBinding )
        {
            mFragmentShaderId.GetData( shaderObjectId );
        }

        if( shaderObjectId != Object::InvalidGuid )
        {
            Shader *pShader = dynamic_cast<Shader*>(Object::LookupObject(shaderObjectId));
            if( pShader && mProgram )
            {
                if( pShader->GetData()->mShader != nullptr )
                {
                    mProgram->AttachShader( *(pShader->GetData()->mShader) );
                    try {
                        mProgram->Link();
                        mProgram->Use();
                    }
                    catch(...)
                    {
                        assert(false);
                    }
                }
            }
        }
    }

private:
    GenericData mVertexShaderId;
    ObjectPropertyBinding mVertexShaderBinding;

    GenericData mFragmentShaderId;
    ObjectPropertyBinding mFragmentShaderBinding;

    oglplus::Program *mProgram;

    std::vector<guid_t> mBoundUniforms;
};

Program::Program( )
    : Object( new ProgramData() )
{
    std::stringstream ss;
    ss<<"Program("<<GetId()<<")";

    SetName(ss.str());
}

ProgramData* Program::GetData()
{
    return (ProgramData*)Object::GetData();
}

/*
const guidlist_t& GetShaders() const;
const guidlist_t& GetUniforms() const;
void AddShader(guid_t shader);
void AddUniform(guid_t uniform);
void AddVertexData(guid_t verts);
*/