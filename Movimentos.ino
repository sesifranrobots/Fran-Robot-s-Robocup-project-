
//______________________________________________________ FUNÇÕES PARA MOVIMENTAR ROBÔ _____________________________________________________________________________
void MOVIMENTO (byte potencia, char mov, char eixo, int tempomov) {

  /* Função para movimentação do robô com parâmetros de potência(em porcentagem),
    movimentação ('T', 'E','D', 'F'), eixo('S', 'N') e tempomov(duração do movimento em delay)
    Em algumas partes da programação verifica-se que o motor da direita é 2% mais devagar
    que o da esquerda, ou que o da esquerda é 2% mais forte que o da direita, isso se deve
    ao fato de que o robô não andava reto e tal altereção foi feita para resolver o problema*/

  //Formula para transformar a potência (porcentagem) para voltagem do motor
  float potfinal = 2.54 * (potencia + 11); // potência de operação do motor
  //float potmid = 2.54 * (potencia - 5); // potência calculada para o giro em curvas fora do eixo do motor;
  float potmid = 2.54 * potencia; // potência calculada para o giro em curvas fora do eixo do motor;



  switch (mov) {//Inicio do switch
    case  'D':
      /*Para fazer uma curva para a direita o motor da esquerda
         frente tem que girar com mais força que o da direita trás*/
      analogWrite( MDT, potfinal);
      analogWrite( MET, 0);
      analogWrite( MDF, 0);
      analogWrite( MEF, potmid); //potmid
      break;

    // ------------------------------------------------------------------------------
    // -----------------------------------------------------------------------------
    // ------------------------------------------------------------------------------

    case  'E':
      /*Para fazer uma curva para a esquerda o motor da direita
         frente tem que girar com mais força que o da esquerda trás*/
      analogWrite( MDT, 0);
      analogWrite( MET, potmid); //potmid
      analogWrite( MDF, potfinal);
      analogWrite( MEF, 0);
      break;

    // ------------------------------------------------------------------------------
    // ------------------------------------------------------------------------------
    // ------------------------------------------------------------------------------
    case  'F':
      /*Utilizado quando o robô deve andar para frente*/
      analogWrite( MDT, 0);
      analogWrite( MET, 0);
      analogWrite( MDF, potfinal);
      analogWrite( MEF, potmid);
      break;

    // ------------------------------------------------------------------------------
    // ------------------------------------------------------------------------------
    // ------------------------------------------------------------------------------

    case  'T':
      /*Utilizado quando o robô deve dar ré*/
      analogWrite( MDT, potfinal);
      analogWrite( MET, (potfinal + 10));
      analogWrite( MDF, 0);
      analogWrite( MEF, 0);
      break;
  } //Fim do switch
  delay(tempomov);
  /*o delay de execução é definido dentro
     da função tornando a progamação mais simples*/

}

void PARAR(int tempo) {
  /*Função para o robô ficar parado
    o delay de execução desse parar é
    definido dentro da função tornando
    a progamação mais simples*/
  analogWrite( MDT, 0);
  analogWrite( MET, 0);
  analogWrite( MDF, 0);
  analogWrite( MEF, 0);
  delay(tempo);
}

//______________________________________________________ FUNÇÕES PARA REALIZAR CURVAS _____________________________________________________________________________

