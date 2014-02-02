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

#include "Property.h"

Property::Property( wxString name, PropertyType type, wxAny& value )
    : mName( name ), mType( type ), mProperty( value )
{

}

wxString Property::GetName()
{
    return mName;
}

wxAny& Property::GetValue()
{
    return mProperty;
}

PropertyType Property::GetType()
{
    return mType;
}