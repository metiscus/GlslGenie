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

#include <GL/glew.h>

#include <vector>
#include <sstream>

#include "Object.h"
#include "ObjectData.h"
#include "ObjectPropertyBinding.h"
#include "GenericData.h"

#include <oglplus/all.hpp>

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

class VertexDataData
    : public ObjectData
    , public ObjectPropertyCallbackInterface
{
public:
    VertexDataData() 
        : mFilenameBinding( "Filename", ObjectPropertyBinding::STRING, this )
        , mBufferType(GenericData::INT)
        , mBufferTypeBinding( "Type(0:vert, 1:color, 2:normal)", ObjectPropertyBinding::INT, this )
        , mVerts( nullptr )
    {
        mFilenameBinding.Bind( &mFilename );
        mBufferTypeBinding.Bind( &mBufferType );
    }

private:
    oglplus::Buffer *mVerts;

    std::string mFilename;
    ObjectPropertyBinding mFilenameBinding;
    
    GenericData mBufferType;
    ObjectPropertyBinding mBufferTypeBinding;
};

class VertexData : public Object
{
public:
    virtual VertexDataData* GetData();
};