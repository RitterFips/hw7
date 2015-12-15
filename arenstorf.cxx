#include <cmath>
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>

using namespace std;

void func(double*,double* , const double);

int main(){
  //Arrays für die k-Werte
  double k1[4];
  double k2[4];
  double k3[4];
  double k4[4];
  double k5[4];
  double k6[4];
  double k7[4];
  
  //Definiere Variablen die im Laufe genutzt werden
  int n = 0; //Zählvariable
  const double tol = 0.00001;//Toleranzwert
  double dt = 0.0001;//Anfangsschrittweite
  double t = 0;//startzeit
  const double T = 17.065216560157;//Periode
  const double m = 0.012277471;
  const double q = 0.8;//Sicherheitsfaktor
  
  double f[4];  //Array für die Funktionswerte
  f[0] = 0.994; //Anfangsbedingungen
  f[1] = 0;
  f[2] = 0;
  f[3] = -2.0015851037908;
  double ftemp[4];
  
  double f4[4];//temp speicher für rk 4. Ordnung
  double f5[4];//temp speicher für rk 5. Ordnung
  double norm[4];//Normiereung
  double Max;
  double max1;
  double max2;
  
  //Butcher table
  //double c[7];
  //c[0] = 0, c[1] = 1/5, c[2] = 3/10, c[3] = 4/5, c[4] = 8/9, c[5] = 1, c[6] = 1;
  //double b1[7];
  //b1[0] = 35/384.0, b1[1] = 0, b1[2] = 500/1113.0, b1[3] = 125/192.0, b1[4] = -2187/6784.0, b1[5] = 11/84.0, b1[6] = 0;
  //double b2[7];
  //b2[0] = 5179/57600.0, b2[1] = 0, b2[2] = 7571/16695.0, b2[3] = 393/640.0, b2[4] = -92097/339200.0, b2[5] = 187/2100.0, b2[6] = 1/40.0;
  //double a1[1], a2[1], a3[2], a4[3], a5[4], a6[5], a7[6];
  //a1[0] = 0;
  //a2[0] = 1/5.0;
  //a3[0] = 3/40.0, a3[1] = 9/40.0;
  //a4[0] = 44/45.0, a4[1] = -56/15.0, a4[2] =32/9.0;
  //a5[0] = 19372/6561.0, a5[1] = -25360/2187.0, a5[2] = 64448/6561.0, a5[3] = -212/729.0;
  //a6[0] = 9017/3168.0, a6[1] = -355/33.0, a6[2] = 46732/5247.0, a6[3] = 49/176.0, a6[4] = -5103/18656.0;
  //a7[0] = 35/384.0, a7[1] = 0, a7[2] = 500/1113.0, a7[3] = 125/192.0, a7[4] = -2187/6784.0, a7[5] = 11/84.0;
  
  cout << n << "\t" << t << "\t" << dt << "\t" << f[0] << "\t" << f[2] << endl;
    while(t <= T && n < 100000){
    t += dt;
    n++;
    
    //-------------------------------------------------------------------------------------
    //Bestimme die k-Werte
    
    func(k1,f,m);
    
    for(int i = 0; i < 4; i++)
    ftemp[i] = f[i] + dt*(1.0/5.0*k1[i]);
    
    func(k2,ftemp,m);
    
    for(int i = 0; i < 4; i++)
    ftemp[i] = f[i] + dt*(3.0/40.0*k1[i] + 9.0/40.0*k2[i]);
    
    func(k3,ftemp,m);
    
    for(int i = 0; i < 4; i++)
    ftemp[i] = f[i] + dt*(44.0/45.0*k1[i] - 56.0/15.0*k2[i] + 32.0/9.0*k3[i]);
    
    func(k4,ftemp,m);
    
    for(int i = 0; i < 4; i++)
    ftemp[i] = f[i] + dt*(19372.0/6561.0*k1[i] - 25360.0/2187.0*k2[i]+ 64448.0/6561.0*k3[i] - 212.0/729.0*k4[i]);
    
    func(k5,ftemp,m);
    
    for(int i = 0; i < 4; i++)
    ftemp[i] = f[i] + dt*(9017.0/3168.0*k1[i]+ -355.0/33.0*k2[i]+ 46732.0/5247.0*k3[i]+ 49.0/176.0*k4[i] - 5103.0/18656.0*k5[i]);
    
    func(k6,ftemp,m);
    
    for(int i = 0; i < 4; i++)
    ftemp[i] = f[i] + dt*(35.0/384.0*k1[i] + 0*k2[i]+ 500.0/1113.0*k3[i]+ 125.0/192.0*k4[i] - 2187.0/6784.0*k5[i]+ 11.0/84.0*k6[i]);
    
    func(k7,ftemp,m);
    //-----------------------------------------------------------------------------------
    //Bestimme die neuen Funktionswerte
    for(int i = 0; i < 4; i++)
    f4[i] = f[i] + dt*(5179.0/57600.0*k1[i]+ 0*k2[i] + 7571.0/16695.0*k3[i] + 393.0/640.0*k4[i] - 92097.0/339200.0*k5[i] + 187.0/2100.0*k6[i] + 1.0/40.0*k7[i]);

    for(int i = 0; i < 4; i++)
    f5[i] = f[i] + dt*(35.0/384.0*k1[i] + 0*k2[i] + 500.0/1113.0*k3[i] + 125.0/192.0*k4[i] - 2187.0/6784.0*k5[i] + 11.0/84.0*k6[i] + 0*k7[i]);
    //-----------------------------------------------------------------------------------
    //Bestimme die neue Schrittweite
    for(int i = 0; i < 4; i++)
    norm[i] = abs(f4[i]-f5[i]);
    
    max1 = max(norm[0],norm[1]);
    max2 = max(norm[2],norm[3]);
    Max = max(max1,max2);
   
    dt = q*dt*pow(tol/Max, 0.2);//neue schrittweite
    
    for(int i = 0; i < 4; i++)
    f[i] = f4[i];
    
    cout << n << "\t" << t << "\t" << dt << "\t" << f[0] << "\t" << f[2] << endl;
  }
    
  
  return 0;
}
  
  void func(double* k,double* f, const double m){//Unterfunktion mit DGL-System
  double  s = sqrt((f[0]-1+m)*(f[0]-1+m)+f[2]*f[2]);
  double  r = sqrt((f[0]+m)*(f[0]+m)+f[2]*f[2]);
  k[0] = f[1];
  k[1] = f[0] + 2.0*f[3] - ((1-m)*(f[0]+m))/(r*r*r) - m*(f[0]-1+m)/(s*s*s);
  k[2] = f[3];
  k[3] = f[2] - 2.0*f[1] - (1-m)*f[2]/(r*r*r) - m*f[2]/(s*s*s);
}