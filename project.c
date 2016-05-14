
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
	char word[45];	//estimate; change to max possible word len //optimized -> word = (char*) malloc(sizeof(char)*(N*N))
	struct node *next;
}dict;

typedef struct nodetag{
	int x;
	struct nodetag *sibling;
	struct nodetag *child;
	char letter;
}node;

int prefix(node *head, char *searchword){
	int i;
	node *lastltrptr = NULL;
	node *ptr = NULL;
	
			for(i=0; i<strlen(searchword); i++){
	    			if(i == 0){
	    				ptr = head->child;
	    				while(ptr != NULL){
	    					if(ptr->letter == searchword[i]){
	    						lastltrptr = ptr;
	    						if(i == strlen(searchword)-1){
	    							//printf("Valid prefix!\n");	    							
	    							return 1;
	    						}
	    						break;
	    					}
	    					if(ptr->sibling == NULL){
	    						//printf("Invalid prefix!\n");
	    						return 0;
	    					}
	    					ptr = ptr->sibling;
	    				}
	    			}
	    			else{
	    				ptr = lastltrptr;
	    				if(ptr->child == NULL){
	    					//printf("Invalid prefix!\n");
	    					return 0;
	    				}
	    				else{
		    				if(ptr->child->letter != searchword[i]){
		    					ptr = ptr->child;
		    					while(ptr != NULL){
		    						if(ptr->letter == searchword[i]){
		    							lastltrptr = ptr;
		    							if(i == strlen(searchword)-1){
			    							//printf("Valid prefix!\n");
			    							return 1;
			    						}
		    							break;
		    						}
		    						if(ptr->sibling == NULL){
		    							//printf("Invalid prefix!\n");
	    								return 0;
		    						}
		    						ptr = ptr->sibling;
		    					}
		    				}else{
		    					lastltrptr = ptr->child;
		    					if(i == strlen(searchword)-1){
	    							//printf("Valid prefix!\n");
	    							return 1;
	    						}
		    				}
	    				}
	    			}
	    		}
	
	
	
	return 0;
}


int search(node *head, char *searchword){
	int i;
	node *lastltrptr = NULL;
	node *ptr = NULL;
	
	// if(strlen(searchword) < 3){
	// 	printf("Invalid word length!\n");
	// 	return 0;
	// }
	// if(strlen(searchword) > 30){
	// 	printf("Invalid word length!\n");
	// 	return 0;
	// }
	
			for(i=0; i<strlen(searchword); i++){
	    			if(i == 0){
	    				ptr = head->child;
	    				while(ptr != NULL){
	    					if(ptr->letter == searchword[i]){
	    						lastltrptr = ptr;
	    						if(i == strlen(searchword)-1){
	    							if(lastltrptr->x == 0){
	    								// printf("Valid word!\n");
	    								return 1;
	    							}
	    							else{
	    								// printf("Invalid word!\n");
	    								return 0;
	    							}
	    						}
	    						break;
	    					}
	    					if(ptr->sibling == NULL){
	    						// printf("Invalid word!\n");
	    						return 0;
	    					}
	    					ptr = ptr->sibling;
	    				}
	    			}
	    			else{
	    				ptr = lastltrptr;
	    				if(ptr->child == NULL){
	    					// printf("Invalid word!\n");
	    					return 0;
	    				}
	    				else{
		    				if(ptr->child->letter != searchword[i]){
		    					ptr = ptr->child;
		    					while(ptr != NULL){
		    						if(ptr->letter == searchword[i]){
		    							lastltrptr = ptr;
		    							if(i == strlen(searchword)-1){
			    							if(lastltrptr->x == 0){
			    								// printf("Valid word!\n");
			    								return 1;
			    							}
			    							else{
			    								// printf("Invalid word!\n");
			    								return 0;
			    							}
			    						}
		    							break;
		    						}
		    						if(ptr->sibling == NULL){
		    							// printf("Invalid word!\n");
	    								return 0;
		    						}
		    						ptr = ptr->sibling;
		    					}
		    				}else{
		    					lastltrptr = ptr->child;
		    					if(i == strlen(searchword)-1){
	    							if(lastltrptr->x == 0){
	    								// printf("Valid word!\n");
	    								return 1;
	    							}
	    							else{
	    								// printf("Invalid word!\n");
	    								return 0;
	    							}
	    						}
		    				}
	    				}
	    			}
	    		}
	
	
	
	return;
}

