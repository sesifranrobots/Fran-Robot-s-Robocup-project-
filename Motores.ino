////______________________________________________________ FUNÇÕES PARA CONTROLE DOS MOTORES _________________________________________________________________
void MOTOR(char lado, char sentido) {
  switch (lado) {
    case 'D':
      switch (sentido) {

        case 'F':
          analogWrite(MDF, 60 * 2.54);
          analogWrite(MDT, 0);
          analogWrite(MEF, 0);
          analogWrite(MET, 0);
          break;


        case 'T':
          analogWrite(MDF, 0);
          analogWrite(MDT, 255);
          analogWrite(MEF, 0);
          analogWrite(MET, 0);
          break;

      }
      break;

    case 'E':
      switch (sentido) {
        case 'F':
          analogWrite(MDF, 0);
          analogWrite(MDT, 0);
          analogWrite(MEF, 55 * 2.54);
          analogWrite(MET, 0);
          break;

        case 'T':
          analogWrite(MDF, 0);
          analogWrite(MDT, 0);
          analogWrite(MEF, 0);
          analogWrite(MET, 255);
          break;
      }
      break;

    case 'P':
      analogWrite(MDF, 0);
      analogWrite(MDT, 0);
      analogWrite(MEF, 0);
      analogWrite(MET, 0);
      break;

    case 'F':
      analogWrite(MDF, 220);
      analogWrite(MDT, 0);
      analogWrite(MEF, 200);
      analogWrite(MET, 0);
      break;

    case 'T':
      analogWrite(MDF, 0);
      analogWrite(MDT, 150);
      analogWrite(MEF, 0);
      analogWrite(MET, 150);
      break;
  }
}


//______________________________________________________ FUNÇÕES PARA CONTROLE DO ENCODER ____________________________________________________________________
void CALCULOPULSOE() {

  int Lstate = digitalRead(encoderIE);

  if ((encoder_IE == LOW) && (Lstate == HIGH)) {
    int val = digitalRead(encoderDE);

    if (val == LOW && DirecaoE) {
      DirecaoE = false;

    }
    else if (val == HIGH && !DirecaoE) {
      DirecaoE = true;
    }
  }

  encoder_IE = Lstate;

  if (!DirecaoE) pulsosE--;
  else pulsosE++;
}

void CALCULOPULSOD() {

  int Lstate = digitalRead(encoderID);

  if ((encoder_ID == LOW) && (Lstate == HIGH)) {
    int val = digitalRead(encoderDD);

    if (val == LOW && DirecaoD) {
      DirecaoD = false;

    }
    else if (val == HIGH && !DirecaoD) {
      DirecaoD = true;
    }
  }

  encoder_ID = Lstate;

  if (!DirecaoD) pulsosD++;
  else pulsosD--;
}

void ANDAR_FCM(int cm) {
  digitalWrite(lede, HIGH);
  delay(cm * 10);
  digitalWrite(lede, LOW);
  delay(cm * 10);
}

void ANDAR_TCM(int cm) {
  digitalWrite(ledd, HIGH);
  delay(cm * 10);
  digitalWrite(ledd, LOW);
  delay(cm * 10);
}


//______________________________________________________ FUNÇÕES PARA CONTROLE DOS SERVO MOTORES______________________________________________________________
void MOVEGARRA(byte x, int tempo, byte desliga) {
  sgarra.attach(servogarra);
  sgarra.write(x);
  delay(tempo);

  if (desliga == 0) {
    sgarra.detach();
  }
}

void MOVECACAMBA(byte x, int tempo) {
  scacamba.attach(servocacamba);
  scacamba.write(x);
  delay(tempo);
  scacamba.detach();
}

void MOVESERVAO(byte x, int tempo) {
  servao.attach(pservao);
  servao.write(x);
  delay(tempo);
  servao.detach();
}

void MOVESERVO(char servo, byte pos, int tempo) {
  switch (servo) {
    case 'G':
      sgarra.attach(servogarra);
      sgarra.write(pos);
      delay(tempo);
      sgarra.detach();
      delay(100);
      break;

    case 'S':
      servao.attach(pservao);
      servao.write(pos);
      delay(tempo);
      servao.detach();
      delay(100);
      break;

    case 'C':
      scacamba.attach(servocacamba);
      scacamba.write(pos);
      delay(tempo);
      scacamba.detach();
      delay(100);
      break;
  }
}
