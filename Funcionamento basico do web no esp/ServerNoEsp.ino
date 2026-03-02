//// ----- Bibliotecas -----
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <FSTools.h>
#include "FS.h"
#include "LittleFS.h"

// ----- variavel pra conectar na rede local -----
#define WIFI_NAME   "Nome da rede" //pode ter espaço 
#define WIFI_PASS   "Senha da rede" //pode ter espaço

// ----- variaveis para criar uma rede no esp -----
#define AP_SSID "ELCaraXD"
#define AP_PASS "SenhaSenhaSenha"


// ------ Porta da internet ------
ESP8266WebServer server(80);


// ----- variaves para usar o millis -----

unsigned long tempoAnterior = 0;
const long intervalo = 700;

// ----- função para manda um valor para o servidor ------

void enviarValor(float num) {

  if (WiFi.status() == WL_CONNECTED) { //if pra ver se ta conectado com a rede

    WiFiClient client;
    HTTPClient http;

    http.begin(client, "http://ip do pc para conectar no php dele/receber.php"); //iniciando conversa com o servidor

    http.addHeader("Content-Type", "application/json"); //falando que vai manda um arquivo json

    char json[100];
    sprintf(json, "{\"temperatura\":%.2f}", num); //criando o arquivo json e colocando o valor dentro dele

    int httpCode = http.POST(json); //mandando o json para o servidor


    http.end(); //finalizando a conversa
  }

}

// ------- funções do LittleFS -------

void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
    Serial.printf("Listing directory: %s\n", dirname);

    File root = fs.open(dirname,"r");
    if(!root){
        Serial.println("Failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        Serial.println("Not a directory");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if(levels){
                listDir(fs, file.name(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("  SIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}

void readFile(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\n", path);

    File file = fs.open(path, "r");
    if(!file || file.isDirectory()){
        Serial.println("Failed to open file for reading");
        return;
    }

    Serial.print("Read from file: ");
    while(file.available()){
        Serial.write(file.read());
    }
}

void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, "w");
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("File written");
    } else {
        Serial.println("Write failed");
    }
}

void appendFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Appending to file: %s\n", path);

    File file = fs.open(path, "a");
    if(!file){
        Serial.println("Failed to open file for appending");
        return;
    }
    if(file.print(message)){
        Serial.println("Message appended");
    } else {
        Serial.println("Append failed");
    }
}

void renameFile(fs::FS &fs, const char * path1, const char * path2){
    Serial.printf("Renaming file %s to %s\n", path1, path2);
    if (fs.rename(path1, path2)) {
        Serial.println("File renamed");
    } else {
        Serial.println("Rename failed");
    }
}

void deleteFile(fs::FS &fs, const char * path){
    Serial.printf("Deleting file: %s\n", path);
    if(fs.remove(path)){
        Serial.println("File deleted");
    } else {
        Serial.println("Delete failed");
    }
}

void testFileIO(fs::FS &fs, const char * path){
    File file = fs.open(path,"r");
    static uint8_t buf[512];
    size_t len = 0;
    uint32_t start = millis();
    uint32_t end = start;
    if(file && !file.isDirectory()){
        len = file.size();
        size_t flen = len;
        start = millis();
        while(len){
            size_t toRead = len;
            if(toRead > 512){
                toRead = 512;
            }
            file.read(buf, toRead);
            len -= toRead;
        }
        end = millis() - start;
        Serial.printf("%u bytes read for %u ms\n", flen, end);
        file.close();
    } else {
        Serial.println("Failed to open file for reading");
    }


    file = fs.open(path, "w");
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }

    size_t i;
    start = millis();
    for(i=0; i<2048; i++){
        file.write(buf, 512);
    }
    end = millis() - start;
    Serial.printf("%u bytes written for %u ms\n", 2048 * 512, end);
    file.close();
}


// ------- peguei essas funçoes nesse blog https://www.manualdomaker.com/article/sistema-de-arquivos-no-esp8266/ ---



void setup(void)
{
  // Inicializa a comunicação serial
  Serial.begin(115200);
 
  //Inicializar o LittleFS
  LittleFSConfig cfg;
    cfg.setAutoFormat(true);
    LittleFS.setConfig(cfg);
    delay(1000);
    if(!LittleFS.begin()){
        Serial.println("LittleFS Mount Failed");
        return;
    }

    listDir(LittleFS, "/", 0);

  // Internet
  WiFi.mode(WIFI_AP_STA); //falando o modo que vou usar se e criar uma rede ou usar a do roteador nesse caso as duas
  WiFi.softAP(AP_SSID, AP_PASS); //configuração par criar a rede no esp
  Serial.print("AP IP: "); //printando o ip do esp
  Serial.println(WiFi.softAPIP());
  
  WiFi.begin(WIFI_NAME, WIFI_PASS);// conectando no roteador
  Serial.println("Conectando à rede...");

  // Aguarda conexão
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
 
  // Printa o IP
  Serial.print("IP obtido: ");
  Serial.println(WiFi.localIP());
   
  // Configura as funções das páginas
  server.serveStatic("/", LittleFS, "/Banana.html"); //pegando o arquivo do html pelo littlefs recomendo ver o blog do cara de cima
  server.on("/ligar", Click); //puxando uma função quando alguem clica em um botao no html
  server.onNotFound(handle_nao_existe); //pagina inexistente

  // Inicializa o servidor
  server.begin();
  Serial.println("Web Server iniciado");
  
  
}


void loop(void)
{
  // Responde às requisições feitas
  server.handleClient();
  
  unsigned long agora = millis(); // usando a função millis que serve pique um delay sem para o codigo

  if (agora - tempoAnterior >= intervalo) {

    tempoAnterior = agora;

    float Numero = random(1,20);
    enviarValor(Numero);

  } //Loop para fica mandando um valor para o html
  
}

void Click(){
    Serial.println("Clicado");
}// função quando clica no botao

//função para caso a pagina nao exista
void handle_nao_existe()
{
  String message = "<html><meta http-equiv=\'content-type\' content=\'text/html; charset=utf-8\'>";
  message += "<h1>Página não encontrada</h1></html>";
 
  server.send(200, "text/html", message); //criando um html com string 
}