#include<stdio.h>
#include<math.h>
#include<conio.h>
#include<stdlib.h>
#define min(a,blue,c)(a<blue?a:blue)<c?(a<blue?a:blue):c   /* Calculate the minimum of red,green,blue values */


int main()
{
   char ch;
   FILE *fp,*fhue,*fsat;
   unsigned char blue;
   unsigned char green;
   unsigned char red;
   unsigned char hue;
   unsigned char sat;
   float lightness,Num,Den,hue1,sat1,min1;


   fp=fopen("C:/Users/shalini/Desktop/rose.raw","rb");	// Open the .raw image file
	if(fp==NULL)
	{
		printf("Error in opening file\n");
		return (-1);
	}
	fhue=fopen("C:/Users/shalini/Desktop/roses1.raw","wb");	// Open the .raw image file that will have hue values
	if(fhue==NULL)
	{
		printf("Error in opening file\n");
		return (-1);
	}
	fsat=fopen("C:/Users/shalini/Desktop/roses2.raw","wb");	//Open the .raw image file that will have saturation values
	if(fsat==NULL)
	{
		printf("Error in opening file\n");
		return (-1);
	}

   while( ( ch = fgetc(fp) ) != EOF )
    {
        red = (char)fgetc(fp);
        green = (char)fgetc(fp);
        blue = (char)fgetc(fp);

        ////Calculation of hue
        lightness = red + green + blue;
        //printf("lightness : %d", lightness);
        Num = (red - green) + (red - blue);
        //printf("Num : %d", Num);
        Den = 2 * sqrt(pow(2,(red-green))+(red-blue)+(green-blue));
        //printf(" Dem : %d", Den);
        hue1 = Num / Den;

       if (hue1 < 0)
              hue1 += 360;
        hue1 *=  255;
        hue1 /= 360;
        hue = hue1;
        fputc(hue,fhue);

       //printf("%d", hue1);
     /*  int min1 = 0;

       // printf("Min1 : %d" , (min1/lightness));*/
       ////Calculation of Saturation
        min1 = min(red,green,blue);
        sat1 = 1 - (min1/lightness);
       // printf("Sat1 : %d", sat1);
        sat1 *= 255;
        sat = sat1;
        fputc(sat,fsat);

   }

   fclose(fhue);
   fclose(fsat);
   fclose(fp);
   return 0;
}
