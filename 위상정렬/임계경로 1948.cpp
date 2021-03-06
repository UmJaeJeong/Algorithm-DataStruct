#include<iostream>
#include<vector>
#include<algorithm>
#include<queue>
using namespace std;

//임계경로 1948
/*
문제:
월드 나라는 모든 도로가 일방통행인 도로이고, 싸이클이 없다.
그런데 어떤 무수히 많은 사람들이 월드 나라의 지도를 그리기 위해서,
어떤 시작 도시로부터 도착 도시까지 출발을 하여 가능한 모든 경로를 탐색한다고 한다.
이 지도를 그리는 사람들은 사이가 너무 좋아서 지도를 그리는 일을 다 마치고 도착 도시에서 모두 다 만나기로 하였다.
그렇다고 하였을 때 이들이 만나는 시간은 출발 도시로부터 출발한 후 최소 몇 시간 후에 만날 수 있는가?
즉, 마지막에 도착하는 사람까지 도착을 하는 시간을 의미한다.
어떤 사람은 이 시간에 만나기 위하여 1분도 쉬지 않고 달려야 한다.
이런 사람들이 지나는 도로의 수를 카운트 하여라.
출발 도시는 들어오는 도로가 0개이고, 도착 도시는 나가는 도로가 0개이다.

입력:
첫째 줄에 도시의 개수 n(1 ≤ n ≤ 10,000)이 주어지고 둘째 줄에는 도로의 개수 m(1 ≤ m ≤ 100,000)이 주어진다.
그리고 셋째 줄부터 m+2줄까지 다음과 같은 도로의 정보가 주어진다. 처음에는 도로의 출발 도시의 번호가 주어지고
그 다음에는 도착 도시의 번호, 그리고 마지막에는 이 도로를 지나는데 걸리는 시간이 주어진다.
도로를 지나가는 시간은 10,000보다 작거나 같은 자연수이다.
그리고 m+3째 줄에는 지도를 그리는 사람들이 출발하는 출발 도시와 도착 도시가 주어진다.
모든 도시는 출발 도시로부터 도달이 가능하고, 모든 도시로부터 도착 도시에 도달이 가능하다.
*/



//무사이클 = 위상정렬을 사용
//모든 임계구역을 알기위해서는 역추적을 해야함*****
//임계경로 ==> 출발점에서 도착점까지 가는 경로중 가장 긴경로
#define MAX 10001

class Edge {
public:
	int node;
	int time;

	//생성자 해당객체를 초기화 
	Edge(int x, int y) :node(x), time(y) {}

};


int n, start, finish;
int inDegree[MAX], result[MAX], c[MAX];//c라는 변수는 처리가 되었는지 여부
									   //임계경로에 한번만 되게 하려고 체크하는 변수


vector<Edge> a[MAX];
vector<Edge> b[MAX];

void topologySort() {
	queue<int> q;
	//시작점 노드를 큐에 삽입
	q.push(start);
	//방문할 노드가 없을떄까지 실행
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = 0; i < a[x].size(); i++) {
			Edge y = Edge(a[x][i].node, a[x][i].time);
			result[y.node] = max(result[y.node], y.time + result[x]);

			//새롭게 진입차수가 0이 된 정점을 큐에 삽입
			if (--inDegree[y.node] == 0) q.push(y.node);

		}
	}

	//역추적
	int count = 0;
	q.push(finish);
	while (!q.empty()) {
		int y = q.front();
		q.pop();
		for (int i = 0; i < b[y].size(); i++) {
			Edge x = Edge(b[y][i].node, b[y][i].time);
			//최장 경로에 포함되는 간선인지 확인
			if (result[y] - result[x.node] == x.time) {
				count++;
				if (c[x.node] == 0) {
					q.push(x.node);
					c[x.node] = 1;
				}
			}
		}
	}
	cout << result[finish] << ' ' << count << endl;
}

int main(void) {
	int m;
	cin >> n >> m;
	for (int i = 0; i < m; i++) {
		int x, node, time;
		cin >> x >> node >> time;
		a[x].push_back(Edge(node, time));
		b[node].push_back(Edge(x, time));
		inDegree[node]++;
	}
	cin >> start >> finish;
	topologySort();
}