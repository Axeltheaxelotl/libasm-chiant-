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
ssize_t ft_write(int fd, const void *buf, size_t count);
void ft_list_push_front(t_list **begin_list, void *data);
int ft_list_size(t_list *begin_list);
void ft_list_remove_if(t_list **begin_list, void *data_ref, int (*cmp)(), void (*free_fct)(void *));

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

	return (0);
}
