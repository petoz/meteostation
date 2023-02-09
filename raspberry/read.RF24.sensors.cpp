#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <unistd.h>
#include <RF24/RF24.h>
#include <iomanip>
#include <time.h>

using namespace std;

RF24 radio(25,0);
bool radioNumber = 1;

int msg[1];
char theChar;
string strsum = "";
string temp,hum,bat,checksum;
int slength;
float tempf;
float humf;
float batf;
float checksumf;

uint8_t pipeNum = 0;

unsigned char ADDRESS2[1]= {0xb2};
unsigned char ADDRESS3[1]= {0xb3};
unsigned char ADDRESS4[1]= {0xb4};
unsigned char ADDRESS5[1]= {0xb5};

unsigned char ADDRESS1[5]  =
{
   0xb1,0x43,0x88,0x99,0x45
}; // Define a static TX address

unsigned char ADDRESS0[5]  =
{
  0xb0,0x43,0x88,0x99,0x45
}; // Define a static TX address

int fileout(void) {
  #define NAZEV "/var/log/mem/sensor.RF.Ext1.txt"
  FILE *soubor;
  remove(NAZEV);
  soubor = fopen(NAZEV, "a+");
  time_t seconds;
  seconds = time(NULL);
  fprintf(soubor,"U=%ld",seconds);
  fprintf(soubor,"&T=");
  fprintf(soubor,"%.2f", tempf);
	fprintf(soubor,"&H=");
  fprintf(soubor,"%.2f", humf);
  fprintf(soubor,"&TBAT=");
  fprintf(soubor,"%.2f\n", batf);
  fclose(soubor);
}
int fileout2(void) {
  #define NAZEV2 "/var/log/mem/sensor.RF.Ext2.txt"
  FILE *soubor;
  remove(NAZEV2);
  soubor = fopen(NAZEV2, "a+");
  time_t seconds;
  seconds = time(NULL);
  fprintf(soubor,"U=%ld",seconds);
  fprintf(soubor,"&T1=");
  fprintf(soubor,"%.2f", tempf);
  fprintf(soubor,"&H1=");
  fprintf(soubor,"%.2f", humf);
  fprintf(soubor,"&NO2_1=");
  fprintf(soubor,"%.2f\n", batf);
  fclose(soubor);
}
int fileout3(void) {
  #define NAZEV3 "/var/log/mem/sensor.RF.Ext3.txt"
  FILE *soubor;
  remove(NAZEV3);
  soubor = fopen(NAZEV3, "a+");
  time_t seconds;
  seconds = time(NULL);
  fprintf(soubor,"U=%ld",seconds);
  fprintf(soubor,"&T3=");
  fprintf(soubor,"%.2f", tempf);
  fprintf(soubor,"&H3=");
  fprintf(soubor,"%.2f", humf);
  fprintf(soubor,"&NO2_3=");
  fprintf(soubor,"%.2f\n", batf);
  fclose(soubor);
}
int fileout4(void) {
  #define NAZEV4 "/var/log/mem/sensor.RF.Ext4.txt"
  FILE *soubor;
  remove(NAZEV4);
  soubor = fopen(NAZEV4, "a+");
  time_t seconds;
  seconds = time(NULL);
  fprintf(soubor,"U=%ld",seconds);
  fprintf(soubor,"&T4=");
  fprintf(soubor,"%.2f", tempf);
  fprintf(soubor,"&H4=");
  fprintf(soubor,"%.2f", humf);
  fprintf(soubor,"&NO2_4=");
  fprintf(soubor,"%.2f\n", batf);
  fclose(soubor);
}
int fileout5(void) {
  #define NAZEV5 "/var/log/mem/sensor.RF.Ext5.txt"
  FILE *soubor;
  remove(NAZEV5);
  soubor = fopen(NAZEV5, "a+");
  time_t seconds;
  seconds = time(NULL);
  fprintf(soubor,"U=%ld",seconds);
  fprintf(soubor,"&LT1=");
  fprintf(soubor,"%.2f", tempf);
  fprintf(soubor,"&SM1=");
  fprintf(soubor,"%.2f", humf);
  fprintf(soubor,"&CO_1=");
  fprintf(soubor,"%.2f\n", batf);
  fclose(soubor);
}

