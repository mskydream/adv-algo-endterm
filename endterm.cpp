#include <bits/stdc++.h>

using namespace std;

int n; // nodes
int m; // edges

struct edges {
 	// weight of edge
 	int w;
 	
 	// two nodes of edge
 	int x;
 	int y;
};

vector<edges> edge;

int s, v; //from s to v -> s - start node / v - final node

int k; // current day

int p[1000005]; //array for keeping parent of nodes


//comporator of sort
bool cmp(edges a, edges b) {
 	return a.w < b.w; // sort by weight
}

//get parent of node x
int get(int x) {
 	return p[x] == x ? x : p[x] = get(p[x]);
}

//adding edge with x and y nodes from two sides  
void add(int x, int y) {
 	x = get(x);
 	y = get(y);
 	if (x == y) return;
 	p[x] = y;
}


int main() {
	//input of data
	cin >> n >> m >> s >> v >> k;
	for (int i = 1; i <= m; i++) {
		int x, y, w;
		cin >> x >> y >> w;
		                          
		//inserting edge to vector
		edge.push_back({w, x, y});
	}

	//sort edges by weight
	sort(edge.begin(), edge.end(), cmp);  //calling comporator for edge

	//here we will use MST and kruskal algorithm

	for (int i = 1; i <= n; i++) p[i] = i; // parent of i th node - i

	int ans = -1;

	for (int i = 0; i < m; i++) {
		
		//parsing edge in i-th position
		int x = edge[i].x;
		int y = edge[i].y;
		int w = edge[i].w;

		//getting parent of nodes
		x = get(x);
		y = get(y);

		//checking are they in one component
		if (x == y) {
		 	
		 	if (get(s) == get(v)) {
		 		//now if start node and finish node in one component then stop the algorithm
		 		ans = w;
		 		break;
			}
			//just continue;
		 	continue;
		}

		//call adding function to MST
		add(x, y);

		if (get(s) == get(v)) {
		 	//now if start node and finish node in one component then stop the algorithm
		 	ans = w;
		 	break;
		}

  }

  if (ans == -1) {
   	//there is no path from s to v
   	cout << "No path",exit(0);
  }
 
  if (k >= ans) {
   	//all days for creating path from s to v already passed
   	cout << 0, exit(0);
  }
  else cout << ans - k << endl;


	return 0;
}
