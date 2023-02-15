RUN:
	nasm -felf64 encode_64_triplet.asm && gcc -no-pie main.c encode_64_triplet.o -o exec.out && ./exec.out assets/$(file)
