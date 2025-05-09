#include  "../../includes/cub_3d.h"

static bool ft_can_move(char **map, int x, int y)
{
    return y >= 0 && map[y] && x >= 0 && x < (int)ft_strlen(map[y]) && map[y][x] == '1';
}


static int ft_rotate(int current, bool clockwise) 
{
    if (clockwise) {
        return (current + 1) % 4;
    } else {
        return (current + 3) % 4;
    }
}

static bool ft_find_first_wall(char **map, t_cursor *cursor)
{
    int y = 0;
    while (map[y])
    {
        int x = 0;
        while (map[y][x])
        {
            if (map[y][x] == '1')
            {
                cursor->x = x;
                cursor->y = y;
                cursor->dir = DIR_RIGHT;
                return true;
            }
            x++;
        }
        y++;
    }
    return false;
}

void ft_wall_algorithm(char **map)
{
    
    t_cursor start; 
    t_cursor curr;

    int dx[] = {1, 0, -1, 0};
    int dy[] = {0, 1, 0, -1};

    if(!ft_find_first_wall(map, &start))
        return;
    curr = start; 

    while(true)
    {
        ft_dprintf("DEBUG: visitando (%d, %d)\n", curr.y, curr.x); 
        int right_dir = ft_rotate(curr.dir, true);
        int rx = curr.x + dx[right_dir];
        int ry = curr.y + dy[right_dir];

        if (ft_can_move(map, rx, ry))
        {
            curr.x = rx;
            curr.y = ry;
            curr.dir = right_dir;
        }
        else {
            int fx = curr.x + dx[curr.dir];
            int fy = curr.y + dy[curr.dir];

            if (ft_can_move(map, fx, fy))
            {
                curr.x = fx;
                curr.y = fy;
            }
            else
                curr.dir = ft_rotate(curr.dir, false); 
        }
    }
    if (curr.x == start.x && curr.y == start.y && curr.dir == start.dir)
        break; 
}