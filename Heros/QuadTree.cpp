#include "QuadTree.h"
#include <vector>

using namespace std;

QuadTree::QuadTree(AABB* box)
{
	boundary_ = box;

	for (int i = 0; i < QUAD_TREE_CAPACITY; i++)
	{
		points_[i] = NULL;
	}
}

bool QuadTree::Insert(GameObject *object)
{
	// Ignore objects that do not belong in this quad tree
	if (!boundary_->ContainsPoint(object))
		return false;

	// If there is space in this quad tree, add the object here
	if (reserved_ < QUAD_TREE_CAPACITY)
	{
		points_[reserved_++] = object;
		return true;
	}

	// Otherwise, subdivide and then add the point to whichever node will accept it
	if (northWest_ == NULL)
		Subdivide();

	if (northWest_->Insert(object)) return true;
	if (northEast_->Insert(object)) return true;
	if (southWest_->Insert(object)) return true;
	if (southEast_->Insert(object)) return true;

	// Otherwise, the point cannot be inserted for some unknown reason (this should never happen)
	return false;
}

bool QuadTree::Delete(GameObject* object)
{
	// Ignore objects that do not belong in this quad tree
	if (!boundary_->ContainsPoint(object))
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

	if (northWest_->Delete(object)) return true;
	if (northEast_->Delete(object)) return true;
	if (southWest_->Delete(object)) return true;
	if (southEast_->Delete(object)) return true;

	// Otherwise, the point cannot be deleted
	return false;
}

int QuadTree::QueryRange(AABB *box, GameObject** objects, int count)
{
	// Automatically abort if the range does not intersect this quad
	if (!boundary_->IntersectsWith(box))
		return count; // empty list

	for (int i = 0; i < QUAD_TREE_CAPACITY; i++)
		if (points_[i] != NULL)
			if (box->ContainsPoint(points_[i]))
				objects[count++] = points_[i];

	// Terminate here, if there are no children
	if (!northWest_)
		return count;

	// Otherwise, add the points from the children
	count = northWest_->QueryRange(box, objects, count);
	count = northEast_->QueryRange(box, objects, count);
	count = southWest_->QueryRange(box, objects, count);
	count = southEast_->QueryRange(box, objects, count);

	return count;
}

void QuadTree::Subdivide()
{
	Vector2 halfHalfDimension = boundary_->HalfDimension() / 2;

	AABB* nwBox = new AABB(boundary_->Center() - halfHalfDimension, halfHalfDimension);

	Vector2 neVector2;
	neVector2.x = boundary_->Center().x + halfHalfDimension.x;
	neVector2.y = boundary_->Center().y - halfHalfDimension.y;
	AABB* neBox = new AABB(neVector2, halfHalfDimension);

	AABB* seBox = new AABB(boundary_->Center() + halfHalfDimension, halfHalfDimension);

	Vector2 swVector2;
	swVector2.x = boundary_->Center().x - halfHalfDimension.x;
	swVector2.y = boundary_->Center().y + halfHalfDimension.y;
	AABB* swBox = new AABB(swVector2, halfHalfDimension);

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
	
	if (boundary_ != NULL)
		delete boundary_;
	
	for (int i = 0; i < QUAD_TREE_CAPACITY; i++)
	{
		if (points_[i] != NULL)
		{
			delete points_[i];
			points_[i] = NULL;
		}
	}
}