section .text
global sum_to_n
sum_to_n:
    add rax, rdi
    sub rdi, 1
    jg sum_to_n
	ret
