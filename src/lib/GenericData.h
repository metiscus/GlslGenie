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

#include <fstream>

class GenericData
{
public:
    enum Type { INVALID, INT, FLOAT, VEC2, VEC3, VEC4 };
    
    GenericData();
    GenericData( Type type );

    Type GetType() const;
    int  GetNumComponents() const;
    float GetComponent(int idx) const;
    void SetType( Type type );

    void SetData(int x);
    void SetData(float x);
    void SetData(float x, float y);
    void SetData(float x, float y, float z);
    void SetData(float x, float y, float z, float w);

    void GetData(int& x);
    void GetData(float& x);
    void GetData(float& x, float& y);
    void GetData(float& x, float& y, float& z);
    void GetData(float& x, float& y, float& z, float& w);

    bool Read(std::ifstream& istream);
    void Write(std::ofstream& ostream) const;

private:
    Type mType;
    float mData [4];
};