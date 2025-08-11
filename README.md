# Fdf
## Project from 42 school defended at Hive Helsinki
This project will teach the basics of graphics programming, particularly how
to place points in space, connect them , and most importantly, how to view
the scene from a specific viewpoint.

The objective of this project is to create a 3d representation of a landscape.
Creating a siimple wireframe model representation of 3d landscape by linking
various points  (x, y, z) thanks to line segments(edges).
This is the first graphical project of the 42 school, the library allowed to 
be used is minilibx or MLX42. 

### Instalation

clone the repository
```
git clone https://github.com/EzLucca/rank2_fdf rank2_fdf
```
compile the executable
```
cd rank2_fdf && make
```
Run with this command
```
./fdf test_maps/<map_name>.fdf
```

### Usefull commands

This command will show a rule for each error found as MLX leaks.
```
valgrind --leak-check=full --gen-suppressions=all --log-file=valgrind_output.txt ./fdf test_maps/pyramide.fdf
```
```
grep -v '^==' valgrind_output.txt > valgrind.supp
```
```
awk ' BEGIN { RS="}\n"; ORS="" } !seen[$0]++ { print $0 "}\n" } ' suppressions.supp > cleaned.supp
```
The next time run the command and errors will be suppressed
```
valgrind --leak-check=full --suppressions=valgrind.supp ./fdf <map>
valgrind --leak-check=full --track-origins=yes --show-reachable=yes --suppressions=mlx.supp ./fdf <map>
```
### Fonts
`https://pedromelodev.com/index.php/2024/01/14/fdf-chronicles-navigating-the-pro-world-of-2d-projections/`
`https://medium.com/@ouaallaabdelali1/fdf-725b6255d053`
`http://43.128.62.24:91/ArthurSobreira/map_generator_fdf`
`https://velog.io/@tmdgks2222/fdf`
`https://github.com/8luerose/FDF.git`
`https://github.com/ailopez-o/42Barcelona-FdF`
`https://www.youtube.com/watch?v=y_SPO_b-WXk&t=604s`
`https://www.youtube.com/watch?v=CceepU1vIKo`
