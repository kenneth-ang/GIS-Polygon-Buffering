#include "stdafx.h"
#include "stdlib.h"
#include "math.h"
#include "limits"
#include"geometry.h"

point_t *init_point(double x, double y)
{
	point_t *newpt;
	newpt = (point_t*)malloc(sizeof(*newpt));
	newpt->xcoord = x;
	newpt->ycoord = y;
	newpt->bisector = NULL;
	newpt->edgei = NULL;
	newpt->edgei_1 = NULL;
	return newpt;
}

line_t *create_line_seg(point_t * start, point_t * end)
{
	line_t *newline = (line_t*)malloc(sizeof(*newline));
	double x0 = start->xcoord, y0 = start->ycoord;
	double x1 = end->xcoord, y1 = end->ycoord;
	double g, c;
	if (x0 == x1)
	{
		g = INFINITY;
		c = NULL;
	}
	else if (y0 == y1)
	{
		g = 0.0;
		c = y1;
	}
	else
	{
		g = (y1 - y0) / (x1 - x0);
		c = y0 - g * x0;
	}
	newline->grad = g;
	newline->y_intercept = c;
	return newline;
}

line_t *init_line(double grad, double constant)
{
	line_t *newline = (line_t*)malloc(sizeof(*newline));
	newline->grad = grad;
	newline->y_intercept = constant;
	return newline;
}

double dist_points(point_t *p1, point_t *p2)
{
	double x1 = p1->xcoord, y1 = p1->ycoord;
	double x2 = p2->xcoord, y2 = p2->ycoord;
	return sqrt(pow((y2 - y1), 2) + pow((x2 - x1), 2));
}

double dist_to_line(point_t *point, point_t *lineSpt)
{
	line_t *line = lineSpt->edgei; 
	double x0 = point->xcoord, y0 = point->ycoord;
	double grad = line->grad, intercept = line->y_intercept;
	double dist;
	if (grad == INFINITY)
	{
		dist = abs(lineSpt->xcoord - x0);
	}
	else if (grad == 0)
	{
		dist = abs(lineSpt->ycoord - y0);
	}
	else
	{
		double a = grad, b = -1.0, c = intercept;
		dist = abs(a*x0 + b * y0 + c) / sqrt(pow(a, 2) + pow(b, 2));
	}
	return dist;
}

bool left_of_ray(point_t * point, point_t * start, point_t * end)
{
	double x0 = start->xcoord, y0 = start->ycoord;
	double theCos, theSin, dist;

	double x1 = end->xcoord - x0;
	double y1 = end->ycoord - y0;
	double xp = point->xcoord - x0;
	double yp = point->ycoord - y0;
	dist = sqrt(x1*x1 + y1 * y1);

	theCos = x1 / dist;
	theSin = y1 / dist;
	yp = yp * theCos - xp * theSin;

	return yp > 0.0;

}

bool opposite_sides(point_t * p1, point_t * p2, point_t *raystart, point_t *rayend)
{
	bool pt1left, pt2left;
	pt1left = left_of_ray(p1, raystart, rayend);
	pt2left = left_of_ray(p2, raystart, rayend);
	return !(pt1left == pt2left);
}

void assign_bisector(point_t * pprv, point_t * p, point_t * pnxt)
{
	line_t *bisector;
	double A1, A2;

	if (p->edgei_1->grad == INFINITY) A1 = PI / 2;
	else if (p->edgei_1->grad == -INFINITY) A1 = -PI / 2;
	else A1 = atan(p->edgei_1->grad);

	if (p->edgei->grad == INFINITY) A2 = PI / 2;
	else if (p->edgei->grad == -INFINITY) A2 = -PI / 2;
	else A2 = atan(p->edgei->grad);

	double B1 = (A1 + A2) / 2;
	double B2 = (A1 + A2 + PI) / 2;
	double grad3 = tan(B1), c3 = p->ycoord - p->xcoord*grad3;
	double grad4 = tan(B2), c4 = p->ycoord - p->xcoord*grad4;
	double xtest; 
	if (p->xcoord == 0)
	{
		xtest = (p->xcoord+1) * 2;
	}
	else
	{
		xtest = (p->xcoord) * 2;
	}

	point_t *testpt3 = init_point(xtest, grad3*xtest + c3);

	if (opposite_sides(pprv, pnxt, p, testpt3))
	{
		
		p->bisector = init_line(grad3, c3);
	}
	else
	{
		
		p->bisector = init_line(grad4, c4);
	}
}

point_t *intersection_point(line_t *L1, double x1, line_t *L2, double x2)
{
	double x, y; 
	double grad1 = L1->grad, c1 = L1->y_intercept; 
	double grad2 = L2->grad, c2 = L2->y_intercept; 

	if (grad1 == INFINITY || grad1 == -INFINITY) {
		x = x1;
		y = grad2 * x + c2;
	}
	else if (grad2 == INFINITY || grad2 == -INFINITY) {
		x = x2;
		y = grad1 * x + c1;
	}
	else {
		x = (c1 - c2) / (grad2 - grad1);
		y = grad1 * x + c1;
	}
	
	return init_point(x, y);

}

point_t *edge_intersection(point_t *p1, point_t *p2)
{
	point_t *interpt = intersection_point(p1->bisector,p1->xcoord,p2->bisector,p2->xcoord);
	interpt->edgei_1 = p1->edgei_1;
	interpt->edgei = p2->edgei;
	return interpt;
}

point_t *tri_incentre(point_t *p0, point_t *p1, point_t *p2)
{
	p1->edgei_1 = create_line_seg(p0, p1);
	p1->edgei = create_line_seg(p1, p2);
	p0->edgei_1 = create_line_seg(p2, p0);
	p0->edgei = create_line_seg(p0, p1);
	p2->edgei_1 = create_line_seg(p1, p2);
	p2->edgei = create_line_seg(p2, p0);
	assign_bisector(p0, p1, p2);
	assign_bisector(p1, p2, p0);
	assign_bisector(p2, p0, p1);
	return intersection_point(p1->bisector,p1->xcoord,p2->bisector,p2->xcoord);

}

point_t *split_intersection(point_t *prv, point_t *concavept, point_t *nxt, point_t *edgept)
{
	point_t *inters = NULL; 
	line_t *prvE = concavept->edgei_1, *nxtE = concavept->edgei;
	line_t *edge = edgept->edgei; 

	if (prvE->grad == edge->grad || nxtE->grad == edge->grad)
	{
		return inters;
	}

	point_t *p1 = intersection_point(prvE,concavept->xcoord, edge, edgept->xcoord);
	point_t *p2 = intersection_point(nxtE, concavept->xcoord, edge, edgept->xcoord);

	if (left_of_ray(p1, nxt, concavept) == true || left_of_ray(p2, prv, concavept) == false) return inters;

	point_t *p0 = init_point(concavept->xcoord,concavept->ycoord);
	//NEED TO CHECK IF inters is between the bisectors!! (in calling function)

	return tri_incentre(p1, p2, p0);
}
