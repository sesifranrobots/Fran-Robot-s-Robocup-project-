//______________________________________________________ FUNÇÕES PARA SENSORES DE REFLETÂNCIA _____________________________________________________________________________
void ATUALIZASENSORES () {//INICIO ATUALIZASENSORES()
  /*Função para atualização das variáveis de leitura dos sensores
     da placa de refletância, sendo utilizada em diversos momentos
     da programação e tornando a escrita mais fácil sem precisar do
     analogRead */

  /* ldrdp = analogRead(ldrdp); // viriável para controle do ldr da direita mais a ponta
    ldrdm = analogRead(ldrdm); // viriável para controle do ldr da direita ao meio
    ldrde = analogRead(ldrde); // viriável para controle do ldr da direita esquerda
    ldred = analogRead(ldred); // viriável para controle do ldr da esquerda direita
    ldrem = analogRead(ldrem); // viriável para controle do ldr da esquerda ao meio
    ldrep = analogRead(ldrep); // variável para controle do ldr da esquerda mais a ponta*/

  ldp = analogRead(dp); // variável para controle do sensor da direita mais a ponta
  ldm = analogRead(dm); // variável para controle do sensor da direita ao meio
  lde = analogRead(de);
  lcd = analogRead(cd);
  lc = analogRead(c); // variável para controle do sensor do centro direita
  lce = analogRead(ce);
  led = analogRead(ed);
  lem = analogRead(em); // variável para controle do sensor da esquerda ao meio
  lep = analogRead(ep); // variável para controle do sensor da esquerda mais a ponta
}//FIM ATUALIZASENSORES()

void ATUALIZASENSOREST () {//INICIO ATUALIZASENSORES()
  lept = analogRead(ept);
  lemt = analogRead(emt);
  ldmt = analogRead(dmt);
  ldpt = analogRead(dpt);
}//FIM ATUALIZASENSORES()

//______________________________________________________ FUNÇÕES PARA SENSOR DE COR _____________________________________________________________________________
void CHECACORES() {//INICIO CHECACORES()
  /*Função para o robô realizar as leituras no padrão RGB*/

  /*Leds RGB da placa de refletância são
     todos desligados para o robô prosseguir
    com as leituras */
  digitalWrite(ledrgb[0], LOW); //Apaga o RGB cor VERMELHA
  digitalWrite(ledrgb[1], LOW); //Apaga o RGB cor VERDE
  digitalWrite(ledrgb[2], LOW); //Apaga o RGB cor AZUL

  for (byte i = 0; i <= 2; i++) {
    digitalWrite(ledrgb[i], HIGH);
    delay(50);

    LEITURA_MULT_A(pldrdp);
    rgbldrdp.leitura(i);
    LEITURA_MULT_A(pldrdm);
    rgbldrdm.leitura(i);
    LEITURA_MULT_A(pldrde);
    rgbldrde.leitura(i);

    LEITURA_MULT_A(pldred);
    rgbldred.leitura(i);
    LEITURA_MULT_A(pldrem);
    rgbldrem.leitura(i);
    LEITURA_MULT_A(pldrep);
    rgbldrep.leitura(i);

    digitalWrite(ledrgb[i], LOW);
    delay(10);
  }
  //Ao final da função ele acende os leds RGB com a cor Verde
  digitalWrite(ledrgb[1], HIGH);
}

