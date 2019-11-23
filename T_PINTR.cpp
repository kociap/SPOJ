#include <cstdio>

using namespace std;

class Point {
public:
	int x;
	int y;

	Point() {};
	Point(int _x, int _y) {
		x = _x;
		y = _y;
	};
};

inline int determinant(int x1, int y1, int x2, int y2, int x3, int y3);
inline bool overlapsVertex(Point* vertex, Point* point);
inline bool liesOnEdge(Point* vertex1, Point* vertex2, Point* vertex3, Point* point);
inline bool liesInsideTriangle(Point* vertex1, Point* vertex2, Point* vertex3, Point* point);

int main() {

	Point* vertex1 = new Point();
	Point* vertex2 = new Point();
	Point* vertex3 = new Point();
	Point* point = new Point();

	while (true) {
		scanf("%d %d %d %d %d %d %d %d", &(vertex1->x), &(vertex1->y), &(vertex2->x), &(vertex2->y), &(vertex3->x), &(vertex3->y), &(point->x), &(point->y));

		if (vertex1->x == 0 && vertex1->y == 0 && vertex2->x == 0 && vertex2->y == 0 && vertex3->x == 0 && vertex3->y == 0 && point->x == 0 && point->y == 0) {
			break;
		}

		if (overlapsVertex(vertex1, point) || overlapsVertex(vertex2, point) || overlapsVertex(vertex3, point) ||
			liesOnEdge(vertex1, vertex2, vertex3, point) || liesOnEdge(vertex2, vertex3, vertex1, point) ||
			liesOnEdge(vertex3, vertex1, vertex2, point)) {
			printf("E\n");
		} else if (liesInsideTriangle(vertex1, vertex2, vertex3, point)) {
			printf("I\n");
		} else {
			printf("O\n");
		}
	}

	delete vertex1;
	delete vertex2;
	delete vertex3;
	delete point;

	return 0;
}

inline int determinant(int x1, int y1, int x2, int y2, int x3, int y3) {
	int determinant = x1 * y2 + x2 * y3 + x3 * y1 - x2 * y1 - x3 * y2 - x1 * y3;

	if (determinant < 0) {
		return -1;
	} else if (determinant == 0) {
		return 0;
	} else {
		return 1;
	}
}

inline bool overlapsVertex(Point* vertex, Point* point) {
	return vertex->x == point->x && vertex->y == point->y;
}

inline bool liesOnEdge(Point* vertex1, Point* vertex2, Point* vertex3, Point* point) {
	return determinant(vertex1->x, vertex1->y, vertex2->x, vertex2->y, point->x, point->y) == 0 &&
		determinant(vertex3->x, vertex3->y, vertex1->x, vertex1->y, point->x, point->y) == determinant(vertex3->x, vertex3->y, vertex1->x, vertex1->y, vertex2->x, vertex2->y) && 
		determinant(vertex3->x, vertex3->y, vertex2->x, vertex2->y, point->x, point->y) == determinant(vertex3->x, vertex3->y, vertex2->x, vertex2->y, vertex1->x, vertex1->y);
}

inline bool liesInsideTriangle(Point* vertex1, Point* vertex2, Point* vertex3, Point* point) {
	return determinant(vertex3->x, vertex3->y, vertex2->x, vertex2->y, point->x, point->y) == determinant(vertex3->x, vertex3->y, vertex2->x, vertex2->y, vertex1->x, vertex1->y) &&
		determinant(vertex2->x, vertex2->y, vertex1->x, vertex1->y, point->x, point->y) == determinant(vertex2->x, vertex2->y, vertex1->x, vertex1->y, vertex3->x, vertex3->y) &&
		determinant(vertex1->x, vertex1->y, vertex3->x, vertex3->y, point->x, point->y) == determinant(vertex1->x, vertex1->y, vertex3->x, vertex3->y, vertex2->x, vertex2->y);
}