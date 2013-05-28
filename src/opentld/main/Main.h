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
*
*/

/*
 * main.h
 *
 *  Created on: Nov 18, 2011
 *      Author: Georg Nebehay
 */

#ifndef MAIN_H_
#define MAIN_H_

#include "TLD.h"
#include "ImAcq.h"
#include "Gui.h"

enum Retval
{
    PROGRAM_EXIT = 0,
    SUCCESS = 1
};

class Main
{
public:
	//static char key;
	/*static IplImage* imgf;
	static IplImage* img1;
    static IplImage *img;
    static int used;*/
    static IplImage * imag;
    tld::TLD *tld;
    tld::TLD *tld2;//Added
    ImAcq *imAcq;
    static ImAcq *imac;
    tld::TLD* tlds[10];
    tld::Gui *gui;
    bool showOutput;
    const char *printResults;
    const char *saveDir;
    double threshold;
    bool showForeground;
    bool showNotConfident;
    bool selectManually;
    int *initialBB; 
    static IplImage * temp;
    int *initialBB2;//Added
    bool reinit;
    bool exportModelAfterRun;
    bool loadModel;
    const char *modelPath;
    const char *modelExportFile;
    int seed;
	static void* gammacorr(void * );
    Main()
    {
        tld = new tld::TLD();
        tld2= new tld::TLD();//Added
        for(int l=0;l<10;++l)
        {
        	tlds[l]=new tld::TLD();
    	}
        showOutput = 1;
        printResults = NULL;
        saveDir = ".";
        threshold = 0.5;
        showForeground = 0;
		modelPath=new char(10);
		modelPath="model";
        selectManually = 0;

        initialBB = NULL;
        initialBB2=NULL;//Added
        showNotConfident = true;

        reinit = 0;

        loadModel = false;

        exportModelAfterRun = false;
        modelExportFile = "model";
        seed = 0;
    }

    ~Main()
    {
        delete tld;
        imAcqFree(imAcq);
    }

    void doWork();
};

#endif /* MAIN_H_ */
