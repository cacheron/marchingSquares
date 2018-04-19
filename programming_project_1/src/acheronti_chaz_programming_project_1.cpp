/*	Chaz Acheronti
 *	Programming Assignment 1
 *	2.11.18
 */
#include <math.h>
#include <time.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <iostream>
#include <random>

#define X_RESOLUTION 800 
#define Y_RESOLUTION 600 
#define M_PI 3.14159265359
#define UNDEFINED -1
#define NORTH 0
#define NORTHEAST 1
#define EAST 2
#define SOUTHEAST 3
#define SOUTH 4
#define SOUTHWEST 5
#define WEST 6
#define NORTHWEST 7
#define TRUE 1
#define FALSE 0

// Size of the marching squares, change this for higher definition
// I have it on 5 using VS Release mode compilation, hopefully usign CMAKE it should have the same efficiency
#define SQUARE_SIZE 5
bool filled = false, grid_enabled = true, meta_balls_enabled = true;


typedef struct ball_color
{
	int r;
	int g;
	int b;
} ball_color;


typedef struct vec3
{
	int x;
	int y;
	int z;
	int direction;
} vec3;


typedef struct ball_type
{
	vec3 position;
	int radius;
	ball_color color;
} ball_type;



ball_type ball1;
ball_type ball2;
ball_type ball3;
ball_type ball4;
ball_type ball5;
ball_type ball6;
ball_type ball7;
ball_type ball8;

int ball_hit_wall(ball_type);
int select_ball_direction(ball_type);
void move_ball(ball_type&);
void display(void);
void reshape(int, int);
void keyboard(unsigned char, int, int);

int ball_hit_wall(ball_type ball)
{
	int ball_hit_wall;

	ball_hit_wall = FALSE;
	switch (ball.position.direction)
	{
	case NORTH:
		if ((ball.position.y - ball.radius) <= 0)
		{
			ball_hit_wall = TRUE;
		}
		break;
	case NORTHEAST:
		if (((ball.position.y - ball.radius) <= 0) || ((ball.position.x + ball.radius) >= X_RESOLUTION))
		{
			ball_hit_wall = TRUE;
		}
		break;
	case EAST:
		if ((ball.position.x + ball.radius) >= X_RESOLUTION)
		{
			ball_hit_wall = TRUE;
		}
		break;
	case SOUTHEAST:
		if (((ball.position.y + ball.radius) >= Y_RESOLUTION) || ((ball.position.x + ball.radius) >= X_RESOLUTION))
		{
			ball_hit_wall = TRUE;
		}
		break;
	case SOUTH:
		if ((ball.position.y + ball.radius) >= Y_RESOLUTION)
		{
			ball_hit_wall = TRUE;
		}
		break;
	case SOUTHWEST:
		if (((ball.position.y + ball.radius) >= Y_RESOLUTION) || ((ball.position.x - ball.radius) <= 0))
		{
			ball_hit_wall = TRUE;
		}
		break;
	case WEST:
		if ((ball.position.x - ball.radius) <= 0)
		{
			ball_hit_wall = TRUE;
		}
		break;
	case NORTHWEST:
		if (((ball.position.y - ball.radius) <= 0) || ((ball.position.x - ball.radius) <= 0))
		{
			ball_hit_wall = TRUE;
		}
		break;
	default:
		break;
	}
	return ball_hit_wall;
}


