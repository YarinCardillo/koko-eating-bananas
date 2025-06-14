/*
📍 LeetCode #875
🔗 https://leetcode.com/problems/koko-eating-bananas/

🐒 Koko loves to eat bananas. There are n piles of bananas, the ith pile has piles[i] bananas. 
The guards have gone and will come back in h hours.
Koko can decide her bananas-per-hour eating speed of k. Each hour, she chooses some pile of
bananas and eats k bananas from that pile. If the pile has less than k bananas, she eats all 
of them instead and will not eat any more bananas during this hour.
Koko likes to eat slowly but still wants to finish eating all the bananas before the guards 
return.

💡Return the minimum integer k such that she can eat all the bananas within h hours.

Example 1:
Input: piles = [3,6,7,11], h = 8
Output: 4

Example 2:
Input: piles = [30,11,23,4,20], h = 5
Output: 30

Example 3:
Input: piles = [30,11,23,4,20], h = 6
Output: 23
 

Constraints:

1 <= piles.length <= 10^4
piles.length <= h <= 10^9
1 <= piles[i] <= 10^9

*/



#include "stdio.h"
#include "stdlib.h"


int isFeasible(int* piles, int pilesSize, int h, int speed){


    //check if it is possible to eat all piles with given speed in h hours
    long long countHours = 0;
    for(int i=0; i<pilesSize; i++){
        //calculate hours needed for each pile
        countHours += ((long long)piles[i] + speed - 1) / speed; // equivalent to ceil(piles[i] / speed)
    }
    
    
    //alternative more comprehensible way to calculate hours needed for each pile
    /*
    int countHours = 0;
    int load = 0;
    //load is the current load of bananas in the current hour
    if(speed == 0) return 0; //if speed is 0, we cannot eat any bananas
    //count hours needed to eat all piles with given speed
    for(int i=0; i<pilesSize; i++){
        load = piles[i];
        if(load > speed)
            countHours++;
        countHours++;
        
    }
*/

    return countHours <= h;
}



int minEatingSpeed(int* piles, int pilesSize, int h) {
    

    if(piles == NULL || pilesSize < 1 || pilesSize > 10000 || h < 1 || h > 1000000000) {
        return -1;
    }


    //if there is only one pile, give result immediately
    if(pilesSize == 1) {
        return (piles[0] + h - 1) / h; // equivalent to ceil(piles[0] / h)
    }


    //find interval extremes
    long long right = 0;
    long long left = 1;
    long long mid = 0;
    
    for(int i=0; i<pilesSize; i++){
        right+=piles[i];
    }

    
    if(right == 0) return -2; //if all piles are empty, return 0
    if(h == 0) return -3; //if no hours are given, return -1


    //binary iterative search
    while(left<right){

        mid = left + (right-left)/2;
        if(isFeasible(piles, pilesSize, h, mid))
            right = mid;
        else
            left = mid+1;
    }


    return (int)left;
}



int main(){


    int piles[] = {30,11,23,4,20};
    int n = sizeof(piles) / sizeof(int);
    int hours = 6;
    printf("Min eating speed: %d", minEatingSpeed(piles, n, hours));


    return 0;
}