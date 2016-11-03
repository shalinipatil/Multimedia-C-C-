#include<stdio.h>
#include<math.h>

int main()
{
	int H=638,W=393;
	unsigned char a[W][H],Gx[W][H],Gy[W][H],G[W][H],Px[W][H],Py[W][H],P[W][H],G1[W][H];
	int i,j,c,cc=0,dd=0,d,e,pp;
	int  thrsh = 30;
	FILE *ip,*op1,*op2,*op3,*peak;
	int n1=0,m1=0,n2=W,m2=H,min=0,max=255;

	ip = fopen("Building.raw", "rb");				// read raw file  
	if(ip==NULL)
	{
		printf("Error in opening file\n");
		return (-1);
	}
	fread(a, sizeof(unsigned char), W*H, ip);
	
	///Gx Horizontal difference using sobel coordinates {-1,0,1,-2,0,2,-1,0,1} Horizontal edge detection
	for(i= n1+1;i< n2-1;i++)
	{
		for(j= m1+1;j< m2-1;j++)
		{
			
			dd = -(int)a[i-1][j-1] - 2*(int)a[i][j-1] - (int)a[i+1][j-1];
			dd += (int)a[i-1][j+1] + 2*(int)a[i][j+1] + (int)a[i+1][j+1];
			if(dd < min) 
			{ 
				min = dd; 
			}
			if(dd>max) 
			{ 
				max = dd;
			}
			d = 128 * (dd - min) / (max - min);
			//d = abs(dd/4);
			//d +=128;
			
			Gx[i][j] = (unsigned char)d;
				
	/// Gy - Vertical difference using sobel coordinates  {1,2,1,0,0,0,-1,-2,-1} vertical edge detection
				
			cc = (int)a[i-1][j-1] + 2*(int)a[i-1][j] + (int)a[i-1][j+1];
			cc += -(int)a[i+1][j-1] - 2*(int)a[i+1][j] - (int)a[i+1][j+1];
			if(cc < min) 
			{
				min = cc; 
			}
			if(cc>max) 
			{ 
				max = cc; 
			}
			c = 128 * (cc - min) / (max - min);
			//c = abs(cc/4);
			
			//if(c>255)
				//c = 255;
			Gy[i][j] = (unsigned char) c;
			
	// Gradient Image using horizontal and vertical sobel operator
			
			e = sqrt(dd*dd + cc*cc);
			e = e/4;
			//e= sqrt((int)Gx[i][j]*(int)Gx[i][j]+(int)Gy[i][j]*(int)Gy[i][j]);
			G[i][j] = (unsigned char) e;
			G1[i][j] = (unsigned char) e;
				
		}
	}
	
	for(i= n1+1;i< n2-1;i++)
	{
		for(j= m1+1;j< m2-1;j++)
		{
			
			if((int)G1[i][j]>(int)G1[i][j-1] && (int)G1[i][j]>=(int)G1[i][j+1] && (int)G1[i][j] > thrsh)// || 
				//(int)G[i][j]<(int)G[i][j-1] && (int)G[i][j]<=(int)G[i][j+1] && (int)G[i][j] < -thrsh)
				{
					(int)G1[i][j] = 200;
				}
			else
				{
					(int)G1[i][j] = 0;
				}
			Px[i][j] = G1[i][j];
		
		// Peak Detection for diagonal edge for Gy
	
			
			if((int)G1[i][j]>(int)G1[i-1][j] && (int)G1[i][j]>=(int)G1[i+1][j] && (int)G1[i][j] > thrsh)// || 
				//(int)G[i][j]<(int)G[i-1][j] && (int)G[i][j]<=(int)G[i+1][j] && (int)G[i][j] < -thrsh)
				{
					(int)G1[i][j] = 200;
				}
			else
				{
					(int)G1[i][j] = 0;
				}
			Py[i][j] = G1[i][j];
	
			pp = (int)Px[i][j]+(int)Py[i][j] ;
			P[i][j] = (unsigned char) pp;
			
		}
	}
	
    op1 = fopen("SobelVEdge3X3.raw", "wb");
	op2 = fopen("SobelHEdge3X3.raw", "wb");
	op3 = fopen("SobelEdge3X3.raw","wb");
	
	peak = fopen("SPeak3X3.raw","wb");

	if(op1==NULL)
	{
		printf("Error in opening file\n");
		return (-1);
	}
	if(op2==NULL)
	{
		printf("Error in opening file\n");
		return (-1);
	}
	if(op3==NULL)
	{
		printf("Error in opening file\n");
		return (-1);
	}
	
	if(peak==NULL)
	{
		printf("Error in opening file\n");
		return (-1);
	}
	
       	
	fwrite(Gx,sizeof(unsigned char),W*H, op1);
	fwrite(Gy,sizeof(unsigned char),W*H,op2);
	fwrite(G,sizeof(unsigned char),W*H,op3);
	
	fwrite(P,sizeof(unsigned char),W*H,peak);
            	
    fclose(ip);
	fclose(op1);
	fclose(op2);
	fclose(op3);
	
	fclose(peak);
	return 0;
}