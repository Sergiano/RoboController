void setup() {
  pinMode(4, OUTPUT);      // устанавливает режим работы - выход
  pinMode(5, OUTPUT);      // устанавливает режим работы - выход
  pinMode(6, OUTPUT);      // устанавливает режим работы - выход
  pinMode(7, OUTPUT);      // устанавливает режим работы - выход
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(7, LOW);
  // put your main code here, to run repeatedly:
  digitalWrite(4, HIGH);
  delay(1000);
  // put your main code here, to run repeatedly:
  digitalWrite(4, LOW);
  // put your main code here, to run repeatedly:
  digitalWrite(5, HIGH);
  delay(1000);
  // put your main code here, to run repeatedly:
  digitalWrite(5, LOW);
  // put your main code here, to run repeatedly:
  digitalWrite(6, HIGH);
  delay(1000);
  // put your main code here, to run repeatedly:
  digitalWrite(6, LOW);
  // put your main code here, to run repeatedly:
  digitalWrite(7, HIGH);
  delay(1000);
}
