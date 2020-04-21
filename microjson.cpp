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

#include "microjson.h"

#include <iostream>

#ifdef MICROJSON_DEBUG
    #define microjsonDebug std::cout
#else
    struct microjsonNull : public std::ostream {};
    static microjsonNull nullout;
    #define microjsonDebug nullout
#endif

namespace {

template<const char expectedBeginByte>
void lookForBoundaries(const char *buffer, size_t size, size_t &begin, size_t &end) {
    const char expectedEndByte = expectedBeginByte + 2;
    begin = SIZE_MAX;
    end = SIZE_MAX;
    for (size_t i = 0; i < size; i++) {
        const char beginByte = buffer[i];
        const char endByte = buffer[size - i - 1];
        if (begin == SIZE_MAX) {
            if (beginByte == expectedBeginByte) {
                begin = i;
            } else if (beginByte != '\n' && beginByte != ' ' && beginByte != '\r' && beginByte != '\t') {
                std::cerr << "Unexpected begin byte" << beginByte << std::endl;
                break;
            }
        }

        if (end == SIZE_MAX) {
            if (endByte == expectedEndByte) {
                end = size - i - 1;
            } else if (endByte != '\n' && endByte != ' ' && endByte != '\r' && endByte != '\t') {
                std::cerr << "Unexpected end byte" << endByte << std::endl;
                break;
            }
        }

        if (begin != SIZE_MAX && end != SIZE_MAX) {
            break;
        }
    }
}

void lookForName(const char *buffer, size_t size, size_t &i, microjson::JsonProperty &property) {
    property.nameBegin = SIZE_MAX;
    property.nameEnd = SIZE_MAX;
    bool beginFound = false;
    for(; i < size; ++i) {
        const char byte = buffer[i];
        if (microjson::skipWhiteSpace(byte)) {
            microjsonDebug << "Skip space" << std::endl;
            continue;
        }

        if(!beginFound) {
            if (byte == '"') {
                microjsonDebug << "Found name begin" << std::endl;
                property.nameBegin = i + 1;
                beginFound = true;
            } else {
                std::cerr << "Not found name begin, unexpected" << std::endl;
                break;
            }
        } else if(byte == '"') {
            if (i > 0 && buffer[i - 1] == '\\') {
                microjsonDebug << "'\"' found in name" << std::endl;
                continue;
            }
            microjsonDebug << "Found name end" << std::endl;
            property.nameEnd = i;
            break;
        }
    }
    ++i;
}

bool lookForSeparator(const char* buffer, size_t size, size_t &i) {
    bool found = false;
    for(; i < size; ++i) {
        const char byte = buffer[i];
        if (microjson::skipWhiteSpace(byte)) {
            microjsonDebug << "Skip space" << std::endl;
            continue;
        }
        if (byte == ':') {
            microjsonDebug << "Found Separator" << std::endl;
            found = true;
        }
        break;
    }
    ++i;
    return found;
}

void lookForValue(const char *buffer, size_t size, size_t &i, microjson::JsonProperty &property) {
    int valueBracesCounter = -1;
    int valueBracketsCounter = -1;
    int trueCounter = 3;
    int falseCounter = 4;

    std::function<bool(void)> valueEndMarker;
    bool beginFound = false;
    bool stringScope = false;

    property.valueBegin = SIZE_MAX;
    property.valueEnd = SIZE_MAX;
    for(; i < size; i++) {
        const char byte = buffer[i];
        if (!beginFound) {
            microjsonDebug << "lookForValue at: " << i << " byte: " << byte << std::endl;
            if (microjson::skipWhiteSpace(byte)) {
                microjsonDebug << "Skip space" << std::endl;
                continue;
            }
            switch (byte) {
            case '"':
                valueEndMarker = [&](){
                    return buffer[i] == '"' && buffer[i - 1] != '\\';
                };
                property.type = microjson::JsonStringType;
                break;
            case '-':
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                valueEndMarker = [&buffer, &i](){
                    if (buffer[i] != '+'
                            && buffer[i] != '-'
                            && buffer[i] != '0'
                            && buffer[i] != '1'
                            && buffer[i] != '2'
                            && buffer[i] != '3'
                            && buffer[i] != '4'
                            && buffer[i] != '5'
                            && buffer[i] != '6'
                            && buffer[i] != '7'
                            && buffer[i] != '8'
                            && buffer[i] != '9'
                            && buffer[i] != 'e'
                            && buffer[i] != '.') {
                        i--;
                        return true;
                    }
                    return false;
                };
                property.type = microjson::JsonNumberType;
                break;
            case '{':
                valueBracesCounter++;
                valueEndMarker = [&stringScope, &byte, &valueBracesCounter](){
                    if (!stringScope) {
                        switch (byte) {
                        case '}':
                            --valueBracesCounter;
                            break;
                        case '{':
                            ++valueBracesCounter;
                            break;
                        default:
                            break;
                        }
                    }
                    return valueBracesCounter < 0;
                };
                property.type = microjson::JsonObjectType;
                break;
            case 't':
                valueEndMarker = [&trueCounter](){
                    --trueCounter;
                    return trueCounter == 0;
                };
                property.type = microjson::JsonBoolType;
                break;
            case 'f':
                valueEndMarker = [&falseCounter](){
                    --falseCounter;
                    return falseCounter == 0;
                };
                property.type = microjson::JsonBoolType;
                break;
            case '[':
                valueBracketsCounter++;
                valueEndMarker = [&stringScope, &byte, &valueBracketsCounter](){
                    if(!stringScope) {
                        switch(byte) {
                        case ']':
                            --valueBracketsCounter;
                            break;
                        case '[':
                            ++valueBracketsCounter;
                            break;
                        default:
                            break;
                        }
                    }
                    return valueBracketsCounter < 0;
                };
                property.type = microjson::JsonArrayType;
                break;
            }

            if (valueEndMarker) {
                microjsonDebug << "Found value begin" << std::endl;
                property.valueBegin = i;
                beginFound = true;
            } else {
                break;
            }
        } else {
            if (byte == '"' && (i == 0 || buffer[i - 1] != '\\')) {
                stringScope = !stringScope;
            }

            if (valueEndMarker()) {
                microjsonDebug << "Found value end" << std::endl;
                property.valueEnd = i;
                break;
            }
        }
    }

    if (property.checkEof()) {
        property.valueEnd = size - 1; //EOF case
        microjsonDebug << "Found value end at EOF" << std::endl;
    }

    if (property.type == microjson::JsonStringType) {
        ++property.valueBegin;
        --property.valueEnd;
    }
}

void findSeparator(const char *buffer, size_t size, size_t &i, const char expectedEndByte) {
    while (++i < size) {
        if(!microjson::skipWhiteSpace(buffer[i])) {
            break;
        }
    }

    const char endByte = buffer[i];
    if (endByte == expectedEndByte) {
        if(++i != size) {
            i = SIZE_MAX;
        }
    } else if(endByte == ',') {
        ++i;
    } else {
        i = SIZE_MAX;
    }
}

bool extractValue(const char *buffer, size_t size, size_t &i, const char expectedEndByte, microjson::JsonProperty &property) {
    if (size == 0) {
        i = SIZE_MAX;
        return false;
    }
    lookForValue(buffer, size, i, property);
    findSeparator(buffer, size, i, expectedEndByte);

    return property.checkValue();
}

using Extractor = bool(*)(const char *, size_t, size_t &, const char, microjson::JsonProperty &);

template<typename R,
         const char expectedBeginByte,
         Extractor extract,
         void(* collect)(const char *, R &, const microjson::JsonProperty &property)>
R parseJsonCommon(const char *buffer, size_t size) {
    R returnValue;

    if (buffer == nullptr || size == 0 || size == SIZE_MAX) {
        return returnValue;
    }

    size_t objectBeginPosition = SIZE_MAX;
    size_t objectEndPosition = SIZE_MAX;

    lookForBoundaries<expectedBeginByte>(buffer, size, objectBeginPosition, objectEndPosition);
    if (objectBeginPosition == SIZE_MAX || objectEndPosition == SIZE_MAX) {
        return returnValue;
    }

    microjson::JsonProperty property;
    buffer += objectBeginPosition + 1;//Skip '{'
    size = objectEndPosition - objectBeginPosition;//Do not skip '}'

    microjsonDebug << "Object buffer size: " << size << " buffer: " << std::string(buffer, size) << std::endl;

    size_t nextPosition = 0;
    while (nextPosition < size) {
        microjsonDebug << "nextPropertyPosition: " << nextPosition << "size: " << size << std::endl;
        if(extract(buffer, size, nextPosition, expectedBeginByte + 2, property)) {
            collect(buffer, returnValue, property);
        }
    }

    return returnValue;
}

void appendProperty(const char* buffer, microjson::JsonObject &obj, const microjson::JsonProperty &property){
    std::string name((buffer + property.nameBegin), property.nameSize());
    std::string value;
    if(property.valueSize() > 0) {
        value = std::string((buffer + property.valueBegin), property.valueSize());
    }
    microjsonDebug << "name: " << name << " value: " << value << std::endl;
    obj[name] = { value, property.type };
};

void appendValue(const char* buffer, microjson::JsonArray &values, const microjson::JsonProperty &property){
    std::string value = std::string((buffer + property.valueBegin), property.valueSize());
    microjsonDebug << "value: " << value << std::endl;
    values.push_back({value, property.type});
};

}

