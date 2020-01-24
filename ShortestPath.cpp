#include<iostream>
#include<fstream>
#include <cmath>
#include<string>
//#include<sstream>
//#include <cstdlib>
#define INFINITY 100000
#define  numOfVertices 25

using namespace std;
int city_connected_count = 0;
int return_index_string(string **&data_2, string str) {
	for (int i = 0; i < numOfVertices; ++i)
	{
		if (str == data_2[i][0])
			return i;
	}

}
int *most_visited_city = new int[numOfVertices];

struct  link_Node
{
	string city;  int weight; link_Node *next;
	string return_node_city()
	{
		return city;
	}
	int return_node_weight()
	{
		return weight;
	}
};
class Linked_List
{
private:
	link_Node *head, *p, *q, *t; int node_count;
public:
	Linked_List()
	{
		node_count = 0;
		head = NULL;
	}
	void CreateNode(string s, int a)
	{
		p = new link_Node();
		p->city = s;
		p->weight = a;
		head = p;
		p->next = NULL;
	}

	void Insert(string s, int in)
	{
		if (head == NULL)
		{
			p = new link_Node();
			p->city = s;
			p->weight = in;
			head = p;
			p->next = NULL;
		}
		else
		{
			++node_count;
			q = new link_Node();
			q->city = s;
			q->weight = in;
			p->next = q;
			q->next = NULL;
			p = q;
		}
	}
	int return_count()
	{
		return node_count;
	}
	link_Node* GetFront()
	{
		link_Node *t = head;
		link_Node *a = head->next;
		head = NULL;
		head = a;
		// --node_count;
		return t;
	}

	void Sort()
	{
		link_Node *i, *j;
		int temp; string temp_str;
		for (i = head->next; i != NULL; i = i->next)
		{
			for (j = i->next; j != NULL; j = j->next)
			{
				if (i->weight > j->weight)
				{
					temp = i->weight;
					temp_str = i->city;
					i->city = j->city;
					i->weight = j->weight;
					j->weight = temp;
					j->city = temp_str;
				}
			}
		}
	}
	void Traverse()
	{
		t = head;
		if (t == NULL)
			cerr << "Empty\n";
		while (t != NULL)
		{
			cout << t->city << "    " << t->weight << "   " << node_count << endl;
			t = t->next;

		}
		city_connected_count++;
		cout << city_connected_count << " ======= City  End ==========   \n\n";
	}
	~Linked_List() {}
};
class Graph {
private:

	Linked_List *obj;
	Linked_List *obj_2;
	int **adjMatrix;
	int *predecessor, *distance;
	bool *mark;                        //keep track of visited node
	int source;

public:
	Graph()
	{
		obj = new Linked_List[numOfVertices];
		obj_2 = new Linked_List[numOfVertices];
		predecessor = new int[numOfVertices];
		mark = new bool[numOfVertices];
		distance = new int[numOfVertices];
		adjMatrix = new int*[numOfVertices];
		for (int i = 0; i < numOfVertices; ++i)
			adjMatrix[i] = new int[numOfVertices + 1];
	}
	void initialize()
	{
		for (int i = 0; i < numOfVertices; i++)
		{
			mark[i] = false;
			predecessor[i] = -1;
			distance[i] = INFINITY;
		}
		distance[source] = 0;
	}

	void Create_Graph(string **&data_2)
	{
		for (int i = 0; i < numOfVertices; ++i)
			obj[i].CreateNode(data_2[i][0], INFINITY);
	}
	void add_graph(string ** &data_2)
	{
		for (int i = 0; i < numOfVertices; ++i)
		{
			for (int j = 1; j < numOfVertices + 1; ++j)
			{
				if (data_2[i][j] != "0")
				{
					obj[i].Insert(data_2[j - 1][0], atoi(data_2[i][j].c_str()));
				}
			}
		}
	}


	void read(string ** &data_2, int source_argument)
	{
		for (int i = 0; i < numOfVertices; ++i)
		{
			for (int j = 0; j < numOfVertices; j++)
				adjMatrix[i][j] = atoi(data_2[i][j + 1].c_str());
		}
		source = source_argument;
	}

