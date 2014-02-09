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
#define SHADER_CPP_PRIVATE

#include "Shader.h"
#include "ShaderData.h"

static std::string FileToString( const std::string& filename )
{
    std::string ret;
    std::ifstream infile(filename.c_str());
    while( infile.is_open() && ! infile.eof() )
    {
        std::string line;
        std::getline(infile, line);
        ret += line + "\n";
    }
    infile.close();
    return ret;
}

ShaderData::ShaderData() 
    : mFilenameBinding( "Filename", ObjectPropertyBinding::STRING, this )
    , mShaderType(GenericData::INT)
    , mShaderTypeBinding( "Type(0:frag, 1:vert)", ObjectPropertyBinding::INT, this )
    , mShader( nullptr )
{
    mFilenameBinding.Bind( &mFilename );
    mShaderTypeBinding.Bind( &mShaderType );
}

ShaderData::~ShaderData()
{
    ;
}

void ShaderData::ClearData()
{

}

bool ShaderData::LoadFromFile( std::ifstream& filename )
{
    return false;
}

bool ShaderData::WriteToFile( std::ofstream& filename )
{
    return false;
}

PropertyBindingList ShaderData::GetProperties()
{
    PropertyBindingList ret;
    ret.push_back(&mFilenameBinding);
    ret.push_back(&mShaderTypeBinding);
    return ret;
}

void ShaderData::DataChanged( ObjectPropertyBinding *ptr )
{
    if( ptr == &mFilenameBinding || ptr == &mShaderTypeBinding )
    {
        if( mShader )
        {
            delete mShader;
            mShader = nullptr;
        }

        if( mShaderTypeBinding.GetValue() == "0" )
        {
            mShader = new oglplus::FragmentShader();
            mShader->Source( FileToString( mFilename.c_str()) );
        }
        else if ( mShaderTypeBinding.GetValue() == "1" )
        {
            mShader = new oglplus::VertexShader();
            mShader->Source( FileToString(mFilename.c_str()) );
        }

        if( mShader != nullptr )
        {
            mShader->Compile();
        }
    }
}