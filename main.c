#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

// Définition de la structure de liste
typedef struct s_list {
	void *data;
	struct s_list *next;
} t_list;

// Déclaration de la fonction assembleur
size_t ft_strlen(const char *str);
// changed: return type adjusted to match strcpy-like behaviour
char *ft_strcpy(const char *src, char *dst);
int ft_strcmp(const char *s1, const char *s2);
ssize_t ft_write(int fd, const void *buf, size_t count);
ssize_t ft_read(int fd, void *buf, size_t count);
char *ft_strdup(const char *s);
int ft_atoi_base(const char *str, const char *base);
void ft_list_push_front(t_list **begin_list, void *data);
int ft_list_size(t_list *begin_list);
void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));
void ft_list_sort(t_list **begin_list, int (*cmp)());

int main(void)
{
	char *test1 = "Hello, World!";
	char *test2 = "";
	char dst1[128];
	char dst2[128];
	t_list *current;
	

	// === ft_strlen ===
	printf("=== ft_strlen ===\n");
	printf("  \"%s\" -> ft: %zu, std: %zu\n", test1, ft_strlen(test1), strlen(test1));
	printf("  \"\" -> ft: %zu, std: %zu\n\n", ft_strlen(test2), strlen(test2));

	// === ft_strcpy ===
	printf("=== ft_strcpy ===\n");
	ft_strcpy(test1, dst1);
	strcpy(dst2, test1);
	printf("  \"%s\" -> ft: \"%s\", std: \"%s\"\n", test1, dst1, dst2);
	ft_strcpy(test2, dst1);
	strcpy(dst2, test2);
	printf("  \"\" -> ft: \"%s\", std: \"%s\"\n\n", dst1, dst2);

	// === ft_strcmp ===
	printf("=== ft_strcmp ===\n");
	printf("  \"Hello\" vs \"Hello\" -> ft: %d, std: %d\n", ft_strcmp("Hello", "Hello"), strcmp("Hello", "Hello"));
	printf("  \"Hello\" vs \"World\" -> ft: %d, std: %d\n", ft_strcmp("Hello", "World"), strcmp("Hello", "World"));
	printf("  \"World\" vs \"Hello\" -> ft: %d, std: %d\n", ft_strcmp("World", "Hello"), strcmp("World", "Hello"));
	printf("  \"ABC\" vs \"ABCD\" -> ft: %d, std: %d\n", ft_strcmp("ABC", "ABCD"), strcmp("ABC", "ABCD"));
	printf("  \"\" vs \"\" -> ft: %d, std: %d\n\n", ft_strcmp("", ""), strcmp("", ""));

	// === ft_write ===
	printf("=== ft_write ===\n");
	char *msg = "Test message\n";
	printf("  ft_write: ");
	fflush(stdout);
	ssize_t ret1 = ft_write(1, msg, strlen(msg));
	printf("  write: ");
	fflush(stdout);
	ssize_t ret2 = write(1, msg, strlen(msg));
	printf("  returns: ft=%zd, std=%zd\n\n", ret1, ret2);

	// === ft_read ===
	printf("=== ft_read ===\n");
	char read_buf[100];
	int pipefd[2];
	pipe(pipefd);
	write(pipefd[1], "Test data for read", 18);
	close(pipefd[1]);
	ssize_t read_ret = ft_read(pipefd[0], read_buf, 18);
	read_buf[read_ret] = '\0';
	printf("  ft_read: read %zd bytes: \"%s\"\n", read_ret, read_buf);
	close(pipefd[0]);
	printf("\n");

	// === ft_strdup ===
	printf("=== ft_strdup ===\n");
	char *dup1 = ft_strdup("Hello, World!");
	char *dup2 = strdup("Hello, World!");
	printf("  ft_strdup(\"Hello, World!\") -> \"%s\"\n", dup1);
	printf("  strdup(\"Hello, World!\") -> \"%s\"\n", dup2);
	printf("  Comparison: %d\n", strcmp(dup1, dup2));
	free(dup1);
	free(dup2);
	char *dup3 = ft_strdup("");
	printf("  ft_strdup(\"\") -> \"%s\" (len=%zu)\n\n", dup3, strlen(dup3));
	free(dup3);

	// === ft_atoi_base ===
	printf("=== ft_atoi_base ===\n");
	printf("  \"1234\" base 10 -> %d (expected: 1234)\n", ft_atoi_base("1234", "0123456789"));
	printf("  \"   -42\" base 10 -> %d (expected: -42)\n", ft_atoi_base("   -42", "0123456789"));
	printf("  \"FF\" base 16 -> %d (expected: 255)\n", ft_atoi_base("FF", "0123456789ABCDEF"));
	printf("  \"1010\" base 2 -> %d (expected: 10)\n", ft_atoi_base("1010", "01"));
	printf("  \"377\" base 8 -> %d (expected: 255)\n", ft_atoi_base("377", "01234567"));
	printf("  \"\" base 10 -> %d (expected: 0)\n", ft_atoi_base("", "0123456789"));
	printf("  Invalid base (duplicate) -> %d (expected: 0)\n\n", ft_atoi_base("123", "0123456789+"));

	// === ft_list_push_front & ft_list_size ===
	printf("=== ft_list_push_front & ft_list_size ===\n");
	t_list *list = NULL;
	
	printf("  Vide: size=%d\n", ft_list_size(list));
	
	ft_list_push_front(&list, "A");
	ft_list_push_front(&list, "B");
	ft_list_push_front(&list, "C");
	printf("  Après 3 push: size=%d, elements: ", ft_list_size(list));
	current = list;
	while (current) {
		printf("[%s]", (char *)current->data);
		if (current->next) printf("->");
		current = current->next;
	}
	printf("\n\n");

	while (list) {
		t_list *temp = list;
		list = list->next;
		free(temp);
	}

	// === ft_list_remove_if ===
	printf("=== ft_list_remove_if ===\n");

	int cmp_str(char *s1, char *s2) { return strcmp(s1, s2); }
	void free_str(void *ptr) { (void)ptr; }

	// Test 1: Supprimer en tête
	t_list *test_list = NULL;
	ft_list_push_front(&test_list, "C");
	ft_list_push_front(&test_list, "B");
	ft_list_push_front(&test_list, "A");
	
	printf("  Avant: ");
	current = test_list;
	while (current) {
		printf("[%s]", (char *)current->data);
		if (current->next) printf("->");
		current = current->next;
	}
	printf("\n");
	
	ft_list_remove_if(&test_list, "A", (int (*)())cmp_str, free_str);
	
	printf("  Après suppression 'A': ");
	current = test_list;
	while (current) {
		printf("[%s]", (char *)current->data);
		if (current->next) printf("->");
		current = current->next;
	}
	printf("\n");

	// Test 2: Supprimer multiples
	ft_list_push_front(&test_list, "A");
	ft_list_push_front(&test_list, "B");
	ft_list_push_front(&test_list, "A");
	
	printf("  Avant: ");
	current = test_list;
	while (current) {
		printf("[%s]", (char *)current->data);
		if (current->next) printf("->");
		current = current->next;
	}
	printf("\n");
	
	ft_list_remove_if(&test_list, "A", (int (*)())cmp_str, free_str);
	
	printf("  Après suppression tous 'A': ");
	current = test_list;
	while (current) {
		printf("[%s]", (char *)current->data);
		if (current->next) printf("->");
		current = current->next;
	}
	printf("\n");

	// Test 3: Liste vide
	t_list *empty = NULL;
	ft_list_remove_if(&empty, "X", (int (*)())cmp_str, free_str);
	printf("  Liste vide: %s\n\n", empty == NULL ? "OK" : "ERREUR");

	while (test_list) {
		t_list *temp = test_list;
		test_list = test_list->next;
		free(temp);
	}

	// === ft_list_sort ===
	printf("=== ft_list_sort ===\n");
	
	int cmp_int(int *a, int *b) { return *a - *b; }
	
	// Test avec des entiers
	t_list *sort_list = NULL;
	int val1 = 5, val2 = 2, val3 = 8, val4 = 1, val5 = 9;
	ft_list_push_front(&sort_list, &val1);
	ft_list_push_front(&sort_list, &val2);
	ft_list_push_front(&sort_list, &val3);
	ft_list_push_front(&sort_list, &val4);
	ft_list_push_front(&sort_list, &val5);
	
	printf("  Avant tri: ");
	current = sort_list;
	while (current) {
		printf("[%d]", *(int *)current->data);
		if (current->next) printf("->");
		current = current->next;
	}
	printf("\n");
	
	ft_list_sort(&sort_list, (int (*)())cmp_int);
	
	printf("  Après tri: ");
	current = sort_list;
	while (current) {
		printf("[%d]", *(int *)current->data);
		if (current->next) printf("->");
		current = current->next;
	}
	printf("\n");
	
	// Test avec des strings
	t_list *str_list = NULL;
	ft_list_push_front(&str_list, "Zebra");
	ft_list_push_front(&str_list, "Apple");
	ft_list_push_front(&str_list, "Mango");
	ft_list_push_front(&str_list, "Banana");
	
	printf("  Avant tri (strings): ");
	current = str_list;
	while (current) {
		printf("[%s]", (char *)current->data);
		if (current->next) printf("->");
		current = current->next;
	}
	printf("\n");
	
	ft_list_sort(&str_list, (int (*)())cmp_str);
	
	printf("  Après tri (strings): ");
	current = str_list;
	while (current) {
		printf("[%s]", (char *)current->data);
		if (current->next) printf("->");
		current = current->next;
	}
	printf("\n");
	
	// Nettoyage
	while (sort_list) {
		t_list *temp = sort_list;
		sort_list = sort_list->next;
		free(temp);
	}
	while (str_list) {
		t_list *temp = str_list;
		str_list = str_list->next;
		free(temp);
	}

	return (0);
}
