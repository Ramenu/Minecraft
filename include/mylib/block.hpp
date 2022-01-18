#ifndef BLOCK_HPP
#define BLOCK_HPP

class Block
{
    public:
        Block(const char* pathToDirectory);
        ~Block();
        void drawBlock();
    private:
        static unsigned int blockID;
        unsigned int blockTextures[3];
        unsigned short noOfTextures;
        unsigned short upTo;
};

#endif