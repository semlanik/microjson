/*
 * MIT License
 *
 * Copyright (c) 2020 Alexey Edelev <semlanik@gmail.com>
 *
 * This file is part of microjson project https://git.semlanik.org/semlanik/microjson
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this
 * software and associated documentation files (the "Software"), to deal in the Software
 * without restriction, including without limitation the rights to use, copy, modify,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software, and
 * to permit persons to whom the Software is furnished to do so, subject to the following
 * conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies
 * or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
 * INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 * PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE
 * FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include <stddef.h>
#include <stdint.h>

#include <string>
#include <unordered_map>

namespace microjson {
enum JsonType {
    JsonNumberType,
    JsonStringType,
    JsonBoolType,
    JsonObjectType,
    JsonArrayType,
    JsonInvalidType
};

struct JsonValue {
    JsonValue() : type(JsonInvalidType) {}
    JsonValue(const std::string &_value, JsonType _type) :
    value(_value)
    , type(_type) {}
    std::string value;
    JsonType type;
};

using JsonObject = std::unordered_map<std::string, JsonValue>;

struct JsonProperty {
    JsonProperty() : nameBegin(SIZE_MAX)
      , nameEnd(SIZE_MAX)
      , valueBegin(SIZE_MAX)
      , valueEnd(SIZE_MAX)
      , type(JsonInvalidType){}

    size_t nameBegin;
    size_t nameEnd;
    size_t valueBegin;
    size_t valueEnd;
    JsonType type;

    size_t nameSize() const {
        return nameEnd - nameBegin;
    }

    size_t valueSize() const {
        return valueEnd - valueBegin + 1;
    }

    bool check() const {
        return type != JsonInvalidType && nameBegin != SIZE_MAX && nameEnd != SIZE_MAX &&
                valueBegin != SIZE_MAX && valueEnd != SIZE_MAX &&
                nameBegin < nameEnd && nameEnd < valueBegin &&
                valueBegin <= valueEnd;
    }

    bool eofCheck() const {
        return (type == JsonNumberType || type == JsonBoolType) && nameBegin != SIZE_MAX && nameEnd != SIZE_MAX &&
                valueBegin != SIZE_MAX && valueEnd == SIZE_MAX &&
                nameBegin < nameEnd && nameEnd < valueBegin;
    }
};

extern JsonObject parseObject(const char *buffer, size_t size);
extern size_t extractNextProperty(const char *buffer, size_t size, JsonProperty &property);
}
