#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>
//Programa para Método ACI, de dosagem do concreto (traço do concreto) - Corresponde ao procedimento adotado para determinação do traço de concreto, com o objetivo de atender às características essenciais que se espera do concreto no estado fresco e durante sua vida útil. São levadas em consideração as condições de preparo, de aplicação, de exposição e as especificações do projeto
//1 - Características do material selecionado:
#define MEcimento 3.15 //Massa especifica do cimento
#define MEareia 2.61 //Massa especifica da areia
#define MEbrita 2.70 //Massa especifica da brita
#define MUcimento 1.42 //Massa unitaria do cimento
#define MUareia 1.37 //Massa unitaria da areia
#define MUbrita 1.44 //Massa unitaria da brita
#define CIareia 1.016 //Coeficiente de inchamento da areia
#define CIbrita 1.005 //Coeficiente de inchamento da brita
using namespace std;

//TRECHO 1 - As funções presentes nesse trecho tem por objetivo interagir com o usuario de modo a salvar os dados referentes ao cobrimento de projeto em [mm], espaçamento de projeto entre as armaduras verticais (av) em [mm] e espaçamento de projeto entre as armaduras horizontais (ah) em [mm]. Dados estes utilizados posteriormente para calculo da dimensão máxima do agregado graudo a ser utilizado.
//Função 1 - Interage com usuario afim de obter dado de cobrimento de projeto, sendo finalizada caso o valor digitado esteja em conformidade com os valores predefinidos como limites do projeto.
void condicoesDeProjeto_cobrimento(double &cobrimento) {
  cin >> cobrimento;
  cobrimento = round(cobrimento);
  if(cobrimento<8){
    cout << endl << "O cobrimento deve ser igual ou superior a 8 [mm]" << endl;
    cout << endl << "Informe o cobrimento de projeto [mm]: ";
    return condicoesDeProjeto_cobrimento(cobrimento);
  } 
  else return;
}
//Função 2 - Interage com usuario afim de obter dado de espaçamento de projeto entre as armaduras verticais (av), sendo finalizada caso o valor digitado esteja em conformidade com os valores predefinidos como limites do projeto.
void condicoesDeProjeto_av(double &av) {
  cin >> av;
  av = round(av);
  if(av<5){
  cout <<  endl << "O espaçamento das armaduras verticais deve ser igual ou superior a 5 [mm]" << endl;
  cout << endl <<  "Informe o espaçamento de projeto entre as armaduras verticais [mm]: "; 
  return condicoesDeProjeto_av(av);
  } 
  else return;
}
//Função 3 - Interage com usuario afim de obter dado de espaçamento de projeto entre as armaduras horizontais (ah), sendo finalizada caso o valor digitado esteja em conformidade com os valores predefinidos como limites do projeto.
void condicoesDeProjeto_ah(double &ah) {
  cin >> ah;
  ah = round(ah);
  if(ah<12){
  cout <<  endl << "O espaçamento das armaduras horizontais deve ser igual ou superior a 12 [mm]" << endl;
  cout <<  endl << "Informe o espaçamento de projeto entre as armaduras horizontais [mm]: ";
  return condicoesDeProjeto_ah(ah);
  }
  else return;
}  
//FIM DO TRECHO 1

//TRECHO 2 - Com os dados de cobrimento,av,ah obtidos através das funções 1,2 e 3 do trecho 1, este trecho do codigo tem por objetivo determinar a dimensão máxima do agregado graudo a ser utilizado. Com esse valor obtemos posteriormente o consumo de agua aproximado em m³ de concreto e o Volume compactado seco de agregado graudo através de tabelas implementadas ao codigo:
//Função 4 - Implementa os valores de cobrimento, av, ah já obtidos através do trecho 1 e calcula a dimensão minima do agregado graudo, retornando o valor calculado como fim da função.
double agregadograudo(int cobrimento, int av, int ah, double &brita) {
  double dmC, dmAv, dmAh, menor, dimensaoBrita;
  //NBR 6118
  dmC = 1.2 * cobrimento;
  dmAv = 2 * av;
  dmAh = 0.83 * ah;
  menor = (dmC < dmAv) ? dmC:dmAv; //é utilizado o menor valor
  dimensaoBrita = (menor < dmAh) ? menor:dmAh;

  if (dimensaoBrita>= 9.5 && dimensaoBrita<12.5) brita = 9.5;
  else if (dimensaoBrita>= 12.5 && dimensaoBrita<19) brita = 12.5;
  else if (dimensaoBrita>=19 && dimensaoBrita<25) brita = 19;
  else if (dimensaoBrita>=25 && dimensaoBrita<32) brita = 25;   
  else if (dimensaoBrita>=32 && dimensaoBrita<37.5) brita = 32;             
  else if (dimensaoBrita>= 37.5) brita = 37.5;
  return brita;                                 
}
//FIM TRECHO 2;

