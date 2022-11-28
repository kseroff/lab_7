#include <iostream>
#include <vector>
using namespace std;

template<typename T>
class MyList {
public:
	class Iterator;
	MyList() : size(0), head(nullptr), tail(nullptr) {}
	~MyList() { delete head; delete tail; }

	T GetSize() { return size; }
    T GetTail() { return tail->data; }
	bool isEmpty() { return(head == nullptr); }
	void push_back(T data);
    void pop_back();
	Iterator begin() { return Iterator(head); }
	Iterator end() { return Iterator(nullptr); }

private:

	template<typename T>
	struct Node {
		T data;
		Node* next;
		Node* pred;

		Node(T data = T(), Node* pNext = nullptr, Node* pPred = nullptr) {
			this->data = data;
			this->next = pNext;
			this->pred = pPred;
		}
	};
	int size;
	Node<T>* head;
	Node<T>* tail;
};
template<typename T>
class MyList<T>::Iterator
{
	Node<T>* ptr;
public:

	Iterator() : ptr(nullptr) {};
	Iterator(Node<T>* p) : ptr(p) {}
	Iterator& operator ++ ()
	{
		if (ptr)
		{
			ptr = ptr->next; //Может быть еще и здесь кинуть исключение
			return *this;
		}
	}
	Iterator& operator -- ()
	{
		if (ptr)
		{
			ptr = ptr->pred; //Может быть еще и здесь кинуть исключение
			return *this;
		}
		else
		{
			ptr = tail;
			return *this;
		}
	}
	T& operator * ()
	{
		if (ptr)
			return ptr->data;

	}
	bool operator != (const Iterator& it) { return ptr != it.ptr; }
	bool operator == (const Iterator& it) { return ptr == it.ptr; }
};
template<typename T>
void MyList<T>::push_back(T data)
{
	Node<T>* temp = new Node<T>(data);
	temp->next = 0;
	temp->data = data;
	temp->pred = tail;

	if (tail != nullptr)
		tail->next = temp;

	if (size == 0) {
		head = tail = temp;
	}
	else {
		tail = temp;
	}
	size++;
}

template<typename T>
void MyList<T>::pop_back()
{
    Node<T>* temp = tail;
    tail = tail->pred;
    delete temp;
    size--;
    (size == 0) ? head=tail=nullptr : tail->next = nullptr;
}


class Graph {
private:
    ///////////////////
    bool** adjMatrix;
    bool* visited;
    bool* v;
    int numVertices;
    //////////////////
    MyList<int>* adjLists;
    bool* visit;

public:

    Graph(int numVertices)
    {
        this->numVertices = numVertices;
        adjMatrix = new bool* [numVertices];
        visited = new bool[numVertices];

        adjLists = new MyList<int>[numVertices];
        visit = new bool[numVertices];

        v = new bool[numVertices];

        for (int i = 0; i < numVertices; i++) {
            adjMatrix[i] = new bool[numVertices];
            visited[i] = false;
            visit[i] = false;
            v[i] = false;
            for (int j = 0; j < numVertices; j++)
                adjMatrix[i][j] = false;
        }
    }
    ~Graph() {
        for (int i = 0; i < numVertices; i++)
            delete[] adjMatrix[i];
        delete[] adjMatrix;
        delete[]visited;
        delete[]visit;
        delete[]v;
    }
    void toMatrix() {
        for (int i = 0; i < numVertices; i++) {
            cout << i << " : ";
            for (int j = 0; j < numVertices; j++) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
    void addEdge(int i, int j) {
        adjMatrix[i][j] = adjMatrix[j][i] = true;

        adjLists[i].push_back(j);
        adjLists[j].push_back(i);
    }
    void DFS_M(int st);
    void DFS(int start);
    void DFS_S(int v);
};

void Graph::DFS_S(int start)
{
    visit[start] = true;
    cout << start << " ";

    for (auto i = adjLists[start].begin(); i != adjLists[start].end(); ++i)
        if (!visit[*i])
            DFS_S(*i);
}

void Graph:: DFS_M(int start)
{
    visited[start] = true;
    cout << start << " ";

    for (int i = 0; i <= numVertices; i++)
        if ((adjMatrix[start][i] != 0) && (!visited[i]))
            DFS_M(i);
}

void Graph::DFS(int start) {
    MyList<int> S;
    int t;
    S.push_back(start);
    v[start]++;
    while (!S.isEmpty())
    {
        t = S.GetTail();
        S.pop_back();
        cout << t << " ";
        for (int i = numVertices - 1; i >= 0; i--)
            if (adjMatrix[t][i] && !v[i])
            {
                S.push_back(i);
                v[i]++;
            }
    }
}


int main()
{
    srand(time(0));
    setlocale(0, "");
    int z = 5;
    Graph c(z);

    for (int i = 0; i < z; i++)
    {
        for (int j = i + 1; j < z; j++)
        {
            if (bool(rand() % 2))
                c.addEdge(i, j);
        }
    }
    cout << "Матрица смежности" << endl;
    c.toMatrix();
    int start;
    cout<<endl << "Стартовая вершина > "; cin >> start;
    cout << "Порядок обхода: ";
    c.DFS_M(start);
    cout << endl<< "Порядок обхода: ";;
    c.DFS_S(start);
    cout<<endl << "Порядок обхода: ";
    c.DFS(start);

    cin.get();
    return 0;
}