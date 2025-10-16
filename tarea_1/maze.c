// Wilson's Algorithm (Loop-Erased Random Walk) for generating a maze
// Compile: cc maze.c -std=c99 -O2 -o maze

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define GRID_W 10
#define GRID_H 5

// Wall bits for each cell
enum {N = 1, E = 2, S = 4, W = 8};

typedef struct {
    unsigned walls;  // bitmask: N|E|S|W set means the wall is present
    bool in_maze;    // has this cell been carved into the maze?
} Cell;

typedef struct Node {
    int x, y;
    struct Node *prev, *next;
} Node;

Cell grid[GRID_H][GRID_W];
// Map cell -> pointer to node if it is currently in the random-walk path (for loop erasure)
Node *in_path[GRID_H][GRID_W];

// Markers
int seed_x, seed_y; // start cell
int end_x, end_y;   // farthest cell from start

// -------- Utilities --------
int rnd(int n) {
    return rand() % n;
}

bool inside(int x, int y) {
    return (x >= 0 && x < GRID_W && y >= 0 && y < GRID_H);
}

void remove_wall_between(int x1, int y1, int x2, int y2) {
    if (x2 == x1 && y2 == y1 - 1) {           // neighbor is north
        grid[y1][x1].walls &= ~N;
        grid[y2][x2].walls &= ~S;
    } else if (x2 == x1 + 1 && y2 == y1) {    // east
        grid[y1][x1].walls &= ~E;
        grid[y2][x2].walls &= ~W;
    } else if (x2 == x1 && y2 == y1 + 1) {    // south
        grid[y1][x1].walls &= ~S;
        grid[y2][x2].walls &= ~N;
    } else if (x2 == x1 - 1 && y2 == y1) {    // west
        grid[y1][x1].walls &= ~W;
        grid[y2][x2].walls &= ~E;
    }
}

// Pick a random in-bounds neighbor
void random_neighbor(int x, int y, int *nx, int *ny) {
    int dirs[4][2] = {{0,-1},{1,0},{0,1},{-1,0}};
    // shuffle directions
    for (int i = 0; i < 4; i++) {
        int j = rnd(4);
        int tx = dirs[i][0], ty = dirs[i][1];
        dirs[i][0] = dirs[j][0];
        dirs[i][1] = dirs[j][1];
        dirs[j][0] = tx;
        dirs[j][1] = ty;
    }
    for (int k = 0; k < 4; k++) {
        int xx = x + dirs[k][0];
        int yy = y + dirs[k][1];
        if (inside(xx, yy)) {
            *nx = xx; 
            *ny = yy; 
            return;
        }
    }
    *nx = x; *ny = y; // fallback (shouldn't happen)
}

bool any_unvisited(void) {
    for (int y = 0; y < GRID_H; y++)
        for (int x = 0; x < GRID_W; x++)
            if (!grid[y][x].in_maze)
                return true;
    return false;
}

void pick_random_unvisited(int *rx, int *ry) {
    int cx, cy;
    do { 
        cx = rnd(GRID_W); 
        cy = rnd(GRID_H);
    } while (grid[cy][cx].in_maze);
    *rx = cx;
    *ry = cy;
}

// -------- Linked-list helpers for the loop-erased walk --------
Node* append_node(Node **head, Node **tail, int x, int y) {

    /* El codigo de esta funcion debe ser completado por el estudiante */

}

void erase_loop_at(Node **tail, Node *first_repeat) {

    /* El codigo de esta funcion debe ser completado por el estudiante */
    
}

void free_path(Node *head) {
    Node *cur = head;
    while (cur) {
        in_path[cur->y][cur->x] = NULL;
        Node *tmp = cur->next;
        free(cur);
        cur = tmp;
    }
}