//TRECHO 3 - As funções presentes nesse trecho tem por objetivo interagir com o usuario de modo a salvar os dados referentes a resistência característica do concreto à compressão (fckproj), ao abatimento do tronco de cone (slump) e determinação do coeficiente de segurança (desvioSd). Com os dados da resistencia de projeto (fckproj) e o coeficiente de segurança (desvioSd) obtidos, posteriormente será possível calcular fcj, que será o valor de resistência considerando o coeficiente de segurança. Em relação ao abatimento do tronco de cone (slump) obtemos posteriormente com o auxilio Tabela 01, o consumo aproximado de água por m³ de concreto.
//Função 5 - Interage com usuario afim de obter dado de resistência característica do concreto à compressão (fckproj), sendo finalizada caso o valor digitado esteja em conformidade com os valores predefinidos como limites do projeto.
void dadosDeResistencia_fckproj(int &fckproj) {
  cin >> fckproj;
  if((fckproj<9 || fckproj>45)){
  cout << endl << "Valor não aceito. De acordo com dados de projeto a Resistência de Projeto varia no intervalo dos numeros inteirios de [9 a 45]" << endl;
  cout << endl << "Informe a Resistência de Projeto [MPa]: ";
  return dadosDeResistencia_fckproj(fckproj);
  }
  else return;
} 
//Função 6 - Interage com usuario afim de obter dado sobre abatimento do tronco de cone (slump), sendo finalizada caso o valor digitado esteja em conformidade com os valores predefinidos como limites do projeto.
void dadosDeResistencia_slump(int &slump) {
  cin >> slump;
  if((slump <40 || slump >200)){
  cout << endl <<  "Valor não aceito. De acordo com dados de projeto o slump varia no intervalo dos numeros inteirios de [40 a 200]" << endl;
  cout << endl <<  "Informe o Slump de projeto [mm]: ";
  return dadosDeResistencia_slump(slump);
  }
  else return;
}
//Função 7 - Interage com usuario afim de obter dado sobre o coeficiente de segurança (desvioSd), sendo finalizada caso o valor digitado esteja em conformidade com os valores predefinidos como limites do projeto.
void coeficienteDeSeguranca(double &desvioSd) {
 string Sd;
 cout << "Digite a letra correspondente a uma das opções abaixo para determinar o fator de segurança:" << endl << "a) Medidas de materiais tomadas em massa." << endl << "b) Medidas de materiais tomadas em volume, com determinação de umidade." << endl << "c) Medidas de materiais tomadas em volume, sem determinação de umidade." << endl;
 cin >> Sd;
 if((Sd=="a")||(Sd=="A")) desvioSd = 4.0; 
 else if((Sd=="b")||(Sd=="B")) desvioSd = 5.5;
 else if((Sd=="c")||(Sd=="C")) desvioSd = 7.0;
 else return coeficienteDeSeguranca(desvioSd);
}
//FIM TRECHO 3.

