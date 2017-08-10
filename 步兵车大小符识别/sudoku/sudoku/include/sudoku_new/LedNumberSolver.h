//
//  LedNumberSolver.h
//  sudoku
//
//  Created by ding on 17/6/6.
//  Copyright (c) 2017年 ding. All rights reserved.
//

#ifndef __sudoku__LedNumberSolver__
#define __sudoku__LedNumberSolver__

#include "Header.h"
#include "sudoku_new/LogicProcess.h"
using namespace cv;

namespace sudoku{

class LedNumberSolver{
public:
    LedNumberSolver(const char *file,InitParams params){
        svm.load(file);
        kernel = getStructuringElement(MORPH_RECT, Size(3,3));
        binary_thres = params.thresholdfindup;
        debug_flag = params.debug_flag;
    };
    ~LedNumberSolver(){};
    void ParamsFresh(const InitParams &params);
    void process(vector<Rect> input,const Mat ForBinary,Mat &img,Confirm &confirm);

public:
    vector<int> result; //from left to right
private:
    CvSVM svm;
    int binary_thres;
    Mat roi,predictimg;
    Mat kernel;
    int debug_flag;
	long countsave,lostframe;
};

}

#endif /* defined(__sudoku__LedNumberSolver__) */
