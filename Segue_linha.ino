void SEGUELINHA () {//INICIO void SEGUELINHA

  /*Função principal do Seguimento de linha, nela
     se encontra as verificações de cruzamento e também
     a função de alinhamento*/

  //variáveis para identificação da linha a frente em casos de cruzamento
  bool linhafrente = false;
  bool confirmalinha = false;

  ATUALIZASENSORES(); //Atualização das leituras dos sensores para as verificações

  if (inclinacao == 1) {
    ALINHAMENTORAMPA();
  }
  else if (inclinacao == 2 || inclinacao == 3) {
    ALINHAMENTORAMPAD();
  }
  else {
    ALINHAMENTO(); //Função de alinhamento
    digitalWrite(ledd, LOW);
    digitalWrite(lede, LOW);
    digitalWrite(ledc, LOW);
  }

  ATUALIZASENSORES();

  //cruzamento para direita
  if (ldp > 500 && ldm > 500 && lde > 500 && inclinacao == false) {

    digitalWrite(ledd, HIGH);
    PARAR(10);
    MOVIMENTO(60, 'T', 'N', 20); //traz contra inércia
    PARAR(100);

    /*se não tiver verde em nenhum dos lados toque para frente
      para verificar se existe linha a frente do cruzamento*/
    if (VERDE() == false) {
      tempo = millis();
      tempo2 = millis() - tempo;

      while (confirmalinha == false && tempo2 < 205) {
        MOVIMENTO(50, 'F', 'N', 0);
        ATUALIZASENSORES();
        tempo2 = millis() - tempo;
        if (ldm < 300 && ldp < 300) {
          confirmalinha = true;
        }
      }
      PARAR(100);
      ATUALIZASENSORES();
      if (lce > 400 || lcd > 400) {
        if (lc > 400 || lde > 400 || led > 400) {
          digitalWrite(ledc, HIGH);
          linhafrente = true;
        }
      }

      /*se tiver linha a frete do cruzamento, segnifica uma intersecção,
        dessa forma o robo da um passo para frente para sair da situação
        de cruzamento e voltar seguir linha*/
      if (linhafrente == true) {
        MOVIMENTO(55, 'F', 'N', 150);
      }

      /*caso não tenha linha a frente se trata de cruzmento simples para direita*/
      else {
        CURVADIR(1, 80, 80);
      }

    }
    digitalWrite(lede, LOW);
    digitalWrite(ledc, LOW);
    digitalWrite(ledd, LOW);
    tempoalinha = millis();
  }

  //cruzamento para esquerda
  else if (led > 500 && lep > 500 && lem > 500 && inclinacao == false) {

    digitalWrite(lede, HIGH);
    PARAR(10);
    MOVIMENTO(60, 'T', 'N', 20); //traz contra inércia
    PARAR(100);

    /*se não tiver verde em nenhum dos lados toque para frente
      para verificar se existe linha a frente do cruzamento*/
    if (VERDE() == false) {

      ATUALIZASENSORES();
      tempo = millis();
      tempo2 = millis() - tempo;

      while (confirmalinha == false && tempo2 < 205)  {

        MOVIMENTO(50, 'F', 'N', 0);
        ATUALIZASENSORES();
        tempo2 = millis() - tempo;

        if (lep < 250 && lem < 250) {
          confirmalinha = true;
        }
      }

      PARAR(100);
      ATUALIZASENSORES();

      if (lce > 400 || lcd > 400) {
        if (lc > 400 || lde > 400 || led > 400) {
          digitalWrite(ledc, HIGH);
          linhafrente = true;
        }
      }

      /*se tiver linha a frete do cruzamento, segnifica uma intersecção,
        dessa forma o robo da um passo para frente para sair da situação
        de cruzamento e voltar seguir linha*/
      if (linhafrente == true) {
        MOVIMENTO(55, 'F', 'N', 150);
      }

      /*caso não tenha linha a frente se trata de cruzmento simples para direita*/
      else {
        CURVAESQ(1, 80, 80);
      }
    }

    digitalWrite(lede, LOW);
    digitalWrite(ledc, LOW);
    digitalWrite(ledd, LOW);
    tempoalinha = millis();
  }
}//FIM void SEGUELINHA

