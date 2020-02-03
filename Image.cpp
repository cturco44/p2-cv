// Project UID af1f95f547e44c8ea88730dfb185559d

#include <cassert>
#include "Image.h"

// REQUIRES: img points to an Image
//           0 < width && width <= MAX_MATRIX_WIDTH
//           0 < height && height <= MAX_MATRIX_HEIGHT
// MODIFIES: *img
// EFFECTS:  Initializes the Image with the given width and height.
// NOTE:     Do NOT use new or delete here.
void Image_init(Image* img, int width, int height) {
  
  img->width = width;
  img->height = height;
  Matrix_init(&(img->red_channel), width, height);
  Matrix_init(&(img->green_channel), width, height);
  Matrix_init(&(img->blue_channel), width, height);
}

// REQUIRES: img points to an Image
//           is contains an image in PPM format without comments
//           (any kind of whitespace is ok)
// MODIFIES: *img
// EFFECTS:  Initializes the Image by reading in an image in PPM format
//           from the given input stream.
// NOTE:     See the project spec for a discussion of PPM format.
// NOTE:     Do NOT use new or delete here.
void Image_init(Image* img, std::istream& is) {
  //Read in information from is
  
  //Check file format
  char check[2];
  is >> check;
  assert(check[0] == 'P' && check[1] == '3');
  
  //Read in width and height
  is >> img->width >> img->height;

  //Read in max
  int max;
  is >> max;

  //Initialize Matrices
  Matrix_init(&(img->red_channel), Image_width(img), Image_height(img));
  Matrix_init(&(img->green_channel), Image_width(img), Image_height(img));
  Matrix_init(&(img->blue_channel), Image_width(img), Image_height(img));

  //Read in values
  for(int i = 0; i < Image_height(img); ++i)
    {
      for(int j = 0; j < Image_width(img); ++j)
      {
        Pixel pix;
        is >> pix.r >> pix.g >> pix.b;
        Image_set_pixel(img, i, j, pix);
      }
    }
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Writes the image to the given output stream in PPM format.
//           You must use the kind of whitespace specified here.
//           First, prints out the header for the image like this:
//             P3 [newline]
//             WIDTH [space] HEIGHT [newline]
//             255 [newline]
//           Next, prints out the rows of the image, each followed by a
//           newline. Each pixel in a row is printed as three ints
//           for its red, green, and blue components, in that order. Each
//           int is followed by a space. This means that there will be an
//           "extra" space at the end of each line. See the project spec
//           for an example.
void Image_print(const Image* img, std::ostream& os) {
  os << "P3\n" << Image_width(img) << " " << Image_height(img) << '\n' << "255" << '\n';
  for(int i = 0; i < Image_height(img); ++i)
  {
    for(int j = 0; j < Image_width(img); ++j)
    {
      Pixel pix = Image_get_pixel(img, i, j);
      os << pix.r << " " << pix.g << " " << pix.b << " ";
    }
    os << '\n';
  }

}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the width of the Image.
int Image_width(const Image* img) {
  return img->width;
}

// REQUIRES: img points to a valid Image
// EFFECTS:  Returns the height of the Image.
int Image_height(const Image* img) {
  return img->height;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// EFFECTS:  Returns the pixel in the Image at the given row and column.
Pixel Image_get_pixel(const Image* img, int row, int column) {
  //Check required
  assert(0 <= row && row < Image_height(img));
  assert(0 <= column && column < Image_width(img));
  
  //Grab reference to matrix 
  const Matrix* red = &(img->red_channel);
  const Matrix* blue = &(img->blue_channel);
  const Matrix* green = &(img->green_channel);

  //Grab reference to element in matrix
  const int* r = Matrix_at(red, row, column);
  const int* b = Matrix_at(blue,row,column);
  const int* g = Matrix_at(green,row,column);

  //Dereference and store in pixel
  Pixel pix;
  pix.r = *r;
  pix.b = *b;
  pix.g = *g;

  return pix;
}

// REQUIRES: img points to a valid Image
//           0 <= row && row < Image_height(img)
//           0 <= column && column < Image_width(img)
// MODIFIES: *img
// EFFECTS:  Sets the pixel in the Image at the given row and column
//           to the given color.
void Image_set_pixel(Image* img, int row, int column, Pixel color) {
  //Check required
  assert(0 <= row && row < Image_height(img));
  assert(0 <= column && column < Image_width(img));
  
  //Grab reference to matrix
  *Matrix_at(&(img->red_channel), row, column) = color.r;
  *Matrix_at(&(img->green_channel), row, column) = color.g;
  *Matrix_at(&(img->blue_channel), row, column) = color.b;
}

// REQUIRES: img points to a valid Image
// MODIFIES: *img
// EFFECTS:  Sets each pixel in the image to the given color.
void Image_fill(Image* img, Pixel color) {
  //Use matrix fill function to modify values of each matrix
  Matrix_fill(&(img->red_channel),color.r);
  Matrix_fill(&(img->blue_channel),color.b);
  Matrix_fill(&(img->green_channel),color.g);
}
