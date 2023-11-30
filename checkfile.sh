read -p "Enter a filename: " filename

if [ -e "$filename" ]; then
    echo "File '$filename' exists."

    # Check file type
    if [ -f "$filename" ]; then
        echo "It's a regular file."
    elif [ -d "$filename" ]; then
        echo "It's a directory."
    else
        echo "It's a different type of file."
    fi

    # Check file permissions
    permissions=$(ls -l "$filename")
    echo "File permissions: $permissions"
else
    echo "File '$filename' does not exist."
fi
