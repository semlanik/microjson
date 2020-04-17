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
#include <functional>

#ifdef MICROJSON_DEBUG
    #define micorJsonDebug std::cout
#else
    struct micorJsonNull : public std::ostream {
    };
    static micorJsonNull nullout;
    #define micorJsonDebug nullout
#endif
size_t microjson::extractNextProperty(const char *buffer, size_t size, JsonProperty &property) {
    if (buffer == nullptr || size == 0 || size == SIZE_MAX) {
        return SIZE_MAX;
    }

    enum ParsingState {
        LookingForNameBegin,
        LookingForNameEnd,
        LookingForSeparator,
        LookingForValueBegin,
        LookingForValueEnd
    };

    property.nameBegin = SIZE_MAX;
    property.nameEnd = SIZE_MAX;
    property.valueBegin = SIZE_MAX;
    property.valueEnd = SIZE_MAX;
    property.type = JsonInvalidType;

    int valueBracesCounter = -1;
    int valueBracketsCounter = -1;
    int trueCounter = 3;
    int falseCounter = 4;

    std::function<bool(void)> valueEndMarker;
    ParsingState state = LookingForNameBegin;
    size_t i = 0;
    for (; i < size; i++) {
        const char byte = buffer[i];
        if (state == LookingForNameBegin) {
            if (byte == '\n' || byte == ' ' || byte == '\r' || byte == '\t') {
                micorJsonDebug << "Skip space" << std::endl;
                continue;
            }
            if (byte == '"') {
                micorJsonDebug << "Found name begin" << std::endl;
                property.nameBegin = i + 1;
                state = LookingForNameEnd;
            } else {
                std::cerr << "Not found name begin, unexpected" << std::endl;
                break;
            }
        } else if (state == LookingForNameEnd && byte == '"') {
            if (byte == '\n' || byte == ' ' || byte == '\r' || byte == '\t') {
                micorJsonDebug << "Skip space" << std::endl;
                continue;
            }
            if (i > 0 && buffer[i - 1] == '\\') {
                micorJsonDebug << "'\"' found in name" << std::endl;
                continue;
            }
            micorJsonDebug << "Found name end" << std::endl;
            property.nameEnd = i;
            state = LookingForSeparator;
        } else if (state == LookingForSeparator) {
            if (byte == '\n' || byte == ' ' || byte == '\r' || byte == '\t') {
                micorJsonDebug << "Skip space" << std::endl;
                continue;
            }
            if (byte == ':') {
                micorJsonDebug << "Found Separator" << std::endl;
                state = LookingForValueBegin;
            } else {
                break;
            }
        } else if (state == LookingForValueBegin) {
            if (byte == '\n' || byte == ' ' || byte == '\r' || byte == '\t') {
                micorJsonDebug << "Skip space" << std::endl;
                continue;
            }
            switch (byte) {
            case '"':
                valueEndMarker = [&](){
                    return buffer[i] == '"' && buffer[i - 1] != '\\';
                };
                property.type = JsonStringType;
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
                property.type = JsonNumberType;
                break;
            case '{':
                valueBracesCounter++;
                valueEndMarker = [&valueBracesCounter](){
                    return valueBracesCounter < 0;
                };
                property.type = JsonObjectType;
                break;
            case 't':
                valueEndMarker = [&trueCounter](){
                    return trueCounter == 0;
                };
                property.type = JsonBoolType;
                break;
            case 'f':
                valueEndMarker = [&falseCounter](){
                    return falseCounter == 0;
                };
                property.type = JsonBoolType;
                break;
            case '[':
                valueBracketsCounter++;
                valueEndMarker = [&valueBracketsCounter](){
                    return valueBracketsCounter < 0;
                };
                property.type = JsonArrayType;
                break;
            }

            if (valueEndMarker) {
                micorJsonDebug << "Found value begin" << std::endl;
                property.valueBegin = i;
                state = LookingForValueEnd;
            } else {
                break;
            }
        } else if (state == LookingForValueEnd) {
            switch (byte) {
            case '}':
                --valueBracesCounter;
                break;
            case '{':
                --valueBracesCounter;
                break;
            case ']':
                --valueBracketsCounter;
                break;
            case '[':
                ++valueBracketsCounter;
                break;
            default:
                --trueCounter;
                --falseCounter;
                break;
            }

            if (valueEndMarker()) {
                micorJsonDebug << "Found value end" << std::endl;
                property.valueEnd = i;
                break;
            }
        }
    }

    if (property.eofCheck()) {
        property.valueEnd = size - 1; //EOF case
        micorJsonDebug << "Found value end at EOF" << std::endl;
    }

    micorJsonDebug << property.nameBegin << " " << property.nameEnd << " " << property.valueBegin << " " << property.valueEnd << " " << property.type << std::endl;
    if (property.check()) {
        if (property.type == JsonStringType) {
            ++property.valueBegin;
            --property.valueEnd;
        }
        for (size_t j = i + 1; j < size; j++) {
            const char &byte = buffer[j];
            if (byte == ',') {
                return j + 1;
            } else if (byte != '\n' && byte != ' ' && byte != '\r' && byte != '\t') {
                micorJsonDebug << "Unexpected: " << byte;
                return SIZE_MAX;
            }
        }
        return size;
    } else {
        micorJsonDebug << "Property check failed" << std::endl;
    }
    return SIZE_MAX;
}

