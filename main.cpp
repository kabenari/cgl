#include <iostream>
#include <GL/glu.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int le[500],re[500],flag=0,m;

    void init(){
        gluOrtho2D(0,500,0,500)
    }

    void edge(int x0, int y0, int xl,int yl){
        if(y1<y0)
        {
            int temp;
            temp = y1;
            y1 = y0;
            y0 = temp;
            temp= x1;
            x1 = x0;
            x0 = temp;
        }
        int x = x0;
        m = (y1 - y0)/(x1 - x0);
        for(int i = y0;i<y1;i++){
            if(x<le[i])
                le[i] = x;
            if(x>re[i])
                re[i] = x;
            x += (1/m);''
        }
    }
    void display(){
        glClearColor(1,1,1,1);
        glClear(GL_COLOR_BUFFER_BIT);

        glColor3f(0,0,1);
        glBegin(GL_LINE_LOOP);
        glVertex2f(200,100);
        glVertex2f(100,200);
        glVertex2f(200,300);
        glVertex2f(300,200);
        glEnd();

        for(int i = 0;i<500;i++){
            le[i] = 500;
            re[i] = 0;
        }
        edge(200,100,100,200);
        edge(100,200,200,300);
        edge(300,200,300,200);
        edge(300,200,200,100);

        if(flag == 1)
        {
            for(int i = 0;i<500;i++){
                if(le[i] < re[i]){
                    for(int j = le[i];j<re[i];j++){
                        glColor3f(1,0,0);
                        glBegin(GL_POINTS);
                        glVertex2f(j,i);
                        glEnd();
                    }
                }
            }
        }
    }