// -------- Wilson's algorithm --------
void wilson(void) {
    // Initialize grid
    for (int y = 0; y < GRID_H; y++)
        for (int x = 0; x < GRID_W; x++) {
            grid[y][x].walls   = N | E | S | W;
            grid[y][x].in_maze = false;
        }

    // Seed (start) cell
    seed_x = rnd(GRID_W);
    seed_y = rnd(GRID_H);
    grid[seed_y][seed_x].in_maze = true;

    while (any_unvisited()) {
        int x0, y0;
        pick_random_unvisited(&x0, &y0);

        // Clear per-walk path map
        for (int y = 0; y < GRID_H; y++)
            for (int x = 0; x < GRID_W; x++)
                in_path[y][x] = NULL;

        Node *head = NULL, *tail = NULL;

        // cx, cy: current position in the random walk, initialized to the start
        // position of the walk.
        int cx = x0, cy = y0;
        // Loop-erased random walk until we hit the maze
        // terminates when the random walk reacheas a visited cell
        while (!grid[cy][cx].in_maze) {
            if (in_path[cy][cx]) {
                // Loop: erase from first occurrence to tail
                erase_loop_at(&tail, in_path[cy][cx]);
            } else {
                Node *n = append_node(&head, &tail, cx, cy);
                in_path[cy][cx] = n;
            }
            int nx, ny;
            random_neighbor(cx, cy, &nx, &ny);
            cx = nx; cy = ny;
        }

        // Carve the loop-erased path into the maze
        if (head) {
            Node *p = head;
            while (p->next) {
                remove_wall_between(p->x, p->y, p->next->x, p->next->y);
                grid[p->y][p->x].in_maze = true;
                p = p->next;
            }
            // connect tail to the hit-in-maze cell (cx, cy)
            remove_wall_between(p->x, p->y, cx, cy);
            grid[p->y][p->x].in_maze = true;
        }

        // Ensure all nodes on the path are marked in_maze
        for (Node *p = head; p; p = p->next)
            grid[p->y][p->x].in_maze = true;

        // Cleanup current walk
        free_path(head);
    }
}

// -------- BFS to find farthest cell from (sx, sy) --------
void try_push(int x, int y, int nx, int ny,
              int wall_bit_here, int wall_bit_there,
              int dist[GRID_H][GRID_W], int *qx, int *qy, int *tail)
{
    if (!inside(nx, ny)) return;
    if (dist[ny][nx] != -1) return;
    // passage must be open in BOTH cells
    if ((grid[y][x].walls & wall_bit_here) != 0) return;
    if ((grid[ny][nx].walls & wall_bit_there) != 0) return;

    dist[ny][nx] = dist[y][x] + 1;
    qx[*tail] = nx;
    qy[*tail] = ny;
    (*tail)++;
}

void find_farthest_from(int sx, int sy) {
    int dist[GRID_H][GRID_W];
    for (int y = 0; y < GRID_H; y++)
        for (int x = 0; x < GRID_W; x++)
            dist[y][x] = -1;

    int qx[GRID_W * GRID_H], qy[GRID_W * GRID_H];
    int head = 0, tail = 0;

    dist[sy][sx] = 0;
    qx[tail] = sx; qy[tail] = sy; tail++;

    while (head < tail) {
        int x = qx[head], y = qy[head]; head++;

        // Explore neighbors through open passages
        try_push(x, y, x,   y-1, N,  S,  dist, qx, qy, &tail); // north
        try_push(x, y, x+1, y,   E,  W, dist, qx, qy, &tail); // east
        try_push(x, y, x,   y+1, S,  N,  dist, qx, qy, &tail); // south
        try_push(x, y, x-1, y,   W, E,  dist, qx, qy, &tail); // west
    }

    // Find farthest reached cell
    int maxd = 0;
    end_x = sx; end_y = sy;
    for (int y = 0; y < GRID_H; y++)
        for (int x = 0; x < GRID_W; x++)
            if (dist[y][x] > maxd) {
                maxd = dist[y][x];
                end_x = x;
                end_y = y;
            }
}

/*
-------- ASCII renderer --------
Since each cell has walls (walls are duplicated) it is enough it is enough to
iterate from left to ringht and top to bottom.
*/
void print_maze(void) {
    // Top border
    printf("+");
    for (int x = 0; x < GRID_W; x++)
        printf("--+");
    printf("\n");

    for (int y = 0; y < GRID_H; y++) {
        // Cell row with east walls
        printf("|");
        for (int x = 0; x < GRID_W; x++) {
            if (x == seed_x && y == seed_y) {
                printf("S");
            } else if (x == end_x && y == end_y) {
                printf("E");
            } else {
                printf(" ");
            }
            printf((grid[y][x].walls & E) ? " |" : "  ");
        }
        printf("\n");

        // Bottom walls
        printf("+");
        for (int x = 0; x < GRID_W; x++) {
            printf((grid[y][x].walls & S) ? "--" : "  ");
            printf("+");
        }
        printf("\n");
    }
}

int main(void) {
    srand((unsigned)time(NULL));
    wilson();
    find_farthest_from(seed_x, seed_y);
    print_maze();

    // Microbenchmarking
    bool mb = false;
    if (mb) {
        const int REPEATS = 10;    // run multiple times
        for (int r = 0; r < REPEATS; r++) {
            clock_t start = clock();      // start timer
            wilson();
            clock_t end = clock();        // stop timer
            double elapsed = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Run %d: took %.6f seconds\n", r+1, elapsed);
        }
    }
    return 0;
}
