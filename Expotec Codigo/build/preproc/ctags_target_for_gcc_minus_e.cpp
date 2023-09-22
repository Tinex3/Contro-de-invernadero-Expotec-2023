# 1 "E:\\GitHub\\Expotec-2023\\Expotec Codigo\\Expotec Codigo.ino"
# 2 "E:\\GitHub\\Expotec-2023\\Expotec Codigo\\Expotec Codigo.ino" 2
# 3 "E:\\GitHub\\Expotec-2023\\Expotec Codigo\\Expotec Codigo.ino" 2
# 4 "E:\\GitHub\\Expotec-2023\\Expotec Codigo\\Expotec Codigo.ino" 2
# 21 "E:\\GitHub\\Expotec-2023\\Expotec Codigo\\Expotec Codigo.ino"
const int PIN_DATOS_DQ = 9;


bool EstadoBooleanoCriticoHumedadTemperaturaDigital,EstadoBooleanoCriticoHumedadTemperaturaAnalogico;

DHT dht(2, DHT11);
OneWire oneWireObjeto(PIN_DATOS_DQ);
DallasTemperature sensorDS18B20(&oneWireObjeto);

void setup()
{
    Serial.begin(115200);
    dht.begin();
    sensorDS18B20.begin();

    pinMode(A0, 0x0);
    pinMode(A1, 0x0);
    pinMode(A2, 0x0);

    pinMode(3, 0x1);
    pinMode(5, 0x1);
    pinMode(6, 0x1);
}

void loop()
{
    int temperaturaDallas = 10000+sensorDS18B20.getTempCByIndex(0);
    int auxiliarDallas = sensorDS18B20.getTempCByIndex(0);

    int lecturaEnTierra = 10000+analogRead(A1);
    int AuxiliarEntierra = analogRead(A1);

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
    digitalWrite(3, 0x1);
    delay(1000);
    digitalWrite(3, 0x0);
    delay(10);

}

void controlVentilador1(int tierra, float temp, float humedad, float temperatura)
{
    // Lógica para controlar el ventilador 1
    digitalWrite(5, 0x1);
    delay(1000);
    digitalWrite(5, 0x0);
    delay(10);

}

void controlVentilador2(int tierra, float temp, float humedad, float temperatura)
{
    // Lógica para controlar el ventilador 2
    digitalWrite(6, 0x1);
    delay(1000);
    digitalWrite(6, 0x0);
    delay(10);

}

void controlBombaVentiladores(int tierra, float temp, float humedad, float temperatura)
{
    // Lógica para controlar la bomba y los ventiladores
    digitalWrite(3, 0x1);
    digitalWrite(5, 0x1);
    digitalWrite(6, 0x1);
    delay(1000);
    digitalWrite(3, 0x0);
    digitalWrite(5, 0x0);
    digitalWrite(6, 0x0);
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
