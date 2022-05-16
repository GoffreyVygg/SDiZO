#include <iostream>
#include <string>
#include <fstream>
#include <sys/time.h>
#include "bst.h"
using namespace std;
 
struct node {
    string key;
    struct node *left, *right;
};

struct node* newNode(string item) {
    struct node* temp = (struct node*)malloc(sizeof(struct node));
    temp->key = item;
    temp->left = temp->right = NULL;
    return temp;
}
 
void inorder(struct node* root) {
    if (root != NULL) {
        inorder(root->left);
        cout << root->key << endl;
        inorder(root->right);
    }
}

struct node* insert(struct node* node, string key) {
    if (node == NULL) {
        return newNode(key);
	}
    if (key < node->key) {
        node->left = insert(node->left, key);
	} else {
        node->right = insert(node->right, key);
	}
    return node;
}

struct node* minValueNode(struct node* node) {
    struct node* current = node;
    while (current && current->left != NULL) {
        current = current->left;
	}
 
    return current;
}
 
struct node* deleteNode(struct node* root, string key) {
    if (root == NULL) {
        return root;
	}
    if (key < root->key) {
        root->left = deleteNode(root->left, key);
	} else if (key > root->key) {
        root->right = deleteNode(root->right, key);
	} else {
        if (root->left==NULL and root->right==NULL) {
            return NULL;
		} else if (root->left == NULL) {
            struct node* temp = root->right;
            free(root);
            return temp;
        } else if (root->right == NULL) {
            struct node* temp = root->left;
            free(root);
            return temp;
        }
        struct node* temp = minValueNode(root->right);
        root->key = temp->key;
        root->right = deleteNode(root->right, temp->key);
    }
    return root;
}
 
int main() {
	string Array[ileSlow];

    ifstream myFile(plikWej);

    if (!myFile ) {
        printf("Error reading file\n");
        exit(1);
    }
    for (int i = 0; i < ileSlow; i++) {
		myFile >> Array[i];
    }
	struct node* root = NULL;
	gettimeofday(&start,0);
    for (int i = 0; i < ileSlow; i++) {
		if (i == 0) {
			root = insert(root, Array[i]);
		} else {
			insert(root, Array[i]);
		}			
    }
	gettimeofday(&koniec,0);
	long sec = koniec.tv_sec - start.tv_sec;
	long usec = koniec.tv_usec - start.tv_usec;
	double czasWykonania = sec + usec*1e-6;
	
	plikWyjsciowy = fopen(czas,"a");
	fprintf(plikWyjsciowy, "%d\t%f\n", ileSlow, czasWykonania);
	fclose(plikWyjsciowy);
	
	inorder(root);

	printf("\nPoczatek pomiaru czasu usuwania:\n");
	for (int i = 0; i < ileSlow; i += 5) {
		gettimeofday(&start,0);
		root = deleteNode(root, Array[i]);	
		gettimeofday(&koniec,0);
		long secs = koniec.tv_sec - start.tv_sec;
		long usecs = koniec.tv_usec - start.tv_usec;
		double czasUsuwania = secs + usecs*1e-6;
		czasCalkowity += czasUsuwania;
		printf("%f\t%f\n", czasCalkowity, czasUsuwania);
	}
	sredniCzas = czasCalkowity/iteracje;
	printf("Sredni czas: %.6f s\n\n", sredniCzas);
    inorder(root);
	printf("\nWcisnij ENTER aby zakonczyc\n", sredniCzas);
	int ch = getchar();
	return 0;
    return 0;
}