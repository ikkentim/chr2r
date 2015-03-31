/**
 * QuadTree.cpp
 * Defines the QuadTree class.
 */

#include "QuadTree.h"
#include <vector>

using namespace std;

QuadTree::QuadTree(AABB box)
{
	boundary_ = box;

	for (int i = 0; i < QUAD_TREE_CAPACITY; i++)
	{
		points_[i] = NULL;
	}
}

bool QuadTree::insert_object(GameObject *object)
{
	// Ignore objects that do not belong in this quad tree
	if (!boundary_.contains_point(object->position()))
		return false;

	// If there is space in this quad tree, add the object here
	if (reserved_ < QUAD_TREE_CAPACITY)
	{
		points_[reserved_++] = object;
		return true;
	}

	// Otherwise, subdivide and then add the point to whichever node will accept it
	if (northWest_ == NULL)
		subdivide();

	if (northWest_->insert_object(object)) return true;
    if (northEast_->insert_object(object)) return true;
    if (southWest_->insert_object(object)) return true;
    if (southEast_->insert_object(object)) return true;

	// Otherwise, the point cannot be inserted for some unknown reason (this should never happen)
	return false;
}

bool QuadTree::delete_object(GameObject* object)
{
	// Ignore objects that do not belong in this quad tree
	if (!boundary_.contains_point(object->position()))
		return false;

	for (int i = 0; i < QUAD_TREE_CAPACITY; i++)
	{
		if (points_[i] == object)
		{
			points_[i] = NULL;

			// move all the objects back in the array, we could have deleted a middle one
			while (i + 1 < QUAD_TREE_CAPACITY)
			{
				i++;
				if (points_[i] != NULL)
				{
					points_[i - 1] = points_[i];
					points_[i] = NULL;
				}
			}
			reserved_--;
			return true;
		}
	}

	if (northWest_ == NULL)
		return false;

	if (northWest_->delete_object(object)) return true;
    if (northEast_->delete_object(object)) return true;
    if (southWest_->delete_object(object)) return true;
    if (southEast_->delete_object(object)) return true;

	// Otherwise, the point cannot be deleted
	return false;
}

int QuadTree::query_range(AABB box, GameObject** objects, int count)
{
	// Automatically abort if the range does not intersect this quad
	if (!boundary_.intersects_with(box))
		return count; // empty list

	for (int i = 0; i < QUAD_TREE_CAPACITY; i++)
		if (points_[i] != NULL)
			if (box.contains_point(points_[i]->position()))
				objects[count++] = points_[i];

	// Terminate here, if there are no children
	if (!northWest_)
		return count;

	// Otherwise, add the points from the children
	count = northWest_->query_range(box, objects, count);
    count = northEast_->query_range(box, objects, count);
    count = southWest_->query_range(box, objects, count);
    count = southEast_->query_range(box, objects, count);

	return count;
}

void QuadTree::subdivide()
{
	Vector2 halfHalfDimension = boundary_.half_dimension / 2;

	AABB nwBox = AABB(boundary_.center - halfHalfDimension, halfHalfDimension);

	Vector2 neVector2;
	neVector2.x = boundary_.center.x + halfHalfDimension.x;
	neVector2.y = boundary_.center.y - halfHalfDimension.y;
	AABB neBox = AABB(neVector2, halfHalfDimension);

	AABB seBox = AABB(boundary_.center + halfHalfDimension, halfHalfDimension);

	Vector2 swVector2;
	swVector2.x = boundary_.center.x - halfHalfDimension.x;
	swVector2.y = boundary_.center.y + halfHalfDimension.y;
	AABB swBox = AABB(swVector2, halfHalfDimension);

	northWest_ = new QuadTree(nwBox);
	northEast_ = new QuadTree(neBox);
	southWest_ = new QuadTree(swBox);
	southEast_ = new QuadTree(seBox);
}

QuadTree::~QuadTree()
{
	if (northWest_ != NULL)
	{
		delete northWest_;
		delete northEast_;
		delete southWest_;
		delete southEast_;

		northWest_ = NULL;
		northEast_ = NULL;
		southWest_ = NULL;
		southEast_ = NULL;
	}
}