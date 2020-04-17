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
    obj.find("testField");
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
    obj.find("testField");
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
