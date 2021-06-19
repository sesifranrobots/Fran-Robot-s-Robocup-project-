void SALAEVAC() {
  ALINHAGIRO(50);

  //MOVIMENTO(50, 'F', 'N', 0);

  ATUALIZAULTRAS();

  //caso o robô já tenha identificado o triângulo ou achado a primeira parede
  if (parede > 0) {
    //atualização do sensor GY da esquerda
    gydiste = gyesquerda.dist_cm();
    gydistd = gydireita.dist_cm();
  }

  //atualização do sensor GY da frente
  //gydistft = gyfrente.dist_cm();

  //VERIFICA PAREDE
  if (lultrae < 10 && lultrad < 10) {
    PARAR(100);

    //confirmação da parede
    verificadistancia = 0;
    for (byte x = 0; x < 10; x++) {
      ATUALIZAULTRAS();
      if (lultrae < 10 && lultrad < 10) {
        verificadistancia ++;
      }
    }

    if (verificadistancia > 7) {

      display.clearDisplay();
      ESCREVE("Vitimas: ", 0, 0, 1);
      ESCREVEBYTE(qtdevitimas, 40, 0, 1);
      ESCREVE("Parede: ", 0, 10, 1);
      ESCREVEBYTE(parede, 40, 10, 1);
      ESCREVE("Triangulo: ", 0, 20, 1);
      ESCREVEBYTE(triangulo, 40, 20, 1);


      delay(5000);

      //caso esteja com vítimas
      if (qtdevitimas == 3) {
        if (parede == 2 && triangulo == 1) {
          //----------------rever essa lógica
          CURVAANGULO(80, 'E');
          //CURVAESQ(0, 80, 74);
          PARAR(200);
        }
        else if (parede == 1 && triangulo == 2) {
          CURVAANGULO(80, 'D');
          PARAR(200);
        }//fim do else if

        else if (parede == 1 && triangulo == 1) {
          parede = 2;
          CURVAANGULO(80, 'D');
          PARAR(200);
          //CURVAANGULO(80, 'D');
          CURVADIR(0, 80, 72);
          PARAR(200);
        }//fim do else if

        else if (parede == 2 && triangulo == 2) {
          parede = 1;
          CURVAANGULO(80, 'D');
          PARAR(200);
          //CURVAANGULO(80, 'D');
          CURVADIR(0, 80, 72);
          PARAR(200);
        }//fim do else if
      }// fim if if (qtdevitimas == 1)

      /*Caso o robô já esteja fazendo o percurso da sala
        curva de 180º */
      else if (parede > 0) {
        CURVAANGULO(80, 'D');
        PARAR(200);
        CURVADIR(0, 80, 72);
        //CURVAANGULO(80, 'D');
        PARAR(200);
      }

      //o robô acabou de entrar na sala de evacuação
      else {
        ATUALIZAULTRAS();
        tempo = millis();
        tempo2 = millis();
        while (lultrad < 40 && ((tempo2 - tempo) < 3000)) {
          MOVIMENTO(50, 'T', 'N', 0);
          tempo2 = millis();
          ATUALIZAULTRAS();
        }

        PARAR(200);
        //atualiza os sensores das laterais
        gydiste = gyesquerda.dist_cm();
        gydistd = gydireita.dist_cm();

        //se a entrada da for pela esquerda da sala
        if (gydiste < 20) {
          parede = 2;
          CURVAANGULO(80, 'D');
          PARAR(200);
        }
        else {
          parede = 1;
          CURVAANGULO(80, 'E');
          PARAR(200);
        }
      }//fim do else

      /*caso nao seja a hora de depoistar vítimas, o robô deve
        andar por tempo até se afastar do rumo do triângulo*/
      if (qtdevitimas < 3) {
        ATUALIZAGIRO();//atualização das leituras do giroscópio
        eixoxaux = eixox; // valor do eixox guardado para utilização na função de alinhamento
        tempo = millis();
        tempo2 = millis();
        while ((tempo2 - tempo) < 1600) {
          ALINHAGIRO(50);
          tempo2 = millis();
        }
        PARAR(200);
      }
    }//fim do if (verificadistancia > 7) {
  }// fim do if (lultrae < 10 && lultrad < 10)

  //-------------------------------------------------------------------------------
  //Verificação de Triângulo
  else if (lultrae > 105 && lultrad > 105) {
    PARAR(200);

    MOVIMENTO(50, 'F', 'N', 500);

    PARAR(200);

    //confirmação de triângulo
    verificadistancia = 0;
    for (byte x = 0; x < 10; x++) {
      gydistft = gyfrente.dist_cm();
      if (gydistft < 20) {
        verificadistancia ++;
      }
    }

    if (verificadistancia > 5) {

      display.clearDisplay();
      ESCREVE("TRIANGULO!!!", 0, 10, 1);

      //verifica se o robô acabou de entrar da sala de evacuação
      if (parede == 0) {
        MOVIMENTO(60, 'T', 'N', 700);
        PARAR(200);

        //atualiza os sensores das laterais
        gydiste = gyesquerda.dist_cm();
        gydistd = gydireita.dist_cm();

        //se a entrada da for pela esquerda da sala
        if (gydiste < 20) {
          parede = 2;
          triangulo = 2;
          CURVAANGULO(80, 'D');
          PARAR(200);
          ATUALIZAGIRO();//atualização das leituras do giroscópio
          eixoxaux = eixox; // valor do eixox guardado para utilização na função de alinhamento
          MOVIMENTO(60, 'F', 'N', 400);
          PARAR(200);
        }
        else {
          parede = 1;
          triangulo = 1;
          CURVAANGULO(80, 'E');
          PARAR(200);
          ATUALIZAGIRO();//atualização das leituras do giroscópio
          eixoxaux = eixox; // valor do eixox guardado para utilização na função de alinhamento
          MOVIMENTO(60, 'F', 'N', 400);
          PARAR(200);
        }
      }// fim do if (parede == 0)

      //----------SE O ESTIVER COM VÍTIMA VIÁVEL + KIT VÍTIMA-------
      else if (qtdevitimas == 3) {

        if (triangulo == 1) {
          MOVIMENTO(60, 'T', 'N', 200);
          PARAR(100);
          CURVAESQ(0, 80, 45);
          MOVIMENTO(60, 'F', 'N', 600);
          PARAR(100);

          MOVESERVAO(100, 500);

          MOVECACAMBA(0, 500);

          CURVAESQ(0, 80, 90);
          MOVIMENTO(60, 'T', 'N', 400);
          PARAR(100);
          delay(1000);
          MOVESERVAO(80, 500);
          MOVESERVAO(80, 500);
          MOVIMENTO(60, 'F', 'N', 200);
          PARAR(100);
          MOVIMENTO(70, 'T', 'N', 400);
          PARAR(100);
          MOVECACAMBA(100, 500);

          delay(300);

          MOVIMENTO(60, 'F', 'N', 1500);

          PARAR(10000);

          //CURVADIR(0, 80, 35);
          //CURVAANGULO(80, 'D');
        }// fim do if (qtdevitimas == 3)

        else if (triangulo == 2) {
          CURVAESQ(0, 80, 111);// curva em direção ao triângulo
          PARAR(200);
          MOVIMENTO(50, 'T', 'N', 1300);
          PARAR(200);
          CURVAESQ(0, 80, 90);
          MOVIMENTO(60, 'T', 'N', 400);
          PARAR(100);

          MOVESERVAO(100, 500);

          MOVECACAMBA(0, 500);
          delay(1000);
          MOVESERVAO(80, 500);
          MOVESERVAO(80, 500);
          MOVIMENTO(60, 'F', 'N', 200);
          PARAR(100);
          MOVIMENTO(70, 'T', 'N', 400);
          PARAR(100);
          MOVECACAMBA(100, 500);

          delay(300);

          MOVIMENTO(60, 'F', 'N', 1500);

          PARAR(10000);

          //CURVADIR(0, 80, 45);
          //CURVAANGULO(80, 'D');
        }// fim do else if (triangulo == 2)

        /*gydistft = gyfrente.dist_cm();

          tempo = millis();
          tempo2 = millis();
          while (gydistft > 13 && ((tempo2 - tempo) < 1500)) {
          MOVIMENTO(60, 'F', 'N', 0);
          gydistft = gyfrente.dist_cm();
          tempo2 = millis();
          }

          PARAR(100);

          CURVAESQ(0, 80, 35);

          PARAR(100);*/

      }//fim do if (qtdevitimas == 3) {
    }//fim do if (verificadistancia > 5) {
  }

  //verificação do verde
  else if (LEITURA_MULT_A(pldrem) > 600 || LEITURA_MULT_A(pldrdm) > 600) {
    PARAR(100);
    MOVIMENTO(60, 'T', 'N', 300);
    display.clearDisplay();
    ESCREVE("VERDE!!!", 0, 10, 1);
    PARAR(5000);
  }

  //verificação de vítimas para a esquerda
  else if (gydiste < 32 && qtdevitimas < 3 && parede > 0) {
    PARAR(200);
    LEDDIR();
    LEDESQ();
    LEDCEN();
    MOVIMENTO(50, 'T', 'N', 100); //traz contra inércia
    PARAR(400);

    //gydiste = gyesquerda.dist_cm();

    //if (gydiste < 34) {

    CURVAESQ(0, 80, 80);
    //CURVAANGULO(80, 'E');
    PARAR(200);

    ATUALIZAGIRO();//atualização das leituras do giroscópio
    eixoxaux = eixox; // valor do eixox guardado para utilização na função de alinhamento

    bool controle = false;

    //posicionamento estratégico antes de ir em direção a vítima
    MOVIMENTO(50, 'T', 'N', 300);
    PARAR(200);

    tempo = millis();
    tempo2 = millis();

    while (controle == false) {
      ALINHAGIRO(50);
      ATUALIZAULTRAS();
      gydistft = gyfrente.dist_cm();
      if (gydistft < 17 || lultrae < 17 || lultrad < 17 || (tempo2 - tempo) > 5000) {
        controle = true;
        PARAR(200);
        ESCREVE("VITIMA MESMO!!!", 0, 10, 1);
        MOVESERVAO(100, 200); // começa a descer a garra
        //delay(300);
        MOVEGARRA(180, 700, 0); // abertura da garra
        //delay(300);
        MOVESERVAO(100, 500); // finaliza a descida da garra

        MOVIMENTO(50, 'F', 'N', 350);// se aproxima da vítima
        PARAR(100);
        RESGATAVITIMA(); // captura e verifica o tipo da vítima

        MOVIMENTO(50, 'T', 'N', 350);// ré estratégica para não "esbarrar" na parede ou triângulo
        PARAR(100);

        MOVESERVAO(80, 1000); // sobe a garra

        MOVEGARRA(50, 300, 0); // desliga o servo da garra

        // retorno ao ponto inicial
        ATUALIZAULTRAS();
        gydistft = gyfrente.dist_cm();

        tempo = millis();
        tempo2 = millis();
        //while (lultrae < 40 && ((tempo2 - tempo) < 3000)) {
        while (gydistft < 40 && (tempo2 - tempo) < 3000) {
          MOVIMENTO(50, 'T', 'N', 0);
          tempo2 = millis();
          //ATUALIZAULTRAS();
          gydistft = gyfrente.dist_cm();
        }
        PARAR(100);
        MOVIMENTO(50, 'F', 'N', 300);
        PARAR(200);
        CURVAANGULO(80, 'D');
        PARAR(200);
        ATUALIZAGIRO();//atualização das leituras do giroscópio
        eixoxaux = eixox; // valor do eixox guardado para utilização na função de alinhamento
        MOVIMENTO(50, 'F', 'N', 300);
        PARAR(200);

      }
      tempo2 = millis();
    }//FIM DO WHILE
    //}// FIM DO if (gydiste < 34)
  }// FIM DO else if (gydiste < 34)

  //-----------------------------------------------------------------------------------------------
  //verificação de vítimas para a direita
  else if (gydistd < 32 && qtdevitimas < 3 && parede > 0) {
    PARAR(200);
    LEDDIR();
    LEDESQ();
    LEDCEN();
    MOVIMENTO(50, 'T', 'N', 100); //traz contra inércia
    PARAR(400);

    //gydiste = gyesquerda.dist_cm();

    //if (gydiste < 34) {

    CURVADIR(0, 80, 70);
    //CURVAANGULO(80, 'D');
    PARAR(200);

    ATUALIZAGIRO();//atualização das leituras do giroscópio
    eixoxaux = eixox; // valor do eixox guardado para utilização na função de alinhamento

    bool controle = false;

    //posicionamento estratégico antes de ir em direção a vítima
    MOVIMENTO(50, 'T', 'N', 300);
    PARAR(200);

    tempo = millis();
    tempo2 = millis();

    while (controle == false) {
      ALINHAGIRO(50);
      ATUALIZAULTRAS();
      gydistft = gyfrente.dist_cm();
      if (gydistft < 17 || lultrae < 17 || lultrad < 17 || (tempo2 - tempo) > 5000) {
        controle = true;
        PARAR(200);
        ESCREVE("VITIMA DIR MESMO!!!", 0, 10, 1);
        MOVESERVAO(100, 200); // começa a descer a garra
        //delay(300);
        MOVEGARRA(180, 700, 0); // abertura da garra
        //delay(300);
        MOVESERVAO(100, 500); // finaliza a descida da garra

        MOVIMENTO(50, 'F', 'N', 350);// se aproxima da vítima
        PARAR(100);
        RESGATAVITIMA(); // captura e verifica o tipo da vítima

        MOVIMENTO(50, 'T', 'N', 350);// ré estratégica para não "esbarrar" na parede ou triângulo
        PARAR(100);

        MOVESERVAO(80, 1000); // sobe a garra

        MOVEGARRA(50, 300, 0); // desliga o servo da garra

        // retorno ao ponto inicial
        ATUALIZAULTRAS();
        gydistft = gyfrente.dist_cm();

        tempo = millis();
        tempo2 = millis();
        //while (lultrae < 40 && ((tempo2 - tempo) < 3000)) {
        while (gydistft < 40 && (tempo2 - tempo) < 3000) {
          MOVIMENTO(50, 'T', 'N', 0);
          tempo2 = millis();
          //ATUALIZAULTRAS();
          gydistft = gyfrente.dist_cm();
        }
        PARAR(100);
        MOVIMENTO(50, 'F', 'N', 300);
        PARAR(200);
        CURVAANGULO(80, 'E');
        //CURVAESQ(0, 80, 72);

        PARAR(200);

        ATUALIZAGIRO();//atualização das leituras do giroscópio
        eixoxaux = eixox; // valor do eixox guardado para utilização na função de alinhamento
        MOVIMENTO(50, 'F', 'N', 300);
        PARAR(200);
        ATUALIZAGIRO();//atualização das leituras do giroscópio
        eixoxaux = eixox; // valor do eixox guardado para utilização na função de alinhamento
      }
      tempo2 = millis();
    }//FIM DO WHILE
    //}// FIM DO if (gydiste < 34)
  }// FIM DO else if (gydiste < 34)
}//FIM do SALAEVAC

void RESGATAVITIMA() {
  MOVEGARRA(0, 700, 1); // fechamento da garra

  //verificação e indicação do tipo de vítima resgatada

  display.clearDisplay();
  if (LEITURA_MULT_D(switchgarra) == 1) {
    if (LEITURA_MULT_D(switchvit) == 1) {
      digitalWrite(lede, HIGH);
      qtdevitimas++;
      digitalWrite(luzD, HIGH);
      ESCREVE("vitima viva", 10, 20, 1);
    }
    else if (LEITURA_MULT_D(switchvit) == 0) {
      digitalWrite(ledc, HIGH);
      qtdevitimas++;
      digitalWrite(luzD, HIGH);
      ESCREVE("vitima morta", 10, 20, 1);
    }

  }
  else {
    digitalWrite(ledd, HIGH);
    ESCREVE("sem vitima" , 10, 20, 1);
  }

  display.clearDisplay();
  digitalWrite(luzD, LOW);
}
