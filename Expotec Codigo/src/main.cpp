#include <Arduino.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

#define BAUDIOS 115200
#define TIEMPO_ACCION 5000 // Tiempo de ejecución de la acción en milisegundos (por ejemplo, 5 segundos)
#define INTERVALO_LECTURA 500 // Intervalo de lectura en milisegundos (150 ms en este caso)

#define LM35 A0
#define EN_TIERRA A1


#define BOMBA 3
#define VENTILADOR1 4
#define VENTILADOR2 5

DHT dht(DHTPIN, DHTTYPE);

enum Estado {
    ESPERANDO_COMANDO,
    EJECUTANDO_ACCION
};

Estado estado = ESPERANDO_COMANDO;
unsigned long tiempoInicioAccion = 0;
unsigned long tiempoUltimaLectura = 0;

void lecturadedatos();
void ejecutarComando(char comando);
void activarBomba();
void activarVentilador1();
void activarVentilador2();
void detenerSalidas();


void setup() {
    Serial.begin(BAUDIOS);
    dht.begin();
    pinMode(LM35, INPUT);
    pinMode(EN_TIERRA, INPUT);
    pinMode(BOMBA, OUTPUT);
    pinMode(VENTILADOR1, OUTPUT);
    pinMode(VENTILADOR2, OUTPUT);
}

void loop() {
    unsigned long tiempoActual = millis();

    // Realizar lectura y enviar datos cada 150 ms
    if (tiempoActual - tiempoUltimaLectura >= INTERVALO_LECTURA) {
        lecturadedatos();
        tiempoUltimaLectura = tiempoActual;
    }

    switch (estado) {
        case ESPERANDO_COMANDO:
            if (Serial.available()) {
                char var = Serial.read();
                ejecutarComando(var);
            }
            break;
        case EJECUTANDO_ACCION:
            if (millis() - tiempoInicioAccion >= TIEMPO_ACCION) {
                detenerSalidas();
                estado = ESPERANDO_COMANDO;
            }
            break;
    }
}

void ejecutarComando(char comando) {
    switch (comando) {
        case 'A':
            activarBomba();
            break;
        case 'B':
            activarVentilador1();
            break;
        case 'C':
            activarVentilador2();
            break;
        case 'D':
            activarBomba();
            activarVentilador1();
            activarVentilador2();
            break;
        // Agrega más casos de comandos si es necesario
    }
}

void activarBomba() {
    digitalWrite(BOMBA, HIGH);
    tiempoInicioAccion = millis();
    estado = EJECUTANDO_ACCION;
}

void activarVentilador1() {
    digitalWrite(VENTILADOR1, HIGH);
    tiempoInicioAccion = millis();
    estado = EJECUTANDO_ACCION;
}

void activarVentilador2() {
    digitalWrite(VENTILADOR2, HIGH);
    tiempoInicioAccion = millis();
    estado = EJECUTANDO_ACCION;
}

void detenerSalidas() {
    digitalWrite(BOMBA, LOW);
    digitalWrite(VENTILADOR1, LOW);
    digitalWrite(VENTILADOR2, LOW);
}

void lecturadedatos() {
    // Lógica para leer datos de los sensores y enviarlos por el puerto serie
    int valorLM35 = analogRead(LM35);
    int temperaturaLM35 = 10000+((5*valorLM35*100)/1024); // Convertir el valor a temperatura en grados Celsius

    int valorTierra = 10000+analogRead(EN_TIERRA);

    int humedad = 10000+dht.readHumidity();
    int temperaturaDHT = 10000+dht.readTemperature();

    // Enviar datos por Serial (puedes modificar este formato según tus necesidades)
    Serial.print(valorTierra);
    Serial.print("\t");
    Serial.print(temperaturaLM35);
    Serial.print("\t");
    Serial.print(humedad);
    Serial.print("\t");
    Serial.print(temperaturaDHT);
    Serial.print("\t"); 
    
}