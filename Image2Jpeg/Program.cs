using System;
using System.Drawing;
using System.Drawing.Imaging;
using System.IO;

namespace Image2Jpeg
{
    class Program
    {
        
        #region CommandParser

        static void ParseAndExecCommand(string[] args)
        {
            string path = args[0];
            string extension = args[1].ToLower();
            if (extension == "jpg")
            {
                Console.WriteLine("Extension must be other one except \'jpg\'");
                return;
            }

            string pattern = "*." + extension;
            string[] fileNames = Directory.GetFiles(path, pattern);

            if (args.Length == 2)
            {
                ConvertAsGray(fileNames, extension);
            }
            else
            {
                int r = 64, b = 128;
                if (args.Length == 6)
                {
                    if (args[2].ToLower() == "r")
                    {
                        r = int.Parse(args[3]);
                        b = int.Parse(args[5]);
                    }
                    else
                    {
                        b = int.Parse(args[3]);
                        r = int.Parse(args[5]);
                    }
                }

                ConvertAsRGB(fileNames, extension, r, b);
            }
        }

        #endregion CommandParser

        #region Converter: Gray

        static void ConvertAsGray(string[] fileNames, string extension)
        {
            foreach (string s in fileNames)
            {
                Console.WriteLine(s);
                using (Bitmap bmp = new Bitmap(s))
                {
                    if (bmp != null)
                    {
                        bmp.Save(s.Replace(extension, "jpg"), ImageFormat.Jpeg);
                    }
                }
                File.Delete(s);
            }
        }

        #endregion Converter: Gray

        #region Converter: RGB

        // val<key_R: d=K (black)
        // val=key_R: d=R (red)
        // val=key_B: d=B (blue)
        // val>key_B: d=W (white)
        static void ConvertAsRGB(string[] fileNames, string extension, int key_R, int key_B)
        {
            foreach (string s in fileNames)
            {
                Console.WriteLine(s);
                using (Bitmap src = new Bitmap(s))
                {
                    int w = src.Width;
                    int h = src.Height;
                    using (Bitmap dst = new Bitmap(w, h, PixelFormat.Format24bppRgb))
                    {
                        BitmapData srcData = src.LockBits(new Rectangle(0, 0, w, h), ImageLockMode.ReadOnly, PixelFormat.Format8bppIndexed);
                        BitmapData dstData = dst.LockBits(new Rectangle(0, 0, w, h), ImageLockMode.WriteOnly, PixelFormat.Format24bppRgb);

                        #region Converter
                        unsafe
                        {
                            byte* pSrc = (byte*)srcData.Scan0.ToPointer();
                            byte* pDst = (byte*)dstData.Scan0.ToPointer();
                            byte val, b0 = (byte)0, bx = (byte)255;
                            for (int i = 0; i < h; ++i)
                            {
                                for (int j = 0; j < w; ++j)
                                {
                                    val = pSrc[0];

                                    if (val < key_R) // Black
                                    {
                                        pDst[0] = b0;
                                        pDst[1] = b0;
                                        pDst[2] = b0;
                                    }

                                    if (val == key_R)  // Red
                                    {
                                        pDst[0] = b0;
                                        pDst[1] = b0;
                                        pDst[2] = bx;
                                    }

                                    if (val == key_B) // Blue
                                    {
                                        pDst[0] = bx;
                                        pDst[1] = b0;
                                        pDst[2] = b0;
                                    }

                                    if (val > key_B)  // White
                                    {
                                        pDst[0] = bx;
                                        pDst[1] = bx;
                                        pDst[2] = bx;
                                    }

                                    pSrc += 1;
                                    pDst += 3;
                                }
                                pSrc += srcData.Stride - w;
                                pDst += dstData.Stride - w * 3;
                            }
                        }
                        #endregion Converter

                        src.UnlockBits(srcData);
                        dst.UnlockBits(dstData);

                        dst.Save(s.Replace(extension, "jpg"), ImageFormat.Jpeg);
                    }
                }
                File.Delete(s);
            }
        }

        #endregion Converter: RGB

        static void Main(string[] args)
        {
            if (args.Length < 2)
            {
                Console.WriteLine("Usage: <Command> <SourcePath> <Extension>");
                Console.WriteLine("Example: Image2Jpeg  F:\\Images\\  bmp");
                return;
            }

            ParseAndExecCommand(args);
        } 

    }
}
