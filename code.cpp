#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<sstream>
#include<algorithm>
#include<cmath>
#include<ctime>
using namespace std;

vector<pair<vector<string>, int>> food;//인원수를 기준으로 정보가 정리된 배열
vector<pair<vector<string>, int>> Food;//모든 음식 정보를 가진 배열
//pair.first는 음식에 대한 정보,  pair.second은 가중치
//first[0]은 이름, first[1]은 방법별, first[2]는 상황별
//first[3]은 재료별, first[4]는 종류별, first[5] 인분, first[6]은 조리시간

int num;//식사인원

int partition1(vector<pair<vector<string>, int>>& v, int low, int high);
void quickSort1(vector<pair<vector<string>, int>> &v, int low, int high);

int partition2(vector<pair<vector<string>, int>>& v, int low, int high, int cmpIndex);
void quickSort2(vector<pair<vector<string>, int>> &v, int low, int high, int cmpIndex);

void QuickSort(vector<pair<vector<string>, int>>& v);

void HeapSort(vector<pair<vector<string>, int>> &v);
void heapify(vector<pair<vector<string>, int>>& v, int heapSize, int i, int cmpIndex);

void bubbleSort(vector<pair<vector<string>, int>> &v);
void selectionSort(vector<pair<vector<string>,int>> &v);
void insertionSort(vector<pair<vector<string>, int>> &v);
void introSort(vector<pair<vector<string>, int>> &v);

clock_t start, finish;

bool areVectorsEqual(const vector<string>& v1, const vector<string>& v2) {
	return v1.size() == v2.size() && equal(v1.begin(), v1.end(), v2.begin());
}

auto findFoodByName(const string& foodName) {
	return find_if(food.begin(), food.end(), [&](const auto& pair) {
		return pair.first.size() > 0 && pair.first[0] == foodName;
	});
}

bool compareByInt(const pair<vector<string>, int>& a, const pair<vector<string>, int>& b) {
	return a.second > b.second;
}

bool compareByName(const pair<vector<string>, int>& a, const pair<vector<string>, int>& b) {
	if (a.second == b.second) {
		if (a.first[6] == b.first[6]) {
			return a.first[0] < b.first[0];
		}
		else return stoi(a.first[6]) < stoi(b.first[6]);
	}
	else return a.second > b.second;
}


bool compareByTime(const pair<vector<string>, int>& a, const pair<vector<string>, int>& b) {
	if (a.second == b.second)
		return stoi(a.first[6]) < stoi(b.first[6]);
	else return a.second > b.second;
}

