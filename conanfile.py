import os
from conans import ConanFile, CMake

class LifeGame(ConanFile):
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake"
    requires = "libx264/cci.20220602@LifeGame/stable"

    def build(self):
        cmake = CMake(self)
        cmake.configure(source_folder='.')
        cmake.build()

    def imports(self):
        self.copy("*.dll", dst="bin", src="bin")
        self.copy("*.dylib*", dst="bin", src="lib")
        self.copy('*.so*', dst='bin', src='lib')
