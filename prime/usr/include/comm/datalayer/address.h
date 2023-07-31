#pragma once

#include <string.h>
#include <vector>

namespace comm
{
  namespace datalayer
  {
    class Address
    {
    private:
      std::string m_token = "/";
      std::string m_path;
      std::vector<std::string> m_elements;

      //
      // enumeration of strings
      //
      void append(void) { generate(m_elements); }
      template<typename T, typename... Args>
      void append(T&& obj, Args&&... args)
      {
        // create temporary vector
        m_elements.push_back(obj);
        append(args...);
      }

      //
      //
      //
      void generate(const std::vector<std::string> elements)
      {
        // because temporary used by append()
        m_elements.clear();
        m_path.clear();

        for (auto it : elements)
        {
          // remove tokens within address element
          std::size_t pos = 0;
          while (std::string::npos != pos)
          {
            pos = it.find(m_token, 0);
            switch (pos)
            {
            case 0:
              // remove all leading tokens if present
              it = it.substr(pos + m_token.length());
              break;
            case std::string::npos:
              // no tokens to be considered
              break;
            default:
              // cut off final tokens (and following stuff) if present
              it = it.substr(0, pos);
              pos = std::string::npos;
              break;
            }
          }

          // append adapted string to complete string path
          m_path.append(it).append(m_token);

          // store adapted string to vector of strings
          m_elements.push_back(it);
        }
      }

      //
      //
      //
      void parse(const std::string& in)
      {
        std::string address(0 == in.find(m_token, 0) ? in.substr(m_token.length()) : in);

        m_elements.clear();
        m_path.clear();

        std::string element;
        std::size_t pos = 0;

        while (std::string::npos != pos)
        {
          element.clear();
          pos = address.find(m_token, 0);
          switch (pos)
          {
          case 0:
            // remove all (leading) tokens if present
            address = address.substr(pos + m_token.length());
            break;
          case std::string::npos:
            if (!address.empty())
            {
              // final address element
              element = address;
            }
            break;
          default:
            // address element
            element = address.substr(0, pos);
            address = address.substr(pos + m_token.length());
            break;
          }

          // store adapted address element to vector
          if (!element.empty())
          {
            m_elements.push_back(element);
          }
        }

        // concatenate address elements to complete address path
        for (auto& it : m_elements)
        {
          m_path.append(it).append(m_token);
        }
      }

    public:
      //
      // parse constructors (address path --> address elements)
      //
      Address(const std::string& path) { parse(path); }
      Address(const char token, const std::string& path) : m_token(std::string(1, token)) { parse(path); }

      //
      // generate constructors (address elements --> address path)
      //
      Address(const std::vector<std::string>& elements) { generate(elements); }
      template<class... Args> Address(const std::string& element, Args&&... args) { append(element, std::forward<Args>(args)...); }
      Address(char token, const std::vector<std::string>& elements) : m_token(std::string(1, token)) { generate(elements); }
      template<class... Args> Address(char token, const std::string& element, Args&&... args) : m_token(std::string(1, token)) { append(element, std::forward<Args>(args)...); }

      // default constructors
      Address() = delete;
      ~Address() = default;

      //
      // additional token getter / setter
      //
      const std::string token(void) { return m_token; }
      void token(const std::string& in) { m_token = in; std::vector<std::string> elements(m_elements); generate(elements); }
      void token(const char& in) { token(std::string(1, in)); }

      //
      // operators
      //
      Address& operator=(const std::string& path)
      {
        parse(path);
        return *this;
      }

      Address& operator=(const std::vector<std::string>& elements)
      {
        generate(elements);
        return *this;
      }

      bool operator==(const Address& var2) const
      {
        return (0 == m_path.compare(var2.generate()));
      }

      bool operator!=(const Address& var2) const
      {
        return (0 != m_path.compare(var2.generate()));
      }

      operator std::string() const
      {
        return m_path;
      }

      operator std::vector<std::string>() const
      {
        return m_elements;
      }

      //
      // getter address path
      //
      const std::string& generate() const { return m_path; }

      //
      // getter address elements
      //
      const std::vector<std::string>& parse() const { return m_elements; }
    };
  }
}