int main() {
	ifstream file("food.txt");

	if (!file.is_open()) {
		cerr << "음식을 불러올 수 없습니다." << endl;
		return 1;
	}


	string line;
	while (getline(file, line)) {
		istringstream iss(line);
		vector<string> f;//음식에 대한 정보를 저장할 배열

		string info;
		while (iss >> info) {
			f.push_back(info);
		}

		Food.push_back(make_pair(f, 0));
	}

	file.close();

	string f;
	int n;
	vector<pair<string, int>> userFood;//유저 선호도와 음식을 저장하는 배열
	while (f!="c") {
		cout << "음식을 입력하세요.(입력 종료를 원하시면 c를 입력해주세요.)" << endl;
		cin >> f;
		if (f == "c") {
			cout << "\n\n";
			break;
		}
		cout << "선호도를 입력해주세요. (-10 ~ 10)" << endl;
		cin >> n;
		userFood.push_back(make_pair(f, n));
		cout << "\n";
	}

	cout << "식사 인원을 입력해주세요(6명 이상이라면 6을 입력해주세요.) : ";
	cin >> num;
	cout << "\n";

	int fs = Food.size();
	for (int i = fs-1; i >= 0; i--) {
		pair<vector<string>, int> F;
		F = Food[i];
		Food.pop_back();
		if (stoi(F.first[5]) >= num) {
			food.push_back(F);
		}
	}//인원수에 맞게 음식 정보 정리

	vector<pair<vector<string>,int>> foundFood;
	for (int i = 0; i < userFood.size(); i++) {
		auto it = findFoodByName(userFood[i].first);
		if (it != food.end()) {
			vector<string> foodElement;
			for (const auto& element : it->first) {
				foodElement.push_back(element);
			}
			foodElement.push_back(to_string(it->second));
			foundFood.push_back(make_pair(foodElement,userFood[i].second));
		}
	}//유저가 입력한 음식이 가진 카테고리를 가진 모든 음식 저장(같은 카테고리라면 중복해서)

	for (int i = 0; i < food.size(); i++) {
		for (int j = 0; j < foundFood.size(); j++) {
			for (int k = 1; k < 7; k++) {
				if (food[i].first[k] == foundFood[j].first[k]) {
					food[i].second = food[i].second + foundFood[j].second;
				}
			}
		}
	}//음식별 가중치 계산

	vector<pair<vector<string>, int>> intro;
	vector<pair<vector<string>, int>> selection;
	vector<pair<vector<string>, int>> insertion;
	vector<pair<vector<string>, int>> bubble;
	vector<pair<vector<string>, int>> quick;
	vector<pair<vector<string>, int>> heap;
	intro = food;
	selection = food;
	insertion = food;
	bubble = food;
	quick = food;
	heap = food;
	cout << "intro" << endl;

	introSort(intro);

	for (int i = 0; i < 5; i++) {
		cout << intro[i].first[0];
		cout << endl;
	}//introsort
	
	cout << "\ninsertion" << endl;
	insertionSort(insertion);
	for (int i = 0; i < 5; i++) {
		cout << insertion[i].first[0];
		cout << endl;
	}//insertsort 

	cout << "\nselect" << endl;
	selectionSort(selection);
	for (int i = 0; i < 5; i++) {
		cout << selection[i].first[0];
		cout << endl;
	}//selectSort

	cout << "\nbubble" << endl;
	bubbleSort(bubble);
	for (int i = 0; i < 5; i++) {
		cout << bubble[i].first[0];
		cout << endl;
	}//bubbleSort

	cout << "\nquick" << endl;
	QuickSort(quick);
	for (int i = 0; i < 5; i++) {
		cout << quick[i].first[0];
		cout << endl;
	}//quickSort

	cout << "\nheap" << endl;
	HeapSort(heap);
	for (int i = 0; i < 5; i++) {
		cout << heap[i].first[0];
		cout << endl;
	}//heapSort

	return 0;
}

void introSort(vector<pair<vector<string>, int>> &v) {
	start = clock();
	sort(v.begin(), v.end(), compareByInt);//가중치 순으로 정렬

	sort(v.begin(), v.end(), compareByTime);//가중치가 같다면 조리시간으로 정렬

	sort(v.begin(), v.end(), compareByName);//가중치와 조리시간이 같다면 이름을 사전순으로 정렬
	finish = clock();
	cout << (double)(finish - start) / CLOCKS_PER_SEC << "초" << endl;
}

void selectionSort(vector<pair<vector<string>, int>> &v) {
	start = clock();
	int i, j, biggest, least;
	pair<vector<string>, int> tmp;
	for (i = 0; i < v.size() - 1; i++) {
		biggest = i;

		for (int j = i + 1; j < v.size(); j++) {
			if (v[j].second > v[biggest].second)
				biggest = j;
		}

		if (i != biggest) {
			tmp = v[i];
			v[i] = v[biggest];
			v[biggest] = tmp;
		}
	}//가중치로 정렬
	vector<int> index;
	int value;
	index.push_back(0);
	value = v[0].second;
	for (i = 1; i < v.size(); i++) {
		if (v[i].second != value) {
			index.push_back(i);
			value = v[i].second;
		}
	}//가중치가 같은 인덱스 범위 뽑아내기
	int n = 0;
	index.push_back(v.size() );
	while (n < index.size() - 1) {
		for (i = index[n]; i < index[n + 1]; i++) {
			least = i;
			for (j = i + 1; j < index[n + 1]; j++) {
				if (stoi(v[least].first[6]) > stoi(v[j].first[6]))
					least = j;
			}

			if (i != least) {
				tmp = v[i];
				v[i] = v[least];
				v[least] = tmp;
			}
		}
		n++;
	}//가중치가 같은 것끼리 조리시간으로 정렬

	vector<int> index3;
	n = 0;
	index3.push_back(0);
	string val = v[0].first[6];
	while (n < index.size() - 1) {
		for (i = index[n] ; i < index[n + 1]; i++) {
			if (v[i].first[6] != val) {
				index3.push_back(i);
				val = v[i].first[6];
			}
		}
		n++;
	}//가중치가 같은 것 중에 조리시간이 같은 것 인덱스 범위 뽑아내기

	n = 0;
	index3.push_back(v.size());


	while (n < index3.size() - 1) {
		for (i = index3[n]; i < index3[n + 1]; i++) {
			least = i;
			for (j = i + 1; j < index3[n + 1]; j++) {
				if (v[least].first[0].compare(v[j].first[0])==1) {
					least = j;
				}
			}

			if (i != least) {
				tmp = v[i];
				v[i] = v[least];
				v[least] = tmp;
			}
		}
		n++;
	}//가중치가 같고 조리시간이 같은 것들을 이름을 사전순으로 정렬
	finish = clock();
	cout << (double)(finish - start) / CLOCKS_PER_SEC << "초" << endl;
}

