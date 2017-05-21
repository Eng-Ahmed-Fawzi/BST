#include <iostream>
#include <string>
#include <fstream>
using namespace std;

struct Patient_Data
{
    string Patient_Name;
    int Patient_Age;
    int Patient_Number;
    int Num_Drugs;
    string Patient_Drugs[10];
    struct Patient_Data *left;
    struct Patient_Data *right;
}*root;

class BST
{
public:

    void Insert (Patient_Data *&, Patient_Data *);
    void Delete (int, Patient_Data *&);
    void Inorder (Patient_Data *);
    void Display(Patient_Data *&, int);
    BST()
    {
        root = NULL;
    }
};

void BST:: Insert(Patient_Data *&root, Patient_Data *newPatient_Data)
{
    if (root == NULL)
    {
        root = new Patient_Data;
        root->Patient_Name = newPatient_Data->Patient_Name;
        root->Patient_Age = newPatient_Data->Patient_Age;
        root->Patient_Number = newPatient_Data->Patient_Number;
        root->Num_Drugs = newPatient_Data->Num_Drugs;
        for (int i=0; i<=root->Num_Drugs; i++)
        {
            root->Patient_Drugs[i] = newPatient_Data->Patient_Drugs[i];
        }
        root->left = NULL;
        root->right = NULL;
        cout<<"Root Patient_Data is Added"<<endl;
        return;
    }
    if (root->Patient_Number > newPatient_Data->Patient_Number)
    {
        if (root->left != NULL)
        {
            Insert(root->left, newPatient_Data);  //recursive function
        }
        else
        {
            root->left = newPatient_Data;
            (root->left)->left = NULL;
            (root->left)->right = NULL;
            cout<<"Patient_Data Added To Left"<<endl;
            return;
        }
    }
    else
    {
        if (root->right != NULL)
        {
            Insert(root->right, newPatient_Data);
        }
        else
        {
            root->right = newPatient_Data;
            (root->right)->left = NULL;
            (root->right)->right = NULL;
            cout<<"Patient_Data Added To Right"<<endl;
            return;
        }
    }
}

void BST:: Delete (int Key, Patient_Data *&root)
{
    bool found = false;
    if(root == NULL)
    {
        cout<<" This Tree is empty! "<<endl;
        return;
    }

    Patient_Data* child;
    Patient_Data* parent;
    child = root;

    while(child != NULL)
    {
        if(child->Patient_Number == Key)
        {
            cout <<endl<< "The Patient data is: "<<endl;
            cout <<"The Patient name is: "<<child->Patient_Name<<endl;
            cout <<"The Patient Age is: "<<child->Patient_Age<<"year"<<endl;
            cout <<"The Patient Drugs are: "<<endl;
            for (int i=0; i<=child->Num_Drugs; i++)
            {
                cout<<child->Patient_Drugs[i]<<endl;
            }
            found = true;
            break;
        }
        else
        {
            parent = child;
            if(Key > child->Patient_Number)
            {
                child = child->right;
            }
            else
            {
                child = child->left;
            }
        }
    }
    if(!found)
    {
        cout<<"Patient Number not found! "<<endl;
        return;
    }

    // 3 cases :
    //1)We're looking at a leaf Patient_Data
    if( child->left == NULL && child->right == NULL)
    {
        if(parent->left == child)
        {
            parent->left = NULL;
        }
        else
        {
            parent->right = NULL;
        }
        delete child;
        return;
    }

    //2) Patient_Data with single child
    if((child->left == NULL && child->right != NULL)||(child->left != NULL && child->right == NULL))
    {
        if(child->left == NULL && child->right != NULL)
        {
            if(parent->left == child)
            {
                parent->left = child->right;
                delete child;
            }
            else
            {
                parent->right = child->right;
                delete child;
            }
        }
        else // left child present, no right child
        {
            if(parent->left == child)
            {
                parent->left = child->left;
                delete child;
            }
            else
            {
                parent->right = child->left;
                delete child;
            }
        }
        return;
    }

    //Patient_Data with 2 children
    if ((child->left != NULL) && (child->right != NULL))
    {
        Patient_Data* chkr;
        chkr = child->right;
        if((chkr->left == NULL) && (chkr->right == NULL))
        {
            child = chkr;
            delete chkr;
            child->right = NULL;
        }
        else // right child has children
        {
            //if the Patient_Data's right child has a left child
            // Move all the way down left to locate smallest element

            if((child->right)->left != NULL)
            {
                Patient_Data* lchild;
                Patient_Data* lchildp;
                lchildp = child->right;
                lchild = (child->right)->left;
                while(lchild->left != NULL)
                {
                    lchildp = lchild;
                    lchild = lchild->left;
                }
                child->Patient_Number = lchild->Patient_Number;
                delete lchild;
                lchildp->left = NULL;
            }
            else
            {
                Patient_Data* tmp;
                tmp = child->right;
                child->Patient_Number = tmp->Patient_Number;
                child->right = tmp->right;
                delete tmp;
            }

        }
        return;
    }

}

