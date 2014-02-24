#include<stdio.h>
#include<stdlib.h>

typedef struct _Entry_Node{
	char *entry;
	struct _Entry_Node *forward;
}Entry_Node;

int compare(Entry_Node *pNode1, Entry_Node *pNode2){
	int i, diff;
	i=0;
	diff = 0;
	while(pNode1->entry[i] != '\0' && pNode2->entry[i] != '\0'){
		
		diff = pNode1->entry[i] - pNode2->entry[i];
		
		if(pNode1->entry[i] >= 'a') diff -= 32;
		if(pNode2->entry[i] >= 'a') diff += 32;
		
		switch(diff){
			case 0:
				i++;
				break;
			default:
				if(diff > 0){
					return 1;
				}else{
					return 0;
				}
				break;
		}
		
	}
	
	if(pNode2->entry[i] == '\0'){
		return 1;
	}
	
	return 0;
}

void freeNode(Entry_Node *pNode){
	free(pNode->entry);
	free(pNode);
}

void RemoveNode(Entry_Node **pHead, Entry_Node *pNode){
	Entry_Node *pBack;
	
	if(!*pHead) return;
	
	if(*pHead = pNode){
		*pHead = pNode->forward;
		freeNode(pNode);
		return;
	}
	
	pBack = *pHead;
	while(pBack){
		if(pBack->forward == pNode){
			pBack->forward = pNode->forward;
			freeNode(pNode);
			return;
		}
		pBack = pBack->forward;
	}
	
	if(!pBack) return;
}

void InsertNode(Entry_Node **pHead, Entry_Node *pNewNode){
	Entry_Node *pFront, *pBack;
	//printf("assert\n");
	if(*pHead){
		//printf("assert\n");
		pFront = *pHead;
		pBack = NULL;
		
		while(pFront){
			if(compare(pFront, pNewNode)){
				if(pBack){
					pBack->forward = pNewNode;
				}else{
					*pHead = pNewNode;
				}
				pNewNode->forward = pFront;
				break;
			}
			pBack = pFront;
			pFront = pFront->forward;
			//printf("assert\n");
		}
		
		if(pFront == NULL){
			pBack->forward = pNewNode;
		}
		
	}else{
		//printf("assert\n");
		*pHead = pNewNode;
		//printf("insert %s\n", (*pHead)->entry);
	}
	
}

void printNodeList(Entry_Node *pHead){
	Entry_Node *pNode;
	pNode = pHead;
	
	while(pNode){
		printf("\"%s\"", pNode->entry);
		pNode = pNode->forward;
		if(pNode){
			printf(" -> ");
		}else{
			printf("\n");
		}
	}
}


int main(void){
	Entry_Node *newNode, *pHead;
	
	pHead = NULL;
	newNode = NULL;
	
	while(1){
		printf("Input String: ");
		
		newNode = malloc( sizeof(Entry_Node) );
		newNode->entry = malloc( sizeof(char)*50 );
		newNode->forward = NULL;
		
		scanf("%49s", newNode->entry);
		if(newNode->entry[0] == '\0') break;
		
		InsertNode(&pHead, newNode);
		printf("Show Result: ");
		printNodeList(pHead);
	}
	
	while(pHead){
		RemoveNode(&pHead, pHead);
		printf("remove Node : ");
		printNodeList(pHead);
	}
	
	return 0;
}
