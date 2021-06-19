void ESCREVE(char Str4[], byte coluna, byte linha, byte fonte) {

  display.setTextSize(fonte);
  display.setTextColor(BLACK);
  display.setCursor(((display.width() - 84 ) + coluna), ((display.height() - 48) + linha));
  display.println(Str4);
  display.display();

}

void ESCREVEBYTE(long x, byte coluna, byte linha, byte fonte) {

  display.setTextSize(fonte);
  display.setTextColor(BLACK);
  display.setCursor(((display.width() - 84 ) + coluna), ((display.height() - 48) + linha));
  display.println(x);
  display.display();

}

void ESCREVEFLOAT(float x, byte coluna, byte linha, byte fonte) {

  display.setTextSize(fonte);
  display.setTextColor(BLACK);
  display.setCursor(((display.width() - 84 ) + coluna), ((display.height() - 48) + linha));
  display.println(x);
  display.display();

}

//______________________________________________________ FUNÇÕES PARA LEITURA DE SENSORES __________________________________________________________________________
void DISPLAYSWITCH() {
  display.clearDisplay();
  ESCREVE("SG:", 0, 0, 1);
  ESCREVEBYTE(LEITURA_MULT_D(switchgarra), 20, 0, 1);
  ESCREVE("SF:", 0, 12, 1);
  ESCREVEBYTE(LEITURA_MULT_D(switchfrente), 20, 12, 1);
  ESCREVE("SP:", 35, 0, 1);
  ESCREVEBYTE(LEITURA_MULT_D(switchparede), 55, 0, 1);
  ESCREVE("ST:", 35, 12, 1);
  ESCREVEBYTE(digitalRead(switchtras), 55, 12, 1);
}

void DISPLAYGIRO() {
  display.clearDisplay();
  ESCREVE("X:", 0, 0, 1);
  ESCREVEFLOAT(eixox, 10, 0, 1);
  ESCREVE("Y:", 0, 10, 1);
  ESCREVEFLOAT(eixoy, 10, 10, 1);
  ESCREVE("Z:", 0, 20, 1);
  ESCREVEFLOAT(eixoz, 10, 20, 1);
}

void DISPLAYGY(char gy) {
  display.clearDisplay();
  switch (gy) {
    case 'F':
      ESCREVE("E", 0, 5, 2);
      ESCREVEBYTE(ultraE.distancia(), 0, 27, 1);

      ESCREVE("M", 30, 5, 2);
      ESCREVEBYTE(gyfrente.dist_cm(), 30, 27, 1);
      

      ESCREVE("D", 65, 5, 2);
      ESCREVEBYTE(ultraD.distancia(), 65, 27, 1);
      break;
  
    case 'L':
      ESCREVE("Dir:", 0, 0, 1);
      ESCREVEBYTE(gydireita.dist_cm(), 0, 9, 2);
      ESCREVE("Esq:", 0, 25, 1);
      ESCREVEBYTE(gyesquerda.dist_cm(), 0, 34, 2);
      break;
  }
}

