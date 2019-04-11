#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lodepng.c"

//PROJECT PART 1 (ENCRYPTION)

char maxStr[255];
int randArr[255];

int inputFunction();
void randomArrayFunction(int sizeOfStr);
void arraySortMethod(int sizeOfStr);
int targetRedDefineMethod(int sizeOfStr);
void encryptionMethod(int targetRedValue, int sizeOfStr);

void encrypritonMethod(int targetRedValue, int sizeOfStr)
{
	/*
	
	file's name MUST be : image.png otherwise, it does not read the file
	
	reads image as an array. Values are sorted like this:
	arr[0] = 0,0 pixel's Red value
	arr[1] = 0,0 pixel's Green value
	arr[2] = 0,0 pixel's Blue value
	arr[3] = 0,0 pixel's A value
	arr[4] = 0,1 pixel's R value
	.
	.
	.
	
	*/
	unsigned error, width, height;
	unsigned char* image;
	
	int i, randomPixel, redValue, greenValue, blueValue;
	
	error = lodepng_decode32_file(&image, &width, &height, "image.png");
	
	if(error)
		printf("error %u: %s\n", error, lodepng_error_text(error));
	
	//check all pixels if any of them has the TargetRedValue on Red. If so, increase this pixel's value by 1.
	for(i = 1; i < width*height; i++)
	{
		if(image[4*i] == targetRedValue)
		{
			image[4*i]++;
		}
	}
	
	//assign sizeOfStr to the Red of 0,0 pixel
	image[0] = sizeOfStr;
	//assign targetRedValue to the Green of 0,0 pixel
	image[1] = targetRedValue;

	for(i = 0; i < sizeOfStr; i++)
	{
		randomPixel = ((rand() % width) * (rand() % height)) + 1;
		
		//assign targetRedValue to Red
		redValue = randomPixel * 4;
		image[redValue] = targetRedValue;
		
		//assign messageStr[i] (ASCII value) to Green
		greenValue = (randomPixel * 4) + 1;
		image[greenValue] = maxStr[i];
		
		//assign randArr[i] to Blue
		blueValue = (randomPixel * 4) + 2;
		image[blueValue] = randArr[i];
	}
	
	//encode image array into the file
	error = lodepng_encode32_file("image.png", image, width, height);
	
	if(error)
		printf("error %u: %s\n", error, lodepng_error_text(error));
	
	printf("Your message is succesfully encrypted.\n");
}

int main()
{	
	srand(time(NULL));
	
	int sizeOfStr, targetRedValue;

	sizeOfStr = inputFunction();
	
	targetRedValue = targetRedDefineMethod(sizeOfStr);
	
	randomArrayFunction(sizeOfStr);
	
	arraySortMethod(sizeOfStr);
	
	encrypritonMethod(targetRedValue, sizeOfStr);
	
	return 0;
}

int inputFunction()
{
	//this function takes a string input from user. If it's size is invalid, asks for another input
	
	int sizeCounter, i;
	
	while(1)
	{
		printf("Enter the message you want to hide(Must be 1-255 characters long): \n");
		
		gets(maxStr);
		
		sizeCounter = 0;
		sizeCounter = strlen(maxStr);
		
		printf("Message lenght is: %d\n", sizeCounter);
		
		if(sizeCounter == 0 || sizeCounter > 255)
		{
			//do nothing
		}
		else
		{
			//if message length is not invalid, get out of the loop and finish taking input.
			break;
		}
	}
	
	return sizeCounter;
	
}
void randomArrayFunction(int sizeOfStr)
{
	int randomValue, i, j, compareCount;
	int firstValueCheck = 1;
	randomValue = rand() % 256;
	
	//Here, I filled my arrray with random values.
	for(i = 0; i < sizeOfStr; i++)
	{
		randomValue = rand() % 256;
		randArr[i] = randomValue;
		
		//If any value inside the array is equal to the new random value, I filled it with another random value. If again so, did it again.
		compareCount = 0;
		while(firstValueCheck == 0)
		{
			for(j = 0; j < sizeOfStr; j++)
			{
				
				//it encounters itself during the compare. If final condition of compare count is greater than 1, there are equal numbers inside.
				if(randArr[i] == randArr[j])
					compareCount++;
					
				if(compareCount > 1)
				{
					randomValue = rand() % 256;
					randArr[i] = randomValue;
					compareCount = 0;
				}
			}
			
			compareCount = 0;
			//checked again if there is any equal value in array. If so, loop it again.
			//If final condition of compare count is greater than 1, there are equal numbers inside.
			for(j = 0; j < sizeOfStr; j++)
			{
				
				if(randArr[i] == randArr[j])
				{
					compareCount++;
				}
			}
			
			//if the comparement does not encounter any equal value except itself, loop ends with an break
			if(compareCount < 2)
			{
				break;
			}	
		}
		
		//Simple protection to avoid an out of boundary exception.
		if(firstValueCheck == 1)
			firstValueCheck = 0;
	}
}

void arraySortMethod(int sizeOfStr)
{
	int i, j, temp;
	//here I sorted my array with bubble sort algorithm
	for(i = 1; i <= sizeOfStr; i += 1)
	{
		for(j = 0; j < sizeOfStr - 1; j += 1)
		{
			if(randArr[j] > randArr[j + 1])
			{
				temp = randArr[j];
				randArr[j] = randArr[j + 1];
				randArr[j + 1] = temp;
			}
		}
	}
}

int targetRedDefineMethod(int sizeOfStr)
{
	int targetRed;
	
	//here I assigned a random value to my targetRedValue
	
	while(1)
	{
		targetRed = rand() % 256;
		if(targetRed != sizeOfStr)
			break;
	}
	
	return targetRed;
}
