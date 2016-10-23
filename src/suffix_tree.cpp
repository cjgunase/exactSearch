#include<iostream>
#include<string>
#include<queue>
#include<vector>
#include<algorithm>
#include<fstream>
const int  Max_nodes = 10;
using namespace std;
bool flag = true;
string name_gene;
string str;
string input_txt;// the input text

class node{
public:
	node* parent;
	node* child[Max_nodes];
	short int pid;       // the number of nodes in the children group
	short int num_child;// the current number of nodes of children
	//int path_position;//the index of start position
	short int edge_start_index;//the incoming edge's start index position
	short int edge_end_index;// the incoming edge's end index posion
	bool leaf;// to see if this node is leaf or not
	short int pos;
	node();
};

class Suffix_tree{
public:
	int node_total;
	node *root;// points to the root of the tree
    bool Insert(int index_start);
	bool Search(string &word);
	//string input_txt;// the input text
	node * Find_son(node* current, char character);
	void print_all(node *curr_node);
	void delete_tree(node *curr_node);
	vector<int> mypos;
	Suffix_tree();
};

node::node(){
	for(int i = 0; i < Max_nodes; i++)
		child[i] = NULL;
    leaf = false;// when creat a node, it applies to non-leaf by default
	num_child = 0;// number of children is set to 0
	pos = -1;// set to -1
}
	
class Edge{
public:
	int first_char_index;
	int last_char_index;
	int start_node;
	int end_node;
};

Suffix_tree::Suffix_tree():root(NULL){
     node_total = 0;      
}

node * Suffix_tree::Find_son(node *current, char character)
{
	//node *temp = current;
	for(int i = 0; i < current->num_child; i++){
		if(input_txt[current->child[i]->edge_start_index] == character)
			return current->child[i];}
	return NULL;
}

bool Suffix_tree::Insert(int index_start)
{
	//cout<<"i is"<<index_start<<endl;
	int start,end,j = index_start;
	int END = input_txt.size() - 1;
	if(root == NULL)
	{
		root = new node;
		node_total++;
	//	cout<<"this time"<<node_total<<endl;
		root->parent = root;
		root->leaf= false;
		//root->num_child = 0;
	}

	node* temp = Find_son(root, input_txt[j]);
	node* current = new node;
	if(temp == NULL){
		root->child[root->num_child] = new node;
		node_total++;
		root->child[root->num_child]->parent = root;
		root->child[root->num_child]->pid = root->num_child;
//		root->num_child++;// the number nodes add 1 when a child node be added
		//root->child[root->num_child]->num_child = 0;
		root->child[root->num_child]->edge_start_index = index_start;
		root->child[root->num_child]->edge_end_index = END;
		root->child[root->num_child]->leaf = true;
		root->child[root->num_child]->pos  = index_start;
		root->num_child++;
		return true;
	    }
	else
		while(temp != NULL){
			start = temp->edge_start_index;
			end   = temp->edge_end_index;
			while( start <= end && input_txt[j] == input_txt[start])
			{
				start++;
				j++;
				//cout<<"start:"<<start<<"	end:"<<end<<"	j:"<<j<<endl;
			}
			if(start > end){
				current = temp;//make a copy before temp assigns to its child
				temp = Find_son(temp, input_txt[j]);}

			else if(input_txt[j] != input_txt[start]){
				node * add_node = new node;
				node_total++;
				add_node->edge_start_index = temp->edge_start_index;
				add_node->edge_end_index   = start - 1;
				add_node->parent = temp->parent;
				add_node->pid    = temp->pid;
				temp->parent->child[temp->pid] = add_node;
				add_node->child[add_node->num_child] = temp;
				add_node->child[add_node->num_child]->pid = add_node->num_child;
				add_node->num_child++;
				temp->edge_start_index = start;
				temp->parent = add_node;
				node* another_node = new node;//this node should be a leaf node 
				node_total++;
				another_node->leaf = true;
				another_node->pos = index_start;// add the starting position of the suffix
				another_node->edge_start_index = j;
				another_node->edge_end_index = END;
				another_node->parent = add_node;
				add_node->child[add_node->num_child] = another_node;
				add_node->child[add_node->num_child]->pid = add_node->num_child;
				add_node->num_child++;
				return true;
			}
		}
		if(temp == NULL){
			node *node_third = new node;
			node_total++;
			node_third->leaf = true;
			node_third->pos   = index_start;
			//root->child[root->num_child]->pos  = index_start;//add the starting positon of the suffix
			node_third->edge_start_index = j;
			node_third->edge_end_index   = END;
			node_third->parent = current;
			current->child[current->num_child] = node_third;
			current->child[current->num_child]->pid = current->num_child;
			current->num_child++;
		}
		return true;
}