void CURVADIR(byte seguelinha, byte forca, int valor) {

  /*Função de curvas para a direita, ela utiliza o parâmetro
     seguelinha para identificar o tipo de curva, se o parâmetro
     for definido como 1 ele faz a curva seguindo as propriedades
     do segue linha, se for com o valor 0 ou 2 ele só executa a
     curva*/

  //curvas para seguimento de linha
  if (seguelinha == 1) {
    MOVIMENTO(50, 'F', 'N', 100);
    PARAR(100);

    /*Atenção o giroscópio BNO055 no eixo x só aceita angulações entre 0 e 360°, por exemplo:
      quando o robô estiver em 359° e virar para a direita para aumentar mais o valor, o giroscópio
      muda para 0° e começa a aumentar a partir desse valor até chegar em 359 novamente.
      Curvas para a Direita aumentam o valor no eixo x do giroscópio*/

    int giro = 0;  //Variável que define até que grau no eixo x o robô deve ir
    int confirmagiro = 0; //Variável que confirma se o robô vai passar pelos 360° em algum momento
    int vplinha = 0; //Váriavel que determina quando o robô deve começar a procurar linha
    int vplinha2 = 0; //Váriavel que determina quando o robô deve começar a procurar linha antes dos 360°

    bool saida = false; //Váriavel para verificar se o robô encontrou a angulação desejada
    bool procuralinha = false; //Váriavel para verificar se o robô deve procurar linha antes ou depois dos 360°
    bool achoulinha = false; //Váriavel para verificar se ele encontrou linha

    ATUALIZAGIRO(); //Atualiza os valores do giroscópio
    DISPLAYGIRO(); //Mostra no Display os valores do Giroscópio

    //Redundancia para maior precisão nas leituras do giscópio
    if (eixox == 0  || eixox == 359) {
      /*Se o robô estiver em 0° ou em 359° ele deve dar uma pequena curva
        para sair dessa angulação, devido a elas serem muito "instáveis" e poderem
        atrapalhar o robô durante o início da curva*/
      MOVIMENTO(forca, 'D', 'S', 10); //Curva para a direita de 10 segundos
      PARAR(10);
      ATUALIZAGIRO(); //Atualiza os valores do giroscópio
      DISPLAYGIRO();
    }

    //Cálculo para verificar se o robô vai passar pelos 360° durante a curva
    confirmagiro = 360 - eixox;

    /*Se o robô vai passar pelos 360° graus durante a curva*/
    if (confirmagiro <= (valor)) {
      /*Se o robô vai passar pelos 360° graus durante a curva*/

      digitalWrite(ledd, HIGH); //LED para sinalização

      /*Cálculo para definir até qual angulação o robô deve ir*/
      giro = valor - confirmagiro;
      //Cálculo para definir em qual angulação o robô deve começar a procurar linha
      vplinha = giro - 15;

      if (vplinha < 0) {
        /*Caso ele tenha que procurar linha antes dos 360° ele define
          ele define o valor para iniciar a procura antes dos 360° */
        vplinha2 = 360 + vplinha;
        procuralinha = true;
      }

      while (saida == false && achoulinha == false) {
        /*Enquanto o robô não passar pelos 360° ou se necessário encontrar a linha
          antes dos 360° ele faz a curva de para a direita*/
        ATUALIZAGIRO(); //Atualiza os valores do giroscópio

        ATUALIZASENSORES(); //Atualiza os valores da placa de refletância frontal

        MOVIMENTO(forca, 'D', 'S', 0); //Curva para a direita

        if (eixox < 0) {
          /*Se por algum acaso do destino o robô pegar um valor negativo no eixo x(lembrando eixo x aceita
            somente valores entre 0 e 360) ele para e atualiza as leituras do giroscópio até conseguir
            um valor positivo*/
          PARAR(10);
          LEDESQ();  //Pisca o LED da esquerda como sinalização
          ATUALIZAGIRO(); //Atualiza as leituras do giroscópio

          while (eixox < 0) {
            /*Atualiza as leituras do giroscópio até que receba um
               valor positivo */
            ATUALIZAGIRO();
          }
        }

        if (eixox >= 1 && eixox <= 3) {
          /*Se o robô passar dos 360° ele faz uma
             segunda verificação para confirmar se
            realmente já saiu dos 360° */

          ATUALIZAGIRO();//Atualiza os valores do giroscópio

          if (eixox >= 1 && eixox <= 3) {
            /*Verifica se já passou dos 360°*/
            digitalWrite(ledc, HIGH); //LED de sinalização
            saida = true; //Variável como verdadeira para terminar a primeira parte da curva
          }
        }

        else if (procuralinha == true && eixox >= vplinha2 && lcd > 400 && lc > 400) {
          /*Se ele precisar começar a procurar a linha antes de passar dos 360° e encontrar
             ela ele encerra a curva */
          PARAR(10);
          //LEDs de Sinalização
          LEDCEN();
          LEDCEN();
          achoulinha = true; //Variável como verdadeira para encerrar a curva
        }
      }

      /*Se ele não achou a linha antes de passar pelos 360° e já passou pelos 360° ele atualiza
         a variável como falsa para continuar a curva*/
      saida = false;

      while (saida == false && achoulinha == false) {

        ATUALIZAGIRO(); //Atualiza os valores do giroscópio

        ATUALIZASENSORES(); //Atualiza os valores da placa de refletância frontal

        MOVIMENTO(forca, 'D', 'S', 0); //Curva para a Direita

        if (eixox < 0) {
          /*Se por algum acaso do destino o robô pegar um valor negativo no eixo x(lembrando eixo x aceita
            somente valores entre 0 e 360) ele para e atualiza as leituras do giroscópio até conseguir
            um valor positivo*/
          PARAR(10);
          LEDESQ();  //Pisca o LED da esquerda como sinalização
          ATUALIZAGIRO(); //Atualiza as leituras do giroscópio
          while (eixox < 0) {
            /*Atualiza as leituras do giroscópio até que receba um
               valor positivo */
            ATUALIZAGIRO();
          }
        }

        if (eixox >= giro) {
          /*Se o robô chegar na angulação desejada ele atualiza
            o giroscópio para confirmar a leitura*/
          ATUALIZAGIRO(); //Atualiza os valores do giroscópio
          if (eixox >= giro) {
            /*Se ele realmente chegou na angulação desejada ele sinaliza e encerra a curva*/
            digitalWrite(ledc, LOW);//LED de sinalização
            saida = true;//Variável como verdadeira para encerrar a curva
          }
        }
        else if (eixox >= vplinha && lcd > 400 && lc > 400) {
          /*Se o robô estiver na angulação certa e achar a linha durante a curva
            ele encerra a curva aqui*/
          PARAR(10);//Parar antes da sinalização
          //Pisca duas vezes o LED para sinalização
          LEDCEN();
          LEDCEN();
          achoulinha = true;//Variável setada como verdadeira para encerrar todas as curvas
        }
      }
    }

    //se robô não vai passar pelos 360°
    else {

      //Cálculo para verificar até que angulação o robô deve ir
      giro = valor + eixox;
      //Cálculo para definir em qual angulação o robô deve começar a procurar linha
      vplinha = giro - 15;

      while (saida == false && achoulinha == false) {
        /*Enquanto o robô não chegar na angulação desejada ou não
           encontrar a linha ele realiza a curva */
        ATUALIZAGIRO(); //Atualiza os valores do giroscópio
        ATUALIZASENSORES(); //Atualiza os valores da placa de refletância frontal
        MOVIMENTO(forca, 'D', 'S', 0); //Curva para a direita
        if (eixox < 0) {
          /*Se por algum acaso do destino o robô pegar um valor negativo no eixo x(lembrando eixo x aceita
            somente valores entre 0 e 360) ele para e atualiza as leituras do giroscópio até conseguir
            um valor positivo*/
          PARAR(10);
          LEDESQ();  //Pisca o LED da esquerda como sinalização
          ATUALIZAGIRO(); //Atualiza as leituras do giroscópio
          while (eixox < 0) {
            /*Atualiza as leituras do giroscópio até que receba um
               valor positivo */
            ATUALIZAGIRO();
          }
        }
        if (eixox >= giro) {
          /*Se o robô chegar na angulação desejada ele atualiza
              o giroscópio para confirmar a leitura*/
          ATUALIZAGIRO(); //Atualiza os valores do giroscópio
          if (eixox >= giro) {
            /*Se ele realmente chegou na angulação desejada ele sinaliza e encerra a curva*/
            digitalWrite(ledc, LOW);//LED de sinalização
            saida = true;//Variável como verdadeira para encerrar a curva
          }
        }
        else if (eixox >= vplinha && lcd > 400 && lc > 400) {
          /*Se o robô estiver na angulação correta e encontrar a linha ele
             sinaliza e terminar a curva*/
          PARAR(10); //Parar antes da sinalização
          //Pisca duas vezes o led central
          LEDCEN();
          LEDCEN();
          achoulinha = true; //Variável como verdadeira para sair da função
        }
      }
    }

    PARAR(10);
    DISPLAYGIRO();
    PARAR(10);
    MOVIMENTO(forca, 'E', 'S', 20); //Movimento Anti-inércia
    PARAR(100);
    MOVIMENTO(60, 'T', 'N', 70); //Passo para trás
    PARAR(100);
  }


  //curvas fora do seguimento de linha
  else {

    /*Atenção o giroscópio BNO055 no eixo x só aceita angulações entre 0 e 360°, por exemplo:
      quando o robô estiver em 359° e virar para a direita para aumentar mais o valor, o giroscópio
      muda para 0° e começa a aumentar a partir desse valor até chegar em 359 novamente.
      Curvas para a Direita aumentam o valor no eixo x do giroscópio*/

    int giro = 0;  //Variável que define até que grau no eixo x o robô deve ir
    int confirmagiro = 0; //Variável que confirma se o robô vai passar pelos 360° em algum momento
    bool saida = false;//Váriavel para verificar se o robô encontrou a angulação desejada

    ATUALIZAGIRO();//Atualiza os valores do giroscópio
    DISPLAYGIRO();//Mostra no Display os valores do Giroscópio


    //Redundancia para maior precisão nas leituras do giscópio
    if (eixox == 0 || eixox == 359) {
      /*Se o robô estiver em 0° ou em 359° ele deve dar uma pequena curva
        para sair dessa angulação, devido a elas serem muito "instáveis" e poderem
        atrapalhar o robô durante o início da curva*/
      MOVIMENTO(forca, 'D', 'S', 10);
      PARAR(10);
      ATUALIZAGIRO(); //Atualiza os valores do giroscópio
      DISPLAYGIRO();
      while (digitalRead(switchtras) == 0) {

      }
      delay(500);
    }

    //Cálculo para verificar se o robô vai passar pelos 360° durante a curva
    confirmagiro = 360 - eixox;


    //se robô vai passar pelo 360
    if (confirmagiro <= (valor + 2)) {
      /*Se o robô vai passar pelos 360° graus durante a curva*/
      digitalWrite(ledd, HIGH); //LED para sinalização
      /*Cálculo para definir até qual angulação o robô deve ir*/
      giro = valor - confirmagiro;

      while (saida == false) {
        /*Enquanto o robô não passar pelos 360° ele faz a curva para a direita*/

        ATUALIZAGIRO(); //Atualiza os valores do giroscópio

        MOVIMENTO(forca, 'D', 'S', 0); //Curva para a direita

        if (eixox < 0) {
          /*Se por algum acaso do destino o robô pegar um valor negativo no eixo x(lembrando eixo x aceita
            somente valores entre 0 e 360) ele para e atualiza as leituras do giroscópio até conseguir
            um valor positivo*/
          PARAR(10);
          LEDESQ();  //Pisca o LED da esquerda como sinalização
          ATUALIZAGIRO(); //Atualiza as leituras do giroscópio
          while (eixox < 0) {
            /*Atualiza as leituras do giroscópio até que receba um
               valor positivo */
            ATUALIZAGIRO();
          }
        }

        if (eixox >= 1 && eixox <= 3) {
          /*Se o robô passar dos 360° ele faz uma
            segunda verificação para confirmar se
            realmente já saiu dos 360° */

          ATUALIZAGIRO(); //Atualiza os valores do giroscópio

          if (eixox >= 1 && eixox <= 3) {
            /*Verifica se já passou dos 360°*/
            digitalWrite(ledc, HIGH); //LED de sinalização
            saida = true; //Variável como verdadeira para terminar a primeira parte da curva
          }
        }
      }

      /*Variável como falsa para ele realizar a segunda parte da curva*/
      saida = false;

      while (saida == false) {

        ATUALIZAGIRO(); //Atualiza os valores do giroscópio

        MOVIMENTO(forca, 'D', 'S', 0); //Curva para a Direita

        if (eixox < 0) {
          /*Se por algum acaso do destino o robô pegar um valor negativo no eixo x(lembrando eixo x aceita
            somente valores entre 0 e 360) ele para e atualiza as leituras do giroscópio até conseguir
            um valor positivo*/
          PARAR(10);
          LEDESQ();  //Pisca o LED da esquerda como sinalização
          ATUALIZAGIRO(); //Atualiza as leituras do giroscópio
          while (eixox < 0) {
            /*Atualiza as leituras do giroscópio até que receba um
               valor positivo */
            ATUALIZAGIRO();
          }
        }

        if (eixox >= giro) {
          /*Se o robô chegar na angulação desejada ele atualiza
            o giroscópio para confirmar a leitura*/
          ATUALIZAGIRO();//Atualiza os valores do giroscópio
          if (eixox >= giro) {
            /*Se ele realmente chegou na angulação desejada ele sinaliza e encerra a curva*/
            digitalWrite(ledc, LOW);//LED de sinalização
            saida = true;//Variável como verdadeira para encerrar a curva
          }
        }
      }
    }

    //se robô não vai passar pelo 360
    else {

      //Cálculo para verificar até que angulação o robô deve ir
      giro = valor + eixox;

      while (saida == false) {
        /*Enquanto o robô não chegar na angulação desejada ele realiza a curva */
        ATUALIZAGIRO();//Atualiza os valores do giroscópio

        MOVIMENTO(forca, 'D', 'S', 0); //Curva para a direita

        if (eixox < 0) {
          /*Se por algum acaso do destino o robô pegar um valor negativo no eixo x(lembrando eixo x aceita
            somente valores entre 0 e 360) ele para e atualiza as leituras do giroscópio até conseguir
            um valor positivo*/
          PARAR(10);
          LEDESQ();  //Pisca o LED da esquerda como sinalização
          ATUALIZAGIRO(); //Atualiza as leituras do giroscópio
          while (eixox < 0) {
            /*Atualiza as leituras do giroscópio até que receba um
               valor positivo */
            ATUALIZAGIRO();
          }
        }

        if (eixox >= giro) {
          /*Se o robô chegar na angulação desejada ele atualiza
            o giroscópio para confirmar a leitura*/
          if (eixox >= giro) {
            /*Se ele realmente chegou na angulação desejada ele sinaliza e encerra a curva*/
            digitalWrite(ledc, LOW);//LED de sinalização
            saida = true;//Variável como verdadeira para encerrar a curva
          }
        }
      }
    }

    DISPLAYGIRO();
    PARAR(10);
    MOVIMENTO(forca, 'E', 'S', 20);
    PARAR(100);
  }

}

