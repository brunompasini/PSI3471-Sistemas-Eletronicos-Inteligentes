// dumbo.cpp - grad2020
#include <cekeikon.h>
int main() {
 Mat_<FLT> a; le(a,"figurinhas.jpg");
 Mat_<FLT> q; le(q,"dumbo.jpg");
 Mat_<FLT> q2=somaAbsDois(dcReject(q));
 Mat_<FLT> p1,p2;
 p1=matchTemplateSame(a, q2, CV_TM_CCORR);
 imp(p1,"dumbo_cc.pgm");
 p2=matchTemplateSame(a, q, CV_TM_CCOEFF_NORMED);
 imp(p2,"dumbo_ncc.pgm");
}