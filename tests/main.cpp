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
    microjson::JsonObject obj = microjson::parseObject(buffer1, size);
    auto it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonStringType);
    EXPECT_STREQ(it->second.value.c_str(), "test");

    obj.clear();
    const char *buffer2 = "{\"testField\":\"\"}";
    size = strlen(buffer2);
    obj = microjson::parseObject(buffer2, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonStringType);
    EXPECT_STREQ(it->second.value.c_str(), "");

    obj.clear();
    const char *buffer3 = "{\"testField\":\"t\"}";
    size = strlen(buffer3);
    obj = microjson::parseObject(buffer3, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonStringType);
    EXPECT_STREQ(it->second.value.c_str(), "t");

    obj.clear();
    const char *buffer4 = "{\"testField\":\"\\\"test\\\"\"}";
    size = strlen(buffer4);
    obj = microjson::parseObject(buffer4, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonStringType);
    EXPECT_STREQ(it->second.value.c_str(), "\\\"test\\\"");

    obj.clear();
    const char *buffer5 = "{\"testField\":\"\\\"test\"}";
    size = strlen(buffer5);
    obj = microjson::parseObject(buffer5, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonStringType);
    EXPECT_STREQ(it->second.value.c_str(), "\\\"test");

    obj.clear();
    const char *buffer6 = "{\"testField\":\"\\\"\"}";
    size = strlen(buffer6);
    obj = microjson::parseObject(buffer6, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonStringType);
    EXPECT_STREQ(it->second.value.c_str(), "\\\"");

    obj.clear();
    const char *buffer7 = "{\"testField\":\"test\",\"testField1\":\"\",\"testField2\":\"t\",\"testField3\":\"\\\"test\\\"\",\"testField4\":\"\\\"test\",\"testField5\":\"\\\"\"}";
    size = strlen(buffer7);
    obj = microjson::parseObject(buffer7, size);
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
    microjson::JsonObject obj = microjson::parseObject(buffer1, size);
    auto it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "5");

    obj.clear();
    const char *buffer2 = "{\"testField\":56}";
    size = strlen(buffer2);
    obj = microjson::parseObject(buffer2, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "56");

    obj.clear();
    const char *buffer3 = "{\"testField\":0}";
    size = strlen(buffer3);
    obj = microjson::parseObject(buffer3, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "0");

    obj.clear();
    const char *buffer4 = "{\"testField\":-5}";
    size = strlen(buffer4);
    obj = microjson::parseObject(buffer4, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "-5");

    obj.clear();
    const char *buffer5 = "{\"testField\":-131}";
    size = strlen(buffer5);
    obj = microjson::parseObject(buffer5, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "-131");

    obj.clear();
    const char *buffer6 = "{\"testField\":5,\"testField1\":56,\"testField2\":0,\"testField3\":-8,\"testField4\":-124}";
    size = strlen(buffer6);
    obj = microjson::parseObject(buffer6, size);
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
    microjson::JsonObject obj = microjson::parseObject(buffer1, size);
    auto it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "5");

    const char *buffer2 = "\n\r\t  {\n\r\t \"testField\"\n\r\t :   5\n\t \r, \n\r\t \"testField2\"\n\r\t :   -0.932e+10\n\t \r}\n\t \r";
    size = strlen(buffer2);
    obj = microjson::parseObject(buffer2, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "5");

    it = obj.find("testField2");
    ASSERT_TRUE(it != obj.end());
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "-0.932e+10");


    const char *buffer3 = "\n\r\t  {\n\r\t \"testField\"\n\r\t :   \"5\"\n\t \r, \n\r\t \"testField2\"\n\r\t :   \"\\\"qwerty\t\t\t\t\"\n\t \r}\n\t \r";
    size = strlen(buffer3);
    obj = microjson::parseObject(buffer3, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_EQ(it->second.type, microjson::JsonStringType);
    EXPECT_STREQ(it->second.value.c_str(), "5");

    it = obj.find("testField2");
    ASSERT_TRUE(it != obj.end());
    EXPECT_EQ(it->second.type, microjson::JsonStringType);
    EXPECT_STREQ(it->second.value.c_str(), "\\\"qwerty\t\t\t\t");
}

