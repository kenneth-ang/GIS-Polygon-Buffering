#ifndef __GEOMETRY__
#define __GEOMETRY__

#define PI 3.14159265

struct line_s
{
	double grad;
	double y_intercept;
};

struct point_s
{
	double xcoord, ycoord;
	struct line_s *bisector;
	struct line_s *edgei_1, *edgei;
};

typedef struct line_s line_t;
typedef struct point_s point_t;

/*
Initializes a point using geometric x and y coordinates
This function does not initialize the edges or angular bisector of the point
*/
point_t *init_point(double x, double y);

/*
Initializes a line segment based on two geometric points
*/
line_t *create_line_seg(point_t *start, point_t *end);
/*
Initializes a line based on a given gradient and constant value
*/
line_t *init_line(double grad, double constant);

/*
Calculates the distance between two points
*/
double dist_points(point_t *p1, point_t *p2);
/*
Calculates the perpendicular distance of a point to a line
*/
double dist_to_line(point_t *point, point_t *lineSpt);

/*
Checks if p1 and p2 are on opposite sides of the line segment created by raystart and rayend points
*/
bool opposite_sides(point_t * p1, point_t * p2, point_t *raystart, point_t *rayend);
/*
Check if a point is on the left of a line segment
*/
bool left_of_ray(point_t *point, point_t *start, point_t *end);

/*
Assigns an angular bisector line to point p
*/
void assign_bisector(point_t *pprv, point_t *p, point_t *pnxt);

/*
Calculates the intersection point between two lines
x1 is the x coordinate of a point on L1 and x2 is the x coordinate of a point on L2
Note: x1 or x2 will be used when either gradients is INFINITY
*/
point_t *intersection_point(line_t *L1, double x1, line_t *L2, double x2);

/*
Calculates the intersection point of the bisectors of two given points
Note: The bisector lines of both input points must already be asigned
*/
point_t *edge_intersection(point_t *p1, point_t *p2);

/*
Calculates the in centre point of the triangle created by the three input points
*/
point_t *tri_incentre(point_t *p0, point_t *p1, point_t *p2);

/*
Calculates the split point of a reflex vertex (concavept) and the edgei of the edgept
*/
point_t *split_intersection(point_t *prv, point_t *concavept, point_t *nxt, point_t *edgept);

#endif