bool Suffix_tree::Search(string &word)
{
	int i = 0 , start, end;
    node *temp = Find_son(root,word[i]);
	while((temp != NULL) && ( i < word.size() ))
	{
       //temp = Find_son(temp, word[i]);
	   start = temp->edge_start_index;
	   end   = temp->edge_end_index;
	   while(i < word.size() && start <= end && word[i] == input_txt[start] )
	   {
		   start++;
		   i++;
	   }
       
	 
	   if( i == word.size()) // search successfully
	   {
		  // cout<<"search is successful"<<endl;// print all the nodes in substree of temp(including the temp node)
		   print_all(temp);
		   sort(mypos.begin(),mypos.end());
		   //cout<<name_gene<<"	"<<str<<"	";
		   
		   
		   if(flag)
		   for(int i = 0; i != mypos.size(); i++)
		   {
			   for(int j = 1; j != name_gene.size(); j++)
				   cout<<name_gene[j];
			   cout<<"	"<<str<<"	+	";
			   cout<<"	"<<mypos[i]<<"	"<<mypos[i] + str.size() - 1;
		       cout<<endl;
		   }
		   else
			   for(int i = 0; i != mypos.size(); i++)
		   {
			   for(int j = 1; j != name_gene.size(); j++)
				   cout<<name_gene[j];
			   cout<<"	"<<str<<"	-	";
			   cout<<"	"<<mypos[i] + str.size() - 1<<"	"<<mypos[i];
		       cout<<endl;
		   }
		   
		   

		   mypos.clear();
		   return true;
		   }
	   //cout<<"i:"<<i<<"	"<<"start"<<start<<"end:"<<end<<endl;
	   if(  (word[i] != input_txt[start]) && (start <= end) )
	   {   
		   //cout<<"failure"<<endl;
		   return false; // failure search for string word
	   }

	   if(start > end)
	   {
		   
		   temp = Find_son(temp, word[i]);
	   }

	        
	}

}

void Suffix_tree::print_all(node *curr_node)
{
	queue<node*> myqueue;
	if( curr_node != NULL)
	{
		myqueue.push(curr_node);
		while(!myqueue.empty())
		{
			node *temp = myqueue.front();
			if(temp->leaf)
			{
				mypos.push_back(temp->pos);
				//cout<<temp->pos<<"	";
			}
			myqueue.pop();
			for(int i = 0; i < Max_nodes; i++)
			   if(temp->child[i] != NULL)
				   myqueue.push(temp->child[i]);
		}
	}
}

void Suffix_tree::delete_tree(node *curr_node)
{
	if(curr_node != NULL)
	{
		for(int i = 0; i < Max_nodes; i++)
			if(curr_node->child[i] != NULL)
				delete_tree(curr_node->child[i]);
		delete curr_node;
		curr_node = NULL;
	}
}

string LCS(const string& S1, const string& S2)
{
	string S4 ="";
	if( S1.empty() || S2.empty())
	{
		return S4;
	}
	int *curr = new int[S2.size()];
	int *prev = new int[S2.size()];
	int *swap = NULL;
	int maxStre = 0;
	int pos;
	for(int i = 0; i < S1.size(); i++)
	{
		for(int j = 0; j < S2.size(); j++)
		{
			if(S1[i] != S2[j])
			{
				curr[j] = 0;
			}
			else
			{
				if(i == 0 || j == 0)
				{
					curr[j] = 1;
				}
				else
				{
					curr[j] = prev[j - 1] + 1;
				}
                if(maxStre < curr[j])
				{
					maxStre = curr[j];
					pos = j;
				}
			}
		}
		swap = curr;
		curr = prev;
		prev = swap;
	}
	//cout<<"the maxStre is:"<<maxStre<<endl;
	char *S3 = new char[maxStre + 1];
	for(int j = 0,i = pos - maxStre + 1; i <= pos; i++)
	{  
		S3[j] = S2[i];
		++j;
	}
	S3[maxStre] = '\0';// add the end sign 
	//cout<<"the string is"<<S3<<endl;
	 S4 = string(S3);
	//cout<<"the s4 is:"<<S4<<"size"<<S4.size()<<endl;
		
	//cout<<"the positon is"<<pos<<"in the string 2"<<endl;
delete [] curr;
delete [] prev;
return S4;
}
string comp_reverse(string word)
{
	//string temp;
	//reverse(word.begin(),word.end());
	for(int i = 0; i != word.size(); i++)
	{
		switch(word[i]){
			case 'A':
				word[i] = 'T';
				break;
			case 'T':
				word[i] = 'A';
				break;
			case 'C':
				word[i] = 'G';
				break;
			case 'G':
				word[i] = 'C';
				break;
			default:
				break;
		}
	}
	reverse(word.begin(), word.end());
	return word;
}


