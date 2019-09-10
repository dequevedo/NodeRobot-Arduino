void RotateMotors(int leSpd, int x1, int x2, int y1, int y2, int riSpd) {
  Serial.print("Leu: ");
  Serial.print(leSpd);
  Serial.print(", ");
  Serial.print(x1);
  Serial.print(", ");
  Serial.print(x2);
  Serial.print(", ");
  Serial.print(y1);
  Serial.print(", ");
  Serial.print(y2);
  Serial.print(", ");
  Serial.println(riSpd);

  analogWrite(leftSpeed, leSpd);
  digitalWrite(left1, x1);
  digitalWrite(left2, x2);

  analogWrite(rightSpeed, riSpd);
  digitalWrite(right1, y1);
  digitalWrite(right2, y2);
}
