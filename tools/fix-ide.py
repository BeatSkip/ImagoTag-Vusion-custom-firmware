import os
import sys
import fileinput
from pathlib import Path

def replace_in_file(file_path):
    """Replace the specified line in a file and return True if changes were made."""
    old_line = '            "$output": "-MMD -o ${out} ${in}",'
    new_line = '            "$output": " -o ${out} ${in}",'
    
    changed = False
    temp_file = str(file_path) + '.tmp'
    
    try:
        with open(file_path, 'r') as file, open(temp_file, 'w') as temp:
            for line in file:
                if line.rstrip() == old_line:
                    temp.write(new_line + '\n')
                    changed = True
                else:
                    temp.write(line)
                    
        if changed:
            os.replace(temp_file, file_path)
        else:
            os.remove(temp_file)
            
        return changed
    
    except Exception as e:
        print(f"Error processing {file_path}: {str(e)}")
        if os.path.exists(temp_file):
            os.remove(temp_file)
        return False

def main():
    if len(sys.argv) != 3:
        print(f"Usage: {sys.argv[0]} <directory_path> <filename>")
        sys.exit(1)
        
    directory = Path(sys.argv[1])
    filename = sys.argv[2]
    
    if not directory.is_dir():
        print(f"Error: Directory '{directory}' does not exist")
        sys.exit(1)
    
    modified_count = 0
    
    # Find all matching files and process them
    for file_path in directory.rglob(filename):
        print(f"Processing: {file_path}")
        if replace_in_file(file_path):
            modified_count += 1
            print(f"Modified: {file_path}")
    
    print(f"\nCompleted! Modified {modified_count} files.")

if __name__ == "__main__":
    main()