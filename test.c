#include <stdio.h>
#include <string.h>

// Fonction avec de l'assembly inline
size_t ft_strlen_inline(const char *s)
{
	size_t len;
	
	// Assembly inline en syntaxe AT&T (GCC)
	__asm__ volatile (
		"xor %%rax, %%rax\n\t"           // rax = 0
		"1:\n\t"                          // label loop
		"cmpb $0, (%%rdi, %%rax)\n\t"    // compare byte à [rdi + rax] avec 0
		"je 2f\n\t"                       // si égal, saute à label 2
		"inc %%rax\n\t"                   // rax++
		"jmp 1b\n\t"                      // retour au label 1
		"2:\n\t"                          // label exit
		: "=a" (len)                      // output: rax -> len
		: "D" (s)                         // input: rdi <- s
		: "cc", "memory"                  // clobbers
	);
	
	return len;
}

// Déclaration de la fonction assembleur externe
extern size_t ft_strlen(const char *s);

int main(void)
{
	const char *test = "Hello, Assembly!";
	
	printf("Test avec assembly inline:\n");
	printf("String: '%s'\n", test);
	printf("Length (inline asm): %zu\n", ft_strlen_inline(test));
	printf("Length (stdlib): %zu\n", strlen(test));
	
	// Si vous avez compilé ft_strlen.s
	// printf("Length (external asm): %zu\n", ft_strlen(test));
	
	// Exemple d'assembly inline simple
	int a = 5, b = 10, result;
	__asm__ (
		"addl %%ebx, %%eax"
		: "=a" (result)
		: "a" (a), "b" (b)
	);
	printf("\nAddition avec assembly inline: %d + %d = %d\n", a, b, result);
	
	return 0;
}
