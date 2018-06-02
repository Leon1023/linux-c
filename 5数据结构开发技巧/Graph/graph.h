#define MAXVEX 100
#define INFINITY  65535

typedef char VertexType;
typedef int EdgeType;
typedef int Status;
typedef struct MGraph
{
    VertexType  vexs[MAXVEX];
    EdgeType arc[MAXVEX][MAXVEX];
    int numVertexes,NumEdges;
}MGraph;
void CreatMGraph(MGraph *G);
