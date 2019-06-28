# Utilities

##Image2Jpeg

###Usage (example)

@Image2Jpeg F:\Dataset\ZY3_2K\Result\a\    bmp      R    64   B   128

<i>(Command)        (SourcePath)          (extension)  (key_R)   (key_B)</i>

###What just happend:

<li>Search file(image)s in [SourcePath]

<li>For each file(image), load it as 'src' and create a new RGB image as 'dst',

<li>Travserse 'src' pixel by pixel, read its gray-value (src[i])

<li>As for src[i], if 
- src[i]<key_R then set dst[i]=black,
- src[i]=key_R then set dst[i]=red,
- src[i]=key_B then set dst[i]=blue,
- src[i]>key_B then set dst[i]=white

<li>Save 'dst' as a jpeg file

<li>Delete 'src' file.

<br><br>

Go to [top(root)](https://github.com/fengyhack/Utilities)
