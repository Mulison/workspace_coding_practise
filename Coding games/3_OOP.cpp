#include <string>
#include <iostream>

using namespace std;

class Sensor 
{
  public:
    virtual double getValue() const = 0;
    virtual string getName() const = 0;
};
  
class TemperatureSensor : public Sensor 
{
  // 模拟温度采集，返回一个浮点值
  public:
    double getValue() const override
    {
      return 23.05;
    }
    string getName() const override
    {
      return "TemperaturSensor";
    }

};

class PressureSensor : public Sensor 
{
  public:
  double getValue() const override
  {
    return 1012.3;
  }
  string getName() const override
  {
    return "PressureSensor";
  }
};

class SensorLogger
{
  public:
    void log(Sensor& sensor) const
    {
      cout << sensor.getName() << " = "<< sensor.getValue() << endl;
    }
};


int main() {
  TemperatureSensor tempSensor;
  PressureSensor pressureSensor;
  SensorLogger logger;

  logger.log(tempSensor);
  logger.log(pressureSensor);

  return 0;
}