void insertionSort(vector<pair<vector<string>, int>> &v) {
	start = clock();
	int i, j, k;
	pair<vector<string>, int> key;

	for (i = 1; i < v.size(); i++) {
		key = v[i];

		j = i;
		while (j>0&&v[j - 1].second < key.second) {
			v[j] = v[j - 1];
			j--;
		}
		v[j] = key;
	}//가중치로 정렬

	vector<int> index;
	int value;
	index.push_back(-1);
	value = v[0].second;
	for (i = 1; i < v.size(); i++) {
		if (v[i].second != value) {
			index.push_back(i - 1);
			value = v[i].second;
		}
	}
	index.push_back(v.size() - 1);//가중치가 같은 것들의 인덱스 범위 뽑아내기

	int n = 0;
	index.push_back(v.size() - 1);
	while (n < index.size() - 1) {
		for (i = index[n] + 2; i < index[n + 1]+1; i++) {
			key = v[i];
			j = i;
			while (j > index[n]+1 && stoi(v[j - 1].first[6]) > stoi(key.first[6])) {
				v[j] = v[j - 1];
				j--;
			}
			v[j] = key;
		}
		n++;
	}//가중치가 같은 것들 중에 조리시간 순으로 정렬

	vector<int> index3;
	n = 0;
	index3.push_back(-1);
	string val = v[0].first[6];
	while (n < index.size() - 1) {
		for (i = index[n] + 1; i < index[n + 1]+1; i++) {
			if (v[i].first[6] != val) {
				index3.push_back(i - 1);
				val = v[i].first[6];
			}
		}
		n++;
	}//가중치가 같은 것들 중 조리시간이 같은 것들의 인덱스 범위 뽑아내기

	n = 0;
	index3.push_back(v.size() - 1);

	while (n < index3.size() - 1) {
		for (i = index3[n] + 2; i < index3[n + 1]+1; i++) {
			key = v[i];
			j = i;
			while (j > index3[n]+1 && v[j-1].first[0]>key.first[0]) {
				v[j] = v[j - 1];
				j--;
			}
			v[j] = key;
		}
		n++;
	}//가중치가 같은 것들 중 조리시간이 같은 것들을 사전순으로 정렬
	finish = clock();
	cout << (double)(finish - start) / CLOCKS_PER_SEC << "초" << endl;
}

void bubbleSort(vector<pair<vector<string>, int>> &v) {
	start = clock();
	int i, j, k;
	pair<vector<string>, int> tmp;

	for (i = v.size() - 1; i > 0; i--) {
		for (j = 0; j < i; j++) {
			if (v[j].second < v[j + 1].second) {
				tmp = v[j];
				v[j] = v[j + 1];
				v[j + 1] = tmp;
			}
		}
	}//가중치순으로 정렬

	vector<int> index;
	int value;
	index.push_back(-1);
	value = v[0].second;
	for (i = 1; i < v.size(); i++) {
		if (v[i].second != value) {
			index.push_back(i - 1);
			value = v[i].second;
		}
	}
	index.push_back(v.size() - 1);//가중치가 같은 것들의 인덱스 범위 뽑아내기


	int n = 0;
	while (n < index.size() - 1) {
		for (i = index[n + 1]; i > index[n] + 1; i--) {
			for (j = index[n] + 1; j < i; j++) {
				if (stoi(v[j].first[6]) > stoi(v[j + 1].first[6])) {
					swap(v[j], v[j + 1]);
				}
			}
		}
		n++;
	}//가중치가 같은 것들을 조리시간 순으로 정렬

	vector<int> index3;
	n = 0;
	index3.push_back(-1);
	string val = v[0].first[6];
	while (n < index.size() - 1) {
		for (i = index[n] + 1; i < index[n + 1]+1; i++) {
			if (v[i].first[6] != val) {
				index3.push_back(i - 1);
				val = v[i].first[6];
			}
		}
		n++;
	}
	index3.push_back(v.size() - 1);//가중치가 같은 것들 중 조리시간이 같은 것들의 인덱스 범위 뽑아내기

	n = 0;
	while (n < index3.size() - 1) {
		for (i = index3[n + 1]; i > index3[n] + 1; i--) {
			for (j = index3[n] + 1; j < i; j++) {
				if (v[j].first[0] > v[j + 1].first[0]) {
					swap(v[j], v[j + 1]);
				}
			}
		}
		n++;
	}//가중치가 같은 것들 중 조리시간이 같은 것들을 사전순으로 정렬
	finish = clock();
	cout << (double)(finish - start) / CLOCKS_PER_SEC << "초" << endl;
}

