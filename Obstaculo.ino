void IDOBSTACULO() {


  //ATUALIZADISTANCIAS();
  //if (lultrad < 15 || lultrae < 15) {
  if (gyfrente.dist_cm() < 15) {

    PARAR(200);

    if (gyfrente.dist_cm() < 15 /*&& lultrad < 15 && lultrae < 15*/) {

      PARAR(10);
      DISPLAYGY('F');
      LEDESQ();
      LEDCEN();
      LEDDIR();


      tempo = millis();
      tempo2 = millis() - tempo;

      while (LEITURA_MULT_D(switchfrente) == 0 && tempo2 < 800) {
        MOVIMENTO(50, 'F', 'N', 0);
        tempo2 = millis() - tempo;
      }
      PARAR(100);

      if (tempo2 >= 800)
      {
        return;
      }

      MOVIMENTO(60, 'T', 'N', 250);
      PARAR(400);

      //obscurva = true;
      //CURVADIR(0, 80, 95);
      //PARAR(200);
      // MOVIMENTO(50, 'T', 'N', 250);
      //PARAR(300);
      //}
      //else {
      CURVAANGULO(80, 'D');
      PARAR(300);
      // }

      DESVIOD();
    }
  }
}

void DESVIOD() {

  byte confirmadistancia = 0;
  byte verificadistancia = 0;

  ATUALIZAGIRO();//atualização das leituras do giroscópio
  eixoxaux = eixox; // valor do eixox guardado para utilização na função de alinhamento

  ATUALIZASENSORES();

  ATUALIZAGIRO();
  while (confirmadistancia == 0) {
    ALINHAGIRO(50);
    if (gyesquerda.dist_cm() > 22) {
      PARAR(400);
      if (gyesquerda.dist_cm() > 22) {
        confirmadistancia = 1;
      }
    }
  }

  confirmadistancia = 0;
  MOVIMENTO(60, 'F', 'N', 250);
  PARAR(300);


  //segunda curva (esquerda)
  if (obscurva == true) {

    CURVAESQ(0, 80, 80);
  }
  else {
    CURVAANGULO (80, 'E');
  }

  PARAR(300);

  ATUALIZAGIRO();//atualização das leituras do giroscópio
  eixoxaux = eixox; // valor do eixox guardado para utilização na função de alinhamento
  MOVIMENTO(50, 'F', 'N', 750);
  while (confirmadistancia == 0) {
    ALINHAGIRO(50);

    if (gyesquerda.dist_cm() < 18) {
      PARAR(300);
      if (gyesquerda.dist_cm() < 18)
      {
        confirmadistancia = 1;
      }
    }
  }

  ATUALIZAGIRO();//atualização das leituras do giroscópio
  eixoxaux = eixox; // valor do eixox guardado para utilização na função de alinhamento
  MOVIMENTO(50, 'F', 'N', 300);
  confirmadistancia = 0;

  while (confirmadistancia == 0) {
    ALINHAGIRO(50);

    if (gyesquerda.dist_cm() > 20) {
      PARAR(300);
      if (gyesquerda.dist_cm() > 20) {
        confirmadistancia = 1;
      }
    }
  }

  confirmadistancia = 0;

  MOVIMENTO(60, 'F', 'N', 200);
  PARAR(300);


  //terceira curva (esquerda)

  if (obscurva == true) {
    CURVAESQ(0, 80, 80);
  }
  else {
    CURVAANGULO (80, 'E');
  }

  PARAR(300);

  ATUALIZAGIRO();//atualização das leituras do giroscópio
  eixoxaux = eixox; // valor do eixox guardado para utilização na função de alinhamento

  while (confirmadistancia == 0) {
    //MOVIMENTO(60, 'F', 'N', 1);
    ALINHAGIRO(50);

    if (gyesquerda.dist_cm() < 8) {
      PARAR(300);
      if (gyesquerda.dist_cm() < 8) {
        confirmadistancia = 1;
      }
    }
  }
  confirmadistancia = 0;

  PARAR(300);

  /*if (obscurva == true) {
    MOVIMENTO(60, 'F', 'N', 70);
    }
    else {
    MOVIMENTO(60, 'F', 'N', 50);
    }*/

  //MOVIMENTO(60, 'F', 'N', 150);//75
  //PARAR(100);

  if (obscurva == true) {
    CURVADIR(0, 80, 80);
  }
  else {
    CURVAANGULO (80, 'D');
  }

  PARAR(100);

  tempo = millis();
  tempo2 = millis();

  while (digitalRead(switchtras) == 0 && tempo2 < 1000) {
    MOVIMENTO(50, 'T', 'N', 0);
    tempo2 = millis() - tempo;
  }

  //MOVIMENTO(60, 'F', 'N', 70);
  PARAR(50);

  obscurva = 0;
}
