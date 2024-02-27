#include <stdio.h>
#include <stdlib.h>

//initializing the global variables
char **map;//pointer to pointer for the 2D map
int H,W,startrow,startcol,endrow,endcol;/*
H- height of the map
W- width of the map
startrow - row value of starting point of the map
startcol - colomn value of starting point of the map
endrow - row value of the ending point of the map
endcol - colomn value of the ending point of the map
*/
char *string;//pointer to store given string input
int **numberArray;//number array for find shortest path

//function prototype
void MakeMap();//creating a 2D map
int IsTravelAble(int nowrow, int nowcol, int nextrow,int nextcol );//To find if the next cell is a possible move
int Cellcheck(int row, int col);//find if the cell is actually in the 2D array(map)
int shortest(int value);//finding the shortest path
void PrintMap();//Printing the created 2D map(just for debugging purpose)
void Num();//Printing the created numberArray(just for debugging purpose)

//main function
int main(){
    scanf("%d %d",&H,&W);
    scanf("%d %d",&startrow,&startcol);
    scanf("%d %d",&endrow,&endcol);
    //intializing string array(memory allocation)
    string = (char *)malloc(H*W+1);
    scanf("%s",string);

    //intializing the map array and numberArray(memory allocation)
    map = (char **)malloc(H*sizeof(char *));
    numberArray =(int **)malloc(H*sizeof(int *));
    for(int i=0; i<H;i++){
        map[i]=(char *)malloc(W*sizeof(char));
        numberArray[i]=(int *)malloc(W*sizeof(int));
    }

    MakeMap();//creating the map and make every element in numberArray to 0
    numberArray[startrow][startcol]=1;//making the starting point in to 1

    //end result
    if(shortest(1)==-1){
        printf("There is no possible path from %c to %c",map[startrow][startcol],map[endrow][endcol]);
    }
    else{
        printf("The minimum distance from %c to %c is %d",map[startrow][startcol],map[endrow][endcol],shortest(1));
    }
    return 0;
}

//creating a 2D map according to the given string input
void MakeMap(){
    int index=0;
    for(int i=0; i<H;i++){
        for(int j=0;j<W;j++){
            map[i][j]=string[index];
            numberArray[i][j]=0;
            index+=1;
        }
    }
}

//printing the created 2D map(for debugging purpose)
void PrintMap(){
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            printf("%c ",map[i][j]);
            //printf("%d",numberArray[i][j]);
        }
        printf("\n");
    }
}

//printing created 2D numberArray(for debugging purpose)
void Num(){
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){
            //printf("%c ",map[i][j]);
            printf("%d ",numberArray[i][j]);
        }
        printf("\n");
    }
}

//finding if the next move is valid under given conditions
int IsTravelAble(int nowrow, int nowcol, int nextrow,int nextcol ){
    if(map[nextrow][nextcol]-map[nowrow][nowcol]<=2 && map[nowrow][nowcol]-map[nextrow][nextcol]<=3){
        return 1;
    }
    else{
        return 0;
    }
}

//finding if the given cell is exist on the map
int Cellcheck(int row, int col){
    if((row>=0 && row<H)&&(col>=0 && col<W )){
        return 1;
    }
    else{
        return 0;
    }
}

//finding the shortest path from starting point to the end point
int shortest(int value){
    for(int i=0;i<H;i++){
        for(int j=0;j<W;j++){

        //base case
        if(numberArray[endrow][endcol]!=0 || value > H*W){
                    return numberArray[endrow][endcol]-1;
                }
            //checking every possible move is valid
            if(numberArray[i][j]==value){

                    //move right
                    if(Cellcheck(i,j+1)&&IsTravelAble(i,j,i,j+1)&&numberArray[i][j+1]==0){
                        numberArray[i][j+1]=value+1;
                    }
                    //move left
                    if(Cellcheck(i,j-1)&&IsTravelAble(i,j,i,j-1)&&numberArray[i][j-1]==0){
                        numberArray[i][j-1]=value+1;
                    }
                    //move down
                    if(Cellcheck(i+1,j)&&IsTravelAble(i,j,i+1,j)&&numberArray[i+1][j]==0){
                        numberArray[i+1][j]=value+1;
                    }
                    //move up
                    if(Cellcheck(i-1,j)&&IsTravelAble(i,j,i-1,j)&&numberArray[i-1][j]==0){
                        numberArray[i-1][j]=value+1;
                    }
            }
        }
    }
    //reccurence
    return shortest(value+1);
}




