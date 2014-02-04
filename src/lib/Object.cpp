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

#include <cstddef>

#include <rapidxml.hpp>

#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>
#include <oglplus/shapes/obj_mesh.hpp>
#include <oglplus/shapes/wrapper.hpp>
#include <oglplus/opt/resources.hpp>
#include <oglplus/opt/list_init.hpp>
#include <oglplus/images/load.hpp>

#include "Object.h"

int Object::s_mId = 0;

struct ObjectData
{
    oglplus::VertexShader vertexShader;
    oglplus::FragmentShader fragmentShader;
    oglplus::Program program;
    oglplus::LazyUniform<oglplus::Mat4f> *modelMatrix;
    //oglplus::VertexArray shape;
    //oglplus::Buffer verts, normals;
    oglplus::Texture tex;
    oglplus::shapes::ShapeWrapper *shape;

    ObjectData() 
        : modelMatrix(nullptr)
        , shape(nullptr)
    {

    }

    ~ObjectData() 
    {
        delete modelMatrix;
    }
};

Object::Object()
    : mData( new ObjectData )
{
    mId = s_mId++;
}

Object::~Object()
{
    delete mData;
}

int Object::GetId()
{
    return mId;
}

ObjectData* Object::GetData() 
{
    return mData;
}

void Object::LoadFromFile( wxString filename )
{
    //using namespace rapidxml;
    rapidxml::xml_document<> doc;
    doc.parse<0>((char*)filename.c_str().AsChar());

    rapidxml::xml_node<> *pObjectNode = doc.first_node("object");
    if( pObjectNode )
    {
        //for( xml_node<char> *pModelNode = pObjectNode->first_node("model"); pModelNode != NULL; pModelNode = pModelNode->next_sibling("object") )
        rapidxml::xml_node<> *pModelNode = pObjectNode->first_node("model");
        if( pModelNode )
        {
            std::ifstream input ((const char*)pModelNode->first_attribute("file"));
            mData->shape = new oglplus::shapes::ShapeWrapper (
                oglplus::List("Position")("Normal")("Material").Get(),
                oglplus::shapes::ObjMesh(
                input,
                oglplus::shapes::ObjMesh::LoadingOptions(false).Normals().Materials()
                )
            );
        }

        rapidxml::xml_node<> *pTextureNode = pObjectNode->first_node("texture");
        if( pTextureNode )
        {
            //oglplus::Texture::Image2D(oglplus::images::LoadTexture(std::string(pTextureNode->first_attribute("file"))));
        }
    }
}