void CURVAESQ(byte seguelinha, byte forca, int valor) {

  /*Função de curvas para a esquerda, ela utiliza o parâmetro
    seguelinha para identificar o tipo de curva, se o parâmetro
    for definido como 1 ele faz a curva seguindo as propriedades
    do segue linha, se for com o valor 0 ou 2 ele só executa a
    curva*/

  //curva para seguimento de linha
  if (seguelinha == 1) {

    MOVIMENTO(50, 'F', 'N', 100);
    PARAR(100);

    /*Atenção o giroscópio BNO055 no eixo x só aceita angulações entre 0 e 360°, por exemplo:
      quando o robô estiver em 0 e virar para a esquerda para diminuir mais o valor, o giroscópio
      muda para 360° e começa a diminuir a partir desse valor até chegar em 0 novamente.
      Curvas para a Esquerda diminuem o valor no eixo x do giroscópio*/

    int giro = 0; //Variável que define até que grau no eixo x o robô deve ir
    int confirmagiro = 0; //Variável que confirma se o robô vai passar pelos 360° em algum momento
    int vplinha = 0; //Variável para o robô saber em qual grau ele deve começar a procurar a linha

    /*Variável para o robô saber em qual grau ele deve começar a procurar a
      linha se ele for passar pelos 360° durante a curva*/
    int vplinha2 = 0;
    bool saida = false; //Variável para o robô parar de realizar a curva quando encontrar a angulação certa

    //Variável utilizada para definir se o robô deve começar a procurar a linha antes de chegar nos 360°
    bool procuralinha = false;
    bool achoulinha = false; //Variável para o robô parar a curva se encontrar linha

    ATUALIZAGIRO(); //Atualiza os valores do giroscópio
    DISPLAYGIRO(); //Mostra no Display os valores

    //reduncia para mais precisão na leitura do giroscópi
    if (eixox == 0 || eixox == 359) {
      /*Se o robô estiver em 0° ou em 359° ele deve dar uma pequena curva
         para sair dessa angulação, devido a elas serem muito "instáveis" e poderem
         atrapalhar o robô durante o início da curva*/
      MOVIMENTO(forca, 'E', 'S', 10); //Curva para a esquerda
      PARAR(10); //Para o robô
      ATUALIZAGIRO(); //Atualiza os valores do Giroscópio
      DISPLAYGIRO(); //Mostra os novos valores
      while (digitalRead(switchtras) == 0) {

      }
      delay(500);
    }

    //Cálculo para verificar se o robô vai passar pelos 360° durante a curva
    confirmagiro = eixox - valor;


    //se robô vai passar pelos 360° durante a curva
    if (confirmagiro <= 2) {

      //Cálculo para verificar até que angulação o robô deve ir após passar pelos 360°
      giro = 360 + confirmagiro;
      //Cálculo para definir em qual angulação o robô deve começar a procurar linha
      vplinha = giro + 15;

      if (vplinha >= 360) {
        /*Caso ele tenha que procurar linha antes dos 360° ele define
           ele define o valor para iniciar a procura antes dos 360° */
        vplinha2 = confirmagiro + 15;
        //Variável setada como verdadeira para o robô começar a procura da linha antes dos 360°
        procuralinha = true;
      }

      //LED de Sinalização para saber que o robô vai passar pelos 360° em algum momento
      digitalWrite(lede, HIGH);

      while (saida == false && achoulinha == false) {
        /*Enquanto o robô não passar pelos 360° ou se necessário encontrar a linha
           antes dos 360° ele faz a curva de para a esquerda*/
        ATUALIZAGIRO(); //Atualiza os valores do giroscópio

        ATUALIZASENSORES(); //Atualiza os valores da placa de refletância frontal

        MOVIMENTO(forca, 'E', 'S', 0); //Curva para a esquerda
        if (eixox < 0) {
          /*Se por algum acaso do destino o robô pegar um valor negativo no eixo x(lembrando eixo x aceita
             somente valores entre 0 e 360) ele para e atualiza as leituras do giroscópio até conseguir
             um valor positivo*/
          PARAR(10);
          LEDESQ();  //Pisca o LED da esquerda como sinalização
          ATUALIZAGIRO(); //Atualiza as leituras do giroscópio
          while (eixox < 0) {
            /*Atualiza as leituras do giroscópio até que receba um
               valor positivo */
            ATUALIZAGIRO();
          }
        }

        if (eixox <= 360 && eixox >= 355) {
          /*Se o robô passar pelos 360° atualiza as leituras no giroscópio
             para confirmar o valor lido e então sai dessa primeira parte da curva*/
          ATUALIZAGIRO(); //Atualiza as leituras do giroscópio
          if (eixox <= 360 && eixox >= 355) {
            //Segunda verificação dos valores do giroscópio
            digitalWrite(ledc, HIGH); //Led de sinalização
            saida = true; //Variável atualizada como verdadeira para sair da primeira parte da curva
          }
        }
        else if (procuralinha == true && eixox <= vplinha2 && lce > 400 && lc > 400) {
          /*Se durante a curva o robô precise começar a procurar a linha antes de passar
            pelos 360° e ele encontrar ele faz uma sinalização e acaba toda a curva */
          PARAR(10); //Parar antes da sinalização
          //Pisca duas vezes o led central
          LEDCEN();
          LEDCEN();
          achoulinha = true; //Atualiza a variável para terminar a curva
        }
      }

      /*Variável como falsa para caso o robô não tenha achado a linha ele continue
         a curva até chegar no angulação definida*/
      saida = false;

      while (saida == false && achoulinha == false) {

        ATUALIZAGIRO(); //Atualiza os valores do giroscópio
        ATUALIZASENSORES(); //Atualiza os valores da placa de refletância frontal
        MOVIMENTO(forca, 'E', 'S', 0); //Curva para a esquerda

        if (eixox < 0) {
          /*Se por algum acaso do destino o robô pegar um valor negativo no eixo x(lembrando eixo x aceita
             somente valores entre 0 e 360) ele para e atualiza as leituras do giroscópio até conseguir
             um valor positivo*/
          PARAR(10);
          LEDESQ(); //Pisca o LED da esquerda como sinalização
          ATUALIZAGIRO(); //Atualiza as leituras do giroscópio
          while (eixox < 0) {
            /*Atualiza as leituras do giroscópio até que receba um
              valor positivo */
            ATUALIZAGIRO();
          }
        }

        if (eixox <= giro) {
          /*Se o robô chegar na angulação desejada ele atualiza
             o giroscópio para confirmar a leitura*/
          ATUALIZAGIRO(); //Atualiza os valores do giroscópio
          if (eixox <= giro) {
            /*Se ele realmente chegou na angulação desejada ele sinaliza e encerra a curva*/
            digitalWrite(ledc, HIGH); //Led de sinalização
            saida = true;//Variável como verdadeira para encerrar a curva
          }
        }

        else if (eixox <= vplinha && lce > 400 && lc > 400) {
          /*Se o robô estiver na angulação certa e achar a linha durante a curva
             ele encerra a curva aqui*/
          PARAR(10); //Parar antes da sinalização
          //Pisca duas vezes o LED para sinalização
          LEDCEN();
          LEDCEN();
          achoulinha = true; //Variável setada como verdadeira para encerrar todas as curvas
        }
      }
    }

    //se robô vai passar pelos 360° durante a curva
    else {
      /*Se o robô não for passar pelos 360° durante a curva*/
      //Angulação que o robô deve ir é igual a variável confirmagiro
      giro = confirmagiro;
      vplinha = giro + 15; //Cálculo para definir em qual angulação o robô deve começar a procurar a linha
      while (saida == false && achoulinha == false) {
        /*Enquanto ele não chegar na angulação certa ou não
          encontrar a linha ele realiza a curva*/

        ATUALIZAGIRO(); //Atualiza as leituras do giroscópio
        ATUALIZASENSORES(); //Atualiza os valores da placa de refletância frontal
        MOVIMENTO(forca, 'E', 'S', 0); //Curva para a esquerda

        if (eixox < 0) {
          /*Se por algum acaso do destino o robô pegar um valor negativo no eixo x(lembrando eixo x aceita
            somente valores entre 0 e 360) ele para e atualiza as leituras do giroscópio até conseguir
            um valor positivo*/
          PARAR(10);
          LEDESQ();//Pisca o LED da esquerda como sinalização
          ATUALIZAGIRO(); //Atualiza as leituras do giroscópio
          while (eixox < 0) {
            /*Atualiza as leituras do giroscópio até que receba um
              valor positivo */
            ATUALIZAGIRO();
          }
        }
        if (eixox <= giro) {
          /*Se o robô chegar na angulação desejada ele atualiza
            o giroscópio para confirmar a leitura*/
          ATUALIZAGIRO(); //Atualiza os valores do giroscópio
          if (eixox <= giro) {
            /*Se ele realmente chegou na angulação desejada ele sinaliza e encerra a curva*/
            digitalWrite(ledc, HIGH);  //Led de sinalização
            saida = true; //Variável como verdadeira para encerrar a curva
          }
        }
        else if (eixox <= vplinha && lce > 400 && lc > 400) {
          /*Se o robô estiver na angulação certa e achar a linha durante a curva
            ele encerra a curva aqui*/
          PARAR(10); //Parar antes da sinalização
          //Pisca duas vezes o LED Central para sinalização
          LEDCEN();
          LEDCEN();
          achoulinha = true; //Variável setada como verdadeira para encerrar todas as curvas
        }
      }
    }

    PARAR(10);
    DISPLAYGIRO();
    MOVIMENTO(forca, 'D', 'S', 20);
    PARAR(100);
    MOVIMENTO(60, 'T', 'N', 70); //Passo para trás
    PARAR(100);

  }

  //curva fora do seguimento de linha
  else {

    /*Atenção o giroscópio BNO055 no eixo x só aceita angulações entre 0 e 360°, por exemplo:
      quando o robô estiver em 0 e virar para a esquerda para diminuir mais o valor, o giroscópio
      muda para 360° e começa a diminuir a partir desse valor até chegar em 0 novamente.
      Curvas para a Esquerda diminuem o valor no eixo x do giroscópio*/

    int giro = 0; //Variável que define até que grau no eixo x o robô deve ir
    int confirmagiro = 0; //Variável que confirma se o robô vai passar pelos 360° em algum momento

    bool saida = false; // Variável para o robô parar de realizar a curva quando encontrar a angulação certa

    ATUALIZAGIRO();//Atualiza os valores do giroscópio
    DISPLAYGIRO(); //Mostra no Display os valores

    //redindancia para mais precisão nas leitura do giroscópio
    if (eixox == 0 || eixox == 359) {
      /*Se o robô estiver em 0° ou em 359° ele deve dar uma pequena curva
        para sair dessa angulação, devido a elas serem muito "instáveis" e poderem
        atrapalhar o robô durante o início da curva*/

      MOVIMENTO(forca, 'E', 'S', 10); //Curva para a esquerda
      PARAR(10);//Para o robô
      ATUALIZAGIRO(); //Atualiza os valores do Giroscópio
      DISPLAYGIRO();//Mostra os novos valores
      while (digitalRead(switchtras) == 0) {

      }
      delay(500);
    }

    //Cálculo para verificar se o robô vai passar pelos 360° durante a curva
    confirmagiro = eixox - valor;

    //se robô vai passar pelos 360° durante a curva
    if (confirmagiro <= 2) {

      //Cálculo para verificar até que angulação o robô deve ir após passar pelos 360°
      giro = 360 + confirmagiro;

      //LED de Sinalização para saber que o robô vai passar pelos 360° em algum momento
      digitalWrite(lede, HIGH);

      while (saida == false) {
        /*Enquanto o robô não passar pelos 360° ele faz a curva para a esquerda*/
        ATUALIZAGIRO();//Atualiza os valores do giroscópio

        MOVIMENTO(forca, 'E', 'S', 0); //Curva para a esquerda
        if (eixox < 0) {
          /*Se por algum acaso do destino o robô pegar um valor negativo no eixo x(lembrando eixo x aceita
             somente valores entre 0 e 360) ele para e atualiza as leituras do giroscópio até conseguir
             um valor positivo*/
          PARAR(10);
          LEDESQ(); //Pisca o LED da esquerda como sinalização
          ATUALIZAGIRO();  //Atualiza as leituras do giroscópio
          while (eixox < 0) {
            /*Atualiza as leituras do giroscópio até que receba um
              valor positivo */
            ATUALIZAGIRO();
          }
        }

        if (eixox <= 360 && eixox >= 355) {
          /*Se o robô passar pelos 360° ele atualiza as leituras no giroscópio
            para confirmar o valor lido e então sai dessa primeira parte da curva*/
          ATUALIZAGIRO(); //Atualiza as leituras do giroscópio
          if (eixox <= 360 && eixox >= 355) {
            //Segunda verificação dos valores do giroscópio
            digitalWrite(ledc, HIGH); //Led de sinalização
            saida = true;  //Variável atualizada como verdadeira para sair da primeira parte da curva
          }
        }
      }

      /*Variável como falsa para o robô realizar a segunda parte(pór 360°) da curva*/
      saida = false;

      while (saida == false) {

        ATUALIZAGIRO();//Atualiza os valores do giroscópio
        MOVIMENTO(forca, 'E', 'S', 0);//Curva para a esquerda

        if (eixox < 0) {
          /*Se por algum acaso do destino o robô pegar um valor negativo no eixo x(lembrando eixo x aceita
            somente valores entre 0 e 360) ele para e atualiza as leituras do giroscópio até conseguir
            um valor positivo*/
          PARAR(10);
          LEDESQ(); //Pisca o LED da esquerda como sinalização
          ATUALIZAGIRO(); //Atualiza as leituras do giroscópio
          while (eixox < 0) {
            /*Atualiza as leituras do giroscópio até que receba um
              valor positivo */
            ATUALIZAGIRO();
          }
        }

        if (eixox <= giro) {
          /*Se o robô chegar na angulação desejada ele atualiza
            o giroscópio para confirmar a leitura*/
          ATUALIZAGIRO(); //Atualiza os valores do giroscópio
          if (eixox <= giro) {
            /*Se ele realmente chegou na angulação desejada ele sinaliza e encerra a curva*/
            digitalWrite(ledc, HIGH);//LED de sinalização
            saida = true;//Variável como verdadeira para encerrar a curva
          }
        }
      }
    }

    //se robô vai passar pelos 360° durante a curva
    else {
      /*Se o robô não for passar pelos 360° durante a curva*/
      //Angulação que o robô deve ir é igual a variável confirmagiro
      giro = confirmagiro;
      while (saida == false) {
        /*Enquanto ele não chegar na angulação certa ou não
          encontrar a linha ele realiza a curva*/
        ATUALIZAGIRO(); //Atualiza as leituras do giroscópio
        MOVIMENTO(forca, 'E', 'S', 0);  //Curva para a esquerda
        if (eixox < 0) {
          /*Se por algum acaso do destino o robô pegar um valor negativo no eixo x(lembrando eixo x aceita
            somente valores entre 0 e 360) ele para e atualiza as leituras do giroscópio até conseguir
            um valor positivo*/
          PARAR(10);
          LEDESQ();//Pisca o LED da esquerda como sinalização
          ATUALIZAGIRO(); //Atualiza as leituras do giroscópio
          while (eixox < 0) {
            /*Atualiza as leituras do giroscópio até que receba um
              valor positivo */
            ATUALIZAGIRO();
          }
        }

        if (eixox <= giro) {
          /*Se o robô chegar na angulação desejada ele atualiza
            o giroscópio para confirmar a leitura*/
          ATUALIZAGIRO();//Atualiza os valores do giroscópio
          if (eixox <= giro) {
            /*Se ele realmente chegou na angulação desejada ele sinaliza e encerra a curva*/
            digitalWrite(ledc, HIGH);//LED de sinalização
            saida = true;//Variável como verdadeira para encerrar a curva
          }
        }
      }
    }

    PARAR(10);
    DISPLAYGIRO();
    MOVIMENTO(forca, 'D', 'S', 20);
    PARAR(100);
  }

}

