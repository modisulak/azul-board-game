#!/bin/bash
(cd ./resources && find . -type f -print0 | xargs -0 dos2unix)
(cd ./save_files && find . -type f -print0 | xargs -0 dos2unix)