int select_ball_direction(ball_type ball)
{
	int new_ball_direction, random_direction;
	float new_move_north, new_move_northeast, new_move_east, new_move_southeast, new_move_south, new_move_southwest, new_move_west, new_move_northwest;
	float random_number, lower_bound, upper_bound;

	switch (ball.position.direction)
	{
	case NORTH:
		if (((ball.position.x - ball.radius) <= 0) && ((ball.position.y - ball.radius) <= 0))
		{
			new_ball_direction = SOUTHEAST;
		}
		else
		{
			if (((ball.position.x + ball.radius) >= X_RESOLUTION) && ((ball.position.y - ball.radius) <= 0))
			{
				new_ball_direction = SOUTHWEST;
			}
			else
			{
				random_number = (float)rand() / (float)RAND_MAX * 2.0f;
				random_direction = (int)random_number;
				switch (random_direction)
				{
				case 0:
					new_ball_direction = SOUTHEAST;
					break;
				case 1:
					new_ball_direction = SOUTHWEST;
					break;
				default:
					new_ball_direction = SOUTHEAST;
					break;
				}
			}
		}
		break;
	case NORTHEAST:
		if ((ball.position.x + ball.radius) >= X_RESOLUTION)
		{
			if ((ball.position.y - ball.radius) <= 0)
			{
				new_ball_direction = SOUTHWEST;
			}
			else
			{
				random_number = (float)rand() / (float)RAND_MAX * 2.0f;
				random_direction = (int)random_number;
				switch (random_direction)
				{
				case 0:
					new_ball_direction = NORTHWEST;
					break;
				case 1:
					new_ball_direction = WEST;
					break;
				default:
					new_ball_direction = NORTHWEST;
					break;
				}
			}
		}
		else
		{
			random_number = (float)rand() / (float)RAND_MAX * 2.0f;
			random_direction = (int)random_number;
			switch (random_direction)
			{
			case 0:
				new_ball_direction = SOUTHEAST;
				break;
			case 1:
				new_ball_direction = EAST;
				break;
			default:
				new_ball_direction = SOUTHEAST;
				break;
			}
		}
		break;
	case EAST:
		if ((ball.position.y - ball.radius) <= 0)
		{
			new_ball_direction = SOUTHWEST;
		}
		else
		{
			if ((ball.position.y + ball.radius) >= Y_RESOLUTION)
			{
				new_ball_direction = NORTHWEST;
			}
			else
			{
				random_number = (float)rand() / (float)RAND_MAX * 2.0f;
				random_direction = (int)random_number;
				switch (random_direction)
				{
				case 0:
					new_ball_direction = NORTHWEST;
					break;
				case 1:
					new_ball_direction = SOUTHWEST;
					break;
				default:
					new_ball_direction = NORTHWEST;
					break;
				}
			}
		}
		break;
	case SOUTHEAST:
		if ((ball.position.y + ball.radius) >= Y_RESOLUTION)
		{
			if ((ball.position.x + ball.radius) >= X_RESOLUTION)
			{
				new_ball_direction = NORTHWEST;
			}
			else
			{
				random_number = (float)rand() / (float)RAND_MAX * 2.0f;
				random_direction = (int)random_number;
				switch (random_direction)
				{
				case 0:
					new_ball_direction = NORTH;
					break;
				case 1:
					new_ball_direction = NORTHEAST;
					break;
				case 2:
					new_ball_direction = EAST;
					break;
				default:
					new_ball_direction = NORTH;
					break;
				}
			}
		}
		else
		{
			random_number = (float)rand() / (float)RAND_MAX * 2.0f;
			random_direction = (int)random_number;
			switch (random_direction)
			{
			case 0:
				new_ball_direction = SOUTH;
				break;
			case 1:
				new_ball_direction = SOUTHWEST;
				break;
			case 2:
				new_ball_direction = WEST;
				break;
			default:
				new_ball_direction = SOUTH;
				break;
			}
		}
		break;
	case SOUTH:
		if ((ball.position.x + ball.radius) >= X_RESOLUTION)
		{
			new_ball_direction = NORTHWEST;
		}
		else
		{
			new_ball_direction = NORTHEAST;
		}
		break;
	case SOUTHWEST:
		if ((ball.position.x - ball.radius) <= 0)
		{
			if ((ball.position.y + ball.radius) >= Y_RESOLUTION)
			{
				new_ball_direction = NORTHEAST;
			}
			else
			{
				new_ball_direction = SOUTHEAST;
			}
		}
		else
		{
			random_number = (float)rand() / (float)RAND_MAX * 2.0f;
			random_direction = (int)random_number;
			switch (random_direction)
			{
			case 0:
				new_ball_direction = NORTH;
				break;
			case 1:
				new_ball_direction = NORTHWEST;
				break;
			case 2:
				new_ball_direction = WEST;
				break;
			default:
				new_ball_direction = NORTH;
				break;
			}
		}
		break;
	case WEST:
		if ((ball.position.y - ball.radius) <= 0)
		{
			new_ball_direction = SOUTHEAST;
		}
		else
		{
			if ((ball.position.y + ball.radius) >= Y_RESOLUTION)
			{
				new_ball_direction = NORTHEAST;
			}
			else
			{
				random_number = (float)rand() / (float)RAND_MAX * 2.0f;
				random_direction = (int)random_number;
				switch (random_direction)
				{
				case 0:
					new_ball_direction = NORTHEAST;
					break;
				case 1:
					new_ball_direction = SOUTHEAST;
					break;
				default:
					new_ball_direction = NORTHEAST;
					break;
				}
			}
		}
		break;
	case NORTHWEST:
		if ((ball.position.x - ball.radius) <= 0)
		{
			if ((ball.position.y - ball.radius) <= 0)
			{
				new_ball_direction = SOUTHEAST;
			}
			else
			{
				random_number = (float)rand() / (float)RAND_MAX * 2.0f;
				random_direction = (int)random_number;
				switch (random_direction)
				{
				case 0:
					new_ball_direction = NORTHEAST;
					break;
				case 1:
					new_ball_direction = EAST;
					break;
				default:
					new_ball_direction = NORTHEAST;
					break;
				}
			}
		}
		else
		{
			if ((ball.position.y - ball.radius) <= 0)
			{
				random_number = (float)rand() / (float)RAND_MAX * 2.0f;
				random_direction = (int)random_number;
				switch (random_direction)
				{
				case 0:
					new_ball_direction = SOUTHWEST;
					break;
				case 1:
					new_ball_direction = SOUTH;
					break;
				case 2:
					new_ball_direction = WEST;
					break;
				default:
					new_ball_direction = SOUTHWEST;
					break;
				}
			}
		}
		break;
	default:
		break;
	}
	ball.position.direction = new_ball_direction;
	return ball.position.direction;
}


