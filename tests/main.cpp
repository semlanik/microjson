#include "microjson.h"

#include <iostream>
#include <string.h>
#include <gtest/gtest.h>

class MicrojsonDeserializationTest : public ::testing::Test
{
public:
    MicrojsonDeserializationTest() = default;
};

TEST_F(MicrojsonDeserializationTest, StringValue)
{
    const char *buffer1 = "{\"testField\":\"test\"}";
    size_t size = strlen(buffer1);
    microjson::JsonObject obj = microjson::parseJsonObject(buffer1, size);
    auto it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonStringType);
    EXPECT_STREQ(it->second.value.c_str(), "test");

    obj.clear();
    const char *buffer2 = "{\"testField\":\"\"}";
    size = strlen(buffer2);
    obj = microjson::parseJsonObject(buffer2, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonStringType);
    EXPECT_STREQ(it->second.value.c_str(), "");

    obj.clear();
    const char *buffer3 = "{\"testField\":\"t\"}";
    size = strlen(buffer3);
    obj = microjson::parseJsonObject(buffer3, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonStringType);
    EXPECT_STREQ(it->second.value.c_str(), "t");

    obj.clear();
    const char *buffer4 = "{\"testField\":\"\\\"test\\\"\"}";
    size = strlen(buffer4);
    obj = microjson::parseJsonObject(buffer4, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonStringType);
    EXPECT_STREQ(it->second.value.c_str(), "\\\"test\\\"");

    obj.clear();
    const char *buffer5 = "{\"testField\":\"\\\"test\"}";
    size = strlen(buffer5);
    obj = microjson::parseJsonObject(buffer5, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonStringType);
    EXPECT_STREQ(it->second.value.c_str(), "\\\"test");

    obj.clear();
    const char *buffer6 = "{\"testField\":\"\\\"\"}";
    size = strlen(buffer6);
    obj = microjson::parseJsonObject(buffer6, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonStringType);
    EXPECT_STREQ(it->second.value.c_str(), "\\\"");

    obj.clear();
    const char *buffer7 = "{\"testField\":\"test\",\"testField1\":\"\",\"testField2\":\"t\",\"testField3\":\"\\\"test\\\"\",\"testField4\":\"\\\"test\",\"testField5\":\"\\\"\"}";
    size = strlen(buffer7);
    obj = microjson::parseJsonObject(buffer7, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonStringType);
    EXPECT_STREQ(it->second.value.c_str(), "test");

    it = obj.find("testField1");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField1");
    EXPECT_EQ(it->second.type, microjson::JsonStringType);
    EXPECT_STREQ(it->second.value.c_str(), "");

    it = obj.find("testField2");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField2");
    EXPECT_EQ(it->second.type, microjson::JsonStringType);
    EXPECT_STREQ(it->second.value.c_str(), "t");

    it = obj.find("testField3");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField3");
    EXPECT_EQ(it->second.type, microjson::JsonStringType);
    EXPECT_STREQ(it->second.value.c_str(), "\\\"test\\\"");

    it = obj.find("testField4");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField4");
    EXPECT_EQ(it->second.type, microjson::JsonStringType);
    EXPECT_STREQ(it->second.value.c_str(), "\\\"test");

    it = obj.find("testField5");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField5");
    EXPECT_EQ(it->second.type, microjson::JsonStringType);
    EXPECT_STREQ(it->second.value.c_str(), "\\\"");
}

