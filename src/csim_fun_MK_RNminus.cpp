// [[Rcpp::depends(BH)]]
#include <Rcpp.h>
#include <boost/math/special_functions/bessel.hpp>
using namespace Rcpp;

// [[Rcpp::export]]
NumericVector csim_fun_MK_RNminus(
    double x,
    NumericVector pars, 
    NumericVector baseradians) {
  
  int i;
  int radian;
  NumericVector kappa;
  int lr = baseradians.size();
  NumericVector out(lr);
  double radians = 0;
  
  kappa = Rcpp::rgamma(x,pars[0]/pars[1], pars[1]);
  
  for (radian = 0; radian < lr; radian++){
    
    for (i = 0; i < x; i++) {
      
      radians = radians + 
        1/(2*PI*exp(-kappa[i])*boost::math::cyl_bessel_i(0, kappa[i])) *
          pow(exp(cos(baseradians[radian]) - 1 ),kappa[i]);
      
    }
    
    out[radian] = radians;
    radians = 0;
  }
  
  return(out/sum(out));
}