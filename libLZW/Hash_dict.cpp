#include "Hash_dict.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>
 
unsigned index(Key k)
{
 
    unsigned temp = 0;
    temp += k.code;
    temp <<= 8;
    temp += k.ch;
    return temp;
 
}
 
Hash_dict::Hash_dict()
{
 
    for (int i=0; i<4099; i++)
        list[i] = 0;
 
}
 
void Hash_dict::AddNode(Key k, unsigned short cd)
{
 
    Hash_Node *newptr = new Hash_Node(k, cd), *ptr;
    unsigned temp = index(k);
    ptr = list[temp%4099];
    if (!ptr)
    {
 
        list[temp%4099] = newptr;
        return;
     
}
    while (ptr->next)
        ptr = ptr->next;
    ptr->next = newptr;
 
}
 
Hash_Node* Hash_dict::Find(Key k)
{
 
    Hash_Node *ptr;
    unsigned temp = index(k);
    ptr = list[temp%4099];
    while (ptr)
    {
 
        if (k.ch == ptr->key.ch && k.code == ptr->key.code)
            return ptr;
        ptr = ptr->next;
     
}
    return 0;
 
}
 
unsigned combine(unsigned short s1, unsigned short s2)
{
 
    unsigned re=0;
    re += s1;
    re <<= 12;
    re += s2;
    return re;
 
}
 
Dictionary::Dictionary()
{
 
    for (unsigned short i=0; i<256; i++)
    {
 
        key[i].code = 0xffff;
        key[i].ch = i;
        code[i] = i;
        hash.AddNode(key[i], code[i]);
     
}
    cur_len = 256;
    for (; i<4096; i++)
        code[i] = i;
 
}
 
bool Dictionary::realkey(char* buffer, unsigned short c)
{
 
    if (c>=cur_len)
        return 0;
    char temp[100];
    int i=0, total;
    while (c != 0xffff)
    {
 
        temp[i++] = key[c].ch;
        c = key[c].code;
     
}
    for (total=i; i>0; i--)
        buffer[total-i] = temp[i-1];
    buffer[total] = 0;
    return 1;
 
}
 
void Dictionary::LZW_pack(char* fileo, char* filep)
{
 
    FILE *origin, *packed;
    origin = fopen(fileo, "rb");
    packed = fopen(filep, "wb");
    char ch;
    int i;
    unsigned element;
    unsigned short c[2], cur_code;
    Key k;
    Hash_Node *ptr;
 
    if (feof(origin) == 0)
    {
 
        cur_code = 0xffff;
        fread(&ch, 1, 1, origin);
        k.ch = ch, k.code = cur_code;
     
}
    while (feof(origin) == 0)
    {
 
        for (i=0; i<2; i++)
        {
 
            k.code = 0xffff;
            cur_code = 0;
            while ((ptr = hash.Find(k)) && feof(origin) == 0)
            {
 
                cur_code = ptr->code;
                fread(&ch, 1, 1, origin);
                k.ch = ch, k.code = cur_code;
             
}
            if (feof(origin) == 0)
            {
 
                key[cur_len].ch = k.ch;
                key[cur_len].code = k.code;
                hash.AddNode(k, cur_len++);
                if (cur_len >= 4096)
                {
 
                    cout << "Wrong! The Key is more than 4096..." << endl;
                    cout << "The dictionary has broken!" << endl;
                    exit(0);
                 
}
             
}
            c[i] = cur_code;
         
}
        element = combine(c[0], c[1]);
        fwrite(&element, 3, 1, packed);
     
}
    fclose(origin);
    fclose(packed);
 
}
 
void Dictionary::LZW_unpack(char* fileo, char* filep)
{
 
    FILE *origin, *packed;
    origin = fopen(fileo, "wb");
    packed = fopen(filep, "rb");
    unsigned element = 0;
    unsigned short c[2], past_code = 0xffff;
    char buffer_p[100], buffer_c[100];
    int i;
    Key k;
 
    fread(&element, 3, 1, packed);
    while (feof(packed) == 0)
    {
 
        c[0] = element >> 12;
        c[1] = element & 0xfff;
        for (i=0; i<2; i++)
        {
 
            if (!realkey(buffer_c, c[i]))
            {
 
                strcpy(buffer_c, buffer_p);
                buffer_c[strlen(buffer_c)+1] = 0;
                buffer_c[strlen(buffer_c)] = *buffer_c;
             
}
            k.ch = *buffer_c, k.code = past_code;
            if (past_code != 0xffff)
            {
     
                key[cur_len].ch = k.ch;
                key[cur_len].code = k.code;
                hash.AddNode(k, cur_len++);
             
}
            if (cur_len >= 4096)
            {
 
                cout << "Wrong! The Key is more than 4096..." << endl;
                cout << "The dictionary has broken!" << endl;
                exit(0);
             
}
            fwrite(buffer_c, 1, strlen(buffer_c), origin);
            past_code = c[i];
            strcpy(buffer_p, buffer_c);
         
}
        fread(&element, 3, 1, packed);
     
}
    fclose(origin);
    fclose(packed);
 
}