#include<iostream>
#include<string>
#include<fstream>
#include<queue>
#include<vector>
using namespace std;
int count_line = 0;
bool flag = true;
int pos = 0;
string S2, S, gene_name;
//void compute_nv(node * );
vector<string> str_set;
vector<int> l_position;
class node{
public:
	int length  ;   // this is the length form the root to the current node, root node is equal 0;
	int sign    ;   // this is the char between the edge from the node to its parent 1:A, 2:T, 3:C, 4:G
	node * failure; // this pointer points to the transition function node
	node * parent;//points to its parent node
	node * edge[4];// the edge between the two nodes, actually, it points to the next nodes from a node
	string content ;// this is the string number from the set string
	bool terminal;  // to see if this is a leaf node
	int pid;// the id of a node;
	int l_number;// this is for wild search
	vector<int> position;

	node();

};
node::node(){
	content = "";
	pid = -1;
	for(int i = 0; i < 4; i++)
		edge[i] = NULL;
	sign = -1;
	failure =	NULL;
	length = 0;
	parent = NULL;
	terminal = false;
}
class keyword_tree{
public:
	node* root; // points to the root node;
	keyword_tree() ;
	int num_node;// the total number of nodes in tree
	void search(string word);// the function to search the word in the keyword tree
	void insert(string word);// the function to insert a string into the keyword tree
	void compute_failure_function(node * t);
	void compute_nv(node *);
	void printall(node *);
	void AC_search(string word);
	void delete_tree(node *); // after finishing the operation , free the memory by deleting the whole tree
};
keyword_tree::keyword_tree():root(NULL){ 
    num_node = 0;}

void keyword_tree::insert(string word) {
	if(root == NULL) {
		root = new node;
		root->parent = root;
		root->pid = 0;// the id of root is 0
	    root->length = 0 ;
		root->failure = root;// at first points to the root
		root->sign = -1; 
	       ++num_node;}
	 node* temp = root;
	 int i = 0;
	 while(i != word.size()){
		 switch(word[i]){
			 case 'A':
				 if(temp->edge[0] == NULL){
					 temp->edge[0] = new node;
					 temp->edge[0]->pid = num_node++;
					 temp->edge[0]->parent = temp;// new node points to its parent
					 temp->edge[0]->length = temp->length + 1; 
					 temp->edge[0]->sign = 0;} 

				 else{
					 temp = temp->edge[0];
					 i++;
				 }
                 break;
			 case 'T':
				 if(temp->edge[1] == NULL){
					 temp->edge[1] = new node;
					  temp->edge[1]->pid = num_node++;
					 temp->edge[1]->parent = temp;
				     temp->edge[1]->length = temp->length + 1;
				     temp->edge[1]->sign = 1;}
				 else{
					 temp = temp->edge[1];
					 i++;
				 }
				 break;
			 case 'C':
				 if(temp->edge[2] == NULL){
					 temp->edge[2] = new node;
					  temp->edge[2]->pid = num_node++;
					 temp->edge[2]->parent = temp;
				     temp->edge[2]->length = temp->length + 1;
				     temp->edge[2]->sign = 2;}
				 else{
					 temp = temp->edge[2];
					 i++;
				 }
				 break;
			 case 'G':
				 if(temp->edge[3] == NULL){
					 temp->edge[3] = new node;
					  temp->edge[3]->pid = num_node++;
					 temp->edge[3]->parent = temp;
				     temp->edge[3]->length = temp->length + 1;
					 temp->edge[3]->sign = 3;}
				 else{
					 temp = temp->edge[3];
					 i++;
				 }
			     break;
			 default:
				 cout<<"your motif format is incorrect, should just include ATCG only"<<endl;
				 i++;
				 break;
				 
		 }
		 
		 
			 
	 }
	 if(temp->content.empty())
	 {
			 temp->content = word;
/*******this lines is just for wild_match only********/
			 if(!l_position.empty())
			 {
			 temp->l_number = l_position[pos];
			 pos++;
			 }
	 }

}
void keyword_tree::delete_tree(node * tree){
	if(tree != NULL){
		for(int i = 0; i < 4; i++)
			if(tree->edge[i] != NULL)  delete_tree(tree->edge[i]);
		delete tree;
		tree = NULL;
	}
}

