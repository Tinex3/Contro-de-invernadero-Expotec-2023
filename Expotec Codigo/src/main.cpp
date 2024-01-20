#include <Arduino.h>
#include <DHT.h>

#define DHTPIN 2
#define DHTTYPE DHT11

#define BAUDIOS 115200
#define TIEMPO_ACCION 5000 // Tiempo de ejecución de la acción en milisegundos (por ejemplo, 5 segundos)
#define INTERVALO_LECTURA 500 // Intervalo de lectura en milisegundos (150 ms en este caso)



typedef struct Controldeinvernadero{
    uint16_t LM35;
    uint16_t Lectura_En_Tierra;
    uint16_t BOMBA;
    uint16_t VENTILADOR1;
    uint16_t VENTILADOR2;
}Control_Agua;
Control_Agua Maqueta;



typedef struct Datos
{
    uint16_t LecturaLM35;
    uint16_t ValorTierra;
    uint16_t HumedadDHT;
    uint16_t TemperaturaDHT;

}Lecturas;
Lecturas Sensores;





DHT dht(DHTPIN, DHTTYPE);

enum Estado {
    ESPERANDO_COMANDO,
    EJECUTANDO_ACCION
};

Estado estado = ESPERANDO_COMANDO;
unsigned long tiempoInicioAccion = 0;
unsigned long tiempoUltimaLectura = 0;

void lecturadedatos(Lecturas *Sensores,Control_Agua *Perifericos);
void ejecutarComando(char comando);
void activarBomba(Control_Agua *Maqueta);
void activarVentilador1(Control_Agua &Perifericos);
void activarVentilador2(Control_Agua &Perifericos);
void detenerSalidas(Control_Agua &Perifericos);
void Init_maqueta(Control_Agua &Perifericos);
void Imprimir(Lecturas *Sensores);


void setup() {
    Serial.begin(BAUDIOS);
    dht.begin();
    Init_maqueta(Maqueta);

}

void Init_maqueta(Control_Agua &Perifericos){
    pinMode(Perifericos.LM35,INPUT);
    pinMode(Perifericos.Lectura_En_Tierra, INPUT);
    pinMode(Perifericos.BOMBA, OUTPUT);
    pinMode(Perifericos.VENTILADOR1,OUTPUT);
    pinMode(Perifericos.VENTILADOR2,OUTPUT);
}

void loop() {
    unsigned long tiempoActual = millis();

    // Realizar lectura y enviar datos cada 150 ms
    if (tiempoActual - tiempoUltimaLectura >= INTERVALO_LECTURA) {
        lecturadedatos( &Sensores,&Maqueta);
        Imprimir(&Sensores);
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
                detenerSalidas(Maqueta);
                estado = ESPERANDO_COMANDO;
            }
            break;
    }
}

void ejecutarComando(char comando) {
    switch (comando) {
        case 'A':
            activarBomba(&Maqueta);
            break;
        case 'B':
            activarVentilador1(Maqueta);
            break;
        case 'C':
            activarVentilador2(Maqueta);
            break;
        case 'D':
            activarBomba(Maqueta);
            activarVentilador1(Maqueta);
            activarVentilador2(Maqueta);
            break;
        // Agrega más casos de comandos si es necesario
    }
}

void activarBomba(Control_Agua &Perifericos){
    digitalWrite(Perifericos.BOMBA, HIGH);
    tiempoInicioAccion = millis();
    estado = EJECUTANDO_ACCION;
}

void activarVentilador1(Control_Agua &Perifericos) {
    digitalWrite(Perifericos.VENTILADOR1, HIGH);
    tiempoInicioAccion = millis();
    estado = EJECUTANDO_ACCION;
}

void activarVentilador2(Control_Agua &Perifericos) {
    digitalWrite(Perifericos.VENTILADOR2, HIGH);
    tiempoInicioAccion = millis();
    estado = EJECUTANDO_ACCION;
}

void detenerSalidas(Control_Agua &Perifericos) {
    digitalWrite(Perifericos.BOMBA, LOW);
    digitalWrite(Perifericos.VENTILADOR1, LOW);
    digitalWrite(Perifericos.VENTILADOR2, LOW);
}

void lecturadedatos(Lecturas *Sensores, Control_Agua *Maqueta) {
    // Lógica para leer datos de los sensores y enviarlos por el puerto serie
    int valorLM35 = analogRead(Maqueta->LM35);
    Sensores->LecturaLM35 = 10000+((5*valorLM35*100)/1024); // Convertir el valor a temperatura en grados Celsius

    int valorTierra = 10000+analogRead(Maqueta->Lectura_En_Tierra);
    Sensores->ValorTierra = valorTierra;
    Sensores->HumedadDHT = 10000+dht.readHumidity();
    Sensores->TemperaturaDHT = 10000+dht.readTemperature();
}
void Imprimir(Lecturas *Sensores){
    // Enviar datos por Serial (puedes modificar este formato según tus necesidades)
    Serial.print(Sensores->ValorTierra);
    Serial.print("\t");
    Serial.print(Sensores->LecturaLM35);
    Serial.print("\t");
    Serial.print(Sensores->HumedadDHT);
    Serial.print("\t");
    Serial.print(Sensores->TemperaturaDHT);
    Serial.print("\t"); 
}