TEST_F(MicrojsonDeserializationTest, BooleanValue)
{
    const char *buffer1 = "{\"testField\":true}";
    size_t size = strlen(buffer1);
    microjson::JsonObject obj = microjson::parseObject(buffer1, size);
    auto it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonBoolType);
    EXPECT_STREQ(it->second.value.c_str(), "true");

    obj.clear();
    const char *buffer2 = "{\"testField\":false}";
    size = strlen(buffer2);
    obj = microjson::parseObject(buffer2, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonBoolType);
    EXPECT_STREQ(it->second.value.c_str(), "false");
    obj.clear();
    const char *buffer7 = "{\"testField\":true,\"testField1\":false}";
    size = strlen(buffer7);
    obj = microjson::parseObject(buffer7, size);
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
    microjson::JsonObject obj = microjson::parseObject(buffer1, size);
    auto it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "0.0");

    obj.clear();
    const char *buffer2 = "{\"testField\":1.0}";
    size = strlen(buffer2);
    obj = microjson::parseObject(buffer2, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "1.0");

    obj.clear();
    const char *buffer3 = "{\"testField\":20.0}";
    size = strlen(buffer3);
    obj = microjson::parseObject(buffer3, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "20.0");

    obj.clear();
    const char *buffer4 = "{\"testField\":20.01}";
    size = strlen(buffer4);
    obj = microjson::parseObject(buffer4, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "20.01");

    obj.clear();
    const char *buffer5 = "{\"testField\":-1.0}";
    size = strlen(buffer5);
    obj = microjson::parseObject(buffer5, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "-1.0");

    obj.clear();
    const char *buffer6 = "{\"testField\":-87.0}";
    size = strlen(buffer6);
    obj = microjson::parseObject(buffer6, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "-87.0");

    obj.clear();
    const char *buffer7 = "{\"testField\":-11.21}";
    size = strlen(buffer7);
    obj = microjson::parseObject(buffer7, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "-11.21");

    obj.clear();
    const char *buffer8 = "{\"testField\":1.1234+e10}";
    size = strlen(buffer8);
    obj = microjson::parseObject(buffer8, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "1.1234+e10");

    obj.clear();
    const char *buffer9 = "{\"testField\":1.1234-e10}";
    size = strlen(buffer9);
    obj = microjson::parseObject(buffer9, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "1.1234-e10");

    obj.clear();
    const char *buffer10 = "{\"testField\":-1.1234-e10}";
    size = strlen(buffer10);
    obj = microjson::parseObject(buffer10, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "-1.1234-e10");

    obj.clear();
    const char *buffer11 = "{\"testField\":-1.1234+e10}";
    size = strlen(buffer11);
    obj = microjson::parseObject(buffer11, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonNumberType);
    EXPECT_STREQ(it->second.value.c_str(), "-1.1234+e10");

    obj.clear();
    const char *buffer12 = "{\"testField\":0.0,\"testField1\":1.0,\"testField2\":20.0,\"testField3\":20.01,\"testField4\":-1.0,\"testField5\":-87.0,\"testField6\":-11.21,\"testField7\":1.1234+e10,\"testField8\":1.1234-e10,\"testField9\":-1.1234-e10,\"testField10\":-1.1234+e10}";
    size = strlen(buffer12);
    obj = microjson::parseObject(buffer12, size);
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
    microjson::JsonObject obj = microjson::parseObject(buffer1, size);
    auto it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonArrayType);
    EXPECT_STREQ(it->second.value.c_str(), "\"test1\"");

    obj.clear();
    const char *buffer2 = "{\"testField\":[\"test1\",\"test2\",\"test3\",\"test5\",\"test6\"]}";
    size = strlen(buffer2);
    obj = microjson::parseObject(buffer2, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonArrayType);
    EXPECT_STREQ(it->second.value.c_str(), "\"test1\",\"test2\",\"test3\",\"test5\",\"test6\"");

    obj.clear();
    const char *buffer3 = "{\"testField\":[],\"testField1\":[\"test1\",\"test2\"]}";
    size = strlen(buffer3);
    obj = microjson::parseObject(buffer3, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonArrayType);
    EXPECT_STREQ(it->second.value.c_str(), "");
    it = obj.find("testField1");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField1");
    EXPECT_EQ(it->second.type, microjson::JsonArrayType);
    EXPECT_STREQ(it->second.value.c_str(), "\"test1\",\"test2\"");

    obj.clear();
    const char *buffer4 = "{\"testField\":[1,1.0,-10,\"test1\",{\"test2\":15}]}";
    size = strlen(buffer4);
    obj = microjson::parseObject(buffer4, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonArrayType);
    EXPECT_STREQ(it->second.value.c_str(), "1,1.0,-10,\"test1\",{\"test2\":15}");

    obj.clear();
    const char *buffer5 = "{\"testField\":[[1,2,3,4,5,6],[7,8,9,10,\"test1\"]]}";
    size = strlen(buffer5);
    obj = microjson::parseObject(buffer5, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonArrayType);
    EXPECT_STREQ(it->second.value.c_str(), "[1,2,3,4,5,6],[7,8,9,10,\"test1\"]");

    obj.clear();
    const char *buffer6 = "{\"testField\":[{\"test1\":[1,2,3,4,5,{\"test2\":[\"test3\",\"test4\",[1,2,3,4]]}]}]}";
    size = strlen(buffer6);
    obj = microjson::parseObject(buffer6, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonArrayType);
    EXPECT_STREQ(it->second.value.c_str(), "{\"test1\":[1,2,3,4,5,{\"test2\":[\"test3\",\"test4\",[1,2,3,4]]}]}");

    const char *buffer7 = "{\"testField\":[\"test1\"],\"testField1\":[\"test1\",\"test2\",\"test3\",\"test5\",\"test6\"],\"testField2\":[],\"testField3\":[\"test1\",\"test2\"],\"testField4\":[1,1.0,-10,\"test1\",{\"test2\":15}],\"testField5\":[[1,2,3,4,5,6],[7,8,9,10,\"test1\"]],\"testField6\":[{\"test1\":[1,2,3,4,5,{\"test2\":[\"test3\",\"test4\",[1,2,3,4]]}]}]}";
    size = strlen(buffer7);
    obj = microjson::parseObject(buffer7, size);

    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonArrayType);
    EXPECT_STREQ(it->second.value.c_str(), "\"test1\"");

    it = obj.find("testField1");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField1");
    EXPECT_EQ(it->second.type, microjson::JsonArrayType);
    EXPECT_STREQ(it->second.value.c_str(), "\"test1\",\"test2\",\"test3\",\"test5\",\"test6\"");

    it = obj.find("testField2");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField2");
    EXPECT_EQ(it->second.type, microjson::JsonArrayType);
    EXPECT_STREQ(it->second.value.c_str(), "");

    it = obj.find("testField3");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField3");
    EXPECT_EQ(it->second.type, microjson::JsonArrayType);
    EXPECT_STREQ(it->second.value.c_str(), "\"test1\",\"test2\"");

    it = obj.find("testField4");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField4");
    EXPECT_EQ(it->second.type, microjson::JsonArrayType);
    EXPECT_STREQ(it->second.value.c_str(), "1,1.0,-10,\"test1\",{\"test2\":15}");

    it = obj.find("testField5");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField5");
    EXPECT_EQ(it->second.type, microjson::JsonArrayType);
    EXPECT_STREQ(it->second.value.c_str(), "[1,2,3,4,5,6],[7,8,9,10,\"test1\"]");

    it = obj.find("testField6");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField6");
    EXPECT_EQ(it->second.type, microjson::JsonArrayType);
    EXPECT_STREQ(it->second.value.c_str(), "{\"test1\":[1,2,3,4,5,{\"test2\":[\"test3\",\"test4\",[1,2,3,4]]}]}");
}

