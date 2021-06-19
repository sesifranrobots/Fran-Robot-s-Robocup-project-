//------------------------------------------------------------------------------incluindo bibliotecas----------------------------------------------------------------------------------------
#include <Servo.h>            //bliclioteca para uso de servo motores
#include <SPI.h>              //bliclioteca para uso do protocolo SPI
#include <DS3231.h>           //bliclioteca para uso do Timer
#include <Wire.h>             //bliclioteca para uso do protocolo I2C
#include <Adafruit_GFX.h>     //bliclioteca para gerar imagens no display nokia 5110 
#include <Adafruit_PCD8544.h> //bliclioteca para uso do display nokia 5110 
#include <Adafruit_BNO055.h>  //bliclioteca para uso do giroscópio
#include <Adafruit_Sensor.h>  //bliclioteca de drivers unificados para uso de sensores 
#include <sensor_rgb.h>       //bliclioteca desenvolvida para leitura de cores RGB
#include <GY53_PWM.h>         //bliclioteca para uso dos sensores de distancia GY-53 em mode PWM
#include <Ultra.h>            //bliclioteca para uso dos sensores ultrassonicos


//------------------------------------------------------------------------------Definindo Objetos---------------------------------------------------------------------------------------------

//_______________________________________Definição dos Motores____________________________________________
#define MDF 4  //motor direita para frente
#define MDT 5  //motor direita para tras
#define MEF 6  //motor esquerda para frente
#define MET 7  //motor direita para tras

//Enconder
#define encoderIE 18  //interrupção esquerda
#define encoderDE 16  //digital esquerda
#define encoderID 19  //interrupção direita
#define encoderDD 17  //digital direita

//Variável para controle da potencia aplicada nos motores
int potdir = 0;
int potesq = 0;

//variaveis para encoder E
byte encoder_IE = 0;
int pulsosE = 0;
boolean DirecaoE = 0;
//variaveis para encoder D
byte encoder_ID = 0;
int pulsosD = 0;
boolean DirecaoD = 0;

//_______________________________________Definição dos Switchs____________________________________________
#define switchtras 52    //switch traseiro
#define switchfrente 15  //switch frontal
#define switchparede 12  //switch parede
#define switchgarra 14   //switch garra

#define switchvit 13  //Contato vitima

//_______________________________________SENSOR DISTANCIA___________________________________________________
#define pingydireita 29   //sensor de distandia da direita
#define pingyesquerda 27  //sensor de distandia da esquerda
#define pingyfrente 31    //sensor de distandia frontal

#define ultraD_t 24  //trig ultassonico direita
#define ultraD_e 25  //echo ultassonico direita
#define ultraE_t 22  //trig ultassonico esquerda
#define ultraE_e 23  //echo ultassonico esquerda

GY53 gydireita(pingydireita, 100);      //Objeto para sensor de distancia da direita
GY53 gyesquerda(pingyesquerda, 100);    //Objeto para sensor de distancia da esquerda
GY53 gyfrente(pingyfrente, 100);        //Objeto para sensor de distancia frontal

ultra_u ultraD(ultraD_t, ultraD_e, 110);  //Objeto para ultrassonico direito
ultra_u ultraE(ultraE_t, ultraE_e, 110);  //Objeto para ultrassonico esquerda

//variaveis para armazenar leitura dos sendsores de distancia
byte lultrad, lultrae, gydistft, gydistd, gydiste = 0;

//_______________________________________SERVO MOTORES_______________________________________________________
#define servogarra 9    //servo motor da garra
#define servocacamba 8  //servo motor da camcamba
#define pservao 15      //servo motor braço da garra


Servo scacamba;  //objeto servo motor caçamba
Servo sgarra;    //objeto servo motor garra
Servo servao;    //objeto servo motor braço da garra

//__________________________________________SENSOR DE TENSAO_______________________________________________________
#define tensao A0  //dinição do pino de liação do sensore de tensão

//varaivel para calculo da tensao da bateria
float te = 0;

//____________________________________________MULTIPLEXADOR_________________________________________________________

#define multiplexador A1  //pino de leitura
#define S0 38             //pino do bit 0
#define S1 40             //pino do bit 1
#define S2 42             //pino do bit 2
#define S3 44             //pino do bit 3

//_______________________________________________LEDS______________________________________________________________
#define lede 51  //led de sinalização da esquerda
#define ledc 53  //led de sinalização cental
#define ledd 49  //led de sinalização da direita

int ledrgb[] = { 46, 48, 50 };  //Definindo pinos do RGB da placa de refletância 52(vermelho) 50(verde) 48(azul)

//__________________________________________PLACA DE REFLETANCIA_____________________________________________________
//sensors C9L3 (sensor de preto e brnco)
#define ep A7  //sensor esquerda ponta
#define em A8  //sensor esquerda meio
#define ed A9  //sensor esquerda direita

#define ce A10  //sensor central à esquerda
#define c A12   //sensor central
#define cd A11  //sensor central à direita

