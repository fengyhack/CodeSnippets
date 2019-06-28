#ifndef HASH_DICT_H
#define HASH_DICT_H
 
struct Key
{
 
    unsigned short code;
    char ch;
 
};
 
class Hash_Node
{
 
    friend class Hash_dict;
    friend class Dictionary;
    Key key;
    unsigned short code;
    Hash_Node *next;
public:
    Hash_Node(Key k, unsigned short cd)
    {
 key.code = k.code, key.ch = k.ch, code = cd, next = 0;
}
 
};
 
class Hash_dict
{
 
    Hash_Node *list[4099];
public:
    Hash_dict();
    void AddNode(Key k, unsigned short cd);
    Hash_Node* Find(Key k);
 
};
 
class Dictionary
{
 
    Key key[4096];
    unsigned short code[4096];
    unsigned short cur_len;
    Hash_dict hash;
public:
    Dictionary();
    bool realkey(char* buffer, unsigned short c);
    void LZW_pack(char* fileo, char* filep);
    void LZW_unpack(char* fileo, char* filep);
    unsigned short current_length() {
 return cur_len;
}
 
};