//TRECHO 4 - A função presente nesse trecho tem por objetivo realizar o Calculo da resistencia de dosagem (FcJ) e determinação da Relação Água Cimento (Rac) através de valores dados pela curva de Abrams (GRÁFICO: Resistência [fcj] X Relação água/cimento [Rac])
//Função 8 - Implementa à função os valores da resistência característica do concreto à compressão (fckproj) e coeficiente de segurança (desvioSd) obtidos através das funções 5 e 7 presentes no trecho 3, afim de determinar a relação água cimento (Rac)  de acordo com valores obtidos pela curva de Abrams.
void resistenciaDeDosagem_relacaoAguaCimento(int fckproj, double desvioSd, double &Rac) {
  double fcj;
  int fcjI;
  fcj = fckproj + (1.65*desvioSd); 
  fcjI = round(fcj); //Este será o valor de resistência utilizado nos cálculos;

  //CONCEITO: Para a determinação da relação a/c utilizamos a Curva de Abrams (GRÁFICO: Resistência ['fcj'] X Relação água/cimento ['Rac']). Foi utilizado um 'switchcase' como ferramenta para relacionar os valores de resistência a relação a/c com auxilio da curva; 
  switch (fcjI){
    case 15: Rac = 0.800; break;
    case 16: Rac = 0.790; break;
    case 17: Rac = 0.770; break;
    case 18: Rac = 0.750; break;
    case 19: Rac = 0.740; break;
    case 20: Rac = 0.720; break;
    case 21: Rac = 0.700; break;
    case 22: Rac = 0.690; break;
    case 23: Rac = 0.680; break;
    case 24: Rac = 0.660; break;
    case 25: Rac = 0.650; break;
    case 26: Rac = 0.640; break;
    case 27: Rac = 0.630; break;
    case 28: Rac = 0.620; break;
    case 29: Rac = 0.610; break;
    case 30: Rac = 0.590; break;
    case 31: Rac = 0.580; break;
    case 32: Rac = 0.570; break;
    case 33: Rac = 0.560; break;
    case 34: Rac = 0.550; break;
    case 35: Rac = 0.540; break;
    case 36: Rac = 0.535; break;
    case 37: Rac = 0.530; break;
    case 38: Rac = 0.520; break;
    case 39: Rac = 0.510; break;
    case 40: Rac = 0.500; break;
    case 41: Rac = 0.495; break;
    case 42: Rac = 0.490; break;
    case 43: Rac = 0.480; break;
    case 44: Rac = 0.475; break;
    case 45: Rac = 0.470; break;
    case 46: Rac = 0.460; break;
    case 47: Rac = 0.450; break;
    case 48: Rac = 0.445; break;
    case 49: Rac = 0.440; break;
    case 50: Rac = 0.435; break;
    case 51: Rac = 0.430; break;
    case 52: Rac = 0.425; break;
    case 53: Rac = 0.420; break;
    case 54: Rac = 0.410; break;
    case 55: Rac = 0.405; break;
    case 56: Rac = 0.400; break;
    }
    return;
}
//FIM TRECHO 4

//TRECHO 5 - A função presente nesse trecho tem por objetivo a determinação dos dados de consumo de água (Cw) resultantes da TABELA1 na qual relaciona a dimensão máxima do agregado graudo (brita) com o abatimento do tronco de cone (slump) retornando assim o valor de Cw e calculando o valor do consumo de cimento (Cc)
//Função 9 - Implementação da função dos valores de dimensão máxima do agregado graudo (brita), abatimento do tronco de cone (slump) e relação água cimento (Rac) obtidos através das funções 4(Trecho 2), 8(Trecho 4) e 6(Trecho 3) respectivamente, além do preenchimento da Tabela 1 para obtenção do Consumo de Água (Cw) e cálculo do consumo de cimento (Cc):
void tabelaCw_valorCc(int tabela1[7][201], double brita, int slump, double Rac, double &Cw, double &Cc, int &linhadatabela1){
        //Preenchimento de Tabela 1 - Obtensao de Cw:

  //Zerando matriz para preenchimento dos dados da tabela:
  for(int i=0;i<7;i++) {
    for(int a=0; a<201; a++) {
      tabela1[i][a] = 0;
      }
    }
  
  //Preenchimento das Linhas - Linha 1 = 9.5 || Linha 2 = 12.5:
  int z = 220;
   for(int i=1;i<=2;i++) {
    for(int a=40; a<61; a++) {
    tabela1[i][a] = z;
    }
    for(int b=61,c=81,d=101,e=121,f=141,g=161,h=181;b<81 && c<101 && d<121 && e<141 && f<161 && g<181 && h<201;b++,c++,d++,e++,f++,g++,h++){
    tabela1[i][b] = z+5;
    tabela1[i][c] = z+10;
    tabela1[i][d] = z+15;
    tabela1[i][e] = z+20;
    tabela1[i][f] = z+25;
    tabela1[i][g] = z+30;
    tabela1[i][h] = z+35;
    }
    z = z-10;
  }

  //Preenchimento das Linhas - Linha 3 = 19 || Linha 4 = 25 || Linha 5 = 32 || Linha 6 = 37.5:
  z = 195;
  for(int i=3;i<=6;i++) {
    for(int a=40; a<61;a++) {
      tabela1[i][a] = z;
    }
    for(int b=61,c=81,d=101,e=121,f=141,g=161,h=181;b<81 && c<101 && d<121 && e<141 && f<161 && g<181 && h<201;b++,c++,d++,e++,f++,g++,h++) {
    tabela1[i][b] = z+5;
    tabela1[i][c] = z+10;
    tabela1[i][d] = z+15;
    tabela1[i][e] = z+20;
    tabela1[i][f] = z+25;
    tabela1[i][g] = z+30;
    tabela1[i][h] = z+35;
    }
    z = z-5;
  }
  //Fim de preenchimento da Tabela 1;
  
  //Correlacionando agregadoGraudo com a respectiva posicao na Tabela 1:
    
  if(brita == 9.5) linhadatabela1 = 1;
  else if(brita == 12.5) linhadatabela1 = 2;
  else if(brita == 19) linhadatabela1 = 3;
  else if(brita == 25) linhadatabela1 = 4;
  else if(brita == 32) linhadatabela1 = 5;
  else if(brita == 37.5) linhadatabela1 = 6;
 
  Cw = tabela1[linhadatabela1][slump]; // Consumo de Água (Cw)
  //Tendo Cw, encontramos Cc (Consumo de cimento):
  //CONCEITO: O consumo de cimento é obtido através da razão entre o consumo de água aproximado e a relação água/cimento fixada.
  Cc = Cw/Rac; // Consumo de Cimento (Cc) [Kg/m³]
  return;
}
//FIM TRECHO 5