void keyword_tree::search(string word){
	node* temp = root;
	if(root == NULL)
		cout<<"the tree is empty, you can't search"<<endl;
	//else
		//cout<<" the tree is created"<<endl;
	int j = 0;
	//int i = 0;
	while(j != word.size()){
             int i = j;
	while(temp != NULL &&  i != word.size()){
		switch(word[i]){
			case 'A':
				temp = temp->edge[0];
				i++;
				break;
			case 'T':
				temp = temp->edge[1];
				i++;
				break;
			case 'C':
				temp = temp->edge[2];
				i++;
				break;
			case 'G':
				temp = temp->edge[3];
				i++;
			    break;
			default:
				break;
		}
		if(temp!= NULL && !temp->content.empty()){
			//cout<<temp->content<<":	"<<j<<"	";
			temp->position.push_back(j);
			++count_line;
		}
	}
	    temp = root;
	    ++j;
	//temp = temp->failure;
	//j = i - temp->failure->length;
	}
	//if(temp != NULL && !(temp->content.empty()) )
	//		cout<<"the search of"<<temp->content<<": is successfual"<<endl;

	}
void keyword_tree::compute_failure_function(node *t ){ 
	queue<node*> myqueue;
	if(t != NULL){
		myqueue.push(t);
		while(!(myqueue.empty())){
			node* temp = myqueue.front();
			//cout<<" "<<temp->length<<" ";
			myqueue.pop();
			compute_nv(temp);
			for(int i = 0; i < 4; i++)
				if(temp->edge[i] != NULL)
					myqueue.push(temp->edge[i]);
		}
	}
                                                
} // using breath first search algorithm to come true this function
void keyword_tree::printall(node *t){
	//cout<<"the motifs is:......................................."<<endl;
	queue<node*> myqueue;
	if(t != NULL){
		myqueue.push(t);
		while(!(myqueue.empty())){
			node* temp = myqueue.front();
			//cout<<""<<temp->failure->length<<" ";
			//cout<<"node "<<temp->pid<<"-- "<<temp->failure->length;
			// print all strings in the set
			if(flag ==true){
			if(!(temp->content.empty())&& !(temp->position.empty()) ){
				//cout<<temp->content<<"	";
				//cout<<"pos :"<<temp->l_number<<"	";
			for(int i = 0; i < temp->position.size(); i++)
			{
				 for(int j = 1; j != gene_name.size(); j++)
					cout<<gene_name[j];
				cout<<"	"<<temp->content<<"		+	";
				cout<<"	"<<temp->position[i] - temp->content.size() + 1 <<"	"<<temp->position[i] +1;
				cout<<endl; 
			}
			temp->position.clear();
			}  
			}
			else{
				if(!(temp->content.empty())&& !(temp->position.empty()) ){
				//cout<<temp->content<<"	";
				//cout<<"pos :"<<temp->l_number<<"	";
			for(int i = 0; i < temp->position.size(); i++)
			{
				 for(int j = 1; j != gene_name.size(); j++)
					cout<<gene_name[j];
				cout<<"	"<<temp->content<<"		-	";
				cout<<"	"<<S2.size() -temp->position[i] + temp->content.size() <<"	"<<S2.size() - temp->position[i] + 1;
				cout<<endl; 
			}
			temp->position.clear();
			}  
			}
                       
			myqueue.pop();
			//compute_nv(temp);
			for(int i = 0; i < 4; i++)
				if(temp->edge[i] != NULL)
					myqueue.push(temp->edge[i]);
		}
	}
	cout<<endl;
}

