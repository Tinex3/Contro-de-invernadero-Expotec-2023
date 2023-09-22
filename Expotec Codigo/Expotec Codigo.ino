#include <DHT.h>
#include <OneWire.h>
#include <DallasTemperature.h>

#define DHTPIN 2
#define DHTTYPE DHT11

#define BAUDIOS 115200
#define TEMPERATURA_CRITICA 35
#define HUMEDAD_CRITICA_DIGITAL 25
#define HUMEDAD_CRITICA_ANALOGICA 450

#define LM35 A0
#define EN_TIERRA A1
#define SENSOR_NIVEL A2

#define BOMBA 3
#define VENTILADOR1 5
#define VENTILADOR2 6

const int PIN_DATOS_DQ = 9;


bool EstadoBooleanoCriticoHumedadTemperaturaDigital,EstadoBooleanoCriticoHumedadTemperaturaAnalogico;

DHT dht(DHTPIN, DHTTYPE);
OneWire oneWireObjeto(PIN_DATOS_DQ);
DallasTemperature sensorDS18B20(&oneWireObjeto);

void setup()
{
    Serial.begin(BAUDIOS);
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
    int temperaturaDallas = 10000+sensorDS18B20.getTempCByIndex(0);
    int auxiliarDallas = sensorDS18B20.getTempCByIndex(0);

    int lecturaEnTierra = 10000+analogRead(EN_TIERRA);
    int AuxiliarEntierra = analogRead(EN_TIERRA);
    
    int lecturaHumedad = 10000+dht.readHumidity();
    int AuxiliarHumedad = dht.readHumidity();
    
    int lecturaTemperatura = 10000+dht.readTemperature();
    int AuxiliarTemperatura = dht.readTemperature();

    imprimirLecturas(lecturaEnTierra, temperaturaDallas, lecturaHumedad, lecturaTemperatura);




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
    delay(150);
    
}

void controlBomba(int tierra, float temp, float humedad, float temperatura)
{
    // Lógica para controlar la bomba
    digitalWrite(BOMBA, HIGH);
    delay(1000);
    digitalWrite(BOMBA, LOW);
    delay(10);
    
}

void controlVentilador1(int tierra, float temp, float humedad, float temperatura)
{
    // Lógica para controlar el ventilador 1
    digitalWrite(VENTILADOR1, HIGH);
    delay(1000);
    digitalWrite(VENTILADOR1, LOW);
    delay(10);
    
}

void controlVentilador2(int tierra, float temp, float humedad, float temperatura)
{
    // Lógica para controlar el ventilador 2
    digitalWrite(VENTILADOR2, HIGH);
    delay(1000);
    digitalWrite(VENTILADOR2, LOW);
    delay(10);
    
}

void controlBombaVentiladores(int tierra, float temp, float humedad, float temperatura)
{
    // Lógica para controlar la bomba y los ventiladores
    digitalWrite(BOMBA, HIGH);
    digitalWrite(VENTILADOR1, HIGH);
    digitalWrite(VENTILADOR2, HIGH);
    delay(1000);
    digitalWrite(BOMBA, LOW);
    digitalWrite(VENTILADOR1, LOW);
    digitalWrite(VENTILADOR2, LOW);
    delay(10);
    
}

// Agrega más funciones de control según sea necesario

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