void DISPLAYREF(char placa) {
  switch (placa) { //inicio switch placa

    case 'f'://inicio caso f


      ESCREVE("E:", 0, 0, 1);
      ESCREVEBYTE(analogRead(ep), 15, 0, 1);
      ESCREVEBYTE(analogRead(em), 40, 0, 1);
      ESCREVEBYTE(analogRead(ed), 65, 0, 1);

      ESCREVE("C:", 0, 10, 1);
      ESCREVEBYTE(analogRead(ce), 15, 10, 1);
      ESCREVEBYTE(analogRead(c), 40, 10, 1);
      ESCREVEBYTE(analogRead(cd), 65, 10, 1);

      ESCREVE("D:", 0, 20, 1);
      ESCREVEBYTE(analogRead(dp), 15, 20, 1);
      ESCREVEBYTE(analogRead(dm), 40, 20, 1);
      ESCREVEBYTE(analogRead(de), 65, 20, 1);


      break;//fim caso f
    //==============================================================
    case 't'://inicio caso t
      ESCREVE("E:", 0, 0, 1);
      ESCREVEBYTE(analogRead(ept), 30, 0, 1);
      ESCREVEBYTE(analogRead(emt), 55, 0, 1);

      ESCREVE("D:", 0, 10, 1);
      ESCREVEBYTE(analogRead(dmt), 30, 10, 1);
      ESCREVEBYTE(analogRead(dpt), 55, 10, 1);

      break;//fim caso t
    //==============================================================

    case 'l'://inicio caso t
      ESCREVE("E:", 0, 0, 1);
      ESCREVEBYTE(LEITURA_MULT_A(pldrep), 15, 0, 1);
      ESCREVEBYTE(LEITURA_MULT_A(pldrem), 35, 8, 1);
      ESCREVEBYTE(LEITURA_MULT_A(pldred), 55, 0, 1);

      ESCREVE("D:", 0, 16, 1);
      ESCREVEBYTE(LEITURA_MULT_A(pldrde), 15, 16, 1);
      ESCREVEBYTE(LEITURA_MULT_A(pldrdm), 35, 24, 1);
      ESCREVEBYTE(LEITURA_MULT_A(pldrdp), 55, 16, 1);

      break;//fim caso t


    case 'p': // ldrs da ponta
      ESCREVE("E:", 0, 0, 1);
      ESCREVEBYTE(rgbldrep.cor('R'), 10, 0, 1);
      ESCREVEBYTE(rgbldrep.cor('G'), 36, 0, 1);
      ESCREVEBYTE(rgbldrep.cor('B'), 60, 0, 1);

      ESCREVE("D:", 0, 16, 1);
      ESCREVEBYTE(rgbldrdp.cor('R'), 10, 16, 1);
      ESCREVEBYTE(rgbldrdp.cor('G'), 36, 16, 1);
      ESCREVEBYTE(rgbldrdp.cor('B'), 60, 16, 1);
      break;

    case 'm': // ldrs do meio
      ESCREVE("E:", 0, 0, 1);
      ESCREVEBYTE(rgbldrem.cor('R'), 10, 0, 1);
      ESCREVEBYTE(rgbldrem.cor('G'), 36, 0, 1);
      ESCREVEBYTE(rgbldrem.cor('B'), 60, 0, 1);

      ESCREVE("D:", 0, 16, 1);
      ESCREVEBYTE(rgbldrdm.cor('R'), 10, 16, 1);
      ESCREVEBYTE(rgbldrdm.cor('G'), 36, 16, 1);
      ESCREVEBYTE(rgbldrdm.cor('B'), 60, 16, 1);
      break;

    case 'i': // ldrs próximos a linha
      ESCREVE("E:", 0, 0, 1);
      ESCREVEBYTE(rgbldred.cor('R'), 10, 0, 1);
      ESCREVEBYTE(rgbldred.cor('G'), 36, 0, 1);
      ESCREVEBYTE(rgbldred.cor('B'), 60, 0, 1);

      ESCREVE("D:", 0, 16, 1);
      ESCREVEBYTE(rgbldrde.cor('R'), 10, 16, 1);
      ESCREVEBYTE(rgbldrde.cor('G'), 36, 16, 1);
      ESCREVEBYTE(rgbldrde.cor('B'), 60, 16, 1);
      break;

  }//fim switch placa
}


//______________________________________________________ FUNÇÕES PARA SINALIZAÇãO COM LEDS __________________________________________________________________________
void LEDDIR () {
  /*Função para Piscar o LED da Direita*/
  digitalWrite(ledd, HIGH); //Ascende o Led
  delay(50); //Espera 50 milissgundos
  digitalWrite(ledd, LOW); //Apaga o LED
  delay(50); //Espera 50 milissegundos
}

void LEDESQ () {
  //função para piscar led esquerda
  digitalWrite(lede, HIGH); //Ascende o Led
  delay(50); //Espera 50 milissegundos
  digitalWrite(lede, LOW); //Apaga o LED
  delay(50); //Espera 50 milissegundos
}

void LEDCEN () {
  //função para piscar led central
  digitalWrite(ledc, HIGH); //Ascende o Led
  delay(50); //Espera 50 milissegundos
  digitalWrite(ledc, LOW); //Apaga o LED
  delay(50); //Espera 50 milissegundos
}

//______________________________________________________ FUNÇÕES PARA COMUNIÇÃO SERIAL __________________________________________________________________________
void TESTEREF() {
  /*Função para mostrar as leituras com os sensores da placa de refletância no Serial*/

  /*Mostra no Serial o valor lido por cada um dos sensores*/
  Serial.print("Direita ponta: ");
  Serial.println(ldp);
  Serial.print("Direita meio: ");
  Serial.println(ldm);
  Serial.print("Direita Esquerda: ");
  Serial.println(lde);
  Serial.print("Central Direita: ");
  Serial.println(lcd);
  Serial.print("Central: ");
  Serial.println(lc);
  Serial.print("Central Esquerda: ");
  Serial.println(lce);
  Serial.print("Esquerda Direita: ");
  Serial.println(led);
  Serial.print("Esquerda meio: ");
  Serial.println(lem);
  Serial.print("Esquerda ponta: ");
  Serial.println(lep);

  /*Serial.print("LDRE Esquerda: ");
    Serial.println(ldrep);
    Serial.print("LDRE Meio: ");
    Serial.println(ldrem);
    Serial.print("LDRD Meio: ");
    Serial.println(ldrdm);
    Serial.print("LDRD Direita: ");
    Serial.println(ldrdp);
    Serial.println("--------------------------");
    delay(1000);*/
}