void keyword_tree::compute_nv(node * mynode){
	//node * temp = mynode;
	node * W;
	int x = mynode->sign;
	/*int i_edge = -1;
	switch(x){
			case 'A':
				i_edge = 0;
				break;
			case 'T':
				i_edge = 1;
				break;
			case 'C':
				i_edge = 2;
				break;
			case 'G':
				i_edge = 3;
			    break;
			default:
				break;
		}*/
	node * parent = mynode->parent;
	if(mynode->length <= 1)
		mynode->failure = root; // the root and first level nodes points to root
	else{
		W = parent->failure;
		while((W->edge[x] == NULL) && (W != root))
			W = W->failure;
		if(W->edge[x] != NULL)
			mynode->failure = W->edge[x];
		else
			mynode->failure = root;
	}
}

bool test_if_node_contain_edge(  node* const my_node, char fv){
	      node *temp = my_node ;
	if(my_node == NULL){
		cout<<" error"<<endl;
		return false;}
          switch(fv){
			case 'A':
				temp = temp->edge[0];
				break;
			case 'T':
				temp = temp->edge[1];
				//i++;
				break;
			case 'C':
				temp = temp->edge[2];
				//i++;
				break;
			case 'G':
				temp = temp->edge[3];
				//i++;
			    break;
			default:
				//cout<<"this is wrong"<<endl;
				return false;

				break;
		}
		  if(temp != NULL)
			  return true;
		  else 
		     return false;
}
 node* get_next( node * const my_node, char fv){
	 node * temp = my_node;
	switch(fv){
			case 'A':
				temp = temp->edge[0];
				break;
			case 'T':
				temp = temp->edge[1];
				//i++;
				break;
			case 'C':
				temp  = temp->edge[2];
				//i++;
				break;
			case 'G':
				temp = temp->edge[3];
				//i++;
			    break;
			default:
				cout<<"this is wrong"<<endl;
				break;
		}
	return temp;
}

 /*void get_link(node * my_node){
	 node* temp = my_node;
	 while(temp->failure != root){
		 if(!(temp->failure->content.empty()))*/


void keyword_tree::AC_search(string word){
	int l = 0;
	int  c = 0;
	node* temp2 = root;
	node* next;

	 //cout<<"this method starts"<<endl;
	
	while(c < word.size()){ 
		//cout<<"the word size is "<<word.size()<<endl;
		//cout<<"this is first while"<<endl;
		while(test_if_node_contain_edge(temp2, word[c]) && c < word.size() ){
			//cout<<"this is second wihle:"<<word[c]<<endl;
			next = get_next(temp2,word[c]);
			//if(!(get_next(temp2,word[c])->content.empty())){
			if(!next->content.empty()){
				//cout<<" the success"<<get_next(temp2,word[c])->content<<" "<<c<<" "<<endl;
				next->position.push_back(c);
				count_line++; 
				//next = get_next(temp2,word[c]) ;
				//while(next->failure != root){
				//	if(!(next->failure->content.empty())){
    //                 //cout<<" the success"<<get_next(temp2,word[c])->content<<" "<<c<<" "<<endl;
				//		count_line++;}
				//	next->failure = next->failure->failure;}
		/**************to theck if there exit a link************************/
				
			     }
			while(next->failure != root){
				if(!(next->failure->content.empty())){
                    //cout<<" the success"<<get_next(temp2,word[c])->content<<" "<<c<<" "<<endl;
						count_line++;}
				next = next->failure;}
				
			temp2 = get_next(temp2,word[c]) ;
			//if(!temp->content.empty())
				//cout<<" "<<temp->content<<" "<<c<<" "<<endl;
			//count_line++;
			c++;
			//cout<<"c is "<<c <<endl;
		
		}
		
		
	/*if(temp2 == NULL)
		cout<<"the pointer is empty"<<endl;*/
	//cout<<"the length<<"<<temp2->length<<endl;
	//cout<<"the current id node is"<<temp2->pid<<endl;
	temp2 = temp2->failure;
    //cout<<"the current id node is"<<temp2->pid<<endl;
	//if(temp2 == NULL)
	//	cout<<"this is wrong"<<endl;
	//cout<<"the length<<"<<temp2->length<<endl;
	//l = c - temp->failure->length;
	}
}

