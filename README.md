# ProjectsIoT2022-Caja fuerte

## Integrantes
- Camacho Pérez Cristian Uriel
- Mendoza Arredondo Alan Manuel
- Rangel Paredón Daniel
- Martínez García José Manuel

## Objetivo general
El obejtivo general es crear una caja fuerte inteligente, ya que esta contará con diversos senores y actuadores que le permitirán tener un mejor control de lo que se encuentre dentro de esta, además de brindar una mejor seguridad.

### Objetivos específicos
- Sólo se abrirá cuando la contraseña sea correcta 
- Advertirá a los dueños sobre posibles incendios o fugas de gas
- Elemento 3 de la lista de objetivos específicos
- Elemento 4 de la lista de objetivos específicos
...
- Elemento n de la lista de objetivos específicos

## Tabla de Software utilizado
| Id | Software | Vesión | Tipo |
|----|------------|-------------|--------|
|1| 	Visual Studio Code |	1.71.2 |	Freeware
|2| 	Arduino IDE |	2 |	2 |
|3| 	Libreria para sensor temperatura y humedad |	x |	x |
|4| 	Mosquitto |	5.0,3.1.1 | 	Freeware |
|5|	NODE-RED |	3.0 |	Freeware |
|5| 	Motor de base de datos |	x |	Freeware |

## Tabla con el hardware utilizado
| Id | Componente | Descripción | Imagen | Cantidad | Costo total |
|----|------------|-------------|--------|----------|-------------|
|   1 |  ESP32         |  	El módulo ESP32 es una solución de Wi-Fi/Bluetooth todo en uno, integrada y certificada que proporciona no solo la radio inalámbrica, sino también un procesador integrado con interfaces para conectarse con varios periféricos. |   ![217643833-2a3555c5-2952-46cf-814e-397453742464](https://user-images.githubusercontent.com/105257367/230508859-b4850e21-7c2b-4272-b3d7-0d3ad95d8447.jpeg)|    2      |      $300      |
|   2 |  Sensor de temperatura y humedad  DHT11        | El DHT11 es un sensor de temperatura y humedad digital de bajo costo. Utiliza un sensor capacitivo de humedad y un termistor para medir el aire circundante, y muestra los datos mediante una señal digital en el pin de datos (no hay pines de entrada analógica). | ![image](https://user-images.githubusercontent.com/105257367/230510094-872958dd-481d-4c51-baf9-1446b8ab70ec.png) |     1     |      $78       |
|   3 |  Buzzer         | Un buzzer o zumbador es un dispositivo que es capaz de enviar avisos a través del sonido. Puede ser mecánico, electromecánico o piezoeléctrico. | ![image](https://user-images.githubusercontent.com/105257367/230510032-1b1647e5-4b44-4852-b9e7-15d9f7ea2ba0.png)|     1     |      $50       |
|   4 |  Led RGB          | El LED RGB emite luz a través del paso de la corriente eléctrica, pero tiene la peculiaridad de estar compuesto por tres LEDs de diferentes colores: rojo (Red), verde (Green) y azul (Blue ), de ahí el nombre "RGB". | ![image](https://user-images.githubusercontent.com/105257367/230510182-00a601a2-430a-4fc9-b4f6-538fb0e69c21.png)|     1     |       $20     |
|   5 |  Display LCD          | Una pantalla de cristal líquido o LCD (sigla del inglés liquid-crystal display) es una pantalla delgada y plana formada por un número de píxeles en color o monocromos colocados delante de una fuente de luz o reflectora. A menudo se utiliza en dispositivos electrónicos de pilas, ya que utiliza cantidades muy pequeñas de energía eléctrica. | ![image](https://user-images.githubusercontent.com/105257367/230510806-9535946f-cd0d-4bfe-8db8-2466e6d91959.png)|   1     |     $120        |
|   6 |  Menbrane Switch         | El Teclado matricial 4×4 es un dispositivo desarrollado para ser utilizado con las placas de desarrollo Arduino, o con Microcontroladores, con este teclado se pueden asignar ordenes a cada una de sus 16 teclas, así mismo se le puede asignar un valor numero a las mismas, la ventaja de este teclado es que al tener una conexión flexible puede ser colocado en cualquier superficie sin problemas. | ![image](https://user-images.githubusercontent.com/105257367/230510946-4b997fe2-0a6c-4888-988e-c32daee5d2d7.png)|    1      |       $196      |
|   7 |  Placa fenólica        | El material fenólico, conocido también como placa, panel, tablero o conglomerado fenólico, es un laminado a base de hojas de celulosa impregnadas con resinas fenólicas prensadas a alta presión y temperatura. | ![image](https://pigra.com.mx/1165-medium_default/placa-fenolica-5x5cm-15mm-verde.jpg)|    1      |     $35      |
|   8 |  MQ-2        | Este es un sensor muy sencillo de usar, ideal para medir concentraciones de gas GLP y GNV en el aire. Puede detectar concentraciones desde 300 hasta 10000 ppm. | ![image](https://media.naylampmechatronics.com/262-superlarge_default/sensor-mq-2-gas-glp-gnv.jpg)|    1      |    $80         |
|  9 |  Servomotor   | Un servomotor es un actuador rotativo o motor que permite un control preciso en términos de posición angular, aceleración y velocidad, capacidades que un motor normal no tiene. |   ![217643550-267eca20-f819-4b53-a030-13fddb7b23e9](https://user-images.githubusercontent.com/105257367/230508822-af154d52-94e2-4044-9a8d-9e47d9e0cd01.jpeg)|    1    |    $180      |


## Epicas del proyecto (Minimo debe de haber una épica por integrante de equipo)
- Quiero tener una caja fuerte que cuente con sensores para garantizar la seguridad de lo que se encuentre dentro y en casos especiales de lo que se encuentre fuera.
- Quiero que el dispositivo emita un sonido si la contraseña es incorrecta.
- Que el dispositivo pueda monitorear el entorno que lo rodea y emitir sonidos acorde a lo que suceda en este.
- Quiero que el dispositivo cuente con una conexión a una base de datos para guardar y modificar las contraseñas.

## Tabla de historias de usuario
| Id | Historia de usuario | Prioridad | Estimación | Como probarlo | Responsable |
|----|---------------------|-----------|------------|---------------|-------------|
| 1  | Como usuario quiero tener una caja fuerte la cual solo se abra al ingresar la contraseña correcta   |  Alta        |  4 meses  |       |             |
| 2  | Como usuario que me muestre por un led si la contraseña es correcta ( verde ) o no ( rojo ) | Baja | 1 dia | Al ingresar una contraseña |            |
| 3  | Como usuario quiero la caja fuerte pueda detectar |           |            |               |             |
| 4  | Como usuario quiero que la caja detecte fugas de gas y haga sonar un buzzer cuando el nivel sea alto | Alta | 2 semanas | Al exponer el sensor a una fuga de gas|
| 5 | Como usuario quiero que la caja fuerte tenga un display en el cual se muestre si la contraseña ingresada es correcta | Alta | 2 semanas | Al ingresar contraseñas de manera correcta e incorrecta con el keypad|| |
## Prototipo en dibujo
- Coloca la fotografia de tu prototipo dibujado a lapiz


