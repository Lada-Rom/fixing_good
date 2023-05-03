#ifndef FG_RESOURCE_MANAGER_HPP
#define FG_RESOURCE_MANAGER_HPP

#include <map>
#include <string_view>
#include <exception>
#include <memory>

#include <SDL2pp/SDL2pp.hh>

namespace pp = SDL2pp;

template<class Resource>
class ResourceManager {
public:
  explicit ResourceManager(std::shared_ptr<pp::Renderer> p_renderer)
    : m_renderer(p_renderer) {}
  ~ResourceManager() = default;

  void Create(
    const std::string_view& id,
    const std::string_view& filename);

  Resource& Get(const std::string_view& id);

private:
  std::map<std::string_view, std::shared_ptr<Resource> > m_resources_map{};
  std::shared_ptr<pp::Renderer> m_renderer{};

private:
  struct bad_args : public std::exception {
    const char* what() const throw() {
      return " ==> Error: No instance with such id.\n";
    }
  };
};

template<class Resource>
void ResourceManager<Resource>::Create(
  const std::string_view& id,
  const std::string_view& filename) {
  m_resources_map[id] = std::make_shared<Resource>(*m_renderer, filename.data());
}

template<class Resource>
Resource& ResourceManager<Resource>::Get(const std::string_view& id) {
  auto ans = m_resources_map.find(id);
  if (ans != m_resources_map.end())
    return *(ans->second);
  throw bad_args();
}


#endif  // !FG_RESOURCE_MANAGER_HPP
