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

#include <fstream>
#include <string>

#include "ObjectData.h"
#include "Object.h"

#include "ObjectPropertyBinding.h"

/* Static Members */
//////////////////////////////////////////////
guid_t Object::s_mId = 0;
objectmap_t Object::s_mObjectMap;

/* Static Functions */
//////////////////////////////////////////////
Object* Object::LookupObject( guid_t guid )
{
    objectmap_t::const_iterator itr = s_mObjectMap.find(guid);
    if( itr != s_mObjectMap.end() )
        return itr->second;
    else
        return nullptr;
}

objectlist_t Object::GetObjectLists()
{
    objectlist_t ret;
    objectmap_t::const_iterator beg = s_mObjectMap.begin();
    for( ; beg!=s_mObjectMap.end(); ++beg )
    {
        ret.push_back(beg->second);
    }
    return ret;
}

/* Member Functions */
//////////////////////////////////////////////
Object::Object(ObjectData *data) : mData( data )
{
    mId = s_mId++;
    s_mObjectMap[mId] = this;

    PropertyBindingList dataList = mData->GetProperties();
    for( int ii =0; ii < dataList.size(); ++ii )
    {
        mPropertyBindings.push_back(dataList[ii]);
    }
}

Object::~Object()
{
    delete mData;
    s_mObjectMap.erase(mId);
}

guid_t Object::GetId()
{
    return mId;
}

ObjectData* Object::GetData() 
{
    return mData;
}

bool Object::LoadFromFile( const std::string& filename )
{
    if( mData )
    {
        std::ifstream infile ( filename.c_str() );
        infile >> mName; 
        mData->ClearData();
        return mData->LoadFromFile(infile);
    }

    return false;
}

bool Object::WriteToFile( const std::string& filename )
{
    if( mData )
    {
        std::ofstream outFile( filename.c_str() );
        outFile << mName;
        bool ret = mData->WriteToFile(outFile);
        outFile.close();
        return ret;
    }

    return false;
}

void Object::SetName( const std::string& name )
{
    mName = name;
}

const std::string& Object::GetName() const
{
    return mName;
}

PropertyBindingList Object::GetProperties()
{
    return mPropertyBindings;
}