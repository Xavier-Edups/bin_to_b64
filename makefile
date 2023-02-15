RUN:
	nasm -felf64 encode_64_triplet.asm && gcc main.c encode_64_triplet.o -o exec.out && ./exec.out assets/test.bin