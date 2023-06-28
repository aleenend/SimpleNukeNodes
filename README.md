# SimpleNukeNodes
A few simple nodes written for Nuke in a Visual Effects and Compositing course at Clemson University. All code is based on sample code provided by the instructor.

AleeneContrast:
Changes the contrast of an image using bias and gain. Adds knobs to control bias and gain within Nuke.

<img src="https://github.com/aleenend/SimpleNukeNodes/assets/59891824/53ac072d-0878-480a-bcdd-69b85dc62f26" alt="original" width="350" height="200"> &emsp; <img src="https://github.com/aleenend/SimpleNukeNodes/assets/59891824/75ece9ba-b4d8-45c0-a85c-d02317f3f44c" width="350" height="200">


AleeneGamma:
Changes gamma of an image and will not go lower than 0.01. Adds knob to control gamma within Nuke.

<img src="https://github.com/aleenend/SimpleNukeNodes/assets/59891824/1f20bab1-52f5-4c69-ac3c-24a77127e366" width="350" height="200"> &emsp; <img src="https://github.com/aleenend/SimpleNukeNodes/assets/59891824/412270c6-f02c-4e22-9574-65afc2098d5b" width="350" height="200"> 


AleeneMedian:
Finds and applies median value to image by sorting pixels. Adds knob to control size within Nuke. Default size is 20.

<img src="https://github.com/aleenend/SimpleNukeNodes/assets/59891824/1f20bab1-52f5-4c69-ac3c-24a77127e366" width="350" height="200"> &emsp; <img src="https://github.com/aleenend/SimpleNukeNodes/assets/59891824/eeb1e3f3-080c-4fdc-bb0a-22cb4fe6a029" width="350" height="200"> 


AleeneOver:
Superimposes one image over another using the equation image A + (1 - M) * image B. Divides image A by its alpha channel to get value for M. Adds knob to control "mix" of the two images similar to the merge node.

<img src="https://github.com/aleenend/SimpleNukeNodes/assets/59891824/1f20bab1-52f5-4c69-ac3c-24a77127e366" width="350" height="200"> &emsp; <img src="https://github.com/aleenend/SimpleNukeNodes/assets/59891824/45573124-aad0-4b32-bc96-561d56194cd2" width="350" height="200"> &emsp; <img src="https://github.com/aleenend/SimpleNukeNodes/assets/59891824/17ddb82c-57f1-408c-93bd-40d78f13313c" width="350" height="200"> 


AleeneSharpen:
Creates a 3x3 matrix of color weights and multiplies them with pixels in a 3x3 space. The resulting values get added and then divided by 9 to create the image.

<img src="https://github.com/aleenend/SimpleNukeNodes/assets/59891824/1f20bab1-52f5-4c69-ac3c-24a77127e366" width="350" height="200"> &emsp; <img src="https://github.com/aleenend/SimpleNukeNodes/assets/59891824/6c057e72-367b-439e-8bc9-f2069d7b7668" width="350" height="200"> 