TEST_F(MicrojsonDeserializationTest, NumberValue)
{
    const char *buffer1 = "{\"testField\":5}";
    size_t size = strlen(buffer1);
    microjson::JsonObject obj = microjson::parseJsonObject(buffer1, size);
    auto it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "5");

    obj.clear();
    const char *buffer2 = "{\"testField\":56}";
    size = strlen(buffer2);
    obj = microjson::parseJsonObject(buffer2, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "56");

    obj.clear();
    const char *buffer3 = "{\"testField\":0}";
    size = strlen(buffer3);
    obj = microjson::parseJsonObject(buffer3, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "0");

    obj.clear();
    const char *buffer4 = "{\"testField\":-5}";
    size = strlen(buffer4);
    obj = microjson::parseJsonObject(buffer4, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "-5");

    obj.clear();
    const char *buffer5 = "{\"testField\":-131}";
    size = strlen(buffer5);
    obj = microjson::parseJsonObject(buffer5, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "-131");

    obj.clear();
    const char *buffer6 = "{\"testField\":5,\"testField1\":56,\"testField2\":0,\"testField3\":-8,\"testField4\":-124}";
    size = strlen(buffer6);
    obj = microjson::parseJsonObject(buffer6, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "5");

    it = obj.find("testField1");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField1");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "56");

    it = obj.find("testField2");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField2");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "0");

    it = obj.find("testField3");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField3");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "-8");

    it = obj.find("testField4");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField4");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "-124");
}

TEST_F(MicrojsonDeserializationTest, TextSpacesCutting)
{
    const char *buffer1 = "\n\r\t  {\n\r\t \"testField\"\n\r\t :   5\n\t \r}\n\t \r";
    size_t size = strlen(buffer1);
    microjson::JsonObject obj = microjson::parseJsonObject(buffer1, size);
    auto it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "5");

    const char *buffer2 = "\n\r\t  {\n\r\t \"testField\"\n\r\t :   5\n\t \r, \n\r\t \"testField2\"\n\r\t :   -0.932e+10\n\t \r}\n\t \r";
    size = strlen(buffer2);
    obj = microjson::parseJsonObject(buffer2, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "5");

    it = obj.find("testField2");
    ASSERT_TRUE(it != obj.end());
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "-0.932e+10");


    const char *buffer3 = "\n\r\t  {\n\r\t \"testField\"\n\r\t :   \"5\"\n\t \r, \n\r\t \"test\n\rField2\"\n\r\t :   \"\\\"qwerty\t\t\t\t\"\n\t \r}\n\t \r";
    size = strlen(buffer3);
    obj = microjson::parseJsonObject(buffer3, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_EQ(it->second.type, microjson::JsonStringType);
    EXPECT_STREQ(it->second.value.c_str(), "5");

    it = obj.find("test\n\rField2");
    ASSERT_TRUE(it != obj.end());
    EXPECT_EQ(it->second.type, microjson::JsonStringType);
    EXPECT_STREQ(it->second.value.c_str(), "\\\"qwerty\t\t\t\t");
}

TEST_F(MicrojsonDeserializationTest, BooleanValue)
{
    const char *buffer1 = "{\"testField\":true}";
    size_t size = strlen(buffer1);
    microjson::JsonObject obj = microjson::parseJsonObject(buffer1, size);
    auto it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonBoolType);
    EXPECT_STREQ(it->second.value.c_str(), "true");

    obj.clear();
    const char *buffer2 = "{\"testField\":false}";
    size = strlen(buffer2);
    obj = microjson::parseJsonObject(buffer2, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonBoolType);
    EXPECT_STREQ(it->second.value.c_str(), "false");
    obj.clear();
    const char *buffer7 = "{\"testField\":true,\"testField1\":false}";
    size = strlen(buffer7);
    obj = microjson::parseJsonObject(buffer7, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonBoolType);
    EXPECT_STREQ(it->second.value.c_str(), "true");

    it = obj.find("testField1");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField1");
    EXPECT_EQ(it->second.type, microjson::JsonBoolType);
    EXPECT_STREQ(it->second.value.c_str(), "false");
}

