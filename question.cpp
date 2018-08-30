#include<bits/stdc++.h>
using namespace std;


//node structure for the dynamic list of records
class node
{
    char timestamp_val[250];
    string data;
    int nodeNumber;
    string nodeid;
    string referenceNodeId;
    string childReferenceNodeId[100];
    string genesisReferenceNodeId;
    int value;
    string hashval;
    //to store the address of the child node
    node *child;
    //to store the address of all the nodes at the same level
    node *same_level;
    //only for root node, to store sum of values of child nodes
    int child_val;
public:
    //function for creating the genesis node
    void create_GensisNode();
    //function for creating the child set for a node
    void create_childset();
    //function for creating a child node
    void create_childnode();
    //function to create a hash value
    int hash_val(int,int);
    //function to find the address of the root node taking in the node value
    node * find(node*, int);
    //function to edit the value of a node
    void edit_value_node(int, int);
};

//function generating unique random strings for nodeId
void gen_random(char *s, int l) {
    for (int c; c=rand()%62, *s++ = (c+"07="[(c+16)/26])*(l-->0););
}
//global variable for storing the unique incremental integer value
int unique_number = 0;
//global variable storing the genesis node's value
int node_val_genesis = -1;
//variable storing the address of the genesis node
node *root;

void  node :: create_GensisNode()
{
    time_t now = time(0);
    char* dt = ctime(&now);
    node *temp;
    temp = new node;
    root = temp;
    unique_number += 1;
    strcpy(temp->timestamp_val, dt);
    temp->nodeNumber = unique_number;
    temp->child = NULL;
    temp->same_level = NULL;
    cout<<"\nEnter the Genesis node's value: ";
    cin>>node_val_genesis;
    temp->value = node_val_genesis;
    temp->referenceNodeId.push_back('\0');
    return;
}

void node :: create_childset()
{
    if (root == NULL)
    {
        return;
    }
    int val,flag = 0;
    cout<<"\nEnter the value of the root node: ";
    cin>>val;
    node *temp;
    //node *temp2;
    temp = new node;
    //temp2 = new node;
    temp = find(root, val);
    do
    {
        if (flag == 0)
        {
            node *temp1;
            temp1 = new node;
            cout<<"\nEnter the node's value to be inserted: ";
            cin>>val;

            unique_number += 1;
            temp1->nodeNumber = unique_number;

            time_t now = time(0);
            char* dt = ctime(&now);
            strcpy(temp1->timestamp_val, dt);

            temp1->child = NULL;
            temp1->same_level = NULL;
            cout<<"\nEnter the node's value: ";
            cin>>temp1->value;

            cout<<"\nDo you want to enter more nodes(1-ye/0-no): ";
            cin>>flag;
            temp->child = temp1;
            //temp->childReferenceNodeId.push_back(temp1);
            //temp2 = temp;
            temp = temp1;
        }
        node *temp1;
        temp1 = new node;
        cout<<"\nEnter the node's value to be inserted: ";
        cin>>val;

        unique_number += 1;
        temp1->nodeNumber = unique_number;

        time_t now = time(0);
        char* dt = ctime(&now);
        strcpy(temp1->timestamp_val, dt);

        temp1->child = NULL;
        temp1->same_level = NULL;
        cout<<"\nEnter the node's value: ";
        cin>>temp1->value;

        cout<<"\nDo you want to enter more nodes(1-ye/0-no): ";
        cin>>flag;
        temp->same_level= temp1;
        //temp2->childReferenceNodeId.push_back(temp1);
        temp = temp1;

    }while(flag == 1);
}

void node :: create_childnode()
{
    if(root == NULL)
    {
        return;
    }
    int val;
    cout<<"\nEnter the value of the root node: ";
    cin>>val;
    node *temp;
    temp = new node;
    temp = find(root, val);
    if(temp->child == NULL)
    {
        node *temp1;
        temp1 = new node;
        unique_number += 1;
        temp1->nodeNumber = unique_number;

        time_t now = time(0);
        char* dt = ctime(&now);
        strcpy(temp1->timestamp_val, dt);

        temp1->child = NULL;
        temp1->same_level = NULL;
        cout<<"\nEnter the node's value: ";
        cin>>temp1->value;
        //temp->childReferenceNodeId.push_back(temp1);
        temp->child = temp1;
    }
    else
    {
        temp = temp->child;
        //loop after which temp will store the address of the last node, after which new node has to be entered.
        while(temp->same_level->same_level != NULL)
        {
            temp = temp->same_level;
        }

        node *temp1;
        temp1 = new node;
        unique_number += 1;
        temp1->nodeNumber = unique_number;

        time_t now = time(0);
        char* dt = ctime(&now);
        strcpy(temp1->timestamp_val, dt);

        temp1->child = NULL;
        temp1->same_level = NULL;
        cout<<"\nEnter the node's value: ";
        cin>>temp1->value;
        temp->same_level = temp1;
        //temp->childReferenceNodeId.push_back(temp1);

    }
}

//function computing the hash value
int node :: hash_val(int val, int id)
{
    int temp_val;
    temp_val = val * id;
    return temp_val;
}

//complexity for the function will be O(n) - where n is the total number of nodes
node * node :: find(node *temp_var, int val)
{
    node *temp=root;
    if(root->value == val)
    {
        return root;
    }
    root = find(root->child, val);
    root = find(root->same_level, val);
    return root;
}

//function for editing a node value.
void node :: edit_value_node(int old_val, int new_val)
{
    node *temp;
    temp = new node;
    temp = find(root, old_val);
    temp->value = new_val;
    return;
}

int main()
{
    root = NULL;
    int choice,flag=1;
    node temp_var;
    do
    {
        cout<<"\n1. Create a Genesis Node ";
        cout<<"\n2. Create a set of child nodes ";
        cout<<"\n3. Create a child node ";
        cout<<"\n4. Encrypt and Decrypt Data ";
        cout<<"\n5. Verify owner of the node ";
        cout<<"\n6. Edit the value of a node ";
        cout<<"\n7. Transfer ownership ";
        cout<<"\n8. Find Longest chain of genesis node ";
        cout<<"\n9.  Find Longest chain of any node";
        cout<<"\n10. Merge 2 nodes with ownership of longer chain ";
        cout<<"\nWhat do you want to do: ";
        cin>>choice;
        switch(choice)
        {
            case 1: temp_var.create_GensisNode();
                    break;
            case 2: temp_var.create_childset();
                    break;
            case 3: temp_var.create_childnode();
                    break;
            case 4: break;
            case 5: break;
            case 6: int old_value, new_value;
                    cout<<"\nEnter the old node value: ";
                    cin>>old_value;
                    cout<<"\nEnter the new node value: ";
                    cin>>new_value;
                    temp_var.edit_value_node(old_value, new_value);
                    break;
            case 7: break;
            case 8: break;
            case 9: break;
            case 10: break;
            default : break;
        }
        cout<<"\nDo you want to continue(1-yes/0-no): ";
        cin>>flag;
    }while(flag == 1);
    return 0;
}
