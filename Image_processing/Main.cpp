#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <iostream>
#include <vector>

#include <opencv2/highgui/highgui.hpp>
#include <opencv/cv.h>

using namespace cv;
using namespace std;

//voithikes sunartiseis
uchar quickSelect(vector<uchar> v,int k){
	int from = 0, to = v.size() - 1;
	// if from == to we reached the kth element
	while (from < to) {
		int r = from, w = to;
		int mid = v.at((r + w) / 2);
	// stop if the reader and writer meets
		while (r < w) {
			if (v.at(r) >= mid) { // put the large values at the end
				int tmp = v.at(w);
				v.at(w) = (uchar)v.at(r);
				v.at(r) = (uchar)tmp;
				w--;
			} else { // the value is smaller than the pivot, skip
				r++;
			}
		}
		// if we stepped up (r++) we need to step one down
		if (v.at(r) > mid) r--;
 
		// the r pointer is on the end of the first k elements
		if (k <= r) {
			to = r;
		} else {
			from = r + 1;
		}
	}
	return v.at(k);
}

Mat convolution2d(Mat &image,Mat &mask){
	Mat convImage=image.clone(); 
	int iif,jjf,iChecked,jChecked;
	float sum;
	for (int i = 0;i<image.rows;i++){
		for (int j =mask.cols;j<image.cols;j++){
			sum = 0;
			for (int ii=0;ii<mask.rows;ii++){
				iif=mask.rows-1-ii;
				for (int jj=0;jj<mask.cols;jj++){
					jjf=mask.cols-1-jj;
					iChecked=i+(ii-mask.rows/2);
					jChecked=j+(jj-mask.rows/2);
					if ((iChecked>=0)&&(iChecked<image.rows)&&(jChecked>=0)&&(jChecked<image.cols))
					sum += float(mask.at<double>(iif,jjf) * (float)image.at<uchar>(iChecked,jChecked));
				}
			}
			sum = sum > 255 ? 255:sum;
            sum = sum < 0 ? 0 : sum;
			convImage.at<uchar>(i,j)=(uchar)sum;
		}
	}
	return convImage;
}

int test_homogeneity(Mat image,int fromRow,int fromCol,int toRow,int toCol,int T){
	int i,j,amax,amin;
	amax=0;amin=255;
	for (i=fromRow;i<toRow;i++){
		for (j=fromCol;j<toCol;j++){
			if (image.at<uchar>(i,j)<amin) amin=image.at<uchar>(i,j);
			if (image.at<uchar>(i,j)>amax) amax=image.at<uchar>(i,j);
		}
	}
	if (abs(amax-amin)<=T) return 1;
	else return 0;
}

Mat InsertNoise(Mat img,int m,double s){
	Mat gaussian_dist = img.clone();
	//randn(gaussian_noise,128,30);
	//randn(gaussian_noise,img.rows,img.cols);
	//randu(gaussian_noise,Scalar(0),Scalar(256));
	randu(gaussian_dist,Scalar(128),Scalar(10)); // gaussian dist
	Mat gausNoise = m + gaussian_dist*sqrt(s); // poies akrivws einai oi parametroi? 0.03
	//Mat gausNoise = 0 + gaussian_noise*0.3;//me variance 800 tha mpei 30
	//GaussianBlur(gaussian_noise, gaussian_noise, Size(3, 3), 0.01, 0.01);
	img=img+gausNoise;
	namedWindow("Image with noise", CV_WINDOW_AUTOSIZE);
    imshow("Image with noise", img);
	return img;
}

Mat RemoveNoise(Mat img,int rank,int kernel){ //(5,3) -> median
	vector<uchar> v=vector<uchar>(); 
	int kdel2=kernel/2;
	for(int i=kdel2; i<img.rows-kdel2;i++){
		for(int j=kdel2; j<img.cols-kdel2; j++){
			for (int ii=0;ii<kernel;ii++){
				for (int jj=0;jj<kernel;jj++){
					v.push_back(img.at<uchar>(i+ii-kdel2,j+jj-kdel2));
				}
			}
			img.at<uchar>(i-kdel2,j-kdel2)=quickSelect(v,rank);
			v.clear();
		}
		
	}
	namedWindow("Image filtered with Ranked Order Filter", CV_WINDOW_AUTOSIZE);
    imshow("Image filtered with Ranked Order Filter", img);
	return img;
}