TEST_F(MicrojsonDeserializationTest, FloatingPointValue)
{
    const char *buffer1 = "{\"testField\":0.0}";
    size_t size = strlen(buffer1);
    microjson::JsonObject obj = microjson::parseJsonObject(buffer1, size);
    auto it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "0.0");

    obj.clear();
    const char *buffer2 = "{\"testField\":1.0}";
    size = strlen(buffer2);
    obj = microjson::parseJsonObject(buffer2, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "1.0");

    obj.clear();
    const char *buffer3 = "{\"testField\":20.0}";
    size = strlen(buffer3);
    obj = microjson::parseJsonObject(buffer3, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "20.0");

    obj.clear();
    const char *buffer4 = "{\"testField\":20.01}";
    size = strlen(buffer4);
    obj = microjson::parseJsonObject(buffer4, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "20.01");

    obj.clear();
    const char *buffer5 = "{\"testField\":-1.0}";
    size = strlen(buffer5);
    obj = microjson::parseJsonObject(buffer5, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "-1.0");

    obj.clear();
    const char *buffer6 = "{\"testField\":-87.0}";
    size = strlen(buffer6);
    obj = microjson::parseJsonObject(buffer6, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "-87.0");

    obj.clear();
    const char *buffer7 = "{\"testField\":-11.21}";
    size = strlen(buffer7);
    obj = microjson::parseJsonObject(buffer7, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "-11.21");

    obj.clear();
    const char *buffer8 = "{\"testField\":1.1234+e10}";
    size = strlen(buffer8);
    obj = microjson::parseJsonObject(buffer8, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "1.1234+e10");

    obj.clear();
    const char *buffer9 = "{\"testField\":1.1234-e10}";
    size = strlen(buffer9);
    obj = microjson::parseJsonObject(buffer9, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "1.1234-e10");

    obj.clear();
    const char *buffer10 = "{\"testField\":-1.1234-e10}";
    size = strlen(buffer10);
    obj = microjson::parseJsonObject(buffer10, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "-1.1234-e10");

    obj.clear();
    const char *buffer11 = "{\"testField\":-1.1234+e10}";
    size = strlen(buffer11);
    obj = microjson::parseJsonObject(buffer11, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "-1.1234+e10");

    obj.clear();
    const char *buffer12 = "{\"testField\":0.0,\"testField1\":1.0,\"testField2\":20.0,\"testField3\":20.01,\"testField4\":-1.0,\"testField5\":-87.0,\"testField6\":-11.21,\"testField7\":1.1234+e10,\"testField8\":1.1234-e10,\"testField9\":-1.1234-e10,\"testField10\":-1.1234+e10}";
    size = strlen(buffer12);
    obj = microjson::parseJsonObject(buffer12, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "0.0");

    it = obj.find("testField1");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField1");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "1.0");

    it = obj.find("testField2");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField2");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "20.0");

    it = obj.find("testField3");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField3");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "20.01");

    it = obj.find("testField4");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField4");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "-1.0");

    it = obj.find("testField5");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField5");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "-87.0");

    it = obj.find("testField6");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField6");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "-11.21");

    it = obj.find("testField7");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField7");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "1.1234+e10");

    it = obj.find("testField8");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField8");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "1.1234-e10");

    it = obj.find("testField9");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField9");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "-1.1234-e10");

    it = obj.find("testField10");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField10");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "-1.1234+e10");
}

