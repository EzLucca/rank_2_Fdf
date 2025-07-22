# Fdf
## Project from 42 school defended at Hive Helsinki
This project will teach the basics of graphics programming, particularly how
to place points in space, connect them , and most importantly, how to view
the scene from a specific viewpoint.

The objective of this project is to create a 3d representation of a landscape.
Creating a siimple wireframe model representation of 3d landscape by linking
various points  (x, y, z) thanks to line segments(edges).
This is the first graphical project of the 42 school, the library allowed to 
be used is minilibx. 

### The Functions 
### The logic
1. Argv checks
2. Map validation
- [x] correct extension
- [x] empty map?
- [x] empty point?
- [x] empty line in between?
- [x] check point values
- [x] check color values
3. Input of data
- [x] Malloc grid
- [x] Fill the grid
4. Draw points and line
5. visualization
### The Bonus

### Tools

This command will show a rule for each error found
```
valgrind --leak-check=full --gen-suppressions=all --log-file=filename.txt ./your_program
```
```
grep -v '^==' valgrind_output.txt > cleaned_output.supp
```
```
awk ' BEGIN { RS="}\n"; ORS="" } !seen[$0]++ { print $0 "}\n" } ' suppressions.supp > cleaned.supp
```
The next time run the command and errors will be suppressed
```
valgrind --leak-check=full --suppressions=<file>.supp ./your_program
```
### Fonts
`https://pedromelodev.com/index.php/2024/01/14/fdf-chronicles-navigating-the-pro-world-of-2d-projections/`
`https://medium.com/@ouaallaabdelali1/fdf-725b6255d053`
`http://43.128.62.24:91/ArthurSobreira/map_generator_fdf`
`https://velog.io/@tmdgks2222/fdf`
`https://github.com/8luerose/FDF.git`
`https://github.com/ailopez-o/42Barcelona-FdF`
