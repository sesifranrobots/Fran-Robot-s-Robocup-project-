void FR_TESTES() {
 
  while (tela == 0) {

    if (clic <= 5) {
      ESCREVEBYTE(clic, 70, 0, 1);
      ESCREVE("1-Tensao", 0, 0, 1);
      ESCREVE("2-Motor", 0, 10, 1);
      ESCREVE("3-Encoder", 0, 20, 1);
      ESCREVE("4-Distancia", 0, 30, 1);
      ESCREVE("5-Refletancia", 0, 40, 1);
    }

    else if (clic > 5 && clic <= 10) {
      ESCREVEBYTE(clic, 70, 0, 1);
      ESCREVE("6-Timer", 0, 0, 1);
      ESCREVE("7-Giroscopio", 0, 10, 1);
      ESCREVE("8-LEDs", 0, 20, 1);
      ESCREVE("9-Servos", 0, 30, 1);
      ESCREVE("10-Garra", 0, 40, 1);
    }

    else if (clic > 10) {
      ESCREVEBYTE(clic, 70, 0, 1);
      ESCREVE("11-CaRGB", 0, 0, 1);
      ESCREVE("12-Zera Tempo", 0, 10, 1);
      ESCREVE("13-Contraste", 0, 20, 1);
      ESCREVE("14-PPrincipal", 0, 30, 1);
    }

    if ( LEITURA_MULT_D(switchgarra) == 1) {
      clic++;
      if (clic > 14 && clic < 254) {
        clic = 0;
      }
      else if (clic == 255) {
        clic = 14;
      }
      display.clearDisplay();
      delay(500);
    }

    else if ( LEITURA_MULT_D(switchparede) == 1) {
      clic--;
      if (clic > 14 && clic < 254) {
        clic = 0;
      }
      else if (clic == 255) {
        clic = 14;
      }
      display.clearDisplay();
      delay(500);
    }

    else if (digitalRead(switchtras) == 1 && clic > 0) {
      display.clearDisplay();
      digitalWrite(ledc, HIGH);
      delay(1000);
      digitalWrite(ledc, LOW);
      tela = 1;
      delay(500);
    }

    else if (digitalRead(switchtras) == 1 && LEITURA_MULT_D(switchfrente) == 1 && clic == 0) {
      tela = 255;
      estado = 0;
      display.clearDisplay();
      ESCREVE("Voltando p/", 10, 10, 1);
      ESCREVE("Programacao", 10, 20, 1);
      ESCREVE("Normal", 22, 30, 1);
      delay(1500);
      display.clearDisplay();
      ESCREVE("FRAN", 17, 8, 2);
      ESCREVE("ROBOT'S", 0, 24, 2);
      delay(100);
    }

    else if (LEITURA_MULT_D(switchfrente) == 1) {
      if (clic >= 1 && clic <= 5) {
        clic = 6;
      }
      else if ( clic > 5 && clic <= 10) {
        clic = 11;
      }
      else if (clic >= 11) {
        clic = 0;
      }
      display.clearDisplay();
      delay(500);
    }
  }

  while (tela == 1) { 

    //REFERENTE A TENSAO    
    if (clic == 1) {
      display.clearDisplay();
      CHECATENSAO();
      ESCREVE("switchT P/", 15, 32, 1);
      ESCREVE("voltar", 25, 40, 1);
      delay(200);
      if (digitalRead(switchtras) == 1) {
        display.clearDisplay();
        digitalWrite(ledc, HIGH);
        delay(1000);
        digitalWrite(ledc, LOW);
        tela = 0;
        clic = 0;
      }
    }


    //REFERENTE A MOTOR
    else if (clic == 2) {
      ESCREVEBYTE(clic_m1, 77, 0, 1);
      ESCREVE("1-MEF", 0, 0, 1);
      ESCREVE("2-MET", 0, 10, 1);
      ESCREVE("3-MDF", 40, 0, 1);
      ESCREVE("4-MDT", 40, 10, 1);
      ESCREVE("5-T", 0, 20, 1);
      ESCREVE("6-F", 40, 20, 1);
      ESCREVE("Zero P/", 25, 32, 1);
      ESCREVE("voltar", 25, 40, 1);

      if ( LEITURA_MULT_D(switchgarra) == 1) {
        clic_m1++;
        if (clic_m1 > 6 && clic_m1 < 254) {
          clic_m1 = 0;
        }
        else if (clic_m1 == 255) {
          clic_m1 = 6;
        }
        display.clearDisplay();
        delay(100);
      }

      else if ( LEITURA_MULT_D(switchparede) == 1) {
        clic_m1--;
        if (clic_m1 > 6 && clic_m1 < 254) {
          clic_m1 = 0;
        }
        else if (clic_m1 == 255) {
          clic_m1 = 6;
        }
        display.clearDisplay();
        delay(100);
      }

      else if (digitalRead(switchtras) == 1 && clic_m1 > 0) {
        display.clearDisplay();
        delay(200);
        tela = 2;
      }

      else if (digitalRead(switchtras) == 1 && clic_m1 == 0) {
        display.clearDisplay();
        digitalWrite(ledc, HIGH);
        delay(1000);
        digitalWrite(ledc, LOW);
        tela = 0;
        clic = 0;
        clic_m1 = 0;
        delay(100);
      }
    }


    //REFERENTE A ENCODER
    else if (clic == 3) {
      ESCREVEBYTE(clic_e1, 77, 0, 1);
      ESCREVE("1-encoder", 0, 0, 1);
      ESCREVE("2-frente p/cm", 0, 10, 1);
      ESCREVE("3-tras p/cm", 0, 20, 1);
      ESCREVE("Zero P/", 25, 32, 1);
      ESCREVE("voltar", 25, 40, 1);

      if ( LEITURA_MULT_D(switchgarra) == 1) {
        clic_e1++;
        if (clic_e1 > 3 && clic_e1 < 254) {
          clic_e1 = 0;
        }
        else if (clic_e1 == 255) {
          clic_e1 = 3;
        }
        display.clearDisplay();
        delay(100);
      }

      else if ( LEITURA_MULT_D(switchparede) == 1) {
        clic_e1--;
        if (clic_e1 > 3 && clic_e1 < 254) {
          clic_e1 = 0;
        }
        else if (clic_e1 == 255) {
          clic_e1 = 3;
        }
        display.clearDisplay();
        delay(100);
      }

      else if (digitalRead(switchtras) == 1 && clic_e1 > 0) {
        display.clearDisplay();
        delay(200);
        tela = 2;
      }

      else if (digitalRead(switchtras) == 1 && clic_e1 == 0) {
        display.clearDisplay();
        digitalWrite(ledc, HIGH);
        delay(1000);
        digitalWrite(ledc, LOW);
        tela = 0;
        clic = 0;
        clic_e1 = 0;
        delay(100);
      }
    }


    //REFERENTE A distancia
    else if (clic == 4) {
      ESCREVEBYTE(clic_d1, 77, 0, 1);
      ESCREVE("1-Laterais", 0, 0, 1);
      ESCREVE("2-Frente", 0, 10, 1);
      ESCREVE("3-Chao", 0, 20, 1);
      ESCREVE("Zero P/", 25, 32, 1);
      ESCREVE("voltar", 25, 40, 1);

      if ( LEITURA_MULT_D(switchgarra) == 1) {
        clic_d1++;
        if (clic_d1 > 3 && clic_d1 < 254) {
          clic_d1 = 0;
        }
        else if (clic_d1 == 255) {
          clic_d1 = 3;
        }
        display.clearDisplay();
        delay(100);
      }

      else if ( LEITURA_MULT_D(switchparede) == 1) {
        clic_d1--;
        if (clic_d1 > 3 && clic_d1 < 254) {
          clic_d1 = 0;
        }
        else if (clic_d1 == 255) {
          clic_d1 = 3;
        }
        display.clearDisplay();
        delay(100);
      }

      else if (digitalRead(switchtras) == 1 && clic_d1 > 0) {
        display.clearDisplay();
        delay(200);
        tela = 2;
      }

      else if (digitalRead(switchtras) == 1 && clic_d1 == 0) {
        display.clearDisplay();
        digitalWrite(ledc, HIGH);
        delay(1000);
        digitalWrite(ledc, LOW);
        tela = 0;
        clic = 0;
        clic_d1 = 0;
        delay(100);
      }
    }
    

    //REFERENTE A refletancia
    else if (clic == 5) {
      ESCREVEBYTE(clic_r1, 77, 0, 1);
      ESCREVE("1-frontal", 0, 0, 1);
      ESCREVE("2-traseira", 0, 10, 1);
      ESCREVE("3-LDRs", 0, 20, 1);
      ESCREVE("4-RGB", 0, 30, 1);
      ESCREVE("Zero P/ voltar", 0, 40, 1);

      if ( LEITURA_MULT_D(switchgarra) == 1) {
        clic_r1++;
        if (clic_r1 > 4 && clic_r1 < 254) {
          clic_r1 = 0;
        }
        else if (clic_r1 == 255) {
          clic_r1 = 4;
        }
        display.clearDisplay();
        delay(100);
      }

      else if ( LEITURA_MULT_D(switchparede) == 1) {
        clic_r1--;
        if (clic_r1 > 4 && clic_r1 < 254) {
          clic_r1 = 0;
        }
        else if (clic_r1 == 255) {
          clic_r1 = 4;
        }
        display.clearDisplay();
        delay(100);
      }

      else if (digitalRead(switchtras) == 1 && clic_r1 > 0) {
        display.clearDisplay();
        delay(200);
        tela = 2;
      }

      else if (digitalRead(switchtras) == 1 && clic_r1 == 0) {
        display.clearDisplay();
        digitalWrite(ledc, HIGH);
        delay(1000);
        digitalWrite(ledc, LOW);
        tela = 0;
        clic = 0;
        clic_r1 = 0;
        delay(100);
      }
    }
    

    //REFERENTE A timer
    else if (clic == 6) {
      ESCREVEBYTE(clic_t1, 77, 0, 1);
      ESCREVE("1-teste timer", 0, 10, 1);
      ESCREVE("2-zera timer", 0, 20, 1);
      ESCREVE("Zero P/", 25, 32, 1);
      ESCREVE("voltar", 25, 40, 1);

      if ( LEITURA_MULT_D(switchgarra) == 1) {
        clic_t1++;
        if (clic_t1 > 2 && clic_t1 < 254) {
          clic_t1 = 0;
        }
        else if (clic_t1 == 255) {
          clic_t1 = 2;
        }
        display.clearDisplay();
        delay(100);
      }

      else if ( LEITURA_MULT_D(switchparede) == 1) {
        clic_t1--;
        if (clic_t1 > 2 && clic_t1 < 254) {
          clic_t1 = 0;
        }
        else if (clic_t1 == 255) {
          clic_t1 = 2;
        }
        display.clearDisplay();
        delay(100);
      }

      else if (digitalRead(switchtras) == 1 && clic_t1 > 0) {
        display.clearDisplay();
        delay(200);
        tela = 2;
      }

      else if (digitalRead(switchtras) == 1 && clic_t1 == 0) {
        display.clearDisplay();
        digitalWrite(ledc, HIGH);
        delay(1000);
        digitalWrite(ledc, LOW);
        tela = 0;
        clic = 0;
        clic_t1 = 0;
        delay(100);
      }
    }

    
    //REFERENTE A giroscópio
    else if (clic == 7) {

      ATUALIZAGIRO();
      DISPLAYGIRO();
      ESCREVE("switchT P/", 15, 32, 1);
      ESCREVE("voltar", 25, 40, 1);
      delay(500);

      if (digitalRead(switchtras) == 1) {
        display.clearDisplay();
        digitalWrite(ledc, HIGH);
        delay(1000);
        digitalWrite(ledc, LOW);
        tela = 0;
        clic = 0;
      }
    }

    
    //REFERENTE A leds 
    else if (clic == 8) {
      ESCREVEBYTE(clic_l1, 77, 0, 1);
      ESCREVE("1-lede", 0, 0, 1);
      ESCREVE("2-ledc", 0, 10, 1);
      ESCREVE("3-leeD", 0, 20, 1);
      ESCREVE("4-R", 40, 0, 1);
      ESCREVE("5-G", 40, 10, 1);
      ESCREVE("6-B", 40, 20, 1);
      ESCREVE("Zero P/", 25, 32, 1);
      ESCREVE("voltar", 25, 40, 1);

      if ( LEITURA_MULT_D(switchgarra) == 1) {
        clic_l1++;
        if (clic_l1 > 6 && clic_l1 < 254) {
          clic_l1 = 0;
        }
        else if (clic_l1 == 255) {
          clic_l1 = 6;
        }
        display.clearDisplay();
        delay(100);
      }

      else if ( LEITURA_MULT_D(switchparede) == 1) {
        clic_l1--;
        if (clic_l1 > 6 && clic_l1 < 254) {
          clic_l1 = 0;
        }
        else if (clic_l1 == 255) {
          clic_l1 = 6;
        }
        display.clearDisplay();
        delay(100);
      }

      else if (digitalRead(switchtras) == 1 && clic_l1 > 0) {
        display.clearDisplay();
        delay(200);
        tela = 2;
      }

      else if (digitalRead(switchtras) == 1 && clic_l1 == 0) {
        display.clearDisplay();
        digitalWrite(ledc, HIGH);
        delay(1000);
        digitalWrite(ledc, LOW);
        tela = 0;
        clic = 0;
        clic_l1 = 0;
        delay(100);
      }
    }

    
    //REFERENTE A servo
    else if (clic == 9) {
      ESCREVEBYTE(clic_s1, 77, 0, 1);
      ESCREVE("1-garra", 0, 0, 1);
      ESCREVE("2-cacamba", 0, 10, 1);
      ESCREVE("3-servao", 0, 20, 1);

      ESCREVE("Zero P/", 25, 32, 1);
      ESCREVE("voltar", 25, 40, 1);

      if ( LEITURA_MULT_D(switchgarra) == 1) {
        clic_s1++;
        if (clic_s1 > 3 && clic_s1 < 254) {
          clic_s1 = 0;
        }
        else if (clic_s1 == 255) {
          clic_s1 = 3;
        }
        display.clearDisplay();
        delay(100);
      }

      else if ( LEITURA_MULT_D(switchparede) == 1) {
        clic_s1--;
        if (clic_s1 > 3 && clic_s1 < 254) {
          clic_s1 = 0;
        }
        else if (clic_s1 == 255) {
          clic_s1 = 3;
        }
        display.clearDisplay();
        delay(100);
      }

      else if (digitalRead(switchtras) == 1 && clic_s1 > 0) {
        display.clearDisplay();
        delay(200);
        tela = 2;
      }

      else if (digitalRead(switchtras) == 1 && clic_s1 == 0) {
        display.clearDisplay();
        digitalWrite(ledc, HIGH);
        delay(1000);
        digitalWrite(ledc, LOW);
        tela = 0;
        clic = 0;
        clic_s1 = 0;
        delay(100);
      }
    }

    //REFERENTE A GARRA
    else if (clic == 10) {
      ESCREVEBYTE(clic_ga1, 77, 0, 1);
      ESCREVE("1-up", 0, 0, 1);
      ESCREVE("2-down", 30, 0, 1);
      ESCREVE("3-abre", 0, 10, 1);
      ESCREVE("4-fecha", 40, 10, 1);
      ESCREVE("5-pega vitima", 0, 20, 1);
      ESCREVE("Zero P/", 25, 32, 1);
      ESCREVE("voltar", 25, 40, 1);

      if ( LEITURA_MULT_D(switchgarra) == 1) {
        clic_ga1++;
        if (clic_ga1 > 5 && clic_ga1 < 254) {
          clic_ga1 = 0;
        }
        else if (clic_ga1 == 255) {
          clic_ga1 = 5;
        }
        display.clearDisplay();
        delay(100);
      }

      else if ( LEITURA_MULT_D(switchparede) == 1) {
        clic_ga1--;
        if (clic_ga1 > 5 && clic_ga1 < 254) {
          clic_ga1 = 0;
        }
        else if (clic_ga1 == 255) {
          clic_ga1 = 5;
        }
        display.clearDisplay();
        delay(100);
      }

      else if (digitalRead(switchtras) == 1 && clic_ga1 == 0) {
        display.clearDisplay();
        digitalWrite(ledc, HIGH);
        delay(1000);
        digitalWrite(ledc, LOW);
        clic = 0;
        tela = 0;
        clic_ga1 = 0;
      }

      else if (digitalRead(switchtras) == 1 && clic_ga1 == 1) {
        display.clearDisplay();
        digitalWrite(ledc, HIGH);
        delay(500);
        MOVESERVAO(80, 500);
        digitalWrite(ledc, LOW);
        clic_ga1 = 0;
      }

      else if (digitalRead(switchtras) == 1  && clic_ga1 == 2) {
        display.clearDisplay();
        digitalWrite(ledc, HIGH);
        delay(500);
        MOVESERVAO(100, 500);
        digitalWrite(ledc, LOW);
        clic_ga1 = 0;
      }

      else if (digitalRead(switchtras) == 1 && clic_ga1 == 3) {
        display.clearDisplay();
        digitalWrite(ledc, HIGH);
        delay(500);
        MOVEGARRA(180, 500, 0);
        digitalWrite(ledc, LOW);
        clic_ga1 = 0;
      }

      else if (digitalRead(switchtras) == 1 && clic_ga1 == 4) {
        display.clearDisplay();
        digitalWrite(ledc, HIGH);
        delay(500);
        MOVEGARRA(85, 500, 0);
        digitalWrite(ledc, LOW);
        clic_ga1 = 0;
      }

      else if (digitalRead(switchtras) == 1 && clic_ga1 == 5) {
        display.clearDisplay();
        delay(500);
        tela = 2;
      }
    }


    //REFERENTE A CALIBRA RGB
    else if (clic == 11) {
      ESCREVE("Deseja", 17, 5, 1);
      ESCREVE("Calibrar?", 15, 15, 1);
      ESCREVE("SwT para Nao", 5, 30, 1);
      ESCREVE("SwF para Sim", 5, 40, 1);
      if (digitalRead(switchtras) == 1) {
        clic = 0;
        tela = 0;
        digitalWrite(ledc, HIGH);
        delay(1000);
        digitalWrite(ledc, LOW);
        delay(100);
        display.clearDisplay();
      }
       if (LEITURA_MULT_D(switchfrente) == 1) {
        digitalWrite(ledc, HIGH);
        digitalWrite(ledd, HIGH);
        digitalWrite(lede, HIGH);
        delay(500);
        digitalWrite(ledc, LOW);
        digitalWrite(ledd, LOW);
        digitalWrite(lede, LOW);
        delay(100);
        CALIBRAGEM();
        display.clearDisplay();
        tela = 0;
        clic = 0;
      }
    }


    //REFERENTE A ZERA TEMPO
    else if (clic == 12) {
      ESCREVE("Deseja", 23, 5, 1);
      ESCREVE("Zerar o Timer?", 0, 15, 1);
      ESCREVE("SwT para Nao", 5, 30, 1);
      ESCREVE("SwF para Sim", 5, 40, 1);
      if (digitalRead(switchtras) == 1) {
        clic = 0;
        tela = 0;
        digitalWrite(ledc, HIGH);
        delay(1000);
        digitalWrite(ledc, LOW);
        delay(100);
        display.clearDisplay();
      }
      else if (LEITURA_MULT_D(switchfrente) == 1) {
        display.clearDisplay();
        ESCREVE("Zerando", 22, 8, 1);
        ESCREVE("o Timer", 22, 18, 1);
        digitalWrite(ledc, HIGH);
        digitalWrite(ledd, HIGH);
        digitalWrite(lede, HIGH);
        delay(1000);
        digitalWrite(ledc, LOW);
        digitalWrite(ledd, LOW);
        digitalWrite(lede, LOW);
        delay(1000);
        EEPROM.write(111, 0);
        ESCREVE("Timer", 15, 5, 1);
        ESCREVE("Zerado", 15, 15, 1);
        display.clearDisplay();
        tela = 0;
        clic = 0;
      }
    }


    //REFERENTE A CONTRASTE
    else if (clic == 13) {
      ESCREVE("CONTRASTE", 15, 0, 1);
      ESCREVEBYTE(contraste, 30, 12, 2);
      ESCREVE("switchT P/", 15, 32, 1);
      ESCREVE("voltar", 25, 40, 1);
      if (LEITURA_MULT_D(switchgarra) == 1) {
        if (apertofrente == true) {
          contraste = contraste + 5;
        }
        else {
          contraste++;
        }
        EEPROM.write(224, contraste);
        display.setContrast(contraste); //Alterando o Contraste
        display.clearDisplay();
        delay(200);
      }
      else if (LEITURA_MULT_D(switchparede) == 1) {
        if (apertofrente == true) {
          contraste = contraste - 5;
        }
        else {
          contraste--;
        }
        EEPROM.write(224, contraste);
        display.setContrast(contraste); //Alterando o Contraste
        display.clearDisplay();
        delay(200);
      }
      else if (LEITURA_MULT_D(switchfrente) == 1) {
        if (apertofrente == false) {
          apertofrente = true;
        }
        else {
          apertofrente = false;
        }
        delay(200);
      }
      else if (digitalRead(switchtras) == 1) {
        digitalWrite(ledc, HIGH);
        delay(1000);
        digitalWrite(ledc, LOW);
        delay(100);
        display.clearDisplay();
        tela = 0;
        clic = 0;
      }
    }


    //REFERENTE A PORGRAMAÇÃO PRINCIPAL
    else if (clic >= 14) {
      tela = 255;
      estado = 0;
      digitalWrite(luzD, LOW);
      display.clearDisplay();
      ESCREVE("Voltando p/", 10, 10, 1);
      ESCREVE("Programacao", 10, 20, 1);
      ESCREVE("Normal", 22, 30, 1);
      delay(1500);
      display.clearDisplay();
      ESCREVE("FRAN", 17, 8, 2);
      ESCREVE("ROBOT'S", 0, 24, 2);
      delay(100);
    }
  }

  while (tela == 2) {

    //***************************
    //REFERENTE A MOTOR
    //***************************
    if (clic_m1 == 1) {
      MOTOR('E', 'F');
      ESCREVE("MEF", 25 , 10 , 2);
      ESCREVE("switchT P/", 15, 32, 1);
      ESCREVE("voltar", 25, 40, 1);
      if (digitalRead(switchtras) == 1) {
        MOTOR('P', '0');
        tela = 1;
        clic = 2;
        clic_m1 = 0;
        display.clearDisplay();
        delay(200);
      }
    }

    else if (clic_m1 == 2) {
      MOTOR('E', 'T');
      ESCREVE("MET", 25 , 10 , 2);
      ESCREVE("switchT P/", 15, 32, 1);
      ESCREVE("voltar", 25, 40, 1);
      if (digitalRead(switchtras) == 1) {
        MOTOR('P', '0');
        tela = 1;
        clic = 2;
        clic_m1 = 0;
        display.clearDisplay();
        delay(200);
      }
    }

    else if (clic_m1 == 3) {
      MOTOR('D', 'F');
      ESCREVE("MDF", 25 , 10 , 2);
      ESCREVE("switchT P/", 15, 32, 1);
      ESCREVE("voltar", 25, 40, 1);
      if (digitalRead(switchtras) == 1) {
        MOTOR('P', '0');
        tela = 1;
        clic = 2;
        clic_m1 = 0;
        display.clearDisplay();
        delay(200);
      }
    }

    else if (clic_m1 == 4) {
      MOTOR('D', 'T');
      ESCREVE("MDT", 25 , 10 , 2);
      ESCREVE("switchT P/", 15, 32, 1);
      ESCREVE("voltar", 25, 40, 1);
      if (digitalRead(switchtras) == 1) {
        MOTOR('P', '0');
        tela = 1;
        clic = 2;
        clic_m1 = 0;
        display.clearDisplay();
        delay(200);
      }
    }

    else if (clic_m1 == 5) {
      MOTOR('T', 'F');
      ESCREVE("MT", 25 , 10 , 2);
      ESCREVE("switchT P/", 15, 32, 1);
      ESCREVE("voltar", 25, 40, 1);
      if (digitalRead(switchtras) == 1) {
        MOTOR('P', '0');
        tela = 1;
        clic = 2;
        clic_m1 = 0;
        display.clearDisplay();
        delay(200);
      }
    }

    else if (clic_m1 == 6) {
      MOTOR('F', 'F');
      ESCREVE("MF", 25 , 10 , 2);
      ESCREVE("switchT P/", 15, 32, 1);
      ESCREVE("voltar", 25, 40, 1);
      if (digitalRead(switchtras) == 1) {
        MOTOR('P', '0');
        tela = 1;
        clic = 2;
        clic_m1 = 0;
        display.clearDisplay();
        delay(200);
      }
    }

    //***************************
    //REFERENTE A ENCODER
    //***************************

    else if (clic_e1 == 1) {
      ESCREVE("E", 20, 0, 2);
      ESCREVE("D", 60, 0, 2);
      ESCREVEBYTE(pulsosE, 20, 20, 1);
      ESCREVEBYTE(pulsosD, 60, 20, 1);
      ESCREVE("switchT P/", 15, 32, 1);
      ESCREVE("voltar", 25, 40, 1);
      display.clearDisplay();
      delay(300);

      if (digitalRead(switchtras) == 1) {
        display.clearDisplay();
        digitalWrite(ledc, HIGH);
        delay(1000);
        digitalWrite(ledc, LOW);
        tela = 1;
        clic = 3;
        clic_e1 = 0;
        delay(200);
      }
    }

    else if (clic_e1 == 2) {
      ESCREVE("Andar frente", 10, 0, 1);
      ESCREVEBYTE(clic_e2, 10, 15, 2);
      ESCREVE("CM", 50, 15, 2);
      ESCREVE("Zero P/", 25, 32, 1);
      ESCREVE("voltar", 25, 40, 1);

      if ( LEITURA_MULT_D(switchgarra) == 1) {
        display.clearDisplay();
        clic_e2 = clic_e2 + 5;
        delay(100);
      }

      else if ( LEITURA_MULT_D(switchparede) == 1) {
        display.clearDisplay();
        clic_e2 = clic_e2 - 5;
        delay(100);
      }

      else if (digitalRead(switchtras) == 1 && clic_e2 > 0) {
        display.clearDisplay();
        delay(200);
        tela = 3;
      }

      else if (digitalRead(switchtras) == 1 && clic_m1 == 0) {
        display.clearDisplay();
        digitalWrite(ledc, HIGH);
        delay(1000);
        digitalWrite(ledc, LOW);
        tela = 1;
        clic = 3;
        clic_e1 = 0;
        clic_e2 = 0;
        delay(100);
      }
    }

    else if (clic_e1 == 3) {
      ESCREVE("Andar tras", 10, 0, 1);
      ESCREVEBYTE(clic_e2, 10, 15, 2);
      ESCREVE("CM", 50, 15, 2);
      ESCREVE("Zero P/", 25, 32, 1);
      ESCREVE("voltar", 25, 40, 1);

      if ( LEITURA_MULT_D(switchgarra) == 1) {
        display.clearDisplay();
        clic_e2 = clic_e2 + 5;
        delay(100);
      }

      else if ( LEITURA_MULT_D(switchparede) == 1) {
        display.clearDisplay();
        clic_e2 = clic_e2 - 5;
        delay(100);
      }

      else if (digitalRead(switchtras) == 1 && clic_e2 > 0) {
        display.clearDisplay();
        delay(200);
        tela = 3;
      }

      else if (digitalRead(switchtras) == 1 && clic_m1 == 0) {
        display.clearDisplay();
        digitalWrite(ledc, HIGH);
        delay(1000);
        digitalWrite(ledc, LOW);
        tela = 1;
        clic = 3;
        clic_e1 = 0;
        clic_e2 = 0;
        delay(100);
      }
    }

    //***************************
    //REFERENTE A distancia
    //***************************
    else if (clic_d1 > 0) {
      ESCREVE("switchT P/", 15, 32, 1);
      ESCREVE("voltar", 25, 40, 1);

      if (clic_d1 == 1) {
        DISPLAYGY('L');
        delay(300);
      }

      else if (clic_d1 == 2) {
        DISPLAYGY('F');
        delay(300);
      }

      else if (clic_d1 == 3) {
        DISPLAYGY('C');
        delay(300);
      }

      if (digitalRead(switchtras) == 1) {
        display.clearDisplay();
        digitalWrite(ledc, HIGH);
        delay(1000);
        digitalWrite(ledc, LOW);
        tela = 1;
        clic = 4;
        clic_d1 = 0;
        delay(200);
      }
    }


    //***************************
    //REFERENTE A relfetancia
    //***************************

    else if (clic_r1 == 1) {
      DISPLAYREF('f');
      ESCREVE("switchT P/", 15, 32, 1);
      ESCREVE("voltar", 25, 40, 1);
      display.clearDisplay();
      delay(1000);
      if (digitalRead(switchtras) == 1) {
        display.clearDisplay();
        digitalWrite(ledc, HIGH);
        delay(1000);
        digitalWrite(ledc, LOW);
        tela = 1;
        clic = 5;
        clic_r1 = 0;
      }
    }

    else if (clic_r1 == 2) {
      DISPLAYREF('t');
      ESCREVE("switchT P/", 15, 32, 1);
      ESCREVE("voltar", 25, 40, 1);
      display.clearDisplay();
      delay(1000);
      if (digitalRead(switchtras) == 1) {
        display.clearDisplay();
        digitalWrite(ledc, HIGH);
        delay(1000);
        digitalWrite(ledc, LOW);
        tela = 1;
        clic = 5;
        clic_r1 = 0;
      }
    }

    else if (clic_r1 == 3) {
      ESCREVEBYTE(clic_r2, 77, 0, 1);
      ESCREVE("1-R", 0, 0, 1);
      ESCREVE("2-G", 25, 0, 1);
      ESCREVE("3-B", 50, 0, 1);
      ESCREVE("4-desligado", 0, 10, 1);
      ESCREVE("Zero P/", 25, 32, 1);
      ESCREVE("voltar", 25, 40, 1);

      if ( LEITURA_MULT_D(switchgarra) == 1) {
        clic_r2++;
        if (clic_r2 > 4 && clic_r2 < 254) {
          clic_r2 = 0;
        }
        else if (clic_r2 == 255) {
          clic_r2 = 4;
        }
        display.clearDisplay();
        delay(100);
      }

      else if ( LEITURA_MULT_D(switchparede) == 1) {
        clic_r2--;
        if (clic_r2 > 4 && clic_r2 < 254) {
          clic_r2 = 0;
        }
        else if (clic_r2 == 255) {
          clic_r2 = 4;
        }
        display.clearDisplay();
        delay(100);
      }

      else if (digitalRead(switchtras) == 1 && clic_r2 > 0) {
        display.clearDisplay();
        delay(200);
        tela = 3;
      }

      else if (digitalRead(switchtras) == 1 && clic_r2 == 0) {
        display.clearDisplay();
        digitalWrite(ledc, HIGH);
        delay(1000);
        digitalWrite(ledc, LOW);
        tela = 1;
        clic = 5;
        clic_r1 = 0;
        delay(100);
      }
    }
    else if (clic_r1 == 4) {
      ESCREVEBYTE(clic_r3, 77, 0, 1);
      ESCREVE("1-Ponta", 0, 0, 1);
      ESCREVE("2-Meio", 0, 10, 1);
      ESCREVE("3-PLinha", 0, 20, 1);
      ESCREVE("Zero P/", 25, 32, 1);
      ESCREVE("voltar", 25, 40, 1);

      if ( LEITURA_MULT_D(switchgarra) == 1) {
        clic_r3++;
        if (clic_r3 > 3 && clic_r3 < 254) {
          clic_r3 = 0;
        }
        else if (clic_r3 == 255) {
          clic_r3 = 3;
        }
        display.clearDisplay();
        delay(100);
      }
      else if ( LEITURA_MULT_D(switchparede) == 1) {
        clic_r3--;
        if (clic_r3 > 3 && clic_r3 < 254) {
          clic_r3 = 0;
        }
        else if (clic_r3 == 255) {
          clic_r3 = 3;
        }
        display.clearDisplay();
        delay(100);
      }
      else if (digitalRead(switchtras) == 1 && clic_r3 > 0) {
        display.clearDisplay();
        delay(200);
        tela = 3;
      }

      else if (digitalRead(switchtras) == 1 && clic_r3 == 0) {
        display.clearDisplay();
        digitalWrite(ledc, HIGH);
        delay(1000);
        digitalWrite(ledc, LOW);
        tela = 1;
        clic = 5;
        clic_r1 = 0;
        delay(100);
      }
    }

    //***************************
    //REFERENTE A timer
    //***************************
    else if (clic_t1 == 1) {
      display.clearDisplay();
      HORARIO();
      if (horas < 10) {
        ESCREVE("0", 0, 10, 2);
        ESCREVEBYTE(horas, 13, 10, 2);
      }
      else if (horas > 10) {
        ESCREVEBYTE(horas, 10, 10, 2);
      }

      ESCREVE(":", 22, 10, 2);

      if (minutos < 10) {
        ESCREVE("0", 30, 10, 2);
        ESCREVEBYTE(minutos, 43, 10, 2);
      }
      else if (minutos > 10) {
        ESCREVEBYTE(minutos, 30, 10, 2);
      }

      ESCREVE(":", 52, 10, 2);

      if (segundos < 10) {
        ESCREVE("0", 60, 10, 2);
        ESCREVEBYTE(segundos, 73, 10, 2);
      }
      else if (segundos > 10) {
        ESCREVEBYTE(segundos, 60, 10, 2);
      }

      ESCREVE("switchT P/", 15, 32, 1);
      ESCREVE("voltar", 25, 40, 1);
      delay(1000);

      if (digitalRead(switchtras) == 1) {
        display.clearDisplay();
        digitalWrite(ledc, HIGH);
        delay(1000);
        digitalWrite(ledc, LOW);
        tela = 1;
        clic = 6;
        clic_t1 = 0;
      }
    }

    else if (clic_t1 == 2) {
      display.clearDisplay();
      ESCREVE("switchF ", 0, 0, 2);
      ESCREVE("P/zerar", 0, 15, 2);
      ESCREVE("switchT P/", 15, 32, 1);
      ESCREVE("voltar", 25, 40, 1);
      delay(500);

      if (digitalRead(switchtras) == 1) {
        display.clearDisplay();
        digitalWrite(ledc, HIGH);
        delay(1000);
        digitalWrite(ledc, LOW);
        tela = 1;
        clic = 6;
        clic_t1 = 0;
        delay(200);
      }
      else if (LEITURA_MULT_D(switchfrente) == 1) {
        tela = 1;
        clic = 6;
        clic_t1 = 0;
        //rtc.setTime(0, 0, 2);
        digitalWrite(lede, HIGH);
        display.clearDisplay();
        delay(800);
        digitalWrite(lede, LOW);
      }
    }

    //***************************
    //REFERENTE A leds
    //***************************

    else if (clic_l1 > 0) {
      display.clearDisplay();
      ESCREVE("switchT P/", 15, 32, 1);
      ESCREVE("voltar", 25, 40, 1);
      delay(500);

      if (clic_l1 == 1) {
        digitalWrite(lede, HIGH);
      }

      else if (clic_l1 == 2) {
        digitalWrite(ledc, HIGH);
      }

      else if (clic_l1 == 3) {
        digitalWrite(ledd, HIGH);
      }

      else if (clic_l1 == 4) {
        digitalWrite(ledrgb[0], HIGH);
      }

      else if (clic_l1 == 5) {
        digitalWrite(ledrgb[1], HIGH);
      }

      else if (clic_l1 == 6) {
        digitalWrite(ledrgb[2], HIGH);
      }

      if (digitalRead(switchtras) == 1) {
        display.clearDisplay();
        digitalWrite(ledc, HIGH);
        delay(1000);
        digitalWrite(ledc, LOW);
        tela = 1;
        clic = 8;
        clic_l1 = 0;
        digitalWrite(lede, LOW);
        digitalWrite(ledc, LOW);
        digitalWrite(ledd, LOW);
        digitalWrite(ledrgb[0], LOW);
        digitalWrite(ledrgb[1], LOW);
        digitalWrite(ledrgb[2], LOW);
        delay(100);
      }
    }

    //***************************
    //REFERENTE A SERVO
    //***************************
    else if (clic_s1 > 0) {


      ESCREVE("switchT", 0, 32, 1);
      ESCREVE("voltar", 0, 40, 1);
      ESCREVE("switchF", 42, 32, 1);
      ESCREVE("mover", 42, 40, 1);

      ESCREVE("POS:", 0, 12, 2);
      ESCREVEBYTE(clic_s2, 45, 12, 2);
      if (clic_s1 == 1) {
        ESCREVE("GARRA", 30, 0, 1);
      }

      else if (clic_s1 == 2) {
        ESCREVE("CACAMBA", 30, 0, 1);
      }

      else if (clic_s1 == 3) {
        ESCREVE("SERVAO", 30, 0, 1);
      }

      if ( LEITURA_MULT_D(switchgarra) == 1) {
        display.clearDisplay();
        clic_s2 = clic_s2 + 5;
        delay(100);
      }

      else if ( LEITURA_MULT_D(switchparede) == 1) {
        display.clearDisplay();
        clic_s2 = clic_s2 - 5;
        delay(100);
      }

      else if ( LEITURA_MULT_D(switchfrente) == 1) {
        digitalWrite(ledc, HIGH);
        delay(500);

        if (clic_s1 == 1) {
          display.clearDisplay();
          MOVEGARRA(clic_s2, 500, 0);
          digitalWrite(ledc, LOW);
          clic_s2 = 90;
        }

        else if (clic_s1 == 2) {
          display.clearDisplay();
          MOVECACAMBA(clic_s2, 500);
          digitalWrite(ledc, LOW);
          clic_s2 = 90;
        }


        else if (clic_s1 == 3) {
          display.clearDisplay();
          MOVESERVAO(clic_s2, 500);
          digitalWrite(ledc, LOW);
          clic_s2 = 90;
        }
      }
      else if (digitalRead(switchtras) == 1) {
        display.clearDisplay();
        digitalWrite(ledc, HIGH);
        delay(1000);
        digitalWrite(ledc, LOW);
        tela = 1;
        clic = 9;
        clic_s1 = 0;
        clic_s2 = 90;
      }
    }

    else if (clic_ga1 == 5) {

      MOVESERVAO(100, 500);
      delay(500);
      MOVEGARRA(180, 500, 0);

      while (digitalRead(switchtras) == 0) {
        delay(10);
      }
    
      sgarra.attach(servogarra);
      sgarra.write(85);
      delay(500);

      if (LEITURA_MULT_D(switchgarra) == 1) {
        if (LEITURA_MULT_D(switchvit) == 1) {
          digitalWrite(lede, HIGH);

          ESCREVE("vitima viva", 10, 20, 1);
        }
        else if (LEITURA_MULT_D(switchvit) == 0) {
          digitalWrite(ledc, HIGH);
          ESCREVE("vitima morta", 10, 20, 1);
        }

      }
      else {
        digitalWrite(ledd, HIGH);
        ESCREVE("sem vitima" , 10, 20, 1);
      }

      delay(500);

      servao.attach(pservao);
      servao.write(83);
      delay(60);
      servao.detach();
      delay(1000);


      sgarra.write(110);
      delay(500);
      sgarra.write(85);
      delay(500);
      sgarra.detach();
      delay(1000);

      digitalWrite(lede, LOW);
      digitalWrite(ledc, LOW);
      digitalWrite(ledd, LOW);

      display.clearDisplay();
      tela = 1;
      clic = 10;
      clic_ga1 = 0;
    }
  }

  while (tela == 3) {

    if (clic_e1 == 2) {
      ANDAR_FCM(clic_e2);
      tela = 2;
      clic_e1 = 2;
      clic_e2 = 0;
    }

    else if (clic_e1 == 3) {
      ANDAR_TCM(clic_e2);
      tela = 2;
      clic_e1 = 3;
      clic_e2 = 0;
    }


    else if (clic_e1 == 3) {
      ANDAR_TCM(clic_e2);
      tela = 2;
      clic_e1 = 3;
      clic_e2 = 0;
    }


    else if (clic_r2 > 0) {

      if (clic_r2 == 1) {
        digitalWrite(ledrgb[0], HIGH);
        digitalWrite(ledrgb[1], LOW);
        digitalWrite(ledrgb[2], LOW);
      }

      else if (clic_r2 == 2) {
        digitalWrite(ledrgb[0], LOW);
        digitalWrite(ledrgb[1], HIGH);
        digitalWrite(ledrgb[2], LOW);
      }

      else if (clic_r2 == 3) {
        digitalWrite(ledrgb[0], LOW);
        digitalWrite(ledrgb[1], LOW);
        digitalWrite(ledrgb[2], HIGH);
      }

      else if (clic_r2 == 4) {
        digitalWrite(ledrgb[0], LOW);
        digitalWrite(ledrgb[1], LOW);
        digitalWrite(ledrgb[2], LOW);
      }



      DISPLAYREF('l');
      ESCREVE("switchT P/", 15, 33, 1);
      ESCREVE("voltar", 25, 41, 1);
      display.clearDisplay();
      delay(1000);

      if (digitalRead(switchtras) == 1) {
        digitalWrite(ledrgb[0], LOW);
        digitalWrite(ledrgb[1], LOW);
        digitalWrite(ledrgb[2], LOW);
        display.clearDisplay();
        digitalWrite(ledc, HIGH);
        delay(1000);
        digitalWrite(ledc, LOW);
        tela = 2;
        clic_r1 = 3;
        clic_r2 = 0;
      }
    }

    else if (clic_r3 > 0) {
      CHECACORES();
      display.clearDisplay();
      if (clic_r3 == 1) {
        DISPLAYREF('p');
      }
      else if (clic_r3 == 2) {
        DISPLAYREF('m');
      }
      else if (clic_r3 == 3) {
        DISPLAYREF('i');
      }

      ESCREVE("switchT P/", 15, 33, 1);
      ESCREVE("voltar", 25, 41, 1);
      delay(1000);
      if (digitalRead(switchtras) == 1) {
        digitalWrite(ledc, HIGH);
        digitalWrite(ledrgb[0], LOW);
        digitalWrite(ledrgb[1], LOW);
        digitalWrite(ledrgb[2], LOW);
        delay(1000);
        digitalWrite(ledc, LOW);
        display.clearDisplay();
        tela = 2;
        clic_r1 = 4;
        clic_r3 = 0;
      }//fim do if (digitalRead(switchtras) == 1)
    }
  }

}
