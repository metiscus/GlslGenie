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

#include <string>

namespace Logging
{
    enum Level {
        LOG_DEBUG = 1,
        LOG_TRACE = 2,
        LOG_WARN  = 4,
        LOG_ERROR = 8
    };

    void debug ( const char* format, ... );
    void trace ( const char* format, ... );
    void warn  ( const char* format, ... );
    void error ( const char* format, ... );
};