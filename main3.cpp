#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>

using namespace std;

int ww = 640, wh = 480;  
int first = 0;  
int xi=0, yi=0, xf=0, yf=0; 

int xmin,ymin,xmax,ymax;
double p[4],q[4];
int xt1;
int yt1;
int xt2;
int yt2;

void setPixel(GLint x, GLint y) {
  glBegin(GL_POINTS);
  glVertex2i(x,y);
  glEnd();
}

void Bresenham(int x1, int y1, int x2, int y2){
	int dx,dy,Po;
	int k=0;
	dx=(x2-x1);
	dy=(y2-y1);
	if(dy<=dx&&dy>0){
		dx=abs(dx);
		dy=abs(dy);
		Po=(2*dy)-dx;
		setPixel(x1,y1);
		int xk=x1;
		int yk=y1;
		for(k=x1;k<x2;k++){ 
			if(Po<0){	
				setPixel(++xk,yk);
				Po=Po+(2*dy);
			}else{
				setPixel(++xk,++yk);
				Po=Po+(2*dy)-(2*dx);
			}
		}
	}else if(dy>dx&&dy>0){
		dx=abs(dx);
		dy=abs(dy);
		Po=(2*dx)-dy;
		setPixel(x1,y1);
		int xk=x1; int yk=y1;
		for(k=y1;k<y2;k++){ 
			if(Po<0){	
				setPixel(xk,++yk);
				Po=Po+(2*dx);
			}else{
				setPixel(++xk,++yk);
				Po=Po+(2*dx)-(2*dy);
			}
		}	
	}else if(dy>=-dx){
		dx=abs(dx);
		dy=abs(dy);
		Po=(2*dy)-dx; 
		setPixel(x1,y1);
		int xk=x1;
		int yk=y1;
		for(k=x1;k<x2;k++){ 
			if(Po<0){	
				setPixel(++xk,yk);
				Po=Po+(2*dy);
			}else{
				setPixel(++xk,--yk);
				Po=Po+(2*dy)-(2*dx);
			}
		}
	}
	else if(dy<-dx){
		dx=abs(dx);
		dy=abs(dy);
		Po=(2*dx)-dy;
		setPixel(x1,y1);
		int xk=x1;
		int yk=y1;
		for(k=y1;k>y2;k--){
			if(Po<0){	
				setPixel(xk,--yk);
				Po=Po+(2*dx);
			}else{
				setPixel(++xk,--yk);
				Po=Po+(2*dx)-(2*dy);
			}
		}
	}
  	glFlush();
}

int clippingAlgo(int x1,int y1,int x2,int y2)
{
	float t1=0.0,t2=1.0;
	int dx=x2-x1;
	int dy=y2-y1;
    int i;
    float t;
    
	p[0]=-dx;
    p[1]=dx;
    p[2]=-dy;
    p[3]=dy;
    
    
    q[0]=x1-xmin;
    q[1]=xmax-x1;
    q[2]=y1-ymin;
    q[3]=ymax-y1;
    
    
    for(i=0;i<4;i++)
    {
        if(p[i]==0 && q[i]<0){
            return 0;
        }
        if(p[i]<0.0){
			t=q[i]/p[i];
            if(t>t1){
            	t1=t;
            }
        }
        if(p[i]>0.0){  
			t=q[i]/p[i];
            if(t<t2){
				t2=t;
			}
        }
    }
    if(t1<t2){  
		xt1=x1+t1*(x2-x1);
		yt1=y1+t1*(y2-y1);
		xt2=x1+t2*(x2-x1);
		yt2=y1+t2*(y2-y1);
        glClear(GL_COLOR_BUFFER_BIT);
        glFlush();
        Bresenham( xmin, ymin, xmax, ymin);
        Bresenham( xmax, ymin, xmax, ymax);
        Bresenham( xmin, ymax, xmax, ymax);
        Bresenham( xmin, ymax, xmin, ymin);
        
		
		int i; 
		for(i=-ww;i<ww;i=i+10){
			setPixel(i,0);
			setPixel(0,i);
		} 
		glColor3f(0.0,1.0,0.0);
		Bresenham( xt1, yt1, xt2, yt2);
		glColor3f(1.0,0.0,0.0);
		Bresenham( xi, yi, xt1, yt1);
		glColor3f(1.0,0.0,0.0);
		Bresenham( xt2, yt2, xf, yf);
		return 1;
    } else {
      	return 0;
    }
}

