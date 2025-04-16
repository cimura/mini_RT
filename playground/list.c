#include <stdlib.h>
#include <stdio.h>
#include <string.h>

typedef struct s_list
{
	void			*content;
	struct s_list	*next;
}	t_list;

typedef struct s_object
{
	char		*identifier;
	double		diameter;
	double		height;
}	t_object;

typedef struct s_world
{
	t_list	*objects;
}	t_world;

// ノードをリストに追加する関数
void list_add_front(t_list **list, void *content)
{
	t_list *new_node = malloc(sizeof(t_list));
	if (!new_node)
		return;
	new_node->content = content;
	new_node->next = *list;
	*list = new_node;
}

// メモリを解放する関数
void free_list(t_list *list)
{
	t_list *tmp;
	while (list)
	{
		tmp = list->next;
		free(((t_object *)list->content)->identifier);
		free(list->content);
		free(list);
		list = tmp;
	}
}

int main()
{
	t_world world = {NULL};

	// 球体オブジェクトの作成
	t_object *sphere = malloc(sizeof(t_object));
	sphere->identifier = strdup("Sphere1");
	sphere->diameter = 10.0;
	sphere->height = 0.0;  // 球体なので高さなし

	// 円柱オブジェクトの作成
	t_object *cylinder = malloc(sizeof(t_object));
	cylinder->identifier = strdup("Cylinder1");
	cylinder->diameter = 5.0;
	cylinder->height = 20.0;

	// リストに追加
	list_add_front(&world.objects, sphere);
	list_add_front(&world.objects, cylinder);

	// 確認
	t_list *current = world.objects;
	while (current)
	{
		t_object *obj = (t_object *)current->content;
		printf("Object: %s, Diameter: %.2f, Height: %.2f\n",
			   obj->identifier, obj->diameter, obj->height);
		current = current->next;
	}
	// メモリ解放
	free_list(world.objects);

	return 0;
}
