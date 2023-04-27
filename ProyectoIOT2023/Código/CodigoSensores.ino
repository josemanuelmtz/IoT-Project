#include <DHT.h> // importa librería para el sensor DHT11
#include <WiFi.h>
#include <PubSubClient.h>
#include <HTTPClient.h>

#define DHTPIN 2 // define el pin del sensor DHT11
#define DHTTYPE DHT11 // define el tipo de sensor DHT11

DHT dht(DHTPIN, DHTTYPE); // crea objeto del sensor DHT11

int MQ2 = 4; // define el pin del sensor MQ-2
int buzzer = 5; // define el pin del buzzer

// Configuración de RED y Broker
const char* ssid = "GDS1";
const char* password = "12345678";
const char* mqtt_server = "192.168.71.135";

//mqtt
WiFiClient wifi_client;
PubSubClient mqtt_client(wifi_client);

void setup() {
Serial.begin(9600);
dht.begin(); // inicializa el sensor DHT11
pinMode(MQ2, INPUT); // establece el pin del sensor MQ-2 como entrada
pinMode(buzzer, OUTPUT); // establece el pin del buzzer como salida
Serial.println("Conectando");
Serial.println(ssid);
WiFi.begin(ssid, password);
while (WiFi.status() != WL_CONNECTED) {
Serial.print("Conectando...");
Serial.println(".");
delay(500);
}
Serial.println("Conexión WiFi establecida.");
mqtt_client.setServer(mqtt_server, 1883);
mqtt_client.setCallback(callback);
}

void callback(char* topic, byte* payload, unsigned int length){
payload[length] = '\0';
String val = String((char*)payload);
Serial.println(val);
}

void loop() {
if (!mqtt_client.connected()) {
if (mqtt_client.connect("ESP32")) {
Serial.println("Conexion exitosa");
}
}

delay(2000); // Retardo para la lectura del sensor

float hum = dht.readHumidity(); // lee la humedad del sensor DHT11
float temp = dht.readTemperature(); // lee la temperatura del sensor DHT11 en grados Celsius
float f = dht.readTemperature(true); // lee la temperatura del sensor DHT11 en grados Fahrenheit
float gas = analogRead(MQ2); // lee la detección de gas del sensor MQ-2

Serial.print("Humedad: ");
Serial.print(hum);
Serial.print("%\t");
Serial.print("Temperatura: ");
Serial.print(temp);
Serial.print("°C\t");
Serial.print(f);
Serial.println("°F");
Serial.print("Deteccion de gas: ");
Serial.print(gas);
Serial.println();

// verifica si la detección de gas es mayor a 1600
if (gas > 1200) {
digitalWrite(buzzer, HIGH); // enciende el buzzer
}
else {
digitalWrite(buzzer, LOW); // apaga el buzzer
}

char temp_str[10];
char hum_str[10];
char gas_str[10];

sprintf(temp_str, "%.2f", temp);
sprintf(hum_str, "%.2f", hum);
sprintf(gas_str, "%.2f", gas);

mqtt_client.publish("iot/temp", temp_str);
mqtt_client.publish("iot/hum", hum_str);
mqtt_client.publish("iot/gas", gas_str);

delay(2000); // espera 2 segundos
}