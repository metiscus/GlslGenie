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

#include "GenericData.h"

#include <sstream>

#include "Object.h"
#include "ObjectData.h"
#include "ObjectPropertyBinding.h"

#include "Texture.h"

class TextureData : public ObjectData
{
public:
    TextureData() 
        : mFilenameBinding( "Filename", ObjectPropertyBinding::STRING )
        , mTextureUnit(GenericData::INT)
        , mTextureUnitBinding( "Texture Unit", ObjectPropertyBinding::INT )
    {
        mFilenameBinding.Bind( &mFilename );
        mTextureUnitBinding.Bind( &mTextureUnit );
    }

    virtual ~TextureData()
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
        ret.push_back(&mTextureUnitBinding);
        return ret;
    }

private:
    std::string mFilename;
    ObjectPropertyBinding mFilenameBinding;

    GenericData mTextureUnit;
    ObjectPropertyBinding mTextureUnitBinding;
};

Texture::Texture()
    : Object( new TextureData() )
{
    std::stringstream ss;
    ss<<"Texture("<<GetId()<<")";

    SetName(ss.str());
}

 TextureData* Texture::GetData()
 {
     return (TextureData*)Object::GetData();
 }