void ALINHAMENTO() {

  difldp = ldp - 100;
  difldm = ldm - 100;
  diflde = lde - 150;
  difled = led - 150;
  diflem = lem - 100;
  diflep = lep - 100;

  pldp = map(difldp, 0, 650, 0, 15);
  pldm = map(difldm, 0, 650, 0, 30);
  plde = map(diflde, 0, 600, 0, 50);
  pled = map(difled, 0, 600, 0, 50);
  plem = map(diflem, 0, 650, 0, 30);
  plep = map(diflep, 0, 650, 0, 15);

  potdir = 55; //60
  potesq = 50; //66


  //Se robô desalinhar
  if (lce < 500 || lcd < 500) {

    //Redundancia em caso que apenas um dos sensores centrais estar no preto
    if (lc < 500) {

      if (lce > 500 && lep < 500 && lem < 500 && led < 500 && ldp < 500 && ldm < 500 && lde < 500 && lcd < 500 && lc < 500) {

        MOVIMENTO(60, 'F', 'N', 25);
      }

      if (lcd > 500 && lep < 500 && lem < 500 && led < 500 && ldp < 500 && ldm < 500 && lde < 500 && lce < 500 && lc < 500) {

        MOVIMENTO(60, 'F', 'N', 25);
      }
    }

    //_______________________________________________________________________
    //_______________________________________________________________________
    //ALINHAMENTO em GAP
    //_______________________________________________________________________
    //_______________________________________________________________________

    if (pldp <= 0 && pldm <= 0 && plde <= 0 && pled <= 0 && plem <= 0 && plep <= 0 && lc < 500) {
      PARAR(300);

      ATUALIZAGIRO();//atualização das leituras do giroscópio
      eixoxaux = eixox; // valor do eixox guardado para utilização na função de alinhamento

      MOVIMENTO(50, 'F', 'N', 120);
      PARAR(100);

      //--------------------------------------VERIFICA VERMELHO------------------------------------

      CHECACORES();
      //IDVERMELHO();
      if (rgbldrdm.cor('R') > rgbldrdm.cor('G') && rgbldrdm.cor('R') > rgbldrdm.cor('B') &&
          rgbldrdm.cor('G') < 200 && rgbldrdm.cor('B') < 200) {
        vermelhodir = true;

      }

      else if (rgbldrem.cor('R') > rgbldrem.cor('G') && rgbldrem.cor('R') > rgbldrem.cor('B') &&
               rgbldrem.cor('G') < 200 && rgbldrem.cor('B') < 200) {
        vermelhoesq = true;

      }
      if (vermelhoesq == true || vermelhodir == true) {
        digitalWrite(luzD, HIGH);
        display.clearDisplay();
        ESCREVE("VERMELHO!!!", 0, 10, 1);
        estado = 2;
        return;
      }
      else {
        digitalWrite(luzD, HIGH);
        display.clearDisplay();
        ESCREVE("BRANCO!!!", 0, 10, 1);
      }

      digitalWrite(luzD, LOW);

      tempo = millis();
      tempo2 = millis();

      byte alinhagiro = 1;

      while (alinhagiro == 1) {

        /*se algum sensor identificar preto atualiza variavel alinhagiro
          para sair do alinhamento pelo giroscíopio e voltar fazer alinhaento normal*/
        ATUALIZASENSORES();
        tempo2 = millis();
        if (ldp > 500 || ldm > 500 || lde > 500 || lce > 500 || lc > 500 || lcd > 500 || led > 500 || lem > 500 || lep > 500) {
          alinhagiro = 0;
        }


        else if (tempo2 - tempo > 2200) {
          PARAR(200);
          alinhagiro = 0;
          estado = 1; // identificou sala de resgate
          LEDDIR();
          LEDESQ();
          LEDCEN();
          digitalWrite(ledrgb[0], HIGH);
          digitalWrite(ledrgb[1], LOW);
          digitalWrite(ledrgb[2], LOW);
          return;
        }

        //se não encontra linha
        else {
          ALINHAGIRO(60);

        }// fim do else
      }//fim do while
    }//fim do if - identifica GAP

    //_______________________________________________________________________
    //_______________________________________________________________________
    //ALINHAMENTO COM O DIREITA PRÓXIMO A LINHA
    //_______________________________________________________________________
    //_______________________________________________________________________

    else if (diflde > difldm && diflde > difldp && diflde > difled && diflde > diflem && diflde > diflep) {
      if (plde < 0) {
        plde = 0;
      }
      if (plde <= 25) {
        potdir = potdir - (plde * 2);
        potesq = potesq + plde;
        analogWrite( MDT, 0);
        analogWrite( MET, 0);
        analogWrite( MDF, potdir * 2.54);
        analogWrite( MEF, potesq * 2.54);
      }
      else if (plde > 25) {
        potdir = 20 + plde;
        potesq = 76;
        analogWrite( MDT, potdir * 2.54);
        analogWrite( MET, 0);
        analogWrite( MDF, 0);
        analogWrite( MEF, potesq * 2.54);
      }
    }

    //_______________________________________________________________________
    //_______________________________________________________________________
    //ALINHAMENTO COM O ESQUERDA PRÓXIMO A LINHA
    //_______________________________________________________________________
    //_______________________________________________________________________

    else if (difled > diflem && difled > diflep && difled > diflde && difled > difldm && difled > difldp) {
      if (pled < 0) {
        pled = 0;
      }
      if (pled <= 25) {
        potdir = potdir + pled;
        potesq = potesq - (pled * 2);
        analogWrite( MDT, 0);
        analogWrite( MET, 0);
        analogWrite( MDF, potdir * 2.54);
        analogWrite( MEF, potesq * 2.54);
      }
      else if (pled >= 25) {
        potdir = 85;
        potesq = 10 + pled;
        analogWrite( MDT, 0);
        analogWrite( MET, potesq * 2.54);
        analogWrite( MDF, potdir * 2.54);
        analogWrite( MEF, 0);
      }
    }

    //_______________________________________________________________________
    //_______________________________________________________________________
    //ALINHAMENTO COM O DIREITA MEIO
    //_______________________________________________________________________
    //_______________________________________________________________________

    else if (difldm > diflde && difldm > difldp && difldm > difled && difldm > diflem && difldm > diflep) {
      potdir = 45 + pldm;
      potesq = 76;
      analogWrite( MDT, potdir * 2.54);
      analogWrite( MET, 0);
      analogWrite( MDF, 0);
      analogWrite( MEF, potesq * 2.54);
    }

    //_______________________________________________________________________
    //_______________________________________________________________________
    //ALINHAMENTO COM O ESQUERDA MEIO
    //_______________________________________________________________________
    //_______________________________________________________________________

    else if (diflem > difled && diflem > diflep && diflem > diflde && diflem > difldm && diflem > difldp) {
      potdir = 85;
      potesq = 35 + plem;
      analogWrite( MDT, 0);
      analogWrite( MET, potesq * 2.54);
      analogWrite( MDF, potdir * 2.54);
      analogWrite( MEF, 0);
    }

    //_______________________________________________________________________
    //_______________________________________________________________________
    //ALINHAMENTO COM O DIREITA PONTA
    //_______________________________________________________________________
    //_______________________________________________________________________

    else if (difldp > diflde && difldp > difldm && difldp > difled && difldp > diflem && difldp > diflep) {
      potdir = 75 + pldp;
      potesq = 76;
      analogWrite( MDT, potdir * 2.54);
      analogWrite( MET, 0);
      analogWrite( MDF, 0);
      analogWrite( MEF, potesq * 2.54);
    }

    //_______________________________________________________________________
    //_______________________________________________________________________
    //ALINHAMENTO COM O ESQUERDA PONTA
    //_______________________________________________________________________
    //_______________________________________________________________________

    else if (diflep > difled && diflep > diflem && diflep > diflde && diflep > difldm && diflep > difldp) {
      potdir = 85;
      potesq = 65 + plep;
      analogWrite( MDT, 0);
      analogWrite( MET, potesq * 2.54);
      analogWrite( MDF, potdir * 2.54);
      analogWrite( MEF, 0);
    }
  }



  //se robo não está desalinhado
  else {
    analogWrite( MDT, 0);
    analogWrite( MET, 0);
    analogWrite( MDF, potdir * 2.54);
    analogWrite( MEF, potesq * 2.54);
  }
}