void IDCORES() {//INICIO IDCORES
  /*viriável para o calculo da diferença entra a leitura com a cor verde
    e com a cor vermelha do lado da direita*/
  int difvdp = 0;

  //viriável para o calculo da diferença entra a leitura com a cor verde e com a cor vermelha do lado da esquerda
  int difvep = 0;

  //viriável para o calculo da diferença entra a leitura com a cor verde e com a cor vermelha do lado da direita
  int difvdm = 0;

  //viriável para o calculo da diferença entra a leitura com a cor verde e com a cor vermelha do lado da esquerda
  int difvem = 0;

  //viriável para o calculo da diferença entra a leitura com a cor verde e com a cor vermelha do lado da direita
  int difvde = 0;

  //viriável para o calculo da diferença entra a leitura com a cor verde e com a cor vermelha do lado da esquerda
  int difved = 0;

  //__________ _________________ ____________________ __________ ___________

  difvdp = rgbldrdp.cor('G') - rgbldrdp.cor('R');//Realiza o calculo da diferença entre a cor Verde e a vermelha do sensor direita ponta
  difvep = rgbldrep.cor('G') - rgbldrep.cor('R');//Realiza o calculo da diferença entre a cor Verde e a vermelha do sensor esquerda ponta

  difvdm = rgbldrdm.cor('G') - rgbldrdm.cor('R');//Realiza o calculo da diferença entre a cor Verde e a vermelha do sensor da direita ponta
  difvem = rgbldrem.cor('G') - rgbldrem.cor('R');//Realiza o calculo da diferença entre a cor Verde e a vermelha do sensor da esquerda ponta

  difvde = rgbldrde.cor('G') - rgbldrde.cor('R');//Realiza o calculo da diferença entre a cor Verde e a vermelha do sensor da direita ponta
  difved = rgbldred.cor('G') - rgbldred.cor('R');//Realiza o calculo da diferença entre a cor Verde e a vermelha do sensor da esquerda ponta

  /*Verificação com o ldr direita esquerda*/
  if (difvde <= 55) {
    /*Caso a diferença seja menor do que 50 o robô não identificou verde e sim
       branco ou preto pois a diferença entra a cor verde(RGB) e vermelha(RGB) quando ele
       realiza as leituras no VERDE é sempre maior que 50 */
  }


  else if (rgbldrde.cor('G') > rgbldrde.cor('R') && rgbldrde.cor('G') > rgbldrde.cor('B')) {
    /*Se a diferença for maior que 50 e a leitura com a cor verde for
      maior que a leitura com a cor vermelha e azul é caracterizado
      a cor verde*/
    verdedir = true;
    digitalWrite(lede, LOW);
    digitalWrite(ledd, HIGH);
    digitalWrite(ledc, HIGH);
    //delay(500);
  }

  else {
    /*Caso não tenha identificado nenhuma das anteriores é alguma
       outra cor */
  }

  //_________________________________________________________________________________
  //_________________________________________________________________________________
  //_________________________________________________________________________________
  //_________________________________________________________________________________
  //_________________________________________________________________________________



  /*Verificação com o ldr direita meio*/
  if (difvdm <= 55) {
    /*Caso a diferença seja menor do que 50 o robô não identificou verde e sim
       branco ou preto pois a diferença entra a cor verde(RGB) e vermelha(RGB) quando ele
       realiza as leituras no VERDE é sempre maior que 50 */
  }


  else if (rgbldrdm.cor('G') > rgbldrdm.cor('R') && rgbldrdm.cor('G') > rgbldrdm.cor('B')) {
    /*Se a diferença for maior que 50 e a leitura com a cor verde for
      maior que a leitura com a cor vermelha e azul é caracterizado
      a cor verde*/
    verdedir = true;
    digitalWrite(lede, LOW);
    digitalWrite(ledd, HIGH);
    digitalWrite(ledc, HIGH);
    //delay(500);
  }

  else {
    /*Caso não tenha identificado nenhuma das anteriores é alguma
       outra cor */
  }

  //_________________________________________________________________________________
  //_________________________________________________________________________________
  //_________________________________________________________________________________
  //_________________________________________________________________________________
  //_________________________________________________________________________________

  /*Verificação do ldr direita ponta*/
  if (difvdp <= 55) {
    /*Caso a diferença seja menor do que 50 o robô não identificou verde e sim
       branco ou preto pois a diferença entra a cor verde(RGB) e vermelha(RGB) quando ele
       realiza as leituras no VERDE é sempre maior que 50 */
  }


  else if (rgbldrdp.cor('G') > rgbldrdp.cor('R') && rgbldrdp.cor('G') > rgbldrdp.cor('B')) {
    /*Se a diferença for maior que 50 e a leitura com a cor verde for
      maior que a leitura com a cor vermelha e azul é caracterizado
      a cor verde*/
    verdedir = true;
    digitalWrite(lede, LOW);
    digitalWrite(ledd, HIGH);
    digitalWrite(ledc, HIGH);
    //delay(500);
  }
  else {
    /*Caso não tenha identificado nenhuma das anteriores é alguma
       outra cor */
  }

  //_________________________________________________________________________________
  //_________________________________________________________________________________
  //_________________________________________________________________________________
  //_________________________________________________________________________________
  //_________________________________________________________________________________
  //}//FIM VERIFICACAO DIREITA

  //_________________________________________________________________________________
  //_________________________________________________________________________________
  //_________________________________________________________________________________
  //_________________________________________________________________________________
  //_________________________________________________________________________________
  //_________________________________________________________________________________

  /*Verificação com o ldr esquerda direita*/
  if (difved <= 55) {
    /*Caso a diferença seja menor do que 50 o robô não identificou verde e sim
       branco ou preto pois a diferença entra a cor verde(RGB) e vermelha(RGB) quando ele
       realiza as leituras no VERDE é sempre maior que 50 */
  }


  else if (rgbldred.cor('G') > rgbldred.cor('R') && rgbldred.cor('G') > rgbldred.cor('B')) {
    /*Se a diferença for maior que 50 e a leitura com a cor verde for
      maior que a leitura com a cor vermelha e azul é caracterizado
      a cor verde*/
    verdeesq = true;
    digitalWrite(lede, LOW);
    digitalWrite(ledd, HIGH);
    digitalWrite(ledc, HIGH);
    //delay(500);
  }

  else {
    /*Caso não tenha identificado nenhuma das anteriores é alguma
       outra cor */
  }

  //_________________________________________________________________________________
  //_________________________________________________________________________________
  //_________________________________________________________________________________
  //_________________________________________________________________________________
  //_________________________________________________________________________________
  /*Verificação do ldr da esquerda meio*/
  if (difvem <= 55) {
    /*Caso a diferença seja menor do que 50 o robô não identificou verde e sim
      branco ou preto pois a diferença entra a cor verde(RGB) e vermelha(RGB) quando ele
      realiza as leituras no VERDE é sempre maior que 50 */
    //delay(500);
  }

  else if (rgbldrem.cor('G') > rgbldrem.cor('R') && rgbldrem.cor('G') > rgbldrem.cor('B')) {
    /*Se a diferença for maior que 50 e a leitura com a cor verde for
      maior que a leitura com a cor vermelha e azul é caracterizado
      a cor verde*/
    verdeesq = true;
    digitalWrite(lede, HIGH);
    digitalWrite(ledd, LOW);
    digitalWrite(ledc, HIGH);
    //delay(500);
  }
  else {
    /*Caso não tenha identificado nenhuma das anteriores é alguma
      outra cor */
    //delay(500);
  }

  //__________________________________________________________________________
  //__________________________________________________________________________
  //__________________________________________________________________________
  //__________________________________________________________________________
  //__________________________________________________________________________

  /*VERIFICAÇÃO COM O LDR ESQUERDA PONTA*/
  if (difvep <= 55) {
    /*Caso a diferença seja menor do que 50 o robô não identificou verde e sim
      branco ou preto pois a diferença entra a cor verde(RGB) e vermelha(RGB) quando ele
      realiza as leituras no VERDE é sempre maior que 50 */
    //delay(500);
  }

  else if (rgbldrep.cor('G') > rgbldrep.cor('R') && rgbldrep.cor('G') > rgbldrep.cor('B')) {
    /*Se a diferença for maior que 50 e a leitura com a cor verde for
      maior que a leitura com a cor vermelha e azul é caracterizado
      a cor verde*/
    //verdeesq = true;
    digitalWrite(lede, HIGH);
    digitalWrite(ledd, LOW);
    digitalWrite(ledc, HIGH);
    //delay(500);
  }
  else {
    /*Caso não tenha identificado nenhuma das anteriores é alguma
      outra cor */
    //delay(500);
  }

  //__________________________________________________________________________
  //__________________________________________________________________________
  //__________________________________________________________________________
  //__________________________________________________________________________
  //__________________________________________________________________________

  //DISPLAYRGB();

  //while (digitalRead(switchtras) == 0) {
  //}
  //delay(500);

  //return retorno;
}//FIM IDCORES


