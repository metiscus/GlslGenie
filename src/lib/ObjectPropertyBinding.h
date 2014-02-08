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

#include "..\lib\GenericData.h"
#include <vector>

class ObjectPropertyBinding;

typedef std::vector<ObjectPropertyBinding*> PropertyBindingList;

class ObjectPropertyCallbackInterface
{
public:
    virtual void DataChanged( ObjectPropertyBinding *ptr ) = 0;
};

class ObjectPropertyBinding
{
public:
    enum BindingType { STRING, INT, FLOAT, VEC2, VEC3, VEC4 }; // these should match GenericData.h with the exception of INVALID == STRING
    ObjectPropertyBinding( const std::string& name, BindingType type, ObjectPropertyCallbackInterface *callback = nullptr );
    std::string GetName();
    BindingType GetType();
    void SetValue( const std::string& value );
    void Bind( std::string *data );
    void Bind( GenericData *data );
    std::string GetValue();

private:
    BindingType mType;
    std::string mName;
    std::string *mStringData;
    GenericData *mData;
    ObjectPropertyCallbackInterface *mCallback;
};