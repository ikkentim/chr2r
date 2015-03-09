#pragma once

#include "AABB.h"
#include <vector>
#include "GameObject.h"

using namespace std;

#define QUAD_TREE_CAPACITY 50

class QuadTree
{
public:
	QuadTree();
	QuadTree(AABB*);
	bool Insert(GameObject*);
	bool Delete(GameObject*);
	void Subdivide();
	int QueryRange(AABB*, GameObject**, int);
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