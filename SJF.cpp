#include<iostream>
#define size 20
using namespace std;
struct time
{
	int bt;
	int at;	
	int at_temp;
	int wt;
};
int p[size];
int min_at_ind(struct time t[size],int n)
{
	int min,t_ind;
	min = 10000;
	t_ind=0;
	for(int i=0;i<n;i++)
	{
		if(min > t[i].at && t[i].at >=0 && min >=0)
		{
			min = t[i].at;
			t_ind = i;
		}
	}
	t[t_ind].at = -1;
	return t_ind;
}
int pa(int ct,struct time t[size],int n)
{
	int j=0,f=0;
	for(int i=0;i<n;i++)
	{
		if(t[i].at <= ct && t[i].at >=0)
		{
			p[j] = i;
			j++;
			f = 1;
		}
	}
	if(f==0)
	{
		return -1;
	}
	else
	{
		return j;
	}
}
int sum(int t_bt[size],int n)
{
	int sum = 0;
	for(int i=0;i<n;i++)
	{
		sum = sum + t_bt[i];
	}
	//cout << "sum" << sum ;
	return sum;
}
int sjf(struct time t[size],int t_bt[size],int n)
{
	int ct=0,min_ind,temp,min,z,q=0;
	min_ind = min_at_ind(t,n);
	t[min_ind].wt = t[min_ind].at_temp;
	ct = ct+t[min_ind].bt;
//	cout << ct << endl;
	t[min_ind].bt = -1;
	
	while(ct < sum(t_bt,n))
	{
	
		temp = pa(ct,t,n);
		if(temp != -1)
		{
			min = 10000;
			for(int i=0;i<temp;i++)
			{
				if(min > t[p[i]].bt && t[p[i]].bt >=0 && min >= 0)
				{
					min = t[p[i]].bt;
					z = p[i];
				}
			}
			t[z].wt = ct;
			ct = ct+min;
			t[z].bt = -1;
			t[z].at = -1;
		}
		else
		{
			min_ind = min_at_ind(t,n);
			t[min_ind].wt = t[min_ind].at_temp;
			q = t[min_ind].at_temp-ct;
			ct = ct+t[min_ind].bt+q;
			t[min_ind].bt = -1;
			//if(ct > sum(t_bt,n))
			//{
			//	break;
			//}
		}
	//	cout << ct <<endl;
	}
}
int main()
{
	int n,i,t_bt[size];
	float sum =0;
	struct time t[size];
	cout << "Enter no. of processes" <<endl;
	cin >> n;
	cout << "Enter burst time and arrival time" <<endl;
	for(i=0;i<n;i++)
	{
		cout << "P" << i+1 << ": ";
		cin >> t[i].bt >> t[i].at;
		t_bt[i] = t[i].bt;
		t[i].at_temp = t[i].at;
	}
	sjf(t,t_bt,n);
	cout << "waiting time :" <<endl;
	for(i=0;i<n;i++)
	{
		t[i].wt = t[i].wt - t[i].at_temp;
		cout <<"P" <<i+1 <<": "<<t[i].wt << endl;
		sum = sum + t[i].wt;
	}
	cout << "average waiting time = " << sum/n;
}
