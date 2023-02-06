import sys, os
from sys import platform

build_type = "--build-release"
enable_android_build = False

for i in range(1, len(sys.argv)):
    if (sys.argv[i] == "--build-release"):
        build_type = "--build-release"

    if (sys.argv[i] == "--build-debug"):
        build_type = "--build-debug"
    
    if (sys.argv[i] == "--enable-tidy"):
        enable_clang_tidy = sys.argv[i]

    if (sys.argv[i] == "--android"):
        enable_android_build = True

if (platform == "linux" or platform == "linux2"):
    if enable_android_build:
        archs = ["arm64-v8a", "armeabi-v7a", "x86_64", "x86"]

        profile_build = os.getcwd() + "/.ci/conan_profiles/conan_profile_linux_release"

        if (build_type == "--build-debug"):
            profile_build = os.getcwd() + "/.ci/conan_profiles/conan_profile_linux_debug"

        for arch in archs:
            profile_host = os.getcwd() + "/.ci/conan_profiles/Android/Release/host_android_" + arch + "_release"

            if (build_type == "--build-debug"):
                profile_host = os.getcwd() + "/.ci/conan_profiles/Android/Debug/host_android_" + arch + "_debug"

            # libx264DeployCommand = "conan create .ci/libx264_conan_recipe libx264/cci.20220602@LifeGame/stable -pr:h " + profile_host + " -pr:b=" + profile_build + " --build=missing"
            testDeployCommand = "conan create . libvideo/1.0.0@ccor/libvideo -tf None -pr:h " + profile_host + " -pr:b=" + profile_build + " --build=missing"

            # os.system(libx264DeployCommand)
            os.system(testDeployCommand)
    else:
        profile = os.getcwd() + "/.ci/conan_profiles/conan_profile_linux_release"

        if (build_type == "--build-debug"):
            profile = os.getcwd() + "/.ci/conan_profiles/conan_profile_linux_debug"
        
        libx264DeployCommand = "conan create .ci/libx264_conan_recipe libx264/cci.20220602@LifeGame/stable -pr=" + profile + " --build=missing"
        testDeployCommand = "conan create . libvideo/1.0.0@ccor/libvideo -tf None -pr=" + profile + " --build=missing"
        testInstallCommand = "conan install . --install-folder build_ -pr=" + profile + " --build=missing"

        os.system(libx264DeployCommand)
        os.system(testDeployCommand)
        os.system(testInstallCommand)

if (platform == "win32"):
    profile = os.getcwd() + "\.ci\conan_profiles\conan_profile_release"

    if (build_type == "--build-debug"):
        profile = os.getcwd() + "\.ci\conan_profiles\conan_profile_debug"

    libx264DeployCommand = "conan create .ci/libx264_conan_recipe libx264/cci.20220602@LifeGame/stable -pr=" + profile + " --build=missing"
    testInstallCommand = "conan install . --install-folder build_ -pr=" + profile + " --build=missing"

    os.system(libx264DeployCommand)
    os.system(testInstallCommand)