//TRECHO 6 - As funções presentes nesse trecho tem por objetivo, interação com o usuario de forma a obter dado referente ao modulo de finura da areia (MFareia) e determinaçao do volume aproximado de agregado graudo (Vap) com o auxilio da Tabela 2, alem de calcular o consumo de agregado graúdo (Cb) e consumo de agregado miudo (Ca).
//Função 10 - Interage com usuario afim de obter dado de modulo de finura da areia (MFareia), sendo finalizada caso o valor digitado esteja em conformidade com os valores predefinidos como limites do projeto.
void agregadomiudo(double &MFareia){
  cin >> MFareia;
  if((MFareia!=1.0)&&(MFareia!=1.1)&&(MFareia!=1.2)&&(MFareia!=1.3)&&(MFareia!=1.4)&&(MFareia!=1.5)&&(MFareia!=1.6)&&(MFareia!=1.7)&&(MFareia!=1.8)&&(MFareia!=1.9)&&(MFareia!=2.0)&&(MFareia!=2.1)&&(MFareia!=2.2)&&(MFareia!=2.3)&&(MFareia!=2.4)&&(MFareia!=2.5)&&(MFareia!=2.6)&&(MFareia!=2.7)&&(MFareia!=2.8)) {
    cout <<  endl <<  "O valor digitado nao condiz com os dados tabelados, por favor digite um valor entre [1.0 e 2.8]" << endl;
    cout <<  endl << "Informe o módulo de finura da areia com precisão de uma casa decimal: ";
    return agregadomiudo(MFareia);
  }
  else if((MFareia==1.1)||(MFareia==1.3)||(MFareia==1.5)||(MFareia==1.7)||(MFareia==1.9)||(MFareia==2.1)||(MFareia==2.3)||(MFareia==2.5)||(MFareia==2.7)){ 
    MFareia = MFareia+0.1;
    return;
  }
  else return;
}
//Função 11 - Implementação da função dos valores de (linha da tabela1), consumo de água (Cw), consumo de cimento (Cc), modulo de finura da areia (MFareia), funções 9(Trecho 5), 9(Trecho 5), 9(Trecho 5) e 10(Trecho 6) respectivamente, além do preenchimento da Tabela 2 para obtenção do volume aproximado de agregado graudo (Vap)e cálculos do consumo de agregado graúdo (Cb) e consumo de agregado miudo (Ca).
void tabelaVap_valorCb_valorCa(double tabela2[7][11], int linhadatabela1, double Cw, double Cc, double MFareia, double &Vap, double &Cb, double &Ca, double &Vareia) {
  
           //INICIO DA TABELA 02:
  //Preenchimento de Tabela 2 - Obtensao de Vap: 

   //Linha 1 e 10 Colunas;
  tabela2[1][1] = 0.665;
  tabela2[1][2] = 0.654;
  double vinicial = 0.625;
  for(int i=3;i<=10;i++) {
  tabela2[1][i] = vinicial;
  vinicial = vinicial - 0.020;
  }
  //Fim;

  //Linha 1 e 10 Colunas;
  tabela2[2][1] = 0.728;
  tabela2[2][2] = 0.712;
  vinicial = 0.688;
  for(int i=3;i<=10;i++) {
  tabela2[2][i] = vinicial;
  vinicial = vinicial - 0.020;
  }
  //Fim;

  //Linha 3 e 10 Colunas;
  vinicial = 0.790;
  for(int i=1;i<=10;i++) {
  tabela2[3][i] = vinicial;
  vinicial = vinicial - 0.020;
  }
  //Fim;

  //Linha 4 e 10 Colunas;
  vinicial = 0.815;
  for(int i=1;i<=10;i++) {
  tabela2[4][i] = vinicial;
  vinicial = vinicial - 0.020;
  }
  //Fim;

  //Linha 5 e 10 Colunas;
   vinicial = 0.840;
  for(int i=1;i<=10;i++) {
  tabela2[5][i] = vinicial;
  vinicial = vinicial - 0.020;
  }
  //Fim;

  //Linha 6 e 10 Colunas;
  vinicial = 0.865;
  for(int i=1;i<=10;i++) {
  tabela2[6][i] = vinicial;
  vinicial = vinicial - 0.020;
  }
  //Fim;
  //Fim preenchimento Tabela 2; 

  //Correlacionando modulo de finura (MFareia) com a respectiva posicao na Tabela 2:
  int linhadatabela2;
 
    if(MFareia == 1.0) linhadatabela2 = 1;
    else if(fabs(MFareia - 1.2) < 0.09) linhadatabela2 = 2;
    else if(fabs(MFareia - 1.4) < 0.09) linhadatabela2 = 3;
    else if(fabs(MFareia - 1.6) < 0.09) linhadatabela2 = 4;
    else if(fabs(MFareia - 1.8) < 0.09) linhadatabela2 = 5;
    else if(fabs(MFareia - 2.0) < 0.09) linhadatabela2 = 6;
    else if(fabs(MFareia - 2.2) < 0.09) linhadatabela2 = 7;
    else if(fabs(MFareia - 2.4) < 0.09) linhadatabela2 = 8;
    else if(fabs(MFareia - 2.6) < 0.09) linhadatabela2 = 9;
    else if(fabs(MFareia - 2.8) < 0.09) linhadatabela2 = 10;
  //Fim de correlação;
  
  //Determinação do Volume de agregado graudo (Vap) dado pela Tabela 2;
  Vap = tabela2[linhadatabela1][linhadatabela2]; 

              //FIM TABELA 2

 Cb = Vap * MUbrita *1000;  //Consumo de agregado graudo [Kg/m³].
 Vareia = 1000 - ((Cc/MEcimento)+(Cb/MEbrita)+Cw); //Volume de areia.
 Ca = Vareia * MEareia; //Consumo de agregado miudo.
}
//FIM TRECHO 6

