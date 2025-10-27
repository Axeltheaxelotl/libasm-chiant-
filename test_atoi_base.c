#include <stdio.h>

int ft_atoi_base(char *str, char *base);

int main(void)
{
    printf("=== Tests ft_atoi_base ===\n\n");
    
    // Tests base décimale
    printf("Base 10:\n");
    printf("  \"42\" base \"0123456789\" = %d (attendu: 42)\n", 
           ft_atoi_base("42", "0123456789"));
    printf("  \"-42\" base \"0123456789\" = %d (attendu: -42)\n", 
           ft_atoi_base("-42", "0123456789"));
    printf("  \"  +123\" base \"0123456789\" = %d (attendu: 123)\n", 
           ft_atoi_base("  +123", "0123456789"));
    
    // Tests base binaire
    printf("\nBase 2:\n");
    printf("  \"101\" base \"01\" = %d (attendu: 5)\n", 
           ft_atoi_base("101", "01"));
    printf("  \"1111\" base \"01\" = %d (attendu: 15)\n", 
           ft_atoi_base("1111", "01"));
    printf("  \"-1010\" base \"01\" = %d (attendu: -10)\n", 
           ft_atoi_base("-1010", "01"));
    
    // Tests base hexadécimale
    printf("\nBase 16:\n");
    printf("  \"2A\" base \"0123456789ABCDEF\" = %d (attendu: 42)\n", 
           ft_atoi_base("2A", "0123456789ABCDEF"));
    printf("  \"FF\" base \"0123456789ABCDEF\" = %d (attendu: 255)\n", 
           ft_atoi_base("FF", "0123456789ABCDEF"));
    printf("  \"-10\" base \"0123456789ABCDEF\" = %d (attendu: -16)\n", 
           ft_atoi_base("-10", "0123456789ABCDEF"));
    
    // Tests base personnalisée
    printf("\nBase custom \"poneyvif\":\n");
    printf("  \"poney\" base \"poneyvif\" = %d (attendu: 0*8^4 + 1*8^3 + 2*8^2 + 3*8 + 4 = 732)\n", 
           ft_atoi_base("poney", "poneyvif"));
    
    // Tests bases invalides
    printf("\nBases invalides (doivent retourner 0):\n");
    printf("  \"42\" base \"\" = %d (base vide)\n", 
           ft_atoi_base("42", ""));
    printf("  \"42\" base \"0\" = %d (base avec 1 seul char)\n", 
           ft_atoi_base("42", "0"));
    printf("  \"42\" base \"0123456789+\" = %d (base avec +)\n", 
           ft_atoi_base("42", "0123456789+"));
    printf("  \"42\" base \"0123456789-\" = %d (base avec -)\n", 
           ft_atoi_base("42", "0123456789-"));
    printf("  \"42\" base \"01234 56789\" = %d (base avec espace)\n", 
           ft_atoi_base("42", "01234 56789"));
    printf("  \"42\" base \"0123456709\" = %d (base avec doublons '0')\n", 
           ft_atoi_base("42", "0123456709"));
    
    // Tests avec caractères non dans la base
    printf("\nCaractères non dans la base:\n");
    printf("  \"12Z34\" base \"0123456789\" = %d (attendu: 12, s'arrête à Z)\n", 
           ft_atoi_base("12Z34", "0123456789"));
    
    // Tests signes multiples
    printf("\nSignes multiples:\n");
    printf("  \"--42\" base \"0123456789\" = %d (attendu: 42)\n", 
           ft_atoi_base("--42", "0123456789"));
    printf("  \"---42\" base \"0123456789\" = %d (attendu: -42)\n", 
           ft_atoi_base("---42", "0123456789"));
    printf("  \"+-42\" base \"0123456789\" = %d (attendu: -42)\n", 
           ft_atoi_base("+-42", "0123456789"));
    


           printf("\n Le test pour le putain de ft_atoi_base\n");
               printf("%d\n", ft_atoi_base("101", "01"));           // 5
    printf("%d\n", ft_atoi_base("  -2a", "0123456789abcdef")); // -42
    printf("%d\n", ft_atoi_base("123", "0123456789"));   // 123
    printf("%d\n", ft_atoi_base("zzz", "0123456789"));   // 0 (base invalide)
    return 0;

}