int partition1(vector<pair<vector<string>, int>>& v, int low, int high) {
	int pivot = v[high].second, i, j;
	i = low - 1;
	pair < vector<string>, int> tmp;
	for (j = low; j < high; j++) {
		if (v[j].second >= pivot) {
			i++;
			tmp = v[j];
			v[j] = v[i];
			v[i] = tmp;
		}
	}

	tmp = v[i + 1];
	v[i + 1] = v[high];
	v[high] = tmp;
	return i + 1;
}
void quickSort1(vector<pair<vector<string>, int>> &v, int low, int high) {
	if (low < high) {
		int pivotIndex = partition1(v, low, high);

		quickSort1(v, low, pivotIndex - 1);
		quickSort1(v, pivotIndex + 1, high);
	}
}

int partition2(vector<pair<vector<string>, int>>& v, int low, int high,int cmpIndex) {
	int i, j;
	string pivot = v[high].first[cmpIndex];
	i = low - 1;
	pair < vector<string>, int> tmp;
	for (j = low; j < high; j++) {
		if (cmpIndex == 6) {
			if (stoi(v[j].first[cmpIndex]) <= stoi(pivot)) {
				i++;
				tmp = v[j];
				v[j] = v[i];
				v[i] = tmp;
			}
		}
		else {
			if (v[j].first[cmpIndex] <= pivot) {
				i++;
				tmp = v[j];
				v[j] = v[i];
				v[i] = tmp;
			}
		}
	}

	tmp = v[i + 1];
	v[i + 1] = v[high];
	v[high] = tmp;
	return i + 1;
}
void quickSort2(vector<pair<vector<string>, int>> &v, int low, int high, int cmpIndex) {
	if (low < high) {
		int pivotIndex = partition2(v, low, high,cmpIndex);

		quickSort2(v, pivotIndex + 1, high, cmpIndex);
		quickSort2(v, low, pivotIndex - 1,cmpIndex);
	}
}

void QuickSort(vector<pair<vector<string>, int>>& v) {
	start = clock();
	int i;
	quickSort1(v, 0, v.size() - 1);//가중치 순으로 정렬

	vector<int> index;
	int value;
	index.push_back(-1);
	value = v[0].second;
	for (i = 1; i < v.size(); i++) {
		if (v[i].second != value) {
			index.push_back(i - 1);
			value = v[i].second;
		}
	}
	index.push_back(v.size() - 1);//가중치가 같은 것들의 인덱스 범위 뽑아내기
	int n;
	
	n = 0;
	while (n < index.size() - 1) {
		quickSort2(v, index[n] + 1, index[n + 1], 6);
		n++;
	}//가중치가 같은 것들을 조리시간 순으로 정렬하기

	vector<int> index3;
	n = 0;
	index3.push_back(-1);
	string val = v[0].first[6];
	while (n < index.size() - 1) {
		for (i = index[n] + 1; i < index[n + 1]+1; i++) {
			if (v[i].first[6] != val) {
				index3.push_back(i - 1);
				val = v[i].first[6];
			}
		}
		n++;
	}
	index3.push_back(v.size() - 1);//가중치가 같은 것들 중 조리시간이 같은 것들의 인덱스 뽑아내기

	n = 0;
	while (n < index3.size() - 1) {
		quickSort2(v, index3[n] + 1, index3[n + 1], 0);
		n++;
	}//가중치가 같은 것들 중 조리시간이 같은 것들을 사전순으로 정렬하기
	finish = clock();
	cout << (double)(finish - start) / CLOCKS_PER_SEC << "초" << endl;
}

