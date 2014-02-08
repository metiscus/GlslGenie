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

#include "GenericData.h"
#include <cassert>

GenericData::GenericData() : mType( INVALID )
{
    mData[0] = mData[1] = mData[2] = mData[3] = 0.0f;
}

GenericData::GenericData( GenericData::Type type ) : mType( type )
{
    assert( type != INVALID );
    mData[0] = mData[1] = mData[2] = mData[3] = 0.0f;
}

GenericData::Type GenericData::GetType() const
{
    return mType;
}

int GenericData::GetNumComponents() const
{
    switch ( mType )
    {
    case INT:
    case FLOAT:
        return 1;
        break;
    case VEC2:
        return 2;
        break;
    case VEC3:
        return 3;
        break;
    case VEC4:
        return 4;
        break;
    default:
        return 0;
        break;
    }
}

float GenericData::GetComponent(int idx) const
{
    return mData[idx];
}

void GenericData::SetType( GenericData::Type type )
{
    mType = type;
}

void GenericData::SetData(int x)
{
    mData[0] = (float)x;
}

void GenericData::SetData(float x)
{
    mData[0] = x;
}

void GenericData::SetData(float x, float y)
{
    mData[0] = x;
    mData[1] = y;
}

void GenericData::SetData(float x, float y, float z)
{
    mData[0] = x;
    mData[1] = y;
    mData[2] = z;
}

void GenericData::SetData(float x, float y, float z, float w)
{
    mData[0] = x;
    mData[1] = y;
    mData[2] = z;
    mData[3] = w;
}

void GenericData::GetData(int& x)
{
    x = (int)mData[0];
}

void GenericData::GetData(float& x)
{
    x = mData[0];
}

void GenericData::GetData(float& x, float& y)
{
    x = mData[0];
    y = mData[1];
}

void GenericData::GetData(float& x, float& y, float& z)
{
    x = mData[0];
    y = mData[1];
    z = mData[2];
}

void GenericData::GetData(float& x, float& y, float& z, float& w)
{
    x = mData[0];
    y = mData[1];
    z = mData[2];
    w = mData[3];
}

bool GenericData::Read(std::ifstream& istream)
{
    try {
        int type = 0;
        istream >> type;
        mType = (Type)type;
        int numToRead = GetNumComponents();

        for( int ii=0; ii<numToRead; ++ii )
        {
            istream >> mData[ii];
        }
    }
    catch ( ... )
    {
        return false;
    }
    return true;
}

void GenericData::Write(std::ofstream& ostream) const
{
    ostream << (int)mType;
    int numToWrite = GetNumComponents();

    for( int ii=0; ii<numToWrite; ++ii )
    {
        ostream << mData[ii];
    }
}