	int getClosestUnmarkedNode() {
		int minDistance = INFINITY;
		int second_index = -1;
		int closestUnmarkedNode = 0;
		for (int i = 0; i < numOfVertices; i++)
		{
			if ((!mark[i]) && (minDistance >= distance[i]))
			{
				minDistance = distance[i];
				closestUnmarkedNode = i;
			}
		}
		return closestUnmarkedNode;
	}
	int getClosestUnmarkedNode_1() {
		int minDistance = INFINITY;
		int second_index = -1;
		int closestUnmarkedNode = 0;
		for (int i = 0; i < numOfVertices; i++)
		{
			if ((!mark[i]) && (minDistance >= distance[i]))
			{
				second_index = closestUnmarkedNode;
				minDistance = distance[i];
				closestUnmarkedNode = i;
			}
		}
		return second_index;
	}

	void calculateDistance()
	{
		initialize();
		int minDistance = INFINITY;
		int closestUnmarkedNode;
		int count = 0;
		while (count < numOfVertices)
		{
			closestUnmarkedNode = getClosestUnmarkedNode();
			mark[closestUnmarkedNode] = true;
			for (int i = 0; i < numOfVertices; i++)
			{
				if ((!mark[i]) && (adjMatrix[closestUnmarkedNode][i] > 0))
				{
					if (distance[i] > distance[closestUnmarkedNode] + adjMatrix[closestUnmarkedNode][i])
					{
						distance[i] = distance[closestUnmarkedNode] + adjMatrix[closestUnmarkedNode][i];
						predecessor[i] = closestUnmarkedNode;
					}
				}
			}
			count++;
		}
	}
	void calculateDistance_1()
	{
		initialize();
		int minDistance = INFINITY;
		int closestUnmarkedNode;
		int count = 0;
		int second_index;
		while (count < numOfVertices)
		{
			closestUnmarkedNode = getClosestUnmarkedNode();
			second_index = getClosestUnmarkedNode_1();
			mark[closestUnmarkedNode] = true;
			mark[second_index] = true;
			for (int i = 0; i < numOfVertices; i++)
			{
				if ((!mark[i]) && (adjMatrix[closestUnmarkedNode][i] > 0))
				{
					if (distance[i] > distance[closestUnmarkedNode] + adjMatrix[closestUnmarkedNode][i])
					{
						distance[i] = distance[closestUnmarkedNode] + adjMatrix[closestUnmarkedNode][i];
						predecessor[i] = closestUnmarkedNode;
					}
				}
			}
			count++;
		}
	}

	void printPath(string ** &data_2, int node)
	{
		if (node == source)
			cout << data_2[node][0] << "...";
		else if (predecessor[node] == -1)
			cout << "No path from " << data_2[source][0] << " to " << data_2[node][0] << endl;
		//1;
		else
		{
			printPath(data_2, predecessor[node]);
			most_visited_city[node]++;
			cout << data_2[node][0] << "...";
		}
	}
	void output(string ** &data_2)
	{
		for (int i = 0; i < numOfVertices; i++)
		{
			if (i == source)
				cout << data_2[source][0] << ".." << source;
			else
				printPath(data_2, i);
			cout << "->" << distance[i] << endl;
		}
	}


	void printPath_1(string ** &data_2, int node)
	{
		if (node == source)
			cout << data_2[node][0] << "..";
		else if (predecessor[node] == -1)
			cout << "No path from " << data_2[node][0] << " to " << data_2[source][0] << endl;
		else
		{
			cout << data_2[node][0] << "..to..";
			most_visited_city[node]++;
			printPath_1(data_2, predecessor[node]);
		}
	}

	void output_1(string ** &data_2)
	{
		for (int i = 0; i < numOfVertices; i++)
		{
			if (i == source)
				cout << data_2[source][0] << "..to.." << source;
			else
				printPath_1(data_2, i);
			cout << "->" << distance[i] << endl;
		}
	}
	void printPath_2(string **& data_2, int node)
	{
		if (node == source)
			cout << data_2[node][0] << "..";
		else if (predecessor[node] == -1)
			cout << "No path from " << data_2[node][0] << " to " << data_2[source][0] << endl;
		else
		{
			printPath_2(data_2, predecessor[node]);
			cout << data_2[node][0] << "..to..";
		}
	}
	void output_2(string ** &data_2, int single_destination)
	{
		for (int i = single_destination; i < single_destination + 1; i++)
		{
			if (i == source)
				cout << data_2[source][0] << "..to.." << source;
			else
				printPath_2(data_2, i);
			cout << "->" << distance[i] << endl;
		}
	}

};
void callMainFunction(Graph G,string directory) {
	
	string **data_2 = new string*[numOfVertices + 1];
	//Data array is storing the data readen from file
	for (int i = 0; i < numOfVertices + 1; ++i)
		data_2[i] = new string[numOfVertices + 1];
	for (int i = 0; i < numOfVertices; ++i)
		most_visited_city[i] = 0;


	ifstream ifile("GraphData.csv", ios::in);
	string line;
	for (int i = 0; i < numOfVertices + 1; ++i)
	{
		for (int j = 0; j < numOfVertices + 1; ++j)
		{
			if (j <= numOfVertices - 1)
			{
				getline(ifile, line, ',');
				data_2[i][j] = line;
			}
			else
			{
				getline(ifile, line, '\n');
				data_2[i][j] = line;
			}
		}
	}
	string** temp = new string*[numOfVertices];

	//allocating temp
	for (int i = 0, k = 0; k < numOfVertices; i++, k++)
	{
		temp[i] = new string[numOfVertices + 1];
		for (int j = 0; j < numOfVertices + 1; j++)
		{
			temp[k][j] = data_2[i + 1][j];
		}
	}
	//deallocating memnory
	for (int i = 0; i < numOfVertices; i++) {
		delete[]data_2[i];
	}
	delete[]data_2;
	data_2 = new string *[numOfVertices];

	//reallocating data_2
	for (int i = 0; i < numOfVertices; i++) {
		data_2[i] = new string[numOfVertices + 1];
		for (int j = 0; j < numOfVertices + 1; j++) {
			data_2[i][j] = temp[i][j];
		}
	}

	for (int i = 0; i < numOfVertices; i++) {
		delete[]temp[i];
	}
	delete[]temp;




	int user_choice = 0;
	G.Create_Graph(data_2);
	G.add_graph(data_2);
	while (true) {

	cout << "            ==================          Enter Your Choice     ========================== \n\n";
		cout << " 1. From One Source to all Destinations.\n";
		cout << " 2. From All Sources to One Destinations.\n";
		cout << " 3. From Single Source to Single Destination.\n";
		//cout << " 4. From Every Source to Every Destination.\n";
		cin >> user_choice;
		system("cls");
		if (user_choice == 1)
		{
			string source_argu;
			cout << "Enter the source City : ";
			cin >> source_argu;
			int indexx = return_index_string(data_2, source_argu);
			cout << "---------------";
			G.read(data_2, indexx);
			G.calculateDistance();
			G.output(data_2);
		}

		else if (user_choice == 2)
		{
			string source_argu;
			cout << "Enter the Destination City : ";
			cin >> source_argu;
			int indexx = return_index_string(data_2, source_argu);
			G.read(data_2, indexx);
			G.calculateDistance();
			G.output_1(data_2);
		}
		else if (user_choice == 3)
		{
			string source_argu;
			cout << "Enter the source City : ";
			cin >> source_argu;
			int indexx = return_index_string(data_2, source_argu);
			G.read(data_2, indexx);
			string single_destination_choice;
			cout << "Enter Destination : ";
			cin >> single_destination_choice;
			int destina_single = return_index_string(data_2, single_destination_choice);
			G.calculateDistance();
			G.output_2(data_2, destina_single);



			//THORUGH FLLOYD///



		//	cout << "Showing 2nd Shortest Path" << endl; 
		//	G.calculateDistance_1();
		//	G.output_2(data_2,destina_single);
		}
		/*else if (user_choice == 4)                       BONUS?????????
		{
			for (int i = 0; i < numOfVertices; ++i)
			{
				G.read(data_2,i);
				G.calculateDistance();
				G.output(data_2);
			}
		}*/
	}
}
int main() {
	Graph G;
	callMainFunction(G, "GraphData.csv");
	cout << endl << endl;
	system("pause");
	return 0;
}