/*****************************************************************************************
 *                                                                                       *
 * OpenSpace                                                                             *
 *                                                                                       *
 * Copyright (c) 2014-2020                                                               *
 *                                                                                       *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this  *
 * software and associated documentation files (the "Software"), to deal in the Software *
 * without restriction, including without limitation the rights to use, copy, modify,    *
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and to    *
 * permit persons to whom the Software is furnished to do so, subject to the following   *
 * conditions:                                                                           *
 *                                                                                       *
 * The above copyright notice and this permission notice shall be included in all copies *
 * or substantial portions of the Software.                                              *
 *                                                                                       *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,   *
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A         *
 * PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT    *
 * HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF  *
 * CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE  *
 * OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                                         *
 ****************************************************************************************/

#include <openspace/properties/matrix/dmat2x3property.h>

#include <ghoul/misc/misc.h>

#include <limits>
#include <sstream>
#include <vector>

namespace {

glm::dmat2x3 fromLuaConversion(lua_State* state, bool& success) {
    glm::dmat2x3 result;
    lua_pushnil(state);
    int number = 1;
    for (glm::length_t i = 0; i < ghoul::glm_cols<glm::dmat2x3>::value; ++i) {
        for (glm::length_t j = 0; j < ghoul::glm_rows<glm::dmat2x3>::value; ++j) {
            int hasNext = lua_next(state, -2);
            if (hasNext != 1) {
                success = false;
                return glm::dmat2x3(0.0);
            }
            if (lua_isnumber(state, -1) != 1) {
                success = false;
                return glm::dmat2x3(0.0);
            }
            else {
                result[i][j] = lua_tonumber(state, -1);
                lua_pop(state, 1);
                ++number;
            }
        }
    }
    // The last accessor argument and the table are still on the stack
    lua_pop(state, 1);
    success = true;
    return result;
}

bool toLuaConversion(lua_State* state, glm::dmat2x3 value) {
    lua_newtable(state);
    int number = 1;
    for (glm::length_t i = 0; i < ghoul::glm_cols<glm::dmat2x3>::value; ++i) {
        for (glm::length_t j = 0; j < ghoul::glm_rows<glm::dmat2x3>::value; ++j) {
            lua_pushnumber(state, value[i][j]);
            lua_rawseti(state, -2, number);
            ++number;
        }
    }
    return true;
}

glm::dmat2x3 fromStringConversion(const std::string& val, bool& success) {
    glm::dmat2x3 result = glm::dmat2x3(1.0);
    std::vector<std::string> tokens = ghoul::tokenizeString(val, ',');
    if (tokens.size() !=
        (ghoul::glm_rows<glm::dmat2x3>::value * ghoul::glm_cols<glm::dmat2x3>::value))
    {
        success = false;
        return result;
    }
    int number = 0;
    for (glm::length_t i = 0; i < ghoul::glm_cols<glm::dmat2x3>::value; ++i) {
        for (glm::length_t j = 0; j < ghoul::glm_rows<glm::dmat2x3>::value; ++j) {
            std::stringstream s(tokens[number]);
            glm::dmat2x3::value_type v;
            s >> v;
            if (s.fail()) {
                success = false;
                return result;
            }
            else {
                result[i][j] = v;
                ++number;
            }
        }
    }
    success = true;
    return result;
}

bool toStringConversion(std::string& outValue, glm::dmat2x3 inValue) {
    outValue = "[";
    for (glm::length_t i = 0; i < ghoul::glm_cols<glm::dmat2x3>::value; ++i) {
        for (glm::length_t j = 0; j < ghoul::glm_rows<glm::dmat2x3>::value; ++j) {
            outValue += std::to_string(inValue[i][j]) + ",";
        }
    }
    outValue.pop_back();
    outValue += "]";
    return true;
}

} // namespace

namespace openspace::properties {

using nl = std::numeric_limits<double>;

REGISTER_NUMERICALPROPERTY_SOURCE(
    DMat2x3Property,
    glm::dmat2x3,
    glm::dmat2x3(0.0),
    glm::dmat2x3(
        nl::lowest(), nl::lowest(),
        nl::lowest(), nl::lowest(),
        nl::lowest(), nl::lowest()
    ),
    glm::dmat2x3(
        nl::max(), nl::max(),
        nl::max(), nl::max(),
        nl::max(), nl::max()
    ),
    glm::dmat2x3(0.01, 0.01, 0.01, 0.01, 0.01, 0.01),
    fromLuaConversion,
    toLuaConversion,
    fromStringConversion,
    toStringConversion,
    LUA_TTABLE
)

}  // namespace openspace::properties
