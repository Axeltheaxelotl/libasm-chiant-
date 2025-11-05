/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libasm.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alanty <alanty@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 00:00:00 by alanty            #+#    #+#             */
/*   Updated: 2025/11/05 17:30:50 by alanty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBASM_H
# define LIBASM_H

# include <stddef.h>
# include <sys/types.h>

/* ************************************************************************** */
/*                              STRUCTURES                                    */
/* ************************************************************************** */

typedef struct s_list
{
	void			*data;
	struct s_list	*next;
}	t_list;

/* ************************************************************************** */
/*                         MANDATORY FUNCTIONS                                */
/* ************************************************************************** */

/**
 * @brief Calcule la longueur d'une chaîne de caractères.
 * @param str La chaîne dont on veut calculer la longueur.
 * @return La longueur de la chaîne (nombre de caractères avant '\0').
 */
size_t		ft_strlen(const char *str);

/**
 * @brief Copie une chaîne de caractères.
 * @param src La chaîne source à copier.
 * @param dst Le buffer de destination.
 * @return Un pointeur vers la chaîne de destination.
 */
char		*ft_strcpy(const char *src, char *dst);

/**
 * @brief Compare deux chaînes de caractères.
 * @param s1 La première chaîne.
 * @param s2 La deuxième chaîne.
 * @return 0 si égales, <0 si s1 < s2, >0 si s1 > s2.
 */
int			ft_strcmp(const char *s1, const char *s2);

/**
 * @brief Écrit dans un descripteur de fichier.
 * @param fd Le descripteur de fichier.
 * @param buf Le buffer contenant les données à écrire.
 * @param count Le nombre d'octets à écrire.
 * @return Le nombre d'octets écrits, ou -1 en cas d'erreur.
 */
ssize_t		ft_write(int fd, const void *buf, size_t count);

/**
 * @brief Lit depuis un descripteur de fichier.
 * @param fd Le descripteur de fichier.
 * @param buf Le buffer où stocker les données lues.
 * @param count Le nombre d'octets à lire.
 * @return Le nombre d'octets lus, ou -1 en cas d'erreur.
 */
ssize_t		ft_read(int fd, void *buf, size_t count);

/**
 * @brief Duplique une chaîne de caractères en allouant de la mémoire.
 * @param s La chaîne à dupliquer.
 * @return Un pointeur vers la nouvelle chaîne, ou NULL si l'allocation échoue.
 */
char		*ft_strdup(const char *s);

/* ************************************************************************** */
/*                          BONUS FUNCTIONS                                   */
/* ************************************************************************** */

/**
 * @brief Convertit une chaîne en entier selon une base donnée.
 * @param str La chaîne à convertir.
 * @param base La base de conversion (ex: "0123456789" pour base 10).
 * @return L'entier résultant de la conversion.
 */
int			ft_atoi_base(const char *str, const char *base);

/**
 * @brief Ajoute un nouvel élément en tête de liste.
 * @param begin_list Pointeur vers le pointeur de tête de liste.
 * @param data Les données à stocker dans le nouvel élément.
 */
void		ft_list_push_front(t_list **begin_list, void *data);

/**
 * @brief Calcule la taille d'une liste chaînée.
 * @param begin_list Le premier élément de la liste.
 * @return Le nombre d'éléments dans la liste.
 */
int			ft_list_size(t_list *begin_list);

/**
 * @brief Supprime tous les éléments de la liste correspondant à data_ref.
 * @param begin_list Pointeur vers le pointeur de tête de liste.
 * @param data_ref La donnée de référence à comparer.
 * @param cmp Fonction de comparaison.
 * @param free_fct Fonction pour libérer les données.
 */
void		ft_list_remove_if(t_list **begin_list, void *data_ref,
				int (*cmp)(), void (*free_fct)(void *));

/**
 * @brief Trie une liste chaînée.
 * @param begin_list Pointeur vers le pointeur de tête de liste.
 * @param cmp Fonction de comparaison pour le tri.
 */
void		ft_list_sort(t_list **begin_list, int (*cmp)());

#endif
