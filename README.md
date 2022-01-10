### Welcome to my ft_containers repository 👋

⭐️ The objective of ft_containers is to implement the various container types of the C++ standard template library (coded in C++98).<br>
Containers implemented : vector, stack and map.

## 💡 Usage

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