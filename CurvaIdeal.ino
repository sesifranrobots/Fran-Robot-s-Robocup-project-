void CURVAANGULO (byte forcamov, char direcao) {
  /*Essa função permite colocar o robô no ângulo desejado, similar ao funcionamento de um servo motor,
    em que é possível definir a posição que o servo deve ficar*/

  double anguloideal = 0;
  double ajusteangulo = 0;

  ATUALIZAGIRO();

  //while (eixox < 0) {
    //MOVIMENTO(80, 'D', 'N', 50);
    //ATUALIZAGIRO();
  //}

  PARAR(200);

  //ATUALIZAGIRO();

  //próximo de 0
  if (eixox > 315 || eixox <= 45) {
    if (eixox > 315 && eixox < 360) {
      ajusteangulo = 360 - eixox;
    }
    else {
      ajusteangulo = 0 - eixox;
    }
    if (direcao == 'E') {
      anguloideal = 286;
    }
    else {
      anguloideal = 74;
    }
  }
  //próximo de 90
  else if (eixox > 45 && eixox <= 135) {
    ajusteangulo = 90 - eixox;
    if (direcao == 'E') {
      anguloideal = 16;
    }
    else {
      anguloideal = 164;
    }
  }

  //próximo de 180
  else if (eixox > 135 && eixox <= 225) {
    ajusteangulo = 180 - eixox;
    if (direcao == 'E') {
      anguloideal = 106;
    }
    else {
      anguloideal = 254;
    }
  }

  //próximo de 270
  else if (eixox > 225 && eixox <= 315) {
    ajusteangulo = 270 - eixox;
    if (direcao == 'E') {
      anguloideal = 196;
    }
    else {
      anguloideal = 344;
    }
  }

  //Cálculos para realização da curva
  double calculo1 = anguloideal - eixox; //Subtrai o ângulo que o robô está com o ângulo que quer manda-lo
  double calculo2 = 0; //Variável para realização das curvas quando o robô vai passar pelo ângulo 0;

  /*digitalWrite(luzD, HIGH);
    display.clearDisplay();
    ESCREVEFLOAT(eixox, 0, 10, 1);
    //ESCREVEFLOAT(eixoaux, 0, 10, 1);
    ESCREVEFLOAT(anguloideal, 0, 30, 1);
    display.clearDisplay();
    digitalWrite(luzD, LOW);

    delay(10000);*/

  if (calculo1 >= 180)
  {
    /*Se o primeiro cálculo for maior que 180, o robô vai fazer a curva para a esquerda. Durante a movimentação
      o robô bai passar pelo ângulo 0, por isso é necessário o primeiro While de movimentação. Depois do robô passar
      pelo ângulo 0, ele faz a curva até atingir o ângulo desejado. Fazendo a curva para a esquerda nessa situação
      ele economiza mais tempo, do que se fazendo pela direita.*/
    calculo2 = eixox + 2; //Soma +2 no ângulo que o robô está
    while (eixox >= 0 && eixox <= calculo2)
    {
      /*Enquanto o robô não passar pelo o ângulo 0, ele se movimenta para a esquerda*/
      MOVIMENTO(forcamov, 'E', 'N', 0);
      ATUALIZAGIRO();
    }
    while (eixox > anguloideal)
    {
      /*Enquanto o robô não chegar no ângulo desejado, ele se movimenta para a esquerda*/
      MOVIMENTO(forcamov, 'E', 'N', 0);
      ATUALIZAGIRO();
    }
  }
  else if (calculo1 >= 0 && calculo1 < 180)
  {
    /*Se o cálculo der um número entre 0 e 180, o robô faz a curva para a direita até atingir
      o ângulo desejado. Dessa maneira ele economiza mais tempo do que fazendo a curva para a esquerda*/
    while (eixox < anguloideal)
    {
      /*Enquanto o robô não atingir o ângulo desejado, ele se movimenta para a direita*/
      MOVIMENTO(forcamov, 'D', 'N', 0);
      ATUALIZAGIRO();
    }
  }
  else if (calculo1 >= (-180) && calculo1 < 0)
  {
    /*Se o cálculo der um número entre -180 e 0, robô se movimenta para a esquerda até atingir
      o ângulo desejado. Dessa maneira ele economiza mais tempo doque fazendo a curva para a direita*/
    if (anguloideal == 0)
    {
      /*Se o ângulo que o robô deve parar é o 0 o robô faz a curva para a esquerda até atingi-lo*/
      calculo2 = eixox + 2; //Calculo para realização da curva
      while (eixox >= 0 && eixox <= calculo2)
      {
        /*Enquanto o robô não atingir o ângulo desejado, ele se movimenta para a esquerda*/
        MOVIMENTO(forcamov, 'E', 'N', 0);
        ATUALIZAGIRO();
      }
    }
    else
    {
      /*Se o robô tiver que atingir qualquer outro ângulo o robô faz a curva para a esquerda*/
      while (eixox > anguloideal)
      {
        /*Enquanto o robô não atingir o ângulo desejado, ele se movimenta para a esquerda*/
        MOVIMENTO(forcamov, 'E', 'N', 0);
        ATUALIZAGIRO();
      }
    }
  }
  else if (calculo1 < (-180))
  {
    /*Se o primeiro cálculo for menor que -180, o robô vai fazer a curva para a direita. Durante a movimentação
      o robô bai passar pelo ângulo 0, por isso é necessário o primeiro While de movimentação. Depois do robô passar
      pelo ângulo 0, ele faz a curva até atingir o ângulo desejado. Fazendo a curva para a direita nessa situação
      ele economiza mais tempo, do que se fazendo para a esquerda.*/

    calculo2 = eixox - 2; //Subtrai 2 do ângulo que o robô está

    while (eixox >= calculo2 && eixox <= 360)
    {
      /*Enquanto o robô não passar pelo ângulo 0, ele se movimenta para a direita*/
      MOVIMENTO(forcamov, 'D', 'N', 0);
      ATUALIZAGIRO();
    }
    while (eixox < anguloideal)
    {
      /*Depois de passar pelo ângulo 0, ele se movimenta para a direita até atingir o ângulo desejado*/
      MOVIMENTO(forcamov, 'D', 'N', 0);
      ATUALIZAGIRO();
    }
  }

  PARAR(200);

  /*if (ajusteangulo < 0) {
    CURVAESQ(0, 80, (ajusteangulo * -1));
    }
    else {
    CURVADIR(0, 80, ajusteangulo);
    }

    PARAR(200);*/
}
