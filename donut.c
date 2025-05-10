// creating a rotating donut; rotating about x-axis and y-axis
// first to create a donut 'torus' we have to create a circle
// Let's assume, we have a circle on the xy-plane with radius r1
// if we rotate this circle(r1) about the y-axis by 2pi radians a 'torus' is
// obtained now again this torus should be spinning, right? So, linear algebra
// comes to help in here, we can multiply the coordinates by rotation matrix to
// rotate them about a given axis (the multiplication follows from right towards
// the left)
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

const int screen_width = 80;  // more like the space where the donut will render
const int screen_height = 80; // so dimension for the donut to render
const float r1 = 1.0;         // the radius of the cross-section-area
const float r2 = 2.0;         // the radius of the inner circle
const float k2 = 60; // the distance of the donut from the observer (used to//
                     // change the depth, flatness of the donut)
const float k1 = screen_width * k2 * 3 / (8 * (r1 + r2)); //
const float two_pi = 6.28;
const float theta_spacing = 0.07; // how the theta angle is incremented (how
                                  // dense the "pixels" are projected)
const float phi_spacing = 0.02;   // same as above (mostly)

int main(int argc, char *argv[]) {
  printf("\x1b[2J]"); // clear the screen
  float theta, phi,
      A = 0,
      B = 0; // angle of rotation about y,x,z axis respectively (theta is the
             // angle used to create the circle; by sweeping the coordinates
             // from 0-2pi) that will be incremented as the loop runs
             // angle A is about x-axis and angle B is about z-axis
  float sinA, sinB, cosA,
      cosB; // for easier calculations later on
  float zbuffer[screen_width * screen_height]; // z-buffer to store the
  char c[screen_width *
         screen_height]; // store all the characters that'll be ploted on the
                         // screen, all the "pixels" of the donut
  for (;;) {
    memset(c, 32, screen_width * screen_height); // clear the entire c array
    memset(zbuffer, 0,
           screen_height * screen_width *
               sizeof(float)); // initialize the entire zbuffer

    sinA = sin(A);
    sinB = sin(B);
    cosA = cos(A);
    cosB = cos(B);

    // this theta loop contributes in the pixels around y-axis i.e. the cross
    // section
    for (theta = 0; theta <= two_pi; theta += theta_spacing) {
      float cos_theta = cos(theta),
            sin_theta = sin(
                theta); // making things easier by calculating standard values
      // this phi loop contributes to the revolution of the torus
      for (phi = 0; phi <= two_pi; phi += phi_spacing) {
        float cos_phi = cos(phi), sin_phi = sin(phi);

        // coordinates of the circle before revolving
        float circle_x =
            r2 + r1 * cos_theta; // since x=rcostheta and it is offset by
                                 // r2(which was the radis of the inner circle
                                 // of the torus)
        float circle_y = r1 * sin_theta;
        // from our formula obtained by the multiplication with rotation matrix
        float x = 1 + circle_x * (cosB * cos_phi + sinA * sinB * sin_phi) -
                  circle_y * cosA * sinB;
        // same as above
        float y = 0.5 + circle_x * (sinB * cos_phi - sinA * cosB * sin_phi) +
                  circle_y * cosA * cosB;
        // the depth
        // this z is calculated by adding k2 which helps in 'offsetting' the
        // projection, so that incase z=0 then adding k2 will shift it away from
        // the screen, towards the viewing frustum this z value is the sum of
        // k2(to remove cases of 0 and -ve) and others are just calculated after
        // rotation about the y-axis,x-axis
        float z_val = k2 + cosA * circle_x * sin_phi + circle_y * sinA;
        float ooz = 1 / z_val; // if ooz = 0 ; then z = oo (infinity) meaning it
                               // is the farthest
        int xp =
            (int)(screen_width / 2 +
                  k1 * ooz *
                      x); // from the perspective projection formula and the
                          // screen_width/2 helps in centering the donut
        int yp = (int)(screen_height / 2 + 2 + k1 * ooz * y);

        // multiplying the surface normal with the <0,1,-1>(the direction of the
        // source of light) (i.e behind and above the observer)
        float L = cos_phi * cos_theta * sinB - cosA * cos_theta * sin_phi -
                  sinA * sin_theta +
                  cosB * (cosA * sin_theta - cos_theta * sinA * sin_phi);

        int index = yp * screen_width + xp;
        if (L > 0) { // if the L is greater than zero the surface is facing the
                     // light(high intensity)
          if (yp >= 0 && yp < screen_height && xp >= 0 && xp < screen_width &&
              ooz > zbuffer[index]) {
            int luminance_index = 8 * L;
            zbuffer[index] = ooz; // replace the depth value
            c[index] = ".,-~:;=!*#$@"[luminance_index];
          }
        }
      }
    }
    printf("\x1b[H"); // reset cursor position to home i.e. top left
    for (int i = 0; i < screen_height; i++) {
      for (int j = 0; j < screen_width; j++) {
        putchar(c[i * screen_width + j]);
      }
      putchar('\n');
    }
    // update the rotating angle for the x and z axis respectively
    A += 0.04;
    B += 0.02;
    usleep(30000);
  }
  return 0;
}