void move_ball(ball_type& ball)
{
	switch (ball.position.direction)
	{
	case NORTH:
		ball.position.y--;
		break;
	case NORTHEAST:
		ball.position.x++;
		ball.position.y--;
		break;
	case EAST:
		ball.position.x++;
		break;
	case SOUTHEAST:
		ball.position.x++;
		ball.position.y++;
		break;
	case SOUTH:
		ball.position.y++;
		break;
	case SOUTHWEST:
		ball.position.x--;
		ball.position.y++;
		break;
	case WEST:
		ball.position.x--;
		break;
	case NORTHWEST:
		ball.position.x--;
		ball.position.y--;
		break;
	default:
		break;
	}
}


void draw_ball(ball_type ball)
{
	float theta, circle_iterations = 24.0;

	glColor3ub(ball.color.r, ball.color.g, ball.color.b);
	glPolygonMode(GL_FRONT, GL_FILL);
	glBegin(GL_LINE_LOOP);
	glVertex3f(ball.position.x + ball.radius, ball.position.y, 0.0f);
	for (theta = 0; theta < 2 * M_PI; theta += M_PI / circle_iterations)
	{
		glVertex3f(ball.position.x + cos(theta) * ball.radius, ball.position.y + sin(theta) * ball.radius, 0.0f);
	}
	glEnd();
}

unsigned int squares_x = X_RESOLUTION / SQUARE_SIZE;
unsigned int squares_y = Y_RESOLUTION / SQUARE_SIZE;

// struct that holds data of 4 collision points and state
struct vec2 {
	int x, y;
};