TEST_F(MicrojsonDeserializationTest, ArrayValue)
{
    const char *buffer1 = "{\"testField\":[\"test1\"]}";
    size_t size = strlen(buffer1);
    microjson::JsonObject obj = microjson::parseJsonObject(buffer1, size);
    auto it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonArrayType);
    EXPECT_STREQ(it->second.value.c_str(), "[\"test1\"]");

    obj.clear();
    const char *buffer2 = "{\"testField\":[\"test1\",\"test2\",\"test3\",\"test5\",\"test6\"]}";
    size = strlen(buffer2);
    obj = microjson::parseJsonObject(buffer2, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonArrayType);
    EXPECT_STREQ(it->second.value.c_str(), "[\"test1\",\"test2\",\"test3\",\"test5\",\"test6\"]");

    obj.clear();
    const char *buffer3 = "{\"testField\":[],\"testField1\":[\"test1\",\"test2\"]}";
    size = strlen(buffer3);
    obj = microjson::parseJsonObject(buffer3, size);

    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonArrayType);
    EXPECT_STREQ(it->second.value.c_str(), "[]");

    it = obj.find("testField1");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField1");
    EXPECT_EQ(it->second.type, microjson::JsonArrayType);
    EXPECT_STREQ(it->second.value.c_str(), "[\"test1\",\"test2\"]");

    obj.clear();
    const char *buffer4 = "{\"testField\":[1,1.0,-10,\"test1\",{\"test2\":15}]}";
    size = strlen(buffer4);
    obj = microjson::parseJsonObject(buffer4, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonArrayType);
    EXPECT_STREQ(it->second.value.c_str(), "[1,1.0,-10,\"test1\",{\"test2\":15}]");

    obj.clear();
    const char *buffer5 = "{\"testField\":[[1,2,3,4,5,6],[7,8,9,10,\"test1\"]]}";
    size = strlen(buffer5);
    obj = microjson::parseJsonObject(buffer5, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonArrayType);
    EXPECT_STREQ(it->second.value.c_str(), "[[1,2,3,4,5,6],[7,8,9,10,\"test1\"]]");

    obj.clear();
    const char *buffer6 = "{\"testField\":[{\"test1\":[1,2,3,4,5,{\"test2\":[\"test3\",\"test4\",[1,2,3,4]]}]}]}";
    size = strlen(buffer6);
    obj = microjson::parseJsonObject(buffer6, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonArrayType);
    EXPECT_STREQ(it->second.value.c_str(), "[{\"test1\":[1,2,3,4,5,{\"test2\":[\"test3\",\"test4\",[1,2,3,4]]}]}]");

    const char *buffer7 = "{\"testField\":[\"test1\"],\"testField1\":[\"test1\",\"test2\",\"test3\",\"test5\",\"test6\"],\"testField2\":[],\"testField3\":[\"test1\",\"test2\"],\"testField4\":[1,1.0,-10,\"test1\",{\"test2\":15}],\"testField5\":[[1,2,3,4,5,6],[7,8,9,10,\"test1\"]],\"testField6\":[{\"test1\":[1,2,3,4,5,{\"test2\":[\"test3\",\"test4\",[1,2,3,4]]}]}]}";
    size = strlen(buffer7);
    obj = microjson::parseJsonObject(buffer7, size);

    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonArrayType);
    EXPECT_STREQ(it->second.value.c_str(), "[\"test1\"]");

    it = obj.find("testField1");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField1");
    EXPECT_EQ(it->second.type, microjson::JsonArrayType);
    EXPECT_STREQ(it->second.value.c_str(), "[\"test1\",\"test2\",\"test3\",\"test5\",\"test6\"]");

    it = obj.find("testField2");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField2");
    EXPECT_EQ(it->second.type, microjson::JsonArrayType);
    EXPECT_STREQ(it->second.value.c_str(), "[]");

    it = obj.find("testField3");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField3");
    EXPECT_EQ(it->second.type, microjson::JsonArrayType);
    EXPECT_STREQ(it->second.value.c_str(), "[\"test1\",\"test2\"]");

    it = obj.find("testField4");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField4");
    EXPECT_EQ(it->second.type, microjson::JsonArrayType);
    EXPECT_STREQ(it->second.value.c_str(), "[1,1.0,-10,\"test1\",{\"test2\":15}]");

    it = obj.find("testField5");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField5");
    EXPECT_EQ(it->second.type, microjson::JsonArrayType);
    EXPECT_STREQ(it->second.value.c_str(), "[[1,2,3,4,5,6],[7,8,9,10,\"test1\"]]");

    it = obj.find("testField6");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField6");
    EXPECT_EQ(it->second.type, microjson::JsonArrayType);
    EXPECT_STREQ(it->second.value.c_str(), "[{\"test1\":[1,2,3,4,5,{\"test2\":[\"test3\",\"test4\",[1,2,3,4]]}]}]");
}

