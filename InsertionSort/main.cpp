#include <cstdlib>
#include <iostream>
#include <fstream>
#include <ctype.h>
#include <sstream>
#include <map>
#include <vector>
#include "stdio.h"
#include <algorithm>
#include <time.h>


using namespace std;

void insertion(vector<string> &, map<string,int> &);
void bubblesort(vector<string> &, map<string,int> &);
void quicksort(vector<string> &, map<string,int> &, int, int);
int partition(vector<string> &, map<string,int> &, int, int);
void heapsort(vector<string> &, map<string,int> &, int);
void adjust(vector<string> &, map<string,int> &, int, int);
void merge(vector<string> &, map<string,int> &, int, int, int);
void mergesort(vector<string> &, map<string,int> &, int p, int r);

string makeposition(int &, int &);



int main(int argc, char *argv[])
{
	string str1,str2,pos;
	int row=0,col=0;
	//for(int i=0;i<argc;i++)
	   // cout<<argv[i]<<endl;

	ifstream fin(argv[1]);
	ofstream fout(argv[2]);
	map<string,int> wordctr;
	map<string,string> index_record;
	vector<string> wordvector;

	while(getline(fin,str1))
	{
		row = row+1;
		col = 0;
		str2="";
		for(int i=0;i<str1.length();i++)
		{
            if(isalpha(str1[i])||str1[i]==' ')
            str2+=str1[i];
		}

		istringstream iss(str2);
		string word;

		while(iss>>word)
		{
			col = col+1;
			pos = makeposition(row,col); // 用row和col做出他的position
			wordctr[word]+=1;
			index_record[word]+=pos+" ";
		}


	}

	    map<string,int>::iterator it;
		for(it=wordctr.begin(); it!=wordctr.end(); it++)
		{
			wordvector.push_back((*it).first); // 產生一個vector來做排序
		}

		    double begin_t = clock();
			insertion(wordvector,wordctr); //insertion sort
			double end_t = clock();
			double runtime = (end_t-begin_t)/(double)CLOCKS_PER_SEC;
			
	     	cout<<"The runtime of "<<argv[1]<<"is: "<<runtime<<" second"<<endl;
			bubblesort(wordvector,wordctr);
			int length = wordvector.size();
			quicksort(wordvector,wordctr,0,length-1);
			heapsort(wordvector, wordctr, length);
			mergesort(wordvector, wordctr, 0, length-1);


		vector<string>::iterator it2;
		for(it2=wordvector.begin(); it2!=wordvector.end(); it2++)
		{
			fout<<(*it2)<< " "<< wordctr[(*it2)]<<" "<<index_record[(*it2)]<<endl;
		}

	return 0;
}




string makeposition(int &r, int &c)
{
	string s1,s2;
    stringstream ss1(s1),ss2(s2);
    ss1 << r;
	ss2 << c;

    return ss1.str()+"_"+ss2.str();
}

void insertion(vector<string> &a,map<string,int> &mapping)
{
	int key, j, length=a.size();
	string strkey;

	for(int i=1;i<length;i++)
	{
		key = mapping[a[i]];
		strkey = a[i];

		j = i-1;
		while(j>=0&&(mapping[a[j]]>key))
		{
			a[j+1] = a[j];
			j=j-1;
		}
		a[j+1] = strkey;

	}
}


void bubblesort(vector<string> &a,map<string,int> &mapping)
{
	int length = a.size();
	for(int i=length;i>1;i--)
	{
		for(int j=0;j<i-1;j++)
		{
			if(mapping[a[j]]>mapping[a[j+1]])
			swap(a[j],a[j+1]);
		}
	}
}



int partition(vector<string> &a, map<string,int> &mapping, int left, int right)
{
	int i,j, pivot = mapping[a[left]];
	i = left-1;
	j = right+1;

	while(true)
	{
		do
		{
            i++;
		}while(mapping[a[i]]<pivot);
		do
		{
			j--;
		}while(mapping[a[j]]>pivot);

		if(i<j)
		swap(a[i],a[j]);
		else
		return j;
	}
}


void quicksort(vector<string> &a, map<string,int> &mapping, int left, int right)
{
    int mid;

	if(left<right)
	{
		mid = partition(a, mapping,left,right);

		quicksort(a, mapping, left, mid);
		quicksort(a, mapping, mid+1, right);
	}
}


void merge(vector<string> &a, map<string,int> &mapping, int p, int q, int r)
{
	int n1, n2, i, j;
	string infinte = "0";
	//n1 = q-p+1;
	//n2 = r-q;
	vector<string> L(a.begin()+p,a.begin()+q+1), R(a.begin()+q+1,a.begin()+r+1);
	mapping[infinte] = 214746;

	/*for(int i=0;i<n1;i++)
	L.push_back(a[p+i]);*/
    L.push_back(infinte);

	/*for(int j=0;j<n2;j++)
	R.push_back(a[q+j+1]);*/
	R.push_back(infinte);

	i=0;
	j=0;

	for(int k=p;k<r+1;k++)
	{
		if(mapping[L[i]]<=mapping[R[j]])
		{
			a[k] = L[i];
			i++;
		}
		else
		{
		a[k] = R[j];
		j++;
	    }
	}

}


void mergesort(vector<string> &a, map<string,int> &mapping, int p, int r)
{
	int q;
	if(p<r)
	{
	q=(p+r)/2;
	mergesort(a, mapping, p, q);
	mergesort(a, mapping, q+1, r);
	merge(a,mapping, p, q, r);
	}
}


void adjust(vector<string> &a, map<string,int> &mapping, int root, int n)
{
	int child, rootkey;
	string temp = a[root];
	rootkey = mapping[a[root]];
	child =2*root;
	while(child<=n-1)
	{
		if((child<n-1)&&(mapping[a[child]]<mapping[a[child+1]]))
		child++;

		if(rootkey>mapping[a[child]])
		break;
		else
		{
			a[child/2] = a[child];
			child*=2;
		}
	}
	a[child/2] = temp;
}


void heapsort(vector<string> &a, map<string,int> &mapping, int n)
{
	int i,j;

	for(i=n/2;i>0;i--)
	adjust(a, mapping, i, n);

	for(i=n-2;i>=0;i--)
	{
	swap(a[1], a[i+1]);
	adjust(a, mapping, 1, i);

}

}

