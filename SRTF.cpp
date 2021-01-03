#include<iostream>
#define size 30
#define minimum 100000
using namespace std;
struct time
{
	int bt;
	int bt_2;
	int at;
	int st;
	int cmpt;
	int wt;	
};
int p[size];
int min_at_ind(struct time t[size],int n)
{
	int temp = -1,min = minimum;
	for(int i=0;i<n;i++)
	{
		if(min > t[i].at)
		{
			min = t[i].at;
			temp=i;
		}
	}
	return temp;
}
int pa(int ct,struct time t[size],int done[size],int n)
{
	int f=0,j=0;
	for(int i=0;i<n;i++)
	{
		if(ct >= t[i].at && done[i] != 1)
		{
			p[j] = i;
			j++;
			f=1;
		}
	}
	if(f==1)
	{
		return j;
	}
	else
	{
		return -1;
	}
}
int srtf(struct time t[size],int n)
{
	int ct,min_ind,done[size],q,visited_processor[size],min_bt_ind = -1,min,comp=0;
	for(int i=0;i<n;i++)
	{
		done[i] = 0;
		visited_processor[i] = 0;
	}
	min_ind = min_at_ind(t,n);
	if(min_ind != -1)
	{
		ct = t[min_ind].at;
	}
	while(comp != n)
	{
		q = pa(ct,t,done,n);
		if(q != -1)
		{
			min = minimum;
			for(int i=0;i<q;i++)
			{
				if(min > t[p[i]].bt)
				{
					min = t[p[i]].bt;
					min_bt_ind = p[i];
				}
			}
			if(min_bt_ind != -1)
			{
				if(visited_processor[min_bt_ind] != 1)
				{
					visited_processor[min_bt_ind] = 1;
					t[min_bt_ind].st = ct;
				}
				t[min_bt_ind].bt = t[min_bt_ind].bt - 1;
				ct = ct+1;
				if(t[min_bt_ind].bt == 0)
				{
					t[min_bt_ind].cmpt = ct;
					t[min_bt_ind].wt = t[min_bt_ind].cmpt - t[min_bt_ind].at - t[min_bt_ind].bt_2;
					done[min_bt_ind] = 1;
					comp++;
				}
			}
		}
		else
		{
			ct++;
		}
	}
}
int main()
{
	int i,n;
	float sum=0;
	struct time t[size];
	cout << "Enter no. of processes" <<endl;
	cin >> n;
	cout << "Input burst time and arrival time " <<endl;
	for(i=0;i<n;i++)
	{
		cout << "P" << i+1 << ": ";
		cin >> t[i].bt>> t[i].at;
		t[i].bt_2 = t[i].bt;
	}
	srtf(t,n);
	cout << "Process \t" << "Arrival_time \t" << "Burst_time \t" << "Start_time \t" << "Completion_time \t" << "Waiting_time" <<endl;
	for(i=0;i<n;i++)
	{
		cout << "P" << i+1 << ":\t\t";
		cout << t[i].at <<"\t\t"<< t[i].bt_2 <<" \t\t"<< t[i].st <<" \t\t" <<t[i].cmpt <<" \t\t\t" <<t[i].wt <<endl;
		sum = sum+t[i].wt;
	}
	cout << "\nAverage waiting time : " << sum/n;
}
