#include <Arduino.h>
#include <Fuzzy.h>

// LED
#define LED 13

// Fuzzy
Fuzzy *fuzzyLED = new Fuzzy();
int ledBrightness;

// Fuzzy Sets for RTC
FuzzySet *morning = new FuzzySet(5, 7, 10, 11);
FuzzySet *afternoon = new FuzzySet(10, 12, 18, 19);
FuzzySet *night = new FuzzySet(18, 19, 24, 24);

// Fuzzy Sets for Volume
FuzzySet *narrow = new FuzzySet(0, 0, 22, 27.5);
FuzzySet *standard = new FuzzySet(25, 33, 60, 64);
FuzzySet *wide = new FuzzySet(56, 65, 80, 80);

// Fuzzy Sets for LED Brightness
FuzzySet *dim = new FuzzySet(0, 0, 20, 30);
FuzzySet *moderate = new FuzzySet(25, 35, 65, 75);
FuzzySet *bright = new FuzzySet(70, 80, 100, 100);

void setup()
{
  Serial.begin(9600);

  // Fuzzy Input for RTC
  FuzzyInput *rtcInput = new FuzzyInput(3);
  rtcInput->addFuzzySet(morning);
  rtcInput->addFuzzySet(afternoon);
  rtcInput->addFuzzySet(night);
  fuzzyLED->addFuzzyInput(rtcInput);

  // Fuzzy Input for Volume
  FuzzyInput *volumeInput = new FuzzyInput(4);
  volumeInput->addFuzzySet(narrow);
  volumeInput->addFuzzySet(standard);
  volumeInput->addFuzzySet(wide);
  fuzzyLED->addFuzzyInput(volumeInput);

  // Fuzzy Output for LED Brightness
  FuzzyOutput *brightnessOutput = new FuzzyOutput(2);
  brightnessOutput->addFuzzySet(dim);
  brightnessOutput->addFuzzySet(moderate);
  brightnessOutput->addFuzzySet(bright);
  fuzzyLED->addFuzzyOutput(brightnessOutput);

  // Fuzzy Rules
  // Rules 1
  FuzzyRuleAntecedent *pagi_sempit = new FuzzyRuleAntecedent();
  pagi_sempit->joinWithAND(morning, narrow);
  FuzzyRuleConsequent *thenBrightnessRedup1 = new FuzzyRuleConsequent();
  thenBrightnessRedup1->addOutput(dim);
  FuzzyRule *fuzzyRule01 = new FuzzyRule(1, pagi_sempit, thenBrightnessRedup1);
  fuzzyLED->addFuzzyRule(fuzzyRule01);

  // Rules 2
  FuzzyRuleAntecedent *siang_sempit = new FuzzyRuleAntecedent();
  siang_sempit->joinWithAND(afternoon, narrow);
  FuzzyRuleConsequent *thenBrightnessRedup2 = new FuzzyRuleConsequent();
  thenBrightnessRedup2->addOutput(dim);
  FuzzyRule *fuzzyRule02 = new FuzzyRule(2, siang_sempit, thenBrightnessRedup2);
  fuzzyLED->addFuzzyRule(fuzzyRule02);

  // Rules 3
  FuzzyRuleAntecedent *malam_sempit = new FuzzyRuleAntecedent();
  malam_sempit->joinWithAND(night, narrow);
  FuzzyRuleConsequent *thenBrightnessTerang1 = new FuzzyRuleConsequent();
  thenBrightnessTerang1->addOutput(moderate);
  FuzzyRule *fuzzyRule03 = new FuzzyRule(3, malam_sempit, thenBrightnessTerang1);
  fuzzyLED->addFuzzyRule(fuzzyRule03);

  // Rules 4
  FuzzyRuleAntecedent *pagi_standar = new FuzzyRuleAntecedent();
  pagi_standar->joinWithAND(morning, standard);
  FuzzyRuleConsequent *thenBrightnessRedup3 = new FuzzyRuleConsequent();
  thenBrightnessRedup3->addOutput(dim);
  FuzzyRule *fuzzyRule04 = new FuzzyRule(4, pagi_standar, thenBrightnessRedup3);
  fuzzyLED->addFuzzyRule(fuzzyRule04);

  // Rules 5
  FuzzyRuleAntecedent *siang_standar = new FuzzyRuleAntecedent();
  siang_standar->joinWithAND(afternoon, standard);
  FuzzyRuleConsequent *thenBrightnessRedup4 = new FuzzyRuleConsequent();
  thenBrightnessRedup4->addOutput(dim);
  FuzzyRule *fuzzyRule05 = new FuzzyRule(5, siang_standar, thenBrightnessRedup4);
  fuzzyLED->addFuzzyRule(fuzzyRule05);

  // Rules 6
  FuzzyRuleAntecedent *malam_standar = new FuzzyRuleAntecedent();
  malam_standar->joinWithAND(night, standard);
  FuzzyRuleConsequent *thenBrightnessTerang2 = new FuzzyRuleConsequent();
  thenBrightnessTerang2->addOutput(bright);
  FuzzyRule *fuzzyRule06 = new FuzzyRule(6, malam_standar, thenBrightnessTerang2);
  fuzzyLED->addFuzzyRule(fuzzyRule06);

  // Rules 7
  FuzzyRuleAntecedent *pagi_luas = new FuzzyRuleAntecedent();
  pagi_luas->joinWithAND(morning, wide);
  FuzzyRuleConsequent *thenBrightnessTerang3 = new FuzzyRuleConsequent();
  thenBrightnessTerang3->addOutput(moderate);
  FuzzyRule *fuzzyRule07 = new FuzzyRule(7, pagi_luas, thenBrightnessTerang3);
  fuzzyLED->addFuzzyRule(fuzzyRule07);

  // Rules 8
  FuzzyRuleAntecedent *siang_luas = new FuzzyRuleAntecedent();
  siang_luas->joinWithAND(afternoon, wide);
  FuzzyRuleConsequent *thenBrightnessRedup5 = new FuzzyRuleConsequent();
  thenBrightnessRedup5->addOutput(dim);
  FuzzyRule *fuzzyRule08 = new FuzzyRule(8, siang_luas, thenBrightnessRedup5);
  fuzzyLED->addFuzzyRule(fuzzyRule08);

  // Rules 9
  FuzzyRuleAntecedent *malam_luas = new FuzzyRuleAntecedent();
  malam_luas->joinWithAND(night, wide);
  FuzzyRuleConsequent *thenBrightnessTerang4 = new FuzzyRuleConsequent();
  thenBrightnessTerang4->addOutput(bright);
  FuzzyRule *fuzzyRule09 = new FuzzyRule(9, malam_luas, thenBrightnessTerang4);
  fuzzyLED->addFuzzyRule(fuzzyRule09);

  // Set up the LED pin
  pinMode(LED, OUTPUT);
}

void loop()
{
  Serial.println("Enter current hour (5-24): ");
  while (Serial.available() == 0) {
    // Wait for user input
  }
  int currentHour = Serial.parseInt();
  while (Serial.read() != '\n') {
    // Wait for user to press enter
  }
  Serial.print("Current Hour: ");
  Serial.println(currentHour);

  Serial.println("Enter room volume (0-80): ");
  while (Serial.available() == 0) {
    // Wait for user input
  }
  int jml = Serial.parseInt();
  while (Serial.read() != '\n') {
    // Wait for user to press enter
  }
  Serial.print("Room Volume: ");
  Serial.println(jml);

  // Fuzzy inference for LED brightness
  fuzzyLED->setInput(3, currentHour);
  fuzzyLED->setInput(4, jml);
  fuzzyLED->fuzzify();
  ledBrightness = fuzzyLED->defuzzify(2);

  // Control the LED brightness
  analogWrite(LED, ledBrightness);

  // Display the result
  Serial.print("LED Brightness: ");
  Serial.println(ledBrightness);
  Serial.println("====================================");
}
