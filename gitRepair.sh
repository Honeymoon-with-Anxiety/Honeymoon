#!/bin/bash

mv -v .git .git_old
git init
git remote add origin "https://github.com/honeymoon-with-anxiety/honeymoon.git"
git fetch
git reset origin/E4A --mixed

