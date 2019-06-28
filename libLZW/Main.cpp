#include "Hash_dict.h"
#include <iostream.h>
#include <string.h>
 
void main()
{
 
    Dictionary d1;
    char text_name[20], cryp_name[20];
    char sw;
    cout << "= = = = = = = LZW packing = = = = = = =" << endl;
    cout << "_____Made by HC_Kirryccc" << endl << endl;
    cout << "1 -- text to code(default: \"text.txt\" to \"code.dat\")" << endl;
    cout << "2 -- code to text(default: \"code.dat\" to \"text2.txt\")" << endl;
    cout << "Input your choose: ";
    cin >> sw;
    if (sw == '1')
    {
 
        strcpy(text_name, "text.txt");
        strcpy(cryp_name, "code.dat");
        d1.LZW_pack(text_name, cryp_name);
        cout << endl << "dictionary length: " << d1.current_length() << endl;
        cout << endl << "The code has been saved to \'code.dat\'" << endl;
        cout << "   ____You may delete \'text.txt\'" << endl << endl;
     
}
    else if(sw == '2')
    {
 
        strcpy(text_name, "text2.txt");
        strcpy(cryp_name, "code.dat");
        d1.LZW_unpack(text_name, cryp_name);
        cout << endl << "dictionary length: " << d1.current_length() << endl;
        cout << endl << "Congratulations!" << endl;
        cout << "The code has been decoded to \'text2.txt\'" << endl;
 
     
}
      