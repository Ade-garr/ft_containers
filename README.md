# 📌 ft_containers 📌

The aim of this project is to re-implement some containers of the C++ standard library.<br>
Containers implemented : vector, stack and map.

## 🔑 How to

Two mains are included, one to test all the functionnalities, one to test performances.
```
make
./ft_containers > log1
make std
./ft_containers > log2
diff log1 log2
```
It will compile the first main once with my containers, then with classic STL containers. Diff to check that there is no difference.
```
make perf
./ft_containers
```
It will perform severals tests with both containers, monitoring time elapsed and printing the ratio between the two.