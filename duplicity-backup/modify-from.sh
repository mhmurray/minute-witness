#!/bin/bash

echo "Modifying original files in backup-from/"

echo "mod " >> backup-from/dir1/file11
echo "mod " >> backup-from/dir1/file12

echo "mod " >> backup-from/dir2/dir21/file212

echo
tree backup-from
