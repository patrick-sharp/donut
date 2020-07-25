// https://www.a1k0n.net/2011/07/20/donut-math.html
// gcc -o pseudonut pseudonut.c -lm
// like the pseudo-code on the site
// goals: sphere with rotating light source, translate donut but not rotation
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int k;
double sin(), cos();
int vanilla() {
  float A = 0, B = 0, phi, theta, zbuffer[1760];
  char output[1760];
  printf("\x1b[2J");
  for (;;) {
    memset(output, 32, 1760); // set all chars in output to ascii #32 (space)
    memset(zbuffer, 0, 7040);  // set all floats in z buffer to 0 (infinite distance from camera)
    // cross sectional circle of the torus
    for (theta = 0; 6.28 > theta; theta += 0.07) {
      // center of revolution of the torus
      for (phi = 0; 6.28 > phi; phi += 0.02) {

        float sinPhi = sin(phi), cosTheta = cos(theta), sinA = sin(A), sinTheta = sin(theta), cosA = cos(A),
              circleX = cosTheta + 2, ooz = 1 / (cosA * circleX * sinPhi + sinTheta * sinA + 5), cosPhi = cos(phi),
              cosB = cos(B), sinB = sin(B);

        float xContinuous = circleX * (cosB * cosPhi + sinA * sinB * sinPhi) - sinTheta * cosA * sinB;
        float yContinuous = circleX * (sinB * cosPhi - sinA * cosB * sinPhi) + sinTheta * cosA * cosB;

        int x = 40 + 30 * ooz * xContinuous, // x is the x value on the screen
            y = 12 + 15 * ooz * yContinuous, // y is the y value on the screen
            o = x + 80 * y;
            float L = cosPhi*cosTheta*sinB - cosA*cosTheta*sinPhi - sinA*sinTheta + cosB*(cosA*sinTheta - cosTheta*sinA*sinPhi);
        if (22 > y && y > 0 && x> 0 && 80 > x && ooz > zbuffer[o]) {
          zbuffer[o] = ooz;
          // assign a character for 
          // light level. N is dot product of surface normal with (x=0, y=1,
          // z=-1)
          int luminance_index = 8 * L;
          output[o] = ".,-~:;=!*#$@"[luminance_index > 0 ? luminance_index : 0]; 
        }
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

int mimic_original_donut() {
  // cos(B)*(sin(phi)*sin(theta) + circleX*cos(phi)) + cos(A)*sin(B)*(cos(phi)*sin(theta) - circleX*sin(phi))
  float A = 0, B = 0, phi, theta, zbuffer[1760];
  char output[1760];
  printf("\x1b[2J");
  for (;;) {
    memset(output, 32, 1760); // set all chars in output to ascii #32 (space)
    memset(zbuffer, 0, 7040);  // set all floats in z buffer to 0 (infinite distance from camera)
    // cross sectional circle of the torus
    for (theta = 0; 6.28 > theta; theta += 0.07) {
      // center of revolution of the torus
      for (phi = 0; 6.28 > phi; phi += 0.02) {

        float sinPhi = sin(phi), cosTheta = cos(theta), sinA = sin(A), sinTheta = sin(theta), cosA = cos(A),
              circleX = cosTheta + 2, /*ooz = 1 / (cosA * circleX * sinPhi + sinTheta * sinA + 5),*/ cosPhi = cos(phi),
              cosB = cos(B), sinB = sin(B);

        // float xContinuous = circleX * (cosB * cosPhi + sinA * sinB * sinPhi) - sinTheta * cosA * sinB;
        // float yContinuous = circleX * (sinB * cosPhi - sinA * cosB * sinPhi) + sinTheta * cosA * cosB;
        // float xContinuous = (cosPhi * circleX);
        // float yContinuous = -(sinPhi * circleX);
        sinA = -sinA; // changes the direction of the A rotation to match the original
        sinB = -sinB; // changes the direction of the B rotation to match the original
        float xContinuous = sinB * (sinA * sinTheta - circleX * cosA * sinPhi) + circleX * cosB * cosPhi;
        float yContinuous = cosB * (sinA * sinTheta - circleX * cosA * sinPhi) - circleX * sinB * cosPhi;
        float ooz = 1 / (cosA * sinTheta + circleX * sinA * sinPhi + 5);

        int x = 40 + 30 * ooz * xContinuous, // x is the x value on the screen
            y = 12 + 15 * ooz * yContinuous, // y is the y value on the screen
            o = x + 80 * y;
        // float L = cosPhi*cosTheta*sinB - cosA*cosTheta*sinPhi - sinA*sinTheta + cosB*(cosA*sinTheta - cosTheta*sinA*sinPhi);
        float L = sinA * (cosPhi * sinTheta - cosTheta * sinPhi) - sinB * (cosPhi * cosTheta + sinPhi * sinTheta) + cosA * cosB * (cosPhi * sinTheta - cosTheta * sinPhi);
        if (22 > y && y > 0 && x> 0 && 80 > x && ooz > zbuffer[o]) {
          zbuffer[o] = ooz;
          // assign a character for 
          // light level. N is dot product of surface normal with (x=0, y=1,
          // z=-1)
          int luminance_index = 8 * L;
          output[o] = ".,-~:;=!*#$@"[luminance_index > 0 ? luminance_index : 0]; 
        }
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

int main() {
  mimic_original_donut();
}

/*
some matlab code I used to do symbolic matrix math
yes, I know I should be using SymPy

syms theta phi A B circleX C D positive

prerot = [circleX, 0, sin(theta)]
phirot = [cos(phi), -sin(phi), 0; sin(phi), cos(phi), 0; 0, 0, 1]
Arot = [1, 0, 0; 0, cos(A), -sin(A); 0, sin(A), cos(A)]
Brot = [cos(B), -sin(B), 0; sin(B), cos(B), 0; 0, 0, 1]

normal_prerot = [cos(theta), sin(theta), 0]

*/