void IDVERMELHO() {//INICIO IDCORES

  /*viriável para o calculo da diferença entra a leitura com a cor verde
    e com a cor vermelha do lado da direita*/

  vermelhodir = false;
  vermelhoesq = false;


  /*viriável para o calculo da diferença entra a leitura com a cor verde
    e com a cor vermelha do lado da direita*/
  int difvdp = 0;

  //viriável para o calculo da diferença entra a leitura com a cor verde e com a cor vermelha do lado da esquerda
  int difvep = 0;

  //viriável para o calculo da diferença entra a leitura com a cor verde e com a cor vermelha do lado da direita
  int difvdm = 0;

  //viriável para o calculo da diferença entra a leitura com a cor verde e com a cor vermelha do lado da esquerda
  int difvem = 0;

  //viriável para o calculo da diferença entra a leitura com a cor verde e com a cor vermelha do lado da direita
  int difvde = 0;

  //viriável para o calculo da diferença entra a leitura com a cor verde e com a cor vermelha do lado da esquerda
  int difved = 0;

  //__________ _________________ ____________________ __________ ___________

  difvdp = rgbldrdp.cor('G') - rgbldrdp.cor('R');//Realiza o calculo da diferença entre a cor Verde e a vermelha do sensor direita ponta
  difvep = rgbldrep.cor('G') - rgbldrep.cor('R');//Realiza o calculo da diferença entre a cor Verde e a vermelha do sensor esquerda ponta

  difvdm = rgbldrdm.cor('G') - rgbldrdm.cor('R');//Realiza o calculo da diferença entre a cor Verde e a vermelha do sensor da direita ponta
  difvem = rgbldrem.cor('G') - rgbldrem.cor('R');//Realiza o calculo da diferença entre a cor Verde e a vermelha do sensor da esquerda ponta

  difvde = rgbldrde.cor('G') - rgbldrde.cor('R');//Realiza o calculo da diferença entre a cor Verde e a vermelha do sensor da direita ponta
  difved = rgbldred.cor('G') - rgbldred.cor('R');//Realiza o calculo da diferença entre a cor Verde e a vermelha do sensor da esquerda ponta



  /*Verificação com o ldr direita esquerda*/
  if (difvde <= 55) {
    /*Caso a diferença seja menor do que 50 o robô não identificou verde e sim
       branco ou preto pois a diferença entra a cor verde(RGB) e vermelha(RGB) quando ele
       realiza as leituras no VERDE é sempre maior que 50 */
  }


  else if (rgbldrde.cor('R') > rgbldrde.cor('G') && rgbldrde.cor('R') > rgbldrde.cor('B')) {
    /*Se a diferença for maior que 50 e a leitura com a cor verde for
      maior que a leitura com a cor vermelha e azul é caracterizado
      a cor verde*/
    vermelhodir = true;
    digitalWrite(lede, LOW);
    digitalWrite(ledd, HIGH);
    digitalWrite(ledc, HIGH);
    //delay(500);
  }

  else {
    /*Caso não tenha identificado nenhuma das anteriores é alguma
       outra cor */
  }

  //_________________________________________________________________________________
  //_________________________________________________________________________________
  //_________________________________________________________________________________
  //_________________________________________________________________________________
  //_________________________________________________________________________________



  /*Verificação com o ldr direita meio*/
  if (difvdm <= 55) {
    /*Caso a diferença seja menor do que 50 o robô não identificou verde e sim
       branco ou preto pois a diferença entra a cor verde(RGB) e vermelha(RGB) quando ele
       realiza as leituras no VERDE é sempre maior que 50 */
  }


  else if (rgbldrdm.cor('R') > rgbldrdm.cor('G') && rgbldrdm.cor('R') > rgbldrdm.cor('B')) {
    /*Se a diferença for maior que 50 e a leitura com a cor verde for
      maior que a leitura com a cor vermelha e azul é caracterizado
      a cor verde*/
    vermelhodir = true;
    digitalWrite(lede, LOW);
    digitalWrite(ledd, HIGH);
    digitalWrite(ledc, HIGH);
    //delay(500);
  }

  else {
    /*Caso não tenha identificado nenhuma das anteriores é alguma
       outra cor */
  }

  //_________________________________________________________________________________
  //_________________________________________________________________________________
  //_________________________________________________________________________________
  //_________________________________________________________________________________
  //_________________________________________________________________________________

  /*Verificação do ldr direita ponta*/
  if (difvdp <= 55) {
    /*Caso a diferença seja menor do que 50 o robô não identificou verde e sim
       branco ou preto pois a diferença entra a cor verde(RGB) e vermelha(RGB) quando ele
       realiza as leituras no VERDE é sempre maior que 50 */
  }


  else if (rgbldrdp.cor('R') > rgbldrdp.cor('G') && rgbldrdp.cor('R') > rgbldrdp.cor('B')) {
    /*Se a diferença for maior que 50 e a leitura com a cor verde for
      maior que a leitura com a cor vermelha e azul é caracterizado
      a cor verde*/
    vermelhodir = true;
    digitalWrite(lede, LOW);
    digitalWrite(ledd, HIGH);
    digitalWrite(ledc, HIGH);
    //delay(500);
  }
  else {
    /*Caso não tenha identificado nenhuma das anteriores é alguma
       outra cor */
  }

  //_________________________________________________________________________________
  //_________________________________________________________________________________
  //_________________________________________________________________________________
  //_________________________________________________________________________________
  //_________________________________________________________________________________
  //}//FIM VERIFICACAO DIREITA

  //_________________________________________________________________________________
  //_________________________________________________________________________________
  //_________________________________________________________________________________
  //_________________________________________________________________________________
  //_________________________________________________________________________________
  //_________________________________________________________________________________

  /*Verificação com o ldr esquerda direita*/
  if (difved <= 55) {
    /*Caso a diferença seja menor do que 50 o robô não identificou verde e sim
       branco ou preto pois a diferença entra a cor verde(RGB) e vermelha(RGB) quando ele
       realiza as leituras no VERDE é sempre maior que 50 */
  }


  else if (rgbldred.cor('R') > rgbldred.cor('G') && rgbldred.cor('R') > rgbldred.cor('B')) {
    /*Se a diferença for maior que 50 e a leitura com a cor verde for
      maior que a leitura com a cor vermelha e azul é caracterizado
      a cor verde*/
    vermelhoesq = true;
    digitalWrite(lede, LOW);
    digitalWrite(ledd, HIGH);
    digitalWrite(ledc, HIGH);
    //delay(500);
  }

  else {
    /*Caso não tenha identificado nenhuma das anteriores é alguma
       outra cor */
  }

  //_________________________________________________________________________________
  //_________________________________________________________________________________
  //_________________________________________________________________________________
  //_________________________________________________________________________________
  //_________________________________________________________________________________
  /*Verificação do ldr da esquerda meio*/
  if (difvem <= 55) {
    /*Caso a diferença seja menor do que 50 o robô não identificou verde e sim
      branco ou preto pois a diferença entra a cor verde(RGB) e vermelha(RGB) quando ele
      realiza as leituras no VERDE é sempre maior que 50 */
    //delay(500);
  }

  else if (rgbldrem.cor('R') > rgbldrem.cor('G') && rgbldrem.cor('R') > rgbldrem.cor('B')) {
    /*Se a diferença for maior que 50 e a leitura com a cor verde for
      maior que a leitura com a cor vermelha e azul é caracterizado
      a cor verde*/
    vermelhoesq = true;
    digitalWrite(lede, HIGH);
    digitalWrite(ledd, LOW);
    digitalWrite(ledc, HIGH);
    //delay(500);
  }
  else {
    /*Caso não tenha identificado nenhuma das anteriores é alguma
      outra cor */
    //delay(500);
  }

  //__________________________________________________________________________
  //__________________________________________________________________________
  //__________________________________________________________________________
  //__________________________________________________________________________
  //__________________________________________________________________________

  /*VERIFICAÇÃO COM O LDR ESQUERDA PONTA*/
  if (difvep <= 55) {
    /*Caso a diferença seja menor do que 50 o robô não identificou verde e sim
      branco ou preto pois a diferença entra a cor verde(RGB) e vermelha(RGB) quando ele
      realiza as leituras no VERDE é sempre maior que 50 */
    //delay(500);
  }

  else if (rgbldrep.cor('R') > rgbldrep.cor('G') && rgbldrep.cor('R') > rgbldrep.cor('B')) {
    /*Se a diferença for maior que 50 e a leitura com a cor verde for
      maior que a leitura com a cor vermelha e azul é caracterizado
      a cor verde*/
    //verdeesq = true;
    digitalWrite(lede, HIGH);
    digitalWrite(ledd, LOW);
    digitalWrite(ledc, HIGH);
    //delay(500);
  }
  else {
    /*Caso não tenha identificado nenhuma das anteriores é alguma
      outra cor */
    //delay(500);
  }

  //__________________________________________________________________________
  //__________________________________________________________________________
  //__________________________________________________________________________
  //__________________________________________________________________________
  //__________________________________________________________________________

  //DISPLAYRGB();

  //while (digitalRead(switchtras) == 0) {
  //}
  //delay(500);

  //return retorno;






}//FIM IDCORES


