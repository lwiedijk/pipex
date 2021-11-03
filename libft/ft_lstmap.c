/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstmap.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: lwiedijk <marvin@codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/28 11:50:34 by lwiedijk      #+#    #+#                 */
/*   Updated: 2020/12/03 17:42:28 by lwiedijk      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*new_lst;
	t_list	*new_node;

	if (!lst || !*f)
		return (NULL);
	new_lst = 0;
	while (lst)
	{
		new_node = ft_lstnew(f(lst->content));
		if (new_node == 0)
			ft_lstclear(&new_lst, del);
		ft_lstadd_back(&new_lst, new_node);
		lst = lst->next;
	}
	return (new_lst);
}