TEST_F(MicrojsonDeserializationTest, ObjectValue)
{
    const char *buffer1 = "{\"testField\":{\"testField1\":1}}";
    size_t size = strlen(buffer1);
    microjson::JsonObject obj = microjson::parseJsonObject(buffer1, size);
    auto it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonObjectType);
    EXPECT_STREQ(it->second.value.c_str(), "{\"testField1\":1}");

    const char *buffer2 = "{\"testField\":{\"testField1\":1,\"testField2\":2}}";
    size = strlen(buffer2);
    obj = microjson::parseJsonObject(buffer2, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonObjectType);
    EXPECT_STREQ(it->second.value.c_str(), "{\"testField1\":1,\"testField2\":2}");

    const char *buffer3 = "{\"testField\":{\"testField1\":1.0,\"testField2\":\"2\"}}";
    size = strlen(buffer3);
    obj = microjson::parseJsonObject(buffer3, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonObjectType);
    EXPECT_STREQ(it->second.value.c_str(), "{\"testField1\":1.0,\"testField2\":\"2\"}");

    const char *buffer4 = "{\"testField\":{}}";
    size = strlen(buffer4);
    obj = microjson::parseJsonObject(buffer4, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonObjectType);
    EXPECT_STREQ(it->second.value.c_str(), "{}");

    const char *buffer5 = "{\"testField\":{\"testField1\":{},\"testField2\":{\"testField3\":\"2\"}}}";
    size = strlen(buffer5);
    obj = microjson::parseJsonObject(buffer5, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonObjectType);
    EXPECT_STREQ(it->second.value.c_str(), "{\"testField1\":{},\"testField2\":{\"testField3\":\"2\"}}");

    const char *buffer6 = "{\"testField\":{\"testField1\":{},\"testField2\":{\"testField3\":[\"2\",0,1,2,{\"testField4\":9}]}}}";
    size = strlen(buffer6);
    obj = microjson::parseJsonObject(buffer6, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonObjectType);
    EXPECT_STREQ(it->second.value.c_str(), "{\"testField1\":{},\"testField2\":{\"testField3\":[\"2\",0,1,2,{\"testField4\":9}]}}");
}