void TESTERGB () {//INICIO TESTERGB
  Serial.print("DER: ");
  Serial.println(rgbldrde.cor('R'));

  Serial.print("DEG: ");
  Serial.println(rgbldrde.cor('G'));

  Serial.print("DEB: ");
  Serial.println(rgbldrde.cor('B'));

  Serial.println("___________________________________________________");

  Serial.print("DMR: ");
  Serial.println(rgbldrdm.cor('R'));

  Serial.print("DMG: ");
  Serial.println(rgbldrdm.cor('G'));

  Serial.print("DMB: ");
  Serial.println(rgbldrdm.cor('B'));

  Serial.println("___________________________________________________");

  Serial.print("DPR: ");
  Serial.println(rgbldrdp.cor('R'));

  Serial.print("DPG: ");
  Serial.println(rgbldrdp.cor('G'));

  Serial.print("DPB: ");
  Serial.println(rgbldrdp.cor('B'));

  Serial.println("____________________________________________________");

  Serial.print("EDR: ");
  Serial.println(rgbldred.cor('R'));

  Serial.print("EDG: ");
  Serial.println(rgbldred.cor('G'));

  Serial.print("EDB: ");
  Serial.println(rgbldred.cor('B'));

  Serial.println("____________________________________________________");

  Serial.print("EMR: ");
  Serial.println(rgbldrem.cor('R'));

  Serial.print("EMG: ");
  Serial.println(rgbldrem.cor('G'));

  Serial.print("EMB: ");
  Serial.println(rgbldrem.cor('B'));

  Serial.println("___________________________________________________");

  Serial.print("EPR: ");
  Serial.println(rgbldrep.cor('R'));

  Serial.print("EPG: ");
  Serial.println(rgbldrep.cor('G'));

  Serial.print("EPB: ");
  Serial.println(rgbldrep.cor('B'));

  Serial.println("____________________________________________________");
}//FIM TESTERGB

