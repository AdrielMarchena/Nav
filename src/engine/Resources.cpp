#include "Resources.h"
//#include <future>

namespace engine {
    /*
        Singleton "Require" this here
        because i can't modify memeber non static members in static funtions
    */
    gl::Shader* Resources::GetShader(const char* name)
    {
        return Resources::getInstance().IGetShader(name);
    }
    gl::Texture* Resources::GetTexture(const char* name)
    {
        return Resources::getInstance().IGetTexture(name);;
    }
    void Resources::LoadShader(const char* name, const char* path, int count)
    {
        Resources::getInstance().ILoadShader(name, path,count);
    }
    void Resources::LoadTexture(const char* name, const char* path, int count)
    {
        Resources::getInstance().ILoadTexture(name, path, count);
    }
    void Resources::Clear()
    {
        Resources::getInstance().IClear();
    }

    gl::Shader* Resources::IGetShader(const char* name)
    {
        for (auto i = shaders_list.begin(); i != shaders_list.end(); ++i)
        {
            if (i->first == name)
            {
                auto tmp = i->second;
                shaders_list.erase(i);
                return tmp;
            }
        }
        std::string a = name;
        std::string mes = "Can't find Shader < " + a + " >";
        throw std::exception(mes.c_str());
    }

    gl::Texture* Resources::IGetTexture(const char* name)
    {
        for (auto i = texture_list.begin(); i != texture_list.end(); ++i)
        {
            if (i->first == name)
            {
                /* No need to erase a texture, this can be used multiple times */
                //auto tmp = i->second;
                //texture_list.erase(i);
                //return tmp
                return i->second;
            }
        }
        std::string a = name;
        std::string mes = "Can't find Texture < " + a + " >";
        throw std::exception(mes.c_str());
    }

    void Resources::IClear()
    {
        for (auto sh : shaders_list)
            delete sh.second;
        for (auto tx : texture_list)
            delete tx.second;
        shaders_list.clear();
        texture_list.clear();
    }

    /* Just a dream here :( */
    //static std::mutex ResourcesMutex;

    void Resources::ILoadShader(const char* name, const char* path, int count)
    {
        if (count < 1)
            return;
        for (int i = 0; i < count; i++)
        {
            gl::Shader* sh = new gl::Shader(path);
            //std::lock_guard<std::mutex> lock(ResourcesMutex);
            shaders_list.push_back(std::make_pair(name, sh));
        }
    }

    void Resources::ILoadTexture(const char* name, const char* path, int count)
    {
        if (count < 1)
            return;
        for (int i = 0; i < count; i++)
        {
            gl::Texture* tx = new gl::Texture(path);
            //std::lock_guard<std::mutex> lock(ResourcesMutex);
            texture_list.push_back(std::make_pair(name, tx));
        } 
    }
}