Mat EdgeDetection(Mat img){
	Mat maskY=	(Mat_<double>(3,3) << -1,0,1,-1,0,1,-1,0,1);
	Mat maskX= (Mat_<double>(3,3) << 1,1,1,0,0,0,-1,-1,-1);
	Mat prewittY=convolution2d(img,maskY);
	Mat prewittX=convolution2d(img,maskX);
	Mat prewitt(prewittX.size(),prewittY.type());
	add(abs(prewittY),abs(prewittX),prewitt);
	namedWindow("Image filtered with Prewitt3x3", CV_WINDOW_AUTOSIZE);
    imshow("Image filtered with Prewitt3x3", prewittY);
	return img;
}

Mat ImageSegmentation_AdaptiveThresholding(Mat img,int ndim){
	vector<uchar> v=vector<uchar>(); 
	int kernel=ndim;
	float mo;
	int rank=(ndim*ndim)/2;//median
	int kdel2=kernel/2;
	for(int i=kdel2; i<img.rows-kdel2;i++){
		for(int j=kdel2; j<img.cols-kdel2; j++){
			//if ((i<kdel2)||(i>img.rows-kdel2)||(j<kdel2)||(j>img.cols-kdel2)){
		    // tha eprepe na kanei kati diaforetiko apo auto pou kanei

			for (int ii=0;ii<kernel;ii++){
				for (int jj=0;jj<kernel;jj++){
					v.push_back(img.at<uchar>(i+ii-kdel2,j+jj-kdel2));
				}
			}
			mo=(int)quickSelect(v,rank);
			if (img.at<uchar>(i,j) > mo) img.at<uchar>(i,j)=(uchar)255;
			else img.at<uchar>(i,j)=(uchar)0;
			v.clear();
		}
		
	}
	namedWindow("Segmented Image with Adaptive Thresholding", 1);
    imshow("Segmented Image with Adaptive Thresholding", img);
	return img;
}

void ImageSegmentation_RegionSplitting(Mat img,Mat imgSgm,int fromRow,int fromCol,int toRow,int toCol,unsigned long nRegions,int T){
	int i,j,test;
	int long sum;
	test=test_homogeneity(img,fromRow,fromCol,toRow,toCol,T);
	if ((test==0)&&(toRow-fromRow>1)&&(toCol-fromCol>1)){
		ImageSegmentation_RegionSplitting(img,imgSgm,fromRow,fromCol,fromRow+(toRow-fromRow)/2,fromCol+(toCol-fromCol)/2,nRegions,T);
		ImageSegmentation_RegionSplitting(img,imgSgm,fromRow+(toRow-fromRow)/2,fromCol,toRow,fromCol+(toCol-fromCol)/2,nRegions,T);
		ImageSegmentation_RegionSplitting(img,imgSgm,fromRow,fromCol+(toCol-fromCol)/2,fromRow+(toRow-fromRow)/2,toCol,nRegions,T);
		ImageSegmentation_RegionSplitting(img,imgSgm,fromRow+(toRow-fromRow)/2,fromCol+(toCol-fromCol)/2,toRow,toCol,nRegions,T);
	}
	else{
		nRegions++;
		sum=0;
		for (i=fromRow;i<toRow;i++){
			for(j=fromCol;j<toCol;j++){
				sum += (int) img.at<uchar>(i,j);
			}
		}
		sum /= ((toRow-fromRow)*(toCol-fromCol));
		for (i=fromRow;i<toRow;i++){
			for(j=fromCol;j<toCol;j++){
				imgSgm.at<uchar>(i,j)=(uchar)sum;
			}
		}
	}
}

