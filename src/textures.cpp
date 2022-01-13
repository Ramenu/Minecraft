#define STB_IMAGE_IMPLEMENTATION
#include "mylib/textures.h"

//loadTexture method with the name of the file as a parameter, and a boolean to see if the image is a JPG
void Textures::loadTexture(const char* fileName, bool isJPG)
{
    int width, height, colourChannels; //Declare variables
    unsigned char* data = stbi_load(fileName, &width, &height, &colourChannels, 0); //Retrieve image data with stbi_load

    //If the image is a JPG
    if (isJPG)
    {
        //If the was successfully retrieved
        if (data)
        {
            //Once glTexImage2D is called, the currently bounded texture will have the data attached onto it
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data); //Generate texture using glTexImage2D
            glGenerateMipmap(GL_TEXTURE_2D); //Generate the mipmaps for currently bound texture
        }

        //Print a console error with the associated file name
        else {
            printf("\nERROR: Failed to load JPG texture at: %s\n", fileName);
        }
    }
    else {
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else {
            printf("\nFailed to load PNG texture at: %s\n", fileName);
        }
    }
    stbi_image_free(data);
}


//Method that sets the default texture configurations
void Textures::set_Default_2D_Texture_Configs()
{
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}