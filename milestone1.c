
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
	char word[45];	//estimate; change to max possible word len //optimized -> word = (char*) malloc(sizeof(char)*(N*N))
	struct node *next;
}dict;

int main(){
	int start, move, N, validCount;
	int *nopts, **option;
	char **letters, *tempString;
	dict *head, *newWord, *ptr, *ptr2, *ptr3, *answerKey;
	int i, k, l, m, x, y, candidate, prevCandidate, prevCandidateX, prevCandidateY;
	int instances, dimensions;
	FILE *fp;
	int j; //for tracing	

	head = NULL;	

	// read dictionary
	fp = fopen("TWL06.txt", "r");
	while(!feof(fp)){
		newWord = (dict *) malloc(sizeof(dict));
		newWord->next = NULL;
		fscanf(fp, "%s", newWord->word);
		// printf("%s, ", newWord->word);
		if(head==NULL){
			head = newWord;
			ptr = head;
		}else{
			ptr->next = newWord;
			ptr = ptr->next;
		}		

	}
	fclose(fp);

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
		letters = (char **) malloc(sizeof(char*)*N);
		for(k=0; k<((N*N)+2); k++){
			option[k] = (int *) malloc(sizeof(int)*((N*N)+2));	
						
		}
		for(k=0; k<N; k++)
			letters[k] = (char *) malloc(sizeof(char)*N);	

		tempString = (char *) malloc(sizeof(char)*N);
		answerKey = NULL;

		for(k=0; k<N; k++){	//read dictionary file
			for(l=0; l<N; l++){
				fscanf(fp, "%c ", &letters[k][l]);
				// printf("%c", letters[k][l]);				
			}
			// printf("\n");
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
							x = option[i][nopts[i]] / N;
							y = option[i][nopts[i]] % N;
							// printf("%c,", letters[x][y]);
							tempString[(i-1)] = letters[x][y];
 							
						}else{
							tempString[(i-1)] = '\0';
							break;
						}
					}
					// printf("\n");

					//check if word is found in the dictionary
					ptr=head;
					while(ptr!=NULL){	//traverse dictionary
						if(strcmp(tempString, ptr->word)==0){	//found in dictionary
							// printf("curword: %s, dictword: %s\n", tempString, ptr->word);
							// printf("Valid word: %s\n", tempString);
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
							break;
						}
						ptr = ptr->next;
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

							//todo: future optimization check if current prefix (prevCandidates+candidate) is found in the dictionary (up to first 4 letters?)

							if(prevCandidateX-1>=0 && prevCandidateY-1>=0){	//northeast
								candidate = (prevCandidateX-1)*N + prevCandidateY-1;
								// printf("candidate: %d ? prevCandidate: %d\n", candidate, prevCandidate);	
								for(i=move-1; i>=1; i--)
									if(candidate == option[i][nopts[i]])
										break;						
								if (i==0)
									option[move][++nopts[move]] = candidate;
							}

							if(prevCandidateX-1>=0){	//north		
								candidate = (prevCandidateX-1)*N + prevCandidateY;		
								// printf("candidate: %d ? prevCandidate: %d\n", candidate, prevCandidate);				
								for(i=move-1; i>=1; i--)
									if(candidate == option[i][nopts[i]])
										break;						
								if (i==0)
									option[move][++nopts[move]] = candidate;
							}

							if(prevCandidateX-1>=0 && prevCandidateY+1<N){	//northwest
								candidate = (prevCandidateX-1)*N + prevCandidateY+1;
								// printf("candidate: %d ? prevCandidate: %d\n", candidate, prevCandidate);	
								for(i=move-1; i>=1; i--)
									if(candidate == option[i][nopts[i]])
										break;						
								if (i==0)
									option[move][++nopts[move]] = candidate;
							}

							if(prevCandidateY-1>=0){	//east
								candidate = prevCandidateX*N + prevCandidateY-1;
								// printf("candidate: %d ? prevCandidate: %d\n", candidate, prevCandidate);	
								for(i=move-1; i>=1; i--)
									if(candidate == option[i][nopts[i]])
										break;						
								if (i==0)
									option[move][++nopts[move]] = candidate;
							}

							if(prevCandidateY+1<N){		//west
								candidate = prevCandidateX*N + prevCandidateY+1;
								// printf("candidate: %d ? prevCandidate: %d\n", candidate, prevCandidate);	
								for(i=move-1; i>=1; i--)
									if(candidate == option[i][nopts[i]])
										break;						
								if (i==0)
									option[move][++nopts[move]] = candidate;
							}
							if(prevCandidateX+1<N && prevCandidateY-1>=0){	//southeast
								candidate = (prevCandidateX+1)*N + prevCandidateY-1;
								// printf("candidate: %d ? prevCandidate: %d\n", candidate, prevCandidate);	
								for(i=move-1; i>=1; i--)
									if(candidate == option[i][nopts[i]])
										break;						
								if (i==0)
									option[move][++nopts[move]] = candidate;
							}
							if(prevCandidateX+1<N){		//south
								candidate = (prevCandidateX+1)*N + prevCandidateY;
								// printf("candidate: %d ? prevCandidate: %d\n", candidate, prevCandidate);	
								for(i=move-1; i>=1; i--)
									if(candidate == option[i][nopts[i]])
										break;						
								if (i==0)
									option[move][++nopts[move]] = candidate;
							}

							if(prevCandidateX+1<N && prevCandidateY+1<N){	//southwest
								candidate = (prevCandidateX+1)*N + prevCandidateY+1;
								// printf("candidate: %d ? prevCandidate: %d\n", candidate, prevCandidate);	
								for(i=move-1; i>=1; i--)
									if(candidate == option[i][nopts[i]])
										break;						
								if (i==0)
									option[move][++nopts[move]] = candidate;
							}

							if(move>3)	//at least three letters
								option[move][++nopts[move]] = -1;
						}
					}				

					// for tracing candidate generation
					// printf("Move : %d\n", move);
					// for(i=1; i<=move; i++){
					// 	for(j=1; j<=nopts[i]; j++){
					// 		if (option[i][j]>-2) printf("%2i,",option[i][j]);
					// 	}
					// 	printf("\n");
					// }printf("===============\n");
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
		for(k=0; k<N; k++)
			free(letters[k]);
		free(letters);

	}
	fclose(fp);
	
	//free dictionary
	ptr = head;
	while(ptr!=NULL){
		head = head->next;
		free(ptr);
		ptr = head;
	}
		
}
