#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define INFINITY INT_MAX

int ** createMatrix(int numberOfRows, int numberOfColumns) {
    int i = 0;
    int ** matrix = (int **)malloc(sizeof(int*[numberOfRows]));

	for(i; i < numberOfRows; i++) {
		matrix[i] = (int *) malloc(sizeof(int[numberOfColumns]));
    }

    return matrix;
}

int isValidToApplyDijkstra(int ** graph, int numbersOfNode) {
    for(int i = 0; i < numbersOfNode; i++) {
        for(int j = 0; i < numbersOfNode; j++) {
            if((i == j && graph[i][j] != INFINITY) || graph[i][j] < 0) return 0;
        }
    }

    return 1;
}

int findIndex(int item, int items[], int numberOfItems) {
    for(int i = 0; i < numberOfItems; i++)
        if(items[i] == item) return i;

    return -1;
}

int minDistance(int distance[], int visited[], int numbersOfNodes) {
    int min = INFINITY;
    int min_index = INFINITY;

    for(int i = 0; i < numbersOfNodes; i++) {
        if(!visited[i] && distance[i] <= min) {
            min = distance[i];
            min_index = i;
        }
    }

    return min_index;
}

void dijkstra(int ** graph, int src, int end, int nodes[], int numbersOfNode) {
    int distance[numbersOfNode];
    int visited[numbersOfNode];
    int path[numbersOfNode];

    int indexStartNode = findIndex(src, nodes, numbersOfNode);
    int indexEndNode = findIndex(end, nodes, numbersOfNode);

    for(int i = 0; i < numbersOfNode; i++) {
        distance[i] = INFINITY;
        path[i] = INFINITY;
        visited[i] = 0;
    }

    path[indexStartNode] = src;
    path[indexEndNode] = end;
    distance[indexStartNode] = 0;

    for(int i = 0; i < numbersOfNode - 1; i++) {
        int md = minDistance(distance, visited, numbersOfNode);
        visited[md] = 1;

        for(int j = 0; j < numbersOfNode; j++) {
            if(!visited[j] && graph[md][j] != INFINITY && distance[md] != INFINITY && distance[md] + graph[md][j] < distance[j]) {
                distance[j] = distance[md] + graph[md][j];
                path[md] = nodes[md];
            }
        }
    }

    printf("caminho: ");

    for(int i = 0; i < numbersOfNode; i++) {
        if(path[i] != INFINITY)
            (i == (numbersOfNode - 1)) ? printf("%d", path[i]) : printf("%d,", path[i]);
    }

    printf("\n");
}

void freeMatrix(int ** matrix, int numberOfRows) {
    for(int i = 0; i < numberOfRows; i++)
		free(matrix[i]);
	free(matrix);
}

void createUnDirectedGraph(int ** matrix, int * nodes, int isWeighted, int quantityOfNodes) {
    int relation, weight;

    for(int i = 0; i < quantityOfNodes; i++) {
        printf("\nDigite os nos adjacentes ao no %d (nem todos os valores serao perguntados) \n\n", nodes[i]);
        for(int j = 0; j < quantityOfNodes; j++) {

            if(j >= i) {
                printf("\nO no %d esta conectado com o no %d? (0 - Nao, 1 - Sim): ", nodes[i], nodes[j]);
                scanf("%d", &relation);

                if(isWeighted) {
                    if(relation) {
                        printf("\nDigite o peso da aresta entre o no %d e o no %d: ",  nodes[i], nodes[j]);
                        scanf("%d", &weight);
                        matrix[i][j] = weight;
                        matrix[j][i] = weight;
                    } else {
                        matrix[i][j] = INFINITY;
                        matrix[j][i] = INFINITY;
                    }
                } else {
                    if(relation) {
                        matrix[i][j] = 1;
                        matrix[j][i] = 1;
                    } else {
                        matrix[i][j] = 0;
                        matrix[j][i] = 0;
                    }
                }
            }
        }
    }

    printf("\n");
}