struct point {
	vec2 pos;
	double sum;
};

struct square {
	point p1, p2, p3, p4;
	int state = 0;
};

void reset_state(square& square) {
	square.p1.sum = 0.0;
	square.p2.sum = 0.0;
	square.p3.sum = 0.0;
	square.p4.sum = 0.0;
	square.state = 0;
}

std::vector<std::vector<square>> squares;

void init_squares() {
	squares.resize(squares_y);
	for (int i = 0; i < squares.size(); i++) {
		squares[i].resize(squares_x);
		for (int j = 0; j < squares[i].size(); j++) {
			squares[i][j].state = 0;
			// init 4 corners of the square
			squares[i][j].p1 = { j * SQUARE_SIZE, i * SQUARE_SIZE, 0.0 };
			squares[i][j].p2 = { j * SQUARE_SIZE + SQUARE_SIZE, i * SQUARE_SIZE, 0.0 };
			squares[i][j].p3 = { j * SQUARE_SIZE + SQUARE_SIZE, i * SQUARE_SIZE + SQUARE_SIZE, 0.0 };
			squares[i][j].p4 = { j * SQUARE_SIZE, i * SQUARE_SIZE + SQUARE_SIZE, 0.0 };
		}
	}
}

double distance(int x, int y, int x2, int y2) {
	int sum = pow((x2 - x), 2) + pow((y2 - y), 2);
	return sqrt(sum);
}

void update_point(point& p, ball_type& meta_ball) {
	// calculate distances for p1
	int dist_sum = pow((meta_ball.position.x - p.pos.x), 2) + pow((meta_ball.position.y - p.pos.y), 2);
	p.sum += pow(meta_ball.radius, 2) / dist_sum;
}

// update the states of corners for one square and one ball
void calculate_state(square& square, ball_type& meta_ball) {
	update_point(square.p1, meta_ball);
	update_point(square.p2, meta_ball);
	update_point(square.p3, meta_ball);
	update_point(square.p4, meta_ball);
	// update state
	square.state = 0;
	if (square.p1.sum >= 1.0f) square.state += 1;
	if (square.p2.sum >= 1.0f) square.state += 2;
	if (square.p3.sum >= 1.0f) square.state += 4;
	if (square.p4.sum >= 1.0f) square.state += 8;
}

void calculate_states(ball_type& meta_ball) {
	// optimize the number of squares that we check
	int x_pos = meta_ball.position.x / SQUARE_SIZE;
	int y_pos = meta_ball.position.y / SQUARE_SIZE;

	int start_x = x_pos - 1.2 * meta_ball.radius;
	int start_y = y_pos - 1.2 * meta_ball.radius;

	if (start_x < 0) start_x = 0;
	if (start_y < 0) start_y = 0;

	int end_x = x_pos + 1.2 * meta_ball.radius;
	int end_y = y_pos + 1.2 * meta_ball.radius;

	if (end_x >= squares_x) end_x = squares_x - 1;
	if (end_y >= squares_y) end_y = squares_y - 1;

	for (size_t i = start_y; i < end_y; i++) {
		for (size_t j = start_x; j < end_x; j++) {
			calculate_state(squares[i][j], meta_ball);
		}
	}
}

// update only the squares that are near each meta_ball
void update_squares() {
	// reset the sums
	for (size_t i = 0; i < squares.size(); i++) {
		for (size_t j = 0; j < squares[i].size(); j++) {
			reset_state(squares[i][j]);
		}
	}
	// update sums
	calculate_states(ball1);
	calculate_states(ball2);
	calculate_states(ball3);
	calculate_states(ball4);
	calculate_states(ball5);
	calculate_states(ball6);
	calculate_states(ball7);
	calculate_states(ball8);
}

