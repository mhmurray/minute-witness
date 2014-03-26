#!/bin/bash

echo "Making backup..."
echo "duplicity --no-encryption backup-from file://backup-to/"
duplicity --no-encryption backup-from file://backup-to/

echo "Original:"
tree backup-from

echo "Backup:"
tree backup-to
