#include<bits/stdc++.h>
using namespace std;
struct node{
        int key,degree;
        struct node *p,*child,*sibling;
};
struct node* merget(struct node* h1,struct node* h2)
{
        struct node* p=NULL;
        struct node* p1=h1;
        struct node* p2=h2;
        if(p1!=NULL && p2!=NULL)
        {
                if(p1->degree <= p2->degree)
                {
                        p =p1;
            p1 = p1->sibling;
                }
                else
                {
                        p = p2;
                        p2 = p2->sibling;
                }
        }
        else if(p1!=NULL)
        {
                p=p1;
                p1=p1->sibling;
        }
        else if(p1!=NULL)
        {
                p=p1;
                p1=p1->sibling;
        }
        else
        {
                return NULL; 
        }
        struct node* ps=p;
        while(p1!=NULL && p2!=NULL)
        {
                if(p1->degree < p2->degree)
                {
                        p->sibling=p1;
                        p1=p1->sibling;
                        p=p->sibling;
                }
                else
                {
                        p->sibling=p2;
                        p2=p2->sibling;
                        p=p->sibling;
                }
        }
        if(p1!=NULL)
        {
        while(p1!=NULL)
         {
                p->sibling=p1;
                p1=p1->sibling;
                p=p->sibling;
         }
    }
    if(p2!=NULL)
    {
             while(p2!=NULL)
            {
                        p->sibling=p2;
                        p2=p2->sibling;
                        p=p->sibling;
            }
    }
    return ps;
}
node* minkey(struct node* h)
{
        struct node* y=NULL;
        struct node* x=h;
        int min1=INT_MAX;
        while(x!=NULL)
        {
                if( (x->key) < min1)
                {
                    min1=x->key;
                    y=x;
                }
                x=x->sibling;
        }
        return y;
}
void print(struct node* h)
{
        struct node* x=h;
        while(x!=NULL)
        {
                //cout<<x->key<<" ";
                queue<struct node*>q;
                q.push(x);
                while(!q.empty())
                {
                        struct node* p = q.front();
                        q.pop();
                        cout<<p->key<<" ";
                        if (p->child != NULL) 
                        {
                                struct node* temp = p->child;
                                while (temp != NULL) 
                                {
                                        q.push(temp);
                                        temp = temp->sibling;
                                }
                        } 
                }
                x=x->sibling;
        }
        cout<<endl;
}
void link(struct node* x,struct node* next_x)
{
        next_x->p = x;
        next_x->sibling = x->child;
        x->child = next_x;
        x->degree += 1;
}
node* uniontree(node* h1,node* h2)
{
        //cout<<endl<<(h1)->key<<endl;
        node* h=merget(h1,h2);
        struct node* prev = NULL;
        struct node* x=h;
        struct node* x1=h;
        struct node* next_x = h->sibling;
        struct node* temp=NULL;
        while(next_x != NULL)
        {
                if((x->degree!=next_x->degree) || (next_x->sibling!=NULL && next_x->sibling->degree==x->degree))
                {
                        prev=x;
                        x=next_x;
                }
                else 
                {
                        if(x->key<=next_x->key)
                        {
                                x->sibling = next_x->sibling;
                                link(x, next_x);
                        }
                        else
                        {
                                if(prev==NULL)
                                   temp=next_x;//temp=next_x
                                else
                                    prev->sibling=next_x;
                                link(next_x,x);
                                x=next_x;
                        }
                }
                next_x=x->sibling;
    }
    //print(x1);
    if(temp!=NULL)
    h2=temp;
    else
    h2=x1;
    //cout<<endl;
    //cout<<temp->key<<endl;
    return h2;
}
node* create (int data, node* h1)
{
        node *newNode = (struct node*)malloc(sizeof(struct node));
        newNode->key=data;
        newNode->degree=0;
        newNode->p=NULL;
        newNode->child=NULL;
        newNode->sibling=NULL;
        node* h=uniontree(newNode,h1);
        //print(h1);
        //return newnode;
        return h;
}
//last vala minimum ho toh problem ho rah hai
node* extractmin(node* h)
{
	struct node* y=NULL;
	node* prev=NULL;
        node* prevmin=NULL;
        struct node* x=h;
        int min1=INT_MAX;
        while(x!=NULL)
        {
                if( (x->key) < min1)
                {
                    prevmin=prev;
                    min1=x->key;
                    y=x;
                }
                prev=x;
                x=x->sibling;
        }
    if(prevmin!=NULL && y->sibling!=NULL)
    {
    	prevmin->sibling=y->sibling;
    }
    else if(prevmin==NULL && y->sibling!=NULL)
    {
    	h=y->sibling;
    }
    else if(prevmin!=NULL && y->sibling==NULL)
    {
    	prevmin->sibling=NULL;
    }
    else
    {
    	h=NULL;
    }
    node* ch = y->child;
    while (ch != NULL) 
    {
	ch->p = NULL;
	ch = ch->sibling;
    }
    vector<node*>s;
    node* chi= y->child;
    while (chi != NULL) 
    {
    	s.push_back(chi);
    	chi= chi->sibling;
    }
    x=s.back();
    node* temp=x;
    while(!s.empty())
    {
    	x->sibling=s.back();
    	s.pop_back();
    	x=x->sibling;
    }
    x->sibling=NULL;
    node* head=uniontree(temp,h);
    return head;
}
node* search(int data,node* h)
{
        struct node* x=h;
        node* temp=NULL;
        while(x!=NULL)
        {
           queue<struct node*>q;
                q.push(x);
                while(!q.empty())
                {
                        struct node* p = q.front();
                        q.pop();
                        //cout<<p->key<<" ";
                        if (p->child != NULL) 
                        {
                                temp = p->child;
                                while (temp != NULL) 
                                {
                                        if(temp->key==data)
                                        {
                                                return temp;
                                        }
                                        q.push(temp);
                                        temp = temp->sibling;
                                }
                        } 
                }
                x=x->sibling;
        }
return NULL;
}
int decreasekey(int data,int data1,node* h)
{
        node* s=search(data,h);
        if(s==NULL)
        {
                cout<<"Data is not found in binomial heap"<<endl;
                return 0;
        }
        if(data<data1)
        {
                cout<<"Value should only decrease not increase"<<endl;
                return 0;
        }
        s->key=data1;
        if(s->p!=NULL && s->p->key>s->key)
        {
                while(s->p!=NULL)
                {
                        if(s->p->key<s->key)
                        {
                                break;
                        }
                        else
                        {
                                int temp=s->key;
                                s->key=s->p->key;
                                s->p->key=temp;
                        }
                }
        }
        return 1;
}
node* deletenode(int data,node* root)
{
        int in=decreasekey(data,INT_MIN,root);
        if(in==1)
        {
         node* d=extractmin(root);
         return d;
        }
        else
        {
                return root;
        }
}
int main()
{
	struct node* root=NULL;
        int n;
        cin>>n;
        vector<int>a(n,0);
        for(int i=0;i<n;i++)
                cin>>a[i];
        for(int i=0;i<n;i++)
                root=create(a[i],root);

        cout<<"After Traversing heap is : ";
        print(root);
        cout<<endl;

        cout<<"Minimum from heap is : ";
        node* min1=minkey(root);
        cout<<min1->key;
        cout<<endl<<endl;

        cout<<"Extracting minimum from heap :";
        root=extractmin(root);
        print(root);
        cout<<endl;

        cout<<"Decreasing key 7 to 2:";
        decreasekey(7,2,root);
        print(root);
        cout<<endl;

        cout<<"Deleting node 9 from heap : ";
        root=deletenode(9,root);
        print(root);
}