void createTrie(node **head){
	int i;
	char word[30];
    	FILE *fp = fopen ( "TWL06.txt", "r");

	node *lastltrptr = NULL;
	node *ptr = NULL;
    	
    	while(fscanf(fp, "%s", word) != EOF){
	    	if((*head)->child == NULL){	
	    		for(i=0; i<strlen(word); i++){
	    			//printf("Okay\n");
	    			node *temp;
	    			temp = (node *)malloc(sizeof(node));
	    			temp->sibling = temp->child = NULL;
	    			temp->letter = word[i];
	    			temp->x = 1;
	    			
	    			if(i == strlen(word)-1){
	    				temp->x = 0;
	    			}
	    			
	    			if(i == 0){
	    				(*head)->child = temp;
	    			}else{
	    				node *ptr;
	    				ptr = (*head)->child;
	    				while(ptr != NULL){
	    					if(ptr->child == NULL){
	    						ptr->child = temp;
	    						break;
	    					}
	    					
	    					ptr = ptr->child;	
	    				}
	    			}		
	    					
	    		}
	    	}else{
	    		for(i=0; i<strlen(word); i++){
	    			node *temp;
	    			temp = (node *)malloc(sizeof(node));
	    			temp->sibling = temp->child = NULL;
	    			temp->letter = word[i];
	    			temp->x = 1;
	    			
	    			if(i == strlen(word)-1){
	    				temp->x = 0;
	    			}
	    		
	    			if(i == 0){
	    				ptr = (*head)->child;
	    				while(ptr != NULL){
	    					if(ptr->letter == word[i]){
	    						lastltrptr = ptr;
	    						break;
	    					}
	    					if(ptr->sibling == NULL){
	    						ptr->sibling = temp;
	    						lastltrptr = ptr->sibling;
		    					break;
	    					}
	    					ptr = ptr->sibling;
	    				}
	    			}
	    			else{
	    				ptr = lastltrptr;
	    				if(ptr->child == NULL){
	    					ptr->child = temp;
	    					lastltrptr = ptr->child;
	    				}
	    				else{
		    				if(ptr->child->letter != word[i]){
		    					ptr = ptr->child;
		    					while(ptr != NULL){
		    						if(ptr->letter == word[i]){
		    							lastltrptr = ptr;
		    							break;
		    						}
		    						if(ptr->sibling == NULL){
		    							ptr->sibling = temp;
		    							lastltrptr = ptr->sibling;
		    							break;
		    						}
		    						ptr = ptr->sibling;
		    					}
		    				}else{
		    					lastltrptr = ptr->child;
		    				}
	    				}
	    			}
	    		}
	    	}
    	}
    	
    	fclose ( fp );	
    	printf ("Dictionary loaded.\n");
}

void addToOptions(node *triehead, int candidate, char *curString, char *letters, int **option, int *nopts, int move){
	int i, k = 0, temp;
	for(i=1; i<move; i++){								
		temp = option[i][nopts[i]];
		//printf("%d-", temp);								
		if(candidate == temp)
			break;
		curString[k] = letters[temp];
		k++;
	}
	if(i==move){								
		//printf("%d-", candidate);
		curString[k] = letters[candidate];
		curString[k+1] = '\0';
		if (prefix(triehead,curString)==1){
			//printf("Valid Prefix: %s\n", curString);									
			option[move][++nopts[move]] = candidate;
		}
	}
}

