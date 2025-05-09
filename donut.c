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
const float k2 = 5; // the distance of the donut from the observer (used to
                    // change the depth, flatness of the donut)

int main(int argc, char *argv[]) {
  printf("\x1b[2J]");        // clear the screen
  float theta, A = 0, B = 0; // angle of rotation about y,x,z axis respectively
                             // that will be incremented as the loop runs
  float z[1760];             // z-buffer to store the
  char c[1760];
  for (;;) {
    memset(c, 32, 1760); // the screen size is taken as 80x22(columsxrows)| 32 is the ascii code for ' ' <space> so 
    // it's just filling the array c with empty space
    memset(z, 0, 7040); // why? // since it's all float(size 4) so 4 * 1760(no of )
  }

  return 0;
}
