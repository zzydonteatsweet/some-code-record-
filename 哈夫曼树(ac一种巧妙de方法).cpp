#include<iostream>
#include<cstdlib>
#include<queue>
using namespace std;
int main(){
  priority_queue<int,vector<int>,greater<int> > q;
  int n;
  cin >> n;
  int temp;
  for(int i=0;i<n;i++){
    cin >> temp;
    q.push(temp);
  }
 //不用建树直接求编码的值
 int sum=0;
 while(q.size()>1){
   int t=q.top();
   q.pop();
   t+=q.top();
   q.pop();
   q.push(t);
   sum+=t;
 } 
 printf("%d\n",sum);
}
