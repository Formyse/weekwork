int rob(int* nums, int numsSize){
int dp0=0;
int dp1=nums[0];
int temp;
if(numsSize==0)
return 0;
for(int i=1;i<numsSize;i++){
    temp=fmax(dp0,dp1);
    dp1=dp0+nums[i];
    dp0=temp;
}
return fmax(dp0,dp1);
}
