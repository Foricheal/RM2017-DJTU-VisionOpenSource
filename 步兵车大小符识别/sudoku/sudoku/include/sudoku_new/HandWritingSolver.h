//
//  HandWritingSolver.h
//  sudoku
//
//  Created by ding on 17/6/6.
//  Copyright (c) 2017年 ding. All rights reserved.
//

#ifndef __sudoku__HandWritingSolver__
#define __sudoku__HandWritingSolver__


#include "sudoku_new/caffe_prototype.h"
#include "sudoku_new/LogicProcess.h"


using namespace cv;

namespace sudoku{
    
class NumberPredict{
public:
    NumberPredict(const string& model_file,
                   const string& trained_file,
                   const string& mean_file,
                   const string& label_file,
                   const string& low_trained_file);
    
    ~NumberPredict(){};
    
    void process(vector<Rect> input,const Mat Binaryimg,Mat &img,Confirm &confirm);
public:
    vector<int> result,oldresult;                         //value:  1 2 3
    vector<std::pair<int,int> > sudoku_repeat;            //        4 5 6
private:                                                  //        7 8 9
    Classifier classifier,lowrate;
    Mat roi;
    Mat kernel;
    vector<std::pair<int,int> > Judgedata;      // 0: index 1: digit
    vector<Point> Position;
};
    
}




#endif /* defined(__sudoku__HandWritingSolver__) */
