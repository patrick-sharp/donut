// https://www.a1k0n.net/2011/07/20/donut-math.html
// gcc -o donut donut.c -lm
// goals: sphere with rotating light source, translate donut but not rotation
// axis, cube
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int k;
double sin(), cos();
int main() {
  float A = 0, B = 0, phi, theta, zbuffer[1760];
  char output[1760];
  printf("\x1b[2J");
  for (;;) {
    memset(output, 32, 1760); // set all chars in output to ascii #32 (space)
    memset(zbuffer, 0, 7040);  // set all floats in z buffer to 0 (infinite distance from camera)
    // cross sectional circle of the torus
    for (theta = 0; 6.28 > theta; theta += 0.07)
      // center of revolution of the torus
      for (phi = 0; 6.28 > phi; phi += 0.02) {
        float sinPhi = sin(phi), cosTheta = cos(theta), sinA = sin(A), sinTheta = sin(theta), cosA = cos(A),
              circleX = cosTheta + 2, ooz = 1 / (sinPhi * circleX * sinA + sinTheta * cosA + 5), cosPhi = cos(phi),
              cosB = cos(B), sinB = sin(B),
              t = sinPhi * circleX * cosA - sinTheta * sinA;

        int x = 40 + 30 * ooz * (cosPhi * circleX * cosB - t * sinB),
            y = 12 + 15 * ooz * (cosPhi * circleX * sinB + t * cosB), o = x + 80 * y,
            N = 8 * ((sinTheta * sinA - sinPhi * cosTheta * cosA) * cosB - sinPhi * cosTheta * sinA - sinTheta * cosA - cosPhi * cosTheta *
            sinB); // N / 8 is between 0 and sqrt(2). N is between 0 and 11
        if (22 > y && y > 0 && x > 0 && 80 > x && ooz > zbuffer[o]) {
          zbuffer[o] = ooz;
          // assign a character for 
          // light level. N is dot product of surface normal with (x=0, y=1,
          // z=-1)
          output[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0]; 
        }
      }
    usleep(10000); // I added this to make it proceed at a non-ridiculous speed
    printf("\x1b[H"); for (k = 0; 1761 > k; k++) putchar(k % 80 ? output[k]
    : 10); // 10 is newline character. basically, print what's in the output
           // arr unless we're at the end of an 80 char row A += 0.04; // rotate around
           // the x axis (rolls towards the camera) B += 0.02; // rotate around the z
           // axis (clockwise from camera's perspective)
    A += 0.04;  // rotate around the x axis (rolls towards the camera)
    B += 0.02;  // rotate around the z axis (clockwise from camera's perspective)
  }
}

// *****************
// donut shaped code
// *****************
//
//              k;double sin()
//          ,cos();main(){float A=
//        0,B=0,i,j,z[1760];char b[
//      1760];printf("\x1b[2J");for(;;
//   ){memset(b,32,1760);memset(z,0,7040)
//   ;for(j=0;6.28>j;j+=0.07)for(i=0;6.28
//  >i;i+=0.02){float c=sin(i),d=cos(j),e=
//  sin(A),f=sin(j),g=cos(A),h=d+2,D=1/(c*
//  h*e+f*g+5),l=cos      (i),m=cos(B),n=s\
// in(B),t=c*h*g-f*        e;int x=40+30*D*
// (l*h*m-t*n),y=            12+15*D*(l*h*n
// +t*m),o=x+80*y,          N=8*((f*e-c*d*g
//  )*m-c*d*e-f*g-l        *d*n);if(22>y&&
//  y>0&&x>0&&80>x&&D>z[o]){z[o]=D;;;b[o]=
//  ".,-~:;=!*#$@"[N>0?N:0];}}/*#****!!-*/
//   printf("\x1b[H");for(k=0;1761>k;k++)
//    putchar(k%80?b[k]:10);A+=0.04;B+=
//      0.02;}}/*****####*******!!=;:~
//        ~::==!!!**********!!!==::-
//          .,~~;;;========;;;:~-.
//              ..,--------,*/