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

#include <sstream>

#include "ObjectPropertyBinding.h"

ObjectPropertyBinding::ObjectPropertyBinding( const std::string& name, BindingType type, ObjectPropertyCallbackInterface *callback )
    : mName( name )
    , mType( type )
    , mStringData( nullptr )
    , mData( nullptr )
    , mCallback( callback )
{

}

std::string ObjectPropertyBinding::GetName()
{
    return mName;
}

ObjectPropertyBinding::BindingType ObjectPropertyBinding::GetType()
{
    return mType;
}

std::string ObjectPropertyBinding::GetValue()
{
    if( mStringData )
    {
        return *mStringData;
    }
    else if( mData ) 
    {
        std::stringstream ss;
        for( int ii=0; ii<mData->GetNumComponents(); ++ii )
        {
            ss<<mData->GetComponent(ii);
        }
        return ss.str();
    }
    else
    {
        return "";
    }
}

void ObjectPropertyBinding::SetValue( const std::string& value )
{
    if( mStringData == nullptr && mData == nullptr )
        return;

    switch(mType)
    {
    case STRING:
        *mStringData = value;
        break;

    case INT:
        {
            std::stringstream ss(value);
            int val;
            ss >> val;
            mData->SetData(val);
        }
        break;
    case FLOAT:
        {
            std::stringstream ss(value);
            float x;
            ss >> x;
            mData->SetData(x);
        }
        break;
    case VEC2:
        {
            std::stringstream ss(value);
            float x, y;
            ss >> x;
            ss >> y;
            mData->SetData(x, y);
        }
        break;
    case VEC3:
        {
            std::stringstream ss(value);
            float x, y, z;
            ss >> x;
            ss >> y;
            ss >> z;
            mData->SetData(x, y, z);
        }
        break;
    case VEC4:
        {
            std::stringstream ss(value);
            float x, y, z, w;
            ss >> x;
            ss >> y;
            ss >> z;
            ss >> w;
            mData->SetData(x, y, z, w);
        }
        break;
    }

    if( mCallback )
    {
        mCallback->DataChanged(this);
    }
}

void ObjectPropertyBinding::Bind( std::string *data )
{
    mStringData = data;
}

void ObjectPropertyBinding::Bind( GenericData *data )
{
    mData = data;
}