int main(){
	/*input_txt = "CGCTTTCGTTACCTTAAATTTTGGCTTGTTATGAAGGCATGTCATAACGTTTCTAGTCACAACTCACAAGCATACCAACGACCATGATAAATCCAAAAAGTAGAAACAATCTATTATCTAAACCCCCAAAAGACAAAAGAAAAAAGTAGAAAGAAAAGGTAGGCAGAGATATAATGCTGGTTTTATTTGTTTGTTAAAAGATATTGCTATTTCTGCCAATATTAAAACTTCACTTAGGAAGACTTGAACCTACCACACGTTAGTGACTAATGAGAGCCACTAGATAATTGCATGCATCCCACACTAGTACTAATTTTCTAGGGATATTAGAGTTTTCTAATCACCTACTTCCTACTATGTGTATGTTATCTACTGGCGTGGATGCTTTTAAAGATGTTACGTTATTATTTTGTTCGGTTTGGAAAACGGCTCAATCGTTATGAGTTCGTAAGACACATACATTGTTCCATGATAAAATGCAACCCCACGAACCATTTGCGACAAGCAAAACAACATGGTCAAAATTAAAAGCTAACAATTAGCCAGCGATTCAAAAAGTCAACCTTCTAGATGGATTTAACAACATATCGATAGGATTCAAGATTAAAAATAAGCACACTCTTATTAATGTTAAAAAACGAATGAGATGAAAATATTTGGCGTGTTCACACACATAATCTAGAAGACAGATTCGAGTTGCTCTCCTTTGTTTTGCTTTGGGAGGGACCCATTATTACCGCCCAGCAGCTTCCCAGCCTTCCTTTATAAGGCTTAATTTATATTTATTTAAATTTTATATGTTCTTCTATTATAATACTAAAAGGGGAATACAAATTTCTACAGAGGATGATATTCAATCCACGGTTCACCCAAACCGATTTTATAAAATTTATTATTAAATCTTTTTTAATTGTTAAATTGGTTTAAATCTGAACTCTGTTTACTTACATTGATTAAAATTCTAAACCATCATAAGTAAAAAATAATATGATTAAGACTAATAAATCTTAATAGTTAATACTACTCGGTTTACTACATGAAATTTCATACCATCAATTGTTTTAATAATCTTTAAAATTGTTAGGACCGGTAAAACCATACCAATTAAACCGGAGATCCATATTAATTTAATTAAGAAAATAAAAATAAAAGGAATAAATTGTCTTATTTAAACGCTGACTTCACTGTCTTCCTCCCTCC$";
	Suffix_tree mytree;
	cout<<"the size of tree is "<<input_txt.size()<<endl;
	for(int i = 0; i < input_txt.size()  ; i++)
	mytree.Insert(i);
	cout<<"the root"<<mytree.root->num_child<<endl;
	
	cout<<"the total number of nodes in tree is"<<mytree.node_total<<endl;*/


	//input_txt = "abcdabcdabcdabcdefghijabcdkabcdabcdabcdabcdefghijabcdkabcdabcdabcdabcdefghijabcdk";
	/*input_txt = "CGCTTTCGTTACCTTAAATTTTGGCTTGTTATGAAGGCATGTCATAACGTTTCTAGTCACAACTCACAAGCATACCAACGACCATGATAAATCCAAAAAGTAGAAACAATCTATTATCTAAACCCCCAAAAGACAAAAGAAAAAAGTAGAAAGAAAAGGTAGGCAGAGATATAATGCTGGTTTTATTTGTTTGTTAAAAGATATTGCTATTTCTGCCAATATTAAAACTTCACTTAGGAAGACTTGAACCTACCACACGTTAGTGACTAATGAGAGCCACTAGATAATTGCATGCATCCCACACTAGTACTAATTTTCTAGGGATATTAGAGTTTTCTAATCACCTACTTCCTACTATGTGTATGTTATCTACTGGCGTGGATGCTTTTAAAGATGTTACGTTATTATTTTGTTCGGTTTGGAAAACGGCTCAATCGTTATGAGTTCGTAAGACACATACATTGTTCCATGATAAAATGCAACCCCACGAACCATTTGCGACAAGCAAAACAACATGGTCAAAATTAAAAGCTAACAATTAGCCAGCGATTCAAAAAGTCAACCTTCTAGATGGATTTAACAACATATCGATAGGATTCAAGATTAAAAATAAGCACACTCTTATTAATGTTAAAAAACGAATGAGATGAAAATATTTGGCGTGTTCACACACATAATCTAGAAGACAGATTCGAGTTGCTCTCCTTTGTTTTGCTTTGGGAGGGACCCATTATTACCGCCCAGCAGCTTCCCAGCCTTCCTTTATAAGGCTTAATTTATATTTATTTAAATTTTATATGTTCTTCTATTATAATACTAAAAGGGGAATACAAATTTCTACAGAGGATGATATTCAATCCACGGTTCACCCAAACCGATTTTATAAAATTTATTATTAAATCTTTTTTAATTGTTAAATTGGTTTAAATCTGAACTCTGTTTACTTACATTGATTAAAATTCTAAACCATCATAAGTAAAAAATAATATGATTAAGACTAATAAATCTTAATAGTTAATACTACTCGGTTTACTACATGAAATTTCATACCATCAATTGTTTTAATAATCTTTAAAATTGTTAGGACCGGTAAAACCATACCAATTAAACCGGAGATCCATATTAATTTAATTAAGAAAATAAAAATAAAAGGAATAAATTGTCTTATTTAAACGCTGACTTCACTGTCTTCCTCCCTCC$";
	string str ="AACAATCTATTATCTAAACCCCCAAAAGACAAAAGAAAAAAGTAGAAAGAAAAGGTAGGCAGA";
	Suffix_tree mytree;
	for(int i = 0; i < input_txt.size()  ; i++)
	mytree.Insert(i);
	mytree.Search(str);
	mytree.delete_tree(mytree.root);*/

	//Suffix_tree mytree;
	//string str ;
	/*string temp = "12345678";
	reverse(temp.begin(),temp.end());
	cout<<temp<<endl;*/
	//string temp = "ATCGATCGATCG";
	//string temp;
     //temp =comp_reverse(temp);

	//cout<<temp<<endl;
	//reverse(temp.begin(),temp.end());
	//cout<<"after reverse:"<<temp;
	int even = 0;
   
/****************to read from the file********************************************/
	ifstream out("sequence_temp");
	while(getline(out,input_txt))
	{   
		if(!(even % 2))
		{
			name_gene = input_txt;
			//cout<<"gene name:"<<name_gene<<endl;
		}
		else
		{

		Suffix_tree mytree;
		for(int i = 0; i < input_txt.size(); i++)
			mytree.Insert(i);
		ifstream in("motif_temp1");
		//bool flag = true;
		string temp;
		while(getline(in,str))
		   {
			mytree.Search(str);
			flag = false;
			temp = comp_reverse(str);
			mytree.Search(temp);
			flag = true;


		   }
		//mytree.Search(str);
		mytree.delete_tree(mytree.root);
		input_txt.clear();
		}
		even++;
	}

	/*string S1,S2;
	S1 = "1bcdefghijkbcdefghijkbcdefghijkbcdefghijk";
	S2 = "AAAAAAAAAabcdefghijkbcdefghijkbcdefghijkbcdefghijkbcdefghijk";
	string lcs;
	lcs = LCS(S1,S2);
	cout<<"the longest common sub string is:"<<lcs<<endl;*/
	/*cout<<"the size of Edge class:"<<sizeof(Edge)<<endl;
	cout<<"the size of node class:"<<sizeof(node)<<endl;
	cout<<"the size of suffix_tree class:"<<sizeof(Suffix_tree)<<endl;
	cout<<"the size of int:"<<sizeof(int)<<endl;
	cout<<"the size of node*"<<sizeof(node *)<<endl;*/
	return 0;
}
