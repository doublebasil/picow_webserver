#define HBridgeForward 3
#define HBridgeBackward 2

void setup() {
  // put your setup code here, to run once:
  pinMode(HBridgeForward, OUTPUT);
  pinMode(HBridgeBackward, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(HBridgeForward, HIGH);
  delay(1000);
  digitalWrite(HBridgeForward, LOW);
  delay(1000);

  digitalWrite(HBridgeBackward, HIGH);
  delay(1000);
  digitalWrite(HBridgeBackward, LOW);
  delay(1000);
}
