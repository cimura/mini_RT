#include <stdio.h>

#define	WIDTH	512
#define	HEIGHT	512

typedef	struct s_coordinate
{
	int	x;
	int	y;
	int	z;
}	t_coordinate;

void	set_coordinate(t_coordinate *pos, int x, int y, int z)
{
	pos->x = x;
	pos->y = y;
	pos->z = z;
}

void	print_coordinate(t_coordinate pos)
{
	printf("x is %d\n", pos.x);
	printf("y is %d\n", pos.y);
	printf("z is %d\n", pos.z);
}

int	main() {
	t_coordinate	p_e;
	set_coordinate(&p_e, 0, 0, -5);
	
	print_coordinate(pos);
}
