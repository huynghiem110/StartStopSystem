#define pinA0  A0             // nút nhấn được kết nối với pin 5
#define pinacc  8
#define pinon  9
#define pinst  11
#define pinA1 10
int val;                        // đọc trạng thái pinA0
int val2;                      // đọc trạng thái bị trì hoãn
int buttonState2 = 0;
int buttonState;        // giữ trạng thái nút
int mode = 0;              // led sẽ sáng ở chế độ nào
int trung =0;
int reset =0;
int enco = 2;
int dem = 0;
int rpm = 0;
float tocdo = 0;
int time7s=7000;

int timecho = 1000;
unsigned long thoigian;
unsigned long hientai;
unsigned long now;
void dem_xung()
 {
  dem++; //đếm xung
 }
void setup () 
{     
      pinMode(enco, INPUT);           // set pin to input
      pinMode(pinA0, INPUT);
      pinMode(pinA1, INPUT);// đặt nút nhấn làm ngỏ vào
      pinMode(pinacc, OUTPUT);
      pinMode(pinon, OUTPUT);
      pinMode(pinst, OUTPUT);
     attachInterrupt(0, dem_xung, RISING); 
      buttonState = digitalRead(pinA0);   // đọc trạng thái ban đầu
     Serial.begin(9600);
}

void loop ()
  {   
    
      buttonState2 = digitalRead(pinA1);
      val = digitalRead(pinA0);      // đọc giá trị đầu vào và lưu trữ nó trong val
      delay(5);                         // 5 mili giây là thời gian chờ
      val2 = digitalRead(pinA0);     // đọc lại đầu vào để kiểm tra xem có bị trả lại không
      
    
      if(buttonState2==LOW && val == val2)
      { // make sure we got 2 consistant readings!
          Serial.println("Dang nhan led ");              
        if (val != buttonState) // trạng thái nút đã thay đổi!
            {       Serial.println("Dang nhan");  
             if (val == LOW)// kiểm tra xem nút có được nhấn hay không
             {                
                     if (mode == 0) 
                      {          
                       mode = 1;  
                        Serial.println("Den 1 sang");
                                      
                      }
               else 
               {
                     if (mode == 1) 
                      {        
                       mode = 2;
                       Serial.println("Den 2 sang");

                       
                                 
                       } 
               else 
               {
                    if (mode == 2) 
                      {      
                       mode = 0;           
                      } 
              
                }
                }
               }
           
        
        buttonState = val;                // lưu trạng thái mới trong biến của chúng tôi
      } 
      }

         if(buttonState2==HIGH && val == val2)
       {       
        
        Serial.println("Dang nhan motor");                             
               if (val != buttonState) // trạng thái nút đã thay đổi!
                 {       Serial.println("Dang nhan");  
                       if (val == LOW)// kiểm tra xem nút có được nhấn hay không
                   {                  
                          if (mode == 0) 
                          {          
                             mode = 3;
                             
                             Serial.println("motor chay");                     
                           }                   

                    
        else
        { if (mode==3)
         {mode=0;
          trung=0;
         }
        }
            }
        buttonState = val;
            }
        }

        thoigian = millis();
//  Serial.print("Time: "); Serial.print(thoigian); Serial.print("   ");
//  Serial.print("Hiện tại: "); Serial.println(hientai);
  
  if (thoigian - hientai >= timecho) //millis thay delay
  {    
    hientai = thoigian;
    rpm = (dem/20)*60;    
        /*
         * Đĩa encoder có 20 xung, chúng ta đo được 120 xung/s
         * vậy lấy 120/20 = 6 vòng/s
         * ta được: 6*60 = số vòng quay / phút (RPM)
         */
    tocdo = float(dem/20)*float(0.025*3.14); // m/s
    /*
     * dem/20 là số vòng/s
     * 0.025 là đường kính vòng tròn (đơn vị: m)
     * 3.14 là số pi
     */
    //Serial.print("\t\t\t\t"); Serial.print("Số xung/s: "); Serial.println(dem);
    dem = 0; 
    Serial.print("\t\t\t\t"); Serial.print("RPM: "); Serial.print(rpm);
    Serial.print("   "); Serial.print("M/s: "); Serial.println(tocdo);
  }

  if (rpm <= 100 && mode==3)
  { 
   if(thoigian - now >= time7s)
   { now=thoigian;
    if(rpm<=100)
    {
      if(trung ==0)
      {
      //digitalWrite(pinon, HIGH);
      //digitalWrite(pinst, HIGH);     
    //delay(7000);
    //mode=0;    
    trung = 1;
      }
    else
    {
      if(trung==1)
      { trung=0;
        mode =0;
      }   
    }
    }
   }
  
  }
  
  else
  {
    now=thoigian;
  }


      
                 
      
      //Thiết lập các chế độ
      if (mode == 0) 
        {                           
          digitalWrite(pinacc, LOW);
          digitalWrite(pinon, LOW);
          digitalWrite(pinst, HIGH);
        }

      if (mode == 1) 
        { 
          digitalWrite(pinacc, HIGH);
          digitalWrite(pinon, LOW);
        }

      if (mode == 2) 
        { 
          digitalWrite(pinacc, LOW);
          digitalWrite(pinon, HIGH);
        }
      if (mode == 3) 
     { 
          digitalWrite(pinst, LOW);
          digitalWrite(pinon, HIGH); 
        }
      if (trung == 1)
      {
        digitalWrite(pinst, HIGH);
        digitalWrite(pinon, HIGH);
      }
        
      }
      
