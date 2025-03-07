#include <iostream>
#include <vector>

using namespace std;

int n, answer = 0;
int dx[4] = { 0, 0, 1, 1 };
int dy[4] = { 0, 1, 0, 1 };
int map[101][101] = { 0 };
vector< vector<int> > curves;

void dragon_curve(int x, int y, int d, int g) {
	int lastX = x, lastY = y;
	int dirx[4] = { 0, -1, 0, 1 };
	int diry[4] = { 1, 0, -1, 0 };
	vector< pair<int, int> > points, diff;
	points.push_back({ x, y });

	if (x > 0 && y > 0 && x < 100 && y < 100) {		//0세대
		points.push_back({ x + dirx[d], y + diry[d] });
		lastX = x + dirx[d];
		lastY = y + diry[d];
	}

	for (int i = 1; i <= g; i++) {
		diff.clear();
		for (int j = 0; j < points.size() - 1; j++) {
			diff.push_back({ points[j + 1].first - points[j].first, points[j + 1].second - points[j].second });	//두 점 간 차이
		}

		for (int j = 1; j <= diff.size(); j++) {
			int addX = -1, addY = -1;
			for (int k = 0; k < 4; k++) {			//90도 회전
				if (diff[diff.size() - j].first == dirx[k] && diff[diff.size() - j].second == diry[k]) {
					if (k == 0) {
						addX = dirx[3] * -1;
						addY = diry[3] * -1;
						break;
					}
					else {
						addX = dirx[k - 1] * -1;
						addY = diry[k - 1] * -1;
						break;
					}
				}
			}

			lastX += addX;
			lastY += addY;

			points.push_back({ lastX, lastY });		//i세대 드래곤 커브
		}
	}

	for (int i = 0; i < points.size(); i++)			//좌표 표시
		map[points[i].first][points[i].second] = 1;
}

int main() {
	cin >> n;		//input
	for (int i = 0; i < n; i++) {
		vector<int> v(4);
		curves.push_back(v);
		for (int j = 0; j < 4; j++) {
			cin >> curves[i][j];
		}
	}

	for (int i = 0; i < curves.size(); i++) {		//드래곤 커브 실행
		dragon_curve(curves[i][1], curves[i][0], curves[i][2], curves[i][3]);
	}

	for (int i = 0; i < 100; i++) {		//answer 카운트
		for (int j = 0; j < 100; j++) {
			for (int k = 0; k < 4; k++) {
				if (map[i + dx[k]][j + dy[k]] != 1)	//(점 4개 중 일부) != 1
					break;
				else if (k == 3)		//(점 4개) == 1
					answer++;
			}
		}
	}

	cout << answer << endl;

	return 0;
}