bool VERDE() {
  bool retorno = false; //viriável de retorno definida como false
  bool idpreto = false;//viriável para identificação de linha definida como false
  bool confirmalinha = false;
  CHECACORES();//Função CHECACORES para realizar as leituras dos LDRS
  /*Função IDCORES para comparar as leituras feitas anteriormente e caracterizar
    como verde ou outra cor*/
  IDCORES();
  if (verdedir == true && verdeesq == true) {//INICIO 180
    /*Caso o robô tenha identificado verde da direita
      e da esquerda ele vira 180 graus (beco sem saída)*/
    //Sinal luminoso para que a equipe saiba que ele está realizando 180°
    digitalWrite(ledd, HIGH);
    digitalWrite(lede, HIGH);
    digitalWrite(ledc, LOW);
    CURVAESQ(0, 83, 85);
    PARAR(50);
    MOVIMENTO(50, 'T', 'N', 100);
    PARAR(50);
    CURVAESQ(0, 83, 85);
    PARAR(50);

    //Apaga todos os leds
    digitalWrite(ledd, LOW);
    digitalWrite(ledc, LOW);
    digitalWrite(lede, LOW);
    //viriável retorno setada como true para ser retornada no final da função
    retorno = true;
  }//FIM 180

  //___________________________________________________________________________________________
  //___________________________________________________________________________________________
  //___________________________________________________________________________________________
  //___________________________________________________________________________________________
  //___________________________________________________________________________________________
  //___________________________________________________________________________________________

  else if (verdedir == true) { // && cruzdir == true) { //INICIO VERDEDIR
    /*Caso ele tenha identificado verde só para a direita ele faz a curva
       para a direita*/
    //Sinal luminoso para que a equipe saiba que ele encontrou verde da direita
    digitalWrite(ledd, HIGH);
    digitalWrite(ledc, HIGH);
    digitalWrite(lede, LOW);
    bool confirmalinha = false;
    tempo = millis();
    tempo2 = millis() - tempo;
    while (confirmalinha == false && tempo2 < 205) {
      /*Enquanto o robô não encontrar o cruzamento da direita
         ou não passar 300 milissegundos ele vai para frente*/
      MOVIMENTO(50, 'F', 'N', 0);
      ATUALIZASENSORES(); //Atualização das leituras dos sensores para as verificações
      if (ldp <= 300 && ldm <= 300) {
        confirmalinha = true;
      }
      tempo2 = millis() - tempo;
    }
    CURVADIR(1, 80, 80); //Faz a curva para a direita
    //Apaga todos os leds
    digitalWrite(ledd, LOW);
    digitalWrite(ledc, LOW);
    digitalWrite(lede, LOW);
    retorno = true;//viriável setada como true para ser retornada no final da função
  }

  else if (verdeesq == true) { //INICIO VERDE ESQ
    /*Caso ele tenha identificado verde só para a esquerda ele
       faz a curva para a esquerda */
    //Sinal luminoso para que a equipe saiba que ele encontrou verde da esquerda
    digitalWrite(ledd, LOW);
    digitalWrite(ledc, HIGH);
    digitalWrite(lede, HIGH);
    bool confirmalinha = false;
    tempo = millis();
    tempo2 = millis() - tempo;
    while (confirmalinha == false && tempo2 < 205) {
      /*Enquanto o robô não encontrar o cruzamento da esquerda
        ou não passar 300 milissegundos ele vai para frente*/
      MOVIMENTO(50, 'F', 'N', 0);
      ATUALIZASENSORES();//Atualização das leituras dos sensores para as verificações
      if (lep <= 300 && lem <= 300) {
        confirmalinha = true;
      }
      tempo2 = millis() - tempo;
    }
    CURVAESQ(1, 80, 80);//Curva para a esquerda
    //Apaga todos os leds
    digitalWrite(ledd, LOW);
    digitalWrite(ledc, LOW);
    digitalWrite(lede, LOW);
    retorno = true; //viriável setada como verdadeira para ser retornada no final da função
  }//FIM VERDE ESQ

  else {
    /*Caso ele não tenha encontrado verde
       para nenhum dos lados ele apenas apaga
       os leds e seta a viriável retorno como
       falsa para ser retornada no final da
       função*/
    digitalWrite(ledd, LOW);
    digitalWrite(ledc, LOW);
    digitalWrite(lede, LOW);
    retorno = false;
  }

  PARAR(50);
  /*Variaveis de identificação do verde setadas como falsas
     para evitar erros*/
  verdedir = false;
  verdeesq = false;


  /*Leds RGB da placa de refletância acesos apenas com
     a cor verde para que ele possa voltar a seguir linha*/
  digitalWrite(ledrgb[0], LOW);
  digitalWrite(ledrgb[1], HIGH);
  digitalWrite(ledrgb[2], LOW);
  tempo3 = 500; //Reseta as variaveis para evitar erros no segue linha
  tempo = millis(); //Reseta as variaveis para evitar erros no segue linha
  //Retorna o estado (true ou false) da viriável retorno
  return retorno;

}

