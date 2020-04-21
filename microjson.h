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

#include <functional>

#include <string>
#include <vector>
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

struct JsonProperty {
    JsonProperty() : nameBegin(SIZE_MAX)
      , nameEnd(SIZE_MAX)
      , valueBegin(SIZE_MAX)
      , valueEnd(SIZE_MAX)
      , type(microjson::JsonInvalidType){}

    size_t nameBegin;
    size_t nameEnd;
    size_t valueBegin;
    size_t valueEnd;
    microjson::JsonType type;

    size_t nameSize() const {
        return nameEnd - nameBegin;
    }

    size_t valueSize() const {
        return valueEnd - valueBegin + 1;
    }

    bool checkValue() const {
        return type != microjson::JsonInvalidType && valueBegin != SIZE_MAX && valueEnd != SIZE_MAX;
    }

    bool checkEof() const {
        return (type == microjson::JsonNumberType || type == microjson::JsonBoolType) &&
                valueBegin != SIZE_MAX && valueEnd == SIZE_MAX;
    }

    bool check() const {
        return checkValue() && nameBegin != SIZE_MAX && nameEnd != SIZE_MAX &&
                nameBegin < nameEnd && nameEnd < valueBegin;
    }
};

using JsonObject = std::unordered_map<std::string, JsonValue>;
using JsonArray = std::vector<JsonValue>;

extern JsonArray parseJsonArray(const char *buffer, size_t size);
extern JsonObject parseJsonObject(const char *buffer, size_t size);

inline bool skipWhiteSpace(const char byte) {
    return byte == '\n' || byte == ' ' || byte == '\r' || byte == '\t' || byte == '\f' || byte == '\v';
}

extern bool extractValue(const char *buffer, size_t size, size_t &i, const char expectedEndByte, microjson::JsonProperty &property);
extern bool extractProperty(const char *buffer, size_t size, size_t &i, const char expectedEndByte, microjson::JsonProperty &property);
}
