  #include <Wire.h>  // communicate with sensors
  
  #include <TimeLib.h>
  #include "RTClib.h"
  RTC_DS1307 rtc;
    
  #include <SPI.h>
  #include <SD.h>
  const int chipSelect = 5; // sd

  char nombreDia[7][12] = {"Domingo", "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado"};
  char nombreMes[12][12]= {"Enero", "Febrero", "Marzo", "Abril", "Mayo",  "Junio", "Julio","Agosto","Septiembre","Octubre","Noviembre","Diciembre"};
  int segundo,minuto,hora,dia,mes,diaDeLaSemana;
  long anio; //variable año
  DateTime HoraFecha;

  #include "DHT.h"        //Añadimos la libreria con la cual trabaja nuestro sensor
  #define DHTTYPE DHT22  // El sensor que vas a emplear. En este caso usamos el DHT11

  #define DHT1 2  
  #define DHT2 3   
  #define DHT3 4   //Pin sensor dht1

  DHT dht1 (DHT1, DHTTYPE);   
  DHT dht2 (DHT2, DHTTYPE);  
  DHT dht3 (DHT3, DHTTYPE);  //Indica el pin con el que trabajamos y el tipo de sensor


void setup(){
  
        
            
            rtc.begin(); //Inicializamos el RTC
            
            dht1.begin();  //Iniciamos el sensor
            dht2.begin();
            dht3.begin();   

            pinMode(5, OUTPUT);  //Inicializamos la sd
            if (!SD.begin(chipSelect)) {   // verifica si hay SD
                                       return;
                                       }
            }

void loop() {

             String dataString = "";  //Hacemos una cadena para la union de datos
  
             float h1, t1= 0;
             h1 = dht1.readHumidity();     //Guarda la lectura de la humedad en la variable float h
             t1 = dht1.readTemperature();  //Guarda la lectura de la temperatura en la variable float t

             float h2, t2= 0;
             h2 = dht2.readHumidity();     //Guarda la lectura de la humedad en la variable float h
             t2 = dht2.readTemperature();  //Guarda la lectura de la temperatura en la variable float t
  
             float h3, t3= 0;
             h3 = dht3.readHumidity();     //Guarda la lectura de la humedad en la variable float h
             t3 = dht3.readTemperature();  //Guarda la lectura de la temperatura en la variable float t

             HoraFecha = rtc.now(); //obtenemos la hora y fecha actual
             segundo=HoraFecha.second();
             minuto=HoraFecha.minute();
             hora=HoraFecha.hour();
             dia=HoraFecha.day();
             mes=HoraFecha.month();
             anio=HoraFecha.year();
             diaDeLaSemana=HoraFecha.dayOfTheWeek();
             
   
          

            File dataFile = SD.open("datalog4.txt", FILE_WRITE); //nombre de archivo 

            dataString += (" ") ;

              int Aa = mes;
              int Ae = dia;
              int Ai = hora;
              int Ao = minuto;   

            dataString += String (" Mes ") + String(Aa) + String (" ");
            dataString += String (" Dia ") + String(Ae) + String (" "); 
            dataString += String (" Hora ") + String(Ai) + String (" "); 
            dataString += String (":") + String(Ao) + String (" "); 

            float sensor1 = t1; //Declara para almacenar
            float sensor2 = h1; //Declara para almacenar
            
            dataString += String (" Temperatura ") + String(sensor1) + String (" C") ; //escribir
            dataString += String (" Humedad ") + String(sensor2) + String (" "); //escribir

            float sensor3 = t2; //Declara para almacenar
            float sensor4 = h2; //Declara para almacenar
         
            dataString += (" ") ; 
            dataString += String (" Temperatura ") + String(sensor3) + String (" C") ; //escribir
            dataString += String (" Humedad ") + String(sensor4) + String (" "); //escribir

            float sensor5 = t3; //Declara para almacenar
            float sensor6 = h3; //Declara para almacenar
         
            dataString += (" ") ; 
            dataString += String (" Temperatura ") + String(sensor5) + String (" C") ; //escribir
            dataString += String (" Humedad ") + String(sensor6) + String (" "); //escribir

            
                             // Si el archivo esta disponible escribe
            if (dataFile) {
                         
                          dataFile.println(dataString);
                          dataFile.close();
                          // Imprime lo registrado
                         
                          } 
                    
          delay(5000);
   
 }
