ft_list_size:

[A] -> [B] -> [C] -> NULL;
- chaque noeud contient une valeur
- un lien vers le suivant
et quand next = NULL c la fin de la liste

CE QUE FAIT LE CODE EN RESUME:

int ft_list_size(t_list *begin)
{
    int count = 0;
    while(begin_list != NULL)
    {
        count++;
        begin_list = begin_list->next;
    }
    return count;
}

le code compte le nombre de noeuds, chaque tour de boucle ajoute 1 au compteur inc rax

CE QUE CA FAIT EXACTEMENT EN MEMOIRE

une liste de 3 elememts

node1-> node2-> node3-> NULL

Au debut:  
    - rdi = &node1
    - rax = 0

Etapes      rdi (le neoud actuel)       rax (compteur)      Action


Debut       &node1                      0                   test si rdi est NULL -> non


1           &node1                      1                   inc rax (on compte node 1)


->          &node2                      1                   mov rdi, [rdi + 8]
                                                            avance vers node 2

2           &node2                      2                   compte node2


->          &node3                      2                   avance vers node3


3           &node3                      3                   compte node3


->          NULL                        3                   avance vers NULL


Fin         NULL                        3                   sort de la boucle -> retourne 3




C QUOI LES PUTAIN DE OFFSET
chaque noeud ressemble en memoire a ca:

Adresses de node (rdi)
↓
+----------------+----------------+
|data (8 octets) | next (8 octets)|
+----------------+----------------+
offest 0          offest 8

[rdi + 0] -> data
[rdi + 8] -> next

donc offset = 8 signifie "vas  8 octets apres le debut du noeud pour acceder au next"