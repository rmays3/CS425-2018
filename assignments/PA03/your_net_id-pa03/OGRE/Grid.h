////////////////////////////////////////////////////////
// Class to hold the grid layout of our environment

#ifndef GRID_H
#define GRID_H

#include <Ogre.h>
//#include <OgreApplicationContext.h>
//#include <OgreInput.h>

#include <iostream>
#include <vector>
#include <assert.h>

#define NODESIZE 10.0

class GridNode
{

private:

	int nodeID;			// identify for the node
	int rCoord;			// row coordinate
	int cCoord;			// column coordinate
	bool clear;			// is the node walkable?

public:
	Ogre::Entity *entity;	// a pointer to the entity in this node
	char contains;		// For printing... B = blocked, S = start, G = goal, numbers = path
	GridNode();			// default constructor
	GridNode(int nID, int row, int column, bool isC = true);	// create a node
	~GridNode();		// destroy a node

	void setID(int id);		// set the node id
	int getID(){return nodeID;};			// get the node ID
	void setRow(int r);		// set the row coordinate
	void setColumn(int c);		// set the column coordinate
	int getRow();				// get the row and column coordinate of the node
	int getColumn();
	Ogre::Vector3 getPosition(int rows, int cols);	// return the position of this node given the number of rows and columns
	void setClear();		// set the node as walkable
	void setOccupied();		// set the node as occupied
	bool isClear();			// is the node walkable
};

class GridRow // helper class
{
public:
	std::vector<GridNode> data;
	GridRow(int size) {data.resize(size);};
	~GridRow(){};
};

class Grid
{

public:

	Grid(Ogre::SceneManager* mSceneMgr, int numRows, int numCols);	// create a grid
	~Grid();					// destroy a grid

	GridNode* getNode(int r, int c);  // get the node specified

	GridNode* getNorthNode(GridNode* n);		  // get adjacent nodes;
	GridNode* getSouthNode(GridNode* n);
	GridNode* getEastNode(GridNode* n);
	GridNode* getWestNode(GridNode* n);
	GridNode* getNENode(GridNode* n);
	GridNode* getNWNode(GridNode* n);
	GridNode* getSENode(GridNode* n);
	GridNode* getSWNode(GridNode* n);

  // get Manhattan distance between between two nodes
	int getDistance(GridNode* node1, GridNode* node2);

	void printToFile();				// Print a grid to a file.  Good for debugging

  // load and place a model in a certain location.
	void loadObject(std::string name, std::string filename, int row, int height, int col, float scale = 1);

	Ogre::Vector3 getPosition(int r, int c);	// return the position, center of a cell

	//new!!!
	GridNode* getNode(const Ogre::Vector3& pos); //get the node based on position
	int getRows() const { return nRows; }
	int getCols() const { return nCols; }
	int getHeight() const { return NODESIZE*nRows;  }
	int getWidth() const { return NODESIZE*nCols; }

private:

	Ogre::SceneManager* mSceneMgr;		// pointer to scene graph
	std::vector<GridRow> data;  // actually hold the grid data
	int nRows;					// number of rows
	int nCols;					// number of columns
};

#endif