//______________________________________________________ FUNÇÕES PARA REALIZAR ALINHAMENTOS _____________________________________________________________________________

void ALINHAMENTORAMPA() {
  if (ldp > 500 || ldm > 500 || lde > 500) {
    analogWrite( MDT, 0);
    analogWrite( MET, 0);
    analogWrite( MDF, 100 * 2.54);
    analogWrite( MEF, 100 * 2.54);
  }
  else if (lep > 500 || lem > 500 || led > 500) {
    analogWrite( MDT, 0);
    analogWrite( MET, 0);
    analogWrite( MDF, 100 * 2.54);
    analogWrite( MEF, 65 * 2.54);
  }
  else {
    analogWrite( MDT, 0);
    analogWrite( MET, 0);
    analogWrite( MDF, 100 * 2.54);
    analogWrite( MEF, 82 * 2.54);
  }
}

void ALINHAMENTORAMPAD() {
  ATUALIZASENSOREST ();
  ATUALIZAGIRO();

  if (ldmt > 500 && lemt > 500) {
    if (eixoz <= 15) {
      analogWrite( MDT, 60 * 2.54); //analogWrite( MDT, 30 * 2.54);
      analogWrite( MET, 50 * 2.54); //analogWrite( MET, 12 * 2.54);
      analogWrite( MDF, 0);
      analogWrite( MEF, 0);
    }
    else {
      analogWrite( MDT, 30 * 2.54); //analogWrite( MDT, 30 * 2.54);
      analogWrite( MET, 20 * 2.54); //analogWrite( MET, 12 * 2.54);
      analogWrite( MDF, 0);
      analogWrite( MEF, 0);
    }
  }


  else if (ldmt > 500 || ldpt > 500) { // || ldp > 500 || ldm > 500 || lde > 500) {
    analogWrite( MDT, 0); //analogWrite( MET, 30 * 2.54);
    analogWrite( MET, 70 * 2.54); //analogWrite( MET, 30 * 2.54);
    analogWrite( MDF, 50 * 2.54);
    analogWrite( MEF, 0);
  }
  else if (lept > 500 || lemt > 500 ) { //|| lep > 500 || lem > 500 || led > 500) {
    analogWrite( MDT, 80 * 2.54); // analogWrite( MDT, 30 * 2.54);
    analogWrite( MET, 0); //analogWrite( MET, 10 * 2.54);
    analogWrite( MDF, 0);
    analogWrite( MEF, 50 * 2.54);
  }
  else {
    if (eixoz <= 15) {
      analogWrite( MDT, 60 * 2.54); //analogWrite( MDT, 30 * 2.54);
      analogWrite( MET, 50 * 2.54); //analogWrite( MET, 12 * 2.54);
      analogWrite( MDF, 0);
      analogWrite( MEF, 0);
    }
    else {
      analogWrite( MDT, 30 * 2.54); //analogWrite( MDT, 30 * 2.54);
      analogWrite( MET, 20 * 2.54); //analogWrite( MET, 12 * 2.54);
      analogWrite( MDF, 0);
      analogWrite( MEF, 0);
    }
  }
}

