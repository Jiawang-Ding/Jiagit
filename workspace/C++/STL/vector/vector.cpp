#include <iostream>
#include <vector>
#include <algorithm>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/time.h>

using namespace std;

typedef struct {
	int m_value;
	char m_name[10];
}student;

student stu[5]={
	{1,"aaaa"},
	{2,"bbbb"},
	{3,"cccc"},
	{4,"dddd"},
	{5,"eeee"},
};

static unsigned int cnt=0;

void siglrm_fn(int sig){
	cout << "alarm" << endl;
	alarm(2);
	return;
}
void printMes(int signo){
	cout << "Get a signal: " << signo << " cnt: " <<  ++cnt << " counts!" << endl;
}

int main()
{
	int res = 0;
	struct itimerval tick,tick_v;
	
	signal(SIGALRM, printMes);
	signal(SIGVTALRM, printMes);
	//memset(&tick, 0, sizeof(tick));
	//memset(&tick_v, 0, sizeof(tick_v));
	
	//Timeout to run first time
	tick.it_value.tv_sec = 2;
	tick.it_value.tv_usec = 0;

	tick.it_interval.tv_sec = 1;
	tick.it_interval.tv_usec = 0;

	if(setitimer(ITIMER_REAL, &tick, NULL) < 0){
		cout << "Set timer1 failed!" << endl;
	}

	//Timeout to run first time
	tick_v.it_value.tv_sec = 0;
	tick_v.it_value.tv_usec = 500000;

	tick_v.it_interval.tv_sec = 0;
	tick_v.it_interval.tv_usec = 500000;

	if(setitimer(ITIMER_VIRTUAL, &tick_v, NULL) < 0){
		cout << "Set timer2 failed!" << endl;
	}
	

	while(1){
		//pause();
		//sleep(1);
		for(int i=0; i<0xfffffff; i++){}
		cout << "Hello world" << endl;  
	}
	/*
	signal(SIGALRM,siglrm_fn);
	alarm(10);
	cout << "Alarm(10)" << endl;
	while(1){
		pause();
		cout << "Hello world" << endl;
	}
	**/
	
}


/*
int main()
{
	vector<int> x;
	//vector<int> v(10);
	//vector<int> v(10,2);
	for(int n=0; n<10; n++){
		x.push_back(n);
	}


	vector<int> v(x.begin(),x.end()); //将 v 容器初始化为 x 容器的值
	cout << "************** 1 ***************" << endl;
	vector<int>::iterator i;
	for(i=v.begin(); i != v.end(); ++i){
		cout << *i << " ";
		*i *= 2;
	}
	cout << endl;

	cout << "************** 2 ***************" << endl;
	for(i=v.begin(); i < v.end(); ++i){
		cout << *i << " ";
	}
	cout << endl;

	cout << "************** 3 ***************" << endl;
	vector<int>::reverse_iterator j;
	for(j=v.rbegin(); j != v.rend(); ++j)
		cout << *j << " ";
	cout << endl;

	i = find(v.begin(), v.end(), 6);
	if(i != v.end()){
		cout << "Find is :" << *i << endl;
	}
	
	cout << "************** 4 ***************" << endl;
	i = v.begin();
	while(i < v.end()){
		cout << *i << " ";
		i++;
	}
	cout << endl;
	return 0;
}

*/

/*
int main()
{
	student tmp;
	vector<student> st;
	for(int n=0; n<5; n++){
		cout << "What's your name? ";
		cin >> tmp.m_name;
		cout << "Enter number:";
		cin >> tmp.m_value;
		
		st.push_back(tmp);
	}

	

	vector<student>::iterator i;
	for(i=st.begin(); i < st.end(); ++i){
		cout << i->m_value << ":" << i->m_name << endl;
	}
	cout << endl;


	i = find(st.begin(), st.end(), tmp.m_name);
	if(i != st.end()){
		cout << "Find is :" << i->m_name << ":" << i->m_value << endl;
	}
	
	sort(st.begin(), st.end());

	vector<student>::reverse_iterator j;
	for(j=st.rbegin(); j<st.rend(); ++j){
		cout << j->m_value << ":" <<j->m_name << endl;
	}
	cout << endl;
	return 0;
}
*/

/***********************************************************************
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <sys/time.h>

int sec;

void sigroutine(int signo){
   switch (signo){
   case SIGALRM:
       printf("Catch a signal -- SIGALRM \n");
       signal(SIGALRM, sigroutine);
       break;
   case SIGVTALRM:
       printf("Catch a signal -- SIGVTALRM \n");
       signal(SIGVTALRM, sigroutine);
       break;
   }
   return;
}

int main()
{
   struct itimerval value, ovalue, value2;

   sec = 5;
   printf("process id is %d ", getpid());
   signal(SIGALRM, sigroutine);
   signal(SIGVTALRM, sigroutine);
   value.it_value.tv_sec = 1;
   value.it_value.tv_usec = 0;
   value.it_interval.tv_sec = 1;
   value.it_interval.tv_usec = 0;
   setitimer(ITIMER_REAL, &value, &ovalue);
   value2.it_value.tv_sec = 0;
   value2.it_value.tv_usec = 500000;
   value2.it_interval.tv_sec = 0;
   value2.it_interval.tv_usec = 500000;
   setitimer(ITIMER_VIRTUAL, &value2, &ovalue);
   for(;;);
}
***********************************************************************/


