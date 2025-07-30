# 1. Duplicate the entire src folder
cp -r src src_bonus

# 2. Navigate into the new src_bonus directory
cd src_bonus

# 3. Loop through all .c files and rename them
for file in *.c; do
	# Skip if no .c files are found (glob might expand to "*.c" literally)
	if [ ! -f "$file" ]; then
		continue
	fi

	filename_no_ext="${file%.*}"   # Gets "main", "utils", etc.
	extension="${file##*.}"       # Gets "c"
	new_filename="${filename_no_ext}_bonus.${extension}"

  # Rename the file
  mv "$file" "$new_filename"
  sed -i 's|#include "../include/fdf.h"|#include "../include_bonus/fdf_bonus.h"|g' $new_filename
	  echo "Renamed '$file' to '$new_filename'"
  done


# 4. Go back to your original directory
cd ..

# 1. Duplicate the entire src folder
cp -r include include_bonus

# 2. Navigate into the new src_bonus directory
cd include_bonus

# 3. Loop through all .c files and rename them
for file in *.h; do
	# Skip if no .h files are found (glob might expand to "*.h" literally)
	if [ ! -f "$file" ]; then
		continue
	fi

	filename_no_ext="${file%.*}"   # Gets "main", "utils", etc.
	extension="${file##*.}"       # Gets "c"
	new_filename="${filename_no_ext}_bonus.${extension}"

  # Rename the file
  mv "$file" "$new_filename"
  echo "Renamed '$file' to '$new_filename'"
done


# 4. Go back to your original directory
cd ..
