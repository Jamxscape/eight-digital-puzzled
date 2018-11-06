package writeHTML;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Scanner;
import java.util.Stack;

public class test {//广度优先搜索

    class EightNumNode{
        int[][] numMap;    //eight num map
        int x;          //the space coordinate in lateral
        int y;            //the space coordinate in vertical
        int parentID;    //the ID of parent(the ID is the index in the closeList)
        int selfID;        //the ID of itself
    }

    public static EightNumNode beginStat;
    public static EightNumNode endStat;
    public static Queue<EightNumNode> openList;
    public static ArrayList<EightNumNode> closeList; 
    public static Stack<EightNumNode> pathStack;
    
    public int findSpaceX(int[][] M){
        for(int i=0; i<M.length; i++)
            for(int j=0; j<M[0].length; j++)
                if(M[i][j] == 0)
                    return i;
        return -1;
    }
    
    public int findSpaceY(int[][] M){
        for(int i=0; i<M.length; i++)
            for(int j=0; j<M[0].length; j++)
                if(M[i][j] == 0)
                    return j;
        return -1;
    }
    
    public boolean checkSame(int[][] A, int[][] B){
        for(int i=0; i<A.length; i++)
            for(int j=0; j<A[0].length; j++)
                if(A[i][j] != B[i][j])
                    return false;
        return true;
    }
    
    public void printMap(int[][] M){
        for(int i=0; i<M.length; i++){
            for(int j=0; j<M[0].length; j++){
                System.out.print(M[i][j]+" ");
            }
            System.out.println();
        }
    }
    
    public boolean expendPointN(EightNumNode par){
        if(par.y-1 >= 0){//move left
            EightNumNode son = new EightNumNode();
            son.numMap = new int[3][3];
            for(int i=0; i<par.numMap.length; i++)
                for(int j=0; j<par.numMap[0].length; j++)
                    son.numMap[i][j] = par.numMap[i][j];
            son.numMap[par.x][par.y] = son.numMap[par.x][par.y-1];
            son.numMap[par.x][par.y-1] = 0;
            son.x = par.x;
            son.y = par.y-1;
            son.parentID = par.selfID;
            if(par.parentID == -1){
                openList.offer(son);
            }
            else {
                if(!checkSame(son.numMap, closeList.get(par.parentID).numMap))
                    openList.offer(son);
            }
            if(checkSame(son.numMap, endStat.numMap)){
                pathStack.push(son);
                return true;
            }
        }
        if(par.x-1 >= 0){//move up
            EightNumNode son = new EightNumNode();
            son.numMap = new int[3][3];
            for(int i=0; i<par.numMap.length; i++)
                for(int j=0; j<par.numMap[0].length; j++)
                    son.numMap[i][j] = par.numMap[i][j];
            son.numMap[par.x][par.y] = son.numMap[par.x-1][par.y];
            son.numMap[par.x-1][par.y] = 0;
            son.x = par.x-1;
            son.y = par.y;
            son.parentID = par.selfID;
            if(par.parentID == -1){
                openList.offer(son);
            }
            else {
                if(!checkSame(son.numMap, closeList.get(par.parentID).numMap))
                    openList.offer(son);
            }            
            if(checkSame(son.numMap, endStat.numMap)){
                pathStack.push(son);
                return true;
            }
        }
        if(par.y+1 < 3){//move right
            EightNumNode son = new EightNumNode();
            son.numMap = new int[3][3];
            for(int i=0; i<par.numMap.length; i++)
                for(int j=0; j<par.numMap[0].length; j++)
                    son.numMap[i][j] = par.numMap[i][j];
            son.numMap[par.x][par.y] = son.numMap[par.x][par.y+1];
            son.numMap[par.x][par.y+1] = 0;
            son.x = par.x;
            son.y = par.y+1;
            son.parentID = par.selfID;
            if(par.parentID == -1){
                openList.offer(son);
            }
            else {
                if(!checkSame(son.numMap, closeList.get(par.parentID).numMap))
                    openList.offer(son);
            }
            if(checkSame(son.numMap, endStat.numMap)){
                pathStack.push(son);
                return true;
            }
        }
        if(par.x+1 < 3){//move down
            EightNumNode son = new EightNumNode();
            son.numMap = new int[3][3];
            for(int i=0; i<par.numMap.length; i++)
                for(int j=0; j<par.numMap[0].length; j++)
                    son.numMap[i][j] = par.numMap[i][j];
            son.numMap[par.x][par.y] = son.numMap[par.x+1][par.y];
            son.numMap[par.x+1][par.y] = 0;
            son.x = par.x+1;
            son.y = par.y;
            son.parentID = par.selfID;
            if(par.parentID == -1){
                openList.offer(son);
            }
            else {
                if(!checkSame(son.numMap, closeList.get(par.parentID).numMap))
                    openList.offer(son);
            }
            if(checkSame(son.numMap, endStat.numMap)){
                pathStack.push(son);
                return true;
            }
        }
        return false;
    }
    
    public void driver(int[][] beginM, int[][] endM){
        
        openList = new LinkedList<test.EightNumNode>(); 
        closeList = new ArrayList<test.EightNumNode>();
        pathStack = new Stack<test.EightNumNode>();
        //set the begin state
        beginStat = new EightNumNode();
        beginStat.numMap = beginM;
        beginStat.x = findSpaceX(beginM);
        beginStat.y = findSpaceY(beginM);
        beginStat.parentID = -1;
        //set the end state
        endStat = new EightNumNode();
        endStat.numMap = endM;
        endStat.x = findSpaceX(endM);
        endStat.y = findSpaceY(endM);
        endStat.parentID = -1;
        
        openList.offer(beginStat);
        EightNumNode n;
        int idcount = 0;
        while (!openList.isEmpty()) {
            n = openList.remove();
            closeList.add(n);
            n.selfID = idcount++;
            if (expendPointN(n)) {
                System.out.println("Success!!!");
                break;
            }
        }
        
        if (openList.isEmpty()) {
            System.out.println("Fail!!!");
        } else {
            int tempParID = pathStack.peek().parentID;
            EightNumNode tempNode;
            while(tempParID != -1){
                tempNode = closeList.get(tempParID);
                pathStack.push(tempNode);
                tempParID = tempNode.parentID;
            }
            System.out.println("The path from beginning to end:");
            int i=0;
            while(!pathStack.empty()){
                System.out.println("step "+(i++));
                printMap(pathStack.pop().numMap);
                System.out.println();
            }
            
        }
    }
    
    public static void main(String[] args) {
        Scanner scan = new Scanner(System.in);
        System.out.println("Please input the beginMAP:");
        int[][] beginMap = new int[3][3];
        for(int i=0; i<beginMap.length; i++)
            for(int j=0; j<beginMap[0].length; j++)
                beginMap[i][j] = scan.nextInt();
        System.out.println("Please input the endMAP:");
        int[][] endMap = new int[3][3];
        for(int i=0; i<endMap.length; i++)
            for(int j=0; j<endMap[0].length; j++)
                endMap[i][j] = scan.nextInt();
/*       int[][] beginMap = { { 2, 8, 3 }, 
                              { 1, 0, 4 }, 
                              { 7, 6, 5 } };
        int[][] endMap = { { 1, 2, 3 }, 
                            { 8, 0, 4 }, 
                            { 7, 6, 5 } };
*/
        test t = new test();
        if(t.checkSame(beginMap, endMap)){
            System.out.println("The beginMap and endMap are the same.");
            System.out.println("No need to move!");
        }
        else{
            t.driver(beginMap, endMap);
        }
        
    } 

}
