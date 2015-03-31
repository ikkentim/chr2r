/**
 * QuadTree.h
 * Declares the QuadTree class.
 */
#pragma once

#include "AABB.h"
#include <vector>
#include "GameObject.h"

using namespace std;

#define QUAD_TREE_CAPACITY 10

// Represents a quad tree
class QuadTree
{
public:
    // A constructor which sets the boundaries
    QuadTree(AABB boundaries);

    // Default destructor
	~QuadTree();

    // Inserts an object into the tree
    bool insert_object(GameObject *object);

    // Removes an object from the tree
	bool delete_object(GameObject *object);

    // Queries the specified range
	int query_range(AABB range, GameObject **result, int previousCount);

private:
	// Axis-aligned bounding box stored as a center with half-dimensions
	// to represent the boundaries of this quad tree
	AABB boundary_;

	// Points in this quad tree node
	GameObject *points_[QUAD_TREE_CAPACITY];

	int reserved_ = 0;

	// Children
	QuadTree *northWest_ = NULL;
	QuadTree *northEast_ = NULL;
	QuadTree *southWest_ = NULL;
	QuadTree *southEast_ = NULL;

	void subdivide();
};