microjson::JsonObject microjson::parseObject(const char *buffer, size_t size) {
    JsonObject obj;

    if (buffer == nullptr || size == 0 || size == SIZE_MAX) {
        return obj;
    }

    size_t objectBeginPosition = SIZE_MAX;
    size_t objectEndPosition = SIZE_MAX;
    for (size_t i = 0; i < size; i++) {
        const char beginByte = buffer[i];
        const char endByte = buffer[size - i - 1];
        if (objectBeginPosition == SIZE_MAX) {
            if (beginByte == '{') {
                objectBeginPosition = i;
            } else if (beginByte != '\n' && beginByte != ' ' && beginByte != '\r' && beginByte != '\t') {
                std::cerr << "Unexpected begin byte" << beginByte << std::endl;
                break;
            }
        }

        if (objectEndPosition == SIZE_MAX) {
            if (endByte == '}') {
                objectEndPosition = size - i - 1;
            } else if (endByte != '\n' && endByte != ' ' && endByte != '\r' && endByte != '\t') {
                std::cerr << "Unexpected end byte" << endByte << std::endl;
                break;
            }
        }

        if (objectBeginPosition != SIZE_MAX && objectEndPosition != SIZE_MAX) {
            break;
        }

    }

    if (objectBeginPosition == SIZE_MAX || objectEndPosition == SIZE_MAX) {
        return obj;
    }

    JsonProperty property;
    buffer += objectBeginPosition + 1;//Skip '{'
    size = objectEndPosition - objectBeginPosition - 1;//Skip '}'

    micorJsonDebug << "Object buffer size: " << size << " buffer: " << std::string(buffer, size) << std::endl;

    for (size_t nextPropertyPosition = microjson::extractNextProperty(buffer, size, property); nextPropertyPosition != SIZE_MAX; ) {
        micorJsonDebug << "nextPropertyPosition: " << nextPropertyPosition << "size: " << size << std::endl;
        if (nextPropertyPosition != SIZE_MAX) {
            std::string name((buffer + property.nameBegin), property.nameSize());
            std::string value((buffer + property.valueBegin), property.valueSize());
            micorJsonDebug << "name: " << name << " value: " << value << std::endl;
            obj[name] = { value, property.type };
        }
        buffer += nextPropertyPosition;
        size = size - nextPropertyPosition;
        nextPropertyPosition = microjson::extractNextProperty(buffer, size, property);
    }
    return obj;
}
