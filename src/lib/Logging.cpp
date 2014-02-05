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

#include "Logging.h"

#include <cstdarg>

namespace Logging 
{
    static const int MAX_LOG_STRING_LENGTH = 100000;

    static void log_print ( const char *name, const std::string& string )
    {
        fprintf(stderr, "[%s]\t%s", name, string.c_str());
    }
    
    void debug ( const char* format, ... )
    {
        char *buff = new char[MAX_LOG_STRING_LENGTH];
        va_list args;
        va_start(args, format);
        vsnprintf(buff, MAX_LOG_STRING_LENGTH, format, args);
        va_end(args);
        log_print( "DEBUG", buff );

        delete [] buff;
    }

    void trace ( const char* format, ... )
    {
        char *buff = new char[MAX_LOG_STRING_LENGTH];
        va_list args;
        va_start(args, format);
        vsnprintf(buff, MAX_LOG_STRING_LENGTH, format, args);
        va_end(args);
        log_print( "TRACE", buff );

        delete [] buff;
    }

    void warn  ( const char* format, ... )
    {
        char *buff = new char[MAX_LOG_STRING_LENGTH];
        va_list args;
        va_start(args, format);
        vsnprintf(buff, MAX_LOG_STRING_LENGTH, format, args);
        va_end(args);
        log_print( "WARN", buff );

        delete [] buff;
    }

    void error ( const char* format, ... )
    {
        char *buff = new char[MAX_LOG_STRING_LENGTH];
        va_list args;
        va_start(args, format);
        vsnprintf(buff, MAX_LOG_STRING_LENGTH, format, args);
        va_end(args);
        log_print( "ERR", buff );

        delete [] buff;
    }
}