#define de A13  //sensor direita esquerda
#define dm A14  //sensor direita meio
#define dp A15  //sensor direita ponta

// Placa Traseira
#define ept A3  //sensor esquerda esquerda
#define emt A4  //sensor esquerda meio
#define dmt A5  //sensor direita meio
#define dpt A6  //sensor direita esquerda

//LDRS (Sensor de cor)
#define pldrep 0  //LDR esquerda ponta
#define pldrem 1  //LDR esquerda meio
#define pldred 2  //LDR esquerda direita

#define pldrde 3  //LDR direita esquerda
#define pldrdm 4  //LDR direita meio
#define pldrdp 5  //LDR direita ponta


LDRRGB rgbldrdp(multiplexador, 1);  //objeto RGB dp
LDRRGB rgbldrdm(multiplexador, 7);  //objeto RGB dm
LDRRGB rgbldrde(multiplexador, 14); //objeto RGB de
LDRRGB rgbldrep(multiplexador, 21); //objeto RGB ep
LDRRGB rgbldrem(multiplexador, 28); //objeto RGB em
LDRRGB rgbldred(multiplexador, 35); //objeto RGB ed


//Variável utilizada para armazenar a leitura do sensor C9L3 da placa frontal
int ldm = 0;
int lde = 0;
int ldp = 0;
int lcd = 0;
int lc = 0;
int lce = 0;
int led = 0;
int lem = 0;
int lep = 0;

//Variável utilizada para armazenar a leitura do sensor C9L3 da placa traseira
int lept = 0;
int lemt = 0;
int ldmt = 0;
int ldpt = 0;

//Variável utilizada para armazenar a leitura do sensor do LDR do sendor de cor da esquerda
int ldrdp = 0;
int ldrdm = 0;
int ldrde = 0;

//Variável utilizada para armazenar a leitura do sensor do LDR do sensor de cor da direita
int ldred = 0;
int ldrem = 0;
int ldrep = 0;

//Variáveis para logica do PID para seguimento de linha
int difldp, difldm, diflde, difled, diflem, diflep = 0;
int pldp, pldm, plde, pled, plem, plep = 0;

//variaveis para identificar linha a frete em um cruzamento durante o seguimento de linha
bool controle = false;
long tempoalinha = 0;

bool verdedir = false;  //Variável para identificação do verde na direita
bool verdeesq = false;  //Variável para identificação do verde na esquerda
bool vermelhoesq = false;
bool vermelhodir = false;

//__________________________________________ DISPLAY_____________________________________________________
#define rst 36
#define cs 34
#define dc 32
#define din 30
#define clk 28
#define luzD 26

byte contraste = 0; //varialvel para controlo do contraste do display

//criando obejeto para display
Adafruit_PCD8544 display = Adafruit_PCD8544(clk, din, dc, cs, rst);

//__________________________________________GIROSCÓPIO_____________________________________________________
//criando obejeto para giroscópio
Adafruit_BNO055 bno = Adafruit_BNO055(55, 0x29);

//variaveis para giroscopio
double eixox = 0;
double eixoy = 0;
double eixoz = 0;
double eixoxaux = 0;
byte inclinacao = 0;

//__________________________________________TIMER_____________________________________________________
//crtiando objeto para timer
DS3231  rtc(SDA, SCL);
Time t;

//variaveis para timer
int segundos = 0; //Variável guarda o tempo dos segundos
int minutos = 0; //Variável guarda o tempo dos minutos
int horas = 0; //Variável guarda o tempo das horas

byte variavelByte = 0; //Variável para resetar o timer no início da rodada

//---------------------------------------------------VARIAVEIS GERAIS-------------------------------------------------------------------

//variavel para controle de estado
byte estado = 0;

//Variável para verificação de aperto o switch da frente
bool apertofrente = false;

//Variáveis para FR_testes
byte tela = 0;
byte clic = 0;
byte clic_m1 = 0;
byte clic_e1 = 0;
byte clic_e2 = 0;
byte clic_d1 = 0;
byte clic_r1 = 0;
byte clic_r2 = 0;
byte clic_r3 = 0;
byte clic_t1 = 0;
byte clic_l1 = 0;
byte clic_s1 = 0;
byte clic_s2 = 90;
byte clic_ga1 = 0;

unsigned long tempo = 0;    //Variável utilizada para armazenar o tempo de execução do programa
unsigned long tempo2 = 0;   //Variável utlizando quando o robô deve fazer algo por certo período de tempo
unsigned long tempo3 = 500; //Variável utlizando quando o robô deve fazer algo por certo período de tempo

byte parede = 0;
byte triangulo = 0;
byte qtdevitimas = 0;

byte verificadistancia = 0;
byte confirmadistancia = 0;

byte obscurva = false;




