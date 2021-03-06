#ifndef RESTCLIENT_JSONDICT_H
#define RESTCLIENT_JSONDICT_H

#include <string>
#include <sstream>
#include <vector>

class JsonDict
{
 public:
  // Simple key-value-pair
  // {"key": "value"} / {"key": true} / {"key": 10} / {"key": 2.5}
  JsonDict(const std::string& key, const char * value); // Use char * to avoid string& to bool cast
  JsonDict(const std::string& key, bool value);
  JsonDict(const std::string& key, int value);
  JsonDict(const std::string& key, double value);
  template <typename T> JsonDict(const std::string& key, std::vector<T> values)
      : mKey(toJson(key)), mValue()
  {
    std::stringstream list;
    typename std::vector<T>::iterator it;

    list << "[";
    for (it = values.begin(); it != values.end(); it++) {
      list << toJson(*it);
      if (it < values.end() - 1) {
        list << ", ";
      }
    }
    list << "]";

    mValue = list.str();
  }
  // A single key with an arbitrary dictionary for the value
  // {"key": {"subKey": "value"}}
  JsonDict(const std::string& key, JsonDict& value);
  // Multiple key-value pairs
  // {"key1": "value1", "key2": "value2", "key3": "value3"}
  explicit JsonDict(std::vector<JsonDict>& values);

  std::string str();

 private:
  std::string mKey;
  std::string mValue;

  std::string toJson(const std::string& value);
  std::string toJson(bool value);
  std::string toJson(int value);
  std::string toJson(double value);
};

#endif //RESTCLIENT_JSONDICT_H
