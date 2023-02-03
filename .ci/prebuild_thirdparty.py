import sys, os
from sys import platform

build_type = "--build-release"

for i in range(1, len(sys.argv)):
    if (sys.argv[i] == "--build-release"):
        build_type = "--build-release"

    if (sys.argv[i] == "--build-debug"):
        build_type = "--build-debug"
    
    if (sys.argv[i] == "--enable-tidy"):
        enable_clang_tidy = sys.argv[i]

if (platform == "win32"):
    profile = os.getcwd() + "\.ci\conan_profiles\conan_profile_release"

    if (build_type == "--build-debug"):
        profile = os.getcwd() + "\.ci\conan_profiles\conan_profile_debug"

    libx264DeployCommand = "conan create .ci/libx264_conan_recipe libx264/cci.20220602@LifeGame/stable -pr=" + profile + " --build=missing"
    testInstallCommand = "conan install . --install-folder build_ -pr=" + profile + " --build=missing"

    os.system(libx264DeployCommand)
    os.system(testInstallCommand)