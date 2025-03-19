#include "draw.h"
#include "ft_mlx.h"
#include "vector.h"
#include "minirt.h"
#include "light.h"

typedef struct s_hit
{
	t_object	*obj;
	double		t;
}	t_hit;

void	initializer(t_world *world)
{
	t_mlx	mlx;
	init(&mlx);
	world->mlx = mlx;

	t_ambient_lightning	ambient_lightning;
	ambient_lightning.ratio = 0.2;
	ambient_lightning.rgb.red = 222;
	ambient_lightning.rgb.green = 185;
	ambient_lightning.rgb.blue = 155;
	world->ambient_lightning = ambient_lightning;

	t_light	light;
	set(&light.coordinates_vec, 2, 4, 2.5);
	light.ratio = 0.6;
	light.rgb.red = 255;
	light.rgb.green = 255;
	light.rgb.blue = 255;
	world->light = light;

	t_camera	camera;
	set(&camera.coordinates_vec, 0, 0, -3);
	set(&camera.orientation_vec, 0, 0, 0);
	world->camera = camera;
}

double	calculate_t_intersection(t_camera camera, t_vector dir_vec, t_object obj)
{
	double	result = -1;
	if (ft_strncmp(obj.identifier, "pl", 3) == 0)
	{
		result = -(calculate_inner_product(subst_vector(camera.coordinates_vec, obj.coordinates_vec), obj.orientation_vec)
			/ calculate_inner_product(dir_vec, obj.orientation_vec));
	}
	else if (ft_strncmp(obj.identifier, "sp", 3) == 0)
	{
		// 球の交差判定 (解の公式を使う)
        t_vector oc = subst_vector(camera.coordinates_vec, obj.coordinates_vec);
        double a = calculate_inner_product(dir_vec, dir_vec);
        double b = 2.0 * calculate_inner_product(oc, dir_vec);
        double c = calculate_inner_product(oc, oc) - (obj.diameter / 2.0) * (obj.diameter / 2.0);
        double discriminant = b * b - 4 * a * c;

        if (discriminant < 0)
            return -1; // 交点なし

        double t1 = (-b - sqrt(discriminant)) / (2.0 * a);
        double t2 = (-b + sqrt(discriminant)) / (2.0 * a);

        if (t1 > 0)
            return t1; // 一番近い交点
        if (t2 > 0)
            return t2; // t1が負ならt2
        return -1; // どちらも負
	}
	return (result);
}

t_hit	find_closest_obj(t_world world, t_vector dir_vec)
{
	double closest_t = INFINITY;
	t_object *closest_obj = NULL;
	t_hit	hit;

	// 物体リストをループ
	t_list *current = world.objects;
	while (current)
	{
		t_object *obj = (t_object *)current->content;
		double t = calculate_t_intersection(world.camera, dir_vec, *obj);
		// tが正で、かつこれまでの最小値より小さければ更新
		if (t > 0 && t < closest_t)
		{
			closest_t = t;
			closest_obj = obj;
		}
		current = current->next;
	}
	hit.obj = closest_obj;
	hit.t = closest_t;
	return (hit);
}

void	put_color_on_intersection_pixel(int xs, int ys, t_world world, t_vector dir_vec)
{
	int			color_value;
	t_vector	intersection_point;
	t_hit	hit;

	hit = find_closest_obj(world, dir_vec);
	if (hit.obj != NULL)
	{
		intersection_point = add_vector(world.camera.coordinates_vec, multi_vector(dir_vec, hit.t));
		if (ft_strncmp(hit.obj->identifier, "sp", 3) == 0)
		{
			t_vector	n_tmp;
			n_tmp = subst_vector(intersection_point, hit.obj->coordinates_vec);
			t_vector n = multi_vector(n_tmp, 1 / sqrt(abst_squared(n_tmp)));
			hit.obj->orientation_vec = n;
		}
		color_value = calculate_color(world, hit.obj, dir_vec, intersection_point);
		my_pixel_put(xs, ys, world.mlx.img, color_value);
	}
	else
		my_pixel_put(xs, ys, world.mlx.img, BACKGROUND_COLOR);
}

// いったんカメラの位置ベクトル、方向ベクトル、FOV（視野角）を固定する（原点上のx,yにスクリーンを張る）
void render_scene(t_world world)
{
	// スクリーンの位置ベクトル
	t_vector	screen_vec;
	// カメラから2次元スクリーン上の任意の点(x,y)の方向ベクトル
	t_vector	dir_vec;
	// 2次元スクリーン上のxs,ys
	double xs, ys;
	// 3次元ワールド上のxw,yw
	double xw, yw;

	ys = 0;
	while (ys < HEIGHT - 1)
	{
		xs = 0;
		while (xs < WIDTH - 1)
		{
			// スクリーン上の点の3次元空間における位置ベクトルを計算
			yw = 1.0 - 2 * ys / HEIGHT;
			xw = 1.0 - 2 * xs / WIDTH;
			set(&screen_vec, xw, yw, 0);
			// ray = s + tdの d, sはカメラベクトル
			dir_vec = normalize_vector(subst_vector(screen_vec, world.camera.coordinates_vec));
			put_color_on_intersection_pixel(xs, ys, world, dir_vec);
			xs++;
		}
		ys++;
	}
}

int	main() {
	t_world	world;
	initializer(&world);

	world.objects = NULL;

	t_object	*plane = malloc((sizeof(t_object)));
	set(&plane->coordinates_vec, 0, -1, 0);
	set(&plane->orientation_vec, 0, 1, 0);
	plane->rgb.red = 0;
	plane->rgb.green = 246;
	plane->rgb.blue = 246;
	plane->identifier = "pl";
	ft_lstadd_back(&world.objects, ft_lstnew(plane));

	    /* 2. Sphere オブジェクトの作成 */
    t_object *sphere = malloc(sizeof(t_object));
    if (!sphere)
        return (1);
    sphere->identifier = "sp";
    set(&sphere->coordinates_vec, 0, 0, 3);
    set(&sphere->orientation_vec, 0, 0, 0); // 球体の場合、方向ベクトルは使用しない場合が多い
    sphere->diameter = 1.0;
    sphere->height = 0;
    sphere->rgb.red = 255;
    sphere->rgb.green = 0;
    sphere->rgb.blue = 0;
    ft_lstadd_back(&world.objects, ft_lstnew(sphere));

		    /* 3. Sphere オブジェクトの作成 */
    t_object *sphere2 = malloc(sizeof(t_object));
    if (!sphere2)
        return (1);
    sphere2->identifier = "sp";
    set(&sphere2->coordinates_vec, 1, 0, 2);
    set(&sphere2->orientation_vec, 0, 0, 0); // 球体の場合、方向ベクトルは使用しない場合が多い
    sphere2->diameter = 1.0;
    sphere2->height = 0;
    sphere2->rgb.red = 55;
    sphere2->rgb.green = 44;
    sphere2->rgb.blue = 231;
	ft_lstadd_back(&world.objects, ft_lstnew(sphere2));

    /* リンクリストに追加 */

	render_scene(world);

	mlx_put_image_to_window(world.mlx.ptr, world.mlx.win_ptr, world.mlx.img->ptr, 0, 0);
	mlx_loop(world.mlx.ptr);
}
