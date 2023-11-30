#!/bin/bash

read -p "Enter the path to the file: " file_path

# Check if the file exists
if [ -e "$file_path" ]; then
    # Get file type
    file_type=$(file -b "$file_path")
    
    # Get file permissions
    permissions=$(stat -c %A "$file_path")
    
    echo "File type: $file_type"
    echo "Permissions: $permissions"
else
    echo "File not found at path: $file_path"
fi


