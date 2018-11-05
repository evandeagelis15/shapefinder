#include <stdio.h>
#include <iostream>
#include <fstream>

using namespace std;

void getArgs(int argc, char** argv)
{
	string inputFileName = "";
	string shape = "";
	string color = "";
	string outputFileName = "";
	int count;

	if(argc == 8) //if arg count equals 8
	{

		for (int i=1; i < argc; i++)
		{
			if (strcmp(argv[i], "--shape") == 0 || strcmp(argv[i], "-s") == 0)
			{
				shape = argv[i+1];
				i++;
				cout << "Shape: " << shape << endl;
			}
			else if (strcmp(argv[i], "--color") == 0 || strcmp(argv[i], "-c") == 0)
			{
				color = argv[i+1];
				i++;
				cout << "Color: " << color << endl;
			}
			else if (strcmp(argv[i], "--output") == 0 || strcmp(argv[i], "-o") == 0)
			{
				outputFileName = argv[i+1];
				i++;
				cout << "Output File Name: " << outputFileName << endl;
			}
			else
			{
				inputFileName = argv[i];
				cout << "Input File Name: " << inputFileName << endl;
			}
		}

	}
	else
	{
		cout << "Invalid Number of Arguments" << endl;
	}
}

int readImage(string inputFileName, string header, string height, string width, string max, int** rImage)
{
  	ifstream inpImage;

  	int i = 0;
    int r, g, b, color;

	inpImage.open (inputFileName.c_str ( ), ios::binary);

	inpImage>>header;
    inpImage>>height;
    inpImage>>width;
    inpImage>>max;

    int row=0;
    int col=0;
    char* pixels = new char[stoi(height)*stoi(width)*3];
    
    while (inpImage >> pixels[i]) 
    {
    	if (i>2819960)
  		{
  			cout<<i<<endl;
  		}
    	r=(int)((bitset<8>(pixels[i])).to_ulong());
    	color =r;
  		i++;
  		inpImage >> pixels[i];
  		g=(int)((bitset<8>(pixels[i])).to_ulong());
  		color = (color<<8) | g;
  		i++;
  		inpImage >> pixels[i];
  		b=(int)((bitset<8>(pixels[i])).to_ulong());
  		color = (color<<8) | b;
  		i++;


  		if (col==stoi(width))
  		{
  			col = 0;
  			row++;
  		}
  		rImage[row][col] = color;
  		col++;

  		
	}
	inpImage.close();
	delete [] pixels;

	return 1;
}

int writeImage(int** rImage, string height, string width, string max)
{
	FILE *image;
	if ((image = fopen( "out.ppm", "wb") ) == NULL)
 	{
 		printf("file %s could not be created\n", "newSq.ppm");
 		return 0;
  	}

  	fprintf(image, "P6\t %s\t %s\t 255\n", height.c_str(), width.c_str()); // width = 400, height = 400

 	for (int r = 0; r<stoi(height); r++)
 	{
 		for (int c = 0; c<stoi(width); c++)
 		{
 			// if(r>50 & r<100 & c>100 & c<200)
 			// {
 			// 	unsigned int red = 0x00;//(rImage[r][c] & 0xFF0000)>>16;
 			// 	unsigned int grn = 0x00;//(rImage[r][c] & 0x00FF00)>>8;
 			// 	unsigned int blu = 0x00;//(rImage[r][c] & 0x0000FF);
 			// 	fprintf(image, "%c%c%c", red, grn, blu); // r = 255, g = 255, b = 0
 			// }
 			// else if(r>150 & r<250 & c>150& c<250)
 			// {
 			// 	unsigned int red = 0x00;//(rImage[r][c] & 0xFF0000)>>16;
 			// 	unsigned int grn = 0x00;//(rImage[r][c] & 0x00FF00)>>8;
 			// 	unsigned int blu = 0x00;//(rImage[r][c] & 0x0000FF);
 			// 	fprintf(image, "%c%c%c", red, grn, blu); // r = 255, g = 255, b = 0
 			// }
 			// else if(r>300 & r<350 & c>100 & c<350)
 			// {
 			// 	unsigned int red = 0x00;//(rImage[r][c] & 0xFF0000)>>16;
 			// 	unsigned int grn = 0x00;//(rImage[r][c] & 0x00FF00)>>8;
 			// 	unsigned int blu = 0x00;//(rImage[r][c] & 0x0000FF);
 			// 	fprintf(image, "%c%c%c", red, grn, blu); // r = 255, g = 255, b = 0
 			// }
 			// else
 			// {
 			// 	unsigned int red = 0xFF;//(rImage[r][c] & 0xFF0000)>>16;
 			// 	unsigned int grn = 0xFF;//(rImage[r][c] & 0x00FF00)>>8;
 			// 	unsigned int blu = 0xFF;//(rImage[r][c] & 0x0000FF);
 			// 	fprintf(image, "%c%c%c", red, grn, blu); // r = 255, g = 255, b = 0
 			// }
 			unsigned int red = (rImage[r][c] & 0xFF0000)>>16;
 			unsigned int grn = (rImage[r][c] & 0x00FF00)>>8;
 			unsigned int blu = (rImage[r][c] & 0x0000FF);

 			fprintf(image, "%c%c%c", red, grn, blu); // r = 255, g = 255, b = 0
 		}
 	}
  	
 	fclose (image);
 	return 1;
}