void draw_polygon(std::vector<vec2> vertices) {
	glColor3f(0.0f, 0.0f, 0.7f); // blue
	glPolygonMode(GL_FRONT, GL_FILL);
	
	if (!filled) glBegin(GL_LINE_LOOP);
	else glBegin(GL_POLYGON);

	for (size_t i = 0; i < vertices.size(); i++) {
		glVertex3f(vertices[i].x, vertices[i].y, 0.0f);
	}
	glEnd();
}

void draw_square(square& square) {
	std::vector<vec2> draw_points;
	vec2 p1_p2_mid = { (square.p1.pos.x + square.p2.pos.x) / 2.0, square.p1.pos.y};
	vec2 p1_p4_mid = { square.p1.pos.x, (square.p1.pos.y + square.p4.pos.y) / 2.0};
	vec2 p2_p3_mid = { square.p2.pos.x, (square.p2.pos.y + square.p3.pos.y) / 2.0 };
	vec2 p3_p4_mid = { (square.p3.pos.x + square.p4.pos.x) / 2.0, square.p3.pos.y };

	switch (square.state) {
	case(0):
		break;
	case(15):
		draw_points.push_back(square.p1.pos);
		draw_points.push_back(square.p2.pos);
		draw_points.push_back(square.p3.pos);
		draw_points.push_back(square.p4.pos);
		break;
	case(1):
		draw_points.push_back(p1_p4_mid);
		draw_points.push_back(square.p1.pos);
		draw_points.push_back(p1_p2_mid);
		break;
	case(2):
		draw_points.push_back(p1_p2_mid);
		draw_points.push_back(square.p2.pos);
		draw_points.push_back(p2_p3_mid);
		break;
	case(3):
		draw_points.push_back(p1_p4_mid);
		draw_points.push_back(square.p1.pos);
		draw_points.push_back(square.p2.pos);
		draw_points.push_back(p2_p3_mid);
		break;
	case(4):
		draw_points.push_back(p2_p3_mid);
		draw_points.push_back(square.p3.pos);
		draw_points.push_back(p3_p4_mid);
		break;
	case(5):
		draw_points.push_back(p1_p4_mid);
		draw_points.push_back(square.p1.pos);
		draw_points.push_back(p1_p2_mid);
		draw_points.push_back(p2_p3_mid);
		draw_points.push_back(square.p3.pos);
		draw_points.push_back(p3_p4_mid);
		break;
	case(6):
		draw_points.push_back(p1_p2_mid);
		draw_points.push_back(square.p2.pos);
		draw_points.push_back(square.p3.pos);
		draw_points.push_back(p3_p4_mid);
		break;
	case(7):
		draw_points.push_back(square.p1.pos);
		draw_points.push_back(square.p2.pos);
		draw_points.push_back(square.p3.pos);
		draw_points.push_back(p3_p4_mid);
		draw_points.push_back(p1_p4_mid);
		break;
	case(8):
		draw_points.push_back(p1_p4_mid);
		draw_points.push_back(square.p4.pos);
		draw_points.push_back(p3_p4_mid);
		break;
	case(9):
		draw_points.push_back(p3_p4_mid);
		draw_points.push_back(square.p4.pos);
		draw_points.push_back(p1_p4_mid);
		draw_points.push_back(square.p1.pos);
		draw_points.push_back(p1_p2_mid);
		break;
	case(10):
		draw_points.push_back(p3_p4_mid);
		draw_points.push_back(square.p4.pos);
		draw_points.push_back(p1_p4_mid);

		draw_points.push_back(p1_p2_mid);
		draw_points.push_back(square.p2.pos);
		draw_points.push_back(p2_p3_mid);
		break;
	case(11):
		draw_points.push_back(square.p4.pos);
		draw_points.push_back(square.p1.pos);
		draw_points.push_back(square.p2.pos);
		draw_points.push_back(p2_p3_mid);
		draw_points.push_back(p3_p4_mid);
		break;
	case(12):
		draw_points.push_back(p1_p4_mid);
		draw_points.push_back(p2_p3_mid);
		draw_points.push_back(square.p3.pos);
		draw_points.push_back(square.p4.pos);
		break;
	case(13):
		draw_points.push_back(square.p1.pos);
		draw_points.push_back(p1_p2_mid);
		draw_points.push_back(p2_p3_mid);
		draw_points.push_back(square.p3.pos);
		draw_points.push_back(square.p4.pos);
		break;
	case(14):
		draw_points.push_back(square.p4.pos);
		draw_points.push_back(square.p3.pos);
		draw_points.push_back(square.p2.pos);
		draw_points.push_back(p1_p2_mid);
		draw_points.push_back(p1_p4_mid);
		break;
	default:
		std::cout << "Reached unknown state! Summation error.\n";
		break;
	}
	// only draw if there are points to draw
	if (draw_points.size() > 0) {
		draw_polygon(draw_points);
	}
}

