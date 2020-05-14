
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

typedef struct		s_tree
{
	char			*line;
	struct s_tree	*next;
}					t_tree;

#define GRE_T		"\x1b[32m"
#define STD_T		"\x1b[0m"
#define RANDOM		(rand() * time(NULL)) % 1000

//Add empty linr to struct->line
char				*add_line(int count)
{
	char			*line;

	line = (char*)malloc(count +1);
	if (line)
	{
		line[--count] = '\0';
		while (count)
			line[--count] = ' ';
	}
	return (line);
}
//Add empty level to tree
t_tree				*add_lv(int count)
{
	t_tree			*new_lv;

	new_lv = (t_tree*)malloc(sizeof(t_tree));
	if (new_lv)
	{
		new_lv->line = add_line(count);
		if (new_lv->line == NULL)
		{
			free(new_lv);
			new_lv = NULL;
		}
		new_lv->next = NULL;
	}
	return (new_lv);
}
//Add new lavel to front of the list
void				push_front(t_tree **head, t_tree *new_lv)
{
	if ((*head) == NULL)
		*head = new_lv;
	else
	{
		new_lv->next = *head;
		*head = new_lv;
	}
}
//Clean tree
void				free_tree(t_tree **head)
{
	t_tree			*to_del;

	if (head && *head)
	{
		while (*head)
		{
			to_del = *head;
			free(to_del->line);
			head = &(to_del->next);
			free(to_del);
			to_del = NULL;
		}
		head = NULL;
	}
}
//Init empty map for tree
t_tree				*init_tree(int lv)
{
	t_tree			*head;
	t_tree			*new_lv;
	unsigned int	weith;

	lv = (lv > 0) ? lv : lv * -1;
	weith = lv * 2;
	head = NULL;
	while (lv--)
	{
		new_lv = add_lv(weith);
		if (new_lv)
			push_front(&head, new_lv);
		else
			free_tree(&head);
	}
	return (head);
}
//Print map
void				print_tree(t_tree *tree)
{
	t_tree			*temp;

	temp = tree;
	while (temp)
	{
		printf("%s%s%s\n",GRE_T, temp->line, STD_T);
		temp = temp->next;
	}
}
//Add branch to tree
void				add_branch(t_tree *find, t_tree *to_add)
{
	unsigned int	i;

	i = 0;
	while (find->line[i])
	{
		if (find->line[i] != ' ' && find->line[i] != '*')
		{
			if (RANDOM > 700)
				to_add->line[i - 1] = '\\';
			else if (RANDOM < 300)
				to_add->line[i + 1] = '/';
			else
				continue;
		}
		i++;
	}
}
//Add foliage to end in branches
void				add_foliage(t_tree *find, t_tree *to_add)
{
	unsigned int	i;

	i = 0;
	while (find->line[i])
	{
		if (find->line[i] != ' ' && to_add)
		{
			if (find->line[i] == '/' && to_add->line[i + 1] == ' ')
				to_add->line[i + 1] = '*';
			if (find->line[i] == '\\' && to_add->line[i - 1] == ' ')
				to_add->line[i - 1] = '*';
		}
		else
			find->line[i] = (find->line[i] != ' ') ? '*' : ' ';
		i++;
	}
}
//Add tree to map
void				add_tree(t_tree *tree, int lv)
{
	int				center;


	tree->line[--lv] = '|';
	center = lv / 2;
	while(tree->next)
	{
		add_branch(tree, tree->next);
		if (lv > center)
			add_branch(tree, tree->next);
		add_foliage(tree, tree->next);
		lv--;
		tree = tree->next;
	}
	add_foliage(tree, tree->next);
}
//Revers sort list
void				sort_d_rev(t_tree **head)
{
	t_tree			*temp_a;
	t_tree			*temp_b;
	t_tree			*temp_c;

	temp_a = NULL;
	temp_b = *head;
	while (temp_b)
	{
		temp_c = temp_b->next;
		temp_b->next = temp_a;
		temp_a = temp_b;
		temp_b = temp_c;
	}
	*head = temp_a;
}

int					main(int argc, char** argv)
{	
	int				lv;
	t_tree			*map;

	lv = 0;
	srand(time(NULL));
	if (argc != 2 || !strncmp(argv[1], "--help", 7))
	{
		printf("./three [num lavel]\n");
		return(0);
	}
	lv = atoi(argv[1]);
	if (lv <= 0)
	{
		printf("Bad namber of lavel\n");
		return(0);
	}
	map = init_tree(lv);
	add_tree(map, lv);
	sort_d_rev(&map);
	if (map)
		print_tree(map);
	free_tree(&map);
	return(0);
}