#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//initializing the global variables
char **map;//pointer to pointer for the 2D map
int H,W;/*
H- height of the map
W- width of the map
startrow - row value of starting point of the map
startcol - colomn value of starting point of the map
endrow - row value of the ending point of the map
endcol - colomn value of the ending point of the map
*/
char *string;//pointer to store given string input
int **numberArray;//number array for find shortest path
int arr[1000];//an array to store fibonacci numbers we found in the fin function for optimization

//function prototype
void MakeMap();//creating a 2D map
int IsTravelAble(int nowrow, int nowcol, int nextrow,int nextcol );//To find if the next cell is a possible move
int Cellcheck(int row, int col);//find if the cell is actually in the 2D array(map)
int shortest(int value, int endrow,int endcol);//finding the shortest path
void PrintMap();//Printing the created 2D map(just for debugging purpose)
void Num();//Printing the created numberArray(just for debugging purpose)
int finding_value(int row_nnumber,int col_number);
int fin(int n);
int smallest(int d[4]);
int pathvalue(int v1, int v2);

//main function
int main(){
    //distance array
    int distance[6],coordinates[4][2],fibonacci[2],n,**portal_coordinates;
    /*  distance[0]=distance between starting point and the ending point
        distance[1]=distance between starting point and the first portal
        distance[2]=distance between starting point and the second portal
        distance[3]=distance between ending point and the first portal
        distance[4]=distance between ending point and the second portal

        coordinates[0][0]=starting row      coordinates[0][1]=starting col
        coordinates[1][0]=ending row        coordinates[1][1]=ending col
        coordinates[2][0]=portal 1 row      coordinates[2][1]=portal 1 col
        coordinates[3][0]=portal 2 row      coordinates[3][1]=portal 2 col
    */
    //making every element in distance array a -1
    for(int i=0;i<6;i++){
        distance[i]=-1;
    }
    scanf("%d %d",&H,&W);
    scanf("%d %d",&coordinates[0][0],&coordinates[0][1]);
    scanf("%d %d",&coordinates[1][0],&coordinates[1][1]);
    //intializing string array(memory allocation)
    string = (char *)malloc(H*W+1);
    scanf("%s",string);
    //taking numbers to check fibonacci
    for(int i=0;i<2;i++){
        scanf("%d",&fibonacci[i]);
    }
    //number of coordintes to find if its a magical door
    scanf("%d",&n);

    //intializing portal_coordinaes array
    portal_coordinates=(int*)malloc(n*sizeof(int*));
    for(int i=0;i<n;i++){
        portal_coordinates[i]=(int*)malloc(2*sizeof(int));
    }

    for(int i=0;i<n;i++){
        scanf("%d %d",&portal_coordinates[i][0],&portal_coordinates[i][1]);
    }

    //intializing the map array and numberArray(memory allocation)
    map = (char **)malloc(H*sizeof(char *));
    numberArray =(int **)malloc(H*sizeof(int *));
    for(int i=0; i<H;i++){
        map[i]=(char *)malloc(W*sizeof(char));
        numberArray[i]=(int *)malloc(W*sizeof(int));
    }

     for(int i=0;i<100;i++){
        arr[i]=-1;
    }
    //finding and adding portal coordinates
    int portalNumber=0;
    for(int i=0;i<n;i++){

        //printf("portal values are %d\n",fin(finding_value(portal_coordinates[i][0],portal_coordinates[i][1])));
        if(portalNumber<2){
          if((fin(finding_value(portal_coordinates[i][0],portal_coordinates[i][1]))==fibonacci[0])||(fin(finding_value(portal_coordinates[i][0],portal_coordinates[i][1]))==fibonacci[1])){
            coordinates[portalNumber+2][0]=portal_coordinates[i][0];
            coordinates[portalNumber+2][1]=portal_coordinates[i][1];
            portalNumber+=1;
            //printf("%d \n",portalNumber);
        }
        //else{
          //  break;
        //}
        }

    }
     /*for(int i=0;i<4;i++){
        for(int j=0;j<2;j++){
            //printf("%c ",map[i][j]);
            printf("%d ",coordinates[i][j]);
        }
        printf("\n");
    }*/

    //distance from start to end
    MakeMap();//creating the map and make every element in numberArray to 0
    numberArray[coordinates[0][0]][coordinates[0][1]]=1;//making the starting point in to 1
    if(shortest(1,coordinates[1][0],coordinates[1][1])==-1){
        distance[0]=-1;
    }
    else{
        distance[0]= shortest(1,coordinates[1][0],coordinates[1][1]);
    }


    if(portalNumber>0){
        // distance from start to portal 1
        MakeMap();
        numberArray[coordinates[0][0]][coordinates[0][1]]=1;
        if(shortest(1,coordinates[2][0],coordinates[2][1])==-1){
            distance[1]=-1;
        }
        else{
            distance[1]= shortest(1,coordinates[2][0],coordinates[2][1]);
        }


        //distance from portal 1 to end
        MakeMap();
        numberArray[coordinates[2][0]][coordinates[2][1]]=1;
        if(shortest(1,coordinates[1][0],coordinates[1][1])==-1){
            distance[3]=-1;
        }
        else{
            distance[3]= shortest(1,coordinates[1][0],coordinates[1][1]);
        }
    }



    if(portalNumber>1){
        //distance from start to portal 2
        MakeMap();
        numberArray[coordinates[0][0]][coordinates[0][1]] = 1;
        if (shortest(1, coordinates[3][0], coordinates[3][1]) == -1) {
            distance[2] = -1;
        } else {
            distance[2] = shortest(1, coordinates[3][0], coordinates[3][1]);
        }


        //distance from portal 2 to end
        MakeMap();
        numberArray[coordinates[3][0]][coordinates[3][1]]=1;
        if(shortest(1,coordinates[1][0],coordinates[1][1])==-1){
            distance[4]=-1;
        }
        else{
            distance[4]= shortest(1,coordinates[1][0],coordinates[1][1]);
        }
    }

    //printing the distances
    /*printf("distances are  ");
    for(int i=0;i<5;i++){
        printf("%d ",distance[i]);
    }*/
    int dist[3];
    dist[0]=pathvalue(distance[0],0);
    dist[1]=pathvalue(distance[1],distance[4]);
    dist[2]=pathvalue(distance[2],distance[3]);
    if(smallest(dist)==(H*W*2)){
        printf("There is no possible path from %c to %c",map[coordinates[0][0]][coordinates[0][1]],map[coordinates[1][0]][coordinates[1][1]]);
    }
    else{
       printf("The minimum distance from %c to %c is %d",map[coordinates[0][0]][coordinates[0][1]],map[coordinates[1][0]][coordinates[1][1]],smallest(dist));
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
int shortest(int value,int endrow,int endcol){
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
    return shortest(value+1,endrow,endcol);
}

int fin(int n){
    //if n=0 or n=1 return 0 and 1 respectivly
    if(n<=1){
        return n;
    }
    //if the number exist in arr returning the value
    if(arr[n]!=-1){
        return arr[n];
    }
    //if the number doesnt in the arr, adding the number in to the arr
    arr[n]= fin(n-1)+fin(n-2);
    return arr[n];
}

int finding_value(int row_nnumber,int col_number){

    return row_nnumber*W+col_number;
}


int smallest(int d[3]){
    int small=d[0];
    for(int i=0;i<3;i++){
        if(small>d[i]){
            small = d[i];
        }
    }
    return small;
}

int pathvalue(int v1, int v2){
    if((v1+v2)<0){
        return H*W*2;
    }
    if((v1+v2)<(abs(v1)+abs(v2))){
        return H*W*2;
    }
    else{
        return v1+v2;
    }
}





