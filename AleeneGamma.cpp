// AleeneGamma.C

static const char* const HELP = "Applies gamma to a set of channels";

#include "DDImage/PixelIop.h"
#include "DDImage/Row.h"
#include "DDImage/Knobs.h"
#include <cmath>

using namespace DD::Image;

class AleeneGamma : public PixelIop
{
  float value[4];
public:
  void in_channels(int input, ChannelSet& mask) const;
  AleeneGamma(Node* node) : PixelIop(node)
  {
    value[0] = value[1] = value[2] = value[3] = 1.0f;
  }
  bool pass_transform() const { return true; }
  void pixel_engine(const Row &in, int y, int x, int r, ChannelMask, Row & out);
  virtual void knobs(Knob_Callback);
  static const Iop::Description d;
  const char* Class() const { return d.name; }
  const char* node_help() const { return HELP; }
  void _validate(bool);
};

void AleeneGamma::_validate(bool for_real)
{
  copy_info();
  for (unsigned i = 0; i < 4; i++) {
    if (value[i]) {
      set_out_channels(Mask_All);
      info_.black_outside(false);
      return;
    }
  }
  set_out_channels(Mask_None);
}

void AleeneGamma::in_channels(int input, ChannelSet& mask) const
{
  // mask is unchanged
}

/*
  Applies gamma using the equation from class.
*/
void AleeneGamma::pixel_engine(const Row& in, int y, int x, int r,
                       ChannelMask channels, Row& out)
{
  foreach (z, channels) {
    const float c = value[colourIndex(z)];
    const float* inptr = in[z] + x;
    const float* END = inptr + (r - x);
    float* outptr = out.writable(z) + x;
    while (inptr < END)
      *outptr++ = pow(*inptr++,1.0f/c);
  }
}

void AleeneGamma::knobs(Knob_Callback f)
{
  AColor_knob(f, value, IRange(0.01, 4), "value");
}

#include "DDImage/NukeWrapper.h"

static Iop* build(Node* node) { return new NukeWrapper(new AleeneGamma(node)); }
const Iop::Description AleeneGamma::d("AleeneGamma", "Color/Math/AleeneGamma", build);