void Window(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,1.0,1.0);
	glFlush();
	Bresenham( xi, yi, xf, yf);
	
	Bresenham( xmin, ymin, xmax, ymin);
	Bresenham( xmax, ymin, xmax, ymax);
	Bresenham( xmin, ymax, xmax, ymax);
	Bresenham( xmin, ymax, xmin, ymin);
	
 
}

void line(){
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0,1.0,1.0);
	Bresenham( xi, yi, xf, yf);
	int x=clippingAlgo(xi,yi,xf,yf);
}

void init(){ 
	glViewport(-(ww),0,(ww),0); 
	glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
	glutInitWindowPosition(0,0);
	glutInitWindowSize(ww, wh);
	glutCreateWindow("Algotirma clipping liang barsky");
	glClearColor(0.0,0.0,0.0,0);
	glColor3f(1.0,1.0,1.0);
	gluOrtho2D(-(ww),(ww),-(wh),(wh)); 
}

int main(int argc, char **argv) {
	glutInit(&argc, argv);
	init();
	cout<<"Algotirma clipping liang barsky"<<endl;
	cout<<"Daftar nama kelompok:"<<endl;
	cout<<"1. Faiq Azmi Nurfaizi      (201810370311047)"<<endl;
	cout<<"2. Wahyuli Dwiki Nanda     (201810370311052)"<<endl;
	cout<<"3. Alfin Yusriansyah       (201810370311057)"<<endl;
	cout<<"4. Jafar Shodiq Djawas     (201810370311068)"<<endl;
	cout<<"5. Jody Ririt Krido Suseno (201810370311073)"<<endl;
	
	int pilih;
	
	cout<<"Apakah anda ingin menggunakan inputan atau contoh"<<endl;
	cout<<"1.Inputan (memasukan ukuran clipping dan titik garis oleh user)"<<endl;
	cout<<"2.Contoh (menampilkan hasil clipping dengan ukuran yang telah ditentukan tanpa inputan user)"<<endl;
	cout<<"Pilih : ";
	cin>>pilih;
	if(pilih == 1){
		cout<<"Membuat daerah clipping"<<endl;
		cout<<"----------------------------------------------------------"<<endl;
		cout<<"Masukkan X min : ";
		cin>>xmin;
		cout<<"Masukkan Y min : ";
		cin>>ymin;
		cout<<"Masukkan X max : ";
		cin>>xmax;
		cout<<"Masukkan Y max : ";
		cin>>ymax;
		glutDisplayFunc(Window);
		cout<<"----------------------------------------------------------"<<endl;
		cout<<"Membuat garis"<<endl;
		cout<<"Masukkan ujung awal : "<<endl;
		cout<<"X : ";
		cin>>xi;
		cout<<"Y : ";
		cin>>yi;
		cout<<"Masukkan titik akhir : "<<endl;
		cout<<"X : ";
		cin>>xf;
		cout<<"Y : ";
		cin>>yf;
		glutDisplayFunc(line);
		glutMainLoop();
	}else if (pilih == 2){
		cout<<"Membuat daerah clipping"<<endl;
		cout<<"----------------------------------------------------------"<<endl;
		xmin = 0;
		ymin = 0;
		xmax = 100;
		ymax = 100;
		cout<<"Masukkan X min : "<<xmin<<endl;
		cout<<"Masukkan Y min : "<<ymin<<endl;
		cout<<"Masukkan X max : "<<xmax<<endl;
		cout<<"Masukkan Y max : "<<ymax<<endl;
		glutDisplayFunc(Window);
		cout<<"----------------------------------------------------------"<<endl;
		cout<<"Membuat garis"<<endl;
		cout<<"Masukkan ujung awal : "<<endl;
		xi = -50;
		yi = 100;
		cout<<"X : "<<xi<<endl;
		cout<<"Y : "<<yi<<endl;
		cout<<"Masukkan titik akhir : "<<endl;
		xf = 150;
		yf = 0;
		cout<<"X : "<<xf<<endl;
		cout<<"Y : "<<yf<<endl;
		glutDisplayFunc(line);
		glutMainLoop();
	}
	
	return 0;
}
