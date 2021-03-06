//
//  LedNumberSolver.cpp
//  sudoku
//
//  Created by ding on 17/6/6.
//  Copyright (c) 2017年 ding. All rights reserved.
//

#include "sudoku_new/LedNumberSolver.h"

namespace sudoku{
    
void LedNumberSolver::ParamsFresh(const InitParams &params){
    CheckValue("binary_thres", binary_thres, params.thresholdfindup);
    binary_thres = params.thresholdfindup;
	debug_flag = params.debug_flag;
} 

void LedNumberSolver::process(vector<Rect> input,const Mat ForBinary,Mat &img,Confirm &confirm){
    size_t size = input.size();
    if(size != 5){
		return;
	}
	result.clear();
    confirm.Led = true;
    int val;
    //cout<<"led:";
    for(int i=0;i<5;i++){ 
        HOGDescriptor *hog = new cv::HOGDescriptor(cvSize(28, 28), cvSize(14, 14), cvSize(7, 7), cvSize(7, 7), 9);
        vector<float>descriptors;
        roi = ForBinary(input[i]);
        cvtColor(roi, roi, CV_BGR2GRAY);
        threshold(roi,roi,binary_thres,255,THRESH_BINARY_INV);
        resize(roi,roi,Size(20,20));
		Mat inner = Mat::ones(28,28,CV_8UC1)+254;
		roi.copyTo(inner(Rect(4,4,20,20)));
        erode(inner,inner,kernel);
        if(debug_flag){
            ostringstream name;
            name<<"led";
            name<<i+1;
            imshow(name.str(),inner);
        }
        
        hog->compute(inner,descriptors, cv::Size(1, 1), cv::Size(0, 0));
        Mat SVMPredictMat = Mat(1, (int)descriptors.size(), CV_32FC1);
        memcpy(SVMPredictMat.data,descriptors.data(),descriptors.size()*sizeof(float));
        val = svm.predict(SVMPredictMat);
        
        
        
        if(val == 9 || val == 4){
            //cout<<"val:"<<val;
            int pix = 0;
            for(int i=0;i<8;i++){
                for(int j=8;j<16;j++){
                    if(roi.at<uchar>(i,j) == 0) pix++;
                }
            }
            if (pix < 12) val = 4;
			else val = 9;
            //cout<<val<<" pix:"<<pix<<endl;
        }

		/*if(val == 7 || val == 1){
            //cout<<"val:"<<val;
            int pixt = 0;
            for(int i=0;i<28;i++){
                for(int j=0;j<28;j++){
                    if(roi.at<uchar>(i,j) == 0) pixt++;
                }
            }
            
            cout<<val<<" pix:"<<pixt<<endl;
			if (pixt < 100) val = 1;
			else val = 7;
        }*/
        
		/*if(val == 4){
			int pixz = 0;
			for(int i=3;i<14;i++){
				for(int j=3;j<8;j++){
					if(roi.at<uchar>(i,j) == 0) pixz++;
				}
			}
			if(pixz<10) val = 1;
			//cout<<"pixz"<<pixz<<endl;
		}
		if(val == 3){
			int pixt = 0;
			for(int i=20;i<28;i++){
				for(int j=3;j<16;j++){
					if(roi.at<uchar>(i,j) == 0) pixt++;
				}
			}
			if(pixt < 15) val = 7;
		}
		if(val == 3){
			int pixq = 0;
			for(int i=6;i<15;i++){
				for(int j=3;j<8;j++){
					if(roi.at<uchar>(i,j) == 0) pixq++;
				}
			}
			if(pixq > 20) val = 9;

		}*/
        stringstream value;
        value<<val;
        Point OutValue;
        OutValue.x = input[i].tl().x+5;
        OutValue.y = input[i].tl().y-5;
        putText(img, value.str(), OutValue, CV_FONT_HERSHEY_COMPLEX_SMALL, 1, Scalar(255,0,255));
        delete hog;
		hog = nullptr;
        result.push_back(val);
        //cout led digits
        //cout<<val<<" ";
    }
    //cout<<endl;
}

}
