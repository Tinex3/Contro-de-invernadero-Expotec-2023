# Sistema de Control de Invernadero Expotec 2023



## Descripción

Este proyecto es un sistema de control de invernadero basado en control On-off. Utiliza tecnologías como LabVIEW 2013 y Arduino Firmware para proporcionar un control eficiente de las condiciones ambientales dentro del invernadero. La comunicación entre LabVIEW y Arduino se realiza a través de un puerto serial. Los valores de temperatura se pueden ajustar directamente en el código CPP.

## Características Clave

- Control de temperatura y humedad en tiempo real.
- Interfaz de usuario amigable diseñada con LabVIEW 2013.
- Integración con sensores, incluyendo el sensor Dallas 18B20, DHT11 y el sensor de humedad YI-38, para un control preciso.
- Configuración personalizada de umbrales y alarmas a través del código de arduino.
- Control de dispositivos, como bomba y ventiladores, para mantener las condiciones ideales.

## Requisitos de Instalación

Para ejecutar este proyecto, necesitas:

- LabVIEW 2013.
- Arduino IDE (versión X.X.X)
- Hardware compatible con Arduino (sensores Dallas 18B20, DHT11, sensor de humedad YI-38, sensores adicionales).
- Conexión física entre tu computadora y el Arduino a través de un puerto serial.
- NI Visa (versión 5.3) para la comunicación con LabVIEW.

## Instrucciones de Uso

1. Descarga y ejecuta la última versión del software.
2. Conecta los sensores y actuadores Arduino a tu invernadero.
3. Asegúrate de que la comunicación por puerto serial esté establecida entre LabVIEW y Arduino.
4. Abre la interfaz de usuario de LabVIEW 2013.
5. Configura los umbrales de temperatura y humedad directamente en el código CPP.
6. Inicia el sistema de control y monitorea las condiciones ambientales en tiempo real.
7. Controla dispositivos como la bomba y los ventiladores según sea necesario.

## Ejemplos y Escenarios de Uso

- Controla la temperatura y humedad en tu invernadero para el cultivo de plantas sensibles.
- Automatiza el riego y la ventilación en función de las condiciones actuales.
- Recibe alertas cuando se detecten condiciones fuera de los umbrales establecidos.

## Contribución y Desarrollo

Agradecemos las contribuciones de la comunidad. Si deseas contribuir a este proyecto, sigue los pasos a continuación:

1. Haz un fork del repositorio.
2. Crea una nueva rama para tu contribución.
3. Realiza los cambios y pruebas necesarios.
4. Envía una solicitud de extracción (pull request).

## Licencia

Este proyecto está bajo la [Licencia Apache 2.0](https://www.apache.org/licenses/LICENSE-2.0).

## Contacto y Soporte

Si tienes preguntas o necesitas asistencia, puedes contactarme en `b.riquelme.gomez@gmail.com`.
