#include <string>
#include <vector>
#include <map>
#include <iostream>
#include <sstream>

using namespace std;

class Parser
{
  public:
    void setString(const string& s)
    {
      m_string = s;
      parsing();
    }

    void printVector() const
    {
      for (auto& it : m_vector)
      {
        cout << it << endl;
      }

    }

    void printMap() const
    {
      for (auto& it : m_map)
      {
        cout << it.first << " = " << it.second << endl;
      }

    }

  private:
    void splitSection(const string& s)
    {
      istringstream iss(s);
      string first;
      string strSecond;

      getline(iss, first, '=');
      getline(iss, strSecond);
      int second = stoi(strSecond);
      m_map[first] = second;
    }

    void parsing()
    {
      // split into sections
      istringstream iss(m_string);
      string token;

      while (getline(iss, token, ' '))
      {
        m_vector.push_back(token);
        splitSection(token);
      }    

    }

    string m_string;
    map<string, int> m_map;
    vector<string> m_vector;
};

int main()
{
  Parser parser;
  parser.setString("temp=25 pressure=1012 rpm=2000");
  parser.printVector();
  parser.printMap();

}