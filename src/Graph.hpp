#ifndef GRAPH_H
#define GRAPH_H

#include<set>
#include <string>
#include <vector>
#include <utility>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <stdexcept>
#include <unordered_set>
#include <algorithm>
#include <random>
#include <queue>
#include <set>
#include <cmath>
#include <fstream>
#include <time.h>
#include <cassert>
#include "utils/utils.hpp"
#include "utils/Timer.hpp"
#include "computeGraphlets.hpp"
#include "utils/utils.hpp"
#include "SparseMatrix.h"

using namespace std;

class Graph {

public:
    
    void setMaxGraphletSize(double number);
    static Graph loadGraph(string name);
    static Graph multGraph(string name, uint path);


    static void saveInGWFormat(string outputFile, const vector<string>& nodeNames,
        const vector<vector<ushort>>& edgeList);
    static void saveInGWFormatShuffled(string outputFile, const vector<string>& nodeNames,
        const vector<vector<ushort>>& edgeList);

    static void edgeList2gw(string fin, string fout);

    static void GeoGeneDuplicationModel(uint numNodes, uint numEdges, string outputFile);

    //void returnmaxSize(double max);
    //creates the null graph
    Graph();
    Graph(const Graph& G);
    //double maxsize;
    
    Graph(uint n, const vector<vector<ushort> > edgeList);

    string getName() const;

    uint getNumNodes() const;
    uint getNumEdges() const;
    const vector<vector<ushort> >& getConnectedComponents() const;
    uint getNumConnectedComponents() const;
    void getAdjMatrix(vector<vector<bool> >& adjMatrixCopy) const;
    void getAdjLists(vector<vector<ushort> >& adjListsCopy) const;
    void getEdgeList(vector<vector<ushort> > & edgeListCopy) const;
    vector<string> getNodeNames() const;

    //loads graph from file in GraphWin (.gw) format:
    //http://www.algorithmic-solutions.info/leda_guide/graphs/leda_native_graph_fileformat.html
    //note: it does not parse correctly files with comments or blank lines.
    void loadGwFile(const string& fileName);
    void multGwFile(const string& fileName, uint path);

    //nodes are relabeled so that the new i-th node is the node nodes[i]-th in this
    Graph nodeInducedSubgraph(const vector<ushort>& nodes) const;

    uint numNodeInducedSubgraphEdges(const vector<ushort>& subgraphNodes) const;

    vector<ushort> numEdgesAround(ushort node, ushort maxDist) const;
    vector<ushort> numNodesAround(ushort node, ushort maxDist) const;

    void printStats(int numConnectedComponentsToPrint, ostream& stream) const;

    void writeGraphEdgeListFormat(const string& fileName);
    void writeGraphEdgeListFormatNETAL(const string& fileName);
    void writeGraphEdgeListFormatPISWAP(const string& fileName);
    void writeGraphEdgeListFormatPINALOG(const string& fileName);

    void addRandomEdges(double addedEdgesProportion);
    void removeRandomEdges(double removedEdgesProportion);
    void rewireRandomEdges(double rewiredEdgesProportion);

    ushort randomNode();

    vector<vector<uint> > loadGraphletDegreeVectors();

    map<string,ushort> getNodeNameToIndexMap() const;
    map<ushort,string> getIndexToNodeNameMap() const;

    void getDistanceMatrix(vector<vector<short> >& dist) const;

    vector<uint> degreeDistribution() const;

    double getAverageDistance() const;

    void saveInGWFormat(string outputFile);
    void saveInGWFormatWithNames(string outputFile);
    void saveInShuffledOrder(string outputFile);
    void saveGraphletsAsSigs(string outputFile);

    Graph randomNodeInducedSubgraph(uint numNodes);

    bool isWellDefined();

    bool sameNodeNames(const Graph& other) const;

    // For locking
    void setLockedList(vector<string>& nodes, vector<string>& pairs);
    vector<bool>& getLockedList();
    bool isLocked(uint index) const;
    string getLockedTo(uint index);
    int getLockedCount();

    map<ushort, ushort> getLocking_ReIndexMap() const;
    map<ushort, ushort> getNodeTypes_ReIndexMap() const;

    void reIndexGraph(map<ushort, ushort> reIndexMap);  // Changes the node indexes according to the map

    // nodes-have-types
    void setNodeTypes(set<string> genes, set<string> miRNAs);
    string getNodeType(uint i);
    bool hasNodeTypes();

    // nodes-have-types -- TODO make them private later
    vector<string> nodeTypes;
    uint geneCount = 0;
    uint miRNACount = 0;
    int unlockedGeneCount = -1;
    int unlockedmiRNACount = -1;

private:
    double maxGraphletSize = 4; //default is 4, 5 is too big
    string name;
    //double maxsize;
    vector<vector<ushort> > edgeList; //edges in no particular order
    vector<vector<bool> > adjMatrix;
    vector<vector<ushort> > adjLists; //neighbors in no particular order

    //list of the nodes of each connected component, sorted from larger to smaller
    vector<vector<ushort> > connectedComponents;
    //int maxsize;

    // NOTE: these don't change after reIndexing G1 (method #3 of locking),
    // and they are used to reIndex the graph to normal at the end.
    vector<bool> lockedList;  // shows which nodes are locked
    vector<string> lockedTo;  // name of node we lock to in other graph
    int lockedCount = 0;

    void updateUnlockedGeneCount();

    void initConnectedComponents();

    void addEdge(ushort node1, ushort node2);
    void removeEdge(ushort node1, ushort node2);
    void addRandomEdge();
    void removeRandomEdge();

    string autogenFilesFolder();
    vector<vector<uint> > computeGraphletDegreeVectors();

    //places in dist a matrix with the distance between every pair of nodes (a -1 indicates infinity)
    void computeDistanceMatrix(vector<vector<short> >& dist) const;

};

#endif
