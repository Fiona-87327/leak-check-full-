cc -D BUFFER_SIZE=42 

valgrind ./a.out
  
valgrind ./a.out test.txt

valgrind --leak-check=full --show-leak-kinds=all ./a.out test.txt
