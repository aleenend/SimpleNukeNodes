

static const char* const CLASS = "AleeneSharpen";

static const char* const HELP =
  "Does a simple sharpen";

// Standard plug-in include files.

#include "DDImage/Iop.h"
#include "DDImage/NukeWrapper.h"
using namespace DD::Image;
#include "DDImage/Row.h"
#include "DDImage/Tile.h"
#include "DDImage/Knobs.h"
#include <vector>
#include <algorithm>

using namespace std;

class AleeneSharpen : public Iop
{

  int _size;

public:

  int maximum_inputs() const { return 1; }
  int minimum_inputs() const { return 1; }

  //! Constructor. Initialize user controls to their default values.

  AleeneSharpen (Node* node) : Iop (node)
  {
    _size = 1;
  }

  ~AleeneSharpen () {}

  void _validate(bool);
  void _request(int x, int y, int r, int t, ChannelMask channels, int count);

  //! This function does all the work.

  void engine ( int y, int x, int r, ChannelMask channels, Row& out );

  //! Return the name of the class.

  const char* Class() const { return CLASS; }
  const char* node_help() const { return HELP; }

  //! Information to the plug-in manager of DDNewImage/Nuke.

  static const Iop::Description description;

};


/*! This is a function that creates an instance of the operator, and is
   needed for the Iop::Description to work.
 */
static Iop* AleeneSharpenCreate(Node* node)
{
  return new AleeneSharpen(node);
}

/*! The Iop::Description is how NUKE knows what the name of the operator is,
   how to create one, and the menu item to show the user. The menu item may be
   0 if you do not want the operator to be visible.
 */
const Iop::Description AleeneSharpen::description ( CLASS, "Merge/AleeneSharpen",
                                                     AleeneSharpenCreate );


void AleeneSharpen::_validate(bool for_real)
{
  copy_info(); // copy bbox channels etc from input0, which will validate it.
  info_.pad( _size);

}

void AleeneSharpen::_request(int x, int y, int r, int t, ChannelMask channels, int count)
{
  // request extra pixels around the input
  input(0)->request( x - _size , y - _size , r + _size, t + _size, channels, count );
}


/*
  Performs sharpen by checking a 3x3 area of pixels
*/
void AleeneSharpen::engine ( int y, int x, int r,
                              ChannelMask channels, Row& row )
{

  // make a tile for current line with padding arond for the blur
  Tile tile( input0(), x - _size , y - _size , r + _size, y + _size , channels);
  if ( aborted() ) {
    std::cerr << "Aborted!";
    return;
  }


  foreach ( z, channels ) {
    float* outptr = row.writable(z) + x;
    for( int cur = x ; cur < r; cur++ ) {
      float value = 0;
      float val = 0.0;
      float div = 0;
      float arr[3][3] = { {0.0,-1.0,0.0}, {-1.0,5.0,-1.0}, {0.0,-1.0,0.0}};

      if ( intersect( tile.channels(), z ) ) {
        //sharpens image
        for ( int px = -_size; px < _size; px++ ) {
          for ( int py = -_size; py < _size; py++ ) {
            //val necessary because the math didn't work right in the array
            val = tile[z][ tile.clampy(y + py)][ tile.clampx(cur + px) ];
            val *= arr[px + 1][py + 1];
            value += val;
            div++;
          }
        }
        if ( div )
          value /= div;
      }
      *outptr++ = value;
    }
  }
}
