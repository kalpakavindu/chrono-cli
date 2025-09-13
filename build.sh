#!/usr/bin/env bash

BUILD_DIR="build"
BUILD_CONFIG="Release"

if [[ ! -d "$BUILD_DIR" ]]; then
  mkdir "$BUILD_DIR"
fi

case $1 in
  dev) BUILD_CONFIG="Debug";;
esac

cmake . -B "$BUILD_DIR"
cmake --build "$BUILD_DIR" --config "$BUILD_CONFIG"
