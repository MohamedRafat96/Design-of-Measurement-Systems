
const int trigPin = 9;
const int echoPin = 10;
long duration;
double distance;

double KalmanFilter(double Data);
double KalmanFilter(double Data)
{
  static const double R = 10;
  static const double H = 1.00;
  static  double Q = 10;
  static  double P = 0;
  static  double inti_Data_Es = 4;
  static  double K = 0;

  K  = P*H/(H*P*H+R); // Updat kalman gain
  inti_Data_Es = inti_Data_Es + K*(Data-H*inti_Data_Es); // updata estimated
  P = (1-K*H)*P+Q;
  return inti_Data_Es;
}

void setup() {
pinMode(trigPin, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin, INPUT); // Sets the echoPin as an Input
Serial.begin(9600); // Starts the serial communication


}
void loop() {

digitalWrite(trigPin, LOW);
delayMicroseconds(2);
digitalWrite(trigPin, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin, LOW);
duration = pulseIn(echoPin, HIGH);
distance= duration*0.034/2;
double Data_Est = KalmanFilter(distance);
Serial.print(distance);
Serial.print(",");
Serial.print(Data_Est);
Serial.println();
delay(100);

}
