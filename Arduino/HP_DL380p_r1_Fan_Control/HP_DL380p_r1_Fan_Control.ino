int gCur;
uint8_t gADCInputs[3] = {A4, A5, A6};
uint8_t gPWMOutputs[3] = {12, 3, 2};
int gVRef = 650; // 5V = 650, 3.3V = 985?
int gVal;

int gReductionPercentage = 10, // How much reduction in percentage will be applied
    gCutoffPoint = 80, // Input values above this won't be adjusted.
    gMinPercentage = 10; // Lowest adjusted value.

void setup()
{
  //Serial.begin(9600);
  for (gCur = 0 ; gCur < 3 ; gCur++)
  {
    pinMode(gADCInputs[gCur], INPUT);
    pinMode(gPWMOutputs[gCur], OUTPUT);
  }
}

void loop()
{
  for(gCur = 0 ; gCur < 3 ; gCur++)
  {
    gVal = map(analogRead(gADCInputs[gCur]), gVRef, 0, 0, 100);

    if (gVal > gCutoffPoint)
      analogWrite(gPWMOutputs[gCur], map(constrain(gVal, gMinPercentage, 100), 0, 100, 255, 0));
    else
      analogWrite(gPWMOutputs[gCur], map(constrain(gVal - gReductionPercentage, gMinPercentage, 100), 0, 100, 255, 0));
  }
  
  delay(1000);
}