void transfer_to_many(string input_string)
{   
    string temp;
	for(int i = 0; i < input_string.size(); i++)
	{
		if(input_string[i] != '$')
		{
			temp.push_back(input_string[i]);
		}
		else
		{   
			if(!temp.empty())
			{
			str_set.push_back(temp);
			l_position.push_back(i - temp.size());
			temp.clear();
			}
		}
	}
	if(!temp.empty())
	{
		str_set.push_back(temp);
		int i = input_string.size() - temp.size();
		l_position.push_back(i);
		temp.clear();
	}
}

void Exact_with_wild_cards(string S1, string S2)
{
	int* arr = new int[S1.size()];
	for(int i = 0; i < S1.size(); i++)
		arr[i] = 0;
	transfer_to_many(S2);
	keyword_tree mytree;
	for(int i = 0; i < str_set.size(); i++)
		mytree.insert(str_set[i]);
	mytree.compute_failure_function(mytree.root);
	mytree.search(S1);
	
	//mytree.printall(mytree.root);
/*******these codes from the print_all***************************/
    node* t = mytree.root;
	queue<node*> myqueue;
	if(t != NULL)
	{
		myqueue.push(t);
		while(!(myqueue.empty()))
		{
			node* temp = myqueue.front();
			if(!(temp->content.empty())&& !(temp->position.empty()) )
			  for(int i = 0; i < temp->position.size(); i++)
				++arr[temp->position[i] - temp->l_number + 1];
			myqueue.pop();
			for(int i = 0; i < 4; i++)
				if(temp->edge[i] != NULL)
					myqueue.push(temp->edge[i]);
		}
	}
	for(int i = 0; i < S1.size() ; i++)
	{   //cout<<"the arr is:"<<arr[i]<<"	";
		if( arr[i] == str_set.size() )
			cout<<"the pisiton p is"<< i<<endl;
		}
	mytree.delete_tree(mytree.root);

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

	/*keyword_tree mytree;
	string S;
	S = "input.txt";
	ifstream in("input.txt");
	while(getline(in,S))
		mytree.insert(S);
	mytree.compute_failure_function(mytree.root);*/
	/*keyword_tree mytree;
	mytree.insert("ATCG");
	mytree.insert("ACCG");
	mytree.insert("TCCG");
	mytree.insert("TTGG");
	mytree.insert("GGCC");
	mytree.insert("CCG");
	mytree.compute_failure_function(mytree.root);
	mytree.AC_search("ATCGGGGGGGGACCG");
	mytree.AC_search("ATCGGGGGGGGACCG");
	mytree.printall(mytree.root);
	
	mytree.insert("TTGGCC");*/
	//mytree.AC_search("ATCGA");

	

	//mytree.printall(mytree.root);
	//string S8 = "CGCTTTCGTTACCTTAAATTTTGGCTTGTTATGAAGGCATGTCATAACGTTTCTAGTCACAACTCACAAGCATACCAACGACCATGATAAATCCAAAAAGTAGAAACAATCTATTATCTAAACCCCCAAAAGACAAAAGAAAAAAGTAGAAAGAAAAGGTAGGCAGAGATATAATGCTGGTTTTATTTGTTTGTTAAAAGATATTGCTATTTCTGCCAATATTAAAACTTCACTTAGGAAGACTTGAACCTACCACACGTTAGTGACTAATGAGAGCCACTAGATAATTGCATGCATCCCACACTAGTACTAATTTTCTAGGGATATTAGAGTTTTCTAATCACCTACTTCCTACTATGTGTATGTTATCTACTGGCGTGGATGCTTTTAAAGATGTTACGTTATTATTTTGTTCGGTTTGGAAAACGGCTCAATCGTTATGAGTTCGTAAGACACATACATTGTTCCATGATAAAATGCAACCCCACGAACCATTTGCGACAAGCAAAACAACATGGTCAAAATTAAAAGCTAACAATTAGCCAGCGATTCAAAAAGTCAACCTTCTAGATGGATTTAACAACATATCGATAGGATTCAAGATTAAAAATAAGCACACTCTTATTAATGTTAAAAAACGAATGAGATGAAAATATTTGGCGTGTTCACACACATAATCTAGAAGACAGATTCGAGTTGCTCTCCTTTGTTTTGCTTTGGGAGGGACCCATTATTACCGCCCAGCAGCTTCCCAGCCTTCCTTTATAAGGCTTAATTTATATTTATTTAAATTTTATATGTTCTTCTATTATAATACTAAAAGGGGAATACAAATTTCTACAGAGGATGATATTCAATCCACGGTTCACCCAAACCGATTTTATAAAATTTATTATTAAATCTTTTTTAATTGTTAAATTGGTTTAAATCTGAACTCTGTTTACTTACATTGATTAAAATTCTAAACCATCATAAGTAAAAAATAATATGATTAAGACTAATAAATCTTAATAGTTAATACTACTCGGTTTACTACATGAAATTTCATACCATCAATTGTTTTAATAATCTTTAAAATTGTTAGGACCGGTAAAACCATACCAATTAAACCGGAGATCCATATTAATTTAATTAAGAAAATAAAAATAAAAGGAATAAATTGTCTTATTTAAACGCTGACTTCACTGTCTTCCTCCCTCC";
    //mytree.AC_search(S8);
	//queue<int> myqueue;
	//myqueue.push(10);
	//myqueue.push(20);
	//cout<<"the first is "<<myqueue.front()<<endl;
	//myqueue.pop();
	//cout<<"the second is "<<myqueue.front()<<endl;
	//string s = "ATACG";
	//string s1 = "ATACGA";
	//mytree.insert("ATAC");
	//cout<<"0:is"<<s[0]<<endl;
	//cout<<"s's size is"<<s.size()<<endl;

	//mytree.insert(s);
	//mytree.insert(s1);
	//mytree.search(s2);

	/*string t2 = "ATAT$$CCGG$$CCTT$$TT";
	string t1 = "ATATCCCCGGCCCCTTCCTTATATATCCGGCCCCTTGGTTATTTTTTTTTATTTCCGGGGCCTTGGTTATATATCCGGCCCCTTGGTTATATATCCGGCCCCTTGGTTAAATATCCGGAACCTTCCTTAAATAACCGGAACCTTCCTTTTTTTTTAAATAACCGGAACCTTCCTT";
	Exact_with_wild_cards(t1,t2);*/

	//transfer_to_many(temp);
	/*cout<<"the number of strings are:"<<str_set.size() <<endl;
	for(int i = 0; i < str_set.size(); i++)
		cout<<"string:"<<str_set[i]<<endl;
	for(int i = 0; i < l_position.size(); i++)
		cout<<"position:"<<l_position[i]<<endl;*/



	
	

	//string S2;

	//ifstream out("output");
	int even = 0;
	string temp;
	ifstream out("At_G1078_cluster_up1200.fasta");
	while(getline(out, S2)){
		if(!(even % 2))
			gene_name = S2;
			//cout<<"the gene of "<<S2<<":"<<endl;
		else{
		keyword_tree mytree1;
		mytree1.insert("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
		mytree1.insert("TAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
		mytree1.insert("CAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
		mytree1.insert("GAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
	//string S;
	//S = "input.txt";
	ifstream in("input.txt");
	while(getline(in,S))
		mytree1.insert(S);
	mytree1.compute_failure_function(mytree1.root);
    mytree1.AC_search(S2);
	mytree1.printall(mytree1.root);
	flag = false;
	temp = comp_reverse(S2);
	mytree1.AC_search(temp);
	mytree1.printall(mytree1.root);
	flag = true;
	mytree1.delete_tree( mytree1.root );}
		++even;

	}

	/*mytree.search("ATAC");
	mytree.insert("ATAT");
	mytree.insert("ATATC");*/
	
	//mytree.printall(mytree.root);
	cout<<" the total line is "<<count_line<<endl;
	//cout<<"th total noeds in tree is:"<<mytree.num_node<<endl;
	//mytree.delete_tree( mytree.root );
	return 0;
}
