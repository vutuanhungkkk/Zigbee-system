#include <SPI.h>
#include <MFRC522.h>

#define RST_PIN         9
#define SS_PIN          10

int UID[4], i;

int ID1[4] = {86, 183, 97, 31};   // ID của thẻ từ
int RELAY = 2;

int dem = 0;

MFRC522 mfrc522(SS_PIN, RST_PIN);
 
 
 
 char state;
 
void setup()
{
 // Cài đặt các chân muốn điều khiển thành thành Ouput 
 pinMode(4, OUTPUT);
pinMode(6, OUTPUT);
 Serial.begin(9600); // Kết nối bluetooth module ở tốc độ 9600
  pinMode(RELAY, OUTPUT);
  digitalWrite(RELAY, LOW);

  SPI.begin();
  mfrc522.PCD_Init();
}
 


void loop() 
{
 
 if(Serial.available() > 0)
 {
   // Đọc giá trị nhận được từ bluetooth
   state = Serial.read();
 } else 
   state = 0;
 Serial.println(state);


switch (state) // cài đặt các chân mình muốn điều khiển tương ứng với giá trị mong muốn .VD : nhập số 1 trên điện thoai thì chân 4, tức led sáng ; nhập số 2 thì led tắt
{
  case '1':
    digitalWrite(4, HIGH); //led sáng
    break;
  case '2':
    digitalWrite(4, LOW); // led tắt
    break;
  case '3':
    { 
  analogWrite(6, 3000);//Gán tốc độ quay cho motor chạy
    }
    break;
  case '4':
  {
analogWrite(6,0); //tắt motor
  }
    break;    

  default: 
   break;
}
 
 if ( ! mfrc522.PICC_IsNewCardPresent())  
  {
    return;
  }

  if ( ! mfrc522.PICC_ReadCardSerial())
  {
    return;
  }


  for (byte i = 0; i < mfrc522.uid.size; i++) // đọc ID của thẻ
  {
    UID[i] = mfrc522.uid.uidByte[i];

  }

  if (UID[i] == ID1[i])  //nếu đọc được ID của thẻ mình đang sử dụng thì thực hiện đóng mở relay
  {
    dem++;
  if((dem % 2)==1)
    digitalWrite(RELAY, HIGH);

  else
    digitalWrite(RELAY, LOW);
  }
 
 mfrc522.PICC_HaltA(); // ngừng đọc giá trị
mfrc522.PCD_StopCrypto1();

}

