

static const char* const CLASS = "AleeneMedian";

static const char* const HELP =
  "Does a simple box blur";

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

class AleeneMedian : public Iop
{

  int _size;

public:

  int maximum_inputs() const { return 1; }
  int minimum_inputs() const { return 1; }
  virtual void knobs(Knob_Callback);

  //! Constructor. Initialize user controls to their default values.

  AleeneMedian (Node* node) : Iop (node)
  {
    _size = 20;
  }

  ~AleeneMedian () {}

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
static Iop* AleeneMedianCreate(Node* node)
{
  return new AleeneMedian(node);
}

/*! The Iop::Description is how NUKE knows what the name of the operator is,
   how to create one, and the menu item to show the user. The menu item may be
   0 if you do not want the operator to be visible.
 */
const Iop::Description AleeneMedian::description ( CLASS, "Merge/AleeneMedian",
                                                     AleeneMedianCreate );


void AleeneMedian::_validate(bool for_real)
{
  copy_info(); // copy bbox channels etc from input0, which will validate it.
  info_.pad( _size);

}

void AleeneMedian::_request(int x, int y, int r, int t, ChannelMask channels, int count)
{
  // request extra pixels around the input
  input(0)->request( x - _size , y - _size , r + _size, t + _size, channels, count );
}


/*
  Does median to reduce noise
*/
void AleeneMedian::engine ( int y, int x, int r,
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
      std::vector<float> v;

      if ( intersect( tile.channels(), z ) ) {
        for ( int px = -_size; px < _size; px++ ) {
          for ( int py = -_size; py < _size; py++ ) {
            //stores all values
            v.push_back( tile[z][ tile.clampy(y + py)][ tile.clampx(cur + px) ]);
          }
        }
        //sorts values
        sort(v.begin(),v.end());

        //finds middle and returns
        if(v.size() % 2 != 0) {
          *outptr++ = v.at(v.size() / 2);
        }
        else {
          *outptr++ = (v.at((v.size()- 1 )/ 2) + v.at(v.size() / 2)) / 2.0;
        }
      }
    }
  }
}

void AleeneMedian::knobs(Knob_Callback f)
{
  Int_knob(f, &_size, "size");
}