void createDirectedGraph(int ** matrix, int * nodes ,int isWeighted, int quantityOfNodes) {
    int relation, weight;

    for(int i = 0; i < quantityOfNodes; i++) {
        printf("\nDigite os nos adjacentes ao no %d\n\n", nodes[i]);
        for(int j = 0; j < quantityOfNodes; j++) {
            printf("\nO no %d esta conectado com o no %d? (0 - Nao, 1 - Sim): ", nodes[i], nodes[j]);
            scanf("%d", &relation);

            if(isWeighted) {
                if(relation) {
                    printf("\nDigite o peso da aresta entre o no %d e o no %d: ",  nodes[i], nodes[j]);
                    scanf("%d", &weight);
                    matrix[i][j] = weight;
                } else {
                    matrix[i][j] = INFINITY;
                }
            } else {
                if(relation) {
                    matrix[i][j] = 1;
                } else {
                    matrix[i][j] = 0;
                }
            }
        }
    }

    printf("\n");
}

void showMatrix(int ** matrix, int * nodes, int quantityOfNodes) {
    printf("\n\n\n");
    for(int i = 0; i < quantityOfNodes; i++) {
        printf("\t%d", nodes[i]);
    }
    printf("\n\n\n");
    for(int i = 0; i < quantityOfNodes; i++) {
        printf("%d", nodes[i]);

        for(int j = 0; j < quantityOfNodes; j++) {
            printf("\t%d ", matrix[i][j]);
        }
        printf("\n");
    }
    printf("\n\n\n");
}

int main()
{
    int startNode;
    int endNode;
    int quantityOfNodes;
    int nodeValue;
    int option;
    int isDirected;
    int isWeighted;
    int * nodes = NULL;
    int ** adjacencyMatrix = NULL;

    do {
        printf("0 - Encerrar o programa\n1 - Construir o grafo\n2 - Impressao  da  matriz  de  adjacencias\n3 - Impressao  de  percursos\n4 - Ordenacao Topologica\n5 - Caminho  de  distancia  minima\n");

        printf("\nDigite a opcao desejada: ");
        scanf("%d", &option);

        switch(option) {
            case 1:
                printf("\nDigite a quantidade de nos do grafo: ");
                scanf("%d", &quantityOfNodes);

                if(nodes != NULL) {
                    free(nodes);
                    nodes = NULL;
                }
                nodes = (int *) malloc(sizeof(int[quantityOfNodes]));

                if(adjacencyMatrix != NULL) {
                    freeMatrix(adjacencyMatrix, quantityOfNodes);
                    adjacencyMatrix = NULL;
                }

                adjacencyMatrix = createMatrix(quantityOfNodes, quantityOfNodes);

                for(int i = 0; i < quantityOfNodes; i++) {
                    printf("\nDigite o valor do no %d: ", i);
                    scanf("%d", &nodes[i]);
                }

                printf("\nO grafo vai ser direcionado? (0 - Nao, 1 - Sim): ");
                scanf("%d", &isDirected);

                printf("\nO grafo vai ser ponderado? (0 - Nao, 1 - Sim): ");
                scanf("%d", &isWeighted);

                if(isDirected) {
                    createDirectedGraph(adjacencyMatrix, nodes, isWeighted, quantityOfNodes);
                } else {
                    createUnDirectedGraph(adjacencyMatrix, nodes, isWeighted, quantityOfNodes);
                }

                printf("\n");
            break;
            case 2:

                if(adjacencyMatrix != NULL) {
                    showMatrix(adjacencyMatrix, nodes, quantityOfNodes);
                } else {
                    printf("\nVoce nao criou seu grafo ainda\n");
                }

                printf("\n");
            break;
            case 5:
                if(!isValidToApplyDijkstra(adjacencyMatrix, quantityOfNodes)) {
                    printf("\nGrafo invalido para aplicar dijkstra!\n\n");
                    break;
                }

                printf("\nDigite o no inicial da busca: ");
                scanf("%d", &startNode);

                printf("Digite o no final da busca: ");
                scanf("%d", &endNode);


                printf("\n");

                dijkstra(adjacencyMatrix, startNode, endNode, nodes, quantityOfNodes);

                printf("\n");
            break;
        }
    } while(option != 0);
}
