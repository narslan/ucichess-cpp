#pragma once

#include <map>
#include <memory>
#include <string>

namespace uci {

  class Option {
    public:
    virtual ~Option(){};
    virtual void set(std::string key) = 0;
  };

  class Spin : public Option {
    public:
    void set(std::string key);
    Spin(int d, int min, int max)
        : m_default{d}
        , m_min{min}
        , m_max{max} {};
    ~Spin() = default;

    int m_default;
    int m_min;
    int m_max;
  };

  class String : public Option {
    public:
    void set(std::string key);
    ~String() = default;
  };

  class Button : public Option {
    public:
    void set(std::string key);
    ~Button() = default;
  };

  class Check : public Option {
    public:
    std::string m_default;
    std::string m_value;
    void set(std::string key);
    Check(std::string d)
        : m_default{d}
        , m_value{d} {};
    ~Check() = default;
  };

  class Combo : public Option {
    public:
    std::string m_default;
    std::string m_values;
    void set(std::string key);
    Combo(std::string d, std::string v)
        : m_default{d}
        , m_values{v} {};
    ~Combo() = default;
  };

  struct Info {
    Info()
        : m_id{}
        , m_name{} {};
    std::string m_id;
    std::string m_name;
    std::map<std::string, std::unique_ptr<Option>> opts;
  };

} // namespace uci