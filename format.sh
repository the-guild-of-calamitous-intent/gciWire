#!/bin/zsh

clang-format -style=file:../dotfiles/clang-format.yml -i \
    src/**/*.hpp \
    gtests/**/*.cpp \
    examples/**/*.cpp