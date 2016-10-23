#include<iostream>
#include<string>
#include<algorithm>
#include<fstream>
using namespace std;
bool flag = true;
string gene_name, x, y;
bool compare_two_letter(char a, char b)
{
	if(a == b)
		return true;
	else
		switch (a) {
			case 'R':
				if( b == 'G' || b == 'A')
					return true;
				else
					return false;
				break;
			case 'K':
				if( b == 'G' || b == 'T')
					return true;
				else
					return false;
				break;
			case 'S':
				if( b == 'G' || b == 'C')
					return true;
				else
					return false;
				break;
			case 'W':
				if( b == 'A' || b == 'T')
					return true;
				else
					return false;
				break;
			case 'M':
				if(b == 'A' || b == 'C')
					return true;
				else
					return false;
			    break;
			case 'Y':
				if(b == 'T' || b == 'C')
					return true;
				else
					return false;
				break;
			case 'D':
				if( b == 'C')
					return false;
				else
					return true;
				break;
			case 'V':
				if( b == 'T')
					return false;
				else
					return true;
				break;
			case 'B':
				if( b == 'A')
					return false;
				else
					return true;
				break;
			case 'H':
				if(b == 'G')
					return false;
				else 
					return true;
				break;
			case 'N':
				return true;
				break;
			default:
				return false;
				break;
	}
}
void brute_force(string &x, string &y)
{
	int i,j;
	int m = x.size();
	int n = y.size();
	for(j = 0; j <= n - m; ++j){
		for(i = 0; i < m && compare_two_letter(x[i], y[i+j]); ++i);
		if( i >= m )
			if(flag == true)//which means it is on frist list
                        {       for(int k = 1; k != gene_name.size(); k++)
                                   cout<< gene_name[k];
				cout<<"	"<<x<<"	"<<"+"<<"	"<<j + 1<<"	"<<j + m  <<endl;
                        }
			else
                        {       
                                for(int k = 1; k != gene_name.size(); k++)
                                     cout<< gene_name[k];
				cout<<"	"<<x<<"	"<<"-"<<"	"<<n - j <<"	"<<n - j - m + 1<<endl;
                        }
	}
}
string comp_reverse(string &word)
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

int main()
{
  int even = 0;
  ifstream out("At_G1078_cluster_up1200.fasta");
  while(getline(out, y)){
	  if(!(even % 2))
		  gene_name = y;
	  else
	  {
		  ifstream in("motif_temp2");
                 
		  while(getline(in, x))
		        brute_force(x, y);
                  y = comp_reverse(y);
                  flag = false;
                  ifstream second("motif_temp2");
                  while(getline(second,x))
                        brute_force(x,y);
                  flag = true;
    
	  }
       even++;
  }
  return 0;
}

	  