bool microjson::extractProperty(const char *buffer, size_t size, size_t &i, const char expectedEndByte, microjson::JsonProperty &property) {
    if (size == 0) {
        i = SIZE_MAX;
        return false;
    }

    lookForName(buffer, size, i, property);
    if(property.nameBegin == SIZE_MAX && property.nameEnd == SIZE_MAX) {
        std::cerr << "Name not found" << std::endl;
        return false;
    }

    microjsonDebug << "Found name: " << std::string(buffer + property.nameBegin, property.nameSize()) << std::endl;

    if(!lookForSeparator(buffer, size, i)) {
        std::cerr << "Separator not found" << std::endl;
        return false;
    }

    lookForValue(buffer, size, i, property);
    microjsonDebug << "Found value: " << std::string(buffer + property.valueBegin, property.valueSize()) << std::endl;
    findSeparator(buffer, size, i, expectedEndByte);

    return property.check();
}

microjson::JsonObject microjson::parseJsonObject(const char *buffer, size_t size) {
    return parseJsonCommon<JsonObject, '{', extractProperty, appendProperty>(buffer, size);
}

microjson::JsonArray microjson::parseJsonArray(const char *buffer, size_t size) {
    return parseJsonCommon<JsonArray, '[', extractValue, appendValue>(buffer, size);
}
