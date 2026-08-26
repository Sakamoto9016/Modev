#!/bin/bash

cd ~/Documents/Modev/main-u

git pull --rebase origin main
git add -A
git commit -m "Daily Refresh from Xerver"
git push origin main