TEST_F(MicrojsonDeserializationTest, ObjectValue)
{
    const char *buffer1 = "{\"testField\":{\"testField1\":1}}";
    size_t size = strlen(buffer1);
    microjson::JsonObject obj = microjson::parseObject(buffer1, size);
    auto it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonObjectType);
    EXPECT_STREQ(it->second.value.c_str(), "\"testField1\":1");

    const char *buffer2 = "{\"testField\":{\"testField1\":1,\"testField2\":2}}";
    size = strlen(buffer2);
    obj = microjson::parseObject(buffer2, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonObjectType);
    EXPECT_STREQ(it->second.value.c_str(), "\"testField1\":1,\"testField2\":2");

    const char *buffer3 = "{\"testField\":{\"testField1\":1.0,\"testField2\":\"2\"}}";
    size = strlen(buffer3);
    obj = microjson::parseObject(buffer3, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonObjectType);
    EXPECT_STREQ(it->second.value.c_str(), "\"testField1\":1.0,\"testField2\":\"2\"");

    const char *buffer4 = "{\"testField\":{}}";
    size = strlen(buffer4);
    obj = microjson::parseObject(buffer4, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonObjectType);
    EXPECT_STREQ(it->second.value.c_str(), "");

    const char *buffer5 = "{\"testField\":{\"testField1\":{},\"testField2\":{\"testField3\":\"2\"}}}";
    size = strlen(buffer5);
    obj = microjson::parseObject(buffer5, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonObjectType);
    EXPECT_STREQ(it->second.value.c_str(), "\"testField1\":{},\"testField2\":{\"testField3\":\"2\"}");

    const char *buffer6 = "{\"testField\":{\"testField1\":{},\"testField2\":{\"testField3\":[\"2\",0,1,2,{\"testField4\":9}]}}}";
    size = strlen(buffer6);
    obj = microjson::parseObject(buffer6, size);
    it = obj.find("testField");
    ASSERT_TRUE(it != obj.end());
    EXPECT_STREQ(it->first.c_str(), "testField");
    EXPECT_EQ(it->second.type, microjson::JsonObjectType);
    EXPECT_STREQ(it->second.value.c_str(), "\"testField1\":{},\"testField2\":{\"testField3\":[\"2\",0,1,2,{\"testField4\":9}]}");
}