int main(int argc, char** argv){
radio.begin();
radio.setRetries(15,15);
radio.setChannel(125);
radio.setDataRate(RF24_250KBPS);
radio.setPayloadSize(1);
radio.setPALevel(RF24_PA_MAX);          //for receiver maybee enough

radio.openWritingPipe(ADDRESS0);
radio.openReadingPipe(0,ADDRESS0);
radio.openReadingPipe(1,ADDRESS1);
radio.openReadingPipe(2,ADDRESS2);
radio.openReadingPipe(3,ADDRESS3);
radio.openReadingPipe(4,ADDRESS4);
radio.openReadingPipe(5,ADDRESS5);

radio.printDetails();
radio.startListening();

while (1)  // forever loop
{
 if (radio.available(&pipeNum)) {
   radio.read(msg, 1);
   theChar = msg[0];
   if (msg[0] != 2) {
     strsum = strsum + theChar;
     }
     else {
        printf("string:");  //string sample:221.70272.30wWw285.73bat
        printf("%s\n", strsum.c_str());
        slength = strsum.length();
        printf("length=");
        printf("%i\n",slength);
        if ( slength == 24 && pipeNum == 1) {
          //odstranenie chyby "terminate called after throwing an instance of 'std::out_of_range'
          //  what():  basic_string::erase: __pos (which is 12) > this->size() (which is 2)"
          // string kratsi sposoboval pad programu
          bat = strsum;
          checksum = strsum;
          strsum.erase(12,24);
          temp = strsum;
          hum = strsum;
          temp.erase(6,14);
          hum.erase(0,6);
          bat.erase(0,12);
          bat.erase(6,8);
	        tempf = ::atof(temp.c_str());
          tempf = tempf - 200;
          humf = ::atof(hum.c_str());
          humf = humf - 200;
          batf = ::atof(bat.c_str());
	        batf = batf - 200;
          checksum.erase(0,18);
	  printf("checsum after erase0,18:%s\n",checksum.c_str());
          checksumf = ::atof(checksum.c_str());
          checksumf = checksumf - 400;
          checksumf = checksumf - tempf;
	  printf("checksumf-400=%0.2f\n",checksumf);
          time_t seconds;
          seconds = time(NULL);
          printf("pipeNum=");
          printf("%i\n",pipeNum);
          printf("&T=");
          printf("%.2f",tempf);
          printf("&H=");
          printf("%.2f",humf);
          printf("&TBAT=");
          printf("%.2f\n", batf);
          if (checksumf - humf < 0.001) {
	    printf("cheskum pipe1 ok, writing...\n");
            fileout();
            strsum = "";
            }
	  if (checksumf != humf ) {
	    printf("checksum not ok\n");
            printf("checksumf=%0.12f\n",checksumf);
            printf("humf=%0.12f\n",humf);
            tempf=0;
            humf=0;
            checksumf=0;
            strsum = "";
            }
        }
        if ( slength == 24 && pipeNum == 2) {
          bat = strsum;
          checksum = strsum;
          strsum.erase(12,24);
          temp = strsum;
          hum = strsum;
          temp.erase(6,14);
          hum.erase(0,6);
          bat.erase(0,12);
          bat.erase(6,8);
	        tempf = ::atof(temp.c_str());
          tempf = tempf - 200;
          humf = ::atof(hum.c_str());
          humf = humf - 200;
          batf = ::atof(bat.c_str());
	        batf = batf - 200;
          checksum.erase(0,18);
          checksumf = ::atof(checksum.c_str());
          checksumf = checksumf - 400;
          checksumf = checksumf - tempf;
          time_t seconds;
          seconds = time(NULL);
          printf("pipeNum=");printf("%i\n",pipeNum);
          printf("&T1=");
          printf("%.2f",tempf);
          printf("&H1=");
          printf("%.2f",humf);
          printf("&NO2_1=");
          printf("%.2f\n", batf);
          if (checksumf - humf < 0.001) {
            fileout2();
            strsum = "";
            }
        }
        if ( slength == 24 && pipeNum == 3) {
          bat = strsum;
          checksum = strsum;
          strsum.erase(12,24);
          temp = strsum;
          hum = strsum;
          temp.erase(6,14);
          hum.erase(0,6);
          bat.erase(0,12);
          bat.erase(6,8);
          tempf = ::atof(temp.c_str());
          tempf = tempf - 200;
          humf = ::atof(hum.c_str());
          humf = humf - 200;
          batf = ::atof(bat.c_str());
          batf = batf - 200;
          checksum.erase(0,18);
          checksumf = ::atof(checksum.c_str());
          checksumf = checksumf - 400;
          checksumf = checksumf - tempf;
          time_t seconds;
          seconds = time(NULL);
          printf("pipeNum=");printf("%i\n",pipeNum);
          printf("&T3=");
          printf("%.2f",tempf);
          printf("&H3=");
          printf("%.2f",humf);
          printf("&NO2_3=");
          printf("%.2f\n", batf);
          if (checksumf - humf < 0.001) {
            fileout3();
            strsum = "";
            }
        }
        if ( slength == 24 && pipeNum == 4) {
          bat = strsum;
          checksum = strsum;
          strsum.erase(12,24);
          temp = strsum;
          hum = strsum;
          temp.erase(6,14);
          hum.erase(0,6);
          bat.erase(0,12);
          bat.erase(6,8);
          tempf = ::atof(temp.c_str());
          tempf = tempf - 200;
          humf = ::atof(hum.c_str());
          humf = humf - 200;
          batf = ::atof(bat.c_str());
          batf = batf - 200;
          checksum.erase(0,18);
          checksumf = ::atof(checksum.c_str());
          checksumf = checksumf - 400;
          checksumf = checksumf - tempf;
          time_t seconds;
          seconds = time(NULL);
          printf("pipeNum=");printf("%i\n",pipeNum);
          printf("&T4=");
          printf("%.2f",tempf);
          printf("&H4=");
          printf("%.2f",humf);
          printf("&NO2_4=");
          printf("%.2f\n", batf);
          if (checksumf - humf < 0.001) {
            fileout4();
            strsum = "";
            }
            strsum = "";
          }
        if ( slength == 24 && pipeNum == 5) {
          bat = strsum;
          checksum = strsum;
          strsum.erase(12,24);
          temp = strsum;
          hum = strsum;
          temp.erase(6,12);
          hum.erase(0,6);
          bat.erase(0,12);
          tempf = ::atof(temp.c_str());
          tempf = tempf - 200;
          humf = ::atof(hum.c_str());
          humf = humf - 200;
          batf = ::atof(bat.c_str());
          batf = batf - 200;
	        checksum.erase(0,18);
          checksumf = ::atof(checksum.c_str());
          checksumf = checksumf - 400;
          checksumf = checksumf - tempf;
          time_t seconds;
          seconds = time(NULL);
          printf("&LT1=");
          printf("%.2f",tempf);
          printf("&SM1=");
          printf("%.2f",humf);
          printf("&CO_1=");
          printf("%.2f\n", batf);
	  if (checksumf - humf < 0.001) {
             fileout5();
             strsum = "";
           }
        }
        if (slength != 24 ) {
          printf("bad string on pipe num=");
          printf("%i\n",pipeNum);
          strsum = "";
        }
      }
 }
 // forever loop
 }
  return 0;
}
