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

#include <oglplus/gl.hpp>
#include <oglplus/all.hpp>
#include <oglplus/shapes/obj_mesh.hpp>
#include <oglplus/shapes/wrapper.hpp>
#include <oglplus/opt/resources.hpp>
#include <oglplus/opt/list_init.hpp>
#include <oglplus/images/load.hpp>
#include <oglplus/bound/texture.hpp>

struct ObjectData
{
    oglplus::VertexShader vertexShader;
    oglplus::FragmentShader fragmentShader;
    oglplus::Program program;
    oglplus::LazyUniform<oglplus::Mat4f> *modelMatrix, *cameraMatrix, *projectionMatrix;
    oglplus::Texture tex;
    oglplus::shapes::ShapeWrapper *shape;
    oglplus::VertexArray vao;

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