void draw_squares() {
	for (size_t i = 0; i < squares.size(); i++) {
		for (size_t j = 0; j < squares[i].size(); j++) {
			draw_square(squares[i][j]);
		}
	}
}

void draw_grid() {
	if (!grid_enabled) return;
	// vertical
	for (int i = 0; i < squares_x; i++) {
		glColor3f(0.05f, 0.05f, 0.05f);
		glBegin(GL_LINES);
		glVertex2f(i * SQUARE_SIZE, 0.0f);
		glVertex2f(i * SQUARE_SIZE, Y_RESOLUTION);
		glEnd();
	}

	// horizontal
	for (int i = 0; i < squares_y; i++) {
		glColor3f(0.05f, 0.05f, 0.05f);
		glBegin(GL_LINES);
		glVertex2f(0.0f, i * SQUARE_SIZE);
		glVertex2f(X_RESOLUTION, i * SQUARE_SIZE);
		glEnd();
	}
}

void display(void)
{
	// **********
	// * Ball 1 *
	// **********
	if (ball_hit_wall(ball1))
	{
		ball1.position.direction = select_ball_direction(ball1);
	}
	move_ball(ball1);

	// **********
	// * Ball 2 *
	// **********
	if (ball_hit_wall(ball2))
	{
		ball2.position.direction = select_ball_direction(ball2);
	}
	move_ball(ball2);
	// **********
	// * Ball 3 *
	// **********
	if (ball_hit_wall(ball3))
	{
		ball3.position.direction = select_ball_direction(ball3);
	}
	move_ball(ball3);
	// **********
	// * Ball 4 *
	// **********
	if (ball_hit_wall(ball4))
	{
		ball4.position.direction = select_ball_direction(ball4);
	}
	move_ball(ball4);
	// **********
	// * Ball 5 *
	// **********
	if (ball_hit_wall(ball5))
	{
		ball5.position.direction = select_ball_direction(ball5);
	}
	move_ball(ball5);
	// **********
	// * Ball 6 *
	// **********
	if (ball_hit_wall(ball6))
	{
		ball6.position.direction = select_ball_direction(ball6);
	}
	move_ball(ball6);
	// **********
	// * Ball 7 *
	// **********
	if (ball_hit_wall(ball7))
	{
		ball7.position.direction = select_ball_direction(ball7);
	}
	move_ball(ball7);
	// **********
	// * Ball 8 *
	// **********
	if (ball_hit_wall(ball8))
	{
		ball8.position.direction = select_ball_direction(ball8);
	}
	move_ball(ball8);


	// update the squares
	update_squares();

	//
	// clear the screen to black
	glColor3ub(0, 0, 0);
	glPolygonMode(GL_FRONT, GL_FILL);
	glRecti(0, 0, X_RESOLUTION, Y_RESOLUTION);
	//
	//


	draw_squares();

	draw_grid();

	if (meta_balls_enabled) {
		draw_ball(ball1);
		draw_ball(ball2);
		draw_ball(ball3);
		draw_ball(ball4);
		draw_ball(ball5);
		draw_ball(ball6);
		draw_ball(ball7);
		draw_ball(ball8);
	}
	glutSwapBuffers();
	glutPostRedisplay();
}