void BST:: Display( Patient_Data *&root,int Key)
{
    bool found = false;
    if(root == NULL)
    {
        cout<<" This Tree is empty! "<<endl;
        return;
    }

    Patient_Data* child;
    Patient_Data* parent;
    child = root;

    while(child != NULL)
    {
        if(child->Patient_Number == Key)
        {
            cout <<endl<< "The Patient data is: "<<endl;
            cout <<"The Patient name is: "<<child->Patient_Name<<endl;
            cout <<"The Patient Age is: "<<child->Patient_Age<<"year"<<endl;
            cout <<"The Patient Drugs are: "<<endl;
            for (int i=0; i<=child->Num_Drugs; i++)
            {
                cout<<child->Patient_Drugs[i]<<endl;
            }
            found = true;
            return;
        }
        else
        {
            parent = child;
            if(Key > child->Patient_Number)
            {
                child = child->right;
            }
            else
            {
                child = child->left;
            }
        }
    }
    if(!found)
    {
        cout<<"Patient Number not found! "<<endl;
        return;
    }
}

void BST:: Inorder (Patient_Data *root)
{
    if (root == NULL)
    {
        cout<<" This Tree is empty! "<<endl;
        return;
    }
    Inorder(root->left);
    cout <<endl<< "The Patient data is: "<<endl;
    cout <<"The Patient name is: "<<root->Patient_Name<<endl;
    cout <<"The Patient Age is: "<<root->Patient_Age<<"year"<<endl;
    cout <<"The Patient Number is: "<<root->Patient_Number<<endl;
    cout <<"The Patient Drugs are: "<<endl;
    for (int i=0; i<=root->Num_Drugs; i++)
    {
        cout<<root->Patient_Drugs[i]<<endl;
    }

    Inorder(root->right);
}

int main()
{
    int choice, num,counter,check;
    BST bst;
    Patient_Data *temp;
    while (1)
    {
        cout<<"-----------------"<<endl;
        cout<<"Operations on BST"<<endl;
        cout<<"-----------------"<<endl;
        cout<<"1.Insert Element "<<endl;
        cout<<"2.Delete Element "<<endl;
        cout<<"3.In-order Traversal"<<endl;
        cout<<"4.Display"<<endl;
        cout<<"5.Quit"<<endl;
        cout<<"Enter your choice : ";
        cin>>choice;
        switch(choice)
        {
        case 1:
            temp = new Patient_Data;
            cout <<endl<< "Please enter The Patient data: "<<endl;
            cout <<"The Patient name is: ";
            cin>>temp->Patient_Name;
            cout <<endl<<"The Patient Age is: ";
            cin>>temp->Patient_Age;
            cout <<endl<<"The Patient Number is: ";
            cin>>temp->Patient_Number;
            for (counter=0; counter<3; counter++)
            {
                cout <<endl<<"The Patient Drugs are: ";
                cout <<endl<<counter+1<<" )";
                cin>>temp->Patient_Drugs[counter];

                cout << "Do you need to insert another drug ? " << endl;
                cout << "1- Yes" << endl;
                cout << "2- No" << endl;
                cin>> check;
                if (check == 2)
                {
                    break;
                }
            }
            temp->Num_Drugs = counter;
            bst.Insert(root, temp);
            break;
        case 2:
            if (root == NULL)
            {
                cout<<"Tree is empty, nothing to delete"<<endl;
                continue;
            }
            cout<<"Enter the number to be deleted : ";
            cin>>num;
            bst.Delete(num,root);
            break;
        case 3:
            //cout<<"Inorder Traversal of BST:"<<endl;
            bst.Inorder(root);
            cout<<endl;
            break;
        case 4:
            cout<<"Enter the number to be displayed : ";
            cin>>num;
            bst.Display(root,num);
            cout<<endl;
            break;
        case 5:
            return 0;
        default:
            cout<<"Wrong choice"<<endl;
        }
    }
}
