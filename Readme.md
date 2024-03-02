# Finding the shortest path

This project shows use of flood filing methode to find a shortest path of a given map(gien as a matrix). Each milestone based on defferent constrains given in the project.
## Constraints

The map is given as a matrix of charactors,where we can move only;
 1) In a single move, you can go to the next cell, up, down, left or right. (No diagonal moves).
 2) If you are in a cell with character (C1), you need to go to the new cell with character(C2). The only way you can move is ASCII(C2) - ASCII(C1) <= 2 (Climbing) orASCII(C1) - ASCII(C2) <= 3 (Going down). Otherwise, you can't move to that cell.         

## Milestone 1

Shortest path function gave the shortest path if exists otherwise -1.
~~~c
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
~~~
This is a reccursive methode, which recursively checking every possible path and numbering them. This methode is more similer to the Bredth First searching methode.
parameters in the code will described in the first .c file.

Test case 0 </br>
Input </br>
5 4 </br>
0 0 </br>
4 2 </br>
ABCCDGLCKEZZBLFXYCMGDVEGH </br>

Output </br>
The minimum distance from A to E is 6

Test case 1</br>
5 5</br>
0 0</br>
4 4</br>
KKKKKMMMMMOOOOOLLLLLIIIII</br>

Output</br>
The minimum distance from K to I is 8

Test case 2</br>
6 6</br>
5 5</br>
3 3</br>
AAAAAAAFFFFAAFFFFAAFFBAAAFFFFFAAAAAA</br>

Output</br>
The minimum distance from A to B is 20



## Milestone 2

In milestone 2 there was an assumption that there is a magic door which help user to telepote from one door to another.

Below code snippet will show the developed shortest path funtion

```C
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

```

Since avalability of the path became complex following methode is used, where we compare sum of point to point distance with the sum of modules point to point distance
```C
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

```
```C
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
```

