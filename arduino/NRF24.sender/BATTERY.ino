#ifdef BATTERY

//*read battery voltage part
int BatInput = A2; //cislo analogoveho vstupu
float BatVoltageD;
float BatVoltageA;
float BatVoltageP;

float BatVoltagePercent() {
  BatVoltageD = analogRead(BatInput);
  BatVoltageA = BatVoltageD * (3.3 / 1023.0);
  BatVoltageP = BatVoltageD / 1023 * 100;
  Serial.print("Napatie dig=");
  Serial.println(BatVoltageD);
  Serial.print("Napatie V=");
  Serial.print(BatVoltageA);
  Serial.print("Napatie V%=");
  Serial.println(BatVoltageP);
  return BatVoltageP;
}
//*read batter voltage part

#endif