void CALIBRAGEM() {//INICIO CALIBRAGEM
  digitalWrite(ledrgb[0], LOW);
  digitalWrite(ledrgb[1], LOW);
  digitalWrite(ledrgb[2], LOW);
  Serial.println("Calibrando Branco");
  display.clearDisplay();
  ESCREVE("BRANCO", 8, 8, 2);
  ESCREVE("Switcht P/", 15, 32, 1);
  ESCREVE("Calibrar", 15, 40, 1);
  while (digitalRead(switchtras) == 0) {
  }
  delay(500);
  display.clearDisplay();
  ESCREVE("CALIBRANDO", 12, 12, 1);
  ESCREVE("BRANCO", 22, 22, 1);
  for (byte i = 0; i <= 2; i++) {
    digitalWrite(ledrgb[i], HIGH);
    delay(1000);

    LEITURA_MULT_A(pldrdp);
    rgbldrdp.calibra_b(i);
    LEITURA_MULT_A(pldrdm);
    rgbldrdm.calibra_b(i);
    LEITURA_MULT_A(pldrde);
    rgbldrde.calibra_b(i);

    LEITURA_MULT_A(pldred);
    rgbldred.calibra_b(i);
    LEITURA_MULT_A(pldrem);
    rgbldrem.calibra_b(i);
    LEITURA_MULT_A(pldrep);
    rgbldrep.calibra_b(i);

    digitalWrite(ledrgb[i], LOW);
    delay(1000);
  }//fim do for

  display.clearDisplay();
  ESCREVE("BRANCO", 25, 12, 1);
  ESCREVE("CALIBRADO", 15, 22, 1);
  delay(1000);
  display.clearDisplay();
  ESCREVE("PRETO", 14, 8, 2);
  ESCREVE("Switcht P/", 15, 32, 1);
  ESCREVE("Calibrar", 15, 40, 1);

  Serial.println("Branco Calibrado");
  Serial.println("Calibrando Preto");
  while (digitalRead(switchtras) == 0) {

  }
  delay(1000);
  display.clearDisplay();
  ESCREVE("CALIBRANDO", 12, 12, 1);
  ESCREVE("PRETO", 25, 22, 1);
  for (byte i = 0; i <= 2; i++) {
    digitalWrite(ledrgb[i], HIGH);
    delay(1000);
    LEITURA_MULT_A(pldrdp);
    rgbldrdp.calibra_p(i);
    LEITURA_MULT_A(pldrdm);
    rgbldrdm.calibra_p(i);
    LEITURA_MULT_A(pldrde);
    rgbldrde.calibra_p(i);

    LEITURA_MULT_A(pldred);
    rgbldred.calibra_p(i);
    LEITURA_MULT_A(pldrem);
    rgbldrem.calibra_p(i);
    LEITURA_MULT_A(pldrep);
    rgbldrep.calibra_p(i);

    digitalWrite(ledrgb[i], LOW);
    delay(1000);
  }// fim do for
  display.clearDisplay();
  ESCREVE("Sensores", 18, 12, 1);
  ESCREVE("Calibrados", 13, 22, 1);
  delay(1500);
  Serial.println("Preto Calibrado");
  Serial.println("Sensor Calibrado");
}//FIM CALIBRAGEM

