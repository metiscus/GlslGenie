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
#include <string>
#include <fstream>

#include <rapidxml.hpp>

#include "ObjectData.h"
#include "Object.h"

int Object::s_mId = 0;

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

static inline std::string fileToString( const char* filename )
{
    std::string ret;
    std::ifstream infile( filename );
    while( infile.is_open() && !infile.eof() )
    {
        std::string line;
        std::getline(infile, line);
        ret += line + "\n";
    }
    infile.close();
    return ret;
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
            std::ifstream input(pModelNode->first_attribute("file")->value());
            //((const char*)pModelNode->first_attribute("file"));
            //oglplus::OpenResourceFile(input, "models", pModelNode->first_attribute("file")->value(), ".obj");
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
            std::string textureFilename = pTextureNode->first_attribute("file")->value();
            auto bound_tex = Bind(mData->tex, oglplus::TextureTarget::_2D);
            bound_tex.Image2D(oglplus::images::LoadTexture(textureFilename.c_str()));
            bound_tex.MinFilter(oglplus::TextureMinFilter::Linear);
            bound_tex.MagFilter(oglplus::TextureMagFilter::Linear);
            bound_tex.Anisotropy(2.0f);
            bound_tex.WrapS(oglplus::TextureWrap::Repeat);
            bound_tex.WrapT(oglplus::TextureWrap::Repeat);
        }

        rapidxml::xml_node<> *pVShaderNode = pObjectNode->first_node("vshader");
        if( pVShaderNode )
        {
            std::string shaderFilename = pVShaderNode->first_attribute("file")->value(); 
            mData->vertexShader.Source(fileToString(shaderFilename.c_str()));
            mData->vertexShader.Compile();
        }

        rapidxml::xml_node<> *pFShaderNode = pObjectNode->first_node("fshader");
        if( pFShaderNode )
        {
            std::string shaderFilename = pFShaderNode->first_attribute("file")->value(); 
            mData->fragmentShader.Source(fileToString(shaderFilename.c_str()));
            mData->fragmentShader.Compile();
        }

        mData->program.AttachShader(mData->fragmentShader);
        mData->program.AttachShader(mData->vertexShader);
        
        mData->modelMatrix      = new oglplus::LazyUniform<oglplus::Mat4f> (mData->program, "ModelMatrix");
        mData->cameraMatrix     = new oglplus::LazyUniform<oglplus::Mat4f> (mData->program, "CameraMatrix");
        mData->projectionMatrix = new oglplus::LazyUniform<oglplus::Mat4f> (mData->program, "ProjectionMatrix");
       
        mData->program.Link();

        mData->vao = mData->shape->VAOForProgram(mData->program);

        mData->shape->UseInProgram(mData->program);
        mData->program.Use();
    }
}