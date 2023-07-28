#include<stdio.h>
#include<stdlib.h>
#include<limits.h>
#include "header.h"

// ANY STATIC FUNCTIONS ARE UP HERE


// YOUR SOLUTIONS BELOW

void dfs(int v,int n,const connection_t connections[n][n],int visited[n])
{
  visited[v] = 1;
  for(int i = 0;i<n;i++)
  {
    if(connections[v][i].distance > 0 && connections[v][i].distance < INT_MAX && !visited[i])
      dfs(i,n,connections,visited);
  }
}
void reversegraph(int n,const connection_t connections[n][n],connection_t newconnections[n][n])
{
  for(int i = 0;i<n;i++)
  {
    for(int j = 0;j<n;j++)
    {
      newconnections[i][j].distance = connections[j][i].distance;
      newconnections[i][j].time = connections[j][i].time;
    }
  }
}
int q1(int n,const connection_t connections[n][n])
{
  int visited[n];
  for(int i = 0;i<n;i++)
    visited[i] = 0;
  dfs(0,n,connections,visited);
  for(int i = 0;i<n;i++)
  {
    if(visited[i] == 0)
      return 0;
  }
  connection_t newconnections[n][n];
  reversegraph(n,connections,newconnections);
  for(int i = 0;i<n;i++)
    visited[i] = 0;
  dfs(0,n,newconnections,visited);
  for(int i = 0;i<n;i++)
  {
    if(visited[i] == 0)
      return 0;
  }
  return 1;
}

void paths(int s,int d,int n,const connection_t connections[n][n],int visited[n],int path[n],int path_index,int *K)
{
  visited[s] = 1;
  path[path_index] = s;
  path_index++;
  if(s == d)
  {
    if(*K > path_index)
      *K = path_index-1;
  }
  else
  {
    for (int i = 0;i<n;i++)
    {
      if(connections[s][i].distance > 0 && connections[s][i].distance < INT_MAX && !visited[i])
        paths(i,d,n,connections,visited,path,path_index,K);
    }
  }
  path_index--;
  visited[s] = 0;
}
int q2(const airport_t *src, const airport_t *dest, int n, int k,
       const connection_t connections[n][n])
{
  int visited[n];
  for(int i = 0;i<n;i++)
    visited[i] = 0;
  int path[n];
  int path_index = 0;
  int K = INT_MAX;
  paths(src->num_id,dest->num_id,n,connections,visited,path,path_index,&K);
  if(K <= k)
    return 1;
  else
    return 0;
}

void hamiltonian(int n,const connection_t connections[n][n],int visited[n],int result[n+1],int node,int start,int counter)
{
  if(counter == n && node == start)
    result[counter] = node;
  if(counter >= n || visited[node])
    return;
  visited[node] = 1;
  result[counter] = node;
  for(int i = 0;i<n;i++)
  {
    if(connections[node][i].distance > 0 && connections[node][i].distance < INT_MAX)
      hamiltonian(n,connections,visited,result,i,start,counter+1);   
  }
  visited[node] = 0;
}
int q3(const airport_t *src,int n,const connection_t connections[n][n])
{
  int visited[n];
  for(int i = 0;i<n;i++)
    visited[i] = 0;
  int result[n+1];
  for(int i = 0;i<n+1;i++)
    result[i] = -1;
  hamiltonian(n,connections,visited,result,src->num_id,src->num_id,0);
  for(int i = 0;i<n+1;i++)
  {
    if(result[i] == -1)
      return 0;
  }
  return 1;
}

