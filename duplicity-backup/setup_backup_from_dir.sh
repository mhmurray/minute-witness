#!/bin/bash

echo "rm -rf backup-from/*"
rm -rf backup-from/*

echo "rm -rf backup-to/*"
rm -rf backup-to/*

echo "Making file tree in backup-from..."
mkdir backup-from/dir1
touch backup-from/dir1/file11
touch backup-from/dir1/file12
touch backup-from/dir1/file13
mkdir backup-from/dir2
mkdir backup-from/dir2/dir21
touch backup-from/dir2/dir21/file211

echo
tree backup-from
