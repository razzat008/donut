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

const float r1 = 1; // the radius of the cross-section-area
const float r2 = 2; // the radius of the inner circle
const float k1 = 2; // distance of the screen from the observer
const float k2 = 5; // the distance of the donut from the observer (used to//
                    // change the depth, flatness of the donut)
const float two_pi = 6.28;
const float theta_spacing = 0.07; // how the theta angle is incremented (how
                                  // dense the "pixels" are projected)
const float phi_spacing = 0.02;   // same as above (mostly)
const int screen_width = 100; // more like the space where the donut will render
const int screen_height = 50; // so dimension for the donut to render

int main(int argc, char *argv[]) {
  printf("\x1b[2J]"); // clear the screen
  float theta = 0, phi = 0, A = 0,
        B = 0; // angle of rotation about y,x,z axis respectively
               // that will be incremented as the loop runs
  float sinA = sin(A), sinB = sin(B), cosA = cos(A),
        cosB = cos(B); // for easier calculations later on
  float z[1760];       // z-buffer to store the
  char c[1760]; // store all the characters that'll be ploted on the screen, all
                // the "pixels" of the donut
  for (;;) {
    memset(c, 32, 1760); // the screen size is taken as 80x22(columsxrows)| 32
                         // is the ascii code for ' ' <space> so
    // it's just filling the array c with empty space
    memset(z, 0,
           7040); // why? // since it's all float(size 4) so 4 * 1760(no of )
    // but why zero tho? it's due to the projection formula (will talk about it
    // more)
    for (theta; theta <= two_pi; theta += theta_spacing) {
      float cos_theta = cos(theta),
            sin_theta = sin(
                theta); // making things easier by calculating standard values
      for (phi; phi <= two_pi; phi += phi_spacing) {
        float cos_phi = cos(phi), sin_phi = sin(phi);

        // coordinates of the circle before revolving
        float circle_x =
            r2 + r1 * cos_theta; // since x=rcostheta  and it is offset by
                                 // r2(which was the radis of the inner circle
                                 // of the torus)
        float circle_y = r1 * sin_theta;
        // from our formula obtained by the multiplication with rotation matrix
        float x = circle_x * (cosB * cos_phi + sinA * sinB * sin_phi) -
                  circle_y * cosA * sinB;
        // same as above
        float y = circle_x * (sinB * cos_phi - sinA * cosB * sin_phi) +
                  circle_y * cosA * cosB;
        float z = k2 + cosA * circle_x * sin_phi + circle_y * sinA; // the depth
        float ooz = 1 / z; // cases of inifinity
        //
        // multiplying the surface normal with the <0,1,-1>(the direction of the
        // source of light) (i.e behind and above the observer)
        float L = cos_phi * cos_theta * sinB - cosA * cos_theta * sin_phi -
                  sinA * sin_theta +
                  cosB * (cosA * sin_theta - cos_theta * sinA * sin_phi);

        if (L > 0) { // if the L is greater than zero the surface is facing the
                     // light(high intensity)
        }
      }
    }
  }

  return 0;
}
