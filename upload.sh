#!/bin/bash

cd ~/Documents/Modev/main-u
git add .
git commit -m "Change was made automatically from Xerver, which is Andrew's laptop."
git pull --rebase origin main
git push origin main