void heapify(vector<pair<vector<string>, int>>& v, int heapSize, int i,int cmpIndex) {
	int largest = i;
	int l = 2 * i + 1;
	int r = 2 * i + 2;
	if (cmpIndex == -1) {//가중치기준 정렬
		if (l < heapSize && v[l].second < v[largest].second)
			largest = l;

		if (r < heapSize && v[r].second < v[largest].second)
			largest = r;
	}
	else if (cmpIndex == 6) {//조리시간기준 정렬
		if (l < heapSize && stoi(v[l].first[6]) > stoi(v[largest].first[6]))
			largest = l;

		if (r < heapSize && stoi(v[r].first[6]) > stoi(v[largest].first[6]))
			largest = r;
	}
	else if (cmpIndex == 0) {//이름 사전순 정렬
		if (l < heapSize && v[l].first[0].compare(v[largest].first[0])==1) {
			largest = l;
		}

		if (r < heapSize && v[r].first[0].compare(v[largest].first[0]) == 1) {
			largest = r;
		}
	}

	if (largest != i) {
		swap(v[i], v[largest]);

		heapify(v, heapSize, largest, cmpIndex);
	}
}

void HeapSort(vector<pair<vector<string>, int>>& v) {
	start = clock();
	int heapSize = v.size();
	int i, j;
	for (i = heapSize / 2 - 1; i >= 0; i--) {
		heapify(v, heapSize, i,-1);
	}

	for (i = heapSize - 1; i > 0; i--) {
		swap(v[0], v[i]);

		heapify(v, i, 0,-1);
	}
	//가중치 순으로 정렬
	vector<int> index;
	int value;
	index.push_back(0);
	value = v[0].second;
	for (i = 1; i < v.size(); i++) {
		if (v[i].second != value) {
			index.push_back(i);
			value = v[i].second;
		}
	}
	index.push_back(v.size());//가중치가 같은 것들의 인덱스 범위 뽑아내기
	int n;

	n = 0;

	while (n < index.size() - 1) {
		heapSize = index[n + 1] - index[n];
		vector<pair<vector<string>, int>> tmp;
		for (i = index[n]; i < index[n + 1]; i++)
			tmp.push_back(v[i]);

		for (j = heapSize / 2 - 1; j >= 0; j--) {
			heapify(tmp, heapSize, j, 6);
		}

		for (j = heapSize - 1; j > 0; j--) {
			swap(tmp[0], tmp[j]);

			heapify(tmp, j, 0, 6);
		}
		j = 0;
		for (i = index[n]; i < index[n + 1]; i++,j++) {
			v[i] = tmp[j];
		}

		n++;
	}//가중치가 같은 것들을 조리시간 순으로 정렬

	vector<int> index3;
	n = 0;
	index3.push_back(0);
	string val = v[0].first[6];
	while (n < index.size() - 1) {
		for (i = index[n]; i < index[n + 1]; i++) {
			if (v[i].first[6] != val) {
				index3.push_back(i);
				val = v[i].first[6];
			}
		}
		n++;
	}
	index3.push_back(v.size());//가중치가 같은 것들중 조리시간이 같은 것들의 인덱스 범위 뽑아내기
	n = 0;
	while (n < index3.size() - 1) {
		heapSize = index3[n + 1] - index3[n];
		vector<pair<vector<string>, int>> tmp;
		for (i = index3[n]; i < index3[n + 1]; i++) {
			tmp.push_back(v[i]);
		}

		for (j = heapSize / 2 - 1; j >= 0; j--) {
			heapify(tmp, heapSize, j, 0);
		}

		for (j = heapSize - 1; j > 0; j--) {
			swap(tmp[0], tmp[j]);

			heapify(tmp, j, 0, 0);
		}
		j = 0;
		for (i = index3[n]; i < index3[n + 1]; i++ , j++) {
			v[i] = tmp[j];
		}

		n++;
	}//가중치가 같은 것들 중 조리시간이 같은 것들을 사전순 정렬
	finish = clock();
	cout << (double)(finish - start) / CLOCKS_PER_SEC << "초" << endl;
}