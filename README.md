# SimpleNukeNodes
A few simple nodes written for Nuke in a Visual Effects and Compositing course at Clemson University. All code is based on sample code provided by the instructor.

AleeneContrast:
Changes the contrast of an image using bias and gain. Adds knobs to control bias and gain within Nuke.

<img src="https://github.com/aleenend/SimpleNukeNodes/assets/59891824/53ac072d-0878-480a-bcdd-69b85dc62f26" alt="original" width="350" height="200"> &emsp; <img src="https://github.com/aleenend/SimpleNukeNodes/assets/59891824/75ece9ba-b4d8-45c0-a85c-d02317f3f44c" width="350" height="200">


AleeneGamma:
Changes gamma of an image and will not go lower than 0.01. Adds knob to control gamma within Nuke.

<img src="https://github.com/aleenend/SimpleNukeNodes/assets/59891824/f9bd496c-03c3-4a64-ab3d-ba393e33db62" width="350" height="200"> &emsp; <img src="https://github.com/aleenend/SimpleNukeNodes/assets/59891824/29e3774d-dc2c-482d-8062-71665d5d07ff" width="350" height="200"> 


AleeneMedian:
Finds and applies median value to image by sorting pixels. Adds knob to control size within Nuke. Default size is 20.

<img src="https://github.com/aleenend/SimpleNukeNodes/assets/59891824/f9bd496c-03c3-4a64-ab3d-ba393e33db62" width="350" height="200"> &emsp; <img src="https://github.com/aleenend/SimpleNukeNodes/assets/59891824/fb43bccd-1ebf-494f-8870-2cd2c013cf43" width="350" height="200"> 


AleeneOver:
Superimposes one image over another using the equation image A + (1 - M) * image B. Divides image A by its alpha channel to get value for M. Adds knob to control "mix" of the two images similar to the merge node.

<img src="https://github.com/aleenend/SimpleNukeNodes/assets/59891824/f9bd496c-03c3-4a64-ab3d-ba393e33db62" width="350" height="200"> &emsp; <img src="https://github.com/aleenend/SimpleNukeNodes/assets/59891824/45573124-aad0-4b32-bc96-561d56194cd2" width="350" height="200"> &emsp; <img src="https://github.com/aleenend/SimpleNukeNodes/assets/59891824/5c9906c4-2025-4530-afab-d9e86619dbb5" width="350" height="200"> 


AleeneSharpen:
Creates a 3x3 matrix of color weights and multiplies them with pixels in a 3x3 space. The resulting values get added and then divided by 9 to create the image.

<img src="https://github.com/aleenend/SimpleNukeNodes/assets/59891824/f9bd496c-03c3-4a64-ab3d-ba393e33db62" width="350" height="200"> &emsp; <img src="https://github.com/aleenend/SimpleNukeNodes/assets/59891824/c855e8d4-f2dd-434c-bc95-eeea4b676eec" width="350" height="200"> 