TEST_F(MicrojsonDeserializationTest, ArrayValues)
{
    const char *buffer1 = "[\"test1\",\"test2\",\"test3\",\"test5\",\"test6\"]";
    size_t size = strlen(buffer1);
    microjson::JsonArray arr = microjson::parseJsonArray(buffer1, size);
    ASSERT_EQ(arr.size(), 5);
    EXPECT_STREQ(arr[0].value.c_str(), "test1");
    EXPECT_STREQ(arr[1].value.c_str(), "test2");
    EXPECT_STREQ(arr[2].value.c_str(), "test3");
    EXPECT_STREQ(arr[3].value.c_str(), "test5");
    EXPECT_STREQ(arr[4].value.c_str(), "test6");

    const char *buffer2 = "[\"test1\"]";
    size = strlen(buffer2);
    arr = microjson::parseJsonArray(buffer2, size);
    ASSERT_EQ(arr.size(), 1);
    EXPECT_STREQ(arr[0].value.c_str(), "test1");

    const char *buffer3 = "[]";
    size = strlen(buffer3);
    arr = microjson::parseJsonArray(buffer3, size);
    ASSERT_EQ(arr.size(), 0);

    const char *buffer4 = "[[\"test1\"]]";
    size = strlen(buffer4);
    arr = microjson::parseJsonArray(buffer4, size);
    ASSERT_EQ(arr.size(), 1);
    EXPECT_STREQ(arr[0].value.c_str(), "[\"test1\"]");

    const char *buffer5 = "[[],[],[]]";
    size = strlen(buffer5);
    arr = microjson::parseJsonArray(buffer5, size);
    ASSERT_EQ(arr.size(), 3);
    EXPECT_STREQ(arr[0].value.c_str(), "[]");
    EXPECT_EQ(arr[0].type, microjson::JsonArrayType);
    EXPECT_STREQ(arr[1].value.c_str(), "[]");
    EXPECT_EQ(arr[1].type, microjson::JsonArrayType);
    EXPECT_STREQ(arr[2].value.c_str(), "[]");
    EXPECT_EQ(arr[2].type, microjson::JsonArrayType);

    const char *buffer6 = "[[],\"\",0,0.0,false]";
    size = strlen(buffer6);
    arr = microjson::parseJsonArray(buffer6, size);
    ASSERT_EQ(arr.size(), 5);
    EXPECT_STREQ(arr[0].value.c_str(), "[]");
    EXPECT_EQ(arr[0].type, microjson::JsonArrayType);
    EXPECT_STREQ(arr[1].value.c_str(), "");
    EXPECT_EQ(arr[1].type, microjson::JsonStringType);
    EXPECT_STREQ(arr[2].value.c_str(), "0");
    EXPECT_EQ(arr[2].type, microjson::JsonNumberType);
    EXPECT_STREQ(arr[3].value.c_str(), "0.0");
    EXPECT_EQ(arr[3].type, microjson::JsonNumberType);
    EXPECT_STREQ(arr[4].value.c_str(), "false");
    EXPECT_EQ(arr[4].type, microjson::JsonBoolType);

    const char *buffer7 = "[[[1111,2222,3333],[4444,5555,6666]],\"testString\",787,-123,0.0,0.99,1.0,1.2345+e10,false,[false,true],{\"testField1\":[\"testArrayValue1\", 2, 3, 4],\"testField2\":0.1212+e14}]";
    size = strlen(buffer7);
    arr = microjson::parseJsonArray(buffer7, size);
    ASSERT_EQ(arr.size(), 11);
    EXPECT_STREQ(arr[0].value.c_str(), "[[1111,2222,3333],[4444,5555,6666]]");
    EXPECT_EQ(arr[0].type, microjson::JsonArrayType);
    EXPECT_STREQ(arr[1].value.c_str(), "testString");
    EXPECT_EQ(arr[1].type, microjson::JsonStringType);
    EXPECT_STREQ(arr[2].value.c_str(), "787");
    EXPECT_EQ(arr[2].type, microjson::JsonNumberType);
    EXPECT_STREQ(arr[3].value.c_str(), "-123");
    EXPECT_EQ(arr[3].type, microjson::JsonNumberType);
    EXPECT_STREQ(arr[4].value.c_str(), "0.0");
    EXPECT_EQ(arr[4].type, microjson::JsonNumberType);
    EXPECT_STREQ(arr[5].value.c_str(), "0.99");
    EXPECT_EQ(arr[5].type, microjson::JsonNumberType);
    EXPECT_STREQ(arr[6].value.c_str(), "1.0");
    EXPECT_EQ(arr[6].type, microjson::JsonNumberType);
    EXPECT_STREQ(arr[7].value.c_str(), "1.2345+e10");
    EXPECT_EQ(arr[7].type, microjson::JsonNumberType);
    EXPECT_STREQ(arr[8].value.c_str(), "false");
    EXPECT_EQ(arr[8].type, microjson::JsonBoolType);
    EXPECT_STREQ(arr[9].value.c_str(), "[false,true]");
    EXPECT_EQ(arr[9].type, microjson::JsonArrayType);
    EXPECT_STREQ(arr[10].value.c_str(), "{\"testField1\":[\"testArrayValue1\", 2, 3, 4],\"testField2\":0.1212+e14}");
    EXPECT_EQ(arr[10].type, microjson::JsonObjectType);
}

