// Project UID af1f95f547e44c8ea88730dfb185559d

#include "Matrix.h"
#include "Image_test_helpers.h"
#include "unit_test_framework.h"
#include <iostream>
#include <string>
#include <sstream>
#include <cassert>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());

  delete img; // delete the Image
}

// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.h as needed.

//Image Width Test
TEST(Image_width)
{
  Image *img = new Image;
  Image_init(img, 1, 2);

  ASSERT_EQUAL(1,Image_width(img));
  
  delete img;
}

//Image Height Test
TEST(Image_Height)
{
  Image *img = new Image;
  Image_init(img, 2, 4);

  ASSERT_EQUAL(4,Image_height(img));
  
  delete img;
}

//Image basic init test
TEST(Basic_img_init)
{
  Image *img = new Image;
  Image_init(img, 2, 3);

  ASSERT_EQUAL(2,Image_width(img));
  ASSERT_EQUAL(3,Image_height(img));

  delete img;
}

//Filled Image Test
TEST(Filled_img_init) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 3);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);
  Image_set_pixel(img, 2, 0, blue);
  Image_set_pixel(img, 2, 1, white);

  // Capture our output
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 3\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());
  ASSERT_EQUAL(2,Image_width(img));
  ASSERT_EQUAL(3,Image_height(img));

  delete img; // delete the Image
}

//Image get pixel test
TEST(Image_get_pixel) {
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  Pixel pix = Image_get_pixel(img, 0, 1);
  ASSERT_EQUAL(0, pix.r);
  ASSERT_EQUAL(255, pix.g);
  ASSERT_EQUAL(0, pix.b);

  delete img;
}

TEST(Image_set_pixel)
{
  Image *img = new Image; // create an Image in dynamic memory

  const Pixel red = {255, 0, 0};
  const Pixel green = {0, 255, 0};
  const Pixel blue = {0, 0, 255};
  const Pixel white = {255, 255, 255};

  Image_init(img, 2, 2);
  Image_set_pixel(img, 0, 0, red);
  Image_set_pixel(img, 0, 1, green);
  Image_set_pixel(img, 1, 0, blue);
  Image_set_pixel(img, 1, 1, white);

  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img,0,0),red));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img,0,1),green));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img,1,0),blue));
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img,1,1),white));
  delete img;
}

//Image fill Test
TEST(Image_fill)
{
  Image *img = new Image;
  Image_init(img, 3, 3);
  Pixel color  = {0,255,0};
  Image_fill(img, color);

  Image *img1 = new Image;
  Image_init(img1,3,3);
  Image_set_pixel(img1, 0,0,color);
  Image_set_pixel(img1, 0,1,color);
  Image_set_pixel(img1, 0,2,color);
  Image_set_pixel(img1, 1,0,color);
  Image_set_pixel(img1, 1,1,color);
  Image_set_pixel(img1, 1,2,color);
  Image_set_pixel(img1, 2,0,color);
  Image_set_pixel(img1, 2,1,color);
  Image_set_pixel(img1, 2,2,color);

  ASSERT_TRUE(Image_equal(img, img1));
  delete img;
  delete img1;

}

TEST (Insane_init_small)
{
  Image *img = new Image;
  Image_init(img,1,1);
  Pixel fish = {0,1,0};
  Image_set_pixel(img,0,0,fish);
  ASSERT_TRUE(Pixel_equal(Image_get_pixel(img,0,0),fish));
  ASSERT_EQUAL(Image_width(img),1);
  ASSERT_EQUAL(Image_height(img),1);
  delete img;
}

TEST (Insane_Image_pretty_big)
{
  Image *img = new Image;
  Image_init(img,30,50);
  Pixel fish = {0,1,0};
  Pixel corn = {0,1,0};
  Image_fill(img,fish);
  for(int i = 0; i < 15; ++i)
    {
      for(int j = 0; j < 30; ++j)
      {
        Image_set_pixel(img,i,j,corn);
      }
    }
  for(int i = 0; i < 15; ++i)
    {
      for(int j = 0; j < 30; ++j)
      {
        ASSERT_TRUE(Pixel_equal(Image_get_pixel(img,i,j),corn));
      }
    }
  for(int i = 15; i < 50; ++i)
    {
      for(int j = 0; j < 30; ++j)
      {
        ASSERT_TRUE(Pixel_equal(Image_get_pixel(img,i,j),fish));
      }
    }
    delete img;
}

TEST(Image_init_stream)
{
  Image *img = new Image;
  istringstream in("P3\n2 2\n255\n255 0 0 0 255 0 \n0 0 255 255 255 255 \n");
  Image_init(img,in);
  ostringstream s;
  Image_print(img, s);

  // Correct output
  ostringstream correct;
  correct << "P3\n2 2\n255\n";
  correct << "255 0 0 0 255 0 \n";
  correct << "0 0 255 255 255 255 \n";
  ASSERT_EQUAL(s.str(), correct.str());
  delete img;
}

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
