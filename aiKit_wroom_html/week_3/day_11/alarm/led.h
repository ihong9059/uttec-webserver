#ifndef LED_H
#define LED_H

class LED {
  private:
    int redPin;
    int yellowPin;
    int bluePin;
    
  public:
    LED(int red, int yellow, int blue);
    void begin();
    void setRed(bool state);
    void setYellow(bool state);
    void setBlue(bool state);
    void dimRed(int value);
    void dimYellow(int value);
    void dimBlue(int value);
};

#endif