TEST_F(MicrojsonDeserializationTest, PropertyName) {
    const char *buffer1 = "{\"testField1\":\"test2\"}";
    size_t size = strlen(buffer1);
    microjson::JsonObject obj = microjson::parseJsonObject(buffer1, size);
    auto it = obj.find("testField1");
    ASSERT_TRUE(it != obj.end());

    obj.clear();
    const char *buffer2 = "{\"t\":\"test2\"}";
    size = strlen(buffer2);
    obj = microjson::parseJsonObject(buffer2, size);
    it = obj.find("t");
    ASSERT_TRUE(it != obj.end());

    obj.clear();
    const char *buffer3 = "{\"\":\"test2\"}";
    size = strlen(buffer3);
    obj = microjson::parseJsonObject(buffer3, size);
    ASSERT_EQ(obj.size(), 0);

    obj.clear();
    const char *buffer4 = "{\"\\\"\":\"test2\"}";
    size = strlen(buffer4);
    obj = microjson::parseJsonObject(buffer4, size);
    it = obj.find("\\\"");
    ASSERT_TRUE(it != obj.end());

    obj.clear();
    const char *buffer5 = "{\"testField1{\":{\"testField2\":\"test2\"}}";
    size = strlen(buffer5);
    obj = microjson::parseJsonObject(buffer5, size);
    it = obj.find("testField1{");
    ASSERT_TRUE(it != obj.end());
    EXPECT_EQ(it->second.type, microjson::JsonObjectType);
    EXPECT_STREQ(it->second.value.c_str(), "{\"testField2\":\"test2\"}");

    obj.clear();
    const char *buffer6 = "{\"test}Field1}\":{\"testField2\":\"test2\"}}";
    size = strlen(buffer6);
    obj = microjson::parseJsonObject(buffer6, size);
    it = obj.find("test}Field1}");
    ASSERT_TRUE(it != obj.end());
    EXPECT_EQ(it->second.type, microjson::JsonObjectType);
    EXPECT_STREQ(it->second.value.c_str(), "{\"testField2\":\"test2\"}");

    obj.clear();
    const char *buffer7 = "{\"test[Fiel[d1}\":[\"test1\",\"test2\"]}";
    size = strlen(buffer7);
    obj = microjson::parseJsonObject(buffer7, size);
    it = obj.find("test[Fiel[d1}");
    ASSERT_TRUE(it != obj.end());
    EXPECT_EQ(it->second.type, microjson::JsonArrayType);
    EXPECT_STREQ(it->second.value.c_str(), "[\"test1\",\"test2\"]");

    obj.clear();
    const char *buffer8 = "{\"test]Fiel]d1}\":[\"test1\",\"test2\"]}";
    size = strlen(buffer8);
    obj = microjson::parseJsonObject(buffer8, size);
    it = obj.find("test]Fiel]d1}");
    ASSERT_TRUE(it != obj.end());
    EXPECT_EQ(it->second.type, microjson::JsonArrayType);
    EXPECT_STREQ(it->second.value.c_str(), "[\"test1\",\"test2\"]");
}

TEST_F(MicrojsonDeserializationTest, MixedStringValue) {
    const char *buffer1 = "{\"testField1\":[\"[[test2\",\"[test2\"]}";
    size_t size = strlen(buffer1);
    microjson::JsonObject obj = microjson::parseJsonObject(buffer1, size);
    auto it = obj.find("testField1");
    ASSERT_TRUE(it != obj.end());
    EXPECT_EQ(it->second.type, microjson::JsonArrayType);
    EXPECT_STREQ(it->second.value.c_str(), "[\"[[test2\",\"[test2\"]");

    const char *buffer2 = "{\"testField1\":{\"test]Fiel]d1}\":[\"[[test2\",\"}test{{2\"]}}";
    size = strlen(buffer2);
    obj = microjson::parseJsonObject(buffer2, size);
    it = obj.find("testField1");
    ASSERT_TRUE(it != obj.end());
    EXPECT_EQ(it->second.type, microjson::JsonObjectType);
    EXPECT_STREQ(it->second.value.c_str(), "{\"test]Fiel]d1}\":[\"[[test2\",\"}test{{2\"]}");
}
