#pragma once

#include "AABB.h"
#include <vector>
#include "GameObject.h"

using namespace std;

#define QUAD_TREE_CAPACITY 10

class QuadTree
{
public:
	QuadTree();
	QuadTree(AABB*);
	bool insert_object(GameObject*);
	bool delete_object(GameObject*);
	void subdivide();
	int query_range(AABB*, GameObject**, int);
	~QuadTree();
private:
	// Axis-aligned bounding box stored as a center with half-dimensions
	// to represent the boundaries of this quad tree
	AABB* boundary_;

	// Points in this quad tree node
	GameObject* points_[QUAD_TREE_CAPACITY];

	int reserved_ = 0;

	// Children
	QuadTree* northWest_ = NULL;
	QuadTree* northEast_ = NULL;
	QuadTree* southWest_ = NULL;
	QuadTree* southEast_ = NULL;
};