//===============================================================================================================================
//======================================================SETUP====================================================================
//===============================================================================================================================
void setup() {

  //-----------------------------------------------INICIANDO COMUNICAÇÕES---------------------------------------------------------
  //Serial.begin(9600);
  //rtc.begin();
  delay(1000);
  bno.begin();
  //bno.setExtCrystalUse(true);

  //-----------------------------------------------CONFURAÇÃO INICIAL DO DISPALY-----------------------------------------------
  display.begin();
  //EEPROM.write(224, 50);
  contraste = EEPROM.read(224);
  display.setContrast(contraste);
  display.clearDisplay();
  ESCREVE("FRAN", 17, 8, 2); // mensagem, coluna, linha, tamanho = 1 ou 2
  ESCREVE("ROBOT'S", 0, 24, 2);
  delay(500);

  //-----------------------------------------------PIN MODE---------------------------------------------------------------------


  //****SENSORES DE DISTÂNCIA GY*******
  pinMode(pingyfrente, INPUT);
  pinMode(pingydireita, INPUT);
  pinMode(pingyesquerda, INPUT);

  //****MOTORES*******
  pinMode(MDF, OUTPUT);
  pinMode(MDT, OUTPUT);
  pinMode(MEF, OUTPUT);
  pinMode(MET, OUTPUT);

  //****ENCODER*******
  pinMode(encoderDE, INPUT);
  attachInterrupt(digitalPinToInterrupt(encoderIE), CALCULOPULSOE, CHANGE);
  pinMode(encoderDD, INPUT);
  attachInterrupt(digitalPinToInterrupt(encoderID), CALCULOPULSOD, CHANGE);

  //****SWITCHS*******
  pinMode(switchtras, INPUT);
  pinMode(switchparede, INPUT);
  pinMode(switchgarra, INPUT);
  pinMode(switchvit, INPUT);

  //****sensor de tensão*******
  pinMode(tensao, INPUT);

  //****multiplexador*******
  pinMode(multiplexador, INPUT);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);

  //****LEDS*******
  pinMode(lede, OUTPUT);
  pinMode(ledc, OUTPUT);
  pinMode(ledd, OUTPUT);
  pinMode(ledrgb[0], OUTPUT);
  pinMode(ledrgb[1], OUTPUT);
  pinMode(ledrgb[2], OUTPUT);
  pinMode(luzD, OUTPUT);

  //****PLACA DE REFLETÂNCIA FRONTAL*******
  pinMode(ep, INPUT);
  pinMode(em, INPUT);
  pinMode(ed, INPUT);
  pinMode(ce, INPUT);
  pinMode(c, INPUT);
  pinMode(cd, INPUT);
  pinMode(de, INPUT);
  pinMode(dm, INPUT);
  pinMode(dp, INPUT);

  //****PLACA DE REFLETÂNCIA TRASEIRA*******
  pinMode(ept, INPUT);
  pinMode(emt, INPUT);
  pinMode(dmt, INPUT);
  pinMode(dpt, INPUT);


  //-----------------------------------------------FR_TESTES------------------------------------------------------------------
  if (LEITURA_MULT_D(switchfrente) == 1) {
    estado = 3;
    digitalWrite(ledd, HIGH);
    delay (100);
    digitalWrite(ledd, LOW);
    digitalWrite(ledc, HIGH);
    delay (100);
    digitalWrite(ledc, LOW);
    digitalWrite(lede, HIGH);
    delay(100);
    digitalWrite(lede, LOW);
    digitalWrite(luzD, HIGH);
    display.clearDisplay();
    ESCREVE("FR_TESTES", 15, 20, 1);
    display.clearDisplay();
    delay(1000);
  }


  //---------------resetando o timer---------------------
  // Atualiza a variável de controle para o valor da EEPROM
  /*variavelByte = EEPROM.read(111);
    if (variavelByte == 0) {
    delay(2000);
    //rtc.setTime(0, 0, 4); // definindo o tempo de inicio em formato de 24 hrs
    //----------------------------------------------------------------------------
    variavelByte = 1; //atualização da variável de controle para calibração do timer
    EEPROM.write(111, variavelByte); //Posicao 111 da EEPROM é atualizada com o valor 1
    //----------------------------------------------------------------------------
    delay(500);

    for (byte x = 0; x < 3; x++) {
      //Rotina de sinalização para indicação que o timer foi calibrado
      digitalWrite(ledc, HIGH);
      delay(500);
      digitalWrite(ledc, LOW);
      delay(500);
    }
    delay(500);
    }*/

  MOVEGARRA(20, 500, 0);
  MOVESERVAO(70, 2000);
  MOVECACAMBA(100, 500);

  Serial.println("Setup finalizado");
  delay(200);

}



void loop() {
  if (estado == 0) {

    IDOBSTACULO();
    RAMPA();
    SEGUELINHA ();

  }

  else if (estado == 1) {
    SALAEVAC();
  }

  else if (estado == 2) {
    //fim de rodada();
    PARAR(1);
    digitalWrite(luzD, HIGH);
    display.clearDisplay();
    ESCREVE("TIME UP!", 0, 10, 1);
  }

  else if (estado == 3) {
    FR_TESTES();

  }
}