//______________________________________________________ FUNÇÕES PARA SENSOR DE DISTANCIA _____________________________________________________________________________
void ATUALIZADISTANCIAS() {
  /*Essa função retorna em CM quebrados (ex: 12,5cm) a distância que o sensor leu*/
  gydistft = gyfrente.dist_cm();
  gydistd = gydireita.dist_cm();
  gydiste = gyesquerda.dist_cm();
}


void ATUALIZAULTRAS() {
  lultrad = ultraD.distancia();
  lultrae = ultraE.distancia();
}

//___________________________________________________________ FUNÇÕES PARA GIROSCÓPIO _________________________________________________________________________________
void ATUALIZAGIRO() {

  sensors_event_t orientationData;
  bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);

  eixox = orientationData.orientation.x;
  eixoy = orientationData.orientation.y;
  eixoz = orientationData.orientation.z;

  //digitalWrite(luzD, HIGH);
  //display.clearDisplay();
  //ESCREVE("Giro: ", 0, 10, 1);
  //ESCREVEFLOAT(eixox, 30, 10, 1);

  while (eixox <= 0 && millis() > 10000) {
    PARAR(100);
    digitalWrite(luzD, HIGH);
    display.clearDisplay();
    ESCREVE("Eixo x <= 0: ", 0, 10, 1);
    ESCREVEFLOAT(eixox, 0, 30, 1);
    
    bno.begin();
    delay(100);

    //sensors_event_t orientationData;
    bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);

    eixox = orientationData.orientation.x;
    eixoy = orientationData.orientation.y;
    eixoz = orientationData.orientation.z;

    if (eixox > 0) {
      digitalWrite(luzD, HIGH);
      display.clearDisplay();
      ESCREVE("Eixo x < 0: ", 0, 10, 1);
      ESCREVEFLOAT(eixox, 0, 30, 1);
      sensors_event_t orientationData;
      bno.getEvent(&orientationData, Adafruit_BNO055::VECTOR_EULER);
    }

    //ESCREVEFLOAT(eixox, 0, 30, 1);

  }

  //digitalWrite(luzD, LOW);
  //display.clearDisplay();
}

