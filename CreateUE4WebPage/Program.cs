using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace CreateUE4WebPage
{
    class Program
    {
        static void GenVideoIndexPages()
        {
            //Console.Write("Input path:");
            // string srcPath = Console.ReadLine();
            string srcPath = "E:/Download/Wiki_UE4/video_pack";
            if (!Directory.Exists(srcPath))
            {
                Console.WriteLine(srcPath + " # Does NOT exists!");
                return;
            }
            string[] fns = Directory.GetFiles(srcPath);
            int count = fns.Length;
            Console.WriteLine("Found " + count.ToString() + " items.");
            string html_pre = "<html>\r\n\t<head>\r\n\t</head>\r\n\t<body>";
            string video_pre = "\r\n\t\t<video width=\"1920\" height=\"1080\" controls=\"controls\">\r\n\t\t\t<source src=\"";
            string video_suf = "\" type=\"video/mp4\" />";
            string html_suf = "\r\n\t\t</video>\r\n\t</body>\r\n</html>";
            string dstPath = "E:/Download/Wiki_UE4/video_index/";
            if (!Directory.Exists(dstPath))
            {
                Directory.CreateDirectory(dstPath);
                Console.WriteLine(dstPath + " # path created");
            }
            char[] puc = new char[] { '\\', '/' };
            for (int i = 0; i < count; ++i)
            {
                string short_name = fns[i].Substring(fns[i].LastIndexOfAny(puc) + 1);
                if (!short_name.Contains(".mp4")) continue;
                string html_name = dstPath + short_name.Substring(0,short_name.LastIndexOf('.')) + ".html";
                StreamWriter sw = new StreamWriter(html_name);
                sw.Write(html_pre);
                sw.Write(video_pre);
                sw.Write("../wiki_video/" + short_name);
                sw.Write(video_suf);
                sw.Write(html_suf);
                sw.Flush();
                sw.Close();
            }

            Console.WriteLine("Finished!");
        }

        static void GenWikiPage()
        {
            string path = "E:/Download/Wiki_UE4/";
            StreamReader sr = new StreamReader(path+"UE4md.html");
            StreamWriter sw = new StreamWriter(path + "UE4VT.html");
            int start, end;
            while(!sr.EndOfStream)
            { 
                string srcLine = sr.ReadLine();
                if (srcLine.Contains("<li>"))
                {
                    srcLine = srcLine.Replace(':','-');
                    start = srcLine.IndexOf("<li>");
                    end = srcLine.LastIndexOf("</li>");
                    string name = srcLine.Substring(start + 4, end - start-4);
                    string dstLine = "<li><a href=\"video_index/" + name + ".html\" target=\"_blank\">" + name + "</a></li>";
                    sw.WriteLine(dstLine);
                }
                else
                {
                    sw.WriteLine(srcLine);
                }
            }
            sr.Close();
            sw.Flush();
            sw.Close();

            Console.WriteLine("Finished!");
        }

        static void Main(string[] args)
        {
            GenVideoIndexPages();
            GenWikiPage();

            Console.Write("Press any key...");
            Console.ReadKey();
        }
    }
}
