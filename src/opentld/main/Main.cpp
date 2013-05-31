/*  Copyright 2011 AIT Austrian Institute of Technology
*
*   This file is part of OpenTLD.
*
*   OpenTLD is free software: you can redistribute it and/or modify
*   it under the terms of the GNU General Public License as published by
*    the Free Software Foundation, either version 3 of the License, or
*   (at your option) any later version.
*
*   OpenTLD is distributed in the hope that it will be useful,
*   but WITHOUT ANY WARRANTY; without even the implied warranty of
*   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
*   GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License
*   along with OpenTLD.  If not, see <http://www.gnu.org/licenses/>.
*git pull https://github.com/amnosuperman/handtracking.git
*/
/*
 * MainX.cpp
 *
 *  Created on: Nov 17, 2011
 *      Author: Georg Nebehay
 */

/*Git Update ohoooo1*/

#include "Main.h"
#include<X11/Xlib.h>
#include "Config.h"
#include "ImAcq.h"
#include "Gui.h"
#include "TLDUtil.h"
    #include <pthread.h>
    //int used;

using namespace tld;
using namespace cv;


FILE *fp;

//ImAcq * Main::imac=NULL;

	IplImage* imgf;
	IplImage* img1;
    IplImage *img;
    int used;
    IplImage *im;

char key;

//imAcq * imac;


/*void Gesture1()
{
	XEvent event;
	memset(&event,0,sizeof(event));
	event.xbutton.button=button;
	event.xbutton.same_screen=1;
	event.xbutton.subwindow=DefaultRootWindow(display);
	while(event.xbutton.subwindow)
	{
		event.xbutton.window = event.xbutton.subwindow;
		XQueryPointer(display,event,xbutton.window,&event.xbutton.root,
		&event.xbutton.subwindow,&event.xbutton.x_root,&event.xbutton.y_root,
		&event.xbutton.x,&event.xbutton.y,&event.xbutton.state);
	}
	event.type=ButtonPress;
	if(XSendEvent(display,PointerWindow,1,ButtonPressMask,&event)==0)
	{
		fprintf(stderr,"Error to send the event!\n");
	}
	XFlush(display);
	usleep(1);
}
*/
//IplImage *img;

IplImage * Main::temp=NULL;
IplImage * Main::imag=NULL;


