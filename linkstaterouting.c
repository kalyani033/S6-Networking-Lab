#include <stdio.h>
#include <string.h>

int main()
{
    int count, src_router, i, j, k, w, v, min;
    int cost_matrix[100][100], dist[100], last[100];
    int flag[100];

    // Input the number of routers
    printf("\nEnter the number of routers: ");
    scanf("%d", &count);

    // Input the cost matrix values for each router connection
    printf("\nEnter the cost matrix values:\n");
    for (i = 0; i < count; i++)
    {
        for (j = 0; j < count; j++)
        {
            printf("%d->%d: ", i, j);
            scanf("%d", &cost_matrix[i][j]);
            // If the link cost is negative, set it to a large value (infinity)
            if (cost_matrix[i][j] < 0)
                cost_matrix[i][j] = 1000;
        }
    }

    // Input the source router from which shortest paths are to be calculated
    printf("\nEnter the source router: ");
    scanf("%d", &src_router);

    // Initialization of data structures for the link-state routing algorithm
    for (v = 0; v < count; v++)
    {
        flag[v] = 0;
        last[v] = src_router;
        dist[v] = cost_matrix[src_router][v];
    }
    flag[src_router] = 1;

    // Dijkstra's algorithm to find the shortest paths and costs from the source router to all other routers
    for (i = 0; i < count; i++)
    {
        min = 1000;
        // Find the router with the minimum distance from the source that has not been visited yet
        for (w = 0; w < count; w++)
        {
            if (!flag[w] && dist[w] < min)
            {
                v = w;
                min = dist[w];
            }
        }
        flag[v] = 1;
        // Update the distances and previous routers for the neighbors of the current router
        for (w = 0; w < count; w++)
        {
            if (!flag[w] && min + cost_matrix[v][w] < dist[w])
            {
                dist[w] = min + cost_matrix[v][w];
                last[w] = v;
            }
        }
    }

    // Print the shortest paths and costs from the source router to all other routers
    printf("\nShortest paths from router %d:\n", src_router);
    for (i = 0; i < count; i++)
    {
        printf("%d ==> %d: Path taken: %d", src_router, i, i);
        w = i;
        while (w != src_router)
        {
            printf(" <-- %d", last[w]);
            w = last[w];
        }
        printf("\nShortest path cost: %d\n", dist[i]);
    }

    return 0;
}