//TRECHO 7 - Traço do cimento e massa em betoneira
//Função 12 -  Implementação da função dos valores de consumo de água (Cw), consumo de cimento (Cc), consumo de brita (Cb), consumo de água (Ca), funções 9(Trecho 5), 9(Trecho 5), 10(Trecho 6) e 10(Trecho 6) respectivamente, além do calculo do traço do cimento e traço do cimento corrigido.
void tracoDoCimento(double Cw, double Cc, double Cb, double Ca, double &tracoCimento, double &tracoAreia, double &tracoBrita, double &tracoAgua, double &tracoCorrigidoAreia, double &tracoCorrigidoBrita, double &tracoCorrigidoAgua) {
  //O traco do cimento e calculado através das seguintes relações
  tracoCimento = Cc/Cc;
  tracoAreia = Ca/Cc;
  tracoBrita = Cb/Cc;
  tracoAgua = Cw/Cc;

  //É feita uma correção no traço devido a umidade presente nos materiais utilizados (areia e brita).
  double CaCORRIGIDO, CbCORRIGIDO, CwCORRIGIDO;
  CaCORRIGIDO = Ca * (CIareia);
  CbCORRIGIDO = Cb * (CIbrita);
  //O volume "extra" após a correção é abatido na quantidade de água
  CwCORRIGIDO = Cw - ((CaCORRIGIDO-Ca) + (CbCORRIGIDO-Cb));
  //Com as proporções corrigidas alteramos o traço inicial:
  tracoCorrigidoAreia = CaCORRIGIDO/Cc;
  tracoCorrigidoBrita = CbCORRIGIDO/Cc;
  tracoCorrigidoAgua = CwCORRIGIDO/Cc;
 
 return;
}
//Função 13 - Implementação da função dos valores de traco de cimento corrigido calculado através da funções 12(Trecho 7), além do calculo para proporção em massa para betoneira.
void massaParaBetoneira(double tracoCimento, double tracoCorrigidoAreia, double tracoCorrigidoBrita, double tracoCorrigidoAgua, double &volumeBet, double &massaCimento, double &massaAreia, double &massaBrita, double &massaAgua){
  cin >> volumeBet;
  if(volumeBet<=0){
   cout << endl << "Insira um valor válido" << endl;
   cout << endl << "Informe a capacidade da betoneira (em Litros): ";
   return massaParaBetoneira(tracoCimento, tracoCorrigidoAreia, tracoCorrigidoBrita, tracoCorrigidoAgua, volumeBet, massaCimento, massaAreia, massaBrita, massaAgua);
  }
  else {
    massaCimento = volumeBet / ((tracoCimento/MEcimento)+(tracoCorrigidoAreia/MEareia)+(tracoCorrigidoBrita/MEbrita)+tracoCorrigidoAgua);

    massaAreia = massaCimento*tracoCorrigidoAreia;
    massaBrita = massaCimento*tracoCorrigidoBrita;
    massaAgua = massaCimento*tracoCorrigidoAgua;
    return;
  }
}
//FIM DO TRECHO 7

