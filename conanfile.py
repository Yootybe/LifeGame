import os
from conans import ConanFile, CMake

class LifeGameLib(ConanFile):
    name = "liblife"
    version = "1.0.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"
    exports_sources = ["FieldProcessor.h", "FieldProcessor.cpp", "CMakeLists.txt"]

    def build(self):
        if self.settings.os == "Linux":
            os.environ["ANDROID_HOME"] = 
            os.environ["ANDROID_NDK"] =
            os.environ["ANDROID_NDK_HOME"] =
            os.environ["ANDROID_NDK_LATEST_HOME"] =
            os.environ["ANDROID_NDK_ROOT"] =
            os.environ["ANDROID_SDK_ROOT"] =
        cmake = CMake(self)
        cmake.configure(source_folder='.')
        cmake.build()

    def package(self):
        self.copy("*.h", dst="include", src="Include")
        self.copy("*.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.dylib*", dst="lib", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["liblife"]