void* Main::gammacorr(void *arg)
{
	int yq=0;
	//IplImage* imgf=cvCreateImage(cvGetSize(img),IPL_DEPTH_32F,3);
	//IplImage* img1=cvCreateImage(cvGetSize(img),8,3);
	//cvShowImage("original",img);
	//cvCvtColor(img,hsl,CV_BGR2HLS);
	
	
	imag=imAcqGetImg(imac);
	int lb[256]={0},cumb[256]={0},lg[256]={0},cumg[256]={0},lr[256]={0},cumr[256]={0},totr,totg,totb;
	int x,y,i=0,p5b,p95b,p5g,p95g,p5r,p95r;
	for( y=0;y<imag->height;y++)
	{
		uchar *ptr1=(uchar*)(imag->imageData + y * imag-> widthStep);
		for( x=0;x<imag->width;x++)
		{
			lb[ptr1[3*x]]++;
			lg[ptr1[3*x+1]]++;
			lr[ptr1[3*x+2]]++;
			/*for(i=0;i<256;i++)
			{
				if(ptr1[3*x]==i)
					lb[i]++;
		
				if(ptr1[3*x+1]==i)
					lg[i]++;
		
				if(ptr1[3*x+2]==i)
					lr[i]++;
			}*/	
		}
		}
	//printf("\n%d %d %d \n",lr[100],lg[120],lb[132]);
	int j=0,p5vr,p95vr,p5vg,p95vg,p5vb,p95vb;
	for(i=0;i<256;i++)
	{
		for(j=0;j<i;j++)
		{
			cumb[i]+=lb[j];
			cumg[i]+=lg[j];
			cumr[i]+=lr[j];
		}
	}
	totr=cumr[255];
	totg=cumg[255];
	totb=cumb[255];
	int pers=3,perl=97;
	p5b=(int)totb*pers/100;
	p95b=(int)totb*perl/100;
	p5g=(int)totg*pers/100;
	p95g=(int)totg*perl/100;
	p5r=(int)totr*pers/100;
	p95r=(int)totr*perl/100;
	i=0,j=0;
	while(i<256)
	{
		//printf("%d ",i);
		if(cumr[i]>=p5r)
		{
			p5vr=i;
			break;
		}
		i++;
	}
	i=0;
	while(i<256)
	{
		//printf("%d ",i);
		if(cumg[i]>=p5g)
		{
			p5vg=i;
			break;
		}
		i++;
	}
	i=0;
	while(i<256)
	{
		//printf("%d ",i);
		if(cumb[i]>=p5b)
		{
			p5vb=i;
			break;
		}
		i++;
	}
	i=0;
	while(i<256)
	{
		if(cumr[i]>=p95r)
		{
			p95vr=i;
			break;
		}
		i++;
	}
	i=0;
	while(i<256)
	{
		if(cumg[i]>=p95g)
		{
			p95vg=i;
			break;
		}
		i++;
	}
	i=0;
	while(i<256)
	{
		if(cumb[i]>=p95b)
		{
			p95vb=i;
			break;
		}
		i++;
	}

	//printf("\n%d",img->widpthread_create( &t1, NULL, function1,NULL);th*img->height);
	//printf("\nr5=%d r95=%d\ng5=%d g95=%d \n b5=%d b95=%d\n",p5vr,p95vr,p5vg,p95vg,p5vb,p95vb);
	float ar,br,ag,bg,ab,bb;
	ar=255.0/(float)(p95vr-p5vr);
	br=-1.0*p5vr/(float)(p95vr-p5vr);
	ag=255.0/(float)(p95vg-p5vg);
	bg=-1.0*p5vg/(float)(p95vg-p5vg);
	ab=255.0/(float)(p95vb-p5vb);
	bb=-1.0*p5vb/(float)(p95vb-p5vb);
	//printf("\nar=%f  br=%f \n\nag=%f  bg=%f \n\nab=%f  bb=%f \n",ar,br,ag,bg,ab,bb);
	cvConvertScale(imag,imgf,1.0/255.0);
	//cvShowImage("float",imgf);
	for( y=0;y<imgf->height;y++)
	{
		float *ptr=(float*)(imgf-> imageData + y * imgf-> widthStep);
		for( x=0;x<imgf->width;x++)
		{
			{
				ptr[3*x]=ab*ptr[3*x]+bb;
				ptr[3*x+1]=ag*ptr[3*x+1]+bg;
				ptr[3*x+2]=ar*ptr[3*x+2]+br;
			}
		}
	}
	//printf("diff \n\n");
	cvConvertScale(imgf,img1,255);

	/*for( y=0;y<img1->height;y++)
	{
		uchar *ptr=(uchar*)(img1-> imageData + y * img1-> widthStep);
		uchar *ptr1=(uchar*)(img-> imageData + y * img-> widthStep);
		for( x=0;x<img1->width;x++)
		{
	/*			printf("b= %d  ",ptr[3*x]-ptr1[3*x]);
				printf("g= %d  ",ptr[3*x+1]-ptr1[3*x+1]);
				printf("r= %d\n",ptr[3*x+2]-ptr1[3*x+2]);
				//fprintf(fp,"x=%d  y=%d  r=%d   g=%d   b=%d \n ",x,y,ptr[3*x]-ptr1[3*x],ptr[3*x+1]-ptr1[3*x+1],ptr[3*x+2]-ptr1[3*x+2]);
			}
	}*/
		

	//cvShowImage("final",img1);
	//cvSaveImage("auto.jpg",img1);
	cvCopy(img1,temp);
	//p//rintf("yes%d",yq++);
	used =0;
	cvReleaseImage(&imag);
	
	
	//cvReleaseImage(&img1);
	//cvReleaseImage(&imgf);
	//return img1;
	//cvWaitKey(0);
	return NULL;
}

/*void* call(void *ar)
{
	gammacorr(NULL);
}*/

