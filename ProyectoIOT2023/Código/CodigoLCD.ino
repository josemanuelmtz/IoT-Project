#include <Wire.h>               // importa librería Wire para comunicación I2C
#include <LiquidCrystal_I2C.h>  // importa librería para controlar display LCD por I2C
#include <Keypad.h>             // importa librería Keypad
#include <Servo.h>
#ifdef ESP32
#include <WiFi.h>
#else
#include <ESP8266WiFi.h>
#endif
#include <WiFiClientSecure.h>
#include <UniversalTelegramBot.h>  // Universal Telegram Bot Library written by Brian Lough: https://github.com/witnessmenow/Universal-Arduino-Telegram-Bot
#include <ArduinoJson.h>

  // Replace with your network credentials
  const char* ssid = "GDS1";
  const char* password = "12345678";


// Initialize Telegram BOT
#define BOTtoken "6176045208:AAFEEgcsu4xpqfM7lWKWXi5BEZBiXvvigJk"  // your Bot Token (Get from Botfather)

// Use @myidbot to find out the chat ID of an individual or a group
// Also note that you need to click "start" on a bot before it can
// message you
#define CHAT_ID "1180451719"

#ifdef ESP8266
  X509List cert(TELEGRAM_CERTIFICATE_ROOT);
#endif

  WiFiClientSecure client;
  UniversalTelegramBot bot(BOTtoken, client);

  // Checks for new messages every 1 second.
  int botRequestDelay = 1000;
  unsigned long lastTimeBotRan;


  // define constantes para el teclado
  const byte FILAS = 4;
  const byte COLUMNAS = 4;
  char keys[FILAS][COLUMNAS] = {
    { '1', '2', '3', 'A' },
    { '4', '5', '6', 'B' },
    { '7', '8', '9', 'C' },
    { '*', '0', '#', 'D' }
  };

  byte pinesFilas[FILAS] = { 13, 12, 14, 27 };
  byte pinesColumnas[COLUMNAS] = { 26, 25, 33, 32 };

  Keypad teclado = Keypad(makeKeymap(keys), pinesFilas, pinesColumnas, FILAS, COLUMNAS);  // crea objeto

  // define constantes para el display LCD
  const int LCD_COLS = 21;
  const int LCD_ROWS = 22;
  LiquidCrystal_I2C lcd(0x27, LCD_COLS, LCD_ROWS);  // crea objeto

  // define variables para el control del teclado
  char TECLA;
  char CLAVE[7];
  char CLAVE_MAESTRA[7] = "123456";
  byte INDICE = 0;

  // define pines para LED RGB
  const byte PIN_R = 15;
  const byte PIN_G = 2;
  const byte PIN_B = 4;

  const byte PIN_SERVO = 5;

  // define objeto para controlar el servo
  Servo servo;

  void handleNewMessages(int numNewMessages) {
    Serial.println("handleNewMessages");
    Serial.println(String(numNewMessages));

    for (int i = 0; i < numNewMessages; i++) {
      // Chat id of the requester
      String chat_id = String(bot.messages[i].chat_id);
      if (chat_id != CHAT_ID) {
        bot.sendMessage(chat_id, "Unauthorized user", "");
        continue;
      }

      // Print the received message
      String text = bot.messages[i].text;
      Serial.println(text);

      String from_name = bot.messages[i].from_name;

      if (text == "/start") {
        String welcome = "Welcome, " + from_name + ".\n";
        welcome += "Use the following commands to control your outputs.\n\n";
        welcome += "/Abrir Para abrir la caja fuerte \n";
        welcome += "/Cerrar Para cerrar la caja fuerte \n";
        welcome += "/Reiniciar Para reiniciar  \n";
        bot.sendMessage(chat_id, welcome, "");
      }

      if (text == "/Abrir") {
        bot.sendMessage(chat_id, "Open", "");
        Serial.println(" Correcta");
        lcd.print("Clave Correcta");
        digitalWrite(PIN_R, LOW);
        digitalWrite(PIN_G, HIGH);
        digitalWrite(PIN_B, LOW);
        servo.write(30);  // mueve el servo a la posición 90 grados
      }

      if (text == "/Cerrar") {
        bot.sendMessage(chat_id, "Close", "");
        Serial.println(" Incorrecta");
        lcd.print("Clave Incorrecta");
        digitalWrite(PIN_R, HIGH);
        digitalWrite(PIN_G, LOW);
        digitalWrite(PIN_B, LOW);
        servo.write(140);  // mueve el servo a la posición 90 grados
      }


      if (text == "/Reiniciar") {
        delay(2000);  // espera 2 segundos
      lcd.clear();  // limpia el contenido del display
      INDICE = 0;
      delay(1000);
      digitalWrite(PIN_R, LOW);
      digitalWrite(PIN_G, LOW);
      }
    }
  }

  void setup() {
    Serial.begin(9600);
    lcd.init();       // inicializa el display LCD
    lcd.backlight();  // enciende la retroiluminación del display

    pinMode(PIN_R, OUTPUT);
    pinMode(PIN_G, OUTPUT);
    pinMode(PIN_B, OUTPUT);

    servo.attach(PIN_SERVO);  // indica que el servo está conectado al pin 5
    servo.write(140);         // mueve el servo a la posición central


#ifdef ESP8266
    configTime(0, 0, "pool.ntp.org");  // get UTC time via NTP
    client.setTrustAnchors(&cert);     // Add root certificate for api.telegram.org
#endif



    // Connect to Wi-Fi
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
#ifdef ESP32
    client.setCACert(TELEGRAM_CERTIFICATE_ROOT);  // Add root certificate for api.telegram.org
#endif
    while (WiFi.status() != WL_CONNECTED) {
      delay(1000);
      Serial.println("Connecting to WiFi..");
    }
    // Print ESP32 Local IP Address
    Serial.println(WiFi.localIP());
  }


  void loop() {
    if (millis() > lastTimeBotRan + botRequestDelay) {
      int numNewMessages = bot.getUpdates(bot.last_message_received + 1);

      while (numNewMessages) {
        Serial.println("got response");
        handleNewMessages(numNewMessages);
        numNewMessages = bot.getUpdates(bot.last_message_received + 1);
      }
      lastTimeBotRan = millis();
    }
    TECLA = teclado.getKey();
    if (TECLA) {
      CLAVE[INDICE] = TECLA;
      INDICE++;
      Serial.print(TECLA);
      lcd.print("*");  // muestra asterisco en el display en vez de los caracteres ingresados
    }

    if (TECLA == 'A') {
      lcd.setCursor(0, 1);  // mueve el cursor a la segunda fila del display
      Serial.println(" Incorrecta");
      lcd.print("Clave Incorrecta");
      digitalWrite(PIN_R, HIGH);
      digitalWrite(PIN_G, LOW);
      digitalWrite(PIN_B, LOW);
      servo.write(140);  // mueve el servo a la posición 90 grados
      delay(2000);       // espera 2 segundos
      lcd.clear();       // limpia el contenido del display
      INDICE = 0;
      delay(1000);
      digitalWrite(PIN_R, LOW);
      digitalWrite(PIN_G, LOW);
    }

    if (INDICE == 6) {
      lcd.setCursor(0, 1);  // mueve el cursor a la segunda fila del display
      if (!strcmp(CLAVE, CLAVE_MAESTRA)) {
        Serial.println(" Correcta");
        lcd.print("Clave Correcta");
        digitalWrite(PIN_R, LOW);
        digitalWrite(PIN_G, HIGH);
        digitalWrite(PIN_B, LOW);
        servo.write(30);  // mueve el servo a la posición 90 grados
      } else {
        Serial.println(" Incorrecta");
        lcd.print("Clave Incorrecta");
        digitalWrite(PIN_R, HIGH);
        digitalWrite(PIN_G, LOW);
        digitalWrite(PIN_B, LOW);
        servo.write(140);  // mueve el servo a la posición 90 grados
      }
      delay(2000);  // espera 2 segundos
      lcd.clear();  // limpia el contenido del display
      INDICE = 0;
      delay(1000);
      digitalWrite(PIN_R, LOW);
      digitalWrite(PIN_G, LOW);
    }
  }