void grassfire(Mat img,int row,int col,int fromRow,int toRow,int fromCol,int toCol){
	
	img.at<uchar>(row,col)=(uchar)255; // to asprizw gia na min ksanaperasw
	for (int i = -1;i<=1;i++){
		for (int j =-1;j<=1;j++){
			if (((row+i)>=fromRow)&&((row+i)<toRow)&&((col+j)>=fromCol)&&((col+j)<toCol)){
				if ((int)img.at<uchar>(row+i,col+j) == 0){
					grassfire(img,row+i,col+j,fromRow,toRow,fromCol,toCol);
				}
			}
		}
	}
}

int CountObjects(Mat img,int fromRow,int toRow,int fromCol,int toCol){
	int n=0;
	for (int i=fromRow;i<toRow;i++){
		for(int j=fromCol;j<toCol;j++){
			// an vrethei se 0-mauro shmainei oti exw antikeimeno - arxizei na trexei anadromika o algorithmos grassfire
			// ws otou "kapsei" olo to antikeimeno
			if ((int)img.at<uchar>(i,j) == 0) {
				grassfire(img,i,j,fromRow,toRow,fromCol,toCol);n++;
			}
		}
	}
	return n;
}


int main()
{
	// diavazw arxikh eikona
	cout<<"---Arxiki eikona---\n";
	Mat img = imread("up.jpg", CV_LOAD_IMAGE_GRAYSCALE);   
	if (img.empty())
    {
        cout << "Cannot load image!" << endl;
		return -1;
    }
    namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
    imshow("Original Image", img);
	waitKey(0);
	// efarmozw sunarthseis
	// prosthetw thoruvo
	cout<<"---Prosthiki thoruvou---\n";
	int m;double s;
	cout<<"Mesi timi: ";
	cin>>m;
	cout<<"Tupikh apoklisi: ";
	cin>>s;
	Mat img_copy_1 = img.clone();
	img.copyTo(img_copy_1);
	Mat img_with_noise = InsertNoise(img_copy_1,m,s);
	waitKey(0);
	// afairw thorivo me ranked order
	cout<<"---Afairesh thoruvou---\n";
	int rank,kernel;
	cout<<"Taksi filtrou: ";
	cin>>rank;
	cout<<"Megethos parathurou: ";
	cin>>kernel;
	Mat img_without_noise = RemoveNoise(img_with_noise,5,3);
	waitKey(0);
	// anixneuei akmes
	cout<<"---Anixneusi akmwn---\n";
	Mat img_copy_3 = img.clone();
	img.copyTo(img_copy_3);
	Mat img_detected_edges = EdgeDetection(img_copy_3);
	waitKey(0);
	// katatmisi eikonas
	cout<<"---Katatmisi eikonas---\n"; 
	Mat img_copy_4 = img.clone();
	img.copyTo(img_copy_4);
	int choise;
	cout<<"1 gia Region Splitting/2 gia Adaptive Threshold / ";
	cin>>choise;
	if (choise == 2){
		Mat img_segmented = ImageSegmentation_AdaptiveThresholding(img_copy_4,25); //The size of the neighborhood has to be large enough to cover sufficient foreground and background pixels, otherwise a poor threshold is chosen.
													//On the other hand, choosing regions which are too large can violate the assumption of approximately uniform illumination. 
	}else {
		ImageSegmentation_RegionSplitting(img_copy_4,img_copy_4,0,0,img.rows,img.cols,0,100);
			namedWindow("Segmented Image with Region Splitting", 1);
		imshow("Segmented Image with Region Splitting", img_copy_4);
	}
	waitKey(0);
	// metrisi antikeimenwn
	int fromRow,toRow,fromCol,toCol;
	cout<<"---Metrisi antikeimenwn---\n";
	cout<<"Apo grammi: ";
	cin>>fromRow;
	cout<<"Mexri grammi: ";
	cin>>toRow;
	cout<<"Apo stili: ";
	cin>>fromCol;
	cout<<"Mexri stili: ";
	cin>>toCol;
	int nObjects;
	Mat img_binary = img.clone();
	adaptiveThreshold(img, img_binary,255,CV_ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY,75,10); 
	nObjects = CountObjects(img_binary,fromRow,toRow,fromCol,toCol);
	cout<<nObjects<<" antikeimeno/a";
	namedWindow("Image after grassfire", 1);
    imshow("Image after grassfire", img_binary);
	waitKey(0);
	return 0;
}



