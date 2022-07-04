#!/bin/bash

BUILD_TYPE="Release"
if [ "$#" -ge "1" ]; then
        BUILD_TYPE=$1;
fi

PROJECT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
BUILD_DIR="${PROJECT_DIR}/build/"
BIN_DIR="${PROJECT_DIR}/bin/"
CONAN_DIR="${PROJECT_DIR}/conan/"

rm -rf "$BUILD_DIR";
rm -rf "$BIN_DIR";

echo "Project dir: " ${PROJECT_DIR};
echo "Build   dir: " ${BUILD_DIR};
echo "Conan   dir: " ${CONAN_DIR};
echo "BUILD  TYPE: " ${BUILD_TYPE}

if [ -d "$BUILD_DIR" ]; then
    cd "$BUILD_DIR"
else
    mkdir "$BUILD_DIR"
    cd "$BUILD_DIR"
fi

conan install -s build_type=$BUILD_TYPE "${CONAN_DIR}"

echo "${CONAN_DIR}/conan_toolchain.cmake"

cmake .. -DCMAKE_BUILD_TYPE=$BUILD_TYPE \
         -DCMAKE_TOOLCHAIN_FILE="${BUILD_DIR}conan_toolchain.cmake"
cmake --build "$BUILD_DIR"

