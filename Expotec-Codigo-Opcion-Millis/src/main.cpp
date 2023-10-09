#include <Arduino.h>
#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>

unsigned long tiempoanterior;
const long interval = 2000;

#define DHTPIN 2
#define DHTTYPE DHT11

#define LM35 A0
#define EN_TIERRA A1
#define SENSOR_NIVEL A2

#define BOMBA 3
#define VENTILADOR1 5
#define VENTILADOR2 6

#define tiempobomba 1000
#define tiempoventilador1 1000
#define tiempoventilador2 1000
#define tiempoBombaVentiladores 1000

const int PIN_DATOS_DQ = 9;

int temperaturaDallas;
int lecturaEnTierra;
int lecturaHumedad;
int lecturaTemperatura;
int auxentierra;

void controlBomba(int tierra, float temp, float humedad, float temperatura);
void controlVentilador1(int tierra, float temp, float humedad, float temperatura);
void controlVentilador2(int tierra, float temp, float humedad, float temperatura);
void controlBombaVentiladores(int tierra, float temp, float humedad, float temperatura);
void imprimirLecturas(int tierra, int temp, int humedad, int temperatura);

DHT dht(DHTPIN, DHTTYPE);
OneWire oneWireObjeto(PIN_DATOS_DQ);
DallasTemperature sensorDS18B20(&oneWireObjeto);

void setup()
{
  Serial.begin(9600);
  dht.begin();
  sensorDS18B20.begin();

  pinMode(LM35, INPUT);
  pinMode(EN_TIERRA, INPUT);
  pinMode(SENSOR_NIVEL, INPUT);

  pinMode(BOMBA, OUTPUT);
  pinMode(VENTILADOR1, OUTPUT);
  pinMode(VENTILADOR2, OUTPUT);
}
void loop()
{
  sensorDS18B20.requestTemperatures();
  temperaturaDallas = 10000 + sensorDS18B20.getTempCByIndex(0);
  // int auxiliarDallas = sensorDS18B20.getTempCByIndex(0);

  lecturaEnTierra = 10000 + analogRead(EN_TIERRA);
  lecturaHumedad = 10000 + dht.readHumidity();
  lecturaTemperatura = 10000 + dht.readTemperature();
  if (Serial.available())
  {
    char var = Serial.read();
    switch (var)
    {
    case 'A':
      controlBomba(lecturaEnTierra, temperaturaDallas, lecturaHumedad, lecturaTemperatura);
      break;
    case 'B':
      controlVentilador1(lecturaEnTierra, temperaturaDallas, lecturaHumedad, lecturaTemperatura);
      break;
    case 'C':
      controlVentilador2(lecturaEnTierra, temperaturaDallas, lecturaHumedad, lecturaTemperatura);
      break;
    case 'D':
      controlBombaVentiladores(lecturaEnTierra, temperaturaDallas, lecturaHumedad, lecturaTemperatura);
      break;
    }
  }

  imprimirLecturas(lecturaEnTierra, temperaturaDallas, lecturaHumedad, lecturaTemperatura);
}

void controlBomba(int tierra, float temp, float humedad, float temperatura)
{
  if (tiempoanterior - tiempobomba < millis())
  {
    digitalWrite(BOMBA, HIGH);
    tiempoanterior = millis();
  }
  else
  {
    digitalWrite(BOMBA, LOW);
  }
  // Lógica para controlar la bomba
}

void controlVentilador1(int tierra, float temp, float humedad, float temperatura)
{
  // Lógica para controlar el ventilador 1
  if (tiempoanterior - tiempoventilador1 < millis())
  {
    digitalWrite(VENTILADOR1, HIGH);
    tiempoanterior = millis();
  }
  else
  {
    digitalWrite(VENTILADOR1, LOW);
  }
}

void controlVentilador2(int tierra, float temp, float humedad, float temperatura)
{
  if (tiempoanterior - tiempoventilador2 < millis())
  {
    digitalWrite(VENTILADOR2, HIGH);
    tiempoanterior = millis();
  }
  else
  {
    digitalWrite(VENTILADOR2, LOW);
  }

  // digitalWrite(VENTILADOR2, HIGH);
  // delay(1000);
  // digitalWrite(VENTILADOR2, LOW);
  // delay(10);
}

void controlBombaVentiladores(int tierra, float temp, float humedad, float temperatura)
{
  if (tiempoanterior - tiempoBombaVentiladores < millis())
  {
    digitalWrite(BOMBA, HIGH);
    digitalWrite(VENTILADOR1, HIGH);
    digitalWrite(VENTILADOR2, HIGH);
    tiempoanterior = millis();
  }
  else
  {
    digitalWrite(BOMBA, LOW);
    digitalWrite(VENTILADOR1, LOW);
    digitalWrite(VENTILADOR2, LOW);
  }
  
  // Lógica para controlar la bomba y los ventiladores
  // digitalWrite(BOMBA, HIGH);
  // digitalWrite(VENTILADOR1, HIGH);
  // digitalWrite(VENTILADOR2, HIGH);
  // delay(1000);
  // digitalWrite(BOMBA, LOW);
  // digitalWrite(VENTILADOR1, LOW);
  // digitalWrite(VENTILADOR2, LOW);
  // delay(10);
}

void imprimirLecturas(int tierra, int temp, int humedad, int temperatura)
{
  Serial.print(tierra);
  Serial.print("\t");
  Serial.print(temp);
  Serial.print("\t");
  Serial.print(humedad);
  Serial.print("\t");
  Serial.print(temperatura);
  Serial.print("\t");
}