void RAMPA() {
  //subida
  tempo = millis();
  ATUALIZAGIRO();
  if (eixoz >= 12) {
    PARAR(200);
    MOVIMENTO(60, 'F', 'N', 200);
    PARAR(200);
    if (eixoz >= 12) {
      ATUALIZAGIRO();
      MOVESERVO ('S', 100, 600);
      PARAR(200);
      tempo = millis();
      tempo2 = millis();
      while ((tempo2 - tempo) < 1500) {
        ALINHAMENTORAMPA();
        tempo2 = millis();
      }

      PARAR(1000);

      //CURVADIR(0, 80, 50);

      //PARAR(1000);


      //delay(1000);

      MOVIMENTO(70, 'F', 'N', 600);

      PARAR(1000);

      MOVESERVO ('S', 80, 400);

      MOVESERVO ('S', 80, 400);

      CURVADIR(0, 80, 80);

      MOVIMENTO(60, 'F', 'N', 200);

      PARAR(1000);
    }
  }//fim do if



  /*SOBE A GARRA
    MOVESERVO ('S', 80, 400);
    delay(1000);

    MOVIMENTO(60, 'F', 'N', 1000);
    PARAR(100);

    MOVIMENTO(50, 'T', 'N', 400);
    PARAR(100);
    CURVAESQ(0, 80, 170);
    PARAR(100);

    //desce a garra
    MOVESERVO ('S', 100, 600);
    delay(300);

    MOVIMENTO(60, 'T', 'N', 400);
    PARAR(100);

    inclinacao = 3;

    //inclinacao = 2;
    }

    //IDENTIFICAÇÃO DE DESCIDA DE RAMPA
    else if ((inclinacao == 2 && gydistce >= 10.0) || (inclinacao == 2 && gydistcd >= 10.5)) {
    MOVIMENTO(60, 'T', 'N', 300);
    PARAR(100);
    float gyauxd = gydistcd;
    float gyauxe = gydistce;
    ATUALIZAGY2();
    /*display.clearDisplay();
    ESCREVE("ChD: ", 0, 0, 1);
    ESCREVEFLOAT(gydistcd, 0, 9, 2);
    ESCREVE("ChE: ", 0, 25, 1);
    ESCREVEFLOAT(gydistce, 0, 34, 2);

    while (digitalRead(switchtras) == 0) {
    }
    delay(500);
    while (digitalRead(switchtras) == 0) {
    DISPLAYGY('C');
    delay(200);
    }
    //MOVIMENTO(50, 'T', 'N', 300);
    //PARAR(1000);
    /*DISPLAYGY('C');
    PARAR(5000);
    while (digitalRead(switchtras) == 0) {
    DISPLAYGY('C');
    delay(100);
    }
    delay(1000);
    if (gydistce >= gyauxe || gydistcd >= gyauxd) {
    /*while (digitalRead(switchtras) == 0) {
      DISPLAYGY('C');
      delay(100);
      }
    MOVIMENTO(50, 'T', 'N', 400);
    PARAR(100);
    CURVAESQ(0, 80, 170);
    PARAR(100);

    //desce a garra
    MOVESERVO ('S', 100, 600);
    delay(300);
    inclinacao = 3;
    }
    }
    else if (inclinacao == 3 && eixoz > 20) {
    //PARADA DO ROBÔ JÁ NA RAMPA
    analogWrite( MDT, 0);
    analogWrite( MET, 0);
    analogWrite( MDF, 50 * 2.54);
    analogWrite( MEF, 40 * 2.54);
    delay(1000);
    //CURVAESQ(0, 80, 5);

    /*analogWrite( MDT, 0);
    analogWrite( MET, 0);
    analogWrite( MDF, 100 * 2.54);
    analogWrite( MEF, 82 * 2.54);
    delay(500);

    analogWrite( MDT, 0);
    analogWrite( MET, 0);
    analogWrite( MDF, 50 * 2.54);
    analogWrite( MEF, 40 * 2.54);
    delay(1000);
    inclinacao = 4;
    }
    else if (inclinacao == 4 && eixoz <= 15) {
    PARAR(1000);
    MOVESERVO ('S', 80, 400);
    PARAR(1000);
    CURVAESQ(0, 80, 170);
    PARAR(100);
    //delay(2000);
    inclinacao = 0;
    }


    /*Serial.print("TF: ");
    Serial.print(millis() - tempo);
    Serial.print(" Frente: ");
    Serial.print(gydistft);
    Serial.print(" CD: ");
    Serial.print(gydistcd);
    Serial.print(" CE: ");
    Serial.print(gydistce);
    Serial.print(" LD: ");
    Serial.print(gydistd);
    Serial.print(" LE: ");
    Serial.println(gydiste);*/


}//fim RAMPA

