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

	// --- Tests pour ft_list_remove_if ---
	printf("=== Test de ft_list_remove_if ===\n\n");

	// Fonctions de comparaison et de libération pour les tests
	int cmp_str(char *s1, char *s2)
	{
		return strcmp(s1, s2);
	}

	int cmp_int(int *n1, int *n2)
	{
		return (*n1 - *n2);
	}

	void free_str(void *ptr)
	{
		// Pour les chaînes littérales, on ne libère pas
		// Dans un cas réel avec strdup, il faudrait free(ptr)
		(void)ptr;
	}

	void free_int(void *ptr)
	{
		// Pour les entiers sur la pile, on ne libère pas
		(void)ptr;
	}

	// Test 1 : Supprimer un élément en tête
	printf("Test 1: Supprimer élément en TÊTE\n");
	t_list *test_list1 = NULL;
	ft_list_push_front(&test_list1, "Trois");
	ft_list_push_front(&test_list1, "Deux");
	ft_list_push_front(&test_list1, "Un");
	
	printf("  Liste avant: ");
	current = test_list1;
	while (current)
	{
		printf("[%s] -> ", (char *)current->data);
		current = current->next;
	}
	printf("NULL\n");
	
	ft_list_remove_if(&test_list1, "Un", (int (*)())cmp_str, free_str);
	
	printf("  Liste après suppression de \"Un\": ");
	current = test_list1;
	while (current)
	{
		printf("[%s] -> ", (char *)current->data);
		current = current->next;
	}
	printf("NULL\n");
	printf("  Taille: %d\n\n", ft_list_size(test_list1));

	// Test 2 : Supprimer un élément au milieu
	printf("Test 2: Supprimer élément au MILIEU\n");
	ft_list_push_front(&test_list1, "Un"); // Liste: Un -> Deux -> Trois
	
	printf("  Liste avant: ");
	current = test_list1;
	while (current)
	{
		printf("[%s] -> ", (char *)current->data);
		current = current->next;
	}
	printf("NULL\n");
	
	ft_list_remove_if(&test_list1, "Deux", (int (*)())cmp_str, free_str);
	
	printf("  Liste après suppression de \"Deux\": ");
	current = test_list1;
	while (current)
	{
		printf("[%s] -> ", (char *)current->data);
		current = current->next;
	}
	printf("NULL\n");
	printf("  Taille: %d\n\n", ft_list_size(test_list1));

	// Test 3 : Supprimer un élément en fin
	printf("Test 3: Supprimer élément en FIN\n");
	
	printf("  Liste avant: ");
	current = test_list1;
	while (current)
	{
		printf("[%s] -> ", (char *)current->data);
		current = current->next;
	}
	printf("NULL\n");
	
	ft_list_remove_if(&test_list1, "Trois", (int (*)())cmp_str, free_str);
	
	printf("  Liste après suppression de \"Trois\": ");
	current = test_list1;
	while (current)
	{
		printf("[%s] -> ", (char *)current->data);
		current = current->next;
	}
	printf("NULL\n");
	printf("  Taille: %d\n\n", ft_list_size(test_list1));

	// Libérer test_list1
	while (test_list1)
	{
		t_list *temp = test_list1;
		test_list1 = test_list1->next;
		free(temp);
	}

	// Test 4 : Supprimer PLUSIEURS éléments (doublons)
	printf("Test 4: Supprimer PLUSIEURS éléments identiques\n");
	t_list *test_list2 = NULL;
	ft_list_push_front(&test_list2, "C");
	ft_list_push_front(&test_list2, "A");
	ft_list_push_front(&test_list2, "B");
	ft_list_push_front(&test_list2, "A");
	ft_list_push_front(&test_list2, "C");
	ft_list_push_front(&test_list2, "A");
	
	printf("  Liste avant: ");
	current = test_list2;
	while (current)
	{
		printf("[%s] -> ", (char *)current->data);
		current = current->next;
	}
	printf("NULL\n");
	printf("  Taille: %d\n", ft_list_size(test_list2));
	
	ft_list_remove_if(&test_list2, "A", (int (*)())cmp_str, free_str);
	
	printf("  Liste après suppression de tous les \"A\": ");
	current = test_list2;
	while (current)
	{
		printf("[%s] -> ", (char *)current->data);
		current = current->next;
	}
	printf("NULL\n");
	printf("  Taille: %d\n\n", ft_list_size(test_list2));

	// Libérer test_list2
	while (test_list2)
	{
		t_list *temp = test_list2;
		test_list2 = test_list2->next;
		free(temp);
	}

	// Test 5 : Supprimer TOUS les éléments
	printf("Test 5: Supprimer TOUS les éléments\n");
	t_list *test_list3 = NULL;
	ft_list_push_front(&test_list3, "X");
	ft_list_push_front(&test_list3, "X");
	ft_list_push_front(&test_list3, "X");
	
	printf("  Liste avant: ");
	current = test_list3;
	while (current)
	{
		printf("[%s] -> ", (char *)current->data);
		current = current->next;
	}
	printf("NULL\n");
	printf("  Taille: %d\n", ft_list_size(test_list3));
	
	ft_list_remove_if(&test_list3, "X", (int (*)())cmp_str, free_str);
	
	printf("  Liste après suppression de tous les \"X\": ");
	if (test_list3 == NULL)
		printf("NULL (liste vide)\n");
	else
	{
		current = test_list3;
		while (current)
		{
			printf("[%s] -> ", (char *)current->data);
			current = current->next;
		}
		printf("NULL\n");
	}
	printf("  Taille: %d\n\n", ft_list_size(test_list3));

	// Test 6 : Supprimer dans une liste d'entiers
	printf("Test 6: Supprimer dans une liste d'ENTIERS\n");
	t_list *test_list4 = NULL;
	int v1 = 10, v2 = 42, v3 = 21, v4 = 42, v5 = 99, v6 = 42;
	ft_list_push_front(&test_list4, &v6);
	ft_list_push_front(&test_list4, &v5);
	ft_list_push_front(&test_list4, &v4);
	ft_list_push_front(&test_list4, &v3);
	ft_list_push_front(&test_list4, &v2);
	ft_list_push_front(&test_list4, &v1);
	
	printf("  Liste avant: ");
	current = test_list4;
	while (current)
	{
		printf("[%d] -> ", *(int *)current->data);
		current = current->next;
	}
	printf("NULL\n");
	printf("  Taille: %d\n", ft_list_size(test_list4));
	
	int ref = 42;
	ft_list_remove_if(&test_list4, &ref, (int (*)())cmp_int, free_int);
	
	printf("  Liste après suppression de tous les 42: ");
	current = test_list4;
	while (current)
	{
		printf("[%d] -> ", *(int *)current->data);
		current = current->next;
	}
	printf("NULL\n");
	printf("  Taille: %d\n\n", ft_list_size(test_list4));

	// Libérer test_list4
	while (test_list4)
	{
		t_list *temp = test_list4;
		test_list4 = test_list4->next;
		free(temp);
	}

	// Test 7 : Supprimer dans une liste vide (edge case)
	printf("Test 7: Supprimer dans une LISTE VIDE\n");
	t_list *test_list5 = NULL;
	
	printf("  Liste avant: NULL\n");
	ft_list_remove_if(&test_list5, "X", (int (*)())cmp_str, free_str);
	printf("  Liste après: NULL\n");
	printf("  Taille: %d\n\n", ft_list_size(test_list5));

	// Test 8 : Supprimer un élément qui n'existe pas
	printf("Test 8: Supprimer un élément INEXISTANT\n");
	t_list *test_list6 = NULL;
	ft_list_push_front(&test_list6, "C");
	ft_list_push_front(&test_list6, "B");
	ft_list_push_front(&test_list6, "A");
	
	printf("  Liste avant: ");
	current = test_list6;
	while (current)
	{
		printf("[%s] -> ", (char *)current->data);
		current = current->next;
	}
	printf("NULL\n");
	printf("  Taille: %d\n", ft_list_size(test_list6));
	
	ft_list_remove_if(&test_list6, "Z", (int (*)())cmp_str, free_str);
	
	printf("  Liste après tentative de suppression de \"Z\": ");
	current = test_list6;
	while (current)
	{
		printf("[%s] -> ", (char *)current->data);
		current = current->next;
	}
	printf("NULL\n");
	printf("  Taille: %d (doit être inchangée)\n\n", ft_list_size(test_list6));

	// Libérer test_list6
	while (test_list6)
	{
		t_list *temp = test_list6;
		test_list6 = test_list6->next;
		free(temp);
	}

	printf("Tous les tests de ft_list_remove_if terminés!\n\n");

	return (0);
}
