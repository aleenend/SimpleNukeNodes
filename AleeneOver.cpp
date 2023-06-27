

static const char* const CLASS = "AleeneOver";

static const char* const HELP =
  "Merges two images together with the second over the first";

// Standard plug-in include files.

#include "DDImage/Iop.h"
#include "DDImage/NukeWrapper.h"
using namespace DD::Image;
#include "DDImage/Row.h"
#include "DDImage/Tile.h"
#include "DDImage/Knobs.h"

using namespace std;

class AleeneOver : public Iop
{
  float mix;
public:

  int minimum_inputs() const { return 2; }
  int maximum_inputs() const { return 2; }
  virtual void knobs(Knob_Callback);

  //! Constructor. Initialize user controls to their default values.

  AleeneOver (Node* node) : Iop (node)
  {
    mix = 1.0f;
  }

  ~AleeneOver () {}

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
static Iop* AleeneOverCreate(Node* node)
{
  return new AleeneOver(node);
}

/*! The Iop::Description is how NUKE knows what the name of the operator is,
   how to create one, and the menu item to show the user. The menu item may be
   0 if you do not want the operator to be visible.
 */
const Iop::Description AleeneOver::description ( CLASS, "Merge/AleeneOver",
                                                     AleeneOverCreate );


void AleeneOver::_validate(bool for_real)
{
  copy_info(); // copy bbox channels etc from input0
  merge_info(1); // merge info from input 1
}

void AleeneOver::_request(int x, int y, int r, int t, ChannelMask channels, int count)
{
  // request from input 0 and input 1
  input(0)->request( x, y, r, t, channels, count );
  input(1)->request( x, y, r, t, channels, count );
}



void AleeneOver::engine ( int y, int x, int r,
                              ChannelMask channels, Row& row )
{
  // input 0 row
  row.get(input0(), y, x, r, channels);

  // input 1 row
  Row input1Row(x, r);
  input1Row.get(input1(), y, x, r, channels);

  foreach ( z, channels ) {
    const float* input1 = input1Row[z] + x;
    const float* input0  = row[z] + x;
    float* outptr = row.writable(z) + x;
    const float* end = outptr + (r - x);
    float M = 0.0;

    //gets matte val by dividing by alpha
    if(colourIndex(z) == 3) {
      M = *input0 / channels;
    }

    while (outptr < end) {
      //A premult + ((1-M)B)
      *outptr++ = *input0++ + mix * ((1.0 - M) * *input1++);
    }
  }
}

void AleeneOver::knobs(Knob_Callback f)
{
  Float_knob(f, &mix, IRange(0, 1), "mix");
}