int main(){
	int start, move, N, validCount;
	int *nopts, **option;
	char *letters, *tempString, curString[50];
	dict *newWord, *ptr2, *ptr3, *answerKey;
	node *triehead;
	int i, k, l, m, x, y, candidate, prevCandidate, prevCandidateX, prevCandidateY, temp;
	int instances, dimensions;
	FILE *fp;
	int j; //for tracing	


	triehead = (node*)malloc(sizeof(node));
	triehead->sibling = triehead->child = NULL;
	createTrie(&triehead);	

	//read input file
	fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &instances);
	// printf("Instances: %d\n", instances);

	for(m=0; m<instances; m++){
		//read and initialization
		fscanf(fp, "%d\n", &N);
		// printf("N : %d\n", N);
		nopts = (int *) malloc(sizeof(int)*((N*N)+2));
		option = (int **) malloc(sizeof(int*)*((N*N)+2));
		letters = (char *) malloc(sizeof(char)*N);
		for(k=0; k<((N*N)+2); k++){
			option[k] = (int *) malloc(sizeof(int)*((N*N)+2));	
						
		}
		
		letters = (char *) malloc(sizeof(char)*N);	

		tempString = (char *) malloc(sizeof(char)*N);
		answerKey = NULL;

		for(k=0; k<N*N; k++){	//read dictionary file			
			fscanf(fp, "%c ", &letters[k]);
		}
		
		printf("\n=======================================\n");
		printf("Tray # %d (%d x %d)\n", m+1, N, N);
		//start backtracking
		validCount = 0;
		move = start = 0; 
		nopts[start]= 1;

		while (nopts[start] >0)
		{
			if(nopts[move]>0)
			{
				move++;
				nopts[move]=0; //initialize new move

				//print - solution found!
				if(move==(N*N)+1){
					for(i=1;i<move;i++){
						if(option[i][nopts[i]]>-1){
							//printf("%2i,",option[i][nopts[i]]);	//mute -1 value in printing							
							tempString[(i-1)] = letters[option[i][nopts[i]]];
 							
						}else{
							tempString[(i-1)] = '\0';
							break;
						}
					}				
					// printf("\n");

					//check if word is found in the trie
					
					if(search(triehead, tempString)==1){	//found in dictionary						
						newWord = (dict *) malloc(sizeof(dict));
						newWord->next = NULL;
						strcpy(newWord->word, tempString);	

						if(answerKey==NULL){	//answer key is empty
							answerKey = newWord;
							ptr2 = answerKey;
							validCount++;

						}else{	//not empty
							ptr3 = answerKey;
							while(ptr3!=NULL){	//check if word already in answer key
								if(strcmp(ptr3->word, newWord->word)==0){
									break;
								}
								ptr3 = ptr3->next;
							}
							if(ptr3==NULL){		//not in answer key : add
								ptr2->next = newWord;
								ptr2 = ptr2->next;
								validCount++;
							}								
						}
					}								
					
				}
				//populate
				else //find candidates
				{				
					if(move==1){
						for(i=0; i<(N*N); i++)
							option[move][++nopts[move]] = i;
					}else{
						prevCandidate = option[(move-1)][nopts[(move-1)]];
						// printf("Prev Candidate: %d\n", prevCandidate);	 
						if (prevCandidate == -1)	//prev candidate is -1 (" ")
							option[move][++nopts[move]] = -1;
						else{
							prevCandidateX = prevCandidate / N;
							prevCandidateY = prevCandidate % N;
							// printf("prevCandidateX: %d, prevCandidateY: %d\n", prevCandidateX, prevCandidateY);						

							if(prevCandidateX-1>=0 && prevCandidateY-1>=0){	//northeast
								candidate = (prevCandidateX-1)*N + prevCandidateY-1;
								// printf("candidate: %d ? prevCandidate: %d\n", candidate, prevCandidate);
								addToOptions(triehead,candidate, curString, letters, option, nopts, move);
								//printf("\n");	
							}

							if(prevCandidateX-1>=0){	//north		
								candidate = (prevCandidateX-1)*N + prevCandidateY;		
								// printf("candidate: %d ? prevCandidate: %d\n", candidate, prevCandidate);				
								addToOptions(triehead,candidate, curString, letters, option, nopts, move);
								//printf("\n");	
							}

							if(prevCandidateX-1>=0 && prevCandidateY+1<N){	//northwest
								candidate = (prevCandidateX-1)*N + prevCandidateY+1;
								// printf("candidate: %d ? prevCandidate: %d\n", candidate, prevCandidate);	
								addToOptions(triehead,candidate, curString, letters, option, nopts, move);
								//printf("\n");
							}

							if(prevCandidateY-1>=0){	//east
								candidate = prevCandidateX*N + prevCandidateY-1;
								// printf("candidate: %d ? prevCandidate: %d\n", candidate, prevCandidate);	
								addToOptions(triehead,candidate, curString, letters, option, nopts, move);
								//printf("\n");
							}

							if(prevCandidateY+1<N){		//west
								candidate = prevCandidateX*N + prevCandidateY+1;
								// printf("candidate: %d ? prevCandidate: %d\n", candidate, prevCandidate);	
								addToOptions(triehead,candidate, curString, letters, option, nopts, move);
								//printf("\n");
							}
							if(prevCandidateX+1<N && prevCandidateY-1>=0){	//southeast
								candidate = (prevCandidateX+1)*N + prevCandidateY-1;
								// printf("candidate: %d ? prevCandidate: %d\n", candidate, prevCandidate);	
								addToOptions(triehead,candidate, curString, letters, option, nopts, move);
								//printf("\n");
							}
							if(prevCandidateX+1<N){		//south
								candidate = (prevCandidateX+1)*N + prevCandidateY;
								// printf("candidate: %d ? prevCandidate: %d\n", candidate, prevCandidate);	
								addToOptions(triehead,candidate, curString, letters, option, nopts, move);
								//printf("\n");	
							}

							if(prevCandidateX+1<N && prevCandidateY+1<N){	//southwest
								candidate = (prevCandidateX+1)*N + prevCandidateY+1;
								// printf("candidate: %d ? prevCandidate: %d\n", candidate, prevCandidate);	
								addToOptions(triehead,candidate, curString, letters, option, nopts, move);
								//printf("\n");	
							}

							if(move>3)	//at least three letters
								option[move][++nopts[move]] = -1;
						}
					}				

					//for tracing candidate generation
					/*
					printf("Move : %d\n", move);
					for(i=1; i<=move; i++){
						for(j=1; j<=nopts[i]; j++){
					 		if (option[i][j]>-2) printf("%2i,",option[i][j]);
					 	}
					 	printf("\n");
					}printf("===============\n");
					*/
				}
			}
			else 
			{
				//backtrack
				move--;
				nopts[move]--;
			}
		}
		printf("Valid words (unique) : %d\n", validCount);
		ptr2 = answerKey;
		while(ptr2!=NULL){
			printf("%s\n", ptr2->word);
			answerKey = answerKey->next;
			free(ptr2);
			ptr2 = answerKey;
		}
		//free malloc per tray
		free(nopts);
		for(k=0; k<((N*N)+2); k++)
			free(option[k]);
		free(option);		
		free(letters);
	}
	fclose(fp);	//close input file
	
	//free dictionary
	
		
}
