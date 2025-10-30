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

int main(void)
{
	char *test1 = "Hello, World!";
	char *test2 = "42";
	char *test3 = "";
	char *test4 = "This is a longer string to test";

	printf("=== Test de ft_strlen ===\n\n");

	printf("Test 1: \"%s\"\n", test1);
	printf("  ft_strlen: %zu\n", ft_strlen(test1));
	printf("  strlen:    %zu\n\n", strlen(test1));

	printf("Test 2: \"%s\"\n", test2);
	printf("  ft_strlen: %zu\n", ft_strlen(test2));
	printf("  strlen:    %zu\n\n", strlen(test2));

	printf("Test 3: \"%s\" (chaîne vide)\n", test3);
	printf("  ft_strlen: %zu\n", ft_strlen(test3));
	printf("  strlen:    %zu\n\n", strlen(test3));

	printf("Test 4: \"%s\"\n", test4);
	printf("  ft_strlen: %zu\n", ft_strlen(test4));
	printf("  strlen:    %zu\n\n", strlen(test4));

	// --- Ajout des tests pour ft_strcopy ---
	printf("=== Test de ft_strcopy ===\n\n");

	char dst1[128];
	char dst2[128];
	char dst3[128];
	char dst4[128];

	// Test 1 : chaîne normale
	char *ret_ft;
	char *ret_std;
	ret_ft = ft_strcpy(test1, dst1);
	ret_std = strcpy(dst2, test1);
	printf("Test 1: src \"%s\"\n", test1);
	printf("  ft_strcpy returned: %p dest: \"%s\"\n", (void*)ret_ft, dst1);
	printf("  strcpy        returned: %p dest: \"%s\"\n\n", (void*)ret_std, dst2);

	// Test 2 : petite chaîne
	ret_ft = ft_strcpy(test2, dst1);
	ret_std = strcpy(dst2, test2);
	printf("Test 2: src \"%s\"\n", test2);
	printf("  ft_strcpy returned: %p dest: \"%s\"\n", (void*)ret_ft, dst1);
	printf("  strcpy        returned: %p dest: \"%s\"\n\n", (void*)ret_std, dst2);

	// Test 3 : chaîne vide
	// pré-remplir dst3 pour vérifier que le terminator est bien écrit
	strcpy(dst3, "XXXXX");
	ret_ft = ft_strcpy(test3, dst3);
	ret_std = strcpy(dst4, test3);
	printf("Test 3: src (vide)\n");
	printf("  ft_strcpy returned: %p dest: \"%s\"\n", (void*)ret_ft, dst3);
	printf("  strcpy        returned: %p dest: \"%s\"\n\n", (void*)ret_std, dst4);

	// Test 4 : chaîne plus longue
	ret_ft = ft_strcpy(test4, dst1);
	ret_std = strcpy(dst2, test4);
	printf("Test 4: src \"%s\"\n", test4);
	printf("  ft_strcpy returned: %p dest: \"%s\"\n", (void*)ret_ft, dst1);
	printf("  strcpy        returned: %p dest: \"%s\"\n\n", (void*)ret_std, dst2);

	// --- Ajout des tests pour ft_write ---
	printf("=== Test de ft_write ===\n\n");

	ssize_t ret_write, ret_write_std;
	char *msg1 = "Test 1: Hello from ft_write!\n";
	char *msg2 = "Test 2: Short\n";
	char *msg3 = "";
	char *msg4 = "Test 4: Writing to stderr\n";

	// Test 1 : écriture normale sur stdout
	printf("Test 1: Écriture sur stdout\n");
	printf("  write:    ");
	fflush(stdout);
	ret_write_std = write(1, msg1, strlen(msg1));
	printf("  retour: %zd\n", ret_write_std);
	printf("  ft_write: ");
	fflush(stdout);
	ret_write = ft_write(1, msg1, strlen(msg1));
	printf("  retour: %zd\n\n", ret_write);

	// Test 2 : chaîne courte
	printf("Test 2: Chaîne courte\n");
	printf("  write:    ");
	fflush(stdout);
	ret_write_std = write(1, msg2, strlen(msg2));
	printf("  retour: %zd\n", ret_write_std);
	printf("  ft_write: ");
	fflush(stdout);
	ret_write = ft_write(1, msg2, strlen(msg2));
	printf("  retour: %zd\n\n", ret_write);

	// Test 3 : chaîne vide
	printf("Test 3: Chaîne vide\n");
	ret_write_std = write(1, msg3, 0);
	printf("  write retour:    %zd\n", ret_write_std);
	ret_write = ft_write(1, msg3, 0);
	printf("  ft_write retour: %zd\n\n", ret_write);

	// Test 4 : écriture sur stderr
	printf("Test 4: Écriture sur stderr\n");
	printf("  write:    ");
	fflush(stdout);
	ret_write_std = write(2, msg4, strlen(msg4));
	printf("  retour: %zd\n", ret_write_std);
	printf("  ft_write: ");
	fflush(stdout);
	ret_write = ft_write(2, msg4, strlen(msg4));
	printf("  retour: %zd\n\n", ret_write);

	// Test 5 : test d'erreur (fd invalide)
	printf("Test 5: File descriptor invalide (-1)\n");
	ret_write_std = write(-1, msg1, strlen(msg1));
	printf("  write retour:    %zd\n", ret_write_std);
	ret_write = ft_write(-1, msg1, strlen(msg1));
	printf("  ft_write retour: %zd\n\n", ret_write);

	// --- Tests pour ft_list_push_front et ft_list_size ---
	printf("=== Test de ft_list_push_front et ft_list_size ===\n\n");

	t_list *list = NULL;
	
	// Test 1 : liste vide
	printf("Test 1: Liste vide\n");
	printf("  Taille de la liste: %d\n", ft_list_size(list));
	printf("  Liste: NULL\n\n");

	// Test 2 : ajouter un premier élément
	printf("Test 2: Ajouter \"Premier\"\n");
	ft_list_push_front(&list, "Premier");
	printf("  Taille de la liste: %d\n", ft_list_size(list));
	printf("  Premier élément: %s\n\n", (char *)list->data);

	// Test 3 : ajouter un deuxième élément
	printf("Test 3: Ajouter \"Deuxième\"\n");
	ft_list_push_front(&list, "Deuxième");
	printf("  Taille de la liste: %d\n", ft_list_size(list));
	printf("  Premier élément: %s\n", (char *)list->data);
	printf("  Deuxième élément: %s\n\n", (char *)list->next->data);

	// Test 4 : ajouter un troisième élément
	printf("Test 4: Ajouter \"Troisième\"\n");
	ft_list_push_front(&list, "Troisième");
	printf("  Taille de la liste: %d\n", ft_list_size(list));
	printf("  Liste complète (du début à la fin):\n");
	t_list *current = list;
	int i = 1;
	while (current)
	{
		printf("    [%d] %s\n", i++, (char *)current->data);
		current = current->next;
	}
	printf("\n");

	// Test 5 : ajouter plusieurs éléments
	printf("Test 5: Ajouter 3 éléments supplémentaires\n");
	ft_list_push_front(&list, "Quatrième");
	ft_list_push_front(&list, "Cinquième");
	ft_list_push_front(&list, "Sixième");
	printf("  Taille de la liste: %d\n", ft_list_size(list));
	printf("  Liste complète:\n");
	current = list;
	i = 1;
	while (current)
	{
		printf("    [%d] %s\n", i++, (char *)current->data);
		current = current->next;
	}
	printf("\n");

	// Test 6 : tester avec des entiers
	printf("Test 6: Tester avec des entiers\n");
	t_list *int_list = NULL;
	int val1 = 42, val2 = 21, val3 = 84;
	ft_list_push_front(&int_list, &val1);
	ft_list_push_front(&int_list, &val2);
	ft_list_push_front(&int_list, &val3);
	printf("  Taille de la liste d'entiers: %d\n", ft_list_size(int_list));
	printf("  Liste d'entiers:\n");
	current = int_list;
	i = 1;
	while (current)
	{
		printf("    [%d] %d\n", i++, *(int *)current->data);
		current = current->next;
	}
	printf("\n");

	// Libération de la mémoire (optionnel, pour être propre)
	printf("Libération de la mémoire...\n");
	while (list)
	{
		t_list *temp = list;
		list = list->next;
		free(temp);
	}
	while (int_list)
	{
		t_list *temp = int_list;
		int_list = int_list->next;
		free(temp);
	}
	printf("Mémoire libérée.\n\n");

	return (0);
}
