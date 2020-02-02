#include <cstdio>
#include <utility>
#include <cstdlib>
using namespace std;
typedef pair<int,int> pii; 
struct Node{
	Node* ch[2];
	int id,v,r,s;
	Node(int _id,int _v):id(_id),v(_v){r=rand(); s=1; ch[0]=ch[1]=NULL;}
	int cmp(int x){
		if(x==v) return -1;
		else return x<v?0:1;
	}
	void maintain(){
		s=1;
		if(ch[0]!=NULL) s+=ch[0]->s;
		if(ch[1]!=NULL) s+=ch[1]->s;
	}
};

void rotate(Node* &o,int d)
{
	Node* k=o->ch[d^1]; o->ch[d^1]=k->ch[d]; k->ch[d]=o;
	o->maintain(); k->maintain(); o=k;
}
void insert(Node* &o,int id,int v)
{
	if(o==NULL) o = new Node(id,v);
	else{
		int d=(v < o->v ? 0 : 1); //may have nodes with same v
		insert(o->ch[d],id,v);
		if(o->ch[d]->r > o->r) rotate(o,d^1);
	}
	o->maintain();
}
void remove(Node* &o,int x) 
{
	int d=o->cmp(x);
	if(d==-1){
		Node* u=o;
		if(o->ch[0]!=NULL && o->ch[1]!=NULL){
			int d2 = (o->ch[0]->r > o->ch[1]->r ? 1 : 0);
			rotate(o,d2); remove(o->ch[d2],x);
		}else{
			if(o->ch[0] == NULL) o=o->ch[1];
			else o=o->ch[0];
			delete u;
		}
	}else remove(o->ch[d], x);
	if(o!=NULL) o->maintain();
}
pii kth(Node* o,int k) //find the kth small
{
	//printf("%d %d %d\n",o->id,o->s,k);
	if(o==NULL || k<=0 || k>o->s) return pii(0,0);
	int s = o->ch[0]==NULL?0:o->ch[0]->s;
	if(k==s+1) return pii(o->id,o->v);
	else if(k<=s) return kth(o->ch[0],k);
	else return kth(o->ch[1],k-s-1);
}
void debug(Node* o){
	printf("id=%d, v=%d, s=%d\n",o->id,o->v,o->s);
	if(o->ch[0]!=NULL) puts("left"), debug(o->ch[0]);
	if(o->ch[1]!=NULL) puts("right"), debug(o->ch[1]);
}

Node* root = new Node(0,0);
int main()
{
	int op,cur=1;
	while(scanf("%d",&op) && op){
		/*puts("now, debug!");
		debug(root);*/
		if(op==1){
			int id,v;
			scanf("%d%d",&id,&v);
			insert(root,id,v);
			cur++;
		}else if(op==2){
			if(cur==1) puts("0");
			else{
				pii x=kth(root,cur);
				remove(root,x.second);
				printf("%d\n",x.first);
				cur--;
			}
		}else{
			if(cur==1) puts("0");
			else{
				pii x=kth(root,2);
				//printf("3: x.second=%d\n",x.second);
				remove(root,x.second);
				printf("%d\n",x.first);
				cur--;
			}
		}
	}
}