//___________________________________________________________ FUNÇÕES PARA TIMER _________________________________________________________________________________
void HORARIO() {
  //Função usada para atualizar o valor das variaveis do timer
  //t = rtc.getTime(); //Salva o tempo da rodada

  // = t.min; //Salva na variável apenas os minutos da rodada
  //segundos = t.sec;  //Salva na variável apenas os segundos da rodada
  //horas = t.hour;
}

//______________________________________________________ FUNÇÕES PARA SENSOR DE TENSÃO _____________________________________________________________________________
void CHECATENSAO() {


  te = analogRead(tensao);
  te = te * 25;
  te = te / 1023;

  //Serial.println(t);
  ESCREVEFLOAT(te, 12, 0, 2);
  ESCREVE("volts", 12, 16, 2);
}

//______________________________________________________ FUNÇÕES PARA USO DO MULTIPLEXADOR _____________________________________________________________________________
byte LEITURA_MULT_D (byte x) {
  digitalWrite(S0, bitRead(x, 0));
  digitalWrite(S1, bitRead(x, 1));
  digitalWrite(S2, bitRead(x, 2));
  digitalWrite(S3, bitRead(x, 3));

  return digitalRead(multiplexador);
}

int LEITURA_MULT_A (byte x) {
  digitalWrite(S0, bitRead(x, 0));
  digitalWrite(S1, bitRead(x, 1));
  digitalWrite(S2, bitRead(x, 2));
  digitalWrite(S3, bitRead(x, 3));

  return analogRead(multiplexador);
}
