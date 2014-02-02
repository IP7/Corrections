#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>
#include <time.h> 

using namespace std;

//ex3 & 4
double calcul_sin(char c, double x){  
  x = sin(x);
  switch(c){
  case 'g':
    return (x * (10/9));
  case 'r':
    return ((x * M_PI)/180);
  }
  return x; /* c = 'd' */
}

//ex5
int mon_plus(int a, int b){
  return (a + b); 
}

//ex5
double mon_plus(double a, double b){
  return (a + b); 
}

// ex6 
int *copie(int t[], int n, int l){
  if(l >= n){
    cout << "toto" << endl;
    return t;
  }
  int *ret = new int[n];
  for(int i = 0; i < n; i++){
    ret[i] = t[i];
  }
  return (ret);
}

// ex7
int somme(int t[], int size){
  int s = 0;
  for(int i = 0; i < size; i++){
    s += t[i]; 
  }
  return (s);
}

double somme(double t[], int size){
  double s = 0;
  for(int i = 0; i < size; i++){
    s += t[i]; 
  }
  return (s);
}

int main(int argc, char *argv[]){  
  double val1;
  double val2;
  int l;
  int l2;
  int *t;
  int *t2;
  
  srand(time(NULL));
  
  if(argc < 2){
    return 0;
  }
  
  switch(argv[1][0]){
  case '1': 
    cout << "Hello World" << endl; 
    break;
  case '3': case '4':
    if(argc < 4 || (strlen(argv[2]) != 1 || 
		    (argv[2][0] != 'd' 
		     && argv[2][0] != 'r' 
		     && argv[2][0] != 'g'))){
      cout << "need arguments: <d(degre), g(grade), r(radian)> <int>" << endl;
      break;
    } 
    cout << calcul_sin(argv[2][0], atoi(argv[3])) << endl;;
    break;
  case '5':
    if(argc < 4){
      cout << "need arguments: <int/double> <int/double>" << endl;
      break;
    } 
    val1 = atof(argv[2]);
    val2 = atof(argv[3]);
    if(static_cast<int>(val1) == val1 && static_cast<int>(val2) == val2){
      cout << "+(int,int) : " << mon_plus(atoi(argv[2]), atoi(argv[3]))<< endl;
    } else {
      cout << "+(float, float) : " << mon_plus(val1, val2)<< endl;
    }
    break;
  case '6': 
    if(argc < 4){
      cout << "needs arguments: <int (size table)> <int (size new table)>\n"
	   << "table will be define with random integer"
	   << endl;
      break;
    }
    
    l = atoi(argv[2]);
    l2 = atoi(argv[3]);
    t = new int[l];
    
    cout << "t = [";
    for(int i = 0 ; i < l; i++){
      t[i] = rand() % 100;
      cout << t[i] << " ";
    }
    cout << "]" << endl;
    t2 = copie(t, l, l2);
    cout << "t2 = [";
    l2 = (l2 > l) ? l : l2;
    for(int i = 0; i < l2; i++){
      cout << t2[i] << " ";
    }
    cout << "]" << endl;;
    break;
  case '7':
    if(argc < 3){
      cout << "needs arguments: <int (size table)>\n" << endl;
      break;
    }
    l = atoi(argv[2]);
    t = new int[l];
    cout << "t = [";
    for(int i = 0 ; i < l; i++){
      t[i] = rand() % 100;
      cout << t[i] << " ";
    }
    cout << "]" << endl;
    cout << "somme (int) " << somme(t, l) << endl;
  }
  return 0;
}
