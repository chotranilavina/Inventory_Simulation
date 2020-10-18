#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>

void main()
{
	float Total_HoldingCost[30], Daily_Demand[30], Monthly_Demand[30], Initial_Inventory[30], Final_Inventory[30], Holding_Cost[30], THC;
	float PDF[6]= {0.1,0.2,0.2,0.3,0.1,0.1};
	float CDF[6]= {0,0,0,0,0,0};
	CDF[0]= PDF[0];
	int i, j, DAY;
	for(i=1; i<sizeof(PDF); i++)
		CDF[i]= PDF[i]+CDF[i-1];
	int RAND_NO[30];
	float RAND_NUM[30];
	srand(time(NULL));
	printf("\nRandom Numbers\n\n");
	for(i=0;i<30;i++){
		printf("%3d|",i+1);
	}
	printf("\n");
	for(i=0;i<30;i++){
		RAND_NO[i]=rand() % 100;
		printf("%3d|",RAND_NO[i]);
	}
	printf("\n");
	Initial_Inventory[0]=3;
	Total_HoldingCost[-1]=0;
	THC=0;
	for(DAY=0; DAY<30; DAY++){
		for(j=0; j<sizeof(CDF); j++){
			RAND_NUM[DAY]=(float)RAND_NO[DAY]/100;
			if((float)RAND_NUM[DAY]<CDF[j]){
				Monthly_Demand[DAY]=j;
				Daily_Demand[DAY]=(float)j/30;
				break;
			}
		}
		Final_Inventory[DAY]=Initial_Inventory[DAY]-Daily_Demand[DAY];
		if(Final_Inventory[DAY]>=0){
			Holding_Cost[DAY]=Final_Inventory[DAY]/30;
			Initial_Inventory[DAY+1]=Final_Inventory[DAY];
		}
		else{
			Holding_Cost[DAY]=0;
			Initial_Inventory[DAY+1]=0;
		}
		Total_HoldingCost[DAY]=Total_HoldingCost[DAY-1]+Holding_Cost[DAY];
		THC= THC+Holding_Cost[DAY];
	}
	printf("\n| %4s | %6s | %6s | %8s | %8s | %8s | %8s | %8s | %8s |\n","#Day","Init Inv","RandNo","RandNum","MonthDem","DailyDem","FinalInv","HoldCost","T H Cost");
	for(DAY=0;DAY<30;DAY++)
		printf("\n| %4d | %6f | %6d | %f | %f | %f | %f | %f | %f |",DAY+1,Initial_Inventory[DAY],RAND_NO[DAY],RAND_NUM[DAY],Monthly_Demand[DAY],Daily_Demand[DAY],Final_Inventory[DAY],Holding_Cost[DAY],Total_HoldingCost[DAY]);
	printf("\nTotal Holding Cost = %f per month",THC);
	printf("\nTotal Holding Cost = %f per day",(float)THC/30);
}