void SWAP(const char **str1,const char **str2)
{
  const char *temp = *str1;
  *str1 = *str2;
  *str2 = temp;
}   
void swap(int *a,int *b)
{
  int temp;
  temp = *a;
  *a = *b;
  *b = temp;
}
int partition(airport_t airport_list[],int (*predicate_func)(const airport_t *, const airport_t *),int l,int r)
{
  int i;
  i = l;
  int j;
  j = r;
  while(i < j)
  {
    while(i <= r)
    {
      if(predicate_func(&airport_list[i],&airport_list[l]))
        i++;
      else
        break;
    }
    while(j > l)
    {
      if(!predicate_func(&airport_list[j],&airport_list[l]))
        j--;
      else
        break;
    }
    if(i < j)
    {
      swap(&airport_list[i].num_id,&airport_list[j].num_id);
      SWAP(&airport_list[i].airport_name,&airport_list[j].airport_name);
    }
  } 
  swap(&airport_list[l].num_id,&airport_list[j].num_id);
  SWAP(&airport_list[l].airport_name,&airport_list[j].airport_name);
  return j;
}
void quicksort(airport_t airport_list[],int (*predicate_func)(const airport_t *, const airport_t *),int l,int r)
{
  int p;
  if(l<r)
  {
    p = partition(airport_list,predicate_func,l,r);
    quicksort(airport_list,predicate_func,l,p-1);
    quicksort(airport_list,predicate_func,p+1,r);
  }  
}
void q4(int n, int (*predicate_func)(const airport_t *, const airport_t *),
        airport_t airport_list[n])
{
  quicksort(airport_list,predicate_func,0,n-1);
}

pair_t q5(int n, airport_t airports[n])
{
  pair_t ans = {-1, -1};
  int prefix,prevprefix = 0;
  for(int i = 0;i<n-1;i++)
  {
    prefix = 0;
    for(int j = i+1;j<n;j++)
    {
      for(int k = 0;k<3;k++)
      {
        if(airports[i].airport_name[k] == airports[j].airport_name[k])
          prefix++;
        else
        {
          if(prefix > prevprefix)
          {
            ans.first = i;
            ans.second = j;
          }
          prevprefix = prefix;
          break; 
        }
      }           
    }
  }
  return ans;
}

int q6(int n, int amount, const int entry_fee[n])
{
  int low = 0;
  int high = n-1;
  int mid; 
  while(low <= high)
  {
    mid = (low + high)/2;
    if(amount >= entry_fee[mid] && amount < entry_fee[mid+1])
      return mid+1;
    else if(entry_fee[mid] < amount)
      low = mid + 1;
    else
      high = mid - 1;
  }
  if(low > high)
    return n;
}

void shifttable(const char *pat,int m,int table[])
{
  for(int i = 0;i<125;i++)
    table[i] = m;
  for(int j = 0;j<m-1;j++)
    table[pat[j]] = m-1-j;
}
int horspool(const char *airports,const char *pat,int n,int m,int table[])
{
  int i;
  i = m-1;
  int k;
  while(i < n)
  {
    k = 0;
    while(k<m && pat[m-1-k] == airports[i-k])
      k++;
    if(k == m) 
      return i-m+1;
    else
      i += table[airports[i]];  
  }
  return -1;
}
void q7(int n, const char *pat, int contains[n],const airport_t airports[n])
{
  int table[125];
  int m = 0;
  while(pat[m] != '\0')
    m++;
  shifttable(pat,m,table);
  int p;
  for(int i = 0;i<n;i++)
  {
    p = 0;
    while(airports[i].airport_name[p])
      p++;
    if(horspool(airports[i].airport_name,pat,p,m,table) >= 0)
      contains[i] = 1;
  }
}

