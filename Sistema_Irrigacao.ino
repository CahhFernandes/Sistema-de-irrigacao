#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiServer.h>
#include <WiFiUdp.h>
 

#define SSID_REDE     "House_Pokemon_"  
#define SENHA_REDE    "Carolina17121998*" 
#define INTERVALO_ENVIO_THINGSPEAK  20000

char EnderecoAPIThingSpeak[] = "api.thingspeak.com";
String ChaveEscritaThingSpeak = "J0AXPPG6M97P7145";
long lastConnectionTime; 
WiFiClient client;
 

void EnvioDadosThingspeak(String StringDados);
void ConexaoWiFi(void);
float LeituraUmidade(void);


void EnvioDadosThingspeak(String StringDados)
{
    if (client.connect(EnderecoAPIThingSpeak, 80))
    {         
        client.print("POST /update HTTP/1.1\n");
        client.print("Host: api.thingspeak.com\n");
        client.print("Connection: close\n");
        client.print("X-THINGSPEAKAPIKEY: "+ChaveEscritaThingSpeak+"\n");
        client.print("Content-Type: application/x-www-form-urlencoded\n");
        client.print("Content-Length: ");
        client.print(StringDados.length());
        client.print("\n\n");
        client.print(StringDados);
   
        lastConnectionTime = millis();
        Serial.println("- Informações enviadas ao ThingSpeak!");
     }   
}

void ConexaoWiFi(void)
{
    client.stop();
    Serial.println("Conectando-se à rede WiFi...");
    Serial.println();  
    delay(1000);
    WiFi.begin(SSID_REDE, SENHA_REDE);
 
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(500);
        Serial.print(".");
    }
 
    Serial.println("");
    Serial.println("WiFi connectado com sucesso!");  
    Serial.println("IP obtido: ");
    Serial.println(WiFi.localIP());
 
    delay(1000);
}
 

float UmidadeSolo(void)
{
    int ValorADC;
    float UmidadePercentual;
 
     ValorADC = analogRead(0);
     Serial.print("[Leitura ADC] ");
     Serial.println(ValorADC);
 
     UmidadePercentual = 100 * ((978-(float)ValorADC) / 978);
     Serial.print("[Umidade Percentual] ");
     Serial.print(UmidadePercentual);
     Serial.println("%");
 
     return UmidadePercentual;
}
void setup()
{  
    Serial.begin(9600);
    lastConnectionTime = 0; 
    FazConexaoWiFi();
    Serial.println("Sistema de Irrigacao");
}
 
void loop()
{
    float UmidadeLida;
    int UmidadeTruncada;
    char FieldUmidade[11];
     
    if (client.connected())
    {
        client.stop();
        Serial.println("- Desconectado do ThingSpeak");
        Serial.println();
    }
 
    UmidadePercentualLida = FazLeituraUmidade();
    UmidadePercentualTruncada = (int)UmidadePercentualLida; 

    if(!client.connected() && 
      (millis() - lastConnectionTime > INTERVALO_ENVIO_THINGSPEAK))
    {
        sprintf(FieldUmidade,"field1=%d",UmidadePercentualTruncada);
        EnviaInformacoesThingspeak(FieldUmidade);
    }
 
     delay(1000);
}
