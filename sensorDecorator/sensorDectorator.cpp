#include<iostream>
using namespace std;



class Detector{
    public:
    virtual ~Detector() {}
    virtual void detect() const = 0;
};

class Sensor {
    public:
    virtual ~Sensor() {}
    virtual void analyse() const = 0;
    virtual void getInformatoin() = 0;
};


// Concrete sensor implementation
class FrequencySensor : public Sensor {
public:
    //FrequencySensor():frequency_(7.000){}
    void analyse() const  override { std::cout<<"\n Frequency Sersor analyzing the object"; } 
    void getInformatoin() override { std::cout<<"\n Frequency Sensor find information about the is" << frequency_; }

private:
    double frequency_;
};

class MosistureDetector : public Detector{
    public:
        void detect() const override {};
};

int main(int argc, char *argv[]) {
    return 0;
}

