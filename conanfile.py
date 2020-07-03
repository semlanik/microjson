from conans import ConanFile, CMake, tools
import os


class QtProtobufConan(ConanFile):
    name = "microjson"
    version = "0.1.0"
    license = "MIT"
    url = "https://github.com/semlanik/microjson"
    description = ("Tiny and simple JSON parser")
    topics = ("conan", "json")
    settings = "os", "compiler", "build_type", "arch"
    homepage = "https://github.com/semlanik/microjson"
    generators = "cmake"
    options = {"shared": [True, False]}
    default_options = {
        "shared": True,
    }
    scm = {
        "type": "git",
        "url": "auto",
        "revision": "auto",
    }
    exports_sources = "*"

    def _configure_cmake(self):
        cmake = CMake(self)
        cmake.definitions["MICROJSON_MAKE_TESTS"] = "OFF"
        cmake.configure()
        return cmake

    def build(self):
        cmake = self._configure_cmake()
        cmake.build()
        cmake.install()

    def package(self):
        cmake = self._configure_cmake()
        cmake.configure()
        cmake.install()

        self.copy("LICENSE", dst="licenses")

