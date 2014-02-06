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

#include <map>
#include <vector>
#include <string>

class Object;
class ObjectData;

typedef int guid_t;
typedef std::vector<guid_t> guidlist_t;
typedef std::vector<Object*> objectlist_t;
typedef std::map<guid_t, Object*> objectmap_t;

#include "ObjectPropertyBinding.h"

class Object
{
public:
    static Object* LookupObject( guid_t id );
    static objectlist_t GetObjectLists();
    Object( ObjectData *data );
    virtual ~Object();
    virtual bool LoadFromFile( const std::string& filename );
    virtual bool WriteToFile( const std::string& filename );
    void SetName( const std::string& name );
    const std::string& GetName() const;

    guid_t GetId();

    PropertyBindingList GetProperties();

protected:
    ObjectData* GetData();

    PropertyBindingList mPropertyBindings;

private:
    guid_t mId;
    static guid_t s_mId;
    std::string mName;
    ObjectData *mData;

    static objectmap_t s_mObjectMap;
};