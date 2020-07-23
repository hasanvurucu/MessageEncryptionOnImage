#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lodepng.c"

int decryptionFunction();
void arraySortMethod(int sizeOfStr);



int randValues[255];
char messageArr[255];

int main()
{
	int messageLength, i;
	
	messageLength = decryptionFunction();
	
	arraySortMethod(messageLength);
	
	printf("The hidden message: ");
	
	//prints the message hidden inside the picture
 	for(i = 0; i < messageLength; i++)
 	{
 		printf("%c", messageArr[i]);
	}
	printf("\n");
	
	return 0;
}

int decryptionFunction()
{
	
	/*
	
	file's name MUST be : encryptedGiven.png otherwise, it does not read the file
	
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
	unsigned error;
 	unsigned char* image;
  	unsigned width, height;
  	int targetRedValue, messageLength, i, count;
  	
  	error = lodepng_decode32_file(&image, &width, &height, "encryptedGiven.png");
    if(error) 
		printf("error %u: %s\n", error, lodepng_error_text(error));
    
    //takes the information inside 0,0 pixel
    messageLength = image[0];
    targetRedValue = image[1];
    
    for(i = 1, count = 0; i < width*height; i++)
    {
    	if(image[4*i] == targetRedValue)
    	{
    		//takes message array and random values array from the image.
    		messageArr[count] = image[(4*i)+1];
    		randValues[count] = image[(4*i)+2];
			count++; 
		}
	}
    
    return messageLength;
  	
}

void arraySortMethod(int sizeOfStr)
{
	//sort's Blue values of targeted pixels. Also sorts the ASCII values that hidden inside green values.
	//as green values sorted, message is sorted too.
	int i, j, temp;
	for(i = 0; i < sizeOfStr; i++)
	{
		for(j = 0; j < sizeOfStr - 1; j++)
		{
			if(randValues[j] > randValues[j + 1])
			{
				temp = randValues[j];
				randValues[j] = randValues[j + 1];
				randValues[j + 1] = temp;
				
				temp = messageArr[j];
				messageArr[j] = messageArr[j + 1];
				messageArr[j + 1] = temp;
			}
		}
	}
}
