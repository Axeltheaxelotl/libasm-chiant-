#include <stdio.h>
#include <string.h>
#include <unistd.h>

// Déclaration de la fonction assembleur
size_t _ft_strlen(const char *str);
// changed: return type adjusted to match strcpy-like behaviour
char *_ft_strcopy(const char *src, char *dst);
ssize_t _ft_write(int fd, const void *buf, size_t count);

int main(void)
{
	char *test1 = "Hello, World!";
	char *test2 = "42";
	char *test3 = "";
	char *test4 = "This is a longer string to test";

	printf("=== Test de ft_strlen ===\n\n");

	printf("Test 1: \"%s\"\n", test1);
	printf("  ft_strlen: %zu\n", _ft_strlen(test1));
	printf("  strlen:    %zu\n\n", strlen(test1));

	printf("Test 2: \"%s\"\n", test2);
	printf("  ft_strlen: %zu\n", _ft_strlen(test2));
	printf("  strlen:    %zu\n\n", strlen(test2));

	printf("Test 3: \"%s\" (chaîne vide)\n", test3);
	printf("  ft_strlen: %zu\n", _ft_strlen(test3));
	printf("  strlen:    %zu\n\n", strlen(test3));

	printf("Test 4: \"%s\"\n", test4);
	printf("  ft_strlen: %zu\n", _ft_strlen(test4));
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
	ret_ft = _ft_strcopy(test1, dst1);
	ret_std = strcpy(dst2, test1);
	printf("Test 1: src \"%s\"\n", test1);
	printf("  _ft_strcopy returned: %p dest: \"%s\"\n", (void*)ret_ft, dst1);
	printf("  strcpy        returned: %p dest: \"%s\"\n\n", (void*)ret_std, dst2);

	// Test 2 : petite chaîne
	ret_ft = _ft_strcopy(test2, dst1);
	ret_std = strcpy(dst2, test2);
	printf("Test 2: src \"%s\"\n", test2);
	printf("  _ft_strcopy returned: %p dest: \"%s\"\n", (void*)ret_ft, dst1);
	printf("  strcpy        returned: %p dest: \"%s\"\n\n", (void*)ret_std, dst2);

	// Test 3 : chaîne vide
	// pré-remplir dst3 pour vérifier que le terminator est bien écrit
	strcpy(dst3, "XXXXX");
	ret_ft = _ft_strcopy(test3, dst3);
	ret_std = strcpy(dst4, test3);
	printf("Test 3: src (vide)\n");
	printf("  _ft_strcopy returned: %p dest: \"%s\"\n", (void*)ret_ft, dst3);
	printf("  strcpy        returned: %p dest: \"%s\"\n\n", (void*)ret_std, dst4);

	// Test 4 : chaîne plus longue
	ret_ft = _ft_strcopy(test4, dst1);
	ret_std = strcpy(dst2, test4);
	printf("Test 4: src \"%s\"\n", test4);
	printf("  _ft_strcopy returned: %p dest: \"%s\"\n", (void*)ret_ft, dst1);
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
	ret_write = _ft_write(1, msg1, strlen(msg1));
	printf("  retour: %zd\n\n", ret_write);

	// Test 2 : chaîne courte
	printf("Test 2: Chaîne courte\n");
	printf("  write:    ");
	fflush(stdout);
	ret_write_std = write(1, msg2, strlen(msg2));
	printf("  retour: %zd\n", ret_write_std);
	printf("  ft_write: ");
	fflush(stdout);
	ret_write = _ft_write(1, msg2, strlen(msg2));
	printf("  retour: %zd\n\n", ret_write);

	// Test 3 : chaîne vide
	printf("Test 3: Chaîne vide\n");
	ret_write_std = write(1, msg3, 0);
	printf("  write retour:    %zd\n", ret_write_std);
	ret_write = _ft_write(1, msg3, 0);
	printf("  ft_write retour: %zd\n\n", ret_write);

	// Test 4 : écriture sur stderr
	printf("Test 4: Écriture sur stderr\n");
	printf("  write:    ");
	fflush(stdout);
	ret_write_std = write(2, msg4, strlen(msg4));
	printf("  retour: %zd\n", ret_write_std);
	printf("  ft_write: ");
	fflush(stdout);
	ret_write = _ft_write(2, msg4, strlen(msg4));
	printf("  retour: %zd\n\n", ret_write);

	// Test 5 : test d'erreur (fd invalide)
	printf("Test 5: File descriptor invalide (-1)\n");
	ret_write_std = write(-1, msg1, strlen(msg1));
	printf("  write retour:    %zd\n", ret_write_std);
	ret_write = _ft_write(-1, msg1, strlen(msg1));
	printf("  ft_write retour: %zd\n\n", ret_write);

	return (0);
}
