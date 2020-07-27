// https://www.a1k0n.net/2011/07/20/donut-math.html
// gcc -o pseudonut pseudonut.c -lm
// like the pseudo-code on the site
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int k;
double sin(), cos();
// exactly like pseudocode
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

// exactly like donut.c
int mimic_original_donut() {
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

        float xContinuous = sinB * (sinA * sinTheta - circleX * cosA * sinPhi) + circleX * cosB * cosPhi;
        float yContinuous = cosB * (sinA * sinTheta - circleX * cosA * sinPhi) - circleX * sinB * cosPhi;
        float ooz = 1 / (cosA * sinTheta + circleX * sinA * sinPhi + 5);

        int x = 40 + 30 * ooz * xContinuous, // x is the x value on the screen
            y = 24 - (12 + 15 * ooz * yContinuous), // y is the y value on the screen
            o = x + 80 * y;
        float L = cosB * (sinA * sinTheta - cosA * cosTheta * sinPhi) - cosA * sinTheta - sinB * cosPhi * cosTheta - sinA * cosTheta * sinPhi;
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

int rotating_light_source() {
  float A = 0, B = 0, phi, theta, zbuffer[1760];
  float C = 0, D = 0, E = 0; // these are like A and B, but they rotate the light source
  char output[1760];
  float L;
  int luminance_index;
  // printf("\x1b[2J");
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

        float xContinuous = sinB * (sinA * sinTheta - circleX * cosA * sinPhi) + circleX * cosB * cosPhi;
        float yContinuous = cosB * (sinA * sinTheta - circleX * cosA * sinPhi) - circleX * sinB * cosPhi;
        float ooz = 1 / (cosA * sinTheta + circleX * sinA * sinPhi + 5);

        int x = 40 + 30 * ooz * xContinuous, // x is the x value on the screen
            y = 24 - (12 + 15 * ooz * yContinuous), // y is the y value on the screen
            o = x + 80 * y;

        // float L = cosB * (sinA * sinTheta - cosA * cosTheta * sinPhi) - cosA * sinTheta - sinB * cosPhi * cosTheta - sinA * cosTheta * sinPhi;
        float sinC = sin(C), cosC = cos(C), sinD = sin(D), cosD = cos(D), sinE = sin(E), cosE = cos(E);
        L = (sinE*(cosC - sinC) + cosE*sinD*(cosC + sinC))*(sinB*(sinA*sinTheta - cosA*cosTheta*sinPhi) + cosB*cosPhi*cosTheta) + (cosE*(cosC - sinC) - sinD*sinE*(cosC + sinC))*(cosB*(sinA*sinTheta - cosA*cosTheta*sinPhi) - cosPhi*cosTheta*sinB) - cosD*(cosC + sinC)*(cosA*sinTheta + cosTheta*sinA*sinPhi);

        if (22 > y && y > 0 && x> 0 && 80 > x && ooz > zbuffer[o]) {
          zbuffer[o] = ooz;
          // assign a character for 
          // light level. N is dot product of surface normal with (x=0, y=1,
          // z=-1)
          luminance_index = 8 * L;
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

    // rotate the light source
    C += 0.04;
    D += 0.02;
    E += 0.03;
  }
}

int main() {
  // vanilla();
  // mimic_original_donut();
  rotating_light_source();
  // float C, D, E = 0; // these are like A and B, but they rotate the light source
  // printf("%f, %f, %f\n", C, D, E);
  // float F, G, H, I, J, K, l, M, O, P = 0;
  // printf("%f, %f, %f, %f, %f, %f, %f, %f, %f, %f\n", F, G, H, I, J, K, l, M, O, P);
}

/* some matlab code I used to do symbolic matrix math

syms theta phi A B circleX C D real

prerot = [circleX, 0, sin(theta)]
phirot = [cos(phi), -sin(phi), 0; sin(phi), cos(phi), 0; 0, 0, 1]
Arot = [1, 0, 0; 0, cos(A), -sin(A); 0, sin(A), cos(A)]
Brot = [cos(B), -sin(B), 0; sin(B), cos(B), 0; 0, 0, 1]

normal_prerot = [cos(theta), 0, sin(theta)]
normal_vector = normal_prerot * phirot * Arot * Brot
% for a fixed light source
luminance = normal_vector * [0; 1; -1]

% for a rotating light source
Crot = [1, 0, 0; 0, cos(C), -sin(C); 0, sin(C), cos(C)]
Drot = [cos(D), -sin(D), 0; sin(D), cos(D), 0; 0, 0, 1]
light_vector = [0, 1, -1] * Crot * Drot
luminance = dot(normal_vector, light_vector)


% with all of the trig functions as their own symbol for easy copy paste + precomputing
syms sinTheta cosTheta sinPhi cosPhi sinA cosA sinB cosB circleX sinC cosC sinD cosD sinE cosE real

prerot = [circleX, 0, sinTheta]
phirot = [cosPhi, -sinPhi, 0; sinPhi, cosPhi, 0; 0, 0, 1]
Arot = [1, 0, 0; 0, cosA, -sinA; 0, sinA, cosA]
Brot = [cosB, -sinB, 0; sinB, cosB, 0; 0, 0, 1]

normal_prerot = [cosTheta, 0, sinTheta]
normal_vector = normal_prerot * phirot * Arot * Brot

% rotating light source
Crot = [1, 0, 0; 0, cosC, -sinC; 0, sinC, cosC] % x axis
Drot = [cosD, 0, sinD; 0, 1, 0; -sinD, 0, cosD] % y axis
Erot = [cosE, -sinE, 0; sinE, cosE, 0; 0, 0, 1] % z axis
light_vector = [0, 1, -1] * Crot * Drot * Erot
light_vector = [0, 1, -1] * Drot
luminance = dot(normal_vector, light_vector)

% static donut, moving light source around y
syms sinTheta cosTheta sinPhi cosPhi sinA cosA sinB cosB circleX sinC cosC sinD cosD sinE cosE real

prerot = [circleX, 0, sinTheta]
phirot = [cosPhi, -sinPhi, 0; sinPhi, cosPhi, 0; 0, 0, 1]

normal_prerot = [cosTheta, 0, sinTheta]
normal_vector = normal_prerot * phirot

% rotating light source
Crot = [1, 0, 0; 0, cosC, -sinC; 0, sinC, cosC] % x axis
Drot = [cosD, 0, sinD; 0, 1, 0; -sinD, 0, cosD] % y axis
Erot = [cosE, -sinE, 0; sinE, cosE, 0; 0, 0, 1] % z axis
% light_vector = [0, 1, -1] * Crot * Drot * Erot
light_vector = [0, 1, -1] * Drot
luminance = dot(normal_vector, light_vector)

*/