// AleeneContrast.C

static const char* const HELP = "Adjust contrast in image";

#include "DDImage/PixelIop.h"
#include "DDImage/Row.h"
#include "DDImage/Knobs.h"
#include <cmath>

using namespace DD::Image;

class AleeneContrast : public PixelIop
{
  float gain[4];
  float bias[4];
public:
  void in_channels(int input, ChannelSet& mask) const;
  AleeneContrast(Node* node) : PixelIop(node)
  {
    gain[0] = gain[1] = gain[2] = gain[3] = 1.0f;
    bias[0] = bias[1] = bias[2] = bias[3] = 0.0f;
  }
  bool pass_transform() const { return true; }
  void pixel_engine(const Row &in, int y, int x, int r, ChannelMask, Row & out);
  virtual void knobs(Knob_Callback);
  static const Iop::Description d;
  const char* Class() const { return d.name; }
  const char* node_help() const { return HELP; }
  void _validate(bool);
};

void AleeneContrast::_validate(bool for_real)
{
  copy_info();
  for (unsigned i = 0; i < 4; i++) {
    if (gain[i]) {
      set_out_channels(Mask_All);
      info_.black_outside(false);
      return;
    }
    if (bias[i]) {
      set_out_channels(Mask_All);
      info_.black_outside(false);
      return;
    }
  }
  set_out_channels(Mask_None);
}

void AleeneContrast::in_channels(int input, ChannelSet& mask) const
{
  // mask is unchanged
}

/*
  Applies contrast using values I call bias and gain having no idea if those
  are correct, but I saw it online.
*/
void AleeneContrast::pixel_engine(const Row& in, int y, int x, int r,
                       ChannelMask channels, Row& out)
{
  foreach (z, channels) {
    const float g = gain[colourIndex(z)];
    const float b = bias[colourIndex(z)];
    const float* inptr = in[z] + x;
    const float* END = inptr + (r - x);
    float* outptr = out.writable(z) + x;
    while (inptr < END)
      //contrast equation from book
      *outptr++ = (*inptr++ - b) * g ;
  }
}

void AleeneContrast::knobs(Knob_Callback f)
{
  AColor_knob(f, gain, IRange(0.01, 4), "gain");
  AColor_knob(f, bias, IRange(-1,1), "bias");
}

#include "DDImage/NukeWrapper.h"

static Iop* build(Node* node) { return new NukeWrapper(new AleeneContrast(node)); }
const Iop::Description AleeneContrast::d("AleeneContrast", "Color/Math/AleeneContrast", build);