typedef struct node
{
  int vertex;
  int depth;
  int weight;
}Node;
void nswap(Node *a,Node *b) 
{
  int vertex_a = a->vertex;
  int weight_a = a->weight;
  int depth_a = a->depth;
  a->vertex = b->vertex;
  a->depth = b->depth;
  a->weight = b->weight;
  b->vertex = vertex_a;
  b->depth = depth_a;
  b->weight = weight_a;
}
void selection(Node arr[],int size) 
{
  for(int s = 0;s < size - 1;s++) 
  {
    int min = s;
    for(int i = s + 1;i < size;i++) 
    {
      if(arr[i].weight < arr[min].weight)
        min = i;
    }
    nswap(&arr[min],&arr[s]);
  }
}
int leastCost(int n,const connection_t connections[n][n],int src,int dest,int m,int *reached,int trip_order[n - 1])
{
  Node q[n];
  int r = -1;
  int f = 0;
  int trip_order_index = 0;
  Node temp;
  temp.vertex = src;
  temp.depth = 0;
  temp.weight = 0;
  r++;
  q[r] = temp;
  int min = INT_MAX;
  while(r >= 0)
  {
    Node node = q[0];
    int i = 0;
    while(i < r-1)
    {
      q[i] = q[i+1];
      i++;
    }
    r--;
    int v = node.vertex;
    int depth = node.depth;
    int cost = node.weight;
    trip_order[trip_order_index] = v;
    trip_order_index++;
    if(v == dest && depth == m)
    {
      *reached = 1;
      if(cost < min)
        min = cost;
    }
    if(depth > m) 
      break;
    for(int j = 0;j < n;j++)
    {
      if(connections[v][j].distance > 0 && connections[v][j].distance < INT_MAX && j != v)
      {
        Node h;
        h.vertex = j;
        h.depth = depth+1;
        h.weight = connections[v][j].distance;
        if(h.vertex != 0)
        {
          r++;
          q[r] = h;
        }
        selection(q,r+1);
      }
    }
  }
  return min;
}
int q8(int n,int trip_order[n - 1],const connection_t connections[n][n])
{
  for(int d=1;d<n;d++)
  {
    for(int j=1;j<n;j++)
    {
      int k = 0;
      int min = 0;
      int reached = 0;
      if(j != d && connections[d][j].distance > 0 && connections[d][j].distance < INT_MAX)
      {
        min = connections[d][j].distance;
        min += leastCost(n,connections,j,d,n-2,&reached,trip_order);
        if(reached == 1)
        {
          min = 0;
          for(int y = 0;y < n-2;y++)
            min += connections[trip_order[y]][trip_order[y+1]].distance;
          min += connections[trip_order[n-2]][trip_order[0]].distance;
        }
      }
      if(reached == 0)
      {
        for(int x=0;x < n-1;x++)
          trip_order[x] = -1;
      }
      if(reached == 1)
        return min;
    }
  }
  return -1;
}

void prim(int n,pair_t edges[n - 1],const connection_t connections[n][n])
{
  int *combination = calloc(n,sizeof(int));
  combination[0] = 1;
  int minedges = 0;
  while(minedges < n - 1)
  {
    int min = INT_MAX;
    int ti;
    int tj;
    int time;
    for(int i = 0;i<n;i++)
    {
      if(combination[i])
      {
        for(int j = 0;j<n;j++)
        {
          time = connections[i][j].time;
          if(!combination[j] && time != INT_MAX && time != 0)
          {
            if(time < min)
            {
              min = time;
              ti = i;
              tj = j;
            }
          }
        }
      }
    }
    edges[minedges].first = ti;
    edges[minedges].second = tj;
    combination[tj] = 1;
    minedges++;
  }
}
int q9(int n, pair_t edges[n - 1], const connection_t connections[n][n])
{
  for(int i = 0;i<n;i++)
  {
    edges[i].first = -1;
    edges[i].second = -1;
  }
  prim(n,edges,connections);
  int i = 0;
  int mintime = 0;
  while(edges[i].first != -1)
  {
    mintime += connections[edges[i].first][edges[i].second].time;
    i++;
  }
  return mintime;
}

void routes(int s,int d,int n,const connection_t connections[n][n],int visited[n],int path[n],int path_index,int *cost)
{
  visited[s] = 1;
  path[path_index] = s;
  path_index++;
  int time;
  if(s == d)
  {
    time = 0;
    for(int i = 0; i < path_index-1; i++)
      time += connections[path[i]][path[i+1]].time;
    if(*cost > time)
      *cost = time;
  }
  else
  {
    for (int i = 0;i<n;i++)
    {
      if(connections[s][i].distance > 0 && connections[s][i].distance < INT_MAX && !visited[i])
        routes(i,d,n,connections,visited,path,path_index,cost);
    }
  }
  path_index--;
  visited[s] = 0;
}
void q10(int n, int k, const airport_t *src,
         const connection_t connections[n][n], const int destinations[k],
         int costs[k])
{
  int visited[n];
  for(int i = 0;i<n;i++)
    visited[i] = 0;
  int path[n];
  int path_index = 0;
  for(int i = 0;i<k;i++)
    routes(src->num_id,destinations[i],n,connections,visited,path,path_index,&costs[i]);
}

// END
