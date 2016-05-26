#!/bin/sh

echo -e "\033[0;46mSubmodule\033[0;00m"
git submodule update --init --recursive

./travis_setup.sh