void ALINHAGIRO(byte pot) {
  ATUALIZAGIRO();
  double calculoeixo = eixox - eixoxaux;

  if (calculoeixo > 180 || calculoeixo < -180) {

    //entortou para direita
    //corrigir para esquerda
    if (calculoeixo < 0 ) {
      analogWrite( MDT, 0);
      analogWrite( MET, 0);
      analogWrite( MDF, 80 * 2.54);
      analogWrite( MEF, 0);
    }

    //entortou para esquerda
    //corrigir para direita
    else {
      analogWrite( MDT, 0);
      analogWrite( MET, 0);
      analogWrite( MDF, 0);
      analogWrite( MEF, 60 * 2.54);
    }
  }

  else {
    //entortou para direita
    //corrigirr para esquerda
    if (calculoeixo > 3) {

      if (calculoeixo > 5 && estado != 1) {
        /*digitalWrite(luzD, HIGH);
          display.clearDisplay();
          ESCREVEFLOAT(calculoeixo, 20, 10, 2);
          //PARAR(50);
          LEDCEN ();
          LEDCEN ();
          LEDCEN ();*/
        analogWrite( MDT, 0);
        analogWrite( MET, 0);
        analogWrite( MDF, 80 * 2.54);
        analogWrite( MEF, 0 * 2.54);
        delay(300);
        //MOVIMENTO (70, 'F', 'N', 100);
        //PARAR(50);
        //digitalWrite(luzD, LOW);
        //display.clearDisplay();
      }
      else {

        digitalWrite(lede, HIGH);
        digitalWrite(ledd, LOW);
        digitalWrite(ledc, LOW);

        analogWrite( MDT, 0);
        analogWrite( MET, 0);
        analogWrite( MDF, 80 * 2.54);
        analogWrite( MEF, 0 * 2.54);
      }
    }

    //entortou para esquerda
    //corrigirr para direita
    else if (calculoeixo < -3)  {

      if (calculoeixo < -5 && estado != 1) {
        /*digitalWrite(luzD, HIGH);
          display.clearDisplay();
          ESCREVEFLOAT(calculoeixo, 20, 10, 2);
          PARAR(50);
          LEDCEN ();
          LEDCEN ();
          LEDCEN ();*/
        analogWrite( MDT, 0);
        analogWrite( MET, 0);
        analogWrite( MDF, 0 * 2.54);
        analogWrite( MEF, 60 * 2.54);
        delay(300);
        //MOVIMENTO (70, 'F', 'N', 100);
        //PARAR(50);
        //digitalWrite(luzD, LOW);
        //display.clearDisplay();
      }
      else {

        digitalWrite(ledd, HIGH);
        digitalWrite(lede, LOW);
        digitalWrite(ledc, LOW);

        analogWrite( MDT, 0);
        analogWrite( MET, 0);
        analogWrite( MDF, 0 * 2.54);
        analogWrite( MEF, 60 * 2.54);
      }
    }

    //não entortou
    else {

      digitalWrite(ledd, LOW);
      digitalWrite(lede, LOW);
      digitalWrite(ledc, HIGH);

      MOVIMENTO (pot, 'F', 'N', 0);

      /*analogWrite( MDT, 0);
        analogWrite( MET, 0);
        analogWrite( MDF, (pot + 10) * 2.54);
        analogWrite( MEF, (pot) * 2.54);*/
    }
  }
}