void Main::doWork()
{
	//fp=fopen("results_percent.dat","a");
	bool selected2=false;
	bool selected[10]={false};
    //IplImage *
    Main::imac=imAcq;
    img = imAcqGetImg(imAcq);
    IplImage *img3;
    img=cvCreateImage(cvGetSize(img),8,3);
    temp=cvCreateImage(cvGetSize(img),8,3);
    imgf=cvCreateImage(cvGetSize(img),IPL_DEPTH_32F,3);
    img1=cvCreateImage(cvGetSize(img),8,3);
    Mat grey(img->height, img->width, CV_8UC1);
    cvtColor(cv::Mat(img), grey, CV_BGR2GRAY);

    tld->detectorCascade->imgWidth = grey.cols;
    tld->detectorCascade->imgHeight = grey.rows;
    tld->detectorCascade->imgWidthStep = grey.step;
    
    tld2->detectorCascade->imgWidth = grey.cols;
    tld2->detectorCascade->imgHeight = grey.rows;
    tld2->detectorCascade->imgWidthStep = grey.step;
    
		pthread_t t1;
		
    pthread_create( &t1, NULL, gammacorr,NULL);
	used=1;	
	double tic=0 ;
	double toc=0;
	double fpsavg=0;
	int countfr=0;
  
    for(int k=0;k<10;++k)
    {
		tlds[k]->detectorCascade->imgWidth = grey.cols;
		tlds[k]->detectorCascade->imgHeight = grey.rows;
		tlds[k]->detectorCascade->imgWidthStep = grey.step;
	}
    if(selectManually)
    {

        CvRect box;

        if(getBBFromUser(img, box, gui) == PROGRAM_EXIT)
        {
            return;
        }

        if(initialBB == NULL)
        {
            initialBB = new int[4];
        }

        initialBB[0] = box.x;
        initialBB[1] = box.y;
        initialBB[2] = box.width;
        initialBB[3] = box.height;
    }

    FILE *resultsFile = NULL;

    if(printResults != NULL)
    {
        resultsFile = fopen(printResults, "w");
    }

    bool reuseFrameOnce = false;
    bool skipProcessingOnce = false;

    if(loadModel && modelPath != NULL)
    {
        tld->readFromFile(modelPath);
        reuseFrameOnce = true;
    }
    else if(initialBB != NULL)
    {
        Rect bb = tldArrayToRect(initialBB);

        printf("Starting at %d %d %d %d\n", bb.x, bb.y, bb.width, bb.height);

        tld->selectObject(grey, &bb);
        skipProcessingOnce = true;
        reuseFrameOnce = true;
    }

    for(;imAcqHasMoreFrames(imAcq)!=0;)
    {
        

        if(!reuseFrameOnce)
        {
            if(used==0)
            {
            cvCopy(temp,img);
            used=1;
            pthread_create( &t1, NULL, gammacorr,NULL);
            }
            else
            {
            pthread_join(t1,NULL);
            continue;
            }
      
           /* if(img!=temp&&temp!=NULL)
            	img = temp;
            else
            	continue;*/
            //img3=cvCloneImage(img);
            //if(tld->currBB==NULL&&tld2->currBB==NULL)gammacorr(img);
            if(img == NULL)
            {
                printf("current image is NULL, assuming end of input.\n");
                break;
            }

            cvtColor(cv::Mat(img), grey, CV_BGR2GRAY);
        }
		if(selected2)
		{
			tld2->processImage(img);
		}
		for(int k=0;k<10;++k)
		{
			if(selected[k])
			{
				tlds[k]->processImage(img);
			}
		}	
        if(!skipProcessingOnce)
        {
            tld->processImage(img);
        }
        else
        {
            skipProcessingOnce = false;
        }

        if(printResults != NULL)
        {
            if(tld->currBB != NULL)
            {
                fprintf(resultsFile, "%d %.2d %.2d %.2d %.2d %f\n", imAcq->currentFrame - 1, tld->currBB->x, tld->currBB->y, tld->currBB->width, tld->currBB->height, tld->currConf);
            }
            else
            {
                fprintf(resultsFile, "%d NaN NaN NaN NaN NaN\n", imAcq->currentFrame - 1);
            }
        }

        

        toc = toc / 1000000;
		float fps;
        if(toc!=0)
        	fps = 1 / toc;
        else 
        	fps=0;

        int confident = (tld->currConf >= threshold) ? 1 : 0;

        if(showOutput || saveDir != NULL)
        {
            char string[128];

            char learningString[10] = "";

            if(tld->learning)
            {
                strcpy(learningString, "Learning");
            }

            sprintf(string, "#%d,Posterior %.2f; fps: %.2f, #numwindows:%d, %s", imAcq->currentFrame - 1, tld->currConf, fps, tld->detectorCascade->numWindows, learningString);
            CvScalar yellow = CV_RGB(255, 255, 0);
            CvScalar blue = CV_RGB(0, 0, 255);
            CvScalar black = CV_RGB(0, 0, 0);
            CvScalar white = CV_RGB(255, 255, 255);
            CvScalar green = CV_RGB(0,255,0);
            CvScalar red = CV_RGB(255,0,0);
			int ppp=0;
            if(tld->currBB != NULL)
            {
                CvScalar rectangleColor = (confident) ? blue : yellow;
                ppp=1;
                cvRectangle(img, tld->currBB->tl(), tld->currBB->br(), green, 8, 8, 0);
            }
            
            if(tld2->currBB !=NULL)
            {
            	cv::Rect Brect(tld2->currBB->x-40,tld2->currBB->y-10,tld2->currBB->width+70,tld2->currBB->height+10);
            	cv::Rect* BBrect=&Brect;
            	cvRectangle(img, BBrect->tl(), BBrect->br(), red, 8, 8, 0);
        	}
        	
        	for(int k=0;k<10;++k)
        	{
        		if(tlds[k]->currBB !=NULL)
            	{
            		cvRectangle(img, tlds[k]->currBB->tl(), tlds[k]->currBB->br(), white, 8, 8, 0);
        		}
    		}	

            CvFont font;
            cvInitFont(&font, CV_FONT_HERSHEY_SIMPLEX, .5, .5, 0, 1, 8);
            cvRectangle(img, cvPoint(0, 0), cvPoint(img->width, 50), black, CV_FILLED, 8, 0);
            cvPutText(img, string, cvPoint(25, 25), &font, white);

            if(showForeground)
            {

                for(size_t i = 0; i < tld->detectorCascade->detectionResult->fgList->size(); i++)
                {
                    Rect r = tld->detectorCascade->detectionResult->fgList->at(i);
                    cvRectangle(img, r.tl(), r.br(), white, 1);
                }

            }


            if(showOutput)
            {
                gui->showImage(img);
                toc = (cvGetTickCount() - tic) / cvGetTickFrequency();
                tic = cvGetTickCount();
                countfr++;
                //printf("%d %lf\n",countfr,fpsavg);
                fpsavg+=fps;
                key = gui->getKey();

                if(key == 'q') break;

                if(key == 'b')
                {

                    ForegroundDetector *fg = tld->detectorCascade->foregroundDetector;

                    if(fg->bgImg.empty())
                    {
                        fg->bgImg = grey.clone();
                    }
                    else
                    {
                        fg->bgImg.release();
                    }
                }

                if(key == 'c')
                {
                    //clear everything
                    tld->release();
                }

                if(key == 'l')
                {
                    tld->learningEnabled = !tld->learningEnabled;
                    printf("LearningEnabled: %d\n", tld->learningEnabled);
                }
				if(key == 'o')
                {
                    tld2->learningEnabled = !tld2->learningEnabled;
                    //printf("LearningEnabled: %d\n", tld->learningEnabled);
                }
                if(key == 'a')
                {
                    tld->alternating = !tld->alternating;
                    printf("alternating: %d\n", tld->alternating);
                }

                if(key == 'e')
                {
                    tld->writeToFile(modelExportFile);
                }

                if(key == 'i')
                {
                    tld->readFromFile("model");
                }

                if(key == 'r')
                {
                    CvRect box;

                    if(getBBFromUser(img, box, gui) == PROGRAM_EXIT)
                    {
                        break;
                    }

                    Rect r = Rect(box);

                    tld->selectObject(grey, &r);
                }
                if(key == 'p')
                {
                    CvRect box;

                    if(getBBFromUser(img, box, gui) == PROGRAM_EXIT)
                    {
                        break;
                    }

                    Rect r = Rect(box);

                    tld2->selectObject(grey, &r);
                    
                    selected2=true;
                }
                for(int k=0;k<10;++k)
                {
		            if(key-'0' == k)
		            {
		                CvRect box;

		                if(getBBFromUser(img, box, gui) == PROGRAM_EXIT)
		                {
		                    break;
		                }

		                Rect r = Rect(box);

		                tlds[k]->selectObject(grey, &r);
		                
		                selected[k]=true;
		            }
	            }
	            if(key=='j')
	            {
	            	tld->writeToFile("gesture3");
            	}
            	if(key=='u')
            	{
            		tld2->readFromFile("gesture3");
            		selected2=true;
        		}
	            if(key=='w')
	            {
	            	tld2->writeToFile("gesture2");
            	}
            	if(key=='z')
            	{
            		tld2->readFromFile("gesture2");
            		selected2=true;
            		//tld2->LearningEnabled=!tld->LearningEnabled;
        		}
            }

            if(saveDir != NULL)
            {
                char fileName[256];
                sprintf(fileName, "%s/%.5d.png", saveDir, imAcq->currentFrame - 1);

                cvSaveImage(fileName, img);
            }
        }

        /*if(!reuseFrameOnce)
        {
            cvReleaseImage(&img);
        }
        else
        {
            reuseFrameOnce = false;
        }*/
    }
    

    if(exportModelAfterRun)
    {
        tld->writeToFile(modelExportFile);
    }
    
    cvReleaseImage(&img);
    //cvReleaseImage(&temp);
    //cvReleaseImage(&imgf);
    //cvReleaseImage(&img1);
    printf("\x1b[34mAverage frame rate = %lf fps \x1b[0m\n",fpsavg/(double)countfr);
    //fclose(fp);
}