int highestXOfLineToRight(int** rImage, int y, int x, int boxColor)
{
	while(rImage[y][x]==boxColor)
	{
		x++;
	}
	return x-1;
}

int highestYOfLineToBottom(int** rImage, int y, int x, int boxColor)
{
	 while(rImage[y][x]==boxColor)
	{
		y++;
	}
	return y-1;
}


void findRectangle(int** rImage, int y, int x, int* arr)
{
	int cxInd =x;
	int cyInd =y;
	int boxColor = rImage[y][x];
	int otherx=0;
	int othery=0;
	while(rImage[cyInd][cxInd]==boxColor) 
	{
		while(rImage[cyInd][cxInd]==boxColor)
		{
			if (rImage[cyInd][cxInd+1]==boxColor&&rImage[cyInd+1][cxInd]==boxColor) 
			{
				otherx=highestXOfLineToRight(rImage, cyInd, cxInd, boxColor);
				othery=highestYOfLineToBottom(rImage, cyInd, cxInd, boxColor);
			}
			cxInd++;
		}
		cyInd++;
 	}
 	cxInd=x-1;
 	cyInd=y-1;
 	while(cyInd<=othery+1) 
	{
		rImage[cyInd][x-1] = 0xFF0000;
		rImage[cyInd][otherx+1] = 0xFF0000;
		cyInd++;
	}
	while(cxInd<=otherx+1)
	{
		rImage[y-1][cxInd] = 0xFF0000;
		rImage[othery+1][cxInd] = 0xFF0000;
		cxInd++;
	}
	arr[0]=otherx;
	arr[1]=othery;
}

int main(int argc, char** argv)
{
	//getArgs(argc, argv);
 	
 	string header="";
 	string height="";
 	string width="";
 	string max="";
 	string inputFileName = "test2.ppm";

 	ifstream inpImage;

	inpImage.open (inputFileName.c_str ( ), ios::binary);

 	if (inpImage == NULL)
    {
        cout << "\n File does not exist. \n" << endl;
        return 0;
    }
   
    inpImage>>header;
    inpImage>>height;
    inpImage>>width;
    inpImage>>max;

   

    inpImage.close();

    int** rImage = new int*[stoi(height)];
    for (int i =0; i<stoi(height);i++)
    {
    	rImage[i]=new int[stoi(width)];
    }
 	cout<<stoi(height)<<endl<<stoi(width)<<endl;
 	readImage(inputFileName, header, height, width, max, rImage);

 	int rr = 0;
 	int cc = 0;
 	int *newCoords=new int[2];
 	newCoords[0]=0;
 	newCoords[1]=1;
 	for(int rr =0; rr<stoi(height); rr++)
 	{
 		for (int cc = 0; cc<stoi(width); cc++)
 		{
 			if (rImage[rr][cc]!=rImage[0][0]&&(rr>newCoords[1]+1||cc>newCoords[0]+1))
 			{
 				findRectangle(rImage, rr, cc, newCoords);
 			}
 		}
 	}
 	delete [] newCoords;

     writeImage(rImage, height, width, max);

     for (int i =0; i<stoi(height);i++)
    {
    	delete [] rImage[i];
    }

    delete [] rImage;



	return 0;
}