//Função 14 - Interage com usuario afim de obter variavel (fimdoprograma) que será validada dentro do scopo do main() afim de saber se o usuario gostaria de iniciar um novo projeto ou finalizar o atual.
void end(int &fimdoprograma) {
  cin >> fimdoprograma;
  if((fimdoprograma!=0)&&(fimdoprograma!=1)) {
    cout << "Por favor digite um valor dentre os das opções mostradas [0 ou 1]" << endl;
    return end(fimdoprograma);
  }
  else return;
}

int main() {
  double cobrimento,av,ah; //TRECHO 1
  double brita; //TRECHO 2
  int fckproj, slump; double desvioSd; //TRECHO 3
  double Rac; //TRECHO 4
  int tabela1[7][201], linhadatabela1; double Cw, Cc; //TRECHO 5
  double MFareia, tabela2[7][11], Vap, Cb, Ca, Vareia; //TRECHO 6
  double tracoCimento, tracoAreia, tracoBrita, tracoAgua, tracoCorrigidoAreia, tracoCorrigidoBrita, tracoCorrigidoAgua; double volumeBet, massaCimento, massaAreia, massaBrita, massaAgua; //TRECHO 7

  cout << endl << "  Dosagem Experimental do Concreto - Método ACI" << endl << endl;

  //Coleta de dado (cobrimento);
  cout << "Informe um valor para o cobrimento de projeto [mm]: "; //Cobrimento = camada de concreto sobre a armadura
  condicoesDeProjeto_cobrimento(cobrimento);
 
  //Coleta de dado - variavel (av);
  cout << endl << "Informe um valor para o espaçamento de projeto entre as armaduras verticais [mm]: ";
  condicoesDeProjeto_av(av);
  
  //Coleta de dado - variavel (ah);
  cout << endl << "Informe um valor para o espaçamento de projeto entre as armaduras horizontais [mm]: "; 
  condicoesDeProjeto_ah(ah);

  //Calculo da variavel (brita) - dimensao máxima do agregado graudo; 
  cout << endl << "Dimensão máxima do agregado graúdo: " << agregadograudo(cobrimento,av,ah,brita) << " [mm]" << endl << endl;
  
  //Coleta de dado - varivael (fckproj);
  cout << "Informe a Resistência de Projeto [MPa]: ";
  dadosDeResistencia_fckproj(fckproj);
 
  //Coleta de dado - variavel (slump);
  cout << endl << "Informe o Slump de projeto [mm]: ";
  dadosDeResistencia_slump(slump);
  
  //Determinação de dado - variavel (desvioSd);
  cout <<  endl << "Conforme as condições de controle em campo:" << endl; 
  coeficienteDeSeguranca(desvioSd);
  cout << endl << "Desvio considerado: " << desvioSd << " [MPa]" << endl;
 
  //Calculo da (Rac) - relação água cimento;
  resistenciaDeDosagem_relacaoAguaCimento(fckproj, desvioSd, Rac);
 
  //Determinação da variavel (Cw) e cálculo da variável (Cc);
  tabelaCw_valorCc(tabela1, brita, slump, Rac, Cw, Cc, linhadatabela1);
  cout <<  endl << "O consumo de agua tabelado é de: " << Cw << " [L/m³ de concreto]" << endl;
  cout <<  endl << "O consumo de cimento calculado aproximado é de: " << round(Cc) << " [Kg/m³ de concreto]" << endl << endl;
 
  //Coleta de dado - variavel (MFareia);
  cout << "Prosseguindo para determinação do volume aproximado de agregado graudo para a região de Salvador [m³/m³ de concreto], com dimensão máxima caracteristica do agregado graúdo sendo: " << brita << " [mm]" << endl << endl << "Informe o módulo de finura da areia com precisão de uma casa decimal: ";
  agregadomiudo(MFareia);
 
  //Determinação da variavel (Vap) e cálculo das variáveis (Cb) e (Ca);
  tabelaVap_valorCb_valorCa(tabela2, linhadatabela1, Cw, Cc, MFareia, Vap, Cb, Ca, Vareia);
  cout << fixed << setprecision(3) << endl << "O Volume aproximado de agregado graudo (Vap) tabelado é igual a: " << Vap << endl << endl;

  //Determinação das variáveis (tracoCimento), (tracoAreia), (tracoBrita), (tracoAgua);  
  tracoDoCimento(Cw, Cc, Cb, Ca, tracoCimento, tracoAreia, tracoBrita, tracoAgua, tracoCorrigidoAreia, tracoCorrigidoBrita, tracoCorrigidoAgua);
  cout << "Traço inicial:  " << fixed << setprecision(2) << tracoCimento << " : " << tracoAreia << " : " <<  tracoBrita << " : " << tracoAgua << endl;
  cout << "Traço Corrigido:  " << fixed << setprecision(2) << tracoCimento << " : " << tracoCorrigidoAreia << " : " << tracoCorrigidoBrita << " : " << tracoCorrigidoAgua  << endl;
  	
  
  //Determinação das variáveis (volumeBet), (massaCimento), (massaAreia), (massaBrita), (massaAgua);
  cout << endl << "Informe a capacidade da betoneira (em Litros): ";  
  massaParaBetoneira(tracoCimento,  tracoCorrigidoAreia, tracoCorrigidoBrita, tracoCorrigidoAgua, volumeBet, massaCimento, massaAreia, massaBrita, massaAgua);
  cout << endl << "Proporção em massa para betoneira de " << volumeBet << " litros:  " << endl;
  cout << fixed << setprecision(2) << massaCimento << " [Kg] de Cimento " << endl << massaAreia << " [Kg] de areia " << endl << massaBrita << " [Kg] de Brita " << endl << massaAgua << " [Kg] de Água" << endl  ; 
  //Determina se o usuario gostaria de iniciar um novo projeto ou finalizar o projeto atual. 
  cout << endl << "Os cálculos foram finalizados, como deseja prosseguir?" << endl << "[0] Iniciar novo projeto." << endl << "[1] Finalizar o porgrama." << endl;
  int fimdoprograma;  //Função 14
  end(fimdoprograma);
  if(fimdoprograma==0) return main();
  else {
    cout << endl << "O programa foi finalizado!" << endl;
    return 0;
  }  
}
