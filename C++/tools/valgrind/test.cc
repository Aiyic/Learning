// valgrind --tool=memcheck --leak-check=full ./test 

int main() {
    int *array = new int(10);
    return 0;
}