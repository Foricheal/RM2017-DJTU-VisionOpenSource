//
//  InitParam.h
//  sudoku
//
//  Created by ding on 17/6/10.
//  Copyright (c) 2017年 ding. All rights reserved.
//

#ifndef __sudoku__InitParam__
#define __sudoku__InitParam__

#include "Header.h"
#include "sudoku_old/ImageProcess.h"
using namespace std;
using namespace cv;

void InitParam(InitParams &params,const FileStorage& fs);
void WriteParam(const InitParams &params,FileStorage& fs);
void InitOldParam(sudokuold::Params &params,const FileStorage& fs);

#endif /* defined(__sudoku__InitParam__) */
