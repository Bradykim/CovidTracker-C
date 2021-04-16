#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct TreeNode
{
    char info[80];
    struct TreeNode* right;
    struct TreeNode* left;
};

struct TreeNode* makeNode(char newinfo[])
{
    /*1. Allocate memory when a TreeNode is dynamically created.
      2. Set the info equal to the value given.
      3. Set the right and left pointers to NULL.
      4. Return the TreeNode*/
    struct TreeNode* TreeNode= (struct TreeNode*)malloc(sizeof(struct TreeNode));
    strcpy(TreeNode -> info,newinfo);
    TreeNode -> right = NULL;
    TreeNode -> left = NULL;
    return TreeNode;
}
void makeTree(char infected[], char infector[], struct TreeNode* node)
{
    /*1. Recursively loop through the binary tree.
      2. Find where the value equals the infector.
      3. Create a new node with the info=infected at that location.*/
      /*send in two strings representing infected and infector*/
    if(node ==NULL)
    {
        return;
    }
    if(strcmp(node->info, infector)==0)
    {
        /*insert node vs find node
        make sure I can insert each node first
        when you insert 
        if strcmp(a,b) a is bigger returns positive.*/
        if((node->right == NULL) && (node->left==NULL))
        {
            node-> right = makeNode(infected);
            return;
        }
        else if((node->right != NULL) && (node->left==NULL)){
            if(strcmp(infected, node->right->info)>0)
            {
                struct TreeNode* temp = node-> right;
                node->right = makeNode(infected);
                node->left =temp;
                return;
            }
            node->left= makeNode(infected);
            return;
        }
        else{
            if(strcmp(node->left->info, infected))
            {
                struct TreeNode* temp = node-> left;
                node->left = makeNode(infected);
                node->right =temp;
                return;
            }
            node->right= makeNode(infected);
            return;
        }  
    }
    
    makeTree(infected, infector, node->left);
    makeTree(infected, infector, node->right);
    
}


void printTree(struct TreeNode* root)
{
    if(root != NULL)
    {
        printf("%s \n",root->info);
        printTree(root->left);
        printTree(root->right);
        free(root);
    }
}
/*Need to make print DFS that prints the tree given the root. free every thing and close the file
*/
FILE *fi;
int main(int argc, char* argv[])
{
    /*1. Create root Node.
      2. Open the file.
      3. Read through the file and for each line call maketree.
      4. If we reach DONE, then stop the program.*/
    char bluedevil[] = "BlueDevil";
    struct TreeNode* root = makeNode(bluedevil);
    char wor[80];
    char done [] = "DONE";
    fi = fopen(argv[1],"rt");
    while(1)
    {
        char infected[80];
        char infector[80];
        fscanf(fi,"%s %s",infected,infector);
        if(strcmp(infected,done)==0)
        {
            break;
        }
        makeTree(infected,infector,root);
    }
    printTree(root);
    fclose(fi);
    return 0;
}