void reshape(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (h == 0)
	{
		glOrtho(0.0, X_RESOLUTION, 1, 0, -1.0, 1.0);
	}
	else
	{
		glOrtho(0.0, X_RESOLUTION, Y_RESOLUTION, 0, -1.0, 1.0);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'f':
		filled = !filled;
		break;
	case 'g':
		grid_enabled = !grid_enabled;
		break;
	case 'c':
		meta_balls_enabled = !meta_balls_enabled;
		break;
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

int main(int argc, char *argv[])
{
	// **************************
	// * ball 1 characteristics *
	// **************************
	ball1.position.x = X_RESOLUTION / 2;
	ball1.position.y = Y_RESOLUTION / 2,
		ball1.position.z = 0;
	ball1.position.direction = NORTH;
	ball1.radius = 50;
	ball1.color.r = 255;
	ball1.color.g = 255;
	ball1.color.b = 0;
	// **************************
	// * ball 2 characteristics *
	// **************************
	ball2.position.x = X_RESOLUTION / 2;
	ball2.position.y = Y_RESOLUTION / 2;
	ball2.position.z = 0;
	ball2.position.direction = EAST;
	ball2.radius = 50;
	ball2.color.r = 255;
	ball2.color.g = 255;
	ball2.color.b = 0;
	// **************************
	// * ball 3 characteristics *
	// **************************
	ball3.position.x = X_RESOLUTION / 2;
	ball3.position.y = Y_RESOLUTION / 2;
	ball3.position.z = 0;
	ball3.position.direction = SOUTH;
	ball3.radius = 50;
	ball3.color.r = 255;
	ball3.color.g = 255;
	ball3.color.b = 0;
	// **************************
	// * ball 4 characteristics *
	// **************************
	ball4.position.x = X_RESOLUTION / 2;
	ball4.position.y = Y_RESOLUTION / 2;
	ball4.position.z = 0;
	ball4.position.direction = WEST;
	ball4.radius = 50;
	ball4.color.r = 255;
	ball4.color.g = 255;
	ball4.color.b = 0;
	// **************************
	// * ball 5 characteristics *
	// **************************
	ball5.position.x = X_RESOLUTION / 2;
	ball5.position.y = Y_RESOLUTION / 2;
	ball5.position.z = 0;
	ball5.position.direction = NORTHEAST;
	ball5.radius = 50;
	ball5.color.r = 255;
	ball5.color.g = 255;
	ball5.color.b = 0;
	// **************************
	// * ball 6 characteristics *
	// **************************
	ball6.position.x = X_RESOLUTION / 2;
	ball6.position.y = Y_RESOLUTION / 2;
	ball6.position.z = 0;
	ball6.position.direction = NORTHWEST;
	ball6.radius = 50;
	ball6.color.r = 255;
	ball6.color.g = 255;
	ball6.color.b = 0;
	// **************************
	// * ball 7 characteristics *
	// **************************
	ball7.position.x = X_RESOLUTION / 2;
	ball7.position.y = Y_RESOLUTION / 2;
	ball7.position.z = 0;
	ball7.position.direction = SOUTHEAST;
	ball7.radius = 50;
	ball7.color.r = 255;
	ball7.color.g = 255;
	ball7.color.b = 0;
	// **************************
	// * ball 8 characteristics *
	// **************************
	ball8.position.x = X_RESOLUTION / 2;
	ball8.position.y = Y_RESOLUTION / 2;
	ball8.position.z = 0;
	ball8.position.direction = SOUTHEAST;
	ball8.radius = 50;
	ball8.color.r = 255;
	ball8.color.g = 255;
	ball8.color.b = 0;
	//

	init_squares();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(X_RESOLUTION, Y_RESOLUTION);
	glutCreateWindow("Chaz Acheronti -- Marching Squares");
	glutDisplayFunc(display);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutMainLoop();
}

