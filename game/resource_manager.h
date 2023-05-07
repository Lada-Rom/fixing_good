#ifndef FG_RESOURCE_MANAGER_HPP
#define FG_RESOURCE_MANAGER_HPP

#include <map>
#include <string_view>
#include <exception>
#include <memory>
#include <fstream>

#include <SDL2pp/SDL2pp.hh>

namespace pp = SDL2pp;


template <class Derived, class Type>
class ResourceManager {
    using RefType = std::shared_ptr<Type>;
    using String = std::string_view;

public:
    ResourceManager() {}

    template<typename... Args>
    bool AddResource(const String& resourceName, Args... argv) {
        auto res = Find(resourceName); //see if resource is already allocated
        if(res) return true;

        auto resource = Load(resourceName, argv...);
        //if pass all tests we place resourArgs... argvce on our container keeping track of allocatoin of memory.
        resourceMap.emplace(resourceName, resource);
        return true;
    }

    RefType GetResource(const String& resourceName) {
        auto res = Find(resourceName); //use auto since we don't know what data-type the Find() method will return!
        if(res) return res;
        else throw std::runtime_error("don't have source with such name");
    }

    bool ReleaseResource(const String& resourceName) {
        auto res = Find(resourceName);
        if(!res) return false;

        Unload(resourceName);   //de-allocate memory
        return true;
    }

    template<typename... Args>
    RefType Load(const String& path, Args... argv) {
        return reinterpret_cast<Derived*>(this)->Load(path, argv...);
    }

    ~ResourceManager() {}

private:
    std::unordered_map<String, RefType> resourceMap; //string with pair of a Resource type + counter
    std::unordered_map<String, String> fileMap;   //stores all resources at intialization of instance

    RefType Find(const String& resourceName) {
        auto itr = resourceMap.find(resourceName);
        if(itr != resourceMap.end()) return itr->second;
        else return nullptr;
    }

    void Unload(const String& resourceName) {
        resourceMap.erase(resourceName);
    }

};

class SdlTextureManager {
    using String = std::string_view;

public:
    SdlTextureManager() {}

    std::shared_ptr<pp::Texture> Load(const String& fileName, std::shared_ptr<pp::Renderer> renderer) {
        auto ret = std::make_shared<pp::Texture>(*renderer, fileName.data());
        return ret;
    }

private:
};

#endif // !FG_RESOURCE_MANAGER_HPP
