#include <bits/stdc++.h>
#include <time.h>
#define pb push_back
 
using namespace std;


map<string,string> my_map;

int globalnodeNumber=0;
int globalownernumber=0;
 
string getutctime()
{
	time_t now = time(0);
	tm *gmtm = gmtime(&now);
	string dt = asctime(gmtm);
	
	return dt;
} 

string getnodeId(int nodeNumber)
{
	string s="";
	
	//as utc time will always be different we will always have different Id's 
	s=s+getutctime()+to_string(nodeNumber);
	
	return s;
}
 
 
string getownerid()
{
	string s="";
	
	//as utc time will always be different we will always have different Id's 
	s=s+getutctime()+to_string(globalownernumber);
	globalnodeNumber++;
	
	return s;
	
} 

string hash(string s)
{
	long long hashint=0;
	
	for(int i=0;i<s.len();i++)
	{
		hashint+=(int)s[i];
	}
	
	hashint%=10;
	
	return to_string(hashint);
}

class Node
{
	
	// decide accessibility
	public:
	
		string timestamp;
		string data;
		int nodeNumber;
		string nodeId;
		string referenceNodeId;
		vector<string> childReferenceNodeId;
		string genesisReferenceNodeId;
		string Hash;
		
		
		//create constructor
		Node()
		{
			timestamp=getutctime();
			//data
			nodeNumber=globalnodeNumber++;
			nodeId=getnodeId(nodeNumber);
			//referenceNodeId=
			childReferenceNodeId.clear();
			childReferenceNodeId.resize(0);
			//genesisReferenceNodeId
			//Hash
		}
	
	
	
	
};


string encrypt(string s, string key)
{
	int key=0;
	
	for(int i=0;i<key.length();i++)
	{
		key+=(int)key[i];
	}
	
	key%=10;
	
	char keychar= (char)key;
	
	//encrypt the data using XOR
	for(int i=0;i<s.length();i++)
	{
		s[i]= s[i] ^ keychar;
	}
	
	return s;
}


string decrypt(string s, string key)
{
	int key=0;
	
	for(int i=0;i<key.len();i++)
	{
		key+=(int)key[i];
	}
	
	key%=10;
	
	char keychar= (char)key;
	
	//decrypt the data using XOR
	for(int i=0;i<s.len();i++)
	{
		s[i]= s[i] ^ keychar;
	}
	
	return s;
}

void addchild(Node *node, Node *par)
{
	par->childReferenceNodeId.pb(to_string(node));
}


void filldata(Node *node)
{
	cout<<"give us your name\n";
	string ownername;
	cin>>ownername;
	
	cout<<"give us your value\n";
	int value;
	cin>>value;
	
	cout<<"give us your encryption key as a sequence of integers and/or characters\n";
	string key;
	cin>>key;
	
	string ownerid=getownerid();
	cout<<"your owner id is "<<ownerid<<"\n";
	
	
	//first hash the original data and create a hash string
	string hashstring=hash(ownerid+value+ownername);
	
	node->data=encrypt(ownerid+value+ownername+hashstring,key);
	
}


string gethashvalue(Node *node)
{
	string s=node->timestamp + node->data + to_string(node->nodeNumber) + node->nodeId + node->referenceNodeId + node->genesisReferenceNodeId;
	for(auto it: node->childReferenceNodeId)
	{
		s= s+ it;
	}
	
	return hash(s);
}

void fillnode(Node *node, Node *par)
{
	node->referenceNodeId=to_string(par);
	
	//add as a children to parent node
	addchild(node,par);
	
	node->genesisReferenceNodeId=par->genesisReferenceNodeId;
	
	
	//fill data
	filldata(node);
	
	//address in string
	stringstream ss;
	ss << node;
	string address=ss.str();
	
	my_map.insert( pair<string,string>(nodeId,address);
	
}


void creategenesisnode()
{
	Node node;
	Node *nodepointer=&node;
	
	string nulls="":
	nulls=nulls+'\0';
	
	nodepointer->referenceNodeId=nulls;
	nodepointer->genesisReferenceNodeId=nodepointer; //it's own address is the genesis address
	
	
	filldata(nodepointer);
	
	nodepointer->Hash=gethashvalue(nodepointer);
	
}


void createchildnodes()
{
	cout<<"give us the nodeid of which you want this node to be a child\n";
}



int main()
{
	
	cout<<"Choose your task number, your first task has to be the task 1.\n";
	cout<<"1. create genessis node\n";
	
	// add more tasks
	
	
	int taskno;
	//cin>>taskno;
	
	
	creategenesisnode();
